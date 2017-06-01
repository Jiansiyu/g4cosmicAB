/*
 * MuonRunAction.hh
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONRUNACTION_HH_
#define SOURCE_DIRECTORY__SRC_MUONRUNACTION_HH_

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class MuonRunAction :public G4UserRunAction{
public:
	MuonRunAction();
	virtual ~MuonRunAction();

	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run* run);
};

#endif /* SOURCE_DIRECTORY__SRC_MUONRUNACTION_HH_ */
