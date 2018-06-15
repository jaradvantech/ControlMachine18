/*
 * connexionDisplayParser.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: andres
 */


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <connexion/connexionCucoParser.h>

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

void Process_Dummy(const rapidjson::Document& DOC_in, rapidjson::Writer<rapidjson::StringBuffer>* AnswerWriter)
{
	DOC_in.IsNull(); //removes a warning. I hate warnings.
	AnswerWriter->StartObject();			// Between StartObject()/EndObject(),

	AnswerWriter->Key("command_ID");		// output a key,
	AnswerWriter->String("dummy");			// follow by a value.

	AnswerWriter->Key("message");					// output a key,
	AnswerWriter->String("dummy");			// follow by a value.

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
        if(boost::equals(command_ID, "dummy")) Process_Dummy(DOC_in, &writer);
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
/*
void InitDisplayParser()
{
	SetFunctionToProcessMessages(&ProcessCommand);
}
*/
