/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARANAGG_H
#define STARANAGG_H

#include "TH1D.h"
#include "TH2S.h"
#include "STAR.h"


class STARAnaGG : public STAR
{
	private :
		TH1D* hist_PY = nullptr;
		TH1D* hist_BGL = nullptr;
		TH1D* hist_BGR = nullptr;

		Int_t		peak = 0;
		Int_t		bin = 0;
		Double_t	gamma = 0;
		Double_t	gammaL = 0;
		Double_t	gammaR = 0;
		Double_t	gammaP = 0;

	public :
		TH1D* hist_P = nullptr;

		void Hgate(TH2D *hist_Tot, Int_t iden, Int_t &start, Int_t &end, Int_t &bgls, Int_t &bgle, Int_t &bgrs, Int_t &bgre);
};
#endif

