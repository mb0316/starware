/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 9.Feb.2017, ver.2.0.1
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARANADIS_H
#define STARANADIS_H

#include "TH1D.h"
#include "TString.h"
#include "STAR.h"
#include "TFile.h"


class STARAnaDis : public STAR
{
	private :
		TFile* open = nullptr;
		TH1D* hist1 = nullptr;		//The histogram for the first time condition
		TH1D* hist2 = nullptr;		//The histogram for the second time condition

	public :
		TH1D* hist_diff = nullptr;
		TH1D* gated_hist = nullptr;	//The histogram for a specific energy

		void Htimediff(TH2D *hist_Tot, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth);	//Show two different time gated histograms
		void peakfind(TString &openFile);																				//Show the histogram of a specific energy
};
#endif

