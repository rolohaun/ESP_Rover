#include <ESP8266WiFi.h>
#include <espnow.h>

//int MotorA1 = 5; 
//int MotorA2 = 0;

//int MotorB1 = 4; 
//int MotorB2 = 2;

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


typedef struct struct_message {
    int a;
} struct_message;
// Create a struct_message called myData
struct_message myData;

uint8_t key[] =  {0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44};

void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
}


  
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
  // Wifi STA Mode
  WiFi.mode(WIFI_STA);
  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");
  
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
  //pinMode(LED, OUTPUT);
  //digitalWrite(LED,HIGH);
  //pinMode(MotorA1,OUTPUT); 
  //pinMode(MotorA2,OUTPUT);
  //pinMode(MotorB1,OUTPUT); 
  //pinMode(MotorB2,OUTPUT);

    // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
 
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);

  
  delay(3000); 
}


void loop() {
  if  (myData.a == 3) { // FORWARD
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    //digitalWrite(MotorA1,HIGH);
    //digitalWrite(MotorA2,LOW);
    //digitalWrite(MotorB1,HIGH);
    //digitalWrite(MotorB2,LOW); 
  }
   if  (myData.a == 4) { // LEFT
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    //digitalWrite(MotorA1,LOW);
    //digitalWrite(MotorA2,HIGH);
    //digitalWrite(MotorB1,HIGH);
    //digitalWrite(MotorB2,LOW); 
  }
   if  (myData.a == 2) { // RIGHT
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    //digitalWrite(MotorA1,HIGH);
    //digitalWrite(MotorA2,LOW);
    //digitalWrite(MotorB1,LOW);
    //digitalWrite(MotorB2,HIGH); 
  }
  if  (myData.a == 0) {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
    //digitalWrite(MotorA1,LOW);
    //digitalWrite(MotorA2,LOW);
    //digitalWrite(MotorB1,LOW);
    //digitalWrite(MotorB2,LOW); 
  } 
}
