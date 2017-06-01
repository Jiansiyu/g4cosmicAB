/*
 * MuonTrackerSD.cc
 *
 *  Created on: May 23, 2017
 *      Author: Siyu Jian @ Physics Department of University of Virginia
 *      Email:  jiansiyu@gmail.com
 *      Go Wahoo!
 *
 */

#include "MuonTrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


#include <TH1F.h>   // root interface
#include <TCanvas.h>


extern G4double TotalEvents;
extern G4double DetectoredEvents;
extern TH1F *EffHisto;

MuonTrackerSD::MuonTrackerSD(const G4String& name,const G4String& hitsCollectionName):G4VSensitiveDetector(name)
{
	collectionName.insert(hitsCollectionName);
}

MuonTrackerSD::~MuonTrackerSD() {
	// TODO Auto-generated destructor stub
}

void MuonTrackerSD::Initialize(G4HCofThisEvent* hce)
{
	// create hits collections
	fHitsCollection = new MuonTrackerHitsCollection(SensitiveDetectorName,collectionName[0]);

	// add this collection in hce
	G4int hcID=G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	hce->AddHitsCollection(hcID,fHitsCollection);

}

G4bool MuonTrackerSD::ProcessHits(G4Step * aStep, G4TouchableHistory*)
{
	// energy deposit, which is not used in this code
	G4double edep=aStep->GetTotalEnergyDeposit();
	if(edep==0) return false;

	MuonTrackerHit * newHit=new MuonTrackerHit();
	//G4cout<<"Particle defination: "<<aStep->GetTrack()->GetParticleDefinition()->GetParticleName()<<G4endl;
	newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
	newHit->SetParticleName(aStep->GetTrack()->GetParticleDefinition()->GetParticleName());
	newHit->SetTotalEnergy(aStep->GetTrack()->GetTotalEnergy());
	newHit->SetDetectorName(aStep->GetTrack()->GetVolume()->GetName());
	newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
	newHit->SetEdep(edep);
	newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());

	fHitsCollection->insert(newHit);
	return true;
}

void MuonTrackerSD::EndOfEvent(G4HCofThisEvent*)
{
	TotalEvents++;
	G4int nofHits = fHitsCollection->entries();
	if(nofHits)DetectoredEvents++;
	float ratio=(DetectoredEvents/TotalEvents);
	G4cout<<std::setw(8)<<ratio*100<<"%\r"<<std::flush;
	EffHisto->Fill(TotalEvents,ratio);
	EffHisto->GetXaxis()->SetRange(0,TotalEvents);
	EffHisto->SetBins(TotalEvents,0,TotalEvents);

	if (verboseLevel > 1) {
		for (G4int i = 0; i < nofHits; i++) {
			(*fHitsCollection)[i]->Print();

		}
	}
}
