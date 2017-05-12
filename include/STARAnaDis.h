/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARANADIS_H
#define STARANADIS_H

#include "TH1D.h"
#include "TString.h"
#include "STAR.h"


class STARAnaDis : public STAR
{
	private :

	public :
		TH1D* hist1;
		TH1D* hist2;
		TH1* gated_hist;

		void Htimediff(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth);
		void peakfind(TString &openFile);
};
#endif

