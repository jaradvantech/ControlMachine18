/*
 * PLCInterface.cpp
 *
 *  Created on: Mar 30, 2018
 *      Author: andres
 */




#include "PLCInterface.h"
#include "SynchronizationPoints.h"
#include "Palletizer.h"
#include <iostream>

struct StructInfoPlc {
	const char * PlcAddress;
	int  PlcRack;
	int  PlcSlot;
};


TS7Client PLC18;
StructInfoPlc InfoPlc18;

void SetConfigPLC(StructInfoPlc _InfoPlc)
{
	InfoPlc18=_InfoPlc;
}
void SetConfigPLC(std::string _PlcAddress, int _PlcRack, int _PlcSlot)
{
	InfoPlc18.PlcAddress = _PlcAddress.c_str();
	InfoPlc18.PlcRack = _PlcRack;
	InfoPlc18.PlcSlot = _PlcSlot;
}

bool Check(TS7Client *Client, int Result, const char * function){
    printf("\n");
    printf("+-----------------------------------------------------\n");
    printf("| %s\n",function);
    printf("+-----------------------------------------------------\n");
    if (Result==0) {
        printf("| Result         : OK\n");
        printf("| Execution time : %d ms\n",Client->ExecTime());
        printf("+-----------------------------------------------------\n");
    } else {
        printf("| ERROR !!! \n");
        if (Result<0)
            printf("| Library Error (-1)\n");
        else
            printf("| %s\n",CliErrorText(Result).c_str());
        printf("+-----------------------------------------------------\n");
    }
    return Result==0;
}

bool CliConnectPLC(TS7Client *Client){

    int res = Client->ConnectTo(InfoPlc18.PlcAddress,InfoPlc18.PlcRack,InfoPlc18.PlcSlot);
    if (Check(Client, res, "UNIT Connection")) {
          printf("  Connected to   : %s (Rack=%d, Slot=%d)\n",InfoPlc18.PlcAddress,InfoPlc18.PlcRack,InfoPlc18.PlcSlot);
          printf("  PDU Requested  : %d bytes\n",Client->PDURequested());
          printf("  PDU Negotiated : %d bytes\n",Client->PDULength());
    }
    return res==0;
}

bool CliConnectPLC(TS7Client *Client, StructInfoPlc Config){

    int res = Client->ConnectTo(Config.PlcAddress,Config.PlcRack,Config.PlcSlot);
    if (Check(Client, res, "UNIT Connection")) {
          printf("  Connected to   : %s (Rack=%d, Slot=%d)\n",Config.PlcAddress,Config.PlcRack,Config.PlcSlot);
          printf("  PDU Requested  : %d bytes\n",Client->PDURequested());
          printf("  PDU Negotiated : %d bytes\n",Client->PDULength());
    }
    return res==0;
}

bool StartUpPLC()
{
	SetConfigPLC("192.168.0.199",0,1);
	return CliConnectPLC(&PLC18);
}

void CliDisconnectPLC(TS7Client *Client){
     Client->Disconnect();
}

//RBS
void AttemptReconnection(void)
{
	std::cout << "Could not connect to PLC, trying to reconnect..." << std::endl;
	CliDisconnectPLC(&PLC18);

	//Wait for a couple of seconds before reconnecting
	sleep(2);

	CliConnectPLC(&PLC18, InfoPlc18);
}


//Have a Pointer to the function PerformGlobalReading
//Have a Pointer to the function PerformGlobalWriting

//Have a Seter for the Pointer to the function PerformGlobalReading
//Have a Seter for the Pointer to the function PerformGlobalWriting

void * PLCAdquisitionLoop(void *Arg){
	Synchro::DecreaseSynchronizationPointValue(0);

	//RBS
	while(1){
		int ReadResult, WriteResult;
		//std::chrono::_V2::high_resolution_clock::time_point t1 = std::chrono::_V2::high_resolution_clock::now();
		//Check(ClientPlc14,PerformGlobalReading(),"GLOBAL READING");
		ReadResult = PerformGlobalReading();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		//Check(ClientPlc14,,"GLOBAL Writing");
		WriteResult = PerformGlobalWriting();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		//std::chrono::_V2::high_resolution_clock::time_point t2 = std::chrono::_V2::high_resolution_clock::now();

		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		//cout << "Duration is: " << duration;

		if((ReadResult != 0) || (WriteResult != 0))
			AttemptReconnection();
	}
	return nullptr;
}

TS7Client* GetPLC18()
{
	return &PLC18;
}



