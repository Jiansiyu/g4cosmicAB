/*
 * MuonActionInitialization.cpp
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#include "MuonActionInitialization.hh"

#include "MuonPrimaryGeneratorAction.hh"
#include "MuonRunAction.hh"
#include "MuonEventAction.hh"


MuonActionInitialization::MuonActionInitialization() :G4VUserActionInitialization(){
	// TODO Auto-generated constructor stub

}

MuonActionInitialization::~MuonActionInitialization() {
	// TODO Auto-generated destructor stub
}

void MuonActionInitialization::BuildForMaster() const {
	SetUserAction(new MuonRunAction);
}

void MuonActionInitialization::Build() const
{
	SetUserAction(new MuonPrimaryGeneratorAction);
	SetUserAction(new MuonRunAction);
	SetUserAction(new MuonEventAction);
}
