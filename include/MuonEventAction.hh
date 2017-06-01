/*
 * MuonEventAction.hh
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONEVENTACTION_HH_
#define SOURCE_DIRECTORY__SRC_MUONEVENTACTION_HH_


#include "G4UserEventAction.hh"
#include "globals.hh"

class MuonEventAction :public G4UserEventAction{
public:
	MuonEventAction();
	virtual ~MuonEventAction();

	virtual void  BeginOfEventAction(const G4Event* );
	virtual void    EndOfEventAction(const G4Event* );
};

#endif /* SOURCE_DIRECTORY__SRC_MUONEVENTACTION_HH_ */
