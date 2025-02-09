/*#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configuration Wi-Fi
const char* ssid = "Infinix NOTE 10";
const char* password = "bent chimo";

// Configuration du serveur MQTT
const char* mqtt_server = "127.0.0.1"; // ex : "broker.hivemq.com"
const int mqtt_port = 1883;
const char* mqtt_topic = "PFA";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion Wi-Fi en cours...");
  }
  Serial.println("Connecté au Wi-Fi");

  // Configuration du serveur MQTT
  client.setServer(mqtt_server, mqtt_port);

  // Connexion au serveur MQTT
  while (!client.connected()) {
    Serial.println("Connexion au serveur MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Connecté au serveur MQTT");
    } else {
      Serial.print("Échec de connexion, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    // Reconnexion au serveur MQTT si déconnecté
    while (!client.connected()) {
      if (client.connect("ESP8266Client")) {
        Serial.println("Reconnecté au serveur MQTT");
      } else {
        Serial.print("Échec de reconnexion, rc=");
        Serial.print(client.state());
        delay(2000);
      }
    }
  }

  // Envoi d'un message au serveur MQTT
  String message = "Signal envoyé par ESP8266";
  client.publish(mqtt_topic, message.c_str());
  Serial.println("Message envoyé : " + message);

  delay(1000); // Envoie toutes les secondes
}*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Infinix NOTE 10";
const char* password = "bent chimo";
const char* mqttServer = "test.mosquitto.org" ;
const int mqttPort = 1883; // Port MQTT par défaut
const char* mqtt_topic = "PFA";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Connexion au Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnecté !");
  Serial.println(WiFi.localIP());//l'adresse IP de l'ESP8266 192.168.34.238
  client.setServer(mqttServer, mqttPort);
  if (client.connect("ESP8266_Client")) {
    Serial.println("Connecté au serveur MQTT !");
    client.publish(mqtt_topic, "only half a raw is left!!");
  } else {
    Serial.print("Échec de connexion MQTT : ");
    Serial.println(client.state());
  }
}

void loop() {
  client.loop();
}





/* ne pas oublier la biblipthèque du capteur
int calibrationTime = 30;
int ledPin = 13;                // choose the pin for the LED
int inputPin1 = D1;               // choose the input pin (for PIR sensor)
int inputPin2 = D2;
int inputPin3 = D3;
int inputPin4 = D4;
int inputPin5 = D5;
int inputPin6 = D6;
int pirState = LOW;             // we start, assuming no motion detected
int val1, val2, val3, val4, val5, val6 = 0;                    // variable for reading the pin status
void loop() {
   ... (lecture des capteurs)

   Si une condition est remplie 
   if  (val6 == HIGH){ 
    Serial.println("TOTALLY FULL");
  }
    else if (val6 == LOW) {
      Serial.println("raw 1 is empty");
     
    }
 

   else if  (val5 == LOW){
    Serial.println("ALERT raw 2 is empty only 1 raw left");
   
  }

  else if ((val3 == HIGH) && (val2 == LOW)){
    Serial.println("only half a raw is left");
  
   
}
  Serial.begin(115200);
  
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin1, INPUT);    // declare sensor as input
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(inputPin4, INPUT);
  pinMode(inputPin5, INPUT);
  pinMode(inputPin6, INPUT);

  Serial.begin(9600);

  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
}
}
void loop() {
  val1 = digitalRead(inputPin1);  // read input value
  Serial.println(val1);

  val2 = digitalRead(inputPin2);
  Serial.println(val2);

  val3 = digitalRead(inputPin3);
  Serial.println(val3);

  val4 = digitalRead(inputPin4);
  Serial.println(val4);

  val5 = digitalRead(inputPin5);
  Serial.println(val5);
  
  val6 = digitalRead(inputPin6);
  Serial.println(val6);

  

  if  (val6 == HIGH){ 
    Serial.println("TOTALLY FULL");
  }
    else if (val6 == LOW) {
      Serial.println("raw 1 is empty");
     
    }
 

   else if  (val5 == LOW){
    Serial.println("ALERT raw 2 is empty only 1 raw left");
   
  }

  else if ((val3 == HIGH) && (val2 == LOW)){
    Serial.println("only half a raw is left");
   m= "only half a raw is left" ;
  }
   else if (val4 == LOW) {
    Serial.println("no receipts");
   
  }
  if (WiFi.status() == WL_CONNECTED) { // hedhi nhotha fi west only one raw is left
    HTTPClient http;
    
    http.begin(serverUrl); // Specify the URL
    http.addHeader("Content-Type", "application/json"); // Set the content-type header if sending JSON
    
    String payload = "{\"message\":\"Hello from ESP!\"}"; // Example JSON payload
    
    int httpResponseCode = http.POST(payload); // Send the POST request
    
    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response from the server
      Serial.println("Response Code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }
    
    http.end(); // End the connection
  } else {
    Serial.println("Error: Not connected to WiFi");
  }
  
  delay(60000);*/
