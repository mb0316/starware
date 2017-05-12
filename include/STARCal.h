/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 07.May.2017, beta ver.1.2
Copyright by B. Moon
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
		void HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit);
};
#endif

