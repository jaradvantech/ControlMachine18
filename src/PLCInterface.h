/*
 * PLCInterface.h
 *
 *  Created on: Mar 30, 2018
 *      Author: andres
 */

#ifndef PLCINTERFACE_H_
#define PLCINTERFACE_H_

#include "connexion/connexionPLC.h"
#include "connexion/connexionPLCdatahandler.h"




void * PLCAdquisitionLoop(void *Arg);
TS7Client* GetPLC18();


#endif /* PLCINTERFACE_H_ */
