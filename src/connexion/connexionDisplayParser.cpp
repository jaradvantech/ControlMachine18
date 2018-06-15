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

bool FindAndAddTo(const rapidjson::Document& DOC, std::string Key, int* Variable)
{
	static rapidjson::Value::ConstMemberIterator itr;
	itr = DOC.FindMember(Key.c_str());
	if(itr !=DOC.MemberEnd()) {
		*Variable=itr->value.GetInt();
		return true;
	}
	else return false;
}

bool FindAndAddTo(const rapidjson::Document& DOC, std::string Key, std::string* Variable)
{
	static rapidjson::Value::ConstMemberIterator itr;
	itr = DOC.FindMember(Key.c_str());
	if(itr !=DOC.MemberEnd()) {
		*Variable=itr->value.GetString();
		return true;
	}
	else return false;
}

bool FindAndAddTo(const rapidjson::Document& DOC, std::string Key, bool* Variable)
{
	static rapidjson::Value::ConstMemberIterator itr;
	itr = DOC.FindMember(Key.c_str());
	if(itr !=DOC.MemberEnd()) {
		*Variable=itr->value.GetBool();
		return true;
	}
	else return false;
}

//-------------------------------------------------------------------------------//

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

void Process_PWDA(const std::string& CMD_from_tablet, const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	Palletizer* palletizer = GetPalletizer();


			FindAndAddTo(DOC_in,"SystemState",&palletizer->SystemState);

			FindAndAddTo(DOC_in, "XAxisSetting", &palletizer->XAxisSetting);
			FindAndAddTo(DOC_in, "YAxisSetting", &palletizer->YAxisSetting);
			FindAndAddTo(DOC_in, "ZAxisSetting", &palletizer->ZAxisSetting);
			FindAndAddTo(DOC_in, "WAxisSetting", &palletizer->WAxisSetting);

			FindAndAddTo(DOC_in, "FingerMovement", &palletizer->FingerMovement);
			FindAndAddTo(DOC_in, "OuterClawMovement", &palletizer->OuterClawMovement);
			FindAndAddTo(DOC_in, "LocationRollingOver", &palletizer->LocationRollingOver);

			FindAndAddTo(DOC_in, "TheSpeedOfXAxis", &palletizer->TheSpeedOfXAxis);
			FindAndAddTo(DOC_in, "TheSpeedOfYAxis", &palletizer->TheSpeedOfYAxis);
			FindAndAddTo(DOC_in, "TheSpeedOfZAxis", &palletizer->TheSpeedOfZAxis);
			FindAndAddTo(DOC_in, "TheSpeedOfWAxis", &palletizer->TheSpeedOfWAxis);

			FindAndAddTo(DOC_in, "OverRunAlarm", &palletizer->OverRunAlarm);
			FindAndAddTo(DOC_in, "HostComputerControlTheSpeedOfXAxis",
					&palletizer->HostComputerControlTheSpeedOfXAxis);
			FindAndAddTo(DOC_in, "AlarmAndStop", &palletizer->AlarmAndStop);

			FindAndAddTo(DOC_in, "ManualControlOfScreen", &palletizer->ManualControlOfScreen);
			FindAndAddTo(DOC_in, "ManualControlTheXAxisOfTheScreen",
					&palletizer->ManualControlTheXAxisOfTheScreen);
			FindAndAddTo(DOC_in, "ManualControlTheYAxisOfTheScreen",
					&palletizer->ManualControlTheYAxisOfTheScreen);
			FindAndAddTo(DOC_in, "ManualControlTheZAxisOfTheScreen",
					&palletizer->ManualControlTheZAxisOfTheScreen);
			FindAndAddTo(DOC_in, "ManualControlTheWAxisOfTheScreen",
					&palletizer->ManualControlTheWAxisOfTheScreen);
			FindAndAddTo(DOC_in, "ManualControlTheFingerOfTheScreen",
					&palletizer->ManualControlTheFingerOfTheScreen);
			FindAndAddTo(DOC_in, "ManualControlTheOuterClawOfTheScreen",
					&palletizer->ManualControlTheOuterClawOfTheScreen);

			FindAndAddTo(DOC_in, "StorageBinFullA", &palletizer->StorageBinFullA);
			FindAndAddTo(DOC_in, "StorageBinFullB", &palletizer->StorageBinFullB);

			FindAndAddTo(DOC_in, "TheTimeOfTheOuterClawHalfOpen",
					&palletizer->TheTimeOfTheOuterClawHalfOpen);
			FindAndAddTo(DOC_in, "WipeDataOfTheChangeTileAndStorageBinFull",
					&palletizer->WipeDataOfTheChangeTileAndStorageBinFull);
			FindAndAddTo(DOC_in, "NearALowSpeed", &palletizer->NearALowSpeed);
			FindAndAddTo(DOC_in, "TheNumberOfPackages", &palletizer->TheNumberOfPackages);

			FindAndAddTo(DOC_in, "TheHighestSpeedOfXAxis", &palletizer->TheHighestSpeedOfXAxis);
			FindAndAddTo(DOC_in, "DecelerationTimeOfXAxis", &palletizer->DecelerationTimeOfXAxis);
			FindAndAddTo(DOC_in, "DecelerationDistanceOfXAxis",
					&palletizer->DecelerationDistanceOfXAxis);
			FindAndAddTo(DOC_in, "NoLoadTimeOfXAxis", &palletizer->NoLoadTimeOfXAxis);
			FindAndAddTo(DOC_in, "NoLoadDistanceOfXAxis", &palletizer->NoLoadDistanceOfXAxis);
			FindAndAddTo(DOC_in, "ManualSpeedOfXAxis", &palletizer->ManualSpeedOfXAxis);

			FindAndAddTo(DOC_in, "TheHighestSpeedOfYAxis", &palletizer->TheHighestSpeedOfYAxis);
			FindAndAddTo(DOC_in, "DecelerationTimeOfYAxis", &palletizer->DecelerationTimeOfYAxis);
			FindAndAddTo(DOC_in, "DecelerationDistanceOfYAxis",
					&palletizer->DecelerationDistanceOfYAxis);
			FindAndAddTo(DOC_in, "NoLoadTimeOfYAxis", &palletizer->NoLoadTimeOfYAxis);
			FindAndAddTo(DOC_in, "NoLoadDistanceOfYAxis", &palletizer->NoLoadDistanceOfYAxis);
			FindAndAddTo(DOC_in, "ManualSpeedOfYAxis", &palletizer->ManualSpeedOfYAxis);

			FindAndAddTo(DOC_in, "TheHighestSpeedOfZAxis", &palletizer->TheHighestSpeedOfZAxis);
			FindAndAddTo(DOC_in, "DecelerationTimeOfZAxis", &palletizer->DecelerationTimeOfZAxis);
			FindAndAddTo(DOC_in, "DecelerationDistaceOfZAxis",
					&palletizer->DecelerationDistaceOfZAxis);
			FindAndAddTo(DOC_in, "ManualSpeedOfZAxis", &palletizer->ManualSpeedOfZAxis);

			FindAndAddTo(DOC_in, "TheHighestSpeedOfWAxis", &palletizer->TheHighestSpeedOfWAxis);
			FindAndAddTo(DOC_in, "DecelerationTimeOfWAxis", &palletizer->DecelerationTimeOfWAxis);
			FindAndAddTo(DOC_in, "DecelerationDistaceOfWAxis",
					&palletizer->DecelerationDistanceOfWAxis);
			FindAndAddTo(DOC_in, "ManualSpeedOfWAxis", &palletizer->ManualSpeedOfWAxis);

			FindAndAddTo(DOC_in, "TheAccuracyOfXAxis", &palletizer->TheAccuracyOfXAxis);
			FindAndAddTo(DOC_in, "TheAccuracyOfYAxis", &palletizer->TheAccuracyOfYAxis);
			FindAndAddTo(DOC_in, "TheAccuracyOfZAxis", &palletizer->TheAccuracyOfZAxis);
			FindAndAddTo(DOC_in, "TheAccuracyOfWAxis", &palletizer->TheAccuracyOfWAxis);

			FindAndAddTo(DOC_in, "CommunicationExchange", &palletizer->CommunicationExchange);

	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("PWDA");			// follow by a value.

	AnswerWriter->Key("message");					// output a key,
	AnswerWriter->String("PWDA RECEIVED");			// follow by a value.

	AnswerWriter->EndObject();
}

void Process_CHAL(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.
	Palletizer* palletizer = GetPalletizer();

	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("CHAL");			// follow by a value.

	/*Emergency Alarms*/
 	AnswerWriter->Key("EmergencyStopOfElectricCabinet");
	AnswerWriter->Bool(palletizer->EmergencyStopOfElectricCabinet);
 	AnswerWriter->Key("FrameEmergencyStop");
	AnswerWriter->Bool(palletizer->FrameEmergencyStop);

	/*Mechanical Limits*/
 	AnswerWriter->Key("LimitProximitySwitchDetectionOfwAxis");
	AnswerWriter->Bool(palletizer->LimitProximitySwitchDetectionOfwAxis);
 	AnswerWriter->Key("LimitProximitySwitchDetectionOfzAxis");
	AnswerWriter->Bool(palletizer->LimitProximitySwitchDetectionOfzAxis);
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
	AnswerWriter->Key("LimitOptoelectronicOfZAxis");
	AnswerWriter->Int(palletizer->LimitOptoelectronicOfZAxis);

	/*Miscellaneous Alarms*/
 	AnswerWriter->Key("FrequencyConverterAlarmOfxAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfxAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfyAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfyAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfzAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfzAxis);
 	AnswerWriter->Key("FrequencyConverterAlarmOfwAxis");
	AnswerWriter->Bool(palletizer->FrequencyConverterAlarmOfwAxis);
 	AnswerWriter->Key("TheAlarmOfBrickStorehouseDidNotClose1");
	AnswerWriter->Bool(palletizer->TheAlarmOfBrickStorehouseDidNotClose1);
 	AnswerWriter->Key("TheAlarmOfBrickStorehouseDidNotClose2");
	AnswerWriter->Bool(palletizer->TheAlarmOfBrickStorehouseDidNotClose2);

	AnswerWriter->EndObject();
}

void Process_RPRV(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.
	Palletizer* palletizer = GetPalletizer();

	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("RPRV");			// follow by a value.

 	AnswerWriter->Key("RealTimeValueOfxAxis");
	AnswerWriter->Bool(palletizer->RealTimeValueOfxAxis);
 	AnswerWriter->Key("RealTimeValueOfyAxis");
	AnswerWriter->Bool(palletizer->RealTimeValueOfyAxis);
 	AnswerWriter->Key("RealTimeValueOfzAxis");
	AnswerWriter->Bool(palletizer->RealTimeValueOfzAxis);
 	AnswerWriter->Key("RealTimeValueOfwAxis");
	AnswerWriter->Bool(palletizer->RealTimeValueOfwAxis);

	/*Ya veremos como hacemos esto*/
	int currentStep=0;
	int totalSteps=0;

 	AnswerWriter->Key("currentStep");
	AnswerWriter->Int(currentStep);
 	AnswerWriter->Key("totalSteps");
	AnswerWriter->Int(totalSteps);
}

void Process_MANU(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.

	Palletizer* palletizer = GetPalletizer();
	FindAndAddTo(DOC_in,"ManualControlOfScreen",&palletizer->ManualControlOfScreen);
	FindAndAddTo(DOC_in,"ManualControlTheXAxisOfTheScreen",&palletizer->ManualControlTheXAxisOfTheScreen);
	FindAndAddTo(DOC_in,"ManualControlTheYAxisOfTheScreen",&palletizer->ManualControlTheYAxisOfTheScreen);
	FindAndAddTo(DOC_in,"ManualControlTheZAxisOfTheScreen",&palletizer->ManualControlTheZAxisOfTheScreen);
	FindAndAddTo(DOC_in,"ManualControlTheWAxisOfTheScreen",&palletizer->ManualControlTheWAxisOfTheScreen);
	FindAndAddTo(DOC_in,"ManualControlTheFingerOfTheScreen",&palletizer->ManualControlTheFingerOfTheScreen);
	FindAndAddTo(DOC_in,"ManualControlTheOuterClawOfTheScreen",&palletizer->ManualControlTheOuterClawOfTheScreen);

	FindAndAddTo(DOC_in,"ManualSpeedOfXAxis",&palletizer->ManualSpeedOfXAxis);
	FindAndAddTo(DOC_in,"ManualSpeedOfXAxis",&palletizer->ManualSpeedOfYAxis);
	FindAndAddTo(DOC_in,"ManualSpeedOfXAxis",&palletizer->ManualSpeedOfZAxis);
	FindAndAddTo(DOC_in,"ManualSpeedOfXAxis",&palletizer->ManualSpeedOfWAxis);

	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("MANU");			// follow by a value.

	AnswerWriter->Key("message");					// output a key,
	AnswerWriter->String("MANU RECEIVED");			// follow by a value.

	AnswerWriter->EndObject();
}


//-------------------------------------------------------------------------------//

std::string ProcessCommand(std::string Message)
{
	//one document for input
    rapidjson::Document DOC_in;
    rapidjson::StringBuffer Answer_JSON;
    rapidjson::Writer<rapidjson::StringBuffer> writer(Answer_JSON);
    rapidjson::ParseResult result;
    result = DOC_in.Parse(Message.c_str());
    if(!result)
    {
    	 std::cout << "Message is not JSON or is corrupt: " << std::endl;
    	 return "ERROR_MESSAGECORRUPT\n";
    }

    // 2. Modify it by DOM.
    std::string command_ID;
    bool command_ID_check = FindAndAddTo(DOC_in, "command_ID", &command_ID);



    //rapidjson::Value& command_ID = DOC_in["command_ID"]; //An error here is *probably* because command_ID is missing


    if(command_ID_check)
    //try //Yup, it's dirty. But we don't want to risk that the machine stops working by a corrupt packet
    {
        if(boost::equals(command_ID, "PWDA")) Process_PWDA(Message, DOC_in, &writer);
        else if(boost::equals(command_ID, "PGSI")) Process_PGSI(DOC_in, &writer);
        else if(boost::equals(command_ID, "PING")) Process_PING(DOC_in, &writer);
        else if(boost::equals(command_ID, "CHAL")) Process_CHAL(DOC_in, &writer);
        else if(boost::equals(command_ID, "RPRV")) Process_RPRV(DOC_in, &writer);
        else if(boost::equals(command_ID, "MANU"))  Process_MANU(DOC_in, &writer);
        else std::cout << "Unknown command: " << command_ID << std::endl;
    }
    //catch( ... )
    else
    {
    	return "command_ID not found\n";
    	std::cout << command_ID << " Bad Syntax" << std::endl;
    }
    // 3. Stringify the DOM output

    return ((std::string)Answer_JSON.GetString()) + "\n";
}

void InitDisplayParser()
{
	SetFunctionToProcessMessages(&ProcessCommand);
}

