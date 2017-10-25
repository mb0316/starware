/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 25.Oct.2017, ver.1.4
Copyright. 2017. B. Moon
***********************************************************************************/
#include <iostream>
#include "TMath.h"
#include "STARCal.h"
#include "TObject.h"


using namespace std;
	
Double_t STARCal::flogf(Int_t &DecayType, Int_t &ZParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut)
{
	Double_t E0 = QParent + EParent*0.001 - EDaut*0.001;
	Double_t logf;
	if (DecayType == 0)	logf = 4.0*log10(E0) + 0.78 + 0.02*(ZParent+1) - 0.005*(ZParent)*log10(E0);
	if (DecayType == 1)	logf = 4.0*log10(E0) + 0.79 + 0.007*(ZParent-1) - 0.009*(ZParent)*log10(E0/3)*log10(E0/3);
	if (DecayType == 2)	logf = 2.0*log10(E0) - 5.6 + 3.5*log10(ZParent);

	return logf;
}
	
Double_t STARCal::flogt(Double_t &HalfParent, Double_t &PDaut, Double_t &unit)
{
	Double_t logt = log10(HalfParent*unit/PDaut);
	return logt;
}

void STARCal::Hlogft(Int_t &DecayType, Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit)
{
	Double_t logf = flogf(DecayType, ZParent, QParent, EParent, EDaut);
	Double_t logt = flogt(HalfParent, PDaut, unit);

	Double_t logft = logf + logt; 

	if (DecayType == 0)	cout << "Decay Type : Beta-" << endl;
	if (DecayType == 1)	cout << "Decay Type : Beta+" << endl;
	if (DecayType == 2)	cout << "Decay Type : EC" << endl;
	cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	cout << "Z of Parent : " << ZParent << endl;
	cout << "Halflife of Parent : " << HalfParent*unit << " s" << endl;
	cout << "Energy of Parent : " << EParent << " keV"<< endl;
	cout << "Q-value of Parent : " << QParent << " MeV"<< endl;
	cout << "Energy of Daughter : " << EDaut << " keV"<< endl;
	cout << "Intensity of Level : " << PDaut*100 << " %"<< endl;
	cout << "logf : " << logf << endl;
	cout << "logt : " << logt << endl;
	cout << "logft : " << logft << endl;
	cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
}

void STARCal::BGT(Int_t &DecayType, Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit)
{
	Double_t logft = flogf(DecayType, ZParent, QParent, EParent, EDaut) + flogt(HalfParent, PDaut, unit);
	Double_t Bgt = (1/TMath::Power(10, logft))*(6147/TMath::Power(1.262, 2));

	cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	cout << "B(GT) value : " << Bgt << endl;
	cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
}

void STARCal::HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit, Int_t &mass)
{
	Double_t energy = Energy*(1.0E-3);
	Double_t halflife = Halflife*unit;
	Double_t tau = log(2)/(Halflife*unit);
	Double_t bmulti = 0;
	Double_t wu = 0;
	Double_t tsp = 0;
	if (Multitype == 0)
	{
		bmulti = tau/((1.587E15)*TMath::Power(energy, 3));
		tsp = (6.76E-6)/(TMath::Power(Energy, 3)*TMath::Power(mass, 0.667));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = E1" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(E1) = " << bmulti << " " << "e^2fm^2" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(E1) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
	if (Multitype == 1)
	{
		bmulti = tau/((1.779E13)*TMath::Power(energy, 3));
		tsp = (2.20E-5)/(TMath::Power(Energy, 3));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = M1" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(M1) = " << bmulti << " " << "(ehbar2Mc)^2" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(M1) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
	if (Multitype == 2)
	{
		bmulti = tau/((1.223E9)*TMath::Power(energy, 5));
		tsp = (9.52E6)/(TMath::Power(Energy, 5)*TMath::Power(mass, 1.333));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = E2" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(E2) = " << bmulti << " " << "e^2fm^4" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(E2) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
	if (Multitype == 3)
	{
		bmulti = tau/((1.371E7)*TMath::Power(energy, 5));
		tsp = (3.1E7)/(TMath::Power(Energy, 5)*TMath::Power(mass, 0.667));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = M2" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(M2) = " << bmulti << " " << "(ehbar2Mc)^2fm^2" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(M2) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
	if (Multitype == 4)
	{
		bmulti = tau/((5.698E2)*TMath::Power(energy, 7));
		tsp = (2.04E19)/(TMath::Power(Energy, 7)*TMath::Power(mass, 2));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = E3" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(E3) = " << bmulti << " " << "e^2fm^6" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(E3) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
	if (Multitype == 5)
	{
		bmulti = tau/((6.387)*TMath::Power(energy, 7));
		tsp = (6.66E19)/(TMath::Power(Energy, 7)*TMath::Power(mass, 1.333));
		wu = tsp/halflife;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "A = " << mass << ", Energy = " << Energy << " keV, Multipolarity = M3" << ", Half-life = " << halflife << "s" << endl;
		cout << "B(M3) = " << bmulti << " " << "(ehbar2Mc)^2fm^4" << endl;
		cout << "T1/2,sp = " << tsp << " " << "s" << endl;
		cout << "B(M3) = " << wu << " " << "W.u." << endl;
		cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
	}
}

