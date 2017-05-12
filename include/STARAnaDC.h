/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 07.May.2017, beta ver.1.2
Copyright by B. Moon
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
		TH1D* hist_DX;
		TH1D* hist_L;
		TH1D* hist_R;

	public :
		TH1D* hist_D;

		void Hdecaygate(Int_t &tbin);
		void Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs);
};
#endif

