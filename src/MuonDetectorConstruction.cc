/*
 * MuonDetectorConstruction.cc
 *
 *  Created on: May 23, 2017
 *      Author: Siyu Jian @ Physics Department of University of Virginia
 *      Email:  jiansiyu@gmail.com
 *      Go Wahoo!
 *
 */

// user defined functionss
#include "MuonDetectorConstruction.hh"
#include "MuonDetectorMessenger.hh"
#include "MuonTrackerSD.hh"

// used for the construnction of the chamber and the target
#include "G4Box.hh"
#include "G4Tubs.hh"   // used for constuction the self tube
#include  "G4Sphere.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include  "G4SDManager.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

#include "G4ios.hh"



G4ThreadLocal G4GlobalMagFieldMessenger* MuonDetectorConstruction::fMagFieldMessenger = 0;

MuonDetectorConstruction::MuonDetectorConstruction()
:G4VUserDetectorConstruction()
// fLogicTarget(NULL),
// fLogicChambersV(NULL),
// fLogicChambersH(NULL),
// fStepLimit(NULL),
// fCheckOverlaps(true)
{

	// TODO Auto-generated constructor stub
	//fMessenger = new MuonDetectorMessenger(this);
//	fLogicChambersV = new G4LogicalVolume(); // define 4 logical volume for the 4 layout of GEM detectors
}

MuonDetectorConstruction::~MuonDetectorConstruction() {
	delete[] fLogicChambersV;
	delete fStepLimit;
	delete fMessenger;
}

// Construction function for the Detector and the Target
G4VPhysicalVolume* MuonDetectorConstruction::Construct(){
	// define the materials that been used in the simulation toolkit
	DefineMaterials();

	//construct the detector and the Target
	return DefineVolumes();
}


// searching for the nist material database
void MuonDetectorConstruction::DefineMaterials(){
	// material definition
	G4NistManager *nistManager = G4NistManager::Instance();

	// build the materials for the world volume and the for the GEM detector
	fIntermediumMaterials_Air =nistManager->FindOrBuildMaterial("G4_AIR");
	// construct co2/n2 mixture which used inside the gas detector
	G4Material *material_n=nistManager->FindOrBuildMaterial("G4_N");
	G4Material *material_co2=nistManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");

	G4double Gas_mixiture_CO2=0.3;
	G4double Gas_mixiture_N  =0.7;
	G4double density_co2_n= (28*Gas_mixiture_N/22.4+44*Gas_mixiture_CO2/22.4)*mg/cm3;  // calculate the density of the mix gas
	fMaterials_3CO2_7Ar =  new G4Material("fMaterials_3CO2_7Ar",density_co2_n,2);//ncomponents=
	fMaterials_3CO2_7Ar->AddMaterial(material_co2,30*perCent);
	fMaterials_3CO2_7Ar->AddMaterial(material_n,70*perCent);

	// build the materials for the target
	fTargetMaterials_Al = nistManager->FindOrBuildMaterial("G4_Al");
	fTargetMaterials_Pb = nistManager->FindOrBuildMaterial("G4_Pb");
	fTargetMaterials_Bi = nistManager->FindOrBuildMaterial("G4_Bi");
	fTargetMaterials_Fe = nistManager->FindOrBuildMaterial("G4_Fe");
	fTargetMaterials_Cu = nistManager->FindOrBuildMaterial("G4_Cu");
	fTargetMaterials_Pu = nistManager->FindOrBuildMaterial("G4_Pu");
	fTargetMaterials_U  = nistManager->FindOrBuildMaterial("G4_U");

	//build the detector materials
	fChamberMaterials_Cu    = nistManager->FindOrBuildMaterial("G4_Cu");
	fChamberMaterials_Myler = nistManager->FindOrBuildMaterial("G4_MYLAR");

	//print the material table
	 G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

	// return the physics volumes that been used for the simulation
	G4VPhysicalVolume *MuonDetectorConstruction::DefineVolumes(){
	// calculate the length of the word volume
	G4double worldvolumelentgh = (SizeofTarget+3*cm+ThicknessofDtector)*2.3;//((lDetector_space*2+lDetector_TargetSpace)>lDetector_Length)? ((lDetector_space*2+lDetector_TargetSpace)*1.5):lDetector_Length*1.5;

	// draw the world volume
	G4Box* worldVolumeBox=new G4Box("world",worldvolumelentgh/2,worldvolumelentgh/2,worldvolumelentgh/2);
	G4LogicalVolume *worldLogicVolume = new G4LogicalVolume(worldVolumeBox,fIntermediumMaterials_Air,"World");
	// place the world volume at position(0,0,0)
	G4VPhysicalVolume* worldPhyVolume
	=new G4PVPlacement(
			0,
			G4ThreeVector(),
			worldLogicVolume,
			"World",
			0,
			false,
			0,
			fCheckOverlaps
			);


	// Construct the Trackers
	// define the physical structure of the GEM detector,
	// for more detailed simulation, the strcuture of the detector maybe need to take into consideration which is not in he current version
	//	G4Box* detector_Box=new G4Box("detector",lDetector_Length/2,lDetector_Width/2,lDetector_Thickness/2);

	// detector configuration
	G4double detector_sphere_Phi_start   = 0.0 *deg;
	G4double detector_sphere_Phi_end     = 360.0 *deg;
	G4double detector_sphere_Theta_start = 0.0 *deg;
	G4double detector_sphere_Theta_end   = 180.0 *deg;

	G4Sphere *detector_Box = new G4Sphere("detector",SizeofTarget+3*cm,SizeofTarget+3*cm+ThicknessofDtector,detector_sphere_Phi_start,detector_sphere_Phi_end,detector_sphere_Theta_start,detector_sphere_Theta_end);
	fLogicChambersV = new G4LogicalVolume(detector_Box,fMaterials_3CO2_7Ar,"Detector_LogicVolume");

	//construct the physics volume of the detectors in the horizontal directions
	fChamberPhys_VT1 = new G4PVPlacement(
				0,   // rotation matrix
				G4ThreeVector(),
				fLogicChambersV,
				"fChamberPhys_VT1",
				worldLogicVolume,
				false,
				0
				);
	//____________________________________________________________

	//construct the target that used for Tomography

	// sphere configuration
	G4double sphere_pRmax       = SizeofTarget;
	G4double sphere_pRmin       = 0.0 *cm;
	G4double sphere_Phi_start   = 0.0 *deg;
	G4double sphere_Phi_end     = 360.0 *deg;
	G4double sphere_Theta_start = 0.0 *deg;
	G4double sphere_Theta_end   = 180.0 *deg;

	G4Sphere* TestSPhere1= new G4Sphere("TestSphere1",sphere_pRmin,sphere_pRmax,sphere_Phi_start,sphere_Phi_end,sphere_Theta_start,sphere_Theta_end);
	fLogicTarget = new G4LogicalVolume(TestSPhere1,
			fTargetMaterials_U,
			"target_log"
			);
	fPhysicTarget =
			new G4PVPlacement(
					0,
					G4ThreeVector(),
					fLogicTarget,
					"Target_Physics_volume",
					worldLogicVolume,
					false,
					0);


	//Visualization attributes
	G4VisAttributes* boxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	//G4VisAttributes* chamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	G4VisAttributes* target_color = new G4VisAttributes(G4Colour(0.5,0.7,1.0,1.0));
	G4VisAttributes* detector_color = new G4VisAttributes(G4Colour(1.0,1.0,0.0,1.0));
	worldLogicVolume->SetVisAttributes(boxVisAtt);
	fLogicTarget   ->SetVisAttributes(target_color);
	fLogicChambersV->SetVisAttributes(detector_color);
	// Target
	return worldPhyVolume;
}

// set sensitive detector and set the E_B foild for the detector layout
void MuonDetectorConstruction::ConstructSDandField()
{
	// set sensitive detectors
	G4String trackerChamberSDname = "B2/TrackerChamberSD";    // set the sensitive detector
	MuonTrackerSD* aTrackerSD = new MuonTrackerSD(trackerChamberSDname,"TrackerHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);

	SetSensitiveDetector("Detector_LogicVolume",aTrackerSD,true);
}


/// set the target and the chamber materials
void MuonDetectorConstruction::SetTargetMatrials(G4String materialName ){

}
void MuonDetectorConstruction::SetChamberMaterial(G4String materialName){

}

void MuonDetectorConstruction::SetMaxStep(G4double maxStep) {
	if((fStepLimit)&&(maxStep>0))fStepLimit->SetMaxAllowedStep(maxStep);
}

void MuonDetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps) {
	fCheckOverlaps=checkOverlaps;
}
