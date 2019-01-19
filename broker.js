var mosca = require('mosca');
var settings = {
		port:1883
		}

var server = new mosca.Server(settings);

// fired whena  client is connected
server.on('clientConnected', function(client) {
    console.log('message from server == client connected : ', client.id);
  });
  
  // fired when a message is received
  server.on('published', function(packet, client) {
    console.log('message from server == Published : ', packet.payload);
  });
  
  // fired when a client subscribes to a topic
  server.on('subscribed', function(topic, client) {
    console.log('message from server == subscribed : ', topic);
  });
  
  // fired when a client subscribes to a topic
  server.on('unsubscribed', function(topic, client) {
    console.log('message from server == unsubscribed : ', topic);
   });
  
  // fired when a client is disconnecting
  server.on('clientDisconnecting', function(client) {
    console.log('message from server == clientDisconnecting : ', client.id);
  });
  
  // fired when a client is disconnected
  server.on('clientDisconnected', function(client) {
    console.log('message from server == clientDisconnected : ', client.id);
  });

server.on('ready', function(){
console.log("ready");
});