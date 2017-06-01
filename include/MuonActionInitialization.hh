/*
 * MuonActionInitialization.h
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONACTIONINITIALIZATION_HH_
#define SOURCE_DIRECTORY__SRC_MUONACTIONINITIALIZATION_HH_

#include "G4VUserActionInitialization.hh"

class MuonDetectorConstruction;

class MuonActionInitialization : public G4VUserActionInitialization {
public:
	MuonActionInitialization();
	virtual ~MuonActionInitialization();

	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif /* SOURCE_DIRECTORY__SRC_MUONACTIONINITIALIZATION_HH_ */
