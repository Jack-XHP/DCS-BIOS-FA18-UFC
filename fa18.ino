#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#define  DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"
uint32_t charToHex[43] = {
0xCF27,//0
0x4800,//1
0x9B13,//2
0xDB11,//3
0x5830,//4
0xD331,//5
0xD333,//6
0x4B00,//7
0xDB33,//8
0xDB31,//9
0,
0,
0,
0,
0,
0,
0,
0x5B32,//A
0xDB89,//B
0x8323,//C
0xCB89,//D
0x9333,//E
0x1332,//F
0xD323,//G
0x5832,//H
0x8389,//I
0xC803,//J
0x2432,//K
0x8023,//L
0x4C62,//M
0x6862,//N
0xCB23,//O
0x1B32,//P
0xEB23,//Q
0x3B32,//R
0xA341,//S
0x0388,//T
0xC823,//U
0x0426,//V
0x6826,//W
0x2444,//X
0x1838,//Y
0x8705//Z
};
uint32_t twentyToHex[20] = {
  0x4800,//1
  0x9A08,//2
  0xDA00,//3
  0x5880,//4
  0xD280,//5
  0xD088,//6
  0x4A00,//7
  0xDA88,//8
  0x5A80,//9
  0xCAAA,//10
  0x4822,//11
  0x9A2A,//12
  0xDA22,//13
  0x58A2,//14
  0xD2A2,//15
  0xD0AA,//16
  0x4A22,//17
  0xDAAA,//18
  0x5AA2,//19
  0xCB9B,//20
};



U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
U8G2_SH1122_256X64_F_HW_I2C u8g3(U8G2_R2);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void ledPrintChar(int address, char text){
  uint32_t   ledPin = charToHex[int(text) - 48];
  alpha4.writeDigitRaw(address, ledPin);
  alpha4.writeDisplay();
}

void ledPrintDoubleInt(int address, int number){
  uint32_t   ledPin = twentyToHex[number - 1];
  alpha4.writeDigitRaw(address, ledPin);
  alpha4.writeDisplay();
}

void ledPrintUFC(int address, char* text){
  if (isDigit(text[1])){
    int output = atoi(text);
    ledPrintDoubleInt(address, output);
  }else{
    char output = text[1];
    ledPrintChar(address, output);
  }
}
char* deblank(char* input)                                         
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}
void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x71);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
void disNum(int address, char* text ){
  TCA9548A(address);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setCursor(0, 30);
  u8g2.print(text);
  u8g2.sendBuffer(); 
}
void disNumBig(int address, char* text){
  TCA9548A(address);
  u8g3.clearBuffer();          // clear the internal memory 
  u8g3.setCursor(0, 32);
  u8g3.print(text);
  u8g3.sendBuffer(); 
}
void disCue(int address, char* text){
  TCA9548A(address);
  u8g2.clearBuffer(); 
  u8g2.setCursor(0, 30);
  u8g2.print(text);
  u8g2.updateDisplayArea(0,0,3,4);
}
void disOptDis(int address, char* text){
  TCA9548A(address);
  u8g2.clearBuffer(); 
  u8g2.setCursor(24, 30);
  u8g2.print(text);
  u8g2.updateDisplayArea(3,0,13,4);
}
void disScrtachStr1(int address, char* text){
  TCA9548A(address);
  u8g3.setFont(u8g2_font_inb30_mf);
  u8g3.clearBuffer(); 
  u8g3.setCursor(0, 30);
  u8g3.print(text);
  u8g3.updateDisplayArea(0,0,8,4);
}
void disScrtachStr2(int address, char* text){
  TCA9548A(address);
  u8g3.clearBuffer(); 
  u8g3.setCursor(64, 30);
  u8g3.print(text);
  u8g3.updateDisplayArea(8,0,8,4);
}
void disScrtachNum(int address, char* text){
  TCA9548A(address);
  u8g3.clearBuffer();
  u8g3.setCursor(16, 30);
  u8g3.print(text);
  u8g3.updateDisplayArea(16,0,24,4);
}


void onUfcComm1DisplayChange(char* newValue) {
    ledPrintUFC(7, newValue);
}
DcsBios::StringBuffer<2> ufcComm1DisplayBuffer(0x7424, onUfcComm1DisplayChange);
void onUfcComm2DisplayChange(char* newValue) {
    ledPrintUFC(0, newValue);
}
DcsBios::StringBuffer<2> ufcComm2DisplayBuffer(0x7426, onUfcComm2DisplayChange);


void onUfcOptionCueing1Change(char* newValue) {
    disCue(0,newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing1Buffer(0x7428, onUfcOptionCueing1Change);
void onUfcOptionCueing2Change(char* newValue) {
    disCue(2,newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing2Buffer(0x742a, onUfcOptionCueing2Change);
void onUfcOptionCueing3Change(char* newValue) {
    disCue(3,newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing3Buffer(0x742c, onUfcOptionCueing3Change);
void onUfcOptionCueing4Change(char* newValue) {
    disCue(4,newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing4Buffer(0x742e, onUfcOptionCueing4Change);
void onUfcOptionCueing5Change(char* newValue) {
    disCue(5,newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing5Buffer(0x7430, onUfcOptionCueing5Change);


void onUfcOptionDisplay1Change(char* newValue) {
    disOptDis(0,newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);
void onUfcOptionDisplay2Change(char* newValue) {
     disOptDis(2,newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay2Buffer(0x7436, onUfcOptionDisplay2Change);

void onUfcOptionDisplay3Change(char* newValue) {
     disOptDis(3,newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay3Buffer(0x743a, onUfcOptionDisplay3Change);
void onUfcOptionDisplay4Change(char* newValue) {
    disOptDis(4,newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay4Buffer(0x743e, onUfcOptionDisplay4Change);
void onUfcOptionDisplay5Change(char* newValue) {
    disOptDis(5,newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay5Buffer(0x7442, onUfcOptionDisplay5Change);


DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

void onUfcScratchpadString1DisplayChange(char* newValue) {
   String head = "";
   
   String value = head + deblank(newValue)+ufcScratchpadString2DisplayBuffer.getData() +ufcScratchpadNumberDisplayBuffer.getData();
   char* send_value = value.c_str();
   disNumBig(1,send_value );
}
void onUfcScratchpadString2DisplayChange(char* newValue) {
   String head = "";
   String value = head + deblank(ufcScratchpadString1DisplayBuffer.getData())+newValue+ ufcScratchpadNumberDisplayBuffer.getData();
   char* send_value = value.c_str();
   disNumBig(1,send_value );
}
void onUfcScratchpadNumberDisplayChange(char* newValue) {
   String head = "";
   String value = head + deblank(ufcScratchpadString1DisplayBuffer.getData())+ ufcScratchpadString2DisplayBuffer.getData() + newValue;
   char* send_value = value.c_str();
   disNumBig(1,send_value );
}



void setup() 
{
  Wire.begin();
  alpha4.begin(0x70);
  alpha4.setBrightness(2);
  TCA9548A(0);
  u8g2.begin();
  TCA9548A(1);
  u8g3.begin(); 
  TCA9548A(2);
  u8g2.begin(); 
  TCA9548A(3);
  u8g2.begin();
  TCA9548A(4);
  u8g2.begin();
  TCA9548A(5);
  u8g2.begin();
  
  u8g2.setFont(u8g2_font_inb30_mf);
  u8g3.setFont( u8g2_font_logisoso32_tf);
  u8g2.setBusClock(850000);
  u8g3.setBusClock(880000);
  DcsBios::setup();
  disNumBig(1,"test");
  disNum(0,"test");
  disNum(2,"test");
  disNum(3,"test");
  disNum(4,"test");
  disNum(5,"test");
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  alpha4.writeDigitRaw(7, 0xFFFF);
  alpha4.writeDisplay();
}

void loop()
{ 
  DcsBios::loop();
}
