// const express = require('express')
// const app = express()

// let arrMessages = []


// app.set('view engine', 'ejs')
// app.use(express.urlencoded({ extended: true }))
// app.use(express.json())

// app.listen('3030', _ => console.log('server is listening in http://localhost:3030'))

// app.get('/', (req, res) => {
//     res.send('server works')
// })

// app.post('/sendMessage', (req, res) => {
//     let buffer = req.body.message
//     let parsedMessage = buffer
//     console.log(req.body)

//     res.render('index', { messages: arrMessages })
//     // res.render('index', { message: parsedMessage })


// })



const Net = require('net');
const port = 3030;
const server = new Net.Server();
server.listen(port, function () {
    console.log(`Server listening for connection requests on socket localhost:${port}.`);
});
server.on('connection', function (socket) {
    console.log('A new connection has been established.');
    socket.write('Hello, client.');
    socket.on('data', function (chunk) {
        console.log(`Data received from client: ${chunk.toString()}.`);
        // parseBuffer(chunk)
      
        // console.log(chunk.toJSON());
        // chunk.toJSON().data.forEach(e => {
        //     console.log(e);
        // });
    })
    socket.on('close', function () {
        console.log('Closing connection with the client');
    });
    socket.on('error', function (err) {
        console.log(`Error: ${err}`);
    });
});


function parseBuffer(buffer) {
    let message =new {}
    console.log(message);
    message.type = Buffer.from(buffer).readInt8(0)
    message.id = Buffer.from(buffer).readInt8(2)
    if (message.type == 1) {
        message.status = Buffer.from(buffer).readInt8(4)
        message.status = Buffer.from(buffer).readIntBE(4,1)
    } else {
        message.distance = Buffer.from(buffer).readFloatLE(4);
        message.angle = Buffer.from(buffer).readFloatLE(6);
        message.speed = Buffer.from(buffer).readFloatLE(10);
    }
    console.log(message);
}


