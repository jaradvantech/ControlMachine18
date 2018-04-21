/*
 * Palletizer.cpp
 *
 *  Created on: Mar 30, 2018
 *      Author: andres
 */


#include "Palletizer.h"
#include "PLCInterface.h"

#include <stdint.h>


Palletizer palletizer;

Palletizer::Palletizer()
{
	_PalletizerConfigInfo.IODBReading=0;		//DB that holds the PLC information that the PC has to read
	_PalletizerConfigInfo.IODBWriting=0;		//DB that holds the PLC information that the PC has to write
	_PalletizerConfigInfo.ReadingStartByte=0; 	//Number of the position where the reading variables are located at the DB. For the first Arm.
	_PalletizerConfigInfo.ReadingLength=0;		//Number of bytes that have to be red.
	_PalletizerConfigInfo.WritingStartByte=0;	//Number of the position where the writing variables are located at the DB.For the first Arm.
	_PalletizerConfigInfo.WritingLength=0;		//Number of bytes that have to be written.
	//Variables
	//-----------------------------------------------
	//PC Read variables
	//----------------------------------------
	EmergencyStopOfElectricCabinet=0;
	AutomaticSelectionSwithc=0;
	ManualSelectionSwitch=0;
	StartSwitch=0;
	StopSwitch=0;
	ResetButton=0;
	AlarmSilencing=0;
	xAxisForward=0;
	xAxisReversal=0;
	yAxisForward=0;
	yAxisReversal=0;
	zAxisForward=0;
	zAxisReversal=0;
	wAxisForward=0;
	wAxisReversal=0;
	PalletSelection1=0;
	FrameEmergencyStop=0;
	FrameStartButton=0;
	RegionProtectionGrating=0;
	PalletStorageBinPhotoelectricDetectionOfA=0;
	PalletStorageBinPhotoelectricDetectionOfB=0;
	PalletStorageBinPhotoelectricDetection=0;
	ZeroPositionProximitySwitchDetectionOfxAxis=0;
	ZeroPositionProximitySwitchDetectionOfyAxis=0;
	ZeroPositionProximitySwitchDetectionOfzAxis=0;
	ZeroPositionProximitySwitchDetectionOfwAxis=0;
	PalletSelection2=0;
	ZeroPositionAuxiliaryProximitySwitchOfyAxis1=0;
	AirPressureDetectionSwitch=0;
	LimitProximitySwitchDetectionOfwAxis=0;
	StopProximitySwitchDetectionOfzAxis=0;
	LimitProximitySwitchDetectionOfzAxis=0;
	LeftHandFingerOpenDetection=0;
	LeftHandFingerClosedDetection=0;
	RightHandFingerOpenDetection=0;
	RightHandFingerClosedDetection=0;
	HalfTheMagneticDetectionSwitchOfFinger=0;
	ClosedTheMagneticDetectionSwitchOfFinger=0;
	DetectionOfMechanicalLimitStrokeSwitchOfxAxis1=0;
	DetectionOfMechanicalLimitStrokeSwitchOfxAxis2=0;
	DetectionOfMechanicalLimitStrokeSwitchOfyAxis1=0;
	DetectionOfMechanicalLimitStrokeSwitchOfyAxis2=0;
	DetectionOfMechanicalLimitStrokeSwitchOfzAxis1=0;
	DetectionOfMechanicalLimitStrokeSwitchOfzAxis2=0;
	AuxiliaryZeroPositionProximitySwitchOfxAxis=0;
	FrequencyConverterAlarmOfxAxis=0;
	FrequencyConverterAlarmOfyAxis=0;
	FrequencyConverterAlarmOfzAxis=0;
	FrequencyConverterAlarmOfwAxis=0;
	PalletSelection3=0;
	ZeroPositionAuxiliaryProximitySwitchOfyAxis2=0;
	PawPositionSelection=0;
	SomeoneEnteredTheLoadingArea=0;
	TheAlarmOfBrickStorehouseDidNotClose1=0;
	TheAlarmOfBrickStorehouseDidNotClose2=0;

	PLCSystemState=0; 						//1.Run 2.Initialize 3.Manual 4.Emergency Stop
	RealTimeValueOfxAxis=0;					//
	RealTimeValueOfyAxis=0;
	RealTimeValueOfzAxis=0;
	RealTimeValueOfwAxis=0;
	InnerFingerState=0;							//Clip state 1.Done 2.Wait
	OuterClawState=0;							//Outer ClawState 1.Done 2.Wait
	LocationRollingOverState=0;				//Location Rolling-Over 1.Done 2.Action
	StorageBinOfPalletState=0;
	OverTurnTable=0;							//1.Yes 2.No
	LimitOptoelectronicOfZAxis=0;				//1.Yes 2.No
	PhotoelectricSensorOfPallet1=0;			//1.Yes 2.No
	PalletSignalOfA=0;						//1.Yes 2.No
	OutputChooseA=0;							//1.Yes 2.No
	PalletSignalOfB=0;						//1.Yes 2.No
	OutputChooseB=0;							//1.Yes 2.No
	FlipPlatformLevel=0;						//1.Yes 2.No
	FlipPlatformVertical=0;					//1.Yes 2.No
	PhotoelectricSensorOfPallet2=0;			//Photoelectric sensor of Pallet 2
	PhotoelectricSensorOfPallet3=0;			//Photoelectric sensor of Pallet 3
	SupplementaryPalletAB=0;					//1.Yes 2.No
	FingerState=0;							//FingerOpening 1.All 2.No All
	EquipmentStopState=0;						//1.Yes 2.No
	OpenThePhotoelectricSensorDetection=0;	//1.All 2.?  3.All and No All 4.All Off
	CloseThePhotoelectricSensorDetection=0;	//1.All 2.?  3.All and No All 4.All Off
	ReadyOfA=0;								//Reset Completion Of A Output
	ReadyOfB=0;								//Reset Completion Of B Output
	DoorRodBackA=0;							//A Baffle Back
	DoorRodBackB=0;							//B Baffle Back
	SequenceOfTheLastGrab=0;
	NumberOfTheLastGrab=0;
	TheInstructionsOfTheChangePallet=0;		//Replacement condition, rear line emptying 1. change
	TheTileOf1200cm=0;						//1. 1.2M 0.Other


	//----------------------------------------
	//PC Write variables
	//----------------------------------------
	SystemState=0; //1:Run 2:Wait

	XAxisSetting=0;//X axis
	YAxisSetting=0;//X axis
	ZAxisSetting=0;//X axis
	WAxisSetting=0;//X axis

	FingerMovement=0; 	//Clip the tile 1.Open 2.Half open 3.Closed
	OuterClawMovement=0;	//OuterClaw 1.Open 2.Half open 3.Closed
	LocationRollingOver=0;//Location Rolling-Over 1.Flat 2.Rolling-over

	TheSpeedOfXAxis=0;
	TheSpeedOfYAxis=0;
	TheSpeedOfZAxis=0;
	TheSpeedOfWAxis=0;

	OverRunAlarm=0;
	HostComputerControlTheSpeedOfXAxis=0;
	AlarmAndStop=0;		//Stop position of 18 1.Suspend 2.Start

	ManualControlOfScreen=0;						//0.Button control 1.Screen control
	ManualControlTheXAxisOfTheScreen=0;			//0.Stop 1.Forward 2.Back
	ManualControlTheYAxisOfTheScreen=0;			//0.Stop 1.Left	2.Right
	ManualControlTheZAxisOfTheScreen=0;			//0.Stop 1.Up 2.Down
	ManualControlTheWAxisOfTheScreen=0;			//0.Stop 1.Clockwise 2.Anti-clockwisw
	ManualControlTheFingerOfTheScreen=0;			//1.Open 2.Half 3.Closed
	ManualControlTheOuterClawOfTheScreen=0;		//1.Open 2.Half 3.Closed

	StorageBinFullA=0;							//1.Turn OFF 2. Torn ON
	StorageBinFullB=0;							//1.Turn OFF 2. Torn ON

	TheTimeOfTheOuterClawHalfOpen=0;
	WipeDataOfTheChangeTileAndStorageBinFull=0;	//Clear the last grab
	NearALowSpeed=0;								//1.Near a low speed 0. Go through the pulse value
	TheNumberOfPackages=0;						//Exchange data bits

	TheHighestSpeedOfXAxis=0;
	DecelerationTimeOfXAxis=0;
	DecelerationDistanceOfXAxis=0;
	NoLoadTimeOfXAxis=0;
	NoLoadDistanceOfXAxis=0;
	ManualSpeedOfXAxis=0;

	TheHighestSpeedOfYAxis=0;
	DecelerationTimeOfYAxis=0;
	DecelerationDistanceOfYAxis=0;
	NoLoadTimeOfYAxis=0;
	NoLoadDistanceOfYAxis=0;
	ManualSpeedOfYAxis=0;

	TheHighestSpeedOfZAxis=0;
	DecelerationTimeOfZAxis=0;
	DecelerationDistaceOfZAxis=0;
	ManualSpeedOfZAxis=0;

	TheAccuracyOfXAxis=0;
	TheAccuracyOfYAxis=0;
	TheAccuracyOfZAxis=0;
	TheAccuracyOfWAxis=0;

	CommunicationExchange=0;
	//-----------------------------------------------
}
Palletizer* GetPalletizer() {return &palletizer;}

PalletizerConfigInfo Palletizer::GetPalletizerConfig()
{
	return _PalletizerConfigInfo;
}

void Palletizer::SetPalletizerConfig(PalletizerConfigInfo argPalletizerConfigInfo)
{
	 _PalletizerConfigInfo=argPalletizerConfigInfo;
}
//--------------------------------------------------------------------
// PerformGlobalReading stores at the PLC the public variables of the object that are set somewhere else in the code
//--------------------------------------------------------------------
int PerformGlobalReading(){
	byte Buffer[palletizer.GetPalletizerConfig().ReadingLength];

	int res = GetPLC18()->DBRead(palletizer.GetPalletizerConfig().IODBReading,
			palletizer.GetPalletizerConfig().ReadingStartByte,
			palletizer.GetPalletizerConfig().ReadingLength,
			&Buffer);
	//----------------------//
	//Get  information//
	//----------------------//
	//Here we parse the buffer

	//S7_SetByteAt(Buffer,1,);
	palletizer.EmergencyStopOfElectricCabinet = S7::GetBitAt(Buffer, 0, 0);
	palletizer.AutomaticSelectionSwithc = S7::GetBitAt(Buffer, 0, 1);
	palletizer.ManualSelectionSwitch = S7::GetBitAt(Buffer, 0, 2);
	palletizer.StartSwitch = S7::GetBitAt(Buffer, 0, 3);
	palletizer.StopSwitch = S7::GetBitAt(Buffer, 0, 4);
	palletizer.ResetButton = S7::GetBitAt(Buffer, 0, 5);
	palletizer.AlarmSilencing = S7::GetBitAt(Buffer, 0, 6);
	palletizer.xAxisForward = S7::GetBitAt(Buffer, 0, 7);
	palletizer.xAxisReversal = S7::GetBitAt(Buffer, 1, 0);
	palletizer.yAxisForward = S7::GetBitAt(Buffer, 1, 1);
	palletizer.yAxisReversal = S7::GetBitAt(Buffer, 1, 2);
	palletizer.zAxisForward = S7::GetBitAt(Buffer, 1, 3);
	palletizer.zAxisReversal = S7::GetBitAt(Buffer, 1, 4);
	palletizer.wAxisForward = S7::GetBitAt(Buffer, 1, 5);
	palletizer.wAxisReversal = S7::GetBitAt(Buffer, 1, 6);
	palletizer.PalletSelection1 = S7::GetBitAt(Buffer, 1, 7);
	palletizer.FrameEmergencyStop = S7::GetBitAt(Buffer, 2, 0);
	palletizer.FrameStartButton = S7::GetBitAt(Buffer, 2, 2);
	palletizer.RegionProtectionGrating = S7::GetBitAt(Buffer, 2, 3);
	palletizer.PalletStorageBinPhotoelectricDetectionOfA = S7::GetBitAt(Buffer, 2, 4);
	palletizer.PalletStorageBinPhotoelectricDetectionOfB = S7::GetBitAt(Buffer, 2, 5);
	palletizer.PalletStorageBinPhotoelectricDetection = S7::GetBitAt(Buffer, 2, 6);
	palletizer.ZeroPositionProximitySwitchDetectionOfxAxis = S7::GetBitAt(Buffer, 2, 7);
	palletizer.ZeroPositionProximitySwitchDetectionOfyAxis = S7::GetBitAt(Buffer, 3, 0);
	palletizer.ZeroPositionProximitySwitchDetectionOfzAxis = S7::GetBitAt(Buffer, 3, 1);
	palletizer.ZeroPositionProximitySwitchDetectionOfwAxis = S7::GetBitAt(Buffer, 3, 2);
	palletizer.PalletSelection2 = S7::GetBitAt(Buffer, 3, 4);
	palletizer.ZeroPositionAuxiliaryProximitySwitchOfyAxis1 = S7::GetBitAt(Buffer, 3, 5);
	palletizer.AirPressureDetectionSwitch = S7::GetBitAt(Buffer, 3, 7);
	palletizer.LimitProximitySwitchDetectionOfwAxis = S7::GetBitAt(Buffer, 4, 0);
	palletizer.StopProximitySwitchDetectionOfzAxis = S7::GetBitAt(Buffer, 4, 1);
	palletizer.LimitProximitySwitchDetectionOfzAxis = S7::GetBitAt(Buffer, 4, 2);
	palletizer.LeftHandFingerOpenDetection = S7::GetBitAt(Buffer, 4, 3);
	palletizer.LeftHandFingerClosedDetection = S7::GetBitAt(Buffer, 4, 4);
	palletizer.RightHandFingerOpenDetection = S7::GetBitAt(Buffer, 4, 5);
	palletizer.RightHandFingerClosedDetection = S7::GetBitAt(Buffer, 4, 6);
	palletizer.HalfTheMagneticDetectionSwitchOfFinger = S7::GetBitAt(Buffer, 4, 7);
	palletizer.ClosedTheMagneticDetectionSwitchOfFinger = S7::GetBitAt(Buffer, 5, 0);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfxAxis1 = S7::GetBitAt(Buffer, 5, 1);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfxAxis2 = S7::GetBitAt(Buffer, 5, 2);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfyAxis1 = S7::GetBitAt(Buffer, 5, 3);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfyAxis2 = S7::GetBitAt(Buffer, 5, 4);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfzAxis1 = S7::GetBitAt(Buffer, 5, 5);
	palletizer.DetectionOfMechanicalLimitStrokeSwitchOfzAxis2 = S7::GetBitAt(Buffer, 5, 6);
	palletizer.AuxiliaryZeroPositionProximitySwitchOfxAxis = S7::GetBitAt(Buffer, 5, 7);
	palletizer.FrequencyConverterAlarmOfxAxis = S7::GetBitAt(Buffer, 6, 0);
	palletizer.FrequencyConverterAlarmOfyAxis = S7::GetBitAt(Buffer, 6, 1);
	palletizer.FrequencyConverterAlarmOfzAxis = S7::GetBitAt(Buffer, 6, 2);
	palletizer.FrequencyConverterAlarmOfwAxis = S7::GetBitAt(Buffer, 6, 3);
	palletizer.PalletSelection3 = S7::GetBitAt(Buffer, 6, 5);
	palletizer.ZeroPositionAuxiliaryProximitySwitchOfyAxis2 = S7::GetBitAt(Buffer, 6, 6);
	palletizer.PawPositionSelection = S7::GetBitAt(Buffer, 6, 7);
	palletizer.SomeoneEnteredTheLoadingArea = S7::GetBitAt(Buffer, 7, 0);
	palletizer.TheAlarmOfBrickStorehouseDidNotClose1 = S7::GetBitAt(Buffer, 7, 1);
	palletizer.TheAlarmOfBrickStorehouseDidNotClose2 = S7::GetBitAt(Buffer, 7, 2);


	palletizer.PLCSystemState=S7::GetByteAt(Buffer,101); 						//1.Run 2.Initialize 3.Manual 4.Emergency Stop
	palletizer.RealTimeValueOfxAxis=S7::GetDIntAt(Buffer,102);					//
	palletizer.RealTimeValueOfyAxis=S7::GetDIntAt(Buffer,106);
	palletizer.RealTimeValueOfzAxis=S7::GetDIntAt(Buffer,110);
	palletizer.RealTimeValueOfwAxis=S7::GetDIntAt(Buffer,114);
	palletizer.InnerFingerState=S7::GetByteAt(Buffer,118);							//Clip state 1.Done 2.Wait
	palletizer.OuterClawState=S7::GetByteAt(Buffer,119);							//Outer ClawState 1.Done 2.Wait
	palletizer.LocationRollingOverState=S7::GetByteAt(Buffer,120);				//Location Rolling-Over 1.Done 2.Action
	palletizer.StorageBinOfPalletState=S7::GetByteAt(Buffer,121);
	palletizer.OverTurnTable=S7::GetByteAt(Buffer,122);							//1.Yes 2.No
	palletizer.LimitOptoelectronicOfZAxis=S7::GetByteAt(Buffer,123);				//1.Yes 2.No
	palletizer.PhotoelectricSensorOfPallet1=S7::GetByteAt(Buffer,124);			//1.Yes 2.No
	palletizer.PalletSignalOfA=S7::GetByteAt(Buffer,125);						//1.Yes 2.No
	palletizer.OutputChooseA=S7::GetByteAt(Buffer,126);							//1.Yes 2.No
	palletizer.PalletSignalOfB=S7::GetByteAt(Buffer,127);						//1.Yes 2.No
	palletizer.OutputChooseB=S7::GetByteAt(Buffer,128);							//1.Yes 2.No
	palletizer.FlipPlatformLevel=S7::GetByteAt(Buffer,129);						//1.Yes 2.No
	palletizer.FlipPlatformVertical=S7::GetByteAt(Buffer,130);					//1.Yes 2.No
	palletizer.PhotoelectricSensorOfPallet2=S7::GetByteAt(Buffer,131);			//Photoelectric sensor of Pallet 2
	palletizer.PhotoelectricSensorOfPallet3=S7::GetByteAt(Buffer,132);			//Photoelectric sensor of Pallet 3
	palletizer.SupplementaryPalletAB=S7::GetByteAt(Buffer,133);					//1.Yes 2.No
	palletizer.FingerState=S7::GetByteAt(Buffer,134);							//FingerOpening 1.All 2.No All
	palletizer.EquipmentStopState=S7::GetByteAt(Buffer,135);						//1.Yes 2.No
	palletizer.OpenThePhotoelectricSensorDetection=S7::GetByteAt(Buffer,136);	//1.All 2.?  3.All and No All 4.All Off
	palletizer.CloseThePhotoelectricSensorDetection=S7::GetByteAt(Buffer,137);	//1.All 2.?  3.All and No All 4.All Off
	palletizer.ReadyOfA=S7::GetByteAt(Buffer,138);								//Reset Completion Of A Output
	palletizer.ReadyOfB=S7::GetByteAt(Buffer,139);								//Reset Completion Of B Output
	palletizer.DoorRodBackA=S7::GetByteAt(Buffer,140);							//A Baffle Back
	palletizer.DoorRodBackB=S7::GetByteAt(Buffer,141);							//B Baffle Back
	palletizer.SequenceOfTheLastGrab=S7::GetByteAt(Buffer,142);
	palletizer.NumberOfTheLastGrab=S7::GetByteAt(Buffer,143);
	palletizer.TheInstructionsOfTheChangePallet=S7::GetByteAt(Buffer,144);		//Replacement condition, rear line emptying 1. change
	palletizer.TheTileOf1200cm=S7::GetByteAt(Buffer,145);						//1. 1.2M 0.Other
	//----------------------------

	return res;
}
//--------------------------------------------------------------------
// PerformGlobalWriting stores at the PLC the public variables of the object that are set somewhere else in the code
//--------------------------------------------NUMBEROFARMS------------------------
int PerformGlobalWriting(){
	byte Buffer[palletizer.GetPalletizerConfig().WritingLength];
	//----------------------//
	//Set the information//
	//----------------------//
	//Here we prepare the buffer
	S7::SetByteAt(Buffer,1,palletizer.SystemState); //1:Run 2:Wait

	S7::SetDIntAt(Buffer,2,palletizer.XAxisSetting);//X axis
	S7::SetDIntAt(Buffer,6,palletizer.YAxisSetting);//X axis
	S7::SetDIntAt(Buffer,10,palletizer.ZAxisSetting);//X axis
	S7::SetDIntAt(Buffer,14,palletizer.WAxisSetting);//X axis

	S7::SetDIntAt(Buffer,18,palletizer.FingerMovement); 	//Clip the tile 1.Open 2.Half open 3.Closed
	S7::SetByteAt(Buffer,19,palletizer.OuterClawMovement);	//OuterClaw 1.Open 2.Half open 3.Closed
	S7::SetByteAt(Buffer,20,palletizer.LocationRollingOver);//Location Rolling-Over 1.Flat 2.Rolling-over

	S7::SetByteAt(Buffer,21,palletizer.TheSpeedOfXAxis);
	S7::SetByteAt(Buffer,22,palletizer.TheSpeedOfYAxis);
	S7::SetByteAt(Buffer,23,palletizer.TheSpeedOfZAxis);
	S7::SetByteAt(Buffer,24,palletizer.TheSpeedOfWAxis);

	S7::SetByteAt(Buffer,25,palletizer.OverRunAlarm);
	S7::SetByteAt(Buffer,26,palletizer.HostComputerControlTheSpeedOfXAxis);
	S7::SetByteAt(Buffer,27,palletizer.AlarmAndStop);		//Stop position of 18 1.Suspend 2.Start

	S7::SetByteAt(Buffer,28,palletizer.ManualControlOfScreen);						//0.Button control 1.Screen control
	S7::SetByteAt(Buffer,29,palletizer.ManualControlTheXAxisOfTheScreen);			//0.Stop 1.Forward 2.Back
	S7::SetByteAt(Buffer,30,palletizer.ManualControlTheYAxisOfTheScreen);			//0.Stop 1.Left	2.Right
	S7::SetByteAt(Buffer,31,palletizer.ManualControlTheZAxisOfTheScreen);			//0.Stop 1.Up 2.Down
	S7::SetByteAt(Buffer,32,palletizer.ManualControlTheWAxisOfTheScreen);			//0.Stop 1.Clockwise 2.Anti-clockwisw
	S7::SetByteAt(Buffer,33,palletizer.ManualControlTheFingerOfTheScreen);			//1.Open 2.Half 3.Closed
	S7::SetByteAt(Buffer,34,palletizer.ManualControlTheOuterClawOfTheScreen);		//1.Open 2.Half 3.Closed

	S7::SetByteAt(Buffer,35,palletizer.StorageBinFullA);							//1.Turn OFF 2. Torn ON
	S7::SetByteAt(Buffer,36,palletizer.StorageBinFullB);							//1.Turn OFF 2. Torn ON

	S7::SetDIntAt(Buffer,38,palletizer.TheTimeOfTheOuterClawHalfOpen);
	S7::SetDIntAt(Buffer,42,palletizer.WipeDataOfTheChangeTileAndStorageBinFull);	//Clear the last grab
	S7::SetByteAt(Buffer,43,palletizer.NearALowSpeed);								//1.Near a low speed 0. Go through the pulse value
	S7::SetByteAt(Buffer,44,palletizer.TheNumberOfPackages);						//Exchange data bits

	S7::SetDIntAt(Buffer,46,palletizer.TheHighestSpeedOfXAxis);
	S7::SetDIntAt(Buffer,50,palletizer.DecelerationTimeOfXAxis);
	S7::SetDIntAt(Buffer,54,palletizer.DecelerationDistanceOfXAxis);
	S7::SetDIntAt(Buffer,58,palletizer.NoLoadTimeOfXAxis);
	S7::SetDIntAt(Buffer,62,palletizer.NoLoadDistanceOfXAxis);
	S7::SetDIntAt(Buffer,66,palletizer.ManualSpeedOfXAxis);

	S7::SetDIntAt(Buffer,70,palletizer.TheHighestSpeedOfYAxis);
	S7::SetDIntAt(Buffer,74,palletizer.DecelerationTimeOfYAxis);
	S7::SetDIntAt(Buffer,78,palletizer.DecelerationDistanceOfYAxis);
	S7::SetDIntAt(Buffer,82,palletizer.NoLoadTimeOfYAxis);
	S7::SetDIntAt(Buffer,86,palletizer.NoLoadDistanceOfYAxis);
	S7::SetDIntAt(Buffer,90,palletizer.ManualSpeedOfYAxis);

	S7::SetDIntAt(Buffer,94,palletizer.TheHighestSpeedOfZAxis);
	S7::SetDIntAt(Buffer,98,palletizer.DecelerationTimeOfZAxis);
	S7::SetDIntAt(Buffer,102,palletizer.DecelerationDistaceOfZAxis);
	S7::SetDIntAt(Buffer,114,palletizer.ManualSpeedOfZAxis);

	S7::SetDIntAt(Buffer,142,palletizer.TheAccuracyOfXAxis);
	S7::SetDIntAt(Buffer,146,palletizer.TheAccuracyOfYAxis);
	S7::SetDIntAt(Buffer,150,palletizer.TheAccuracyOfZAxis);
	S7::SetDIntAt(Buffer,154,palletizer.TheAccuracyOfWAxis);

	S7::SetByteAt(Buffer,194,palletizer.CommunicationExchange);




	//----------------------------


		int res = GetPLC18()->DBWrite(palletizer.GetPalletizerConfig().IODBWriting,
				palletizer.GetPalletizerConfig().WritingStartByte,
				palletizer.GetPalletizerConfig().WritingLength,
				Buffer);
	    return res;
}
