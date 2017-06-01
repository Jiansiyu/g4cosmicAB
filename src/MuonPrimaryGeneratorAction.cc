/*
 * MuonPrimaryGenerator.cc
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#include "MuonPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "MuonDetectorConstruction.hh"
// random number generator
#include "Randomize.hh"

MuonPrimaryGeneratorAction::MuonPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
	// TODO Auto-generated constructor stub

	  G4int nofParticles = 1;
	  fParticleGun = new G4ParticleGun(nofParticles);
	  G4cout <<"TOTAL NUMBER OF Events"<<nofParticles<<G4endl;
	  // default particle kinematic

	  G4ParticleDefinition* particleDefinition
	    = G4ParticleTable::GetParticleTable()->FindParticle("mu+");

	  fParticleGun->SetParticleDefinition(particleDefinition);
	  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	  fParticleGun->SetParticleEnergy(3.0*GeV);

}

MuonPrimaryGeneratorAction::~MuonPrimaryGeneratorAction() {
	// TODO Auto-generated destructor stub
	delete fParticleGun;
}

void MuonPrimaryGeneratorAction::GeneratePrimaries(G4Event * anEvent) {
	  // This function is called at the begining of event

	  // In order to avoid dependence of PrimaryGeneratorAction
	  // on DetectorConstruction class we get world volume
	  // from G4LogicalVolumeStore.

	  G4double worldZHalfLength = 0;
	  G4LogicalVolume* worldLV
	    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
	  G4Box* worldBox = NULL;
	  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
	  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
	  else  {
	    G4cerr << "World volume of box not found." << G4endl;
	    G4cerr << "Perhaps you have changed geometry." << G4endl;
	    G4cerr << "The gun will be place in the center." << G4endl;
	  }

	  // generate random distributed  Muon that used for the cosmic rawy imaging
	  // set the initial position of the muons
	  G4double position_x=G4UniformRand()*worldZHalfLength*2-worldZHalfLength;
	  G4double position_y=G4UniformRand()*worldZHalfLength*2-worldZHalfLength;


	  G4double direction_x= G4UniformRand()*worldZHalfLength*2-worldZHalfLength-position_x;
	  G4double direction_y= G4UniformRand()*worldZHalfLength*2-worldZHalfLength-position_y;
	  G4double direction_z= worldZHalfLength*2;
	  G4ThreeVector direction(direction_x,direction_y,direction_z);//direction_x,direction_y,direction_z);

	  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	  // used for muon attenuation simulation
	  //
	  // muon start from the center of the target
	  fParticleGun->SetParticlePosition(G4ThreeVector());

	  // donot need directions
	  //fParticleGun->SetParticleMomentumDirection(direction);

	  fParticleGun->GeneratePrimaryVertex(anEvent);

}
