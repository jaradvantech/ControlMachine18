#ifndef S7_H
#define S7_H

#include <connexion/connexionPLC.h>

namespace S7{
// Define different PLC Types
#define PLC_300_400    0 // for PLC S7 300/400
#define PLC_1200_1500  1 // for PLC S7 1200/1500
#define PLC_LOGO_200   2 // for PLC S7 LOGO / 200
#define PLC_SINAMICS   3 // for SINAMICS Driver

// Define different Area sources
#define AREA_SOURCE_I  0    // Inputs
#define AREA_SOURCE_Q  1    // Outputs
#define AREA_SOURCE_M  2    // Memory Marks
#define AREA_SOURCE_DB 3    // Data Blocks

// Define different S7 data types
#define TYPE_BOOL    1
#define TYPE_BYTE    2
#define TYPE_SINT    3
#define TYPE_WORD    4
#define TYPE_UINT    5
#define TYPE_INT     6
#define TYPE_DWORD   7
#define TYPE_UDINT   8
#define TYPE_DINT    9
#define TYPE_LWORD   10
#define TYPE_ULINT   11
#define TYPE_LINT    12
#define TYPE_REAL    13
#define TYPE_LREAL   14

#define TYPE_STRING  15
#define TYPE_ARRAYCHAR 16

std::string GetTxtPLCType(short int plcType); // Get Text description of PLC Type

int GetDataTypeSize(int type); // Get data type size

uint16_t GetWordFromTSAP(std::string TSAP); // Get the word from Transport Service Access Point (TSAP) in hex format, e.g: 10.02 => 0x1002, used by Cli_SetConnectionParams

std::string GetTxtAreaSource(int areaSource); // Get Text message of Area Source

int BDCToByte(byte B); // Get BDC and convert to byte

byte ByteToBDC(int Value); // Convert Byte to BDC

bool GetBitAt(byte Buffer[], int Pos, int Bit); // Get Bit position at buffer of bytes

void SetBitAt(byte Buffer[], int Pos, int Bit, bool Value); // Set Bit position at buffer of bytes

uint8_t GetByteAt(byte Buffer[], int Pos); // Get Byte (0..255) at buffer of bytes

void SetByteAt(byte Buffer[], int Pos, uint8_t Value); // Set Byte (0..255) at buffer of bytes

int8_t GetSIntAt(byte Buffer[], int Pos); // Get SInt (-128..127) at buffer of bytes

void SetSIntAt(byte Buffer[], int Pos, int8_t Value); // Set SInt (-128..127) at buffer of bytes

uint16_t GetUIntAt(byte Buffer[], int Pos); // Get 16 bit unsigned value (S7 UInt) 0..65535

void SetUIntAt(byte Buffer[], int Pos, uint16_t Value); // Set 16 bit unsigned value (S7 UInt) 0..65535

uint16_t GetWordAt(byte Buffer[], int Pos); // Get 16 bit unsigned value (S7 UInt) 0..65535

void SetWordAt(byte Buffer[], int Pos, uint16_t Value); // Set 16 bit unsigned value (S7 UInt) 0..65535

int16_t GetIntAt(byte Buffer[], int Pos); // Get 16 bit signed value (S7 int) -32768..32767 at buffer of bytes

void SetIntAt(byte Buffer[], int Pos, int16_t Value); // Set 16 bit signed value (S7 int) -32768..32767 at buffer of bytes

uint32_t GetUDIntAt(byte Buffer[], int Pos); //  Get 32 bit unsigned value (S7 UDInt) 0..4294967295

void SetUDIntAt(byte Buffer[], int Pos, uint32_t Value); //  Set 32 bit unsigned value (S7 UDInt) 0..4294967295

uint32_t GetDWordAt(byte Buffer[], int Pos); //  Get 32 bit unsigned value (S7 UDInt) 0..4294967295

void SetDWordAt(byte Buffer[], int Pos, uint32_t Value); //  Set 32 bit unsigned value (S7 UDInt) 0..4294967295

long GetDIntAt(byte Buffer[], int Pos); // Get 32 bit signed value (S7 DInt) -2147483648..2147483647

void SetDIntAt(byte Buffer[], int Pos, long Value); // Set 32 bit signed value (S7 DInt) -2147483648..2147483647

uint64_t GetULIntAt(byte Buffer[], int Pos); // Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

void SetULIntAt(byte Buffer[], int Pos, uint64_t Value); // Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

uint64_t GetLWordAt(byte Buffer[], int Pos); // Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

void SetLWordAt(byte Buffer[], int Pos, uint64_t Value); // Set 64 bit unsigned value (S7 ULint) 0..18446744073709551615

int64_t GetLIntAt(byte Buffer[], int Pos); // Get 64 bit signed value (S7 LInt) -9223372036854775808..9223372036854775807

void SetLIntAt(byte Buffer[], int Pos, int64_t Value); // Set 64 bit signed value (S7 LInt) -9223372036854775808..9223372036854775807

float GetRealAt(byte Buffer[], int Pos); // Get 32 bit floating point number (S7 Real) (Range of float)

void SetRealAt(byte Buffer[], int Pos, float Value); // Set 32 bit floating point number (S7 Real) (Range of float)

double GetLRealAt(byte Buffer[], int Pos); // Get 64 bit floating point number (S7 LReal) (Range of double)

void SetLRealAt(byte Buffer[], int Pos, double Value); // Set 64 bit floating point number (S7 LReal) (Range of double)

std::string GetStringAt(byte Buffer[], int Pos); // Get String (S7 String)

void SetStringAt(byte Buffer[], int Pos, int MaxLen, std::string Value); // Set String (S7 String)

std::string GetCharsAt(byte Buffer[], int Pos, int Size); //Get Array of char (S7 ARRAY OF CHARS)

void SetCharsAt(byte Buffer[], int BufferLen, int Pos, std::string Value); //Set Array of char (S7 ARRAY OF CHARS)
}
#endif // S7_H
