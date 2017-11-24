/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 10.Aug.2017, ver.1.1
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARANADC_H
#define STARANADC_H

#include "TH1D.h"
#include "TCanvas.h"
#include <vector>
#include "STAR.h"


class STARAnaDC : public STAR
{
	private :
		TH1D* hist_DX = nullptr;	//Gated histogram for the decay curve
		TH1D* hist_L = nullptr;	//Gated histogram to remove the left hand sided bg
		TH1D* hist_R = nullptr;	//Gated histogram to remove the right hand sided bg

		Int_t peak = 0;
		Double_t gam = 0;
		Double_t gamL = 0;
		Double_t gamR = 0;
		Double_t gamP = 0;

	public :
		TH1S* hist_D = nullptr;	//Decay curve histogram(hist_DX - hist_L, hist_R)

		void Hdecaygate(TH2D *hist_Tot, Int_t iden, Int_t &start, Int_t &end, Int_t &bg_ls, Int_t &bg_le, Int_t &bg_rs, Int_t &bg_re, Int_t &nbin);	//The function to get the decay curve
		void Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs);	//The fuction to get the half-life
};
#endif

