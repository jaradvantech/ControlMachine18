/*
 * Algorithm.cpp
 *
 *  Created on: May 10, 2018
 *      Author: andres
 */

#include "Algorithm.h"
#include <SynchronizationPoints.h>
#include <Palletizer.h>
#include <deque>

/*						DATA STRUCTURES USED						*/




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
struct MovementVector{
	int x=0;
	int y=0;
	int z=0;
	int w=0;

	friend MovementVector operator+ (MovementVector lhs, const MovementVector & rhs){
		lhs.x+=rhs.x;
		lhs.y+=rhs.y;
		lhs.z+=rhs.z;
		lhs.w+=rhs.w;
		return lhs;
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
	MovementVector Working_Position;

	MovementVector PalletStack_PositionUP;
	MovementVector PalletStack_PositionDOWN;

	MovementVector PalletA_PositionUP;
	MovementVector PalletB_PositionUP;

	MovementVector PalletA_PositionDOWN;
	MovementVector PalletB_PositionDOWN;

	MovementVector GrabBoxes_PositionUP;
	MovementVector GrabBoxes_PositionDOWN;



};

class PalletPlace{
	struct MovementVectorContainer{
		MovementVector LandingPosition;
		MovementVector DisplacedPosition;
	};
	typedef std::vector<MovementVectorContainer> Receipe; //The first elem
	typedef std::deque<Receipe> Orders;
	private:
	Orders ListOfPalletsTodo;
	int actualPosition=0;
	bool PalletReady=0;
	public:

	void SetConfigurationForNextPallet(Receipe receipe){
		if(ListOfPalletsTodo.size()<=1){
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
			ListOfPalletsTodo.push_back(ListOfPalletsTodo.at(ListOfPalletsTodo.size()-1));
			ListOfPalletsTodo.pop_front();
			actualPosition=0;
		}
	}

	bool isPalletReady() const
	{
		return PalletReady;
	}
	void setPalletReady(bool palletReady)
	{
		PalletReady = palletReady;
	}

};



JAGMbool FirstCycle=true;
JAGMbool M0;


JAGMbool P0=false; //PC Ready
JAGMbool P1=false; //Go waiting position
JAGMbool P2=false; //Waiting
JAGMbool P3=false; //Flat
JAGMbool P4=false; //Rolling over
JAGMbool P5=false; //GRAB PALLET
JAGMbool P6=false; //Emergency stop
JAGMbool P7=false; //GRAB PALLET
JAGMbool P8=false; //GRAB BOX


JAGMbool P0_1=false;
JAGMbool P0_2=false;
JAGMbool P0_3=false;
JAGMbool P0_4=false;
JAGMbool P0_5=false;
JAGMbool P0_6=false;
JAGMbool P0_7=false;
JAGMbool P0_8=false;
JAGMbool P0_9=false;
JAGMbool P0_10=false;
JAGMbool P0_11=false;
JAGMbool P0_12=false;


JAGMbool P1_1=false;
JAGMbool P1_2=false;
JAGMbool P1_3=false;
JAGMbool P1_4=false;
JAGMbool P1_5=false;
JAGMbool P1_6=false;
JAGMbool P1_7=false;
JAGMbool P1_8=false;
JAGMbool P1_9=false;
JAGMbool P1_10=false;
JAGMbool P1_11=false;



JAGMbool T0__1=false;
JAGMbool T1__2=false;
JAGMbool T2__3=false;
JAGMbool T2__4=false;
JAGMbool T3__2=false;
JAGMbool T3__5=false;
JAGMbool T3__6=false;
JAGMbool T4__6=false;
JAGMbool T4__7=false;
JAGMbool T4__8=false;
JAGMbool T5__2=false;
JAGMbool T7__8=false;
JAGMbool T8__1=false;

JAGMbool T0_0__0_1=false;
JAGMbool T0_1__0_2=false;
JAGMbool T0_2__0_3=false;
JAGMbool T0_3__0_4=false;
JAGMbool T0_4__0_5=false;
JAGMbool T0_5__0_6=false;
JAGMbool T0_6__0_7=false;
JAGMbool T0_7__0_8=false;
JAGMbool T0_8__0_9=false;
JAGMbool T0_9__0_10=false;
JAGMbool T0_10__0_11=false;
JAGMbool T0_11__0_12=false;

JAGMbool T1_0__0_1=false;
JAGMbool T1_1__0_2=false;
JAGMbool T1_2__0_3=false;
JAGMbool T1_3__0_4=false;
JAGMbool T1_4__0_5=false;
JAGMbool T1_5__0_6=false;
JAGMbool T1_6__0_7=false;
JAGMbool T1_7__0_8=false;
JAGMbool T1_8__0_9=false;
JAGMbool T1_9__0_10=false;
JAGMbool T1_10__0_11=false;


static Palletizer* palletizer = GetPalletizer();

ManipulatorGeneral manipulator;
PalletPlace palletA;
PalletPlace palletB;

void PerformMovement(int x, int y, int z, int w){
	palletizer->XAxisSetting=x;
	palletizer->YAxisSetting=y;
	palletizer->ZAxisSetting=z;
	palletizer->WAxisSetting=w;
}

void PerformMovement(MovementVector _movement){
	palletizer->XAxisSetting=_movement.x;
	palletizer->YAxisSetting=_movement.y;
	palletizer->ZAxisSetting=_movement.z;
	palletizer->WAxisSetting=_movement.w;
}

void ProcessStatesGeneralMission()
{
	if(P0) {
		palletizer->AlarmAndStop=2;
	}
	if(P1) {
		palletizer->SystemState=1;
		//PerformMovement();
		palletizer->FingerMovement=1;
	}
	if(P2) {

	}
	if(P3) {
		palletizer->LocationRollingOver=1;
	}
	if(P4) {
		palletizer->LocationRollingOver=2;
	}
	if(P5) {

	}
	if(P6) {
		//SHOW ALARMS
	}
	if(P7) {


	}
	if(P8) {

	}
}

void ProcessStatesGrabPallet()
{
	if(P0_1) {
		//PerformMovement(); //Move to working Position
	}
	if(P0_2) {
		palletizer->FingerMovement=3; //Close fingers
	}
	if(P0_3) {
		//PerformMovement(); //Move to ABOVE of where the pallet stack is
	}
	if(P0_4) {
		//PerformMovement(); //Move DOWN to where the pallet is
	}
	if(P0_5) {
		palletizer->OuterClawMovement=2;
	}
	if(P0_6) {
		//PerformMovement(); //Move UP to where the pallet is
	}
	if(P0_7) {
		//PerformMovement(); //Move to ABOVE of the place of the storage A or B
	}
	if(P0_8) {
		//PerformMovement(); //Move DOWN to the storage location
	}
	if(P0_9) {
		palletizer->OuterClawMovement=1;
	}
	if(P0_10) {
		//PerformMovement(); //Move UP
	}
	if(P0_11) {
		//PerformMovement(); //Move to working Position
		palletizer->OuterClawMovement=3;
	}
	if(P0_12) {

	}
}

void ProcessStatesGrabBrick()
{
	if(P1_1) {
		//PerformMovement();
	}
	if(P1_2) {
		palletizer->FingerMovement=1;
	}
	if(P1_3) {
		//PerformMovement();
	}
	if(P1_4) {
		palletizer->FingerMovement=3;
	}
	if(P1_5) {
		//PerformMovement();
	}
	if(P1_6) {
		//PerformMovement();
	}
	if(P1_7) {
		palletizer->FingerMovement=2;
	}
	if(P1_8) {
		//PerformMovement();
	}
	if(P1_9) {
		//PerformMovement();
	}
	if(P1_10) {
		//PerformMovement();
	}
}

bool ManipulatorArrived(MovementVector Destination)
{
	//This function checks if the actual position matches the position that was set for the manipulator, within a certain range.
	float MarginUP=1.05;
	float MarginDOWN=0.95;
	if(Destination.x>palletizer->RealTimeValueOfxAxis*MarginUP ||
	   Destination.x<palletizer->RealTimeValueOfxAxis*MarginDOWN) return false;
	if(Destination.y>palletizer->RealTimeValueOfyAxis*MarginUP ||
	   Destination.y<palletizer->RealTimeValueOfyAxis*MarginDOWN) return false;
	if(Destination.z>palletizer->RealTimeValueOfzAxis*MarginUP ||
	   Destination.z<palletizer->RealTimeValueOfzAxis*MarginDOWN) return false;
	if(Destination.w>palletizer->RealTimeValueOfwAxis*MarginUP ||
	   Destination.w<palletizer->RealTimeValueOfwAxis*MarginDOWN) return false;
	return true;
}


void* AlgorithmLoop(void *Arg)
{
	Synchro::DecreaseSynchronizationPointValue(0);
	//FirstCycle=true;
	//JAGMbool casa=false;
	while(1)
	{
		//Logic general mission
		P0= M0 && ((P0 && !P1));
		P1= M0 && ((P1 && !P2) || (P0 && T0__1) || (P8 && T8__1));
		P2= M0 && ((P2 && !P3 && !P4) || (P1 && T1__2) || (P3 && T3__2) || (P5 && T5__2));
		P3= M0 && ((P3 && !P5) || (P2 && T2__3));
		P4= M0 && ((P4 && !P2) || (P4 && T2__4));
		P5= M0 && ((P5 && !P2) || (P3 && T3__5));
		P6= M0 && ((P6) || (P3 && T3__6) || (P4 && T4__6));
		P7= M0 && ((P7 && !P8) || (P4 && T4__7));
		P8= M0 && ((P8 && !P1) || (P4 && T4__8) || (P7 && T7__8));

		//Logic grab pallet
		P0_1 = M0 && ((P0_1 && !P0_2) || (T0_0__0_1));
		P0_2 = M0 && ((P0_2 && !P0_3) || (P0_1 && T0_1__0_2));
		P0_3 = M0 && ((P0_3 && !P0_4) || (P0_2 && T0_2__0_3));
		P0_4 = M0 && ((P0_4 && !P0_5) || (P0_3 && T0_3__0_4));
		P0_5 = M0 && ((P0_5 && !P0_6) || (P0_4 && T0_4__0_5));
		P0_6 = M0 && ((P0_6 && !P0_7) || (P0_5 && T0_5__0_6));
		P0_7 = M0 && ((P0_7 && !P0_8) || (P0_6 && T0_6__0_7));
		P0_8 = M0 && ((P0_8 && !P0_9) || (P0_7 && T0_7__0_8));
		P0_9 = M0 && ((P0_9 && !P0_10) || (P0_8 && T0_8__0_9));
		P0_10 = M0 && ((P0_10 && !P0_11) || (P0_9 && T0_9__0_10));
		P0_11 = M0 && ((P0_11 && !P0_3) || (P0_10 && T0_10__0_11));
		P0_12 = M0 && ((P0_12 && (P7 || P4)) || (P0_11 && T0_11__0_12));

		//Logic grab brick

		P1_1 = M0 && ((P1_1 && !P1_2) || (T1_0__0_1));
		P1_2 = M0 && ((P1_2 && !P1_3) || (P1_1 && T1_1__0_2));
		P1_3 = M0 && ((P1_3 && !P1_4) || (P1_2 && T1_2__0_3));
		P1_4 = M0 && ((P1_4 && !P1_5) || (P1_3 && T1_3__0_4));
		P1_5 = M0 && ((P1_5 && !P1_6) || (P1_4 && T1_4__0_5));
		P1_6 = M0 && ((P1_6 && !P1_7) || (P1_5 && T1_5__0_6));
		P1_7 = M0 && ((P1_7 && !P1_8) || (P1_6 && T1_6__0_7));
		P1_8 = M0 && ((P1_8 && !P1_9) || (P1_7 && T1_7__0_8));
		P1_9 = M0 && ((P1_9 && !P1_10) || (P1_8 && T1_8__0_9));
		P1_10 = M0 && ((P1_10 && !P1_11) || (P1_9 && T1_9__0_10));
		P1_11 = M0 && ((P1_11 && P8) || (P1_10 && T1_10__0_11));


		//Process states of General mission
		ProcessStatesGeneralMission();
		//Process states of Grab pallet
		ProcessStatesGrabPallet();
		//Process states of Grab brick
		ProcessStatesGrabBrick();
		//Process transitions of General mission
		T0__1=(1==palletizer->OverTurnTable) && (1==palletizer->PLCSystemState) ;
		T1__2=ManipulatorArrived(manipulator.Working_Position); //Arrived
		T2__3=(2==palletizer->LocationRollingOverState) && (2==palletizer->OverTurnTable);
		T2__4=(1==palletizer->LocationRollingOverState) && (1==palletizer->OverTurnTable);
		T3__2=(2==palletizer->StorageBinOfPalletState);
		T3__5=(1==palletizer->StorageBinOfPalletState) && (1==palletizer->PhotoelectricSensorOfPallet1);
		T3__6=(1==palletizer->StorageBinOfPalletState) && (2==palletizer->PhotoelectricSensorOfPallet1);
		T4__6=(2==palletizer->PalletSignalOfA) && (2==palletizer->PalletSignalOfB) &&
				((2==palletizer->StorageBinOfPalletState) || ((1==palletizer->StorageBinOfPalletState)&&(2==palletizer->PhotoelectricSensorOfPallet1)));
		T4__7=(2==palletizer->PalletSignalOfA) && (2==palletizer->PalletSignalOfB) &&
				(1==palletizer->StorageBinOfPalletState) && (1==palletizer->PhotoelectricSensorOfPallet1);
		T4__8=(1==palletizer->PalletSignalOfA) && (1==palletizer->PalletSignalOfB);
		T5__2=P0_12.TriggerUP();
		T7__8=P0_12.TriggerUP();
		T8__1=P1_11.TriggerUP();

		//Process transitions of Grab pallet
		T0_0__0_1=P5.TriggerUP() || P8.TriggerUP();
		T0_1__0_2=ManipulatorArrived(manipulator.Working_Position); //arrived
		T0_2__0_3=(2==palletizer->FingerState) && (1==palletizer->InnerFingerState);
		T0_3__0_4=ManipulatorArrived(manipulator.PalletStack_PositionUP); //arrived
		T0_4__0_5=ManipulatorArrived(manipulator.PalletStack_PositionDOWN); //arrived
		T0_5__0_6=(2==palletizer->FingerState);
		T0_6__0_7=ManipulatorArrived(manipulator.PalletStack_PositionUP); //arrived
		T0_7__0_8=ManipulatorArrived(manipulator.PalletA_PositionUP) || ManipulatorArrived(manipulator.PalletB_PositionUP); //arrived
		T0_8__0_9=ManipulatorArrived(manipulator.PalletA_PositionDOWN) || ManipulatorArrived(manipulator.PalletB_PositionDOWN); //arrived
		T0_9__0_10=(2==palletizer->OuterClawState);
		T0_10__0_11=ManipulatorArrived(manipulator.PalletA_PositionUP) || ManipulatorArrived(manipulator.PalletB_PositionUP); //arrived
		T0_11__0_12=ManipulatorArrived(manipulator.Working_Position) && (1==palletizer->OuterClawState); // and arrived

		//Process transitions of Grab brick
		T1_0__0_1=P8.TriggerUP();
		T1_1__0_2=ManipulatorArrived(manipulator.GrabBoxes_PositionUP); //arrived
		T1_2__0_3=(1==palletizer->FingerState);
		T1_3__0_4=ManipulatorArrived(manipulator.GrabBoxes_PositionDOWN); //arrived
		T1_4__0_5=(2==palletizer->FingerState);
		T1_5__0_6=ManipulatorArrived(manipulator.GrabBoxes_PositionUP); //arrived
		T1_6__0_7=ManipulatorArrived(palletA.GetNextBoxPosition().LandingPosition) || ManipulatorArrived(palletB.GetNextBoxPosition().LandingPosition); //arrived
		T1_7__0_8=(2==palletizer->FingerState);
		T1_8__0_9=ManipulatorArrived(palletA.GetActualBoxPosition().DisplacedPosition) || ManipulatorArrived(palletB.GetActualBoxPosition().DisplacedPosition); //arrived
		T1_9__0_10=ManipulatorArrived(manipulator.PalletA_PositionUP) || ManipulatorArrived(manipulator.PalletB_PositionUP); //arrived
		T1_10__0_11=ManipulatorArrived(manipulator.Working_Position); //arrived
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return nullptr;
}
