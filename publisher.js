var mqtt = require('mqtt');
var client  = mqtt.connect('mqtt://192.168.1.183:1883');
client.on('connect', function () {
setInterval(function() {
client.publish('myTopic', '0');
console.log('Message Sent');
}, 5000);
});