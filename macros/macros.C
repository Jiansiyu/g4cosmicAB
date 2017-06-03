/*
############################################
#   Mac Generator used for Geant4 MC
# 	tested @ root5.34.36
# Autor: Siyu Jian @ University of Virginia
# Email: jiansiyu@gmail.com
#          Go Wahoo
############################################
*/

#include<string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

//***********************************************************************
// You may need modify the following lines according to your requirements
float StartEnergy=1;		// G4 particle gun energy scan -> start energy
float EndEnergy =20;		// G4 particle gun energy scan -> end energy
string EnergyUnits="GeV";	// G4 particle gun energy scan -> energy Units (MUST BE G4 PREDEFINED UNITS)
float Steps=50;			// simulation steps
int NumberEvents=5000;		// # of events in single simulation step
string Particlename="mu+";	// particle that used for simulation (MUST BE PREDEFINED IN G4 PARTICLE LIST)
//***********************************************************************


string GenerateFilename(string name,float Energy,int Events) {
std::ostringstream oss;
char cwd[1024];
if(getcwd(cwd,sizeof(cwd))!=NULL){
oss << cwd<<"/"<<name.c_str()<<"_Energy"<<Energy<<"_events"<<Events<<".mac";
   
   }else{
   oss <<name.c_str()<<"_Energy"<<Energy<<"_events"<<Events<<".mac";
   }
   return oss.str();
}

void macros() {
	string batchmodename="batch.bh";
	ofstream bachio;
	bachio.open(batchmodename.c_str());
	bachio<<StartEnergy<<", "<<EndEnergy<<", "<<Steps<<endl;
	bachio<<"############################################"<<endl;
	bachio<<"#   Auto Generated Batch Mode Run File"<<endl;
	bachio<<"# !!!!!!! Caution when Changing it !!!!!"<<endl;
	bachio<<"# Autor: Siyu Jian @ University of Virginia"<<endl;
	bachio<<"# Email: jiansiyu@gmail.com"<<endl;
	bachio<<"#          Go Wahoo"<<endl;
	bachio<<"############################################"<<endl;
	
	for(int i =0; i <=Steps; i ++){
	 //GenerateFilename(Particlename,(EndEnergy-StartEnergy)*i/Steps+StartEnergy,NumberEvents);
	 ofstream myfile;
	 myfile.open(GenerateFilename(Particlename,(EndEnergy-StartEnergy)*i/Steps+StartEnergy,NumberEvents).c_str());
	 bachio<<GenerateFilename(Particlename,(EndEnergy-StartEnergy)*i/Steps+StartEnergy,NumberEvents).c_str()<<endl;
	 myfile<<"# auto generated mac for geant4"<<endl;
	 myfile<<"# Autor:Siyu"<<endl;
	 myfile<<"/run/verbose 0\n";
	 myfile<<"/tracking/verbose 0\n";
	 myfile<<"/event/verbose 0\n";
	 myfile<<"/run/initialize\n";
	 myfile<<"#set the particle to be "<<Particlename.c_str()<<endl;
	 myfile<<"#Energy of particle is "<<(EndEnergy-StartEnergy)*i/Steps+StartEnergy<<" "<<EnergyUnits.c_str()<<endl;
	 myfile<<"/gun/energy "<<(EndEnergy-StartEnergy)*i/Steps+StartEnergy<<" "<<EnergyUnits.c_str()<<"\n";
	 myfile<<"/gun/particle "<<Particlename.c_str()<<"\n";
	 myfile<<"/run/beamOn "<<NumberEvents<<"\n";
	 myfile.close();
	}
	bachio.close();
}
