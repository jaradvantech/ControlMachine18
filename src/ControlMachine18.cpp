//============================================================================
// Name        : ControlMachine18.cpp
// Author      : Jose Andres Grau
// Version     :
// Copyright   : JARADVANTECH
// Description :
//============================================================================

#include <iostream>

#include <pthread.h>

#include <SynchronizationPoints.h>
#include <PLCInterface.h>
#include <connexion/TCPServerLibrary.h>
#include "connexion/connexionDisplayParser.h"
#include <Algorithm.h>
#include <Palletizer.h>
pthread_t PLCThread;
pthread_t DisplayServerThread;
pthread_t AlgorithmThread;

void init()
{
	//--------------------------------------------------------------------
	// CONFIGURE PALLETIZER MEMORY
	//--------------------------------------------------------------------
	PalletizerConfigInfo palletizerConfigInfo;

	palletizerConfigInfo.IODBReading=5;
	palletizerConfigInfo.ReadingStartByte=0;
	palletizerConfigInfo.ReadingLength=220;

	palletizerConfigInfo.IODBWriting=2;
	palletizerConfigInfo.WritingStartByte=0;
	palletizerConfigInfo.WritingLength=196;

	GetPalletizer()->SetPalletizerConfig(palletizerConfigInfo);
	//--------------------------------------------------------------------
	// CONFIGURE PLCs
	//--------------------------------------------------------------------
	Synchro::IncreaseSynchronizationPointValue(0);
	StartUpPLC();
	pthread_create(&PLCThread, NULL, PLCAdquisitionLoop, (void *) 0);
	while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//--------------------------------------------------------------------
	// OPEN DISPLAY COMMUNICATIONS
	//--------------------------------------------------------------------
	Synchro::IncreaseSynchronizationPointValue(0);
	InitDisplayParser();
	pthread_create(&DisplayServerThread, NULL, OpenServer, (void *) 0); //23623
	while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//--------------------------------------------------------------------
	// CONFIGURE DATABASE CONNEXION
	//--------------------------------------------------------------------
	//Synchro::IncreaseSynchronizationPointValue(0);
	//pthread_create(&DataBaseThread, NULL, ConnectToDataBase, (void *) 0);
	//while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//--------------------------------------------------------------------
	// CONFIGURE Algorithm
	//--------------------------------------------------------------------
	//Synchro::IncreaseSynchronizationPointValue(0);
	pthread_create(&AlgorithmThread, NULL, AlgorithmLoop, (void *) 0);
	while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//Wait until the algorithm has entered in its loop
}


int main()
{
	std::cout << "!!!Hello World!!!"<< std::endl; // prints !!!Hello World!!!

	init();

	while(1){


		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
