/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 10.Aug.2017, ver.1.1
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARANATG_H
#define STARANATG_H

#include "TH1D.h"
#include "TCanvas.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "STAR.h"


class STARAnaTG : public STAR
{
	private :

	public :
		TH1D* hist_N = nullptr;
		TH1D* hist_TY = nullptr;
		TGraphErrors* graph = new TGraphErrors();

		void Htimegate(TH2D *hist_Tot, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &start, Int_t &end);
		void Hnetarea(TH2D *hist_Tot, Int_t iden, Int_t start, Int_t end, TCanvas *tempcvs, TString &openFile);
		void Hnetarea2(TH2D *hist_Tot, Int_t iden, Int_t start, Int_t end, TCanvas *tempcvs,TString &openFile, Int_t &tstart, Int_t &tend);
//		void Htimegrow(TString &openFile, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &peak);
};
#endif

