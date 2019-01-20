var mqtt = require('mqtt')
var  server_ip  ='localhost:1883'; // server ini sesuai dengan  host ip server jika kita mejalankan di komputer yang sama maka bisa diganti dengan  localhost
// localhost:1883
var client  = mqtt.connect('mqtt://'+server_ip)
// akan dijalankan  ketika   client sudah terkonsi 
client.on('connect', function () {
// men-subcribe   topic  bernama myTopic
    client.subscribe('myTopic')
})
//akan dijalan ketika  mendapatkana pesan dari publisher
client.on('message', function (topic, message) {
    
    context = message.toString(); // mengubah  pesan  ke string 
    // menampilakan pesan  yang dikirim  oleh publisher 
    console.log(context)
})


