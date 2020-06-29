#pragma once
#include "Configuration.h"
#include "InstructionConfiguration.h"
// Clear ArrayUserInput
void ClearUserInput() {
	for (uint16_t i = 0; i < LcdColumn; ++i) {
		UserInput[i] = 0x20;
	}
}
// Set operation function
// Set Content of EEPROM buffer array
void InitializeEEPROMBufferArray()
{
	for (uint16_t i = 0; i < L2VehicalMax; ++i) {
		L2VehicalStatus[i] = EEPROM.read(L2AddressEEPROM[i]);
		L2KeyHighByte[i] = EEPROM.read(L2KeyAddressHighByte[i]);
		L2KeyLowByte[i] = EEPROM.read(L2KeyAddressLowByte[i]);
	}
}
// Set Content of LCD1602
void SetLcdContent(const char* firstLine, const char* secondLine) {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(firstLine);
	lcd.setCursor(1, 0);
	lcd.print(secondLine);
}
// Set Pins and perpherials
void InitializePinsPerPherials() {
	// Pins of the keyboard
	Serial.begin(SerialBaudRate);
	ClearUserInput();
	for (uint16_t row = 0; row < KeyBoardRows; ++row) {
		pinMode(rowPins[row], INPUT_PULLUP);
		// Same effect as digitalWrite(Pin,HIGH);  
	}
	for (uint16_t col = 0; col < KeyBoardsColumn; ++col) {
		pinMode(colPins[col], OUTPUT);
		digitalWrite(colPins[col], HIGH);
	}
	// Pins of L1
	pinMode(L1EnMotorRotation, OUTPUT);
	pinMode(L1StepMotorRotation, OUTPUT);
	pinMode(L1DirMotorRotation, OUTPUT);
	// HIGH means off and vice versa <LOW meas on>
	digitalWrite(L1EnMotorRotation, LOW);

	pinMode(L1EnMotorScrew, OUTPUT);
	pinMode(L1StepMotorScrew, OUTPUT);
	pinMode(L1DirMotorScrew, OUTPUT);
	digitalWrite(L1EnMotorScrew, HIGH);

	// Pins of L2
	pinMode(L2EnMotorScrew, OUTPUT);
	pinMode(L2StepMotorScrew, OUTPUT);
	pinMode(L2DirMotorScrew, OUTPUT);
	digitalWrite(L2EnMotorScrew, HIGH);

	pinMode(L2EnMainScrew, OUTPUT);
	pinMode(L2StepMainScrew, OUTPUT);
	pinMode(L2DirMainScrew, OUTPUT);
	digitalWrite(L2EnMainScrew, LOW);

	pinMode(L2EnMotorRotation, OUTPUT);
	pinMode(L2StepMotorRotation, OUTPUT);
	pinMode(L2DirMotorRotation, OUTPUT);
	digitalWrite(L2EnMotorRotation, LOW);

	InitializeEEPROMBufferArray();

	// Initialize the LCD1602 model 
	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print(LcdDefaultStr);
	delay(LcdTimeAfterStart);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(LcdWorkMode);
}
// Reset content of EEPROM
// Warning : make sure that you know what are you doing!
void ReinitializeEEPROM() {
	SetLcdContent(LcdDebugMode, LcdReInitializeEEPROM);
	EEPROM.write(L1MotorRotationEEPROMAddress, L1MotorRotationEEPROMDefaultPosition);
	EEPROM.write(L2MotorScrewEEPROMAddress, L2MotorScrewEEPROMDefaultPosition);
	EEPROM.write(L2MainScrewEEPROMAddress, L2MainScrewEEPROMDefaultPosition);
	EEPROM.write(L2MotorRotationEEPROMAddress, L2MotorRotationEEPROMDefaultPosition);
	for (uint16_t i = 0; i < L1VehicalMax; ++i) {
		EEPROM.write(L1AddressEEPROM[i], VehicalDefaultStatus);
		EEPROM.write(L1KeyAddressHighByte[i], (KeyByteDefault * 10) + i);
		EEPROM.write(L1KeyAddressLowByte[i], (KeyByteDefault * 10) + i);
	}
	for (uint16_t i = 0; i < L2VehicalMax; ++i) {
		EEPROM.write(L2AddressEEPROM[i], VehicalDefaultStatus);
		EEPROM.write(L2KeyAddressHighByte[i], (KeyByteDefault + 1) * 10 + i);
		EEPROM.write(L2KeyAddressLowByte[i], (KeyByteDefault + 1) * 10 + i);
	}
}
// Make sure L2 is full
bool IsL2Full()
{
	return (EEPROM.read(L2MotorScrewEEPROMAddress) == 1);
}
// Array Reverse
void ArrayReverse(byte arr[], uint16_t begin, uint16_t end)
{
	uint16_t i = 0, j = 0;
	for (i = begin, j = end; i<j; i++, j--) {
		arr[i] = arr[i] ^ arr[j];
		arr[j] = arr[i] ^ arr[j];
		arr[i] = arr[i] ^ arr[j];
	}
}
void ArrayLeftShift(byte arr[], uint16_t count, uint16_t length) {
	ArrayReverse(arr, 0, count - 1);
	ArrayReverse(arr, count, length - 1);
	ArrayReverse(arr, 0, length - 1);
}
void ArrayRightShift(byte arr[], uint16_t count, uint16_t length) {
	ArrayReverse(arr, length-count, length - 1);
	ArrayReverse(arr, 0, count);
	ArrayReverse(arr, 0, length - 1);
}

// Set status of L2 (include EEPROM operation) Swift by count(offset)
void SetL2Status(byte L2Status[], uint16_t count)
{	// >>count
	// 1.[length-count:length-1] Reverse Sequence
	// 2.[0:count] Reverse Sequence
	// 3.Entire Array Reverse Sequence
	ArrayRightShift(L2Status, count, L2VehicalMax);

	for (uint16_t i = 0; i < L2VehicalMax; i++)
	{
		EEPROM.write(L2AddressEEPROM[i], L2Status[i]);
	}
}
// Set KeyLowByte of L2 (include EEPROM operation) Swift by count(offset)
void SetL2KeyLowByte(byte L2KeyLowByte[], uint16_t count)
{
	ArrayRightShift(L2KeyLowByte, count, L2VehicalMax);
	for (uint16_t i = 0; i < L2VehicalMax; i++)
	{
		EEPROM.write(L2KeyAddressLowByte[i], L2KeyLowByte[i]);
	}
}
// Set KeyHighByte of L2 (include EEPROM operation) Swift by count(offset)
void SetL2KeyHighByte(byte L2KeyHighByte[], uint16_t count)
{
	ArrayRightShift(L2KeyHighByte, count, L2VehicalMax);
	for (uint16_t i = 0; i < L2VehicalMax; i++)
	{
		EEPROM.write(L2KeyAddressHighByte[i], L2KeyHighByte[i]);
	}
}

// Get operation function
// Get character from matrix keyboard
char GetKeyBoardCharacter() {
	char character = DefaultKey;
	for (uint16_t column = 0; column < KeyBoardsColumn; column++)
	{
		digitalWrite(colPins[column], LOW);
		for (uint16_t row = 0; row < KeyBoardRows; row++)
		{
			if (digitalRead(rowPins[row]) == LOW)
			{
				delay(DebounceTime);
				while (digitalRead(rowPins[row]) == LOW);
				character = KeyMap[row][column];
			}
		}
		digitalWrite(colPins[column], HIGH);
	}
	return character;
}
// Get String from matrix keyboard
void GetKeyBoardInstructionString() {
	int index = 0;
	while (true) {
		char character = GetKeyBoardCharacter();
		// '*'means ok, '#' means ResetKey, 'D' means BackSpace, 'C' means Exit
		if ((character != KeyMap[3][0]) && (character != KeyMap[3][2]) &&
			(character != KeyMap[3][3]) && (character != KeyMap[2][3]) &&
			(character != DefaultKey)) {
			UserInput[index]=character;
			SetLcdContent(LcdEnterPrompt, UserInput);
			++index;
		}
		else if (character == KeyMap[3][3]) {
			// BackSpace
			--index;
			UserInput[index] = ' ';
			SetLcdContent(LcdEnterPrompt, UserInput);
		}
		else if (character == KeyMap[3][2]) {
			// Reset Password
			ClearUserInput();
			UserInput[0] = KeyMap[3][2];
		}
		else if (character == KeyMap[2][3]) {
			// Exit
			ClearUserInput();
			break;
		}
		else if (character != KeyMap[3][0]) {
			// OK
			// Now we get the stable char array outside
			break;
		}
		// If the array is full,just update the last element
		if (index == LcdColumn) {
			index = (LcdColumn - 1);
		}
	}
}
// Move operation function through PWM
// L1MotorRotation
void L1MotorRotationWork() {
	SetLcdContent(LcdWorkMode, LcdWorking);
	digitalWrite(L1EnMotorRotation, LOW);
	digitalWrite(L1DirMotorRotation, L1MotorRotationWorkDir);
	for (uint64_t i = 0; i < L1MotorRotationLoopTimes; ++i) {
		digitalWrite(L1StepMotorRotation, HIGH);
		delayMicroseconds(L1MotorRotationHighDelayms);
		digitalWrite(L1StepMotorRotation, LOW);
		delayMicroseconds(L1MotorRotationHighDelayms);
	}
}
void L1MotorRotationInitialize() {
	digitalWrite(L1EnMotorRotation, LOW);
	digitalWrite(L1DirMotorRotation, L1MotorRotationInitializeDir);
	for (uint64_t i = 0; i < L1MotorRotationLoopTimes; ++i) {
		digitalWrite(L1StepMotorRotation, HIGH);
		delayMicroseconds(L1MotorRotationHighDelayms);
		digitalWrite(L1StepMotorRotation, LOW);
		delayMicroseconds(L1MotorRotationHighDelayms);
	}
}
void L1MotorRotation(uint8_t targetPos) {
	int8_t movementDirection = targetPos - EEPROM.read(L1MotorRotationEEPROMAddress);
	uint8_t movementAmplitude = abs(movementDirection);
	if (movementAmplitude != 0) {
		// need move to new position
		if (movementDirection > 0)
		{
			for (uint8_t i = 0; i < movementAmplitude; ++i)
			{
				L1MotorRotationWork();
			}
		}
		else 
		{
			for (uint8_t i = 0; i < movementAmplitude; ++i)
			{
				L1MotorRotationInitialize();
			}
		}
		EEPROM.write(L1MotorRotationEEPROMAddress,targetPos);
	}
}
// Debug
void L1MotorRotationDebugWork() {
	digitalWrite(L1EnMotorRotation, LOW);
	digitalWrite(L1DirMotorRotation, L1MotorRotationWorkDir);
	for (uint64_t i = 0; i < L1MotorRotationDebugLoopTimes; ++i) {
		digitalWrite(L1StepMotorRotation, HIGH);
		delayMicroseconds(L1MotorRotationHighDelayms);
		digitalWrite(L1StepMotorRotation, LOW);
		delayMicroseconds(L1MotorRotationHighDelayms);
	}
}
void L1MotorRotationDebugInitialize() {
	digitalWrite(L1EnMotorRotation, LOW);
	digitalWrite(L1DirMotorRotation, L1MotorRotationInitializeDir);
	for (uint64_t i = 0; i < L1MotorRotationDebugLoopTimes; ++i) {
		digitalWrite(L1StepMotorRotation, HIGH);
		delayMicroseconds(L1MotorRotationHighDelayms);
		digitalWrite(L1StepMotorRotation, LOW);
		delayMicroseconds(L1MotorRotationHighDelayms);
	}
}
// L1MotorScrew
void L1MotorScrewWork() {
	digitalWrite(L1EnMotorScrew, LOW);
	digitalWrite(L1DirMotorScrew, L1MotorScrewWorkDir);
	for (uint16_t i = 0; i < L1MotorScrewLoopTimes; ++i) {
		digitalWrite(L1StepMotorScrew, HIGH);
		delayMicroseconds(L1MotorScrewHighDelayms);
		digitalWrite(L1StepMotorScrew, LOW);
		delayMicroseconds(L1MotorScrewHighDelayms);
	}
	digitalWrite(L1EnMotorScrew, HIGH);
}
void L1MotorScrewInitialize() {
	digitalWrite(L1EnMotorScrew, LOW);
	digitalWrite(L1DirMotorScrew, L1MotorScrewInitializeDir);
	for (uint16_t i = 0; i < L1MotorScrewLoopTimes; ++i) {
		digitalWrite(L1StepMotorScrew, HIGH);
		delayMicroseconds(L1MotorScrewHighDelayms);
		digitalWrite(L1StepMotorScrew, LOW);
		delayMicroseconds(L1MotorScrewHighDelayms);
	}
	digitalWrite(L1EnMotorScrew, HIGH);
}
// Debug
void L1MotorScrewDebugWork() {
	digitalWrite(L1EnMotorScrew, LOW);
	digitalWrite(L1DirMotorScrew, L1MotorScrewWorkDir);
	for (uint16_t i = 0; i < L1MotorScrewDebugLoopTimes; ++i) {
		digitalWrite(L1StepMotorScrew, HIGH);
		delayMicroseconds(L1MotorScrewHighDelayms);
		digitalWrite(L1StepMotorScrew, LOW);
		delayMicroseconds(L1MotorScrewHighDelayms);
	}
	digitalWrite(L1EnMotorScrew, HIGH);
}
void L1MotorScrewDebugInitialize() {
	digitalWrite(L1EnMotorScrew, LOW);
	digitalWrite(L1DirMotorScrew, L1MotorScrewInitializeDir);
	for (uint16_t i = 0; i < L1MotorScrewDebugLoopTimes; ++i) {
		digitalWrite(L1StepMotorScrew, HIGH);
		delayMicroseconds(L1MotorScrewHighDelayms);
		digitalWrite(L1StepMotorScrew, LOW);
		delayMicroseconds(L1MotorScrewHighDelayms);
	}
	digitalWrite(L1EnMotorScrew, HIGH);
}
// L2MotorScrew
void L2MotorScrewWork() {
	digitalWrite(L2EnMotorScrew, LOW);
	digitalWrite(L2DirMotorScrew, L2MotorScrewWorkDir);
	for (uint16_t i = 0; i < L2MotorScrewLoopTimes; ++i) {
		digitalWrite(L2StepMotorScrew, HIGH);
		delayMicroseconds(L2MotorScrewHighDelayms);
		digitalWrite(L2StepMotorScrew, LOW);
		delayMicroseconds(L2MotorScrewLowDelayms);
	}
	digitalWrite(L2EnMotorScrew, HIGH);
}
void L2MotorScrewInitialize() {
	digitalWrite(L2EnMotorScrew, LOW);
	digitalWrite(L2DirMotorScrew, L2MotorScrewInitializeDir);
	for (uint16_t i = 0; i < L2MotorScrewLoopTimes; ++i) {
		digitalWrite(L2StepMotorScrew, HIGH);
		delayMicroseconds(L2MotorScrewHighDelayms);
		digitalWrite(L2StepMotorScrew, LOW);
		delayMicroseconds(L2MotorScrewLowDelayms);
	}
	digitalWrite(L2EnMotorScrew, HIGH);
}
// Debug
void L2MotorScrewDebugWork() {
	digitalWrite(L2EnMotorScrew, LOW);
	digitalWrite(L2DirMotorScrew, L2MotorScrewWorkDir);
	for (uint16_t i = 0; i < L2MotorScrewDebugLoopTimes; ++i) {
		digitalWrite(L2StepMotorScrew, HIGH);
		delayMicroseconds(L2MotorScrewHighDelayms);
		digitalWrite(L2StepMotorScrew, LOW);
		delayMicroseconds(L2MotorScrewLowDelayms);
	}
	digitalWrite(L2EnMotorScrew, HIGH);
}
void L2MotorScrewDebugInitialize() {
	digitalWrite(L2EnMotorScrew, LOW);
	digitalWrite(L2DirMotorScrew, L2MotorScrewInitializeDir);
	for (uint16_t i = 0; i < L2MotorScrewDebugLoopTimes; ++i) {
		digitalWrite(L2StepMotorScrew, HIGH);
		delayMicroseconds(L2MotorScrewHighDelayms);
		digitalWrite(L2StepMotorScrew, LOW);
		delayMicroseconds(L2MotorScrewLowDelayms);
	}
	digitalWrite(L2EnMotorScrew, HIGH);
}
// L2MainScrew
void L2MainScrewWork() {
	digitalWrite(L2EnMainScrew, LOW);
	digitalWrite(L2DirMainScrew, L2MainScrewWorkDir);
	for (uint16_t i = 0; i < L2MainScrewLoopTimes; ++i) {
		digitalWrite(L2StepMainScrew, HIGH);
		delayMicroseconds(L2MainScrewHighDelayms);
		digitalWrite(L2StepMainScrew, LOW);
		delayMicroseconds(L2MainScrewLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
void L2MainScrewInitialize() {
	digitalWrite(L2EnMainScrew, LOW);
	digitalWrite(L2DirMainScrew, L2MainScrewInitializeDir);
	for (uint16_t i = 0; i < L2MainScrewLoopTimes; ++i) {
		digitalWrite(L2StepMainScrew, HIGH);
		delayMicroseconds(L2MainScrewHighDelayms);
		digitalWrite(L2StepMainScrew, LOW);
		delayMicroseconds(L2MainScrewLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
// Debug
void L2MainScrewDebugWork() {
	digitalWrite(L2EnMainScrew, LOW);
	digitalWrite(L2DirMainScrew, L2MainScrewWorkDir);
	for (uint16_t i = 0; i < L2MainScrewDebugLoopTimes; ++i) {
		digitalWrite(L2StepMainScrew, HIGH);
		delayMicroseconds(L2MainScrewHighDelayms);
		digitalWrite(L2StepMainScrew, LOW);
		delayMicroseconds(L2MainScrewLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
void L2MainScrewDebugInitialize() {
	digitalWrite(L2EnMainScrew, LOW);
	digitalWrite(L2DirMainScrew, L2MainScrewInitializeDir);
	for (uint16_t i = 0; i < L2MainScrewDebugLoopTimes; ++i) {
		digitalWrite(L2StepMainScrew, HIGH);
		delayMicroseconds(L2MainScrewHighDelayms);
		digitalWrite(L2StepMainScrew, LOW);
		delayMicroseconds(L2MainScrewLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
// L2MotorRotation
void L2MotorRotationWork() {
	digitalWrite(L2EnMotorRotation, LOW);
	digitalWrite(L2DirMotorRotation, L2MotorRotationWorkDir);
	for (uint16_t i = 0; i < L2MotorRotationLoopTimes; ++i) {
		digitalWrite(L2StepMotorRotation, HIGH);
		delayMicroseconds(L2MotorRotationHighDelayms);
		digitalWrite(L2StepMotorRotation, LOW);
		delayMicroseconds(L2MotorRotationLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
void L2MotorRotationInitialize() {
	digitalWrite(L2EnMotorRotation, LOW);
	digitalWrite(L2DirMotorRotation, L2MotorRotationInitializeDir);
	for (uint16_t i = 0; i < L2MotorRotationLoopTimes; ++i) {
		digitalWrite(L2StepMotorRotation, HIGH);
		delayMicroseconds(L2MotorRotationHighDelayms);
		digitalWrite(L2StepMotorRotation, LOW);
		delayMicroseconds(L2MotorRotationLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
void L2MotorRotation(uint8_t targetPos) {
		for (uint8_t i = 0; i < targetPos; ++i) {
			L2MotorRotationWork();
		}
}
// Debug
void L2MotorRotationDebugWork() {
	digitalWrite(L2EnMotorRotation, LOW);
	digitalWrite(L2DirMotorRotation, L2MotorRotationWorkDir);
	for (uint16_t i = 0; i < L2MotorRotationDebugLoopTimes; ++i) {
		digitalWrite(L2StepMotorRotation, HIGH);
		delayMicroseconds(L2MotorRotationHighDelayms);
		digitalWrite(L2StepMotorRotation, LOW);
		delayMicroseconds(L2MotorRotationLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}
void L2MotorRotationDebugInitialize() {
	digitalWrite(L2EnMotorRotation, LOW);
	digitalWrite(L2DirMotorRotation, L2MotorRotationInitializeDir);
	for (uint16_t i = 0; i < L2MotorRotationDebugLoopTimes; ++i) {
		digitalWrite(L2StepMotorRotation, HIGH);
		delayMicroseconds(L2MotorRotationHighDelayms);
		digitalWrite(L2StepMotorRotation, LOW);
		delayMicroseconds(L2MotorRotationLowDelayms);
	}
	//digitalWrite(L2EnMainScrew, HIGH);
}

// Other operation
uint16_t GetInstructionContent() {
	// Debug Instruction
	if (strcmp(UserInput, InstructionDebugModePassWord)) { return StatusDebugModePassWord; }
	if (strcmp(UserInput, InstructionDebugL1MotorRotation)) { return StatusDebugL1MotorRotation; }
	if (strcmp(UserInput, InstructionDebugL1MotorScrew)) { return StatusDebugL1MotorScrew; }
	if (strcmp(UserInput, InstructionDebugL2MotorScrew)) { return StatusDebugL2MotorScrew; }
	if (strcmp(UserInput, InstructionDebugL2MainScrew)) { return StatusDebugL2MainScrew; }
	if (strcmp(UserInput, InstructionDebugL2MotorRotation)) { return StatusDebugL2MotorRotation; }
	if (strcmp(UserInput, InstructionDebugClearEEPROM)) { return StatusDebugClearEEPROM; }
	// Work Instruction
	// Position Select L1
	if (strcmp(UserInput, InstructionPositionL1P1)) { return StatusPositionL1P1; }
	if (strcmp(UserInput, InstructionPositionL1P2)) { return StatusPositionL1P2; }
	if (strcmp(UserInput, InstructionPositionL1P3)) { return StatusPositionL1P3; }
	if (strcmp(UserInput, InstructionPositionL1P4)) { return StatusPositionL1P4; }
	if (strcmp(UserInput, InstructionPositionL1P5)) { return StatusPositionL1P5; }
	if (strcmp(UserInput, InstructionPositionL1P6)) { return StatusPositionL1P6; }
	if (strcmp(UserInput, InstructionPositionL1P7)) { return StatusPositionL1P7; }
	if (strcmp(UserInput, InstructionPositionL1P8)) { return StatusPositionL1P8; }
	// Position Select L2
	if (strcmp(UserInput, InstructionPositionL2P0)) { return StatusPositionL2P0; }
	if (strcmp(UserInput, InstructionPositionL2P1)) { return StatusPositionL2P1; }
	if (strcmp(UserInput, InstructionPositionL2P2)) { return StatusPositionL2P2; }
	if (strcmp(UserInput, InstructionPositionL2P3)) { return StatusPositionL2P3; }
	if (strcmp(UserInput, InstructionPositionL2P4)) { return StatusPositionL2P4; }
	if (strcmp(UserInput, InstructionPositionL2P5)) { return StatusPositionL2P5; }
	if (strcmp(UserInput, InstructionPositionL2P6)) { return StatusPositionL2P6; }
	if (strcmp(UserInput, InstructionPositionL2P7)) { return StatusPositionL2P7; }
	if (strcmp(UserInput, InstructionPositionL2P8)) { return StatusPositionL2P8; }
	// Special Instruction
	if (strcmp(UserInput, " ")) { return StatusInstructionExit; }
	if (strcmp(UserInput, "*")) { return StatusInstructionResetPassWord; }
	else { return StatusInstructionERROR; }
}

inline void LogOut(const char *const arr) {
#ifdef DEBUGLOG
	Serial.println(arr);
#endif // !DEBUGLOG
}