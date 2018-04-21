#include <connexion/connexionPLCdatahandler.h>
#include "string.h" // for memcpy
#include "stdlib.h" // for strtol


static byte Mask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

//****************************************************************************

// Get Text description of PLC Type
std::string S7::GetTxtPLCType(short int plcType) {
	switch (plcType) {
	case  PLC_300_400:
		return "S7 300/400";
		break;

	case  PLC_1200_1500:
		return "S7 1200/1500";
		break;

	case  PLC_LOGO_200:
		return "LOGO/S7 200";
		break;

	case  PLC_SINAMICS:
		return "SINAMICS";
		break;
	default:
		return "Default"; // to avoid warning
		break;

	}
}

//****************************************************************************

// Get data type size in bytes of the specified type
int S7::GetDataTypeSize(int type) {
	int size = 0; // for unknown type return 0

	switch (type) {
	case  TYPE_BOOL:
	case  TYPE_BYTE:
	case  TYPE_SINT:
		size = 1;
		break;

	case  TYPE_WORD:
	case  TYPE_UINT:
	case  TYPE_INT:
		size = 2;
		break;

	case  TYPE_DWORD:
	case  TYPE_UDINT:
	case  TYPE_DINT:
	case  TYPE_REAL:
		size = 4;
		break;

	case  TYPE_LWORD:
	case  TYPE_ULINT:
	case  TYPE_LINT:
	case  TYPE_LREAL:
		size = 8;
		break;

	};

	return size;
}

//****************************************************************************

// Get the word from Transport Service Access Point (TSAP) in hex format, e.g: 10.02 => 0x1002, used by Cli_SetConnectionParams
// Enter TSAP in format ##.## in hex
// Return: the TSAP number in a word and decimal format
uint16_t S7::GetWordFromTSAP(std::string TSAP) {
	size_t pos = TSAP.find('.'); // find the delimiter into the source string

	if (pos == std::string::npos) { // no delimiter was found, return 0
		return 0;
	} else { // was found '.'
		short usepos=pos;
		std::string first = TSAP.substr(0, usepos);    // get the first argument
		std::string second = TSAP.substr(usepos + 1, 2); // get the second argument

		// convert both TSAP arguments from hex (16) in string format to a number in decimal
		char* p; // used in the strtol function

		uint8_t number1 = strtol(first.c_str(), &p, 16); // convert string with data in any base (10, 16) to long
		uint8_t number2 = strtol(second.c_str(), &p, 16); // convert string with data in any base (10, 16) to long

		uint16_t res = number1 << 8 | number2;

		return res;
	}

}

//****************************************************************************
// Get Text message of Area Source
std::string S7::GetTxtAreaSource(int areaSource) {
	switch (areaSource) {
	case  AREA_SOURCE_I: // Inputs
		return "INPUTS";
		break;

	case  AREA_SOURCE_Q: // Outputs
		return "OUTPUTS";
		break;

	case  AREA_SOURCE_M: // Memory Marks
		return "Marks";
		break;

	case  AREA_SOURCE_DB: // Data Block
		return "DB";
		break;

	default:
		return "Unkown Data Source";
	};
}

//****************************************************************************

// Get BDC and convert to byte
int S7::BDCToByte(byte B) {
	return ((B >> 4) * 10) + (B & 0x0F);
}

//****************************************************************************

// Convert Byte to BDC
byte S7::ByteToBDC(int Value) {
	return (byte) (((Value / 10) << 4) | (Value % 10));
}

//****************************************************************************

// Get Bit position at buffer of bytes, bits 0..7
bool S7::GetBitAt(byte Buffer[], int Pos, int Bit) {
	if (Bit < 0)
		Bit = 0;
	if (Bit > 7)
		Bit = 7;

	return (Buffer[Pos] & Mask[Bit]) != 0;
}

//****************************************************************************

// Set Bit position at buffer of bytes

void  S7::SetBitAt(byte Buffer[], int Pos, int Bit, bool Value) {
	if (Bit < 0)
		Bit = 0;
	if (Bit > 7)
		Bit = 7;

	if (Value)
		Buffer[Pos] = (byte) (Buffer[Pos] | Mask[Bit]);
	else
		Buffer[Pos] = (byte) (Buffer[Pos] & ~Mask[Bit]);
}

//****************************************************************************

// Get Byte (0..255) at buffer of bytes
uint8_t S7::GetByteAt(byte Buffer[], int Pos) {
	return Buffer[Pos];
}

//****************************************************************************

// Set Byte (0..255) at buffer of bytes
void  S7::SetByteAt(byte Buffer[], int Pos, uint8_t Value) {
	Buffer[Pos] = Value;
}

//****************************************************************************

// Get SInt (-128..127) at buffer of bytes
int8_t  S7::GetSIntAt(byte Buffer[], int Pos) {
	int Value = Buffer[Pos];
	if (Value < 128)
		return Value;
	else
		return (int8_t) (Value - 256);
}

//****************************************************************************

// Set SInt (-128..127) at buffer of bytes
void  S7::SetSIntAt(byte Buffer[], int Pos, int8_t Value) {
	//if (Value < -128)
	//	Value = -128;
	//if (Value > 127)
	//	Value = 127;
	Buffer[Pos] = (byte) Value;
}

//****************************************************************************

// Get 16 bit unsigned value (S7 UInt) 0..65535
uint16_t  S7::GetUIntAt(byte Buffer[], int Pos) {
	return (uint16_t) ((Buffer[Pos] << 8) | Buffer[Pos + 1]);
}

//****************************************************************************

// Set 16 bit unsigned value (S7 UInt) 0..65535

void  S7::SetUIntAt(byte Buffer[], int Pos, uint16_t Value) {
	Buffer[Pos] = (byte) (Value >> 8);
	Buffer[Pos + 1] = (byte) (Value & 0x00FF);
}

//****************************************************************************

// Get 16 bit unsigned value (S7 Word) 0..65535

uint16_t  S7::GetWordAt(byte Buffer[], int Pos) {
	return  S7::GetUIntAt(Buffer, Pos);
}

//****************************************************************************
// Set 16 bit unsigned value (S7 Word) 0..65535
void  S7::SetWordAt(byte Buffer[], int Pos, uint16_t Value) {
	S7::SetUIntAt(Buffer, Pos, Value);
}

//****************************************************************************

// Get 16 bit signed value (S7 int) -32768..32767 at buffer of bytes
int16_t  S7::GetIntAt(byte Buffer[], int Pos) {
	return (int16_t) ((Buffer[Pos] << 8) | Buffer[Pos + 1]);
}

//****************************************************************************

// Set 16 bit signed value (S7 int) -32768..32767 at buffer of bytes

void  S7::SetIntAt(byte Buffer[], int Pos, int16_t Value) {
	Buffer[Pos] = (byte) (Value >> 8);
	Buffer[Pos + 1] = (byte) (Value & 0x00FF);
}

//****************************************************************************

// Get 32 bit signed value (S7 DInt) -2147483648..2147483647
long  S7::GetDIntAt(byte Buffer[], int Pos) {
	long Result;
	Result = Buffer[Pos];
	Result <<= 8;
	Result += Buffer[Pos + 1];
	Result <<= 8;
	Result += Buffer[Pos + 2];
	Result <<= 8;
	Result += Buffer[Pos + 3];
	return Result;
}

//****************************************************************************

// Set 32 bit signed value (S7 DInt) -2147483648..2147483647

void  S7::SetDIntAt(byte Buffer[], int Pos, long Value) {
	Buffer[Pos + 3] = (byte) (Value & 0xFF);
	Buffer[Pos + 2] = (byte) ((Value >> 8) & 0xFF);
	Buffer[Pos + 1] = (byte) ((Value >> 16) & 0xFF);
	Buffer[Pos] = (byte) ((Value >> 24) & 0xFF);
}

//****************************************************************************

//  Get 32 bit unsigned value (S7 UDInt) 0..4294967295
uint32_t  S7::GetUDIntAt(byte Buffer[], int Pos) {
	uint32_t Result;
	Result = Buffer[Pos];
	Result <<= 8;
	Result |= Buffer[Pos + 1];
	Result <<= 8;
	Result |= Buffer[Pos + 2];
	Result <<= 8;
	Result |= Buffer[Pos + 3];
	return Result;
}

//****************************************************************************

//  Set 32 bit unsigned value (S7 UDInt) 0..4294967295

void  S7::SetUDIntAt(byte Buffer[], int Pos, uint32_t Value) {
	Buffer[Pos + 3] = (byte) (Value & 0xFF);
	Buffer[Pos + 2] = (byte) ((Value >> 8) & 0xFF);
	Buffer[Pos + 1] = (byte) ((Value >> 16) & 0xFF);
	Buffer[Pos] = (byte) ((Value >> 24) & 0xFF);
}

//****************************************************************************

//  Get 32 bit unsigned value (S7 UDInt) 0..4294967295
uint32_t  S7::GetDWordAt(byte Buffer[], int Pos) {
	return  S7::GetUDIntAt(Buffer, Pos);
}

//****************************************************************************

//  Set 32 bit unsigned value (S7 UDInt) 0..4294967295

void  S7::SetDWordAt(byte Buffer[], int Pos, uint32_t Value) {
	S7::SetUDIntAt(Buffer, Pos, Value);
}

//****************************************************************************

// Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615
uint64_t  S7::GetULIntAt(byte Buffer[], int Pos) {
	uint64_t Result;
	Result = Buffer[Pos];
	Result <<= 8;
	Result |= Buffer[Pos + 1];
	Result <<= 8;
	Result |= Buffer[Pos + 2];
	Result <<= 8;
	Result |= Buffer[Pos + 3];
	Result <<= 8;
	Result |= Buffer[Pos + 4];
	Result <<= 8;
	Result |= Buffer[Pos + 5];
	Result <<= 8;
	Result |= Buffer[Pos + 6];
	Result <<= 8;
	Result |= Buffer[Pos + 7];
	return Result;
}

//****************************************************************************

// Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615
void  S7::SetULIntAt(byte Buffer[], int Pos, uint64_t Value) {
	Buffer[Pos + 7] = (byte) (Value & 0xFF);
	Buffer[Pos + 6] = (byte) ((Value >> 8) & 0xFF);
	Buffer[Pos + 5] = (byte) ((Value >> 16) & 0xFF);
	Buffer[Pos + 4] = (byte) ((Value >> 24) & 0xFF);
	Buffer[Pos + 3] = (byte) ((Value >> 32) & 0xFF);
	Buffer[Pos + 2] = (byte) ((Value >> 40) & 0xFF);
	Buffer[Pos + 1] = (byte) ((Value >> 48) & 0xFF);
	Buffer[Pos] = (byte) ((Value >> 56) & 0xFF);
}

//****************************************************************************
// Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

uint64_t  S7::GetLWordAt(byte Buffer[], int Pos) {
	return  S7::GetULIntAt(Buffer, Pos);
}

//****************************************************************************
// Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

void  S7::SetLWordAt(byte Buffer[], int Pos, uint64_t Value) {
	S7::SetULIntAt(Buffer, Pos, Value);
}

//****************************************************************************

// Get 64 bit signed value (S7 LInt) -9223372036854775808..9223372036854775807
int64_t  S7::GetLIntAt(byte Buffer[], int Pos) {
	int64_t Result;
	Result = Buffer[Pos];
	Result <<= 8;
	Result += Buffer[Pos + 1];
	Result <<= 8;
	Result += Buffer[Pos + 2];
	Result <<= 8;
	Result += Buffer[Pos + 3];
	Result <<= 8;
	Result += Buffer[Pos + 4];
	Result <<= 8;
	Result += Buffer[Pos + 5];
	Result <<= 8;
	Result += Buffer[Pos + 6];
	Result <<= 8;
	Result += Buffer[Pos + 7];
	return Result;
}

//****************************************************************************

// Set 64 bit signed value (S7 LInt) -9223372036854775808..9223372036854775807
void  S7::SetLIntAt(byte Buffer[], int Pos, int64_t Value) {
	Buffer[Pos + 7] = (byte) (Value & 0xFF);
	Buffer[Pos + 6] = (byte) ((Value >> 8) & 0xFF);
	Buffer[Pos + 5] = (byte) ((Value >> 16) & 0xFF);
	Buffer[Pos + 4] = (byte) ((Value >> 24) & 0xFF);
	Buffer[Pos + 3] = (byte) ((Value >> 32) & 0xFF);
	Buffer[Pos + 2] = (byte) ((Value >> 40) & 0xFF);
	Buffer[Pos + 1] = (byte) ((Value >> 48) & 0xFF);
	Buffer[Pos] = (byte) ((Value >> 56) & 0xFF);
}

//****************************************************************************
// Get 32 bit floating point number (S7 Real) (Range of float)
float  S7::GetRealAt(byte Buffer[], int Pos) {
	uint32_t Pack =  GetUDIntAt(Buffer, Pos);
	float Res;
	memcpy(&Res, &Pack, 4);
	return Res;
}

//****************************************************************************

// Set 32 bit floating point number (S7 Real) (Range of float)
void  S7::SetRealAt(byte Buffer[], int Pos, float Value) {

	uint32_t Pack;
	memcpy(&Pack, &Value, 4);
	S7::SetUDIntAt(Buffer, Pos, Pack);
}

//****************************************************************************

// Get 64 bit floating point number (S7 LReal) (Range of double)
double  S7::GetLRealAt(byte Buffer[], int Pos) {
	uint64_t Pack =  GetULIntAt(Buffer, Pos);
	double Res;
	memcpy(&Res, &Pack, 8);
	return Res;
}

//****************************************************************************

// Set 64 bit floating point number (S7 LReal) (Range of double)
void  S7::SetLRealAt(byte Buffer[], int Pos, double Value) {
	uint64_t Pack;
	memcpy(&Pack, &Value, 8);
	S7::SetULIntAt(Buffer, Pos, Pack);
}

//****************************************************************************
// Get String (S7 String)
// In Siemens the standard string has format:
//  - 1st byte: Max Length
//  - 2nd byte: Current Length
//  - 3rd ... n byte: string characters

std::string  S7::GetStringAt(byte Buffer[], int Pos) {
	std::string res;

	int size = (int) Buffer[Pos + 1];

	res.insert(0, (char*) &Buffer[Pos + 2], size);

	return res;
}

//****************************************************************************
// Set String (S7 String)
// In Siemens the standard string has format:
//  - 1st byte: Max Length
//  - 2nd byte: Current Length
//  - 3rd ... n byte: string characters

void  S7::SetStringAt(byte Buffer[], int Pos, int MaxLen, std::string Value) {
	int size = Value.size();

	Buffer[Pos] = (byte) MaxLen;
	Buffer[Pos + 1] = (byte) size;

	Value.copy((char*) &Buffer[Pos + 2], size);
}

//****************************************************************************
//Get Array of char (S7 ARRAY OF CHARS)
std::string  S7::GetCharsAt(byte Buffer[], int Pos, int Size) {
	std::string res;

	res.insert(0, (char*) &Buffer[Pos], Size);

	return res;
}

#include <iostream>

//****************************************************************************
//Set Array of char (S7 ARRAY OF CHARS)
void  S7::SetCharsAt(byte Buffer[], int BufferLen, int Pos, std::string Value) {
	int MaxLen = BufferLen - Pos;
	int Size = Value.size();

	std::cout << " Max Len: " << MaxLen << " Size: " << Size << std::endl;

	// Truncs the string if there's no room enough
	if (Size > MaxLen)
		Size = MaxLen;

	Value.copy((char*) &Buffer[Pos], Size);
}

//****************************************************************************
