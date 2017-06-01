//
//

#include<string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


float StartEnergy=1;
float EndEnergy =20;
float Steps=50;
int NumberEvents=5000;
string EnergyUnits="GeV";
string Particlename="mu+";

string GenerateFilename(string name,float Energy,int Events) {
std::ostringstream oss;
oss << name.c_str()<<"_Energy"<<Energy<<"_events"<<Events<<".mac";
   return oss.str();
}

void macros() {
	string batchmodename="batch.bh";
	ofstream bachio;
	bachio.open(batchmodename.c_str());
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


