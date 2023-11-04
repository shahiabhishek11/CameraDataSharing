  
const fs = require('fs');
const util = require('util');
const express = require('express');
const app = express();
app.use(express.json());
app.use(express.urlencoded());
app.use(express.static(__dirname+"/public") );
const port = 3000;
const path = require('path');
var PROTO_PATH = '../protos/sensorsharing.proto';

app.set('view engine', 'ejs');
var parseArgs = require('minimist');
var grpc = require('@grpc/grpc-js');
var protoLoader = require('@grpc/proto-loader');
const session = require('express-session') 
    

app.use(session({ 
  
    secret: 'dhomya', 
  
    // Forces the session to be saved 
    // back to the session store 
    resave: true, 
  
    // Forces a session that is "uninitialized" 
    // to be saved to the store 
    saveUninitialized: true
}));

// var sessionId = undefined;
const WebSocket = require('ws');

const server = new WebSocket.Server({
  port: 3001
});
let sockets = [];
// var socketMap = new Map();

var packageDefinition = protoLoader.loadSync(
  PROTO_PATH,
  {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
  });
var sensor = grpc.loadPackageDefinition(packageDefinition).sspkg;
var frames = [];
var counter = 0;
var file = fs.writeFileSync("logfile.txt", 'utf-8');
var clientId = undefined;
var confToRender = undefined;
var configToRender = undefined;
server.on('connection', function (socket) {
  sockets.push(socket);
  sockets.push("");
  // socketMap.set(sessionId,socket);
  console.log('connection received...');

});

function main() {
  var argv = parseArgs(process.argv.slice(2), {
    string: ['appIp', 'target']
  });
  var target;
  const appIp = argv.appIp;
  if (argv.target) {
    target = argv.target;
  } else {
    target = 'localhost:1999';
    // target = '10.80.2.193:1999';
  }
  console.log("grpc server target :: ", target);
  var client = new sensor.SensorSharing(target,
    grpc.credentials.createInsecure());

  app.get('/', (req, res) => {
   
    const imagePath = path.join(__dirname, 'public', 'CameraInterface.png');
    const image = fs.readFileSync(imagePath);
    // Convert image to base64
    const base64Image = image.toString('base64');

    const cameraIconPath = path.join(__dirname, 'public', 'camera-mode1.png');
    const camera = fs.readFileSync(cameraIconPath);
    // Convert image to base64
    const base64Camera = camera.toString('base64');

    const videoIconPath = path.join(__dirname, 'public', 'video-player.png'); 
    const video = fs.readFileSync(videoIconPath);
    // Convert image to base64
    const base64Video = video.toString('base64');

    const captureIconPath = path.join(__dirname, 'public', 'capture.png'); 
    const capture = fs.readFileSync(captureIconPath);
    // Convert image to base64
    const base64Capture = capture.toString('base64');

    const playIconPath = path.join(__dirname, 'public', 'play.png'); 
    const play = fs.readFileSync(playIconPath);
    // Convert image to base64
    const base64Play = play.toString('base64');

    const pauseIconPath = path.join(__dirname, 'public', 'pause.png'); 
    const pause = fs.readFileSync(pauseIconPath);
    // Convert image to base64
    const base64Pause = pause.toString('base64');

    var request = sensor.Request;

    var reg = client.register_(request, function (err, response) {
      //console.log("registration is successful");
      console.log("client ID " + response);
      confToRender = (response.cameraList);
      clientId = response.clientId;
      req.session.userName = clientId;
      console.log("// ---- confToRender ---- //");
      console.log(confToRender);
      console.log("// ---- ------------ ---- //");
      request.clientId = response.clientId;
      console.log("Client Id : "+clientId);
      fs.readFile('./cache.dbc', 'utf8', (err, data) => {
        if (err) {
          //console.error(err);
          return;
        }
        if (data.length == 0) {
          var conf = client.getConfiguration(request, function (err, response) {
            //console.log("Response conf " + JSON.stringify(response.conf[0]));
            configToRender = response.conf;
            console.log("// ---- configToRender ---- //");
            console.log(configToRender);
            console.log("// ---- ------------ ---- //");
            //  fs.truncate('./cache.dbc', 0, function(){//console.log('done')})
            // fs.writeFileSync('./cache.dbc', JSON.stringify(response.conf), 'utf-8');

            res.render('index', { appIp,base64Camera, base64Video, base64Image, base64Capture,base64Play, base64Pause, confToRender, configToRender });


          });

        }
        else {

          var confObj = JSON.parse(data);

          var configurations = sensor.Configurations;

          //Possible point of error:confObj is of type [object object],[object object]
          configurations.conf = confObj;
          // request.clientId = clientId;
          //console.log("Configuration : "+JSON.stringify(configurations.conf));
          request.configlist = configurations;
          configToRender = confObj;
          client.setConfiguration(request, function (err, response) {
            if (err)
              console.log('error : ' + err);
            else
              console.log('Response : ' + JSON.stringify(response));
          });

          res.render('index', {appIp, base64Camera, base64Video, base64Image, base64Capture, base64Play,base64Pause, confToRender, configToRender });
        }

        // //console.log("Config obj sent to render:"+ configToRender);
      });
    });
  });


  app.post('/setconfig', (req, res) => {
    // console.log(req.sessionID);
    var request = sensor.Request;
    //console.log('Request body : '+JSON.stringify(req.body[0]));
    configToRender = req.body;
    localArr = [];
    var configurations = sensor.Configurations;
    configToRender.forEach(element => {
      if(element.cameraState == "true"){
          localArr.push(element);
          console.log(element);
        }
      });
      configurations.conf = localArr;
      // configurations.conf = configToRender;
      request.clientId = req.session.userName;
      console.log(request.clientId);
    //console.log("Configuration : "+JSON.stringify(configurations.conf));
    request.configlist = configurations;
    // fs.writeFileSync('./cache.dbc',JSON.stringify(configToRender) , 'utf-8');
    client.setConfiguration(request, function (err, response) {
      if (err)
        console.log('error : ' + err);
      else {

        console.log('Response : ' + JSON.stringify(response));
        res.end();
      }

    });


  });

  app.get('/image*', (req, res) => {
    // console.log(req.sessionID);
    console.log("Client Id from capture image "+req.session.userName);
    var request = sensor.Request;
    console.log("cam id = ", req.query.cam);
    request.cameraId = req.query.cam;
    request.clientId = req.session.userName;
    const camBuf = Buffer.from(request.cameraId);
    var img = client.captureImage(request, function (err, response) {

      const buff = Buffer.concat([response.rawBuffer, camBuf]);
      // socketMap.get(req.sessionID).send(buff);
       sockets[req.session.userName].send(buff);
      res.end();
      
    });
  });
  
  app.get('/startStream*', (req, res) => {
    // console.log(req.sessionID);
    console.log(clientId);
    var request = sensor.Request;
    request.clientId = req.session.userName;
    request.cameraId = req.query.cam;
    console.log(req.query.cam);
    var video = client.startStream(request);

    const camBuf = Buffer.from(request.cameraId);
    video.on('data', (args) => {
      const buff = Buffer.concat([args.rawBuffer, camBuf]);
      console.log("User name from start stream"+req.session.userName)
      sockets[req.session.userName].send(buff);
      //console.log("in the on-data function");
    });

    video.on('end', function (arg) {
      //console.log(" in the end function");
      res.end();
    });

    video.on('error', function (arg) {
      //console.log(" in the error function");
      res.end();
    });

    video.on('status', function (arg) {
      //console.log(" in the status function");
    });

  });

  app.get('/stopStream*', (req, res) => {
    //console.log("inside stopStream...");
    var request = sensor.Request;
    request.clientId = req.session.userName;
    request.cameraId = req.query.cam;
    res.writeHead(200, { 'Content-Type': 'text' });
    client.stopStream(request, (err, response) => {
      //console.log("executed stopStream...");
      res.end();
    });
  });
  app.get('/deregister', (req, res) => {
    //console.log('Inside deregister');
    var request = sensor.Request;
    request.cameraList = confToRender;

    var img = client.deregister(request, function (err, response) {
      res.end();

      //console.log(response);
    });
  });

  //Need to update camera state in the conf file too
  app.get('/toggleCamera', (req, res) => {
    var request = sensor.Request;
    var configuration = sensor.Configurations;
    request.clientId = req.session.userName;
    request.cameraId = req.query.camId;
    configToRender.forEach(element => {
      if (element.cameraId == req.query.camId) {
       // console.log("Camera state from toggle API ::BEFORE:: "+element.cameraState);
        element.cameraState = !element.cameraState;
       // console.log("Camera state from toggle API ::AFTER:: "+element.cameraState);
        fs.writeFileSync('./cache.dbc',JSON.stringify(configToRender) , 'utf-8');
        configuration.conf=configToRender;
        request.configlist = configuration;
        client.toggleCameraState(request, function (err, response) {
          res.end();
        });
      } 
    });
    // console.log(configToRender);
    // console.log("index: "+index);
    // request.configlist = configToRender[index];
    // console.log(request.configlist);
    // client.toggleCameraState(request, function (err, response) {
    //   res.end();
    // });
  })

}

main();


app.listen(port, () => {
  // console.log(`Server running on port ${port}`);
});