/*
 * MuonDetectorConstruction.hh
 *
 *  Created on: May 23, 2017
 *      Author: Siyu Jian @ Physics Department of University of Virginia
 *      Email:  jiansiyu@gmail.com
 *      Go Wahoo
 */

#ifndef SOURCE_DIRECTORY__SRC_MUONDETECTORCONSTRUCTION_HH_
#define SOURCE_DIRECTORY__SRC_MUONDETECTORCONSTRUCTION_HH_


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"     						// what is this used for
#include "G4SystemOfUnits.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class MuonDetectorMessenger;

class MuonDetectorConstruction : public G4VUserDetectorConstruction {
public:
	MuonDetectorConstruction();
	virtual ~MuonDetectorConstruction();

public:
	virtual G4VPhysicalVolume * Construct();
	virtual void ConstructSDandField();

	//construct the volume
	void SetTargetMatrials(G4String);
	void SetChamberMaterial(G4String);
	void SetMaxStep(G4double);
	void SetCheckOverlaps(G4bool);

private:
	//construction of the detetcor and the target

	void DefineMaterials();
	G4VPhysicalVolume* DefineVolumes();

	// elements used for construction the detector and the target
	G4LogicalVolume*   fLogicTarget;
	G4VPhysicalVolume* fPhysicTarget;

	G4LogicalVolume* fLogicChambersV;    //  Horizontal chambers
	G4VPhysicalVolume* fChamberPhys_VT1;   // vertical chamber top layar No.1 chamber
	//G4VPhysicalVolume* fChamberPhys_VT2;
	//G4VPhysicalVolume* fChamberPhys_VB1;
	//G4VPhysicalVolume* fChamberPhys_VB2;

	//Detector Materials
	G4Material* fChamberMaterials_Cu;
	G4Material* fChamberMaterials_Myler;    // polymide material which is the iselator materials in the GEM detector

	// target Materials
	G4Material* fIntermediumMaterials_Air;  //
	G4Material* fMaterials_3CO2_7Ar;        //

	G4Material* fTargetMaterials_Pb;
	G4Material* fTargetMaterials_Al;
	G4Material* fTargetMaterials_Bi;
	G4Material* fTargetMaterials_Fe;
	G4Material* fTargetMaterials_Cu;
	G4Material* fTargetMaterials_Pu;
	G4Material* fTargetMaterials_U;        //Uranium



private:
	// GEM detector Physical Dimension Construction

	// Size of the detector
	G4double lDetector_Width  =50.0*cm;
	G4double lDetector_Length =60.0*cm;
	G4double lDetector_Thickness=2.0*cm;

	// detector Spacial layout characters
	G4double lDetector_space  =10.0*cm;
	G4double lDetector_TargetSpace=30.0*cm;



	//+++++++++++++++++++++++++++++++++++
	// used for the muon attenuatiuon simulation
	// set the target size

	G4double SizeofTarget=200.0 *cm;
	G4double ThicknessofDtector=1.0 *cm;

	//+++++++++++++++++++++++++++++++++++



private:
	G4UserLimits* fStepLimit;            // pointer to user step limits
	MuonDetectorMessenger* fMessenger;   // messenger

	static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
	                                         // magnetic field messenger
	G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps

};

#endif /* SOURCE_DIRECTORY__SRC_MUONDETECTORCONSTRUCTION_HH_ */
