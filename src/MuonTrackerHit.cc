/*
 * MuonTrackerHit.cc
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#include "MuonTrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>


G4ThreadLocal G4Allocator<MuonTrackerHit>* MuonTrackerHitAllocator=0;

MuonTrackerHit::MuonTrackerHit() :G4VHit(),
		fTrackID(-1),
		fChamberNb(-1),
		fEdep(0.),
		fPos(G4ThreeVector())
{
	// TODO Auto-generated constructor stub
}

MuonTrackerHit::MuonTrackerHit(const MuonTrackerHit& right): G4VHit(){

	fTrackID   = right.fTrackID;
	fChamberNb = right.fChamberNb;
	fEdep	   = right.fEdep;
	fPos	   = right.fPos;
}

MuonTrackerHit::~MuonTrackerHit() {
	// TODO Auto-generated destructor stub
};

const MuonTrackerHit& MuonTrackerHit::operator =(const MuonTrackerHit & right){
	fTrackID   = right.fTrackID;
	fChamberNb = right.fChamberNb;
	fEdep	   = right.fEdep;
	fPos	   = right.fPos;
	return *this;
}

G4int MuonTrackerHit::operator ==(const MuonTrackerHit& right) const{
	return (this==&right)?1:0;
}

void MuonTrackerHit::Draw(){
	G4VVisManager * pVVisManager = G4VVisManager::GetConcreteInstance();
	if(pVVisManager)
	  {
	    G4Circle circle(fPos);
	    circle.SetScreenSize(4.);
	    circle.SetFillStyle(G4Circle::filled);
	    G4Colour colour(1.,0.,0.);
	    G4VisAttributes attribs(colour);
	    circle.SetVisAttributes(attribs);
	    pVVisManager->Draw(circle);
	  }
}

void MuonTrackerHit::Print() {
	G4cout
	     << "  trackID: " << fTrackID << " chamberNb: " << fChamberNb
	     << " Edep: "<<G4endl
	     << std::setw(7) << G4BestUnit(fEdep,"Energy")<<G4endl
	     << " Position: "
	     << std::setw(7) << G4BestUnit( fPos,"Length")<<G4endl
		 <<"ParticleName : "<<fParticleName<<G4endl
		 <<"Total E : "<< fTotalEnergy<<G4BestUnit(fTotalEnergy,"Energy")<<G4endl
		 <<"DetectorName: "<<fDetectorName<<G4endl
	     << G4endl;
}
