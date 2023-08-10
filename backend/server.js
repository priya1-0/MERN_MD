const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const fs = require('fs');
require('dotenv').config();
const express = require('express')
const cors = require('cors')
const multer = require('multer')
// const unzip = require('unzip')
const app = express();
const port = process.env.PORT || 5000;
const decompress = require("decompress");
const path = require("path");
const { exec } = require('child_process');
// const fileupload = require("express-fileupload");
const morgan = require("morgan");
const { createProxyMiddleware } = require('http-proxy-middleware');
const { parse } = require('fast-csv');
// const cheerio = require('cheerio'); 

require('dotenv').config()
// let dynname = ""
app.use(cors())
// app.use(fileupload());
// app.use(express.static("files"));
// app.use(bodyParser.json());
// app.use(bodyParser.urlencoded({ extended: true }));
// ******************************************Validate function********************************************************** //
let rows = [];
let columns =[];

fs.createReadStream(path.resolve(__dirname, 'SoupList.csv'))
  .pipe(parse({ headers: true }))
  .on('error', error => console.error(error))
  .on('headers', (headers) => {
    console.log(headers)
  })
  // .on('data', row => {
  //     console.log(row);
  //     //each row can be written to db
  //     rows.push(row);
  // })
  .on('end', rowCount => {
      console.log(`Parsed ${rowCount} rows`);
      // console.log(rows[81484].postcode); // this data can be used to write to a db in bulk
  });
// ******************************************Validate function********************************************************** //

app.get('/extract', (req,res) => {
  console.log("received extract request")
  exec('7z x C:/SBOM/SBOM_OCT_v1/backend/upload/SourceCode.zip  -oC:/SBOM/SBOM_OCT_v1/backend/Scan', (error, stdout, stderr) => {
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      
      return;
      
    }
    console.log(`stdout: ${stdout}`)
    res.send();
  });
  
// fs.createReadStream("./images/SourceCode.zip")
// .pipe(unzipper.Extract({ path: "Dest" }))
// .on("close", () => {
//   console.log("Files unzipped successfully");
// });
// const zip = new AdmZip("./images/SourceCode.zip");
// zip.extractAllTo("Dest")
// res.send(`received`)
// fs.createReadStream('path/to/archive.zip').pipe(unzip.Extract({ path: 'output/path' }));
//  decompress('./images/SourceCode.zip', 'Scan', { 
// })
// res.json({})
// decompress('./images/SourceCode.zip', 'Dest')
//   .then((files) => {
//     console.log(files);
//     res.send(`received`)
//     console.log("response sent to frontend")
//   })
//   .catch((error) => {
//     console.log(error);
//   });
})
//*********************************************************************** generate master csv ***********************************************************************************/

app.get('/mastercsv', (req,res) => {
  console.log("received csv request")
  
  exec('python parser.py', (error, stdout, stderr) => {
  
    if (stderr) {
      console.log(`stderr: ${stderr}`)
      return;
    }
    console.log(`stdout: ${stdout}`)
  });
  exec('python generate_souplist.py', (error, stdout, stderr) => {
    // if (stderr) {
    //   console.log(`stderr: ${stderr}`)
    //   return; 
    // }
    console.log(`stdout: ${stdout}`)
    res.send();
  });
  
  
 
})

//********************************************************************** generate master csv  ***********************************************************************************/

//*********************************************************** scan *********************************************************************/
app.get('/scan', (req,res) => {
  console.log("received scan request")
  exec('C:/SBOM/SBOM/dependency-check-7.1.2-release/dependency-check/bin/dependency-check.bat --scan C:/SBOM/SBOM_OCT_v1/backend/Scan --out C:/SBOM/SBOM_OCT_v1/backend --format HTML --format CSV  --enableExperimental', (error, stdout, stderr) => {
   
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`)
    res.send();
  });
})

// *********************************************** scan soup ****************************************************************************************************************//
app.get('/scansoup', (req,res) => {
  console.log("received soup scan request")
  
  exec('C:/SBOM/SBOM/cyclonedx-win-x64.exe convert --input-file C:/SBOM/SBOM_OCT_v1/backend/SoupList.csv --output-file C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.xml --output-format xml', (error, stdout, stderr) => {
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`)
    res.send(stdout);
  });
})
// *********************************************** scan soup ****************************************************************************************************************//
// *********************************************** MsSbom scan  ****************************************************************************************************************//
app.get('/MsSbomscan', (req,res) => {
  console.log("received soup scan request")
  
  exec('sbom-tool generate -b C:/SBOM/SBOM_OCT_v1/backend/Scan -bc C:/SBOM/SBOM_OCT_v1/backend/Scan -nsb https://azsxd.com -pn test -pv 1.0 -ps test', (error, stdout, stderr) => {
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`)
    res.send(stdout);
  });
})
// *********************************************** MsSbom scan ****************************************************************************************************************//
// *********************************************** Syft scan  ****************************************************************************************************************//
app.get('/syftscan', (req,res) => {
  console.log("received soup scan request")
  
  exec('syft C:/SBOM/SBOM_OCT_v1/backend/Scan -o json=C:/SBOM/SBOM_OCT_v1/backend/sbom.syft.json', (error, stdout, stderr) => {
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`)
    res.send(stdout);
  });
})
// *********************************************** Syft scan ****************************************************************************************************************//


/************************Report download ***************************************/
// app.get('/download', (req,res) => {
//   console.log("hi")
   
// })
// app.get('/download', (req, res) => {
//   res.download('C:/SBOM/SBOM_OCT_v1/backend/Output/dependency-check-report.html', function (err) {
//     console.log(err);
//   });
// })

// *******************************download dependency check report************************************************************************************** //
app.get('/downloadhtml', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/dependency-check-report.html', function (err) {
    console.log(err);
  });
})
app.get('/downloadmastercsv', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/SoupList.csv', function (err) {
    console.log(err);
  });
})
app.get('/downloadcsv', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/dependency-check-report.csv', function (err) {
    console.log(err);
  });
})
app.get('/downloadxml', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.xml', function (err) {
    console.log(err);
  });
})

// *******************************download dependency check report************************************************************************************** //
//***********Microsoft SBOM tool */
app.get('/downloadmanifest', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/Scan/_manifest/spdx_2.2/manifest.spdx.json', function (err) {
    console.log(err);
  });
})
//***********Microsoft SBOM tool */
app.get('/downloadsyft', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/sbom.syft.json', function (err) {
    console.log(err);
  });
})
// ***********************************download cyclone dx report************************************************************************************** //

// ***********************************download cyclone dx report xml************************************************************************************** //
app.get('/downloadcyclonedxxml', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.xml', function (err) {
    console.log(err);
  });
})

// ***********************************download cyclone dx report json************************************************************************************** //
app.get('/downloadcyclonedxjson', (req, res) => {
  res.download('C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.json', function (err) {
    console.log(err);
  });
})
// ***********************************download cyclone dx report************************************************************************************** //

app.get('/docdownload', (req, res) => {
  res.download('Guide of SBOM.docx', function (err) {
    console.log(err);
  });
})
// ******************************* template download ************************************************************************************** //
app.get('/templatedownload', (req, res) => {
  res.download('Sample (1).csv',function (err) {
    console.log(err);
  });
})
// ******************************* template download ************************************************************************************** //
//************************************Delete folders ********************************************************************/
app.get('/delete', (req, res) => {
  // directory path
const dir = 'C:/SBOM/SBOM_OCT_v1/backend/Scan'
const zip = 'C:/SBOM/SBOM_OCT_v1/backend/upload/SourceCode.zip'
const rephtml = 'C:/SBOM/SBOM_OCT_v1/backend/dependency-check-report.html'
const repcsv = 'C:/SBOM/SBOM_OCT_v1/backend/dependency-check-report.csv'
// const repxml = 'C:/SBOM/SBOM_OCT_v1/backend/dependency-check-report.xml'
const mascsv = 'C:/SBOM/SBOM_OCT_v1/backend/Report.csv'
const soupcsv = 'C:/SBOM/SBOM_OCT_v1/backend/upload/SoupList.csv'
const sourcexmlrep = 'C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.xml'

// delete directory recursively
fs.rm(dir, { recursive: true, force: true }, (err) => {
  if (err) {
    console.log('CONTINUE');
  }
  console.log(`${dir} is deleted!`);
});
// (async () => {
//   try {
//     await del(dir)

//     console.log(`${dir} is deleted!`)
//   } catch (err) {
//     console.error(`Error while deleting ${dir}.`)
//   }
// })()

fs.unlinkSync(zip)
console.log(`${zip} is deleted!`)
fs.unlinkSync(rephtml)
console.log(`${rephtml} is deleted!`)
fs.unlinkSync(repcsv)
console.log(`${repcsv} is deleted!`)
// fs.unlinkSync(repxml)
// console.log(`${repxml} is deleted!`)
// res.send('done')
fs.unlinkSync(mascsv)
console.log(`${mascsv} is deleted!`)
res.send('done')
fs.unlinkSync(soupcsv)
console.log(`${soupcsv} is deleted!`)
res.send('done')
fs.unlinkSync(sourcexmlrep)
console.log(`${sourcexmlrep} is deleted!`)
res.send('done')
})

//***************************Delete folders *************************************/

const uri = process.env.MONGO_URI;
/********upload file******* */
// ***********************************Soup delete******************************//
app.get('/soupdelete', (req, res) => {
  // directory path

const csvfile = 'C:/SBOM/SBOM_OCT_v1/backend/upload/SoupList.csv'
const csvrep = 'C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.xml'
// const jsonrep = 'C:/SBOM/SBOM_OCT_v1/backend/Output/cyclonedx_sbom.json'
// delete directory recursively

// (async () => {
//   try {
//     await del(dir)

//     console.log(`${dir} is deleted!`)
//   } catch (err) {
//     console.error(`Error while deleting ${dir}.`)
//   }
// })()

fs.unlinkSync(csvfile)
console.log(`${csvfile} is deleted!`)
fs.unlinkSync(csvrep)
console.log(`${csvrep} is deleted!`)
// fs.unlinkSync(jsonrep)
// console.log(`${jsonrep} is deleted!`)
res.send('done')
})

// ***********************************Soup delete******************************//


// ***********************************upload excel file******************************//
const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    console.log("hello")
    cb(null, 'C:/SBOM/SBOM_OCT_v1/backend/upload/')
  },
  filename: (req, file, cb) => {
    cb(null, file.originalname)
    
  },
})

const upload = multer({ storage: storage, 
  limits: 5000000000})

app.use(cors())

app.post('/upload', upload.single('file'), function (req, res) {
  
  res.json({})
})



// app.post('/excelfile', (req, res) => {
//     const file = req.body.file;
//     if (!file) {
//       return res.status(400).send({ message: 'No file uploaded.' });
//     }   const fileName = file.name;
//     const filePath = path.join(__dirname, 'uploads', fileName);   fs.writeFile(filePath, file.data, 'base64', (err) => {
//       if (err) {
//         return res.status(500).send({ message: 'Error saving the file.' });
//       }
//       res.status(200).send({ message: 'File uploaded successfully.' });
//     });
//   res.json({})
//   });

  // app.post('/excelfile', (req, res) => {
  //     const file = req.body.file;
  //     if (!file) {
  //       return res.status(400).send({ message: 'No file uploaded.' });
  //     }   const fileName = file.name || 'file-' + Date.now() + '.zip';
  //     const filePath = path.join(__dirname, 'uploads', fileName);   fs.writeFile(filePath, file.data, 'base64', (err) => {
  //       if (err) {
  //         return res.status(500).send({ message: 'Error saving the file.' });
  //       }
  //       res.status(200).send({ message: 'File uploaded successfully.' });
  //     });
  //   res.json({})
  //   });
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

mongoose.connect(uri, { useNewUrlParser: true}
);
const connection = mongoose.connection;
connection.once('open', () => {
  console.log("MongoDB database connection established successfully");

});
let bucket;
mongoose.connection.on("connected", () => {
  var db = mongoose.connections[0].db;
  bucket = new mongoose.mongo.GridFSBucket(db, {
    bucketName: "newBucket"
  });
  console.log(bucket);
});
//to parse json content
app.use(express.json());
//to parse body from url
app.use(express.urlencoded({
  extended: false
}));

const appdetailsRouter = require('./routes/appdetails');

app.use('/appdetails', appdetailsRouter);
// app.get('/download', (res,req)=> {
//   res.download("./C:/SBOM/Output/dependency-check-report.html")

// })

// app.post("/uploaded_file", (req, res) => {
//   let files = req.body;
//  fs.writeFile(files.fileName, files.data, "base64", function (err) {
//     if(err)
//        res.send(err);
//     else
//        res.end("Uploaded");
//    });
//  });

// app.use(express.static(path.join(__dirname, '/build')));
app.listen(port, '0.0.0.0', () => {
    console.log(`Server is running on port: ${port}`);
});
