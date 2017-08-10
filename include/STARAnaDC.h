/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
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

	public :
		TH1S* hist_D = nullptr;	//Decay curve histogram(hist_DX - hist_L, hist_R)

		void Hdecaygate(Int_t &tbin);																		//The function to get the decay curve
		void Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs);	//The fuction to get the half-life
};
#endif

