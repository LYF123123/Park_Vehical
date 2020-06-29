#pragma once
// This file is used to set instruction
const char* InstructionDebugModePassWord = "7355608";		const uint16_t StatusDebugModePassWord = 0xE3;
// Debug Instruction
// Motor Select L1
const char* InstructionDebugL1MotorRotation = "A1";			const uint16_t StatusDebugL1MotorRotation = 0xA1;
const char* InstructionDebugL1MotorScrew = "A2";			const uint16_t StatusDebugL1MotorScrew = 0xA2;
// Motor Select L2
const char* InstructionDebugL2MotorScrew = "B1";			const uint16_t StatusDebugL2MotorScrew = 0xB1;
const char* InstructionDebugL2MainScrew = "B2";				const uint16_t StatusDebugL2MainScrew = 0xB2;
const char* InstructionDebugL2MotorRotation = "B3";			const uint16_t StatusDebugL2MotorRotation = 0xB3;
// Movement Instruction
const char  InstructionDebugWorkDirection = 'A';			// Only one character can use GetKeyBoardCharacter()
const char  InstructionDebugInitializeDirection = 'B';
// Clear entire EEPROM
const char* InstructionDebugClearEEPROM = "AA";				const uint16_t StatusDebugClearEEPROM = 0xAA;

// Work Instruction
// Position Select L1
const char* InstructionPositionL1P1 = "11";				const uint16_t StatusPositionL1P1 = 0xC1;
const char* InstructionPositionL1P2 = "12";				const uint16_t StatusPositionL1P2 = 0xC2;
const char* InstructionPositionL1P3 = "13";				const uint16_t StatusPositionL1P3 = 0xC3;
const char* InstructionPositionL1P4 = "14";				const uint16_t StatusPositionL1P4 = 0xC4;
const char* InstructionPositionL1P5 = "15";				const uint16_t StatusPositionL1P5 = 0xC5;
const char* InstructionPositionL1P6 = "16";				const uint16_t StatusPositionL1P6 = 0xC6;
const char* InstructionPositionL1P7 = "17";				const uint16_t StatusPositionL1P7 = 0xC7;
const char* InstructionPositionL1P8 = "18";				const uint16_t StatusPositionL1P8 = 0xC8;
// Position Select L2
const char* InstructionPositionL2P0 = "20";				const uint16_t StatusPositionL2P0 = 0xD0;
const char* InstructionPositionL2P1 = "21";				const uint16_t StatusPositionL2P1 = 0xD1;
const char* InstructionPositionL2P2 = "22";				const uint16_t StatusPositionL2P2 = 0xD2;
const char* InstructionPositionL2P3 = "23";				const uint16_t StatusPositionL2P3 = 0xD3;
const char* InstructionPositionL2P4 = "24";				const uint16_t StatusPositionL2P4 = 0xD4;
const char* InstructionPositionL2P5 = "25";				const uint16_t StatusPositionL2P5 = 0xD5;
const char* InstructionPositionL2P6 = "26";				const uint16_t StatusPositionL2P6 = 0xD6;
const char* InstructionPositionL2P7 = "27";				const uint16_t StatusPositionL2P7 = 0xD7;
const char* InstructionPositionL2P8 = "28";				const uint16_t StatusPositionL2P8 = 0xD8;

														const uint16_t StatusInstructionERROR = 0xE0;
const char ResetPassWord = '#';							const uint16_t StatusInstructionResetPassWord = 0xE1;
const char Exit='C';									const uint16_t StatusInstructionExit = 0xE2;