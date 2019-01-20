var mqtt = require('mqtt');
var  server_ip  ='localhost:1883'; // server ini sesuai dengan  host ip server jika kita mejalankan di komputer yang sama maka bisa diganti dengan  localhost
// localhost:1883
var client  = mqtt.connect('mqtt://'+server_ip);
// akan dijalankan  ketika   client sudah terkonsi 
client.on('connect', function () {
    // setIterval  akan dijalankan  setiap 2 detik sekali 
    setInterval(function() {
        // makan akan melakukan  publish pesan  '0' dengan  topic  : myTopic
        client.publish('myTopic', '0');
        // melakukkan  console.log mendakan  pesan terkirim 
        console.log('Message Sent');
}, 2000);
});