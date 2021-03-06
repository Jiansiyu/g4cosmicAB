
// ********************************************************************
//
//		Muon Tomography Geant4 Simulation
//		Author: Siyu Jian	@ Physics Department of University of Virginia
//		Email:  jiansiyu@gmail.com
//		Notes:  Based on the Geant4 ExampleN02
//				Partly refer to Prof. Wen same simulation toolkit
//
// ********************************************************************


// Detector Constructiuon class
#include "MuonDetectorConstruction.hh"
#include "MuonActionInitialization.hh"
#include "MuonPhysicsList.hh"


//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include <TH1F.h>   // root interface
#include <TCanvas.h>


// used for get the externtion of the input filename
#include "iostream"
#include "string"
#include "fstream"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

G4double TotalEvents;
G4double DetectoredEvents;
TH1F *EffHisto;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc,char** argv)
{

  //Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

// Construct the default run manager
//#ifdef G4MULTITHREADED
//G4MTRunManager* runManager = new G4MTRunManager;
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif

  // Set mandatory initialization classes
  //detector construction
  runManager->SetUserInitialization(new MuonDetectorConstruction());

  // physiclist configuration
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);

  // Set user action classes
  runManager->SetUserInitialization(new MuonActionInitialization());

  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();


  EffHisto=new TH1F("Infor ","Percentage_of_Particle_Detected", 100, 0, 5000);
  			EffHisto->GetXaxis()->SetTitle("# Events");
  			EffHisto->GetYaxis()->SetTitle("Detected/TotalEvents");

  // Process macro or start UI session
  if ( ! ui ) { 
	std::string inputfilename(argv[1]);
	if(inputfilename.substr(inputfilename.find_last_of(".")+1)=="bh"){
		TH1F *EnergyScanHisto;

		ifstream inputbachname(inputfilename.c_str());
		std::string singlelineMacFilename;
		// read the first line and configure the histogram
		std::string configurations;
		std::getline(inputbachname,configurations);
		configurations.erase( remove_if(configurations.begin(), configurations.end(), ::isspace), configurations.end() );
		char *tokens=std::strtok( (char *)configurations.data(), ",");

		float startenergy;
		float endenergy;
		int steps;
		if(tokens!=NULL){
			startenergy=std::atof(tokens);
			tokens=std::strtok(NULL,",");
			endenergy=std::atof(tokens);
			tokens=std::strtok(NULL,",");
			steps=std::atoi(tokens);
			//printf("\n\n\n************\n start: %f\n end:%f\n steps:%d\n*******************\n\n",startenergy,endenergy,steps);
			EnergyScanHisto=new TH1F(Form("E_infor"),Form("Energy_Scan_%f_to_%f_step_%d",startenergy,endenergy,steps),steps,startenergy,endenergy);
			EnergyScanHisto->GetXaxis()->SetTitle("Energy");
			EnergyScanHisto->GetYaxis()->SetTitle("Percentage Remain");
		}
		while(std::getline(inputbachname,singlelineMacFilename)){
			// initialize the data
			TotalEvents=0;
			DetectoredEvents=0;
			EffHisto->Clear();
			singlelineMacFilename=singlelineMacFilename.substr(0,singlelineMacFilename.find_first_of("#")); // delete notations from the batch
			if(singlelineMacFilename.substr(singlelineMacFilename.find_last_of(".")+1)=="mac")
			{
				G4String command = "/control/execute ";
				G4String fileName =singlelineMacFilename;
				G4cout<<fileName<<G4endl;
				UImanager->ApplyCommand(command+fileName);
				G4cout<<"Percentage remains :"<<DetectoredEvents*100.0/TotalEvents<<"%"<<G4endl;
				EnergyScanHisto->Fill(UImanager->GetCurrentStringValue("/gun/energy").data(),DetectoredEvents/TotalEvents);
				// save the graph
				EffHisto->SaveAs(Form("Result/%s_Energy%s.C",UImanager->GetCurrentStringValue("/gun/particle").data(),
						  UImanager->GetCurrentStringValue("/gun/energy").data()
						  ));
			}

		}
		EnergyScanHisto->SaveAs(Form("%s_Energy_Scan_%f_to_%f_step_%d.C",UImanager->GetCurrentStringValue("/gun/particle").data(),
				startenergy,endenergy,steps
		));

	}else {
		G4cout<<".mac file detected"<<G4endl;
		// batch mode
	    G4String command = "/control/execute ";
	    G4String fileName = argv[1];
	    UImanager->ApplyCommand(command+fileName);
	}
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  EffHisto->SaveAs(Form("%s_Energy%s.C",UImanager->GetCurrentStringValue("/gun/particle").data(),
  		  UImanager->GetCurrentStringValue("/gun/energy").data()
  		  ));

  G4cout<<"Percentage remains :"<<DetectoredEvents*100.0/TotalEvents<<"%"<<G4endl;

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !
  delete visManager;/**/
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
