/*
 * connexionDisplayParser.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: andres
 */


#include "connexion/connexionDisplayParser.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include "connexion/TCPServerLibrary.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "Palletizer.h"


void Process_PGSI(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.
	Palletizer *palletizer=GetPalletizer();
	AnswerWriter->StartObject();
	AnswerWriter->Key("command_ID");
	AnswerWriter->String("PGSI");
	AnswerWriter->Key("EmergencyStopOfElectricCabinet");
	AnswerWriter->Bool(palletizer->EmergencyStopOfElectricCabinet);
	AnswerWriter->Key("AutomaticSelectionSwitch");
	AnswerWriter->Bool(palletizer->AutomaticSelectionSwitch);
	AnswerWriter->Key("ManualSelectionSwitch");
	AnswerWriter->Bool(palletizer->ManualSelectionSwitch);
	AnswerWriter->Key("StartSwitch");
	AnswerWriter->Bool(palletizer->StartSwitch);
	AnswerWriter->Key("StopSwitch");
	AnswerWriter->Bool(palletizer->StopSwitch);
 	AnswerWriter->Key("ResetButton");
	AnswerWriter->Bool(palletizer->ResetButton);
 	AnswerWriter->Key("AlarmSilencing");
	AnswerWriter->Bool(palletizer->AlarmSilencing);
 	AnswerWriter->Key("xAxisForward");
	AnswerWriter->Bool(palletizer->xAxisForward);
 	AnswerWriter->Key("xAxisReversal");
	AnswerWriter->Bool(palletizer->xAxisReversal);
 	AnswerWriter->Key("yAxisForward");
	AnswerWriter->Bool(palletizer->yAxisForward);
 	AnswerWriter->Key("yAxisReversal");
	AnswerWriter->Bool(palletizer->yAxisReversal);
 	AnswerWriter->Key("zAxisForward");
	AnswerWriter->Bool(palletizer->zAxisForward);
 	AnswerWriter->Key("zAxisReversal");
	AnswerWriter->Bool(palletizer->zAxisReversal);
 	AnswerWriter->Key("wAxisForward");
	AnswerWriter->Bool(palletizer->wAxisForward);
 	AnswerWriter->Key("wAxisReversal");
	AnswerWriter->Bool(palletizer->wAxisReversal);
 	AnswerWriter->Key("PalletSelection1");
	AnswerWriter->Bool(palletizer->PalletSelection1);
 	AnswerWriter->Key("FrameEmergencyStop");
	AnswerWriter->Bool(palletizer->FrameEmergencyStop);
 	AnswerWriter->Key("FrameStartButton");
	AnswerWriter->Bool(palletizer->FrameStartButton);
 	AnswerWriter->Key("RegionProtectionGrating");
	AnswerWriter->Bool(palletizer->RegionProtectionGrating);
 	AnswerWriter->Key("PalletStorageBinPhotoelectricDetectionOfA");
	AnswerWriter->Bool(palletizer->PalletStorageBinPhotoelectricDetectionOfA);
 	AnswerWriter->Key("PalletStorageBinPhotoelectricDetectionOfB");
	AnswerWriter->Bool(palletizer->PalletStorageBinPhotoelectricDetectionOfB);
 	AnswerWriter->Key("PalletStorageBinPhotoelectricDetection");
	AnswerWriter->Bool(palletizer->PalletStorageBinPhotoelectricDetection);
 	AnswerWriter->Key("ZeroPositionProximitySwitchDetectionOfxAxis");
	AnswerWriter->Bool(palletizer->ZeroPositionProximitySwitchDetectionOfxAxis);
 	AnswerWriter->Key("ZeroPositionProximitySwitchDetectionOfyAxis");
	AnswerWriter->Bool(palletizer->ZeroPositionProximitySwitchDetectionOfyAxis);
 	AnswerWriter->Key("ZeroPositionProximitySwitchDetectionOfzAxis");
	AnswerWriter->Bool(palletizer->ZeroPositionProximitySwitchDetectionOfzAxis);
 	AnswerWriter->Key("ZeroPositionProximitySwitchDetectionOfwAxis");
	AnswerWriter->Bool(palletizer->ZeroPositionProximitySwitchDetectionOfwAxis);
 	AnswerWriter->Key("PalletSelection2");
	AnswerWriter->Bool(palletizer->PalletSelection2);
 	AnswerWriter->Key("ZeroPositionAuxiliaryProximitySwitchOfyAxis1");
	AnswerWriter->Bool(palletizer->ZeroPositionAuxiliaryProximitySwitchOfyAxis1);
 	AnswerWriter->Key("AirPressureDetectionSwitch");
	AnswerWriter->Bool(palletizer->AirPressureDetectionSwitch);
 	AnswerWriter->Key("LimitProximitySwitchDetectionOfwAxis");
	AnswerWriter->Bool(palletizer->LimitProximitySwitchDetectionOfwAxis);
 	AnswerWriter->Key("StopProximitySwitchDetectionOfzAxis");
	AnswerWriter->Bool(palletizer->StopProximitySwitchDetectionOfzAxis);
 	AnswerWriter->Key("LimitProximitySwitchDetectionOfzAxis");
	AnswerWriter->Bool(palletizer->LimitProximitySwitchDetectionOfzAxis);
 	AnswerWriter->Key("LeftHandFingerOpenDetection");
	AnswerWriter->Bool(palletizer->LeftHandFingerOpenDetection);
 	AnswerWriter->Key("LeftHandFingerClosedDetection");
	AnswerWriter->Bool(palletizer->LeftHandFingerClosedDetection);
 	AnswerWriter->Key("RightHandFingerOpenDetection");
	AnswerWriter->Bool(palletizer->RightHandFingerOpenDetection);
 	AnswerWriter->Key("RightHandFingerClosedDetection");
	AnswerWriter->Bool(palletizer->RightHandFingerClosedDetection);
 	AnswerWriter->Key("HalfTheMagneticDetectionSwitchOfFinger");
	AnswerWriter->Bool(palletizer->HalfTheMagneticDetectionSwitchOfFinger);
 	AnswerWriter->Key("ClosedTheMagneticDetectionSwitchOfFinger");
	AnswerWriter->Bool(palletizer->ClosedTheMagneticDetectionSwitchOfFinger);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfxAxis1");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfxAxis1);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfxAxis2");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfxAxis2);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfyAxis1");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfyAxis1);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfyAxis2");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfyAxis2);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfzAxis1");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfzAxis1);
 	AnswerWriter->Key("DetectionOfMechanicalLimitStrokeSwitchOfzAxis2");
	AnswerWriter->Bool(palletizer->DetectionOfMechanicalLimitStrokeSwitchOfzAxis2);
 	AnswerWriter->Key("AuxiliaryZeroPositionProximitySwitchOfxAxis");
	AnswerWriter->Bool(palletizer->AuxiliaryZeroPositionProximitySwitchOfxAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfxAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfxAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfyAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfyAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfzAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfzAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfwAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfwAxis);
 	AnswerWriter->Key("PalletSelection3");
	AnswerWriter->Bool(palletizer->PalletSelection3);
 	AnswerWriter->Key("ZeroPositionAuxiliaryProximitySwitchOfyAxis2");
	AnswerWriter->Bool(palletizer->ZeroPositionAuxiliaryProximitySwitchOfyAxis2);
 	AnswerWriter->Key("PawPositionSelection");
	AnswerWriter->Bool(palletizer->PawPositionSelection);
 	AnswerWriter->Key("SomeoneEnteredTheLoadingArea");
	AnswerWriter->Bool(palletizer->SomeoneEnteredTheLoadingArea);
 	AnswerWriter->Key("TheAlarmOfBrickStorehouseDidNotClose1");
	AnswerWriter->Bool(palletizer->TheAlarmOfBrickStorehouseDidNotClose1);
 	AnswerWriter->Key("TheAlarmOfBrickStorehouseDidNotClose2");
	AnswerWriter->Bool(palletizer->TheAlarmOfBrickStorehouseDidNotClose2);

	AnswerWriter->Key("PLCSystemState");
	AnswerWriter->Int(palletizer->PLCSystemState); 						//1.Run 2.Initialize 3.Manual 4.Emergency Stop
	AnswerWriter->Key("RealTimeValueOfxAxis");
	AnswerWriter->Int(palletizer->RealTimeValueOfxAxis);					//
	AnswerWriter->Key("RealTimeValueOfyAxis");
	AnswerWriter->Int(palletizer->RealTimeValueOfyAxis);
	AnswerWriter->Key("RealTimeValueOfzAxis");
	AnswerWriter->Int(palletizer->RealTimeValueOfzAxis);
	AnswerWriter->Key("RealTimeValueOfwAxis");
	AnswerWriter->Int(palletizer->RealTimeValueOfwAxis);
	AnswerWriter->Key("InnerFingerState");
	AnswerWriter->Int(palletizer->InnerFingerState);							//Clip state 1.Done 2.Wait
	AnswerWriter->Key("OuterClawState");
	AnswerWriter->Int(palletizer->OuterClawState);							//Outer ClawState 1.Done 2.Wait
	AnswerWriter->Key("LocationRollingOverState");
	AnswerWriter->Int(palletizer->LocationRollingOverState);				//Location Rolling-Over 1.Done 2.Action
	AnswerWriter->Key("StorageBinOfPalletState");
	AnswerWriter->Int(palletizer->StorageBinOfPalletState);				//1.Yes 2.No
	AnswerWriter->Key("OverTurnTable");
	AnswerWriter->Int(palletizer->OverTurnTable);							//1.Yes 2.No
	AnswerWriter->Key("LimitOptoelectronicOfZAxis");
	AnswerWriter->Int(palletizer->LimitOptoelectronicOfZAxis);				//1.Yes 2.No
	AnswerWriter->Key("PhotoelectricSensorOfPallet1");
	AnswerWriter->Int(palletizer->PhotoelectricSensorOfPallet1);			//1.Yes 2.No
	AnswerWriter->Key("PalletSignalOfA");
	AnswerWriter->Int(palletizer->PalletSignalOfA);						//1.Yes 2.No
	AnswerWriter->Key("OutputChooseA");
	AnswerWriter->Int(palletizer->OutputChooseA);							//1.Yes 2.No
	AnswerWriter->Key("PalletSignalOfB");
	AnswerWriter->Int(palletizer-> PalletSignalOfB);						//1.Yes 2.No
	AnswerWriter->Key("OutputChooseB");
	AnswerWriter->Int(palletizer->OutputChooseB);							//1.Yes 2.No
	AnswerWriter->Key("FlipPlatformLevel");
	AnswerWriter->Int(palletizer->FlipPlatformLevel);						//1.Yes 2.No
	AnswerWriter->Key("FlipPlatformVertical");
	AnswerWriter->Int(palletizer->FlipPlatformVertical);					//1.Yes 2.No
	AnswerWriter->Key("PhotoelectricSensorOfPallet2");
	AnswerWriter->Int(palletizer->PhotoelectricSensorOfPallet2);			//Photoelectric sensor of Pallet 2
	AnswerWriter->Key("PhotoelectricSensorOfPallet3");
	AnswerWriter->Int(palletizer->PhotoelectricSensorOfPallet3);			//Photoelectric sensor of Pallet 3
	AnswerWriter->Key("SupplementaryPalletAB");
	AnswerWriter->Int(palletizer->SupplementaryPalletAB);					//1.Yes 2.No
	AnswerWriter->Key("FingerState");
	AnswerWriter->Int(palletizer->FingerState);							//FingerOpening 1.All 2.No All
	AnswerWriter->Key("EquipmentStopState");
	AnswerWriter->Int(palletizer->EquipmentStopState);						//1.Yes 2.No
	AnswerWriter->Key("OpenThePhotoelectricSensorDetection");
	AnswerWriter->Int(palletizer->OpenThePhotoelectricSensorDetection);	//1.All 2.?  3.All and No All 4.All Off
	AnswerWriter->Key("CloseThePhotoelectricSensorDetection");
	AnswerWriter->Int(palletizer->CloseThePhotoelectricSensorDetection);	//1.All 2.?  3.All and No All 4.All Off
	AnswerWriter->Key("ReadyOfA");
	AnswerWriter->Int(palletizer->ReadyOfA);								//Reset Completion Of A Output
	AnswerWriter->Key("ReadyOfB");
	AnswerWriter->Int(palletizer->ReadyOfB);								//Reset Completion Of B Output
	AnswerWriter->Key("DoorRodBackA");
	AnswerWriter->Int(palletizer->DoorRodBackA);							//A Baffle Back
	AnswerWriter->Key("DoorRodBackB");
	AnswerWriter->Int(palletizer->DoorRodBackB);							//B Baffle Back
	AnswerWriter->Key("SequenceOfTheLastGrab");
	AnswerWriter->Int(palletizer->SequenceOfTheLastGrab);
	AnswerWriter->Key("NumberOfTheLastGrab");
	AnswerWriter->Int(palletizer->NumberOfTheLastGrab);
	AnswerWriter->Key("TheInstructionsOfTheChangePallet");
	AnswerWriter->Int(palletizer->TheInstructionsOfTheChangePallet);		//Replacement condition, rear line emptying 1. change
	AnswerWriter->Key("TheTileOf1200cm");
	AnswerWriter->Int(palletizer->TheTileOf1200cm);						//1. 1.2M 0.Other

	AnswerWriter->EndObject();
}
void Process_PING(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.
	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("PING");			// follow by a value.

	AnswerWriter->Key("message");					// output a key,
	AnswerWriter->String("PING RECEIVED");			// follow by a value.

	AnswerWriter->EndObject();
}

void Process_PWDA(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	//rapidjson::Value& s = DOC_in["casa"];
	//s.GetInt();
	Palletizer* palletizer = GetPalletizer();
	palletizer->SystemState=DOC_in["SystemState"].GetInt();

	palletizer->XAxisSetting = DOC_in["XAxisSetting"].GetInt();
	palletizer->YAxisSetting = DOC_in["YAxisSetting"].GetInt();
	palletizer->ZAxisSetting = DOC_in["ZAxisSetting"].GetInt();
	palletizer->WAxisSetting = DOC_in["WAxisSetting"].GetInt();

	palletizer->FingerMovement = DOC_in["FingerMovement"].GetInt();
	palletizer->OuterClawMovement = DOC_in["OuterClawMovement"].GetInt();
	palletizer->LocationRollingOver = DOC_in["LocationRollingOver"].GetInt();

	palletizer->TheSpeedOfXAxis = DOC_in["TheSpeedOfXAxis"].GetInt();
	palletizer->TheSpeedOfYAxis = DOC_in["TheSpeedOfYAxis"].GetInt();
	palletizer->TheSpeedOfZAxis = DOC_in["TheSpeedOfZAxis"].GetInt();
	palletizer->TheSpeedOfWAxis = DOC_in["TheSpeedOfWAxis"].GetInt();

	palletizer->OverRunAlarm = DOC_in["OverRunAlarm"].GetInt();
	palletizer->HostComputerControlTheSpeedOfXAxis =
			DOC_in["HostComputerControlTheSpeedOfXAxis"].GetInt();
	palletizer->AlarmAndStop = DOC_in["AlarmAndStop"].GetInt();

	palletizer->ManualControlOfScreen = DOC_in["ManualControlOfScreen"].GetInt();
	palletizer->ManualControlTheXAxisOfTheScreen =
			DOC_in["ManualControlTheXAxisOfTheScreen"].GetInt();
	palletizer->ManualControlTheYAxisOfTheScreen =
			DOC_in["ManualControlTheYAxisOfTheScreen"].GetInt();
	palletizer->ManualControlTheZAxisOfTheScreen =
			DOC_in["ManualControlTheZAxisOfTheScreen"].GetInt();
	palletizer->ManualControlTheWAxisOfTheScreen =
			DOC_in["ManualControlTheWAxisOfTheScreen"].GetInt();
	palletizer->ManualControlTheFingerOfTheScreen =
			DOC_in["ManualControlTheFingerOfTheScreen"].GetInt();
	palletizer->ManualControlTheOuterClawOfTheScreen =
			DOC_in["ManualControlTheOuterClawOfTheScreen"].GetInt();

	palletizer->StorageBinFullA = DOC_in["StorageBinFullA"].GetInt();
	palletizer->StorageBinFullB = DOC_in["StorageBinFullB"].GetInt();

	palletizer->TheTimeOfTheOuterClawHalfOpen = DOC_in["TheTimeOfTheOuterClawHalfOpen"].GetInt();
	palletizer->WipeDataOfTheChangeTileAndStorageBinFull =
			DOC_in["WipeDataOfTheChangeTileAndStorageBinFull"].GetInt();
	palletizer->NearALowSpeed = DOC_in["NearALowSpeed"].GetInt();
	palletizer->TheNumberOfPackages = DOC_in["TheNumberOfPackages"].GetInt();

	palletizer->TheHighestSpeedOfXAxis = DOC_in["TheHighestSpeedOfXAxis"].GetInt();
	palletizer->DecelerationTimeOfXAxis = DOC_in["DecelerationTimeOfXAxis"].GetInt();
	palletizer->DecelerationDistanceOfXAxis = DOC_in["DecelerationDistanceOfXAxis"].GetInt();
	palletizer->NoLoadTimeOfXAxis = DOC_in["NoLoadTimeOfXAxis"].GetInt();
	palletizer->NoLoadDistanceOfXAxis = DOC_in["NoLoadDistanceOfXAxis"].GetInt();
	palletizer->ManualSpeedOfXAxis = DOC_in["ManualSpeedOfXAxis"].GetInt();

	palletizer->TheHighestSpeedOfYAxis = DOC_in["TheHighestSpeedOfYAxis"].GetInt();
	palletizer->DecelerationTimeOfYAxis = DOC_in["DecelerationTimeOfYAxis"].GetInt();
	palletizer->DecelerationDistanceOfYAxis = DOC_in["DecelerationDistanceOfYAxis"].GetInt();
	palletizer->NoLoadTimeOfYAxis = DOC_in["NoLoadTimeOfYAxis"].GetInt();
	palletizer->NoLoadDistanceOfYAxis = DOC_in["NoLoadDistanceOfYAxis"].GetInt();
	palletizer->ManualSpeedOfYAxis = DOC_in["ManualSpeedOfYAxis"].GetInt();

	palletizer->TheHighestSpeedOfZAxis = DOC_in["TheHighestSpeedOfZAxis"].GetInt();
	palletizer->DecelerationTimeOfZAxis = DOC_in["DecelerationTimeOfZAxis"].GetInt();
	palletizer->DecelerationDistaceOfZAxis = DOC_in["DecelerationDistaceOfZAxis"].GetInt();
	palletizer->ManualSpeedOfZAxis = DOC_in["ManualSpeedOfZAxis"].GetInt();

	palletizer->TheAccuracyOfXAxis = DOC_in["TheAccuracyOfXAxis"].GetInt();
	palletizer->TheAccuracyOfYAxis = DOC_in["TheAccuracyOfYAxis"].GetInt();
	palletizer->TheAccuracyOfZAxis = DOC_in["TheAccuracyOfZAxis"].GetInt();
	palletizer->TheAccuracyOfWAxis = DOC_in["TheAccuracyOfWAxis"].GetInt();

	palletizer->CommunicationExchange = DOC_in["CommunicationExchange"].GetInt();

	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("PWDA");			// follow by a value.

	AnswerWriter->Key("message");					// output a key,
	AnswerWriter->String("PWDA RECEIVED");			// follow by a value.

	AnswerWriter->EndObject();
}


std::string ProcessCommand(std::string Message)
{
	//one document for input
    rapidjson::Document DOC_in;
    rapidjson::StringBuffer Answer_JSON;
    rapidjson::Writer<rapidjson::StringBuffer> writer(Answer_JSON);
    DOC_in.Parse(Message.c_str());
    // 2. Modify it by DOM.

    rapidjson::Value& command_ID = DOC_in["command_ID"]; //An error here is *probably* because command_ID is missing

    try //Yup, it's dirty. But we don't want to risk that the machine stops working by a corrupt packet
    {
        if(boost::equals(command_ID.GetString(), "PGSI")) Process_PGSI(DOC_in, &writer);
        else if(boost::equals(command_ID.GetString(), "PWDA")) Process_PWDA(DOC_in, &writer);
        else if(boost::equals(command_ID.GetString(), "PING")) Process_PING(DOC_in, &writer);
        else std::cout << "Unknown command: " << command_ID.GetString() << std::endl;
    }
    catch( ... )
    {
    	std::cout << command_ID.GetString() << " Bad Syntax" << std::endl;
    }
    // 3. Stringify the DOM output

    return ((std::string)Answer_JSON.GetString()) + "\n";
}

void InitDisplayParser()
{
	SetFunctionToProcessMessages(&ProcessCommand);
}

