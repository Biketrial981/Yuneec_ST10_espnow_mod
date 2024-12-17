#include <esp_now.h>
#include <WiFi.h>

#define JOYSTICK_DEADZONE (8);
int CH_1= 0 ; // Y
int CH_2= 0 ; // X
int CH_3= 0 ; // POT
int CH_4= 0 ; // Y DER
int CH_5= 0 ; // X DER
int CH_6= 0 ; // POT tilt

//Valores map
const int minCH1 = 65, medCH1 = 150, maxCH1 = 227; 
const int minCH2 = 41, medCH2 = 155, maxCH2 = 255; 
const int minCH4 = 223, medCH4 = 133, maxCH4 = 43; 
const int minCH5 = 255, medCH5 = 150, maxCH5 = 35;
const int minCH6 = 82, maxCH6 = 188;

const int deadRangeLowCH1  = medCH1-JOYSTICK_DEADZONE; 
const int deadRangeHighCH1 = medCH1+JOYSTICK_DEADZONE;
const int deadRangeLowCH2  = medCH2-JOYSTICK_DEADZONE; 
const int deadRangeHighCH2 = medCH2+JOYSTICK_DEADZONE; 
const int deadRangeLowCH4  = medCH4-JOYSTICK_DEADZONE; 
const int deadRangeHighCH4 = medCH4+JOYSTICK_DEADZONE; 
const int deadRangeLowCH5  = medCH5-JOYSTICK_DEADZONE; 
const int deadRangeHighCH5 = medCH5+JOYSTICK_DEADZONE; 

const int minMap = -100, maxMap = 100;


// clientes
uint8_t broadcastAddress1[] = {0x30, 0xC9, 0x22, 0xB0, 0x2F, 0x88};  //waveshare robot
uint8_t broadcastAddress2[] = {0x34, 0x5F, 0x45, 0xA7, 0x94, 0xE0};  //Pantalla mando sobremesa
uint8_t broadcastAddress3[] = {0xA4, 0xCF, 0x12, 0xED, 0x88, 0xCC};  //mini pantalla
uint8_t broadcastAddress4[] = {0x64, 0xE8, 0x33, 0x7C, 0xB2, 0x04};  //PANTALLA 7" WAVESHARE


typedef struct data_struct {
  int CH1; // CH1
  int CH2; // CH2
  int CH3; // CH3
  int CH4; // CH4
  int CH5; // CH5
  int CH6; // CH6

  byte switch7Value;  // CH7
  byte switch8Value;  // CH8
  byte switch9Value;  // CH9
  byte switch10Value; // CH10
  byte switch11Value; // CH11
  byte switch12Value; // CH12
  byte switch13Value; // CH13
  byte switch14Value; // CH14
  byte switch15Value; // CH15
  byte switch16Value; // CH16
} data_struct;

data_struct data;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //char macStr[18];
  //Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  //         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //Serial.print(macStr);
  //Serial.print(" send status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
  analogReadResolution(8);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  // register peer
registrar_clientes();
pines();     
}
 
void loop() {

int v1 = analogRead(2); 
if (v1 < deadRangeLowCH1) CH_1= (map(v1,minCH1,deadRangeLowCH1,-100,0));
else if (v1 > deadRangeHighCH1){ CH_1= (map(v1,deadRangeHighCH1,maxCH1,0,100));}  //OK
else{CH_1= 0;}
data.CH1 = CH_1;

int v2 = analogRead(3); 
if (v2 < deadRangeLowCH2) CH_2= (map(v2,minCH2,deadRangeLowCH2,-100,0));
else if (v2 > deadRangeHighCH2){ CH_2= (map(v2,deadRangeHighCH2,maxCH2,0,100));}
else{CH_2= 0;}
data.CH2 = CH_2;

int v3 = digitalRead(5); 
data.CH3 = v3;
  
int v4 = analogRead(0); 
if (v4 < deadRangeLowCH4) CH_4= (map(v4,deadRangeLowCH4,minCH4,0,-120));  
else if (v4 > deadRangeHighCH4){ CH_4= (map(v4,maxCH4,deadRangeHighCH4,120,0));} 
else{CH_4= 0;}
data.CH4 = CH_4;

int v5 = analogRead(1); 
if (v5 < deadRangeLowCH5) CH_5= (map(v5,deadRangeLowCH5,minCH5,0,-106)); 
else if (v5 > deadRangeHighCH5){ CH_5= (map(v5,maxCH5,deadRangeHighCH5,127,0));}  //OK
else{CH_5= 0;}
data.CH5 = CH_5;

int v6 = analogRead(4); 
CH_6= (map(v6,maxCH6,minCH6,-100,100));
data.CH6 = CH_6;


//int v3 = 0; 
//if (v3 < deadRangeLowZ) CH_3= (map(v3,0,deadRangeLowZ,-100,0));
//else if (v3 > deadRangeHighZ){ CH_3= (map(v3,deadRangeHigh,255,0,100));}
//else{CH_3= 0;}
//data.CH3 = CH_3;


/*
data.CH1 = map(analogRead(36), 4095, 0, 0, 255);
data.CH2 = map(analogRead(39), 0, 4095, 0, 255);
data.CH3 = map(analogRead(34), 0, 4095, 0, 255);   
data.CH4 = map(analogRead(33), 4095, 0, 0, 255);
data.CH5 = map(analogRead(32), 0, 4095, 0, 255);
data.CH6 = map(analogRead(35), 0, 4095, 0, 255);  

  data.switch7Value   = !digitalRead(2);
  data.switch8Value   = !digitalRead(4);
  data.switch9Value   = !digitalRead(16);
  data.switch10Value  = !digitalRead(15);
  data.switch11Value  = !digitalRead(23);
  data.switch12Value  = !digitalRead(22);
  data.switch13Value  = !digitalRead(21);
  data.switch14Value  = !digitalRead(19);
  data.switch15Value  = !digitalRead(18);
  data.switch16Value  = !digitalRead(17);
  data.CH5 = analogRead(1);
  data.CH4 = analogRead(0);
  data.CH2 = analogRead(3);
  data.CH1 = analogRead(2);  */
  data.switch7Value  = !digitalRead(9); // VIDEO BUTTON
  data.switch8Value  = !digitalRead(8); //PHOTO BUTTON
  data.switch9Value  = 0;
  data.switch10Value = 0;
  data.switch11Value = 0;
  data.switch12Value = 0;
  data.switch13Value = 0;
  data.switch14Value = 0;
  data.switch15Value = 0;
  data.switch16Value = 0;

  esp_err_t result = esp_now_send(0, (uint8_t *) &data, sizeof(data_struct));
   
  if (result == ESP_OK) {
    //analogWrite(2,5);
  }
  else {
    //analogWrite(2,0);
  }
  delay(50);
}