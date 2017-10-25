/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 25.Oct.2017, ver.1.4
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARCAL_H
#define STARCAL_H

class STARCal
{
	private :
		Double_t flogf(Int_t &DecayType, Int_t &ZParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut);
		Double_t flogt(Double_t &HalfParent, Double_t &PDaut, Double_t &unit);

	public :
		void Hlogft(Int_t &DecayType, Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void BGT(Int_t &DecayType, Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit, Int_t &mass);
};
#endif

