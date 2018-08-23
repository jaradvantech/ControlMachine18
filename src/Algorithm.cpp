/*
 * Algorithm.cpp
 *
 *  Created on: May 10, 2018
 *      Author: andres
 */

#include "Algorithm.h"
#include <algorithm>
#include <SynchronizationPoints.h>
#include <Palletizer.h>
#include <deque>
#include <iostream>
/*						DATA STRUCTURES USED						*/

//The c++ program won't provide with a default vector of coordinates to palletize.

/*						FUNCTIONS USED						*/

//Function that checks for a new configuration for a pallet.
//A PalletPlace has 2 vectors of coordinates to palletize. The one that is using at the moment and CANNOT be modified if exists. index 0.
//The one that will use for the next pallet. This one can be changed at any time.


/*						ALGORITHM IMPLEMENTATION						*/

//TODO: It will be cool if we could set different areas in a pallet that can be palletized independently to allow us in the future to mix boxes.
//Cool but I don't see this as consistently useful.
struct MovementVector{
	int x=0;
	int y=0;
	int z=0;
	int w=0;
	MovementVector(){}
	MovementVector(int _x, int _y, int _z, int _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	friend MovementVector operator+ (MovementVector lhs, const MovementVector & rhs)
	{
		lhs.x+=rhs.x;
		lhs.y+=rhs.y;
		lhs.z+=rhs.z;
		lhs.w+=rhs.w;
		return lhs;
	}
	void operator() (int _x, int _y, int _z, int _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

class JAGMbool{
	public:
	bool value;
	bool previousValue;
	JAGMbool(){
		value=false;
		previousValue=false;
	}
	JAGMbool(const bool& _value){
		value=_value;
		previousValue=_value;
	}
	JAGMbool& operator =(const bool& right){
		previousValue=value;
		value = right;
		return *this;
	}

	operator bool() {
		return value;
	}
	bool operator !(){
		return !value;
	}
	bool TriggerUP(){
		return ((previousValue == false) && (value == true));
	}
	bool TriggerDOWN(){
		return ((previousValue == true) && (value == false));
	}
	bool Trigger(){
		return (previousValue != value);
	}
};

class ManipulatorGeneral{
	public:
	//The manipulator needs the coordinates in absolute encoder units.
	MovementVector Origin;

	//For the sake of simplicity we are going to use always relative encoder units
	MovementVector Working_Position;

	MovementVector PalletStack_PositionUP;
	MovementVector PalletStack_PositionDOWN;

	struct PalletPosition
	{
		MovementVector PositionUP;
		MovementVector PositionDOWN;
	};
	PalletPosition PalletA;
	PalletPosition PalletB;

	MovementVector GrabBoxes_PositionUP;
	MovementVector GrabBoxes_PositionDOWN;
};

class PalletPlace{
	struct MovementVectorContainer
	{
		MovementVector LandingPosition;
		MovementVector DisplacedPosition;
		int NumberOfBoxes;
	};
	typedef std::vector<MovementVectorContainer> Receipe; //The first elem
	typedef std::deque<Receipe> Orders;
	private:
	Orders ListOfPalletsTodo;
	unsigned int actualPosition=0;
	bool PalletReady=0; //This means that the pallet is ready to pack.
	bool AutomaticMode=0; //This means that the pallet will repeat the last topology endlessly
	public:

	void SetConfigurationForNextPallet(Receipe receipe){
		if(ListOfPalletsTodo.size()==0){
			PalletReady=1;
			ListOfPalletsTodo.push_back(receipe);
		}
		else if(ListOfPalletsTodo.size()==1){
			ListOfPalletsTodo.push_back(receipe);
		}
		else if(ListOfPalletsTodo.size()>1){
			ListOfPalletsTodo.pop_back();
			ListOfPalletsTodo.push_back(receipe);
		}
	}

	MovementVectorContainer GetNextBoxPosition(){
		MovementVectorContainer nextBox = ListOfPalletsTodo.at(0).at(actualPosition);
		actualPosition++;
		if(actualPosition==ListOfPalletsTodo.at(0).size()){
			PalletFinished();
		}
		return nextBox;
	}
	MovementVectorContainer GetActualBoxPosition(){
		return ListOfPalletsTodo.at(0).at(actualPosition);
	}

	void PalletFinished(){
		if(ListOfPalletsTodo.size()>0){
			if(AutomaticMode ==true) ListOfPalletsTodo.push_back(ListOfPalletsTodo.at(ListOfPalletsTodo.size()-1));
			ListOfPalletsTodo.pop_front();
			actualPosition=0;
		}
	}

	bool isPalletReady() const
	{
		return PalletReady;
	}

};

static Palletizer* palletizer = GetPalletizer();

ManipulatorGeneral manipulator;
PalletPlace palletA;
PalletPlace palletB;

MovementVector PerformMovement(MovementVector _movement)
{
	palletizer->XAxisSetting=_movement.x + manipulator.Origin.x;
	palletizer->YAxisSetting=_movement.y + manipulator.Origin.y;
	palletizer->ZAxisSetting=_movement.z + manipulator.Origin.z;
	palletizer->WAxisSetting=_movement.w + manipulator.Origin.w;
	return _movement;
}

const int OPEN = 1;
const int HALF = 2;
const int CLOSE = 3;
const int CLOSED = 3;

void Fingers(int state){palletizer->FingerMovement = state;}
void Claws(int state){palletizer->OuterClawMovement = state;}

//checks wether if the manipulator arrived to a RELATIVE destination
bool ManipulatorArrived(MovementVector Destination)
{
	//This function checks if the actual position matches the position that was set for the manipulator, within a certain range.
	float MarginUP=50;
	float MarginDOWN=50;
	if(Destination.x>palletizer->RealTimeValueOfxAxis - manipulator.Origin.x + MarginUP ||
	   Destination.x<palletizer->RealTimeValueOfxAxis - manipulator.Origin.x + -MarginDOWN) return false;
	if(Destination.y>palletizer->RealTimeValueOfyAxis - manipulator.Origin.y + +MarginUP ||
	   Destination.y<palletizer->RealTimeValueOfyAxis - manipulator.Origin.y + -MarginDOWN) return false;
	if(Destination.z>palletizer->RealTimeValueOfzAxis - manipulator.Origin.z + +MarginUP ||
	   Destination.z<palletizer->RealTimeValueOfzAxis - manipulator.Origin.z + -MarginDOWN) return false;
	if(Destination.w>palletizer->RealTimeValueOfwAxis - manipulator.Origin.w + +MarginUP ||
	   Destination.w<palletizer->RealTimeValueOfwAxis - manipulator.Origin.w + -MarginDOWN) return false;
	return true;
}

void CheckCalibration(bool *calibrated)
{
	if(palletizer->ZeroPositionProximitySwitchDetectionOfxAxis == true &&
	   palletizer->ZeroPositionProximitySwitchDetectionOfyAxis == true &&
	   palletizer->ZeroPositionProximitySwitchDetectionOfzAxis == true &&
	   palletizer->ZeroPositionProximitySwitchDetectionOfwAxis == true)
	{
		static std::deque<int> calibration_points;

		calibration_points.push_back(palletizer->RealTimeValueOfxAxis);
		if(calibration_points.size()>10)calibration_points.pop_front();
		if((unsigned)std::count(calibration_points.begin(), calibration_points.end(),palletizer->RealTimeValueOfxAxis) == calibration_points.size() )
		{
			static int previous_calibrated_point;
			previous_calibrated_point = manipulator.Origin.x;
			manipulator.Origin.x = palletizer->RealTimeValueOfxAxis;
			manipulator.Origin.y = palletizer->RealTimeValueOfyAxis;
			manipulator.Origin.z = palletizer->RealTimeValueOfzAxis;
			manipulator.Origin.w = palletizer->RealTimeValueOfwAxis;
			if(*calibrated==false)*calibrated=true;
			if(previous_calibrated_point != manipulator.Origin.x) std::cout <<"   Calibrated previous:" << previous_calibrated_point << "   new:" << manipulator.Origin.x << std::endl;

		}
	}

}
//bool CheckForOrders();
void loadKeyPoints()
{
	manipulator.Working_Position(7777,11815,1606,0);
	manipulator.PalletStack_PositionUP(10166,11338,8737,0);
	manipulator.PalletStack_PositionDOWN(10166,11338,11833,0);


	manipulator.PalletA.PositionUP(10166,19109,7209,0);
	manipulator.PalletA.PositionDOWN(10166,19109,14419,0);
}
//Pallet Destination 1=A    2=B
const int PalletPlaceA = 1;
const int PalletPlaceB = 2;
void GrabPallet(JAGMbool* GrabPalletLatch, int PalletDestination)
{
	*GrabPalletLatch = true;
	static int InternalState = 0;

	MovementVector Target;
	ManipulatorGeneral::PalletPosition Destination;

	if		(PalletDestination == PalletPlaceA) Destination = manipulator.PalletA;
	else if (PalletDestination == PalletPlaceB) Destination = manipulator.PalletB;

	//Go to Working Position
	if(InternalState == 0)
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(manipulator.Working_Position);
		Fingers(OPEN);
		InternalState++;
	}
	//Close the fingers
	else if(InternalState == 1 && ManipulatorArrived(manipulator.Working_Position))
	{
		std::cout << "state: " << InternalState << std::endl;
		Fingers(CLOSE);
		InternalState++;
	}

	//Open Claws
	else if(InternalState == 2 && palletizer->InnerFingerState == 1 && palletizer->FingerState == 2)
	{
		std::cout << "state: " << InternalState << std::endl;
		Claws(OPEN);
		InternalState++;
	}

	//Go to above the pallets
	else if(InternalState == 3 && palletizer->OuterClawState == 1)
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(manipulator.PalletStack_PositionUP);
		InternalState++;
	}

	//Go down towards the pallets

	else if(InternalState == 4 && ManipulatorArrived(manipulator.PalletStack_PositionUP))
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(manipulator.PalletStack_PositionDOWN);
		InternalState++;

	}

	//Close the claws to middle
	else if(InternalState == 5 && (ManipulatorArrived(manipulator.PalletStack_PositionDOWN) || palletizer->StopProximitySwitchDetectionOfzAxis == true))
	{
		std::cout << "state: " << InternalState << std::endl;
		Claws(HALF);
		InternalState++;
	}
	//Go slightly up
	else if(InternalState == 6 && palletizer->OuterClawState == 1)
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(manipulator.PalletStack_PositionUP);
		InternalState++;
	}
	//Go to above the pallet place desired
	else if(InternalState == 7 && ManipulatorArrived(manipulator.PalletStack_PositionUP))
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(Destination.PositionUP);
		InternalState++;
	}
	//Go down until pallet
	else if(InternalState == 8 && ManipulatorArrived(Destination.PositionUP))
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(Destination.PositionDOWN);
		InternalState++;
	}
	//Go down until pallet
	else if(InternalState == 9 && ManipulatorArrived(Destination.PositionUP))
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(Destination.PositionDOWN+MovementVector(0,0,2000,0));
		InternalState++;
	}
	//Open the claws
	else if(InternalState == 10 && (ManipulatorArrived(Destination.PositionDOWN) || palletizer->StopProximitySwitchDetectionOfzAxis == true))
	{
		std::cout << "state: " << InternalState << std::endl;
		Claws(OPEN);
		InternalState++;
	}

	//Go to above the pallet place desired
	else if(InternalState == 11 && palletizer->OuterClawState == 1)
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(Destination.PositionUP);
		InternalState++;
	}
	//Close the claws
	else if(InternalState == 12 && ManipulatorArrived(Destination.PositionUP))
	{
		std::cout << "state: " << InternalState << std::endl;
		Claws(CLOSE);
		InternalState++;
	}

	//Go to working Position
	else if(InternalState == 13 && palletizer->OuterClawState == 1)
	{
		std::cout << "state: " << InternalState << std::endl;
		Target = PerformMovement(manipulator.Working_Position);
		InternalState++;
	}

	//unlatch
	else if(InternalState == 14 && ManipulatorArrived(manipulator.Working_Position) )
	{
		std::cout << "state: " << InternalState << std::endl;
		*GrabPalletLatch = false;
		InternalState=0;
	}

}

const int CALIBRATION = 4;
const int IDLE = 0;
const int AUTOMATIC = 1;


int Mode=AUTOMATIC;
void* AlgorithmLoop(void *Arg)
{
	Synchro::DecreaseSynchronizationPointValue(0);
	//FirstCycle=true;
	//JAGMbool casa=false;
	loadKeyPoints();
	bool calibrated=false;
	while(1)
	{
		CheckCalibration(&calibrated); //this just checks the origin.




		//Test on simulator
		static JAGMbool GrabPalletLatch=true;
		static int times=3;
		if(calibrated == true && Mode == AUTOMATIC && GrabPalletLatch && times>0)
		{
			GrabPallet(&GrabPalletLatch, PalletPlaceA);
		}
		if(GrabPalletLatch==false && GrabPalletLatch.previousValue == true && times>0){
			times--;
			std::cout << "Cicle finished detected" << std::endl;
			GrabPalletLatch = true;
		}





		//Test
		/*
		MovementVector movement1(1000,1000, 2000, 0);
		MovementVector movement2(5000,5000, 2000, 0);
		MovementVector movement3(8000,5000, 2000, 0);
		MovementVector movement4(5000,1000, 2000, 0);

		if(ManipulatorArrived(MovementVector(0,0,0,0)))
		{
			PerformMovement(movement1);
			std::cout << "origin reached " << std::endl;
		}
		if(ManipulatorArrived(movement1))
		{
			PerformMovement(movement2);
			std::cout << "1 reached " << std::endl;
		}
		if(ManipulatorArrived(movement2))
		{
			PerformMovement(movement3);
			std::cout << "2 reached " << std::endl;
		}
		if(ManipulatorArrived(movement3))
		{
			PerformMovement(movement4);
			std::cout << "3 reached " << std::endl;
		}
		if(ManipulatorArrived(movement4))
		{
			PerformMovement(movement1);
			std::cout << "4 reached " << std::endl;
		}


		*/


		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return nullptr;
}
