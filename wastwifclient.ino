/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "g1";           // SSID of your home WiFi
char pass[] = "123456789";            // password of your home WiFi
const int trigPin = 2;
const int echoPin = 0;
unsigned long askTimer = 0;
long duration;
int distance;

IPAddress server(192,168,4,1);       // the fix IP address of the server
WiFiClient client;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);   
  
  
  // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
/*  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
  pinMode(ledPin, OUTPUT);
}

void loop () {

  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
 Serial.println("dist: ");
 Serial.println(String(distance));
  client.connect(server, 80);   // Connection to the server
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  Serial.println(".");
  client.println("<3,22,222,"+String(distance)+">");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  digitalWrite(ledPin, HIGH);
  delay(2000);                  // client will trigger the communication after two seconds
}
