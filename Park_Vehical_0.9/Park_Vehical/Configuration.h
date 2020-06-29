#pragma once
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// This file is used to set parameters of perpherials
#define DEBUGLOG
const unsigned long SerialBaudRate = 115200;
// Address of LCD1602, Usually one of <0x3F or 0x20 or 0x27>, you can get more information from manual of model
// LiquidCrystal_I2C lcd(0x20, 16, 2);
// LCD1602  Column 1  Column 2  Column 3 ........
// Row 1	  11		12		  13
// Row 2      21		22		  23
const uint16_t LcdAddress = 0x20;
const uint16_t LcdColumn = 16;
const uint16_t LcdRow = 2;
const uint16_t LcdTimeAfterStart = 5000;
const char* LcdDefaultStr = "Welcome";
const char* LcdEnterPrompt = "Please Enter!";
const char* LcdWorkMode = "Work Mode!";
const char* LcdWorking = "Working! ";
const char* LcdStoreVehical = "Store at:";
const char* LcdGetVehical = "Get at:";
const char* LcdEnterPassWord = "Enter Password";
const char* LcdResetPassWord = "Reset Password";
const char* LcdPressOK = "Please Press * ";
const char* LcdFinished = "Finished!";
const char* LcdDebugMode = "Debug Mode!";
const char* LcdDebugWorkDir = "Work Dir";
const char* LcdDebugInitializeDir = "Initialize Dir";
const char* LcdReInitializeEEPROM = "Clear EEPROM";

const char* LcdError = "Error!";
const char* LcdPassWordWrong = "Password Wrong";
const char* LcdEmpty = "Empty!";
const char* LcdFull = "Full";
const unsigned long LcdDelay = 2000;
char UserInput[LcdColumn] = {0x20};// Space

LiquidCrystal_I2C lcd(0x20, 16, 2);
// Length of PassWord
const uint16_t PasswordLength = 4;
// KeyBoard
// The layout is like Matrix[4*4]
const uint16_t KeyBoardRows = 4;
const uint16_t KeyBoardsColumn = 4;
const uint16_t DebounceTime = 20;
// The content of the keyboard
const char KeyMap[KeyBoardRows][KeyBoardsColumn]
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
	
};

const char DefaultKey = 'Q';

// The Capacity of each level
const uint16_t L1VehicalMax = 8;
const uint16_t L2VehicalMax = 9;
// The Buffer Array of the EEPROM<L2>
uint8_t L2VehicalStatus[L2VehicalMax];
uint8_t L2KeyHighByte[L2VehicalMax];
uint8_t L2KeyLowByte[L2VehicalMax];
// The parameters of L1
const uint64_t L1MotorRotationLoopTimes = 356;  // 40*16 /1.8°
const uint64_t L1MotorRotationDebugLoopTimes = 4;
const uint8_t L1MotorRotationWorkDir = HIGH;
const uint8_t L1MotorRotationInitializeDir = LOW;
// HighDelayms or LowDelayms must >=40 and 
// HighDelayms add LowDelayms must >=200
const uint32_t L1MotorRotationHighDelayms = 800; 
const uint32_t L1MotorRotationLowDelayms = 800;

const uint64_t L1MotorScrewLoopTimes = 3000;
const uint64_t L1MotorScrewDebugLoopTimes = 30;
const uint8_t L1MotorScrewWorkDir = LOW;
const uint8_t L1MotorScrewInitializeDir = HIGH;
const uint32_t L1MotorScrewHighDelayms = 800;
const uint32_t L1MotorScrewLowDelayms = 800;

// The parameters of L2

const uint64_t L2MotorScrewLoopTimes = 3000; 
const uint64_t L2MotorScrewDebugLoopTimes = 30;
const uint8_t L2MotorScrewWorkDir = LOW;
const uint8_t L2MotorScrewInitializeDir = HIGH;
const uint32_t L2MotorScrewHighDelayms = 800;
const uint32_t L2MotorScrewLowDelayms = 800;

const uint64_t L2MainScrewLoopTimes = 136600;
const uint64_t L2MainScrewDebugLoopTimes = 100;
const uint8_t L2MainScrewWorkDir = LOW;
const uint8_t L2MainScrewInitializeDir = HIGH;
const uint32_t L2MainScrewHighDelayms = 800;
const uint32_t L2MainScrewLowDelayms = 800;

const uint64_t L2MotorRotationLoopTimes = 3200; // one Loop 
const uint64_t L2MotorRotationDebugLoopTimes = 320;
const uint8_t L2MotorRotationWorkDir = LOW;
const uint8_t L2MotorRotationInitializeDir = HIGH;
const uint32_t L2MotorRotationHighDelayms = 800;
const uint32_t L2MotorRotationLowDelayms = 800;

// You can get more information from this website:
// https://reprap.org/wiki/File:MksGenV14-Pinout.png
// Pins of the keyboard

const uint32_t rowPins[KeyBoardRows] = { 37, 17, 23, 27 }; 
const uint32_t colPins[KeyBoardsColumn] = { 50, 31, 33, 49 }; 

// Pins of L1
const uint16_t L1EnMotorRotation = 38; 
const uint16_t L1StepMotorRotation = A0;
const uint16_t L1DirMotorRotation = A1;

const uint16_t L1EnMotorScrew = A2; 
const uint16_t L1StepMotorScrew = A6;
const uint16_t L1DirMotorScrew = A7;
// Pins of L2
const uint16_t L2EnMotorScrew = A8; 
const uint16_t L2StepMotorScrew = 46;
const uint16_t L2DirMotorScrew = 48;

const uint16_t L2EnMainScrew = 24;   
const uint16_t L2StepMainScrew = 26;
const uint16_t L2DirMainScrew = 28;

const uint16_t L2EnMotorRotation = 30;   
const uint16_t L2StepMotorRotation = 36;
const uint16_t L2DirMotorRotation = 34;

// EEPROM 
// L1
const uint16_t L1AddressEEPROM[L1VehicalMax] = { 0, 1, 2, 3, 4, 5, 6, 7 }; //L1_0-L1_7
const uint16_t L1MotorRotationEEPROMAddress = 8;
const uint16_t L1KeyAddressLowByte[L1VehicalMax] = { 30, 31, 32, 33, 34, 35, 36, 37 };
const uint16_t L1KeyAddressHighByte[L1VehicalMax] = { 40, 41, 42, 43, 44, 45, 46, 47 };
// L2
const uint16_t L2AddressEEPROM[L2VehicalMax] = { 10, 11, 12, 13, 14, 15, 16, 17, 18 }; //L2_0-L2_9
const uint16_t L2MotorScrewEEPROMAddress = 20;
const uint16_t L2MainScrewEEPROMAddress = 21;
const uint16_t L2MotorRotationEEPROMAddress = 22;
const uint16_t L2KeyAddressLowByte[L2VehicalMax] = { 50, 51, 52, 53, 54, 55, 56, 57, 58 };
const uint16_t L2KeyAddressHighByte[L2VehicalMax] = { 60, 61, 62, 63, 64, 65, 66, 67, 68 };

// EEPROM Default Values
const byte L1MotorRotationEEPROMDefaultPosition = 1;
const byte L2MotorScrewEEPROMDefaultPosition = 0;
const byte L2MainScrewEEPROMDefaultPosition = 0;
const byte L2MotorRotationEEPROMDefaultPosition = 0;
const byte VehicalDefaultStatus = 0;
const byte KeyByteDefault = 1;