

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "PONG";
const char* password = "123akumau";
const char* mqtt_server = "192.168.1.183";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int LED = 13;
int BUTTON = 12;
int temp=0;
void setup_wifi() {

  delay(10);        //delay selama  10  milisecond 
  // We start by connecting to a WiFi network
  Serial.println();    //  lakukan serial print 
  Serial.print("Connecting to ");   //lakukan serial print Conneting to 
  Serial.println(ssid);         // lakukan  serial  print SSID 

  WiFi.begin(ssid, password);    //  WIfi.begin  untuk melalkuan  connnecting ke ssid  yang sesuai

  while (WiFi.status() != WL_CONNECTED) {   //mengecek  stataus wifi sudah terkonssi belum secara berulang2  dengan delay 500 
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);   // Menapilan Topic yang di subcribe
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);    //Menapilakan payload dengan loop karna  betuknya  array charakter
  }
  Serial.println(); 

//   cood dibawah akan menceke  payload  di index pertama  atau 0 
  if ((char)payload[0] == '1') { // jika payload  yang di awal 
    digitalWrite(LED, LOW);   // maka LED akan meti 
  } else {
    digitalWrite(LED, HIGH);  // led akan menyala  jika payload di index 0 tidak 1 
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("myTopic", "hello world");
      // ... and resubscribe
      client.subscribe("myTopic");
       temp = digitalRead(BUTTON);
 if(temp==HIGH){
    Serial.println("Button Push");
        client.publish("myTopic", "Btton Push...");
        delay(500);
 }if(temp==LOW){
    Serial.println("Button Not Pus");
    delay(500);
 }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);     // Inisiasi LED  ke mode output
  pinMode(BUTTON, INPUT);
   Serial.begin(115200);    // Serial MOnitor Menggunaaknd 115200
  setup_wifi();             //menjalankan Metode  setup_wifi
  client.setServer(mqtt_server, 1883);    // Melakukan  Setup  mqqt_server atau broker  dan port 1883 
  client.setCallback(callback) ;     //setUp Callback callback  , jadi ini akan menjalan  method callback 
}

void loop() {

     // akan dijalankan secara berulang 
  if (!client.connected()) {   //Mengecek  apakah mqqt sudah terkoneksi ke client 
    reconnect(); // jika belum akan mejalankan method reconnect()
  } 
  client.loop();  //jika tidak akan membuat client  selalu loop 

 
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world ", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
   
  }
}