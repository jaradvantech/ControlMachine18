//============================================================================
// Name        : ControlMachine18.cpp
// Author      : Jose Andres Grau
// Version     :
// Copyright   : JARADVANTECH
// Description :
//============================================================================

#include <connexion/connexionCucoParser.h>
#include <iostream>

#include <pthread.h>
#include <pstream.h>
#include <SynchronizationPoints.h>
#include <connexion/TCPClientLibrary.h>
pthread_t PLCThread;
pthread_t DisplayServerThread;
pthread_t AlgorithmThread;

void init()
{
	//--------------------------------------------------------------------
	// OPEN CUCO COMMUNICATIONS
	//--------------------------------------------------------------------
	//Synchro::IncreaseSynchronizationPointValue(0);
	//InitDisplayParser();
	//pthread_create(&DisplayServerThread, NULL, OpenServer, (void *) 0); //23623
	//while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//--------------------------------------------------------------------
	// CONFIGURE DATABASE CONNEXION
	//--------------------------------------------------------------------
	//Synchro::IncreaseSynchronizationPointValue(0);
	//pthread_create(&DataBaseThread, NULL, ConnectToDataBase, (void *) 0);
	//while (Synchro::GetSynchronizationPointValue(0) != 0)	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


int main()
{
	std::cout << "Remote assistance demon started"<< std::endl; // prints !!!Hello World!!!

	init();

	while(1){



	}

	return 0;
}
