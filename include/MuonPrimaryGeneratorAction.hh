/*
 * MuonPrimaryGenerator.hh
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONPRIMARYGENERATOR_HH_
#define SOURCE_DIRECTORY__SRC_MUONPRIMARYGENERATOR_HH_

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class MuonPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	MuonPrimaryGeneratorAction();
	virtual ~MuonPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event* );

	G4ParticleGun* GetParticleGun() {return fParticleGun;}

	// Set methods
	void SetRandomFlag(G4bool );

private:
	G4ParticleGun*          fParticleGun; // G4 particle gun
};

#endif /* SOURCE_DIRECTORY__SRC_MUONPRIMARYGENERATOR_HH_ */
