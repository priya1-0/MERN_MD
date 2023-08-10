/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2003

 MODULE: Network server digest authentication for 2490J.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$


 DESCRIPTION:

 This module contains the http server digest authentication related code.


 ENDPURPOSE

***********************************************************************
*/

/***************************************************************************
                       - Include Files -
***************************************************************************/
#include "nwm_httpdigest.h"
#include "httpcli.h"            //HTTP client header file
#include "global.h"
#include "md5_gbl.h"
#include "md5d.h"
#include "types.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "nwm_http.h"
#include "bsm_SerialPort.h"

static int challengeCount =0;
char       digestHeader[     NWC_HTML_DIGEST_HEADER_SIZE];

/**************************************************************************
                      - Private Functions -
***************************************************************************/
UINT32 prnd32(void);
void generate_cnonce(char *cnonce);
VOID CvtHex(char Bin[HASHLEN], char Hex[HASHHEXLEN]);

/**************************************************************************
 *
 * FUNCTION
 *
 *     prnd32
 *
 * DESCRIPTION
 *
 *     This routine handles Pseudo-random generation. The algorithms
 *     and code was taken from the draft of the C standards document
 *     dataed November 11, 1985.
 *
 * INPUTS
 *      None
 *
 * OUTPUTS
 *      Returns a value in the range of 0 to RAND_MAX32
 *
 **************************************************************************/
#define RAND_MAX32 1000000000ul
UINT32 prnd32(void)
{
    static UINT32 next = 1;

    if (next == 1)
    {
        int i;
        for (i = 0; i < 9; i++)
            next = next * NU_Retrieve_Clock() + 12345;
    }
    else
    {
        next = next * NU_Retrieve_Clock() + 12345;
    }

    return (next % (RAND_MAX32 + 1));
}  /* end rand routine */


/**************************************************************************
 *
 * FUNCTION
 *
 *     generate_cnonce()
 *
 * DESCRIPTION
 *
 *     This routine generates a client nonce (cnonce) as part of the
 *     digest authentication. The resultant cnonce is 32 bytes.
 *
 * INPUTS
 *      pointer to cnonce
 *
 * OUTPUTS
 *      None
 *
 **************************************************************************/
void generate_cnonce(char * cnonce)
{
    // Generate cnonce for session
    struct ranS {
        UINT32 rana;
        UINT32 ranb;
        UINT32 ranc;
        UINT32 rand;
    };
    union datum {
        char ranStr[HASHLEN];
        struct ranS S;
    };
    union datum u;

    /* calculate 128 bit cnonce */
    u.S.rana = prnd32();
    u.S.ranb = prnd32();
    u.S.ranc = prnd32();
    u.S.rand = prnd32();

    CvtHex(u.ranStr, cnonce);
    return;
}

/**************************************************************************
 *
 * FUNCTION
 *
 *     HTTP_DigestChallenge
 *
 * DESCRIPTION
 *
 *     This routine parses the digest response from the server.  Parsing
 *     starts immediately after "Authorization: Digest ".  The following
 *     values are captured:
 *
 *     value     usage
 *     -----------------------
 *     realm      required
 *     nonce      required
 *     algorithm  "MD5" or "MD5-sess"; defaults to "MD5"
 *     qop        "auth" and/or "auth-int"  Only auth supported.
 *     opaque     Echoed back to server only if the server sent it.
 *     stale      Not Used
 *
 * INPUTS
 *      char * challengeStr - response from server, expecting directive=value
 *                            pairs
 *      http_request_data *http_rec - http struct containing ptr to digest struct
 *
 * OUTPUTS
 *      None
 *
 * RETURNS
 *      SUCCESS: 0
 *      FAILURE: non-zero (parse encountered unexpected condition)
 *
 **************************************************************************/
int HTTP_DigestChallenge(char *challengeStr, http_request_data *http_rec)
{
    int  ret_val = 0;
    char * ptr;
    char * namePtr;                     // ptr to Name in challengeStr
    int  nameLength;                    // length of Name in challengeStr
    char * valuePtr;                    // ptr to Value in challengeStr
    int  valueLength;                   // length of Value in challengeStr
    char * ws      = " \r\n\t";         // whitespace chars
    char * wseq    = " \r\n\t=";        // whitespace and "="
    char * wscomma = " \r\n\t,";        // whitespace and ","
    int  schr;                          // length of spanned characters
    int  quotes;                        // quotes around value (T/F)
    char * mvalPtr;                     // ptr to multiple values of qop (auth,auth-int)
    char * qopValPtr;                   // ptr to qop value


    // challengeStr points past "Digest "
    ptr = challengeStr;

    // clear and initialize digest values
    memset(http_rec->digest, '\0', sizeof(http_digest_struct));
    http_rec->digest->algorithm  = ALGORITHM_MD5;   // Default value (RFC 2617)
    http_rec->digest_header      = digestHeader;
    strcpy(http_rec->digest_header, NWC_HTTP_DEFAULT_DIGEST_HEADER_1);
    http_rec->digest_header_size = strlen(http_rec->digest_header);
    challengeCount               = 0;

    for(;; )
    {
        schr = strspn(ptr, wscomma);   // skip whitespace & comma
        ptr += schr;

        if (*ptr == '\0')
            break;

        // get directive token in directive=value
        namePtr = ptr;
        schr    = strcspn(ptr, wseq);  // skip until whitespace or equal sign
        ptr    += schr;
        // When the parsed line stops having name=value pairs then done.
        if (*ptr == '\0')              // end of string reached, done
            break;

        nameLength = ptr - namePtr;

        if (*ptr != '=')
        {
            schr = strspn(ptr, ws);    // skip ws, expecting to find equals sign
            ptr += schr;
            if (*ptr != '=')
                break;                 // no equal sign found, done
        }

        schr = strspn(ptr, wseq);      // *ptr == '=', skip ws and equals sign
        ptr += schr;
        if (*ptr == '\0')               // no quote or value found
        {
            ret_val = 1;                // parse error
            break;
        }

        quotes = false;
        if (*ptr == '"')
        {
            ptr++;
            quotes = true;
        }

        // get value token in directive=value
        valuePtr = ptr;
        if (quotes)
        {
            // Note that when a end quote is missing a starting quote in the next
            // quoted value in the directive=value pair may be matched.  The next
            // matched token (expecting a directive) will be a value and the for
            // loop will terminate normally.since no equal sign will be found.
            schr = strcspn(ptr, "\"");
            ptr += schr;
            if (*ptr != '"')            // missing endquote
            {
                ret_val = 1;            // parse error
                break;
            }
            valueLength = ptr - valuePtr;
            ptr++;                      // inc past closing quote
        }
        else
        {
            schr        = strcspn(ptr, wscomma); // skip until whitespace or comma
            ptr        += schr;
            valueLength = ptr - valuePtr;
        }

        // For a given directive, save the value
        if (5 == nameLength && Str_NI_Cmp(namePtr, "realm", 5) == 0)
        {
            strncpy(http_rec->digest->realm, valuePtr, valueLength <= REALM_LEN ? valueLength : REALM_LEN);
            *(http_rec->digest->realm + valueLength) = 0;
        }
        else if (5== nameLength && Str_NI_Cmp(namePtr, "nonce", 5) == 0)
        {
            strncpy(http_rec->digest->nonce, valuePtr, valueLength <= NONCE_LEN ? valueLength : NONCE_LEN);
            *(http_rec->digest->nonce + valueLength) = 0;
        }
        else if (9 == nameLength && Str_NI_Cmp(namePtr, "algorithm", 9) == 0)
        {
            http_rec->digest->algorithm = ALGORITHM_SPECIFIED;
            if (8 == valueLength && Str_NI_Cmp(valuePtr, "MD5-sess", 8) == 0)
                http_rec->digest->algorithm |= ALGORITHM_MD5_SESS;        // MS IIS
            else if (3 == valueLength && Str_NI_Cmp(valuePtr, "MD5", 3) == 0)
                http_rec->digest->algorithm |= ALGORITHM_MD5;
        }
        else if (3 == nameLength && Str_NI_Cmp(namePtr, "qop", 3) == 0)
        {
            mvalPtr = valuePtr;
            while (mvalPtr < valuePtr + valueLength)
            {
                while ((mvalPtr < valuePtr + valueLength) && strchr(wscomma, *mvalPtr))
                    mvalPtr++;
                qopValPtr = mvalPtr;
                while ((mvalPtr < valuePtr + valueLength) && !strchr(wscomma, *mvalPtr))
                    mvalPtr++;
                if (4 == mvalPtr - qopValPtr && Str_NI_Cmp(qopValPtr, "auth", 4) == 0)
                    http_rec->digest->qop |= QOP_AUTH;
                else if (8 == mvalPtr - qopValPtr && Str_NI_Cmp(qopValPtr, "auth-int", 8) == 0)
                    http_rec->digest->qop |= QOP_AUTH_INT;
            }
        }
        else if (6 == nameLength && Str_NI_Cmp(namePtr, "opaque", 6) == 0)
        {
            strncpy(http_rec->digest->opaque, valuePtr, valueLength <= OPAQUE_LEN ? valueLength : OPAQUE_LEN);
            *(http_rec->digest->opaque + valueLength) = 0;
        }
        else if (5 == nameLength && Str_NI_Cmp(namePtr, "stale", 5) == 0)     // value captured but not used
        {
            if (Str_NI_Cmp(valuePtr, "true", 4) == 0)
                http_rec->digest->stale = true;
            else
                http_rec->digest->stale = false;
        }

    } // end for(;;) loop

    // cnonce for session
    generate_cnonce(http_rec->digest->cnonce);

    // Set nonce count to zero for session
    memcpy(http_rec->digest->nc, "00000000", NONCE_COUNT_LEN);

    if (http_rec->digest->qop & QOP_AUTH_INT)
    {
        // disable unsupported QOP_AUTH_INT request for Digest Authentication
        http_rec->digest->qop &= ~QOP_AUTH_INT;
    }

    /* Verify that the server has sent the necessary directives */
    if ((http_rec->digest->realm[0] == '\0') ||
        (http_rec->digest->qop && (http_rec->digest->nonce[0] == '\0')) ||
        ((http_rec->digest->algorithm == ALGORITHM_MD5_SESS) && (http_rec->digest->nonce[0] == '\0')))
    {   ret_val = 1; }

    if (ret_val == 0)
    {
        /* calculate H(A1) */
        digest_calcHA1(http_rec->user_name,
                       http_rec->digest->realm,
                       http_rec->user_password,
                       http_rec->digest->algorithm,
                       http_rec->digest->nonce,
                       http_rec->digest->cnonce,
                       http_rec->digest->ha1);

        //  Set the Digest Authentication flag.
        http_rec->digest->isReadyToAuthenticate = true;
        challengeCount++;
    }

    return ret_val;
}


/**************************************************************************
 *
 * FUNCTION
 *
 *         CvtHex
 *
 * DESCRIPTION
 *
 *     This routine converts a binary character into two hexidecimal
 *     digits as defined in RFC 2617.  For example the binary number
 *     0xa9 (byte) is converted into two characters 'a' and '9'.
 *
 * INPUTS
 *      HASH Bin - binary input array of HASHLEN
 *
 * OUTPUTS
 *      HASHHEX Hex - hexidecimal output array of HASHHEXLEN
 *
 **************************************************************************/
VOID CvtHex(char Bin[HASHLEN], char Hex[HASHHEXLEN])
{
    unsigned short i;
    unsigned char  j;

    for (i = 0; i < HASHLEN; i++)
    {
        j = (Bin[i] >> 4) & 0xf;         // upper 4 bits of byte
        if (j <= 9)
            Hex[i*2] = (j+ '0');
        else
            Hex[i*2] = (j + 'a' - 10);

        j = Bin[i] & 0xf;             // lower 4 bits of byte
        if (j <= 9)
            Hex[i*2+1] = (j+ '0');
        else
            Hex[i*2+1] = (j + 'a' - 10);
    }

    Hex[HASHHEXLEN] = '\0';
}

/**************************************************************************
 *
 * FUNCTION
 *
 *     digest_calcHA1
 *
 * DESCRIPTION
 *
 *     This routine calculates H(A1) for Digest Authenication
 *     as defined in RFC 2617.
 *
 * AUTHOR
 *
 *     Medtronic Inc.
 *
 * INPUTS
 *      char * pszUserName - username
 *      char * pszRealm    - the realm as returned by the challenge
 *      char * pszPassword - password
 *      char u8Alg         - algorithm mask returned by the challenge
 *      char * pszNonce    - the nonce as returned by the challenge
 *      char * pszCNonce   - client nonce
 *
 * OUTPUTS
 *      HASHHEX SessionKey - key to be used by digest_calcHA2()
 *
 **************************************************************************/
VOID digest_calcHA1(char  * pszUserName,
                    char  * pszRealm,
                    char  * pszPassword,
                    UINT8 chAlg,
                    char  * pszNonce,
                    char  * pszCNonce,
                    char  * SessionKey)
{
    char    HA1[HASHLEN];
    MD5_CTX Md5Ctx;
    char    Buffer[100];


    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, pszUserName, strlen(pszUserName));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszRealm, strlen(pszRealm));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszPassword, strlen(pszPassword));
    MD5Final(HA1, &Md5Ctx);

    if (chAlg & ALGORITHM_MD5_SESS)
    {
        char partialResult[HASHHEXLEN+1];
        CvtHex(HA1, partialResult);
        MD5Init(&Md5Ctx);
        MD5Update(&Md5Ctx, partialResult, HASHHEXLEN);
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        MD5Final(HA1, &Md5Ctx);
    }

    CvtHex(HA1, SessionKey);

}

/**************************************************************************
 *
 * FUNCTION
 *
 *     digest_calcHA2
 *
 * DESCRIPTION
 *
 *     This routine calculates H(A2) for Digest Authenication
 *     as defined in RFC 2617.  Integrity protection (qop=auth-int)
 *     is not supported.
 *
 * AUTHOR
 *
 *     Medtronic Inc.
 *
 * INPUTS
 *      char * pszMethod     - method from the request
 *      char * pszDigestUri  - requested URL
 *      char chQop           - qop-value: "", "auth", "auth-int"
 *      //char * HEntity     - H(entity body) if qop="auth-int"
 *      char * pszNonce      - the nonce as returned by the challenge
 *      char * pszNonceCount - string of 8 hex digits
 *      char * pszCNonce     - client nonce
 *
 * OUTPUTS
 *      char * Response      - request-digest or response-digest
 *
 **************************************************************************/
void digest_calcHA2(char  * pszMethod,     // method from the request (GET/POST)
                    char  * pszDigestUri,  // requested URL
                    UINT8 chQop,           // qop-value: empty, "auth", "auth-int"
                    //char * HEntity,        // H(entity body) if qop="auth-int"
                    char  * HA1,
                    char  * pszNonce,      // nonce from server
                    char  * pszNonceCount, // 8 hex digits
                    char  * pszCNonce,     // client nonce
                    char  * Response)      // OUT: request-digest or response-digest
{
    MD5_CTX Md5Ctx;
    char    HA2[HASHLEN+1];
    char    RespHash[HASHLEN+1];
    char    HA2Hex[HASHHEXLEN+1];
    char    Buffer[100];


    // calculate H(A2)
    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, pszMethod, strlen(pszMethod));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszDigestUri, strlen(pszDigestUri));
    //if (chQop & QOP_AUTH_INT)             // not supported!
    //{
    //    MD5Update(&Md5Ctx, ":", 1);
    //    MD5Update(&Md5Ctx, HEntity, HASHHEXLEN);
    //}
    MD5Final(HA2, &Md5Ctx);

    CvtHex(HA2, HA2Hex);

    // calculate response
    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, HA1, HASHHEXLEN);
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
    MD5Update(&Md5Ctx, ":", 1);
    if (chQop)
    {
        MD5Update(&Md5Ctx, pszNonceCount, strlen(pszNonceCount));
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        MD5Update(&Md5Ctx, ":", 1);
        if (chQop == QOP_AUTH)
            MD5Update(&Md5Ctx, "auth", strlen("auth"));
        else
            MD5Update(&Md5Ctx, "auth-int", strlen("auth-int"));
        MD5Update(&Md5Ctx, ":", 1);
    }
    MD5Update(&Md5Ctx, HA2Hex, HASHHEXLEN);
    MD5Final(RespHash, &Md5Ctx);

    CvtHex(RespHash, Response);

}

/**************************************************************************
 *
 * FUNCTION
 *
 *      HTTP_Append_Digest_Authorization_Hdr
 *
 * DESCRIPTION
 *
 *      This function appends Digest Authorization: headers to the request.
 *
 * RETURNS
 *
 *       Length of Authorization: header fields
 *
 *
 **************************************************************************/
USHORT HTTP_Append_Digest_Authorization_Hdr(http_request_data *http_rec)
{
    INT16 length =0;
    INT16 hdr_len=0;
    char  *start;
    int   temp;
    char  response_digest[HASHHEXLEN+1];


    char buff[5];
    char *requestMethod = buff;

    digestHeader[0]              = 0;
    http_rec->digest_header      = digestHeader;
    strcpy(http_rec->digest_header, NWC_HTTP_DEFAULT_DIGEST_HEADER_1);
    http_rec->digest_header_size = strlen(http_rec->digest_header);


    /* inc the nonce count string +1 */
    temp = atoi(http_rec->digest->nc);
    temp++;
    sprintf(http_rec->digest->nc, "%08x", temp);

    if(http_rec->method_type==HTTP_METHOD_GET)
        strcpy(requestMethod,"GET");
    else if(http_rec->method_type==HTTP_METHOD_POST)
        strcpy(requestMethod, "POST");


    digest_calcHA2(requestMethod,
                   http_rec->filename,
                   http_rec->digest->qop,
                   http_rec->digest->ha1,
                   http_rec->digest->nonce,
                   http_rec->digest->nc,
                   http_rec->digest->cnonce,
                   response_digest);

    start   = http_rec->digest_header+http_rec->digest_header_size;

    *start  ='\0';

    hdr_len = strlen( NWC_HTTP_AUTHORIZATION " ");
    strcpy(start,  NWC_HTTP_AUTHORIZATION " ");         /* <Authorization: > */
    length += hdr_len;

    hdr_len = strlen("Digest ");
    strcpy(start+length, "Digest ");              /* <Digest > */
    length += hdr_len;

    hdr_len = strlen("username=\"");
    strcpy(start+length, "username=\"");          /* <username="> */
    length += hdr_len;

    hdr_len = strlen(http_rec->user_name);
    strcpy(start+length, http_rec->user_name);
    length += hdr_len;

    hdr_len = strlen("\", realm=\"");
    strcpy(start+length, "\", realm=\"");         /* <", realm="> */
    length += hdr_len;

    hdr_len = strlen(http_rec->digest->realm);
    strcpy(start+length, http_rec->digest->realm);
    length += hdr_len;

    hdr_len = strlen("\", nonce=\"");
    strcpy(start+length, "\", nonce=\"");         /* <", nonce="> */
    length += hdr_len;

    hdr_len = strlen(http_rec->digest->nonce);
    strcpy(start+length, http_rec->digest->nonce);
    length += hdr_len;

    hdr_len = strlen("\", uri=\"");
    strcpy(start+length, "\", uri=\"");           /* <", uri="> */
    length += hdr_len;

    hdr_len = strlen(http_rec->filename);
    strcpy(start+length, http_rec->filename);
    length += hdr_len;


    hdr_len = strlen("\"");
    strcpy(start+length, "\"");
    length += hdr_len;

    if (http_rec->digest->algorithm & ALGORITHM_SPECIFIED)
    {
        hdr_len = strlen(", algorithm=");
        strcpy(start+length, ", algorithm="); /* <, algorithm=> <arg not quoted>*/
        length += hdr_len;

        if (http_rec->digest->algorithm & ALGORITHM_MD5_SESS)
        {
            hdr_len = strlen("MD5-sess");
            strcpy(start+length, "MD5-sess");
            length += hdr_len;

        }
        else
        {
            hdr_len = strlen("MD5");
            strcpy(start+length, "MD5");
            length += hdr_len;
        }
    }

    if (http_rec->digest->qop)                             /* <, qop="> */
    {
        hdr_len = strlen(", qop=\"");
        strcpy(start+length, ", qop=\"");
        length += hdr_len;

        hdr_len = strlen("auth");
        strcpy(start+length, "auth");
        length += hdr_len;

        if (http_rec->digest->qop & QOP_AUTH_INT)
        {
            hdr_len = strlen("-int");
            strcpy(start+length, "-int");
            length += hdr_len;
        }

        hdr_len = strlen("\", nc=");
        strcpy(start+length, "\", nc=");          /* <", nc=> <arg not quoted> */
        length += hdr_len;

        hdr_len = strlen(http_rec->digest->nc);
        strcpy(start+length, http_rec->digest->nc);
        length += hdr_len;

        hdr_len = strlen(", cnonce=\"");
        strcpy(start+length, ", cnonce=\"");      /* <, cnonce="> */
        length += hdr_len;

        hdr_len = strlen(http_rec->digest->cnonce);
        strcpy(start+length, http_rec->digest->cnonce);
        length += hdr_len;

        hdr_len = strlen("\"");
        strcpy(start+length, "\"");
        length += hdr_len;
    }

    hdr_len = strlen(", response=\"");
    strcpy(start+length, ", response=\"");      /* <", response="> */
    length += hdr_len;

    hdr_len = strlen(response_digest);
    strcpy(start+length, response_digest);
    length += hdr_len;

    if (http_rec->digest->opaque[0] != '\0')
    {
        hdr_len = strlen("\", opaque=\"");
        strcpy(start+length, "\", opaque=\"");    /* <", opaque="> */
        length += hdr_len;

        hdr_len = strlen(http_rec->digest->opaque);
        strcpy(start+length, http_rec->digest->opaque);
        length += hdr_len;
    }

    hdr_len = strlen("\"");                                             //Close the final quote
    strcpy(start+length, "\"");
    length += hdr_len;

    return(length);
}


/*************************************************************************
*
* FUNCTION
*
*     Str_NI_Cmp
*
* DESCRIPTION
*
*      Compares first n bytres of two strings (not case sensitive)
*
* INPUTS
*
*       s1  - pointer to firsst string
*       s2  - pointer to second string
*       n   - number of bytes to compare
*
* OUTPUTS
*
*   Returns:
*       0 if s1 == s2
*      -1 if s1 < s2
*       1 if s1 > s2
*
*************************************************************************/
UINT16 Str_NI_Cmp(const char *s1, const char *s2, signed short n)
{

    char  *wPtrS1, *wPtrS2;
    INT16 i;
    INT16 ret_val = 0;   /* assume that strings are equal */

    for(wPtrS1=(char *)s1, wPtrS2=(char *)s2, i = 0;
        ((*wPtrS1 != 0) && (*wPtrS2 != 0) && (i < n) );
        wPtrS1++, wPtrS2++, i++)
    {

        if (*wPtrS1 < *wPtrS2 )
        {
            if (!(  (*wPtrS1+32 == *wPtrS2) &&
                    ((*wPtrS1 >= 'A') && (*wPtrS1 <='Z')) &&
                    ((*wPtrS2 >= 'a') && (*wPtrS2 <='z'))))
            {
                /* s1 is less than s2 */
                ret_val = -1;
                break;
            }
        }
        else if (*wPtrS1 > *wPtrS2)
        {
            if(!(   (*wPtrS2+32 == *wPtrS1) &&
                    ((*wPtrS2 >= 'A') && (*wPtrS2 <= 'Z')) &&
                    ((*wPtrS1 >= 'a') && (*wPtrS1 <= 'z'))))
            {
                /* s1 is greater than s2 */
                ret_val = 1;
                break;
            }
        }
    }

    return (ret_val);
}



/*****************************************************/
//	Unit Test 1
/****************************************************/

void UTest1_calcHA(void)
{
    http_request_data http_rec;
    char              response_digest[HASHHEXLEN+1];
    char              ha1[HASHHEXLEN+1]; /* Digest H(A1) calculated value */

    // test HA1
    digest_calcHA1("Mufasa",             // username
                   "testrealm@host.com", // realm
                   "Circle Of Life",     // password
                   ALGORITHM_MD5,                  // ALGO_MD5
                   "",                   // nonce
                   "",                   // cnonce
                   ha1);


    digest_calcHA2("GET",                 // method
                   "/dir/index.html",     // uri
                   QOP_AUTH,              // QOP_AUTH (0x01)
                   ha1,
                   "dcd98b7102dd2f0e8b11d0f600bfb0c093", // nonce
                   "00000001",            // nc
                   "0a4f113b",            // cnonce
                   response_digest);

}

/****************************************************/
//		Unit Test 2
/****************************************************/

void UTest2_calcHA(void)
{
    char response_digest[HASHHEXLEN+1];
    char ha1[HASHHEXLEN+1];             /* Digest H(A1) calculated value */
    digest_calcHA1("qapp-9188-rwdahs",       // username
                   "Digest",             // realm
                   "7YjZMZ8Sl00zXfgY",   // password
                   ALGORITHM_SPECIFIED | ALGORITHM_MD5_SESS, // (0x01 | 0x04)
                   "d0be9d2da731c6010f1abc0fa4f410b4535e9b9410809a45bff20a4d82f964d79b587357aa4be93a", // nonce
                   "4fc3f142b44231cc7314fda44d502166",  // cnonce
                   ha1);
    digest_calcHA2("GET",                  // method
                   "/2490.html",     // uri
                   QOP_AUTH,               // QOP_AUTH (0x01)
                   ha1,
                   "d0be9d2da731c6010f1abc0fa4f410b4535e9b9410809a45bff20a4d82f964d79b587357aa4be93a", // nonce
                   "00000001", // nc
                   "4fc3f142b44231cc7314fda44d502166",  // cnonce
                   response_digest);
}
