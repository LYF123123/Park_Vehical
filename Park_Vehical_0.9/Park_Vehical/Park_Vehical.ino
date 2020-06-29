/*
 Name:		Park_Vehical.ino
 Created:	2020/6/8 20:11:45
 Author:	luyif
*/
#include "Function.hpp"
// the setup function runs once when you press reset or power the board
void setup() {
	InitializePinsPerPherials();
}

// the loop function runs over and over again until power down or reset
void loop() {
	GetKeyBoardInstructionString();
	switch (GetInstructionContent())
	{
	case StatusDebugModePassWord:
		SetLcdContent(LcdDebugMode,"");
		ClearUserInput();
		GetKeyBoardInstructionString();
		switch (GetInstructionContent())
		{
			ClearUserInput();
			char inst = DefaultKey;
		case StatusDebugL1MotorRotation:
			while ((inst=GetKeyBoardCharacter()) != Exit)
			{
				if (inst== InstructionDebugWorkDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugWorkDir);
					L1MotorRotationDebugWork();
				}
				if (inst == InstructionDebugInitializeDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugInitializeDir);
					L1MotorRotationDebugInitialize();
				}
			}
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusDebugL1MotorScrew:
			while ((inst = GetKeyBoardCharacter()) != Exit)
			{
				if (inst == InstructionDebugWorkDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugWorkDir);
					L1MotorScrewDebugWork();
				}
				if (inst == InstructionDebugInitializeDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugInitializeDir);
					L1MotorScrewDebugInitialize();
				}
			}
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusDebugL2MotorScrew:
			while ((inst = GetKeyBoardCharacter()) != Exit)
			{
				if (inst == InstructionDebugWorkDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugWorkDir);
					L2MotorScrewDebugWork();
				}
				if (inst == InstructionDebugInitializeDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugInitializeDir);
					L2MotorScrewDebugInitialize();
				}
			}
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusDebugL2MainScrew:
			while ((inst = GetKeyBoardCharacter()) != Exit)
			{
				if (inst == InstructionDebugWorkDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugWorkDir);
					L2MainScrewDebugWork();
				}
				if (inst == InstructionDebugInitializeDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugInitializeDir);
					L2MainScrewDebugInitialize();
				}
			}
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusDebugL2MotorRotation:
			while ((inst = GetKeyBoardCharacter()) != Exit)
			{
				if (inst == InstructionDebugWorkDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugWorkDir);
					L2MotorRotationDebugWork();
				}
				if (inst == InstructionDebugInitializeDirection)
				{
					SetLcdContent(LcdDebugMode, LcdDebugInitializeDir);
					L2MotorRotationDebugInitialize();
				}
			}
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusDebugClearEEPROM:
			ReinitializeEEPROM();
			SetLcdContent(LcdDebugMode, "");
			break;
		case StatusInstructionExit:
			// Just Exit
			SetLcdContent(LcdDebugMode, "");
			break;
		}
		break;
	// Work Instruction
	// Position Select L1
	case StatusPositionL1P1:
		if (EEPROM.read(L1AddressEEPROM[0]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P1");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter()!='*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[0], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength]="";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[0]) * 100) + EEPROM.read(L1KeyAddressLowByte[0]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit!=NULL)||(reset!=reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode,"");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P1");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[0], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P2:
		if (EEPROM.read(L1AddressEEPROM[1]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P2");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[1], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[1]) * 100) + EEPROM.read(L1KeyAddressLowByte[1]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P2");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[1], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P3:
		if (EEPROM.read(L1AddressEEPROM[2]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P3");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[2], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[2]) * 100) + EEPROM.read(L1KeyAddressLowByte[2]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P3");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[2], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P4:
		if (EEPROM.read(L1AddressEEPROM[3]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P4");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[3], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[3]) * 100) + EEPROM.read(L1KeyAddressLowByte[3]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P4");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[3], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P5:
		if (EEPROM.read(L1AddressEEPROM[4]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P5");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[4], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[4]) * 100) + EEPROM.read(L1KeyAddressLowByte[4]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P5");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[4], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P6:
		if (EEPROM.read(L1AddressEEPROM[5]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P6");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[5], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[5]) * 100) + EEPROM.read(L1KeyAddressLowByte[5]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P6");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[5], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P7:
		if (EEPROM.read(L1AddressEEPROM[6]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P7");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[6], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[6]) * 100) + EEPROM.read(L1KeyAddressLowByte[6]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P7");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[6], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL1P8:
		if (EEPROM.read(L1AddressEEPROM[7]) == 0) {
			SetLcdContent(LcdStoreVehical, "L1P8");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L1MotorRotation(1);
			L1MotorScrewWork();
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			L1MotorScrewInitialize();
			SetLcdContent(LcdWorkMode, LcdFinished);
			EEPROM.write(L1AddressEEPROM[7], 1);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L1KeyAddressHighByte[7]) * 100) + EEPROM.read(L1KeyAddressLowByte[7]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L1P8");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L1MotorRotation(1);
				L1MotorScrewWork();
				while (GetKeyBoardCharacter() != '*')
				{
					SetLcdContent(LcdPressOK, "");
				}
				L1MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
				EEPROM.write(L1AddressEEPROM[7], 0);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	// Position Select L2
	case StatusPositionL2P0:
		InitializeEEPROMBufferArray();
		if (IsL2Full())
		{	// Get Vehical
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[0]) * 100) + EEPROM.read(L2KeyAddressLowByte[0]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P0");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				EEPROM.write(L2MotorScrewEEPROMAddress, 0);
				EEPROM.write(L2AddressEEPROM[0], 0);
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		else
		{	// Store Vehical
			while (GetKeyBoardCharacter() != '*')
			{
				SetLcdContent(LcdPressOK, "");
			}
			SetLcdContent(LcdStoreVehical,"");
			delay(LcdDelay);
			SetLcdContent(LcdWorking, "");
			L2MotorScrewWork();
			L2MainScrewWork();
			uint8_t index = 0;
			L2VehicalStatus[0] = 1;
			while (L2VehicalStatus[index] != 0)
			{
				L2MotorRotationWork();
				++index;
				if (index == L2VehicalMax) {
					// full
					SetLcdContent(LcdWorkMode, LcdFinished);
					EEPROM.write(L2MotorScrewEEPROMAddress, 1);
					break;
				}
			}
			SetL2Status(L2VehicalStatus, index);
			SetL2KeyHighByte(L2KeyHighByte, index);
			SetL2KeyLowByte(L2KeyLowByte, index);
			if (EEPROM.read(L2MotorScrewEEPROMAddress) == 0)
			{
				L2MotorScrewInitialize();
				L2MainScrewInitialize();
			}
		}
		ClearUserInput();
		break;
		// COPY AND COPY
	case StatusPositionL2P1:
		if (EEPROM.read(L2AddressEEPROM[1]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[1]) * 100) + EEPROM.read(L2KeyAddressLowByte[1]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P1");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(1);
				SetL2Status(L2VehicalStatus, 1);
				SetL2KeyHighByte(L2KeyHighByte, 1);
				SetL2KeyLowByte(L2KeyLowByte, 1);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P2:
		if (EEPROM.read(L2AddressEEPROM[2]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[2]) * 100) + EEPROM.read(L2KeyAddressLowByte[2]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P2");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(1);
				SetL2Status(L2VehicalStatus, 2);
				SetL2KeyHighByte(L2KeyHighByte, 2);
				SetL2KeyLowByte(L2KeyLowByte, 2);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P3:
		if (EEPROM.read(L2AddressEEPROM[3]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[3]) * 100) + EEPROM.read(L2KeyAddressLowByte[3]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P3");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(3);
				SetL2Status(L2VehicalStatus, 3);
				SetL2KeyHighByte(L2KeyHighByte, 3);
				SetL2KeyLowByte(L2KeyLowByte, 3);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P4:
		if (EEPROM.read(L2AddressEEPROM[4]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[4]) * 100) + EEPROM.read(L2KeyAddressLowByte[4]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P4");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(4);
				SetL2Status(L2VehicalStatus, 4);
				SetL2KeyHighByte(L2KeyHighByte, 4);
				SetL2KeyLowByte(L2KeyLowByte, 4);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P5:
		if (EEPROM.read(L2AddressEEPROM[5]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[5]) * 100) + EEPROM.read(L2KeyAddressLowByte[5]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P5");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(5);
				SetL2Status(L2VehicalStatus, 5);
				SetL2KeyHighByte(L2KeyHighByte, 5);
				SetL2KeyLowByte(L2KeyLowByte, 5);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P6:
		if (EEPROM.read(L2AddressEEPROM[6]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[6]) * 100) + EEPROM.read(L2KeyAddressLowByte[6]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P6");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(6);
				SetL2Status(L2VehicalStatus, 6);
				SetL2KeyHighByte(L2KeyHighByte, 6);
				SetL2KeyLowByte(L2KeyLowByte, 6);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P7:
		if (EEPROM.read(L2AddressEEPROM[7]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[7]) * 100) + EEPROM.read(L2KeyAddressLowByte[7]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P7");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(7);
				SetL2Status(L2VehicalStatus, 7);
				SetL2KeyHighByte(L2KeyHighByte, 7);
				SetL2KeyLowByte(L2KeyLowByte, 7);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
	case StatusPositionL2P8:
		if (EEPROM.read(L2AddressEEPROM[8]) == 0) {
			SetLcdContent(LcdError, LcdEmpty);
			delay(LcdDelay);
		}
		else
		{
			SetLcdContent(LcdEnterPassWord, "");
			ClearUserInput();
			GetKeyBoardInstructionString();
			char pwd[PasswordLength] = "";
			uint16_t pwdEEPRom = (EEPROM.read(L2KeyAddressHighByte[8]) * 100) + EEPROM.read(L2KeyAddressLowByte[8]);
			itoa(pwdEEPRom, pwd, DEC);
			char *exit;
			char *reset;
			exit = strchr(UserInput, Exit);
			reset = strchr(UserInput, ResetPassWord);
			if ((exit != NULL) || (reset != reset)) {
				// EXIT
				SetLcdContent(LcdWorkMode, "");
			}
			else if (strcmp(UserInput, pwd)) {
				// Right PassWord
				SetLcdContent(LcdGetVehical, "L2P8");
				delay(LcdDelay);
				SetLcdContent(LcdWorking, "");
				if (!IsL2Full()) {
					L2MotorScrewWork();
					L2MainScrewWork();
				}
				L2MotorRotation(8);
				SetL2Status(L2VehicalStatus, 8);
				SetL2KeyHighByte(L2KeyHighByte, 8);
				SetL2KeyLowByte(L2KeyLowByte, 8);
				L2MainScrewInitialize();
				L2MotorScrewInitialize();
				SetLcdContent(LcdWorkMode, LcdFinished);
			}
			else
			{	// Wrong PassWord
				SetLcdContent(LcdError, LcdPassWordWrong);
			}
		}
		ClearUserInput();
		break;
        // Instruction ReserPassword
	case StatusInstructionResetPassWord:
		SetLcdContent(LcdResetPassWord, "Unfinish ");

		break; 
	case StatusInstructionERROR:
		// Instruction ERROR
		break;
	default:
		// Unknown ERROR
		break;
	}
}
