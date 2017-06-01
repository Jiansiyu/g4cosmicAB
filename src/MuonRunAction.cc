/*
 * MuonRunAction.cc
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#include "MuonRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

MuonRunAction::MuonRunAction():G4UserRunAction() {
	// TODO Auto-generated constructor stub
	G4RunManager::GetRunManager()->SetPrintProgress(1000);
}

MuonRunAction::~MuonRunAction() {
	// TODO Auto-generated destructor stub
}

void MuonRunAction::BeginOfRunAction(const G4Run *){

	G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void MuonRunAction::EndOfRunAction(const G4Run *) {

}
