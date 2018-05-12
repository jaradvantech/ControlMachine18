/*
 * Algorithm.cpp
 *
 *  Created on: May 10, 2018
 *      Author: andres
 */

#include "Algorithm.h"
#include <SynchronizationPoints.h>

/*						DATA STRUCTURES USED						*/

//So, we can have a class "PalletPlace"
//Every PalletPlace will have private pointers to the required PLC Interface variables, all the exchange will be done via getters and setters.
//Every PalletPlace will have a private deque of vectors with the coordinates to palletize. Getters and setters also for this.
//Every PalletPlace will keep track of the actual step where he is.

//So we have an arbitrary amount of PalletPlace, arranged in a vector.

//In the constructor we could make the mapping between the private pointers to the PLC Interface Variables.
//The c++ program won't provide with a default vector of coordinates to palletize.

/*						FUNCTIONS USED						*/

//Function that checks for a new configuration for a pallet.
//A PalletPlace has 2 vectors of coordinates to palletize. The one that is using at the moment and CANNOT be modified if exists. index 0.
//The one that will use for the next pallet. This one can be changed at any time.


/*						ALGORITHM IMPLEMENTATION						*/


//The first approach is going to be the use of nested binaries Petri's Networks implementation.
//
//The reason for choosing this approach is that is easily implementable in the PLC side,
//and I firmly believe that all the palletizer program can be done inside the PLC
//so, in a future we might remove all the logic from this program.
//In case that we don't do it, at least, it should be easy to maintain.
//
//The working diagram can be found in the src folder as a png or collection of png files. And it is needed to understand the code.
//The code, by itself IS NOT SELF EXPLAINATORY as it uses the general notation of Places, transitions and marks.
//
//The Petri's Network states will be defined using ol' school bools.
//Which sadly will take a byte of memory under the hood anyways. Hope that the compiler optimizes this out.



//
//
// The implementation will be as follow:
//
// 1: Check for a new pallet configuration.
// 2: Evaluate Petri's Network of what should the Palletizer do.
//
//
//
//
//

//TODO: It will be cool if we could set different areas in a pallet that can be palletized independently to allow us in the future to mix boxes.
//Cool but I don't see this as consistently useful.


bool P0=true;
bool P1=false;
bool P2=false;
bool P3=false;
bool P4=false;
bool P5=false;
bool P6=false;
bool P7=false;
bool P8=false;

bool T0_1=false;
bool T1_2=false;
bool T2_3=false;
bool T2_4=false;
bool T3_2=false;
bool T3_5=false;
bool T3_6=false;
bool T4_6=false;
bool T4_7=false;
bool T4_8=false;
bool T5_2=false;
bool T7_8=false;
bool T8_1=false;



void* AlgorithmLoop(void *Arg)
{
	Synchro::DecreaseSynchronizationPointValue(0);
	while(1)
	{
		P1=(P1 && !P0 && !P8) || (P0 && T0_1) || (P8 && T8_1);
		P2=(P2 && !P1 && !P3 && !P5) || (P1 && T1_2) || (P3 && T3_2) || (P5 && T5_2);


		P3=(P3 && !P2) || (P2 && T_2);
		P4=(P4 && !P2) || (P2 && T1_2);











		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return nullptr;
}
