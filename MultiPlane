#include <Arduino.h>

#include <U8g2lib.h>

#include <Wire.h>

#include <Adafruit_GFX.h>

#include "Adafruit_LEDBackpack.h"

#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"


U8G2_SH1122_256X64_F_4W_HW_SPI u8g3(U8G2_R0, 10, 9, 8);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x71); // TCA9548A address is 0x70
  Wire.write(1 << bus); // send byte to select bus
  Wire.endTransmission();
}
// ----------------- MultiPlane Switch ----------------
#define AV8 0
#define A10 1
#define F14 2
#define F16 3
#define JF17 4
#define FA18 5
int8_t currentPlane = -1;
int updateCounter = 0;
int previousCounter = -1;
bool refreshed = true;
bool stopped = true;
void onUpdateCounterChange(unsigned int newValue) {}
DcsBios::IntegerBuffer UpdateCounterBuffer(0xfffe, 0x00ff, 0, onUpdateCounterChange);

void onAcftNameChange(char * newValue) {}
DcsBios::StringBuffer < 24 > AcftNameBuffer(0x0000, onAcftNameChange);

// ------------- 2.08 inch OLED ---------------------

void disNumBig(char * text) {
  int s, d = 0;
  char dst[12];
  bool removeSpace = false;
  for (s = 0; text[s] != 0; s++)
    if (text[s] != ' ' || removeSpace) {
      dst[d] = text[s];
      d++;
    } else {
      removeSpace = true;
    }
  dst[d] = 0;
  u8g3.clearBuffer(); // clear the internal memory
  u8g3.setFont(u8g2_font_logisoso34_tf);
  u8g3.setCursor(0, 34);
  u8g3.print(dst);
  u8g3.sendBuffer();
}

void disNumBigA10(char * line1, char * line2) {
  u8g3.clearBuffer();
  u8g3.setFont(u8g2_font_logisoso20_tr);
  u8g3.setCursor(0, 32);
  u8g3.print(line1);
  u8g3.setCursor(0, 64);
  u8g3.print(line2);
  u8g3.sendBuffer();
}

// ------------ 0.91 inch OLED -------------------

uint8_t mini_oled_address[5] = {
  0,
  1,
  7,
  6,
  5
};

void disCue(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_inb30_mf);
  u8g2.setCursor(0, 30);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 0, 3, 4);
}

void disOptDis(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_inb30_mf);
  u8g2.setCursor(24, 30);
  u8g2.print(text);
  u8g2.updateDisplayArea(3, 0, 13, 4);
}

void disLine1(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.setCursor(0, 8);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 0, 16, 1);
}

void disLine2(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(0, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 1, 16, 3);
}

void disNum(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(0, 32);
  u8g2.print(text);
  u8g2.sendBuffer();
}

void disLine1F14(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(0, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 0, 12, 4);
}
void disLine2F14(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(96, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(12, 0, 4, 4);
}
void disLine3F14(int address, char * text) {
  TCA9548A(mini_oled_address[address]);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.setCursor(0, 8);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 0, 16, 1);
}
void disLine4F14(int address, char * text) {
  TCA9548A(mini_oled_address[address]);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(0, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 1, 16, 3);
}

void disLine1F16(int address, char * text) {
  TCA9548A(mini_oled_address[address]);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso28_tf);
  u8g2.setCursor(0, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 0, 5, 4);
}
void disLine2F16(int address, char * text) {
  TCA9548A(mini_oled_address[address]);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso28_tf);
  u8g2.setCursor(40, 32);
  u8g2.print(text);
  u8g2.updateDisplayArea(0, 5, 11, 4);
}

// ----------------- HT16K33 LED Control ----------------------

const uint32_t charToHex[53] PROGMEM = {
  0xAA22, //0
  0x2800, //1
  0xB220, //2
  0xB900, //3
  0x3802, //4
  0x9A02, //5
  0x1A22, //6
  0xA800, //7
  0xBA22, //8
  0xB802, //9
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0, //A
  0, //B
  0x8389, //C
  0, //D
  0, //E
  0, //F
  0x9B89, //G
  0, //H
  0, //I
  0, //J
  0, //K
  0, //L
  0x688C, //M
  0, //N
  0, //O
  0, //P
  0, //Q
  0, //R
  0x9B19, //S
  0, //T
  0, //U
  0, //V
  0, //W
  0, //X
  0, //Y
  0, //Z
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0x0001, //d
};
const uint32_t twentyToHex[20] PROGMEM = {
  0x2800, //1
  0xB220, //2
  0xBA00, //3
  0x3802, //4
  0x9A02, //5
  0x1A22, //6
  0xA800, //7
  0xBA22, //8
  0xB802, //9
  0xAAAA, //10
  0x2888, //11
  0xB2A8, //12
  0xBA88, //13
  0x388A, //14
  0x9A8A, //15
  0x1AAA, //16
  0xA888, //17
  0xBAAA, //18
  0xB88A, //19
  0xABB3, //20
};
uint32_t ledStatus[7] = {
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
};
uint32_t ledPrintChar(int address, char text) {
  uint32_t ledPin = pgm_read_dword( & charToHex[int(text) - 48]);
  return ledPin;
}

uint32_t ledPrintDoubleInt(int address, int number) {
  uint32_t ledPin = pgm_read_dword( & twentyToHex[number - 1]);
  return ledPin;
}

uint32_t ledPrintUFC(int address, char * text) {
  uint32_t ledPin;
  if (isDigit(text[1])) {
    int output = atoi(text);
    ledPin = ledPrintDoubleInt(address, output);
  } else {
    char output = text[1];
    ledPin = ledPrintChar(address, output);
  }
  return ledPin;
}

//AV8
void onMcLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer mcLightBuffer(0x787c, 0x0004, 2, onMcLightChange);
void onLeftGearGChange(unsigned int newValue) {}
DcsBios::IntegerBuffer leftGearGBuffer(0x7888, 0x0040, 6, onLeftGearGChange);
void onNoseGearGChange(unsigned int newValue) {}
DcsBios::IntegerBuffer noseGearGBuffer(0x7888, 0x0010, 4, onNoseGearGChange);
void onRightGearGChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rightGearGBuffer(0x7888, 0x0100, 8, onRightGearGChange);
void onFireLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer fireLightBuffer(0x787c, 0x0400, 10, onFireLightChange);
void onApuWlightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer apuWlightBuffer(0x7886, 0x0002, 1, onApuWlightChange);
void onAiLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer aiLightBuffer(0x7880, 0x0080, 7, onAiLightChange);
void onSamLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer samLightBuffer(0x7880, 0x0020, 5, onSamLightChange);
void onAaaLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer aaaLightBuffer(0x7880, 0x0100, 8, onAaaLightChange);
void onLfuelLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lfuelLightBuffer(0x787c, 0x0010, 4, onLfuelLightChange);
void onFlaps1WlightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flaps1WlightBuffer(0x7882, 0x0800, 11, onFlaps1WlightChange);
void onFlaps2WlightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flaps2WlightBuffer(0x7882, 0x1000, 12, onFlaps2WlightChange);
void onFlapsLightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flapsLightBuffer(0x787c, 0x1000, 12, onFlapsLightChange);
//A10 
//void onMasterCautionChange(unsigned int newValue) {}
//DcsBios::IntegerBuffer masterCautionBuffer(0x1012, 0x0800, 11, onMasterCautionChange);
void onClL2Change(unsigned int newValue) {}
DcsBios::IntegerBuffer clL2Buffer(0x10d8, 0x2000, 13, onClL2Change);
void onClL3Change(unsigned int newValue) {}
DcsBios::IntegerBuffer clL3Buffer(0x10d8, 0x4000, 14, onClL3Change);
void onClC3Change(unsigned int newValue) {}
DcsBios::IntegerBuffer clC3Buffer(0x10d4, 0x0400, 10, onClC3Change);
void onGearLSafeChange(unsigned int newValue) {}
DcsBios::IntegerBuffer gearLSafeBuffer(0x1026, 0x1000, 12, onGearLSafeChange);
void onGearNSafeChange(unsigned int newValue) {}
DcsBios::IntegerBuffer gearNSafeBuffer(0x1026, 0x0800, 11, onGearNSafeChange);
void onGearRSafeChange(unsigned int newValue) {}
DcsBios::IntegerBuffer gearRSafeBuffer(0x1026, 0x2000, 13, onGearRSafeChange);
void onLEngFireChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lEngFireBuffer(0x10da, 0x0008, 3, onLEngFireChange);
void onREngFireChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rEngFireBuffer(0x10da, 0x0020, 5, onREngFireChange);
void onApuFireChange(unsigned int newValue) {}
DcsBios::IntegerBuffer apuFireBuffer(0x10da, 0x0010, 4, onApuFireChange);
void onExtStoresJettisonChange(unsigned int newValue) {}
DcsBios::IntegerBuffer extStoresJettisonBuffer(0x1116, 0x2000, 13, onExtStoresJettisonChange);
void onClI3Change(unsigned int newValue) {}
DcsBios::IntegerBuffer clI3Buffer(0x10d8, 0x0004, 2, onClI3Change);

//F16
void onMasterCautionChange(unsigned int newValue) {}
DcsBios::IntegerBuffer masterCautionBuffer(0x4400, 0x8000, 15, onMasterCautionChange);
void onLightEngFireChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightEngFireBuffer(0x4472, 0x4000, 14, onLightEngFireChange);
void onLightEngineChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightEngineBuffer(0x4472, 0x8000, 15, onLightEngineChange);

//JF17
void onFcsWarnBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer fcsWarnBtnBuffer(0x482c, 0x0002, 1, onFcsWarnBtnChange);
void onWarnLMasterChange(unsigned int newValue) {}
DcsBios::IntegerBuffer warnLMasterBuffer(0x4858, 0x2000, 13, onWarnLMasterChange);
void onWarnLFireChange(unsigned int newValue) {}
DcsBios::IntegerBuffer warnLFireBuffer(0x4858, 0x4000, 14, onWarnLFireChange);
void onWarnLSeatChange(unsigned int newValue) {}
DcsBios::IntegerBuffer warnLSeatBuffer(0x4862, 0x0008, 3, onWarnLSeatChange);
void onWarnLLowFuelChange(unsigned int newValue) {}
DcsBios::IntegerBuffer warnLLowFuelBuffer(0x485c, 0x8000, 15, onWarnLLowFuelChange);
void onLgLLeftChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lgLLeftBuffer(0x4858, 0x0002, 1, onLgLLeftChange);
void onLgLNoseChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lgLNoseBuffer(0x4858, 0x0004, 2, onLgLNoseChange);
void onLgLRightChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lgLRightBuffer(0x4858, 0x0008, 3, onLgLRightChange);
void onWarnLBattChange(unsigned int newValue) {}
DcsBios::IntegerBuffer warnLBattBuffer(0x485e, 0x1000, 12, onWarnLBattChange);

//FA18
void onMasterCautionLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer masterCautionLtBuffer(0x7408, 0x0200, 9, onMasterCautionLtChange);
void onMasterModeAaLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer masterModeAaLtBuffer(0x740c, 0x0200, 9, onMasterModeAaLtChange);
void onMasterModeAgLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer masterModeAgLtBuffer(0x740c, 0x0400, 10, onMasterModeAgLtChange);
void onFireRightLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer fireRightLtBuffer(0x740c, 0x0010, 4, onFireRightLtChange);
void onFireLeftLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer fireLeftLtBuffer(0x7408, 0x0040, 6, onFireLeftLtChange);
uint32_t assemble_com2() {
 uint32_t value;
 if (currentPlane == FA18) {
   value = fireLeftLtBuffer.getData() * 0x0001 +
     fireRightLtBuffer.getData() * 0x0040 +
     masterCautionLtBuffer.getData() * 0x1000 +
     masterModeAaLtBuffer.getData() * 0x2000 +
     masterModeAgLtBuffer.getData() * 0x4000 +
     0x8FBE;
 } else if (currentPlane == F16) {
   value = lightEngFireBuffer.getData() * 0x0001 +
     lightEngineBuffer.getData() * 0x0040 +
     masterCautionBuffer.getData() * 0x1000 +
     0x8FBE;
 } else {
   value = 0x8FBE;
 }

 return value;
}

void onFireApuLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer fireApuLtBuffer(0x740c, 0x0004, 2, onFireApuLtChange);
uint32_t assemble_com3() {
 uint32_t value;
 if (currentPlane == FA18) {
   value = fireApuLtBuffer.getData() * 0x0001 + 0xFFFE;
 } else {
   value = 0xFFFE;
 }
 return value;
}

//F16
void onLightGearLChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightGearLBuffer(0x4474, 0x0400, 10, onLightGearLChange);
void onLightGearNChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightGearNBuffer(0x4474, 0x0200, 9, onLightGearNChange);
void onLightGearRChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightGearRBuffer(0x4474, 0x0800, 11, onLightGearRChange);

void onLightSeatNotChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightSeatNotBuffer(0x446e, 0x4000, 14, onLightSeatNotChange);
void onLightAcftBattFailChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightAcftBattFailBuffer(0x4476, 0x1000, 12, onLightAcftBattFailChange);
void onLightHookChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightHookBuffer(0x4470, 0x0400, 10, onLightHookChange);
void onLightFwdFuelLowChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightFwdFuelLowBuffer(0x4472, 0x0008, 3, onLightFwdFuelLowChange);
void onLightFlcsFaultChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lightFlcsFaultBuffer(0x446e, 0x0800, 11, onLightFlcsFaultChange);

//FA18
void onFlpLgLeftGearLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgLeftGearLtBuffer(0x7430, 0x1000, 12, onFlpLgLeftGearLtChange);
void onFlpLgNoseGearLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgNoseGearLtBuffer(0x7430, 0x0800, 11, onFlpLgNoseGearLtChange);
void onFlpLgRightGearLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgRightGearLtBuffer(0x7430, 0x2000, 13, onFlpLgRightGearLtChange);
void onFlpLgHalfFlapsLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgHalfFlapsLtBuffer(0x7430, 0x4000, 14, onFlpLgHalfFlapsLtChange);
void onFlpLgFlapsLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgFlapsLtBuffer(0x7460, 0x0001, 0, onFlpLgFlapsLtChange);
void onFlpLgFullFlapsLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer flpLgFullFlapsLtBuffer(0x7430, 0x8000, 15, onFlpLgFullFlapsLtChange);
void onLhAdvStbyChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lhAdvStbyBuffer(0x7408, 0x4000, 14, onLhAdvStbyChange);
void onLhAdvRecChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lhAdvRecBuffer(0x740a, 0x0001, 0, onLhAdvRecChange);
void onLhAdvGoChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lhAdvGoBuffer(0x740a, 0x0010, 4, onLhAdvGoChange);
void onRhAdvAiChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rhAdvAiBuffer(0x740a, 0x0400, 10, onRhAdvAiChange);
void onRhAdvSamChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rhAdvSamBuffer(0x740a, 0x0200, 9, onRhAdvSamChange);
void onClipCkSeatLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipCkSeatLtBuffer(0x74a2, 0x4000, 14, onClipCkSeatLtChange);
void onClipBattSwLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipBattSwLtBuffer(0x74a6, 0x0100, 8, onClipBattSwLtChange);
void onArrestingHookLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer arrestingHookLtBuffer(0x74a2, 0x0200, 9, onArrestingHookLtChange);
void onClipFuelLoLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipFuelLoLtBuffer(0x74a6, 0x1000, 12, onClipFuelLoLtChange);
void onClipFcesLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipFcesLtBuffer(0x74a6, 0x2000, 13, onClipFcesLtChange);

uint32_t assemble_com4() {
 uint32_t value;
 if (currentPlane == FA18) {
   value = lightGearLBuffer.getData() * 0x0001 +
     flpLgNoseGearLtBuffer.getData() * 0x0002 +
     flpLgRightGearLtBuffer.getData() * 0x0004 +
     lhAdvGoBuffer.getData() * 0x0008 +
     clipCkSeatLtBuffer.getData() * 0x0010 +
     clipBattSwLtBuffer.getData() * 0x0020 +
     arrestingHookLtBuffer.getData() * 0x0040 +
     flpLgHalfFlapsLtBuffer.getData() * 0x0080 +
     flpLgFlapsLtBuffer.getData() * 0x0100 +
     flpLgFullFlapsLtBuffer.getData() * 0x0200 +
     rhAdvAiBuffer.getData() * 0x0400 +
     rhAdvSamBuffer.getData() * 0x0800 +
     clipFuelLoLtBuffer.getData() * 0x1000 +
     clipFcesLtBuffer.getData() * 0x2000 +
     lhAdvStbyBuffer.getData() * 0x4000 +
     lhAdvRecBuffer.getData() * 0x8000;
 } else if (currentPlane == F16) {
   value = lightGearLBuffer.getData() * 0x0001 +
     lightGearNBuffer.getData() * 0x0002 +
     lightGearRBuffer.getData() * 0x0004 +
     lightSeatNotBuffer.getData() * 0x0010 +
     lightAcftBattFailBuffer.getData() * 0x0020 +
     lightHookBuffer.getData() * 0x0040 +
     lightFwdFuelLowBuffer.getData() * 0x1000 +
     lightFlcsFaultBuffer.getData() * 0x2000;
 } else {
   value = 0x0000;
 }

 return value;
}

void onLhAdvXmitChange(unsigned int newValue) {}
DcsBios::IntegerBuffer lhAdvXmitBuffer(0x740a, 0x0004, 2, onLhAdvXmitChange);
void onRhAdvAaaChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rhAdvAaaBuffer(0x740a, 0x0800, 11, onRhAdvAaaChange);
void onRhAdvCwChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rhAdvCwBuffer(0x740a, 0x1000, 12, onRhAdvCwChange);
void onClipLGenLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipLGenLtBuffer(0x74a6, 0x8000, 15, onClipLGenLtChange);
void onClipRGenLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer clipRGenLtBuffer(0x74ae, 0x0100, 8, onClipRGenLtChange);
void onApuReadyLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer apuReadyLtBuffer(0x74bc, 0x0400, 10, onApuReadyLtChange);

uint32_t assemble_com5() {
 uint32_t value;
 if (currentPlane == FA18) {
   value = lhAdvXmitBuffer.getData() * 0x0001 +
     rhAdvAaaBuffer.getData() * 0x0002 +
     rhAdvCwBuffer.getData() * 0x0004 +
     clipLGenLtBuffer.getData() * 0x0008 +
     clipRGenLtBuffer.getData() * 0x0010 +
     apuReadyLtBuffer.getData() * 0x0080 +
     0xFF60;
 } else {
   value = 0xFF60;
 }
 return value;
}

//F16

void onRwrSysTestBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrSysTestBtnBuffer(0x4452, 0x0200, 9, onRwrSysTestBtnChange);
void onRwrModeBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrModeBtnBuffer(0x4452, 0x0080, 7, onRwrModeBtnChange);
void onRwrTBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrTBtnBuffer(0x4452, 0x0400, 10, onRwrTBtnChange);
void onRwrPwrBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrPwrBtnBuffer(0x4452, 0x4000, 14, onRwrPwrBtnChange);

//FA18
void onEmerJettBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer emerJettBtnBuffer(0x742c, 0x0100, 8, onEmerJettBtnChange);
void onMcDischChange(unsigned int newValue) {}
DcsBios::IntegerBuffer mcDischBuffer(0x740c, 0x4000, 14, onMcDischChange);
void onSjCtrLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer sjCtrLtBuffer(0x742e, 0x4000, 14, onSjCtrLtChange);
void onSjLiLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer sjLiLtBuffer(0x742e, 0x8000, 15, onSjLiLtChange);
void onSjLoLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer sjLoLtBuffer(0x7430, 0x0100, 8, onSjLoLtChange);
void onSjRiLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer sjRiLtBuffer(0x7430, 0x0200, 9, onSjRiLtChange);
void onSjRoLtChange(unsigned int newValue) {}
DcsBios::IntegerBuffer sjRoLtBuffer(0x7430, 0x0400, 10, onSjRoLtChange);
void onRwrBitBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrBitBtnBuffer(0x7482, 0x8000, 15, onRwrBitBtnChange);
void onRwrDisplayBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrDisplayBtnBuffer(0x7482, 0x1000, 12, onRwrDisplayBtnChange);
void onRwrOffsetBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrOffsetBtnBuffer(0x7482, 0x4000, 14, onRwrOffsetBtnChange);
void onRwrPowerBtnChange(unsigned int newValue) {}
DcsBios::IntegerBuffer rwrPowerBtnBuffer(0x7482, 0x0800, 11, onRwrPowerBtnChange);

uint32_t assemble_com6() {
 uint32_t value;
 if (currentPlane == FA18) {
   value = emerJettBtnBuffer.getData() * 0x0001 +
     mcDischBuffer.getData() * 0x0002 +
     sjLiLtBuffer.getData() * 0x0004 +
     sjCtrLtBuffer.getData() * 0x0008 +
     sjRiLtBuffer.getData() * 0x0010 +
     sjLoLtBuffer.getData() * 0x0020 +
     rwrBitBtnBuffer.getData() * 0x0040 +
     sjRoLtBuffer.getData() * 0x0080 +
     rwrDisplayBtnBuffer.getData() * 0x0100 +
     rwrOffsetBtnBuffer.getData() * 0x0200 +
     rwrPowerBtnBuffer.getData() * 0x0400;
 } else if (currentPlane == F16) {
   value = rwrSysTestBtnBuffer.getData() * 0x0040 +
     rwrModeBtnBuffer.getData() * 0x0100 +
     rwrTBtnBuffer.getData() * 0x0200 +
     rwrPwrBtnBuffer.getData() * 0x0200;
 } else {
   value = 0x0000;
 }

 return value;
}

void onUfcComm1DisplayChange(char * newValue) {}
void onUfcComm2DisplayChange(char * newValue) {}

DcsBios::StringBuffer < 2 > ufcComm1DisplayBuffer(0x7424, onUfcComm1DisplayChange);
DcsBios::StringBuffer < 2 > ufcComm2DisplayBuffer(0x7426, onUfcComm2DisplayChange);

uint32_t assemble_com(int index) {
  uint32_t value = 0x0000;
  switch (index) {
  case 0:
    if (currentPlane != AV8 && currentPlane != FA18) {
      break;
    } else if (currentPlane == AV8) {
      break;
    } else if (currentPlane == FA18) {
      value = ledPrintUFC(0, ufcComm2DisplayBuffer.getData());
    }
    break;
  case 1:
    if (currentPlane != AV8 && currentPlane != FA18) {
      break;
    } else if (currentPlane == AV8) {
      break;
    } else if (currentPlane == FA18) {
      value = ledPrintUFC(0, ufcComm1DisplayBuffer.getData());
    }
    break;
 case 2:
   value = assemble_com2();
   break;
 case 3:
   value = assemble_com3();
   break;
 case 4:
   value = assemble_com4();
   break;
 case 5:
   value = assemble_com5();
   break;
 case 6:
   value = assemble_com6();
   break;
  }
  return value;
}

// ------------------ AV8B -----------------------------

void onAv8bnaOdu1SelectChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disCue(0, newValue);
}
DcsBios::StringBuffer < 1 > av8bnaOdu1SelectBuffer(0x7966, onAv8bnaOdu1SelectChange);
void onAv8bnaOdu2SelectChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disCue(1, newValue);
}
DcsBios::StringBuffer < 1 > av8bnaOdu2SelectBuffer(0x796c, onAv8bnaOdu2SelectChange);
void onAv8bnaOdu3SelectChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disCue(2, newValue);
}
DcsBios::StringBuffer < 1 > av8bnaOdu3SelectBuffer(0x7972, onAv8bnaOdu3SelectChange);
void onAv8bnaOdu4SelectChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disCue(3, newValue);
}
DcsBios::StringBuffer < 1 > av8bnaOdu4SelectBuffer(0x7978, onAv8bnaOdu4SelectChange);

void onAv8bnaOdu5SelectChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disCue(4, newValue);
}
DcsBios::StringBuffer < 1 > av8bnaOdu5SelectBuffer(0x797e, onAv8bnaOdu5SelectChange);

void onAv8bnaOdu1TextChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disOptDis(0, newValue);
}
DcsBios::StringBuffer < 4 > av8bnaOdu1TextBuffer(0x7968, onAv8bnaOdu1TextChange);
void onAv8bnaOdu2TextChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disOptDis(1, newValue);
}
DcsBios::StringBuffer < 4 > av8bnaOdu2TextBuffer(0x796e, onAv8bnaOdu2TextChange);
void onAv8bnaOdu3TextChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disOptDis(2, newValue);
}
DcsBios::StringBuffer < 4 > av8bnaOdu3TextBuffer(0x7974, onAv8bnaOdu3TextChange);
void onAv8bnaOdu4TextChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disOptDis(3, newValue);
}
DcsBios::StringBuffer < 4 > av8bnaOdu4TextBuffer(0x797a, onAv8bnaOdu4TextChange);
void onAv8bnaOdu5TextChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disOptDis(4, newValue);
}
DcsBios::StringBuffer < 4 > av8bnaOdu5TextBuffer(0x7980, onAv8bnaOdu5TextChange);

void onUfcScratchpadChange(char * newValue) {
  if (currentPlane != AV8) {
    return;
  }
  disNumBig(newValue);
}
DcsBios::StringBuffer < 12 > ufcScratchpadBuffer(0x7984, onUfcScratchpadChange);

// ------------------ A10 ---------------------------------------------------
void onCmscTxtChaffFlareChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disLine1(0, "----CHAFF----FLARE----");
  disLine2(0, newValue);
}
DcsBios::StringBuffer < 8 > cmscTxtChaffFlareBuffer(0x108e, onCmscTxtChaffFlareChange);
void onCmscTxtJmrChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disLine1(1, "----------JWR----------");
  disLine2(1, newValue);
}
DcsBios::StringBuffer < 8 > cmscTxtJmrBuffer(0x1096, onCmscTxtJmrChange);
void onCmscTxtMwsChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disLine1(2, "----------MWS----------");
  disLine2(2, newValue);
}
DcsBios::StringBuffer < 8 > cmscTxtMwsBuffer(0x12b0, onCmscTxtMwsChange);
void onUhfFrequencyChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disLine1(3, "----------UHF----------");
  disLine2(3, newValue);
}
DcsBios::StringBuffer < 7 > uhfFrequencyBuffer(0x1180, onUhfFrequencyChange);

void onUhfPresetChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  int value = atoi(newValue);
  ledPrintDoubleInt(0, value);
}
DcsBios::StringBuffer < 2 > uhfPresetBuffer(0x1188, onUhfPresetChange);

void onClockEtcChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  String pad = "----------";
  String line1 = pad + newValue + pad;
  char * result = line1.c_str();
  disLine1(4, result);
}
DcsBios::StringBuffer < 3 > clockEtcBuffer(0x1104, onClockEtcChange);
DcsBios::StringBuffer < 2 > clockHhBuffer(0x10fe, onClockHhChange);
DcsBios::StringBuffer < 2 > clockMmBuffer(0x1100, onClockMmChange);
DcsBios::StringBuffer < 2 > clockSsBuffer(0x1102, onClockSsChange);
void onClockHhChange(char * newValue) {
  String start = "";
  String col = ":";
  String clock_time = start + newValue + col + clockMmBuffer.getData() + col + clockSsBuffer.getData();
  char * result = clock_time.c_str();
  disLine2(4, result);
}
void onClockMmChange(char * newValue) {
  String start = "";
  String col = ":";
  String clock_time = start + clockHhBuffer.getData() + col + newValue + col + clockSsBuffer.getData();
  char * result = clock_time.c_str();
  disLine2(4, result);
}
void onClockSsChange(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  String start = "";
  String col = ":";
  String clock_time = start + clockHhBuffer.getData() + col + clockMmBuffer.getData() + col + newValue;
  char * result = clock_time.c_str();
  disLine2(4, result);
}

DcsBios::StringBuffer < 19 > cmsp1Buffer(0x1000, onCmsp1Change);
DcsBios::StringBuffer < 19 > cmsp2Buffer(0x1014, onCmsp2Change);
void onCmsp1Change(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disNumBigA10(newValue, cmsp2Buffer.getData());
}
void onCmsp2Change(char * newValue) {
  if (currentPlane != A10) {
    return;
  }
  disNumBigA10(cmsp1Buffer.getData(), newValue);
}

// ------------------ F16 ------------------------------
void onCmdsChAmountChange(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  disLine1F16(3, "CH");
  disLine2F16(3, newValue);
}
DcsBios::StringBuffer < 4 > cmdsChAmountBuffer(0x4586, onCmdsChAmountChange);
void onCmdsFlAmountChange(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  disLine1F16(2, "FL");
  disLine2F16(2, newValue);
}
DcsBios::StringBuffer < 4 > cmdsFlAmountBuffer(0x458a, onCmdsFlAmountChange);
void onCmdsO1AmountChange(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  disLine1F16(0, "O1");
  disLine2F16(0, newValue);
}
DcsBios::StringBuffer < 4 > cmdsO1AmountBuffer(0x457e, onCmdsO1AmountChange);
void onCmdsO2AmountChange(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  disLine1F16(1, "O2");
  disLine2F16(1, newValue);
}
DcsBios::StringBuffer < 4 > cmdsO2AmountBuffer(0x4582, onCmdsO2AmountChange);

DcsBios::StringBuffer < 25 > dedLine1Buffer(0x44fc, onDedLine1Change);
DcsBios::StringBuffer < 25 > dedLine2Buffer(0x4516, onDedLine2Change);
DcsBios::StringBuffer < 25 > dedLine3Buffer(0x4530, onDedLine3Change);
DcsBios::StringBuffer < 25 > dedLine4Buffer(0x454a, onDedLine4Change);
DcsBios::StringBuffer < 25 > dedLine5Buffer(0x4564, onDedLine5Change);
bool DED_update = true;
void updateDED() {
  if (DED_update) {
    u8g3.clearBuffer(); // clear the internal memory
    u8g3.setFont(u8g2_font_9x15_m_symbols);
    u8g3.setCursor(0, 64);
    u8g3.print(dedLine5Buffer.getData());
    u8g3.setCursor(0, 51);
    u8g3.print(dedLine4Buffer.getData());
    u8g3.setCursor(0, 38);
    u8g3.print(dedLine3Buffer.getData());
    u8g3.setCursor(0, 25);
    u8g3.print(dedLine2Buffer.getData());
    u8g3.setCursor(0, 12);
    u8g3.print(dedLine1Buffer.getData());
    u8g3.sendBuffer();
    DED_update = false;
  }
}
void onDedLine1Change(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  updateDED();
}
void onDedLine2Change(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  updateDED();
}
void onDedLine3Change(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  updateDED();
}
void onDedLine4Change(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  updateDED();
}
void onDedLine5Change(char * newValue) {
  if (currentPlane != F16) {
    return;
  }
  updateDED();
}

// ------------------ JF17 ------------------------------

void onUfcpLine1Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  disNum(0, newValue);
}
DcsBios::StringBuffer < 8 > ufcpLine1Buffer(0x4884, onUfcpLine1Change);
void onUfcpLine2Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  disNum(1, newValue);
}
DcsBios::StringBuffer < 8 > ufcpLine2Buffer(0x488c, onUfcpLine2Change);
void onUfcpLine3Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  disNum(2, newValue);
}
DcsBios::StringBuffer < 8 > ufcpLine3Buffer(0x4894, onUfcpLine3Change);
void onUfcpLine4Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  disNum(3, newValue);
}
DcsBios::StringBuffer < 8 > ufcpLine4Buffer(0x489c, onUfcpLine4Change);

DcsBios::StringBuffer < 8 > radioLine1Buffer(0x48a4, onRadioLine1Change);
DcsBios::StringBuffer < 8 > radioLine2Buffer(0x48ac, onRadioLine2Change);
bool radioUpdate = true;
void updateRadio() {
  if (radioUpdate) {
    TCA9548A(1);
    u8g3.clearBuffer();
    u8g3.setFont(u8g2_font_logisoso32_tf);
    u8g3.setCursor(0, 32);
    u8g3.print(radioLine1Buffer.getData());
    u8g3.setCursor(0, 64);
    u8g3.print(radioLine2Buffer.getData());
    u8g3.sendBuffer();
    radioUpdate = false;
  }
}
void onRadioLine1Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  updateRadio();
}

void onRadioLine2Change(char * newValue) {
  if (currentPlane != JF17) {
    return;
  }
  updateRadio();
}

// ------------------ FA18 ------------------------------

void onUfcOptionCueing1Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disCue(0, newValue);
}
DcsBios::StringBuffer < 1 > ufcOptionCueing1Buffer(0x7428, onUfcOptionCueing1Change);
void onUfcOptionCueing2Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disCue(1, newValue);
}
DcsBios::StringBuffer < 1 > ufcOptionCueing2Buffer(0x742a, onUfcOptionCueing2Change);
void onUfcOptionCueing3Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disCue(2, newValue);
}
DcsBios::StringBuffer < 1 > ufcOptionCueing3Buffer(0x742c, onUfcOptionCueing3Change);
void onUfcOptionCueing4Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disCue(3, newValue);
}
DcsBios::StringBuffer < 1 > ufcOptionCueing4Buffer(0x742e, onUfcOptionCueing4Change);
void onUfcOptionCueing5Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disCue(4, newValue);
}
DcsBios::StringBuffer < 1 > ufcOptionCueing5Buffer(0x7430, onUfcOptionCueing5Change);

void onUfcOptionDisplay1Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disOptDis(0, newValue);
}
DcsBios::StringBuffer < 4 > ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);
void onUfcOptionDisplay2Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disOptDis(1, newValue);
}
DcsBios::StringBuffer < 4 > ufcOptionDisplay2Buffer(0x7436, onUfcOptionDisplay2Change);

void onUfcOptionDisplay3Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disOptDis(2, newValue);
}
DcsBios::StringBuffer < 4 > ufcOptionDisplay3Buffer(0x743a, onUfcOptionDisplay3Change);
void onUfcOptionDisplay4Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disOptDis(3, newValue);
}
DcsBios::StringBuffer < 4 > ufcOptionDisplay4Buffer(0x743e, onUfcOptionDisplay4Change);
void onUfcOptionDisplay5Change(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  disOptDis(4, newValue);
}
DcsBios::StringBuffer < 4 > ufcOptionDisplay5Buffer(0x7442, onUfcOptionDisplay5Change);

DcsBios::StringBuffer < 2 > ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);
DcsBios::StringBuffer < 2 > ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);
DcsBios::StringBuffer < 8 > ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

void onUfcScratchpadString1DisplayChange(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  String head = "";

  String value = head + newValue + ufcScratchpadString2DisplayBuffer.getData() + ufcScratchpadNumberDisplayBuffer.getData();
  char * send_value = value.c_str();
  disNumBig(send_value);
}
void onUfcScratchpadString2DisplayChange(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  String head = "";
  String value = head + ufcScratchpadString1DisplayBuffer.getData() + newValue + ufcScratchpadNumberDisplayBuffer.getData();
  char * send_value = value.c_str();
  disNumBig(send_value);
}
void onUfcScratchpadNumberDisplayChange(char * newValue) {
  if (currentPlane != FA18) {
    return;
  }
  String head = "";
  String value = head + ufcScratchpadString1DisplayBuffer.getData() + ufcScratchpadString2DisplayBuffer.getData() + newValue;
  char * send_value = value.c_str();
  disNumBig(send_value);
}

void setup() {
  Wire.begin();
  alpha4.begin(0x70);
  alpha4.setBrightness(1);

  u8g2.setContrast(128);

  TCA9548A(mini_oled_address[0]);
  u8g2.begin();
  TCA9548A(mini_oled_address[1]);
  u8g2.begin();
  TCA9548A(mini_oled_address[2]);
  u8g2.begin();
  TCA9548A(mini_oled_address[3]);
  u8g2.begin();
  TCA9548A(mini_oled_address[4]);
  u8g2.begin();
  u8g3.begin();

  DcsBios::setup();
}

void loop() {
  int8_t oldPlane = currentPlane;
  if (!strcmp(AcftNameBuffer.getData(), "AV8BNA")) {
    currentPlane = AV8;
  } else if (!strcmp(AcftNameBuffer.getData(), "A-10C") || !strcmp(AcftNameBuffer.getData(), "A-10C_2")) {
    currentPlane = A10;
  } else if (!strcmp(AcftNameBuffer.getData(), "F-16C_50")) {
    currentPlane = F16;
  } else if (!strcmp(AcftNameBuffer.getData(), "JF-17")) {
    currentPlane = JF17;
  } else if (!strcmp(AcftNameBuffer.getData(), "FA-18C_hornet")) {
    currentPlane = FA18;
  } else {
    currentPlane = -1;
  }

  if (oldPlane != currentPlane || (refreshed && !stopped)) {
    refreshed = false;
    switch (currentPlane) {
    case AV8:
      onAv8bnaOdu1SelectChange(av8bnaOdu1SelectBuffer.getData());
      onAv8bnaOdu2SelectChange(av8bnaOdu2SelectBuffer.getData());
      onAv8bnaOdu3SelectChange(av8bnaOdu3SelectBuffer.getData());
      onAv8bnaOdu4SelectChange(av8bnaOdu4SelectBuffer.getData());
      onAv8bnaOdu5SelectChange(av8bnaOdu5SelectBuffer.getData());
      onAv8bnaOdu1TextChange(av8bnaOdu1TextBuffer.getData());
      onAv8bnaOdu2TextChange(av8bnaOdu2TextBuffer.getData());
      onAv8bnaOdu3TextChange(av8bnaOdu3TextBuffer.getData());
      onAv8bnaOdu4TextChange(av8bnaOdu4TextBuffer.getData());
      onAv8bnaOdu5TextChange(av8bnaOdu5TextBuffer.getData());
      onUfcScratchpadChange(ufcScratchpadBuffer.getData());
      break;
    case A10:
      onCmscTxtChaffFlareChange(cmscTxtChaffFlareBuffer.getData());
      onCmscTxtJmrChange(cmscTxtJmrBuffer.getData());
      onCmscTxtMwsChange(cmscTxtMwsBuffer.getData());
      onUhfFrequencyChange(uhfFrequencyBuffer.getData());
      onUhfPresetChange(uhfPresetBuffer.getData());
      onClockEtcChange(clockEtcBuffer.getData());
      onClockSsChange(clockSsBuffer.getData());
      onCmsp2Change(cmsp2Buffer.getData());
      break;
    case F16:
      onCmdsChAmountChange(cmdsChAmountBuffer.getData());
      onCmdsFlAmountChange(cmdsFlAmountBuffer.getData());
      onCmdsO1AmountChange(cmdsO1AmountBuffer.getData());
      onCmdsO2AmountChange(cmdsO2AmountBuffer.getData());
      updateDED();
      break;
    case JF17:
      onUfcpLine1Change(ufcpLine1Buffer.getData());
      onUfcpLine2Change(ufcpLine2Buffer.getData());
      onUfcpLine3Change(ufcpLine3Buffer.getData());
      onUfcpLine4Change(ufcpLine4Buffer.getData());
      updateRadio();
      break;
    case FA18:
      onUfcOptionCueing1Change(ufcOptionCueing1Buffer.getData());
      onUfcOptionCueing2Change(ufcOptionCueing2Buffer.getData());
      onUfcOptionCueing3Change(ufcOptionCueing3Buffer.getData());
      onUfcOptionCueing4Change(ufcOptionCueing4Buffer.getData());
      onUfcOptionCueing5Change(ufcOptionCueing5Buffer.getData());
      onUfcOptionDisplay1Change(ufcOptionDisplay1Buffer.getData());
      onUfcOptionDisplay2Change(ufcOptionDisplay2Buffer.getData());
      onUfcOptionDisplay3Change(ufcOptionDisplay3Buffer.getData());
      onUfcOptionDisplay4Change(ufcOptionDisplay4Buffer.getData());
      onUfcOptionDisplay5Change(ufcOptionDisplay5Buffer.getData());
      onUfcScratchpadString1DisplayChange(ufcScratchpadString1DisplayBuffer.getData());
      break;
    }
  }

  DcsBios::loop();

  DED_update = true;
  radioUpdate = true;
  if (!stopped) {
    for (int i = 0; i < 7; i++) {
      uint32_t ledVal = assemble_com(i);
      if (ledVal != ledStatus[i]) {
        ledStatus[i] = ledVal;
        alpha4.writeDigitRaw(i, ledVal);
        alpha4.writeDisplay();
      }
    }
  }

  if (UpdateCounterBuffer.getData() == updateCounter) {
    if (previousCounter > 1000) {
      previousCounter = 0;
      refreshed = true;
      u8g3.clear();
      for (int i = 0; i < 5; i++) {
        TCA9548A(mini_oled_address[i]);
        u8g2.clear();
      }
      for (int i = 0; i < 7; i++) {
        ledStatus[i] = 0x0000;
        alpha4.writeDigitRaw(i, 0x0000);
        alpha4.writeDisplay();
      }
    } else {
      previousCounter += 1;
    }
    stopped = true;
  } else {
    updateCounter = UpdateCounterBuffer.getData();
    previousCounter = 0;
    stopped = false;
  }

}
