/************************************************************************
*
* MODULE: nwm_httpdigest.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:  This file contains the public prototype definitions for the
*               network HTTP digest authentication code.
*
*************************************************************************/
#ifndef nwm_HTTPDIGEST_H
#define nwm_HTTPDIGEST_H


#include "cx077.h"
#include "..\types.h"

int HTTP_DigestChallenge(char *challengeStr, http_request_data *http_rec);
USHORT HTTP_Append_Digest_Authorization_Hdr(http_request_data *http_rec);
UINT16 Str_NI_Cmp(const char *s1, const char *s2, signed short n);

void digest_calcHA2(char  * pszMethod,     // method from the request (GET/POST)
                    char  * pszDigestUri,  // requested URL
                    UINT8 chQop,           // qop-value: empty, "auth", "auth-int"
                    //char * HEntity,        // H(entity body) if qop="auth-int"
                    char  * HA1,
                    char  * pszNonce,      // nonce from server
                    char  * pszNonceCount, // 8 hex digits
                    char  * pszCNonce,     // client nonce
                    char  * Response);      // OUT: request-digest or response-digest

VOID digest_calcHA1(char  * pszUserName,
                    char  * pszRealm,
                    char  * pszPassword,
                    UINT8 chAlg,
                    char  * pszNonce,
                    char  * pszCNonce,
                    char  * SessionKey);

void UTest1_calcHA(void);
void UTest2_calcHA(void);

#endif
