/*
 * Palletizer.h
 *
 *  Created on: Mar 30, 2018
 *      Author: andres
 */

#ifndef PALLETIZER_H_
#define PALLETIZER_H_

#include <stdint.h>


struct PalletizerConfigInfo
{
	public:
	int IODBReading;		//DB that holds the PLC information that the PC has to read
	int IODBWriting;		//DB that holds the PLC information that the PC has to write
	int ReadingStartByte; 	//Number of the position where the reading variables are located at the DB. For the first Arm.
	int ReadingLength;		//Number of bytes that have to be red.
	int WritingStartByte;	//Number of the position where the writing variables are located at the DB.For the first Arm.
	int WritingLength;		//Number of bytes that have to be written.
};

class Palletizer
{
	private:
	PalletizerConfigInfo _PalletizerConfigInfo;
	public:
	void SetPalletizerConfig(PalletizerConfigInfo argPalletizerConfigInfo);
	PalletizerConfigInfo GetPalletizerConfig();
	Palletizer();

	//Variables
	//-----------------------------------------------
	//PC Read variables
	//----------------------------------------
	bool EmergencyStopOfElectricCabinet;
	bool AutomaticSelectionSwitch;
	bool ManualSelectionSwitch;
	bool StartSwitch;
	bool StopSwitch;
	bool ResetButton;
	bool AlarmSilencing;
	bool xAxisForward;
	bool xAxisReversal;
	bool yAxisForward;
	bool yAxisReversal;
	bool zAxisForward;
	bool zAxisReversal;
	bool wAxisForward;
	bool wAxisReversal;
	bool PalletSelection1;
	bool FrameEmergencyStop;
	bool FrameStartButton;
	bool RegionProtectionGrating;
	bool PalletStorageBinPhotoelectricDetectionOfA;
	bool PalletStorageBinPhotoelectricDetectionOfB;
	bool PalletStorageBinPhotoelectricDetection;
	bool ZeroPositionProximitySwitchDetectionOfxAxis;
	bool ZeroPositionProximitySwitchDetectionOfyAxis;
	bool ZeroPositionProximitySwitchDetectionOfzAxis;
	bool ZeroPositionProximitySwitchDetectionOfwAxis;
	bool PalletSelection2;
	bool ZeroPositionAuxiliaryProximitySwitchOfyAxis1;
	bool AirPressureDetectionSwitch;
	bool LimitProximitySwitchDetectionOfwAxis;
	bool StopProximitySwitchDetectionOfzAxis;
	bool LimitProximitySwitchDetectionOfzAxis;
	bool LeftHandFingerOpenDetection;
	bool LeftHandFingerClosedDetection;
	bool RightHandFingerOpenDetection;
	bool RightHandFingerClosedDetection;
	bool HalfTheMagneticDetectionSwitchOfFinger;
	bool ClosedTheMagneticDetectionSwitchOfFinger;
	bool DetectionOfMechanicalLimitStrokeSwitchOfxAxis1;
	bool DetectionOfMechanicalLimitStrokeSwitchOfxAxis2;
	bool DetectionOfMechanicalLimitStrokeSwitchOfyAxis1;
	bool DetectionOfMechanicalLimitStrokeSwitchOfyAxis2;
	bool DetectionOfMechanicalLimitStrokeSwitchOfzAxis1;
	bool DetectionOfMechanicalLimitStrokeSwitchOfzAxis2;
	bool AuxiliaryZeroPositionProximitySwitchOfxAxis;
	bool FrequencyConverterAlarmOfxAxis;
	bool FrequencyConverterAlarmOfyAxis;
	bool FrequencyConverterAlarmOfzAxis;
	bool FrequencyConverterAlarmOfwAxis;
	bool PalletSelection3;
	bool ZeroPositionAuxiliaryProximitySwitchOfyAxis2;
	bool PawPositionSelection;
	bool SomeoneEnteredTheLoadingArea;
	bool TheAlarmOfBrickStorehouseDidNotClose1;
	bool TheAlarmOfBrickStorehouseDidNotClose2;

	int PLCSystemState; 						//1.Run 2.Initialize 3.Manual 4.Emergency Stop
	int RealTimeValueOfxAxis;					//
	int RealTimeValueOfyAxis;
	int RealTimeValueOfzAxis;
	int RealTimeValueOfwAxis;
	int InnerFingerState;							//Clip state 1.Done 2.Wait
	int OuterClawState;							//Outer ClawState 1.Done 2.Wait
	int LocationRollingOverState;				//Location Rolling-Over 1.Done 2.Action
	int StorageBinOfPalletState;				//1.Yes 2.No
	int OverTurnTable;							//1.Yes 2.No
	int LimitOptoelectronicOfZAxis;				//1.Yes 2.No
	int PhotoelectricSensorOfPallet1;			//1.Yes 2.No
	int PalletSignalOfA;						//1.Yes 2.No
	int OutputChooseA;							//1.Yes 2.No
	int PalletSignalOfB;						//1.Yes 2.No
	int OutputChooseB;							//1.Yes 2.No
	int FlipPlatformLevel;						//1.Yes 2.No
	int FlipPlatformVertical;					//1.Yes 2.No
	int PhotoelectricSensorOfPallet2;			//Photoelectric sensor of Pallet 2
	int PhotoelectricSensorOfPallet3;			//Photoelectric sensor of Pallet 3
	int SupplementaryPalletAB;					//1.Yes 2.No
	int FingerState;							//FingerOpening 1.All 2.No All
	int EquipmentStopState;						//1.Yes 2.No
	int OpenThePhotoelectricSensorDetection;	//1.All 2.?  3.All and No All 4.All Off
	int CloseThePhotoelectricSensorDetection;	//1.All 2.?  3.All and No All 4.All Off
	int ReadyOfA;								//Reset Completion Of A Output
	int ReadyOfB;								//Reset Completion Of B Output
	int DoorRodBackA;							//A Baffle Back
	int DoorRodBackB;							//B Baffle Back
	int SequenceOfTheLastGrab;
	int NumberOfTheLastGrab;
	int TheInstructionsOfTheChangePallet;		//Replacement condition, rear line emptying 1. change
	int TheTileOf1200cm;						//1. 1.2M 0.Other


	//----------------------------------------
	//PC Write variables
	//----------------------------------------
	int SystemState; //1:Run 2:Wait

	int XAxisSetting;//X axis
	int YAxisSetting;//X axis
	int ZAxisSetting;//X axis
	int WAxisSetting;//X axis

	int FingerMovement; 	//Clip the tile 1.Open 2.Half open 3.Closed
	int OuterClawMovement;	//OuterClaw 1.Open 2.Half open 3.Closed
	int LocationRollingOver;//Location Rolling-Over 1.Flat 2.Rolling-over

	int TheSpeedOfXAxis;
	int TheSpeedOfYAxis;
	int TheSpeedOfZAxis;
	int TheSpeedOfWAxis;

	int OverRunAlarm;
	int HostComputerControlTheSpeedOfXAxis;
	int AlarmAndStop;		//Stop position of 18 1.Suspend 2.Start

	int ManualControlOfScreen;						//0.Button control 1.Screen control
	int ManualControlTheXAxisOfTheScreen;			//0.Stop 1.Forward 2.Back
	int ManualControlTheYAxisOfTheScreen;			//0.Stop 1.Left	2.Right
	int ManualControlTheZAxisOfTheScreen;			//0.Stop 1.Up 2.Down
	int ManualControlTheWAxisOfTheScreen;			//0.Stop 1.Clockwise 2.Anti-clockwisw
	int ManualControlTheFingerOfTheScreen;			//1.Open 2.Half 3.Closed
	int ManualControlTheOuterClawOfTheScreen;		//1.Open 2.Half 3.Closed

	int StorageBinFullA;							//1.Turn OFF 2. Torn ON
	int StorageBinFullB;							//1.Turn OFF 2. Torn ON

	int TheTimeOfTheOuterClawHalfOpen;
	int WipeDataOfTheChangeTileAndStorageBinFull;	//Clear the last grab
	int NearALowSpeed;								//1.Near a low speed 0. Go through the pulse value
	int TheNumberOfPackages;						//Exchange data bits

	int TheHighestSpeedOfXAxis;
	int DecelerationTimeOfXAxis;
	int DecelerationDistanceOfXAxis;
	int NoLoadTimeOfXAxis;
	int NoLoadDistanceOfXAxis;
	int ManualSpeedOfXAxis;

	int TheHighestSpeedOfYAxis;
	int DecelerationTimeOfYAxis;
	int DecelerationDistanceOfYAxis;
	int NoLoadTimeOfYAxis;
	int NoLoadDistanceOfYAxis;
	int ManualSpeedOfYAxis;

	int TheHighestSpeedOfZAxis;
	int DecelerationTimeOfZAxis;
	int DecelerationDistaceOfZAxis;
	int ManualSpeedOfZAxis;

	int TheHighestSpeedOfWAxis;
	int DecelerationTimeOfWAxis;
	int DecelerationDistanceOfWAxis;
	int NoLoadTimeOfWAxis;
	int NoLoadDistanceOfWAxis;
	int ManualSpeedOfWAxis;

	int TheAccuracyOfXAxis;
	int TheAccuracyOfYAxis;
	int TheAccuracyOfZAxis;
	int TheAccuracyOfWAxis;

	int CommunicationExchange;
	//-----------------------------------------------

};

Palletizer* GetPalletizer();

int PerformGlobalWriting();
int PerformGlobalReading();


#endif /* PALLETIZER_H_ */
