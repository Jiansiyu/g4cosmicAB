/*
 * MuonTrackerSD.hh
 *
 *  Created on: May 23, 2017
 *      Author: newdriver
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONTRACKERSD_HH_
#define SOURCE_DIRECTORY__SRC_MUONTRACKERSD_HH_

#include "G4VSensitiveDetector.hh"
#include "MuonTrackerHit.hh"

#include <vector>


class G4Step;
class G4HCofThisEvent;

// tracker sensitive detector class

class MuonTrackerSD : public G4VSensitiveDetector
{
public:
	MuonTrackerSD(const G4String& name,
            const G4String& hitsCollectionName);
	virtual ~MuonTrackerSD();

	// base class methods
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

private:
	MuonTrackerHitsCollection* fHitsCollection;

};

#endif /* SOURCE_DIRECTORY__SRC_MUONTRACKERSD_HH_ */
