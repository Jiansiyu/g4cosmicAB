/*
 * MuonTrackerHit.hh
 *
 *  Created on: May 25, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONTRACKERHIT_HH_
#define SOURCE_DIRECTORY__SRC_MUONTRACKERHIT_HH_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Tracker hit class


class MuonTrackerHit : public G4VHit
{
public:
	MuonTrackerHit();
	MuonTrackerHit(const MuonTrackerHit&);     // ??
	virtual ~MuonTrackerHit();

	// operators
	const MuonTrackerHit& operator = (const MuonTrackerHit&);
	G4int operator == (const MuonTrackerHit &) const;
	inline void* operator new(size_t);
	inline void operator delete(void*);

	/// methods from base class
	virtual void Draw();
	virtual void Print();

	// set methods
	void SetTrackID  (G4int track) {fTrackID   = track;};
	void SetChamberNb(G4int chamb) {fChamberNb = chamb;};
	void SetEdep	 (G4double de) {fEdep 	   = de;};
	void SetPos		 (G4ThreeVector xyz) {fPos=xyz;};
	void SetParticleName(G4String particlename){fParticleName=particlename;};
	void SetTotalEnergy(G4double energy) {fTotalEnergy=energy;};
	void SetDetectorName(G4String detectorname) {fDetectorName=detectorname;};
	// get methods
	G4int GetTrackID  () const {return fTrackID;};
	G4int GetChamberNb() const {return fChamberNb;};
	G4double GetEdep()   const {return fEdep;};
	G4ThreeVector GetPos() const {return fPos;};
	G4String GetParticleName() const {return fParticleName;};
	G4double GetTotalEnergy() const {return fTotalEnergy;};
	G4String GetDetectorName() const {return fDetectorName;};
private:
	G4int 	 		fTrackID;
	G4int 	 		fChamberNb;
	G4double 		fEdep;
	G4ThreeVector	fPos;
	G4String		fParticleName;
	G4double        fTotalEnergy;
	G4String		fDetectorName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<MuonTrackerHit> MuonTrackerHitsCollection;
extern G4ThreadLocal G4Allocator<MuonTrackerHit>* MuonTrackerHitAllocator;

inline void* MuonTrackerHit::operator new(size_t) {
	if(!MuonTrackerHitAllocator)
		MuonTrackerHitAllocator = new G4Allocator<MuonTrackerHit>;
	return (void *) MuonTrackerHitAllocator->MallocSingle();
}

inline void MuonTrackerHit::operator delete(void *hit)
{
	MuonTrackerHitAllocator->FreeSingle((MuonTrackerHit*) hit);
}

#endif /* SOURCE_DIRECTORY__SRC_MUONTRACKERHIT_HH_ */
