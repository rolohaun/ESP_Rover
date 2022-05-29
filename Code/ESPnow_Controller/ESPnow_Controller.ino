#include <ESP8266WiFi.h>
#include <espnow.h>

//int LED = 2;

int button1 = 12; //D6
int button2 = 13; //D7
int button3 = 14; //D5
int button4 = 5;  //D1
int button5 = 4;  //D2
int button6 = 0;  //D3
int button7 = 2;  //D4
//int button8 = 3;  //RX


int passFlag = 0;


typedef struct struct_message {
  int a;
} struct_message;

// Create a struct_message called myData
struct_message myData;


// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x84, 0xCC, 0xA8, 0xB0, 0x2B, 0x0D};

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

     pinMode(button1, INPUT_PULLUP);
     pinMode(button2, INPUT_PULLUP);
     pinMode(button3, INPUT_PULLUP);
     pinMode(button4, INPUT_PULLUP);
     pinMode(button5, INPUT_PULLUP);
     pinMode(button6, INPUT_PULLUP);
     pinMode(button7, INPUT_PULLUP);
     //pinMode(button8, INPUT_PULLUP);
   // Define pin #2 as output, for the LED
   //pinMode(LED, OUTPUT);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
   int buttonValue1 = digitalRead(button1);
   int buttonValue2 = digitalRead(button2);
   int buttonValue3 = digitalRead(button3);
   int buttonValue4 = digitalRead(button4);
   int buttonValue5 = digitalRead(button5);
   int buttonValue6 = digitalRead(button6);
   int buttonValue7 = digitalRead(button7);
   //int buttonValue8 = digitalRead(button8);


//------------------------------BUTON 1-----------------------------------------------
   if (buttonValue1 == LOW){
    //digitalWrite(LED,LOW);
    myData.a = 1;
    passFlag = 1;
    Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 2-----------------------------------------------   
   } else if (buttonValue2 == LOW){
     myData.a = 2;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 3-----------------------------------------------   
   } else if (buttonValue3 == LOW){
     myData.a = 3;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 4-----------------------------------------------   
   } else if (buttonValue4 == LOW){
     myData.a = 4;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 5-----------------------------------------------   
   } else if (buttonValue5 == LOW){
     myData.a = 5;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 6-----------------------------------------------   
   } else if (buttonValue6 == LOW){
     myData.a = 6;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
//------------------------------BUTON 7-----------------------------------------------   
   } else if (buttonValue7 == LOW){
     myData.a = 7;
     passFlag = 1;
     Serial.println(myData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   delay(100);
   
   } else {
      // Otherwise, turn the LED off
        if (passFlag == 1) {
        Serial.print("hello, world!");// Display on Serial monitor
        myData.a = 0;
        esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
         passFlag++;                     // Increment passFlag
  }
   }
}
