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
#include "TH1S.h"
#include "STAR.h"


class STARAnaGG : public STAR
{
	private :
		TH1D* hist_PY = nullptr;
		TH1D* hist_BGL = nullptr;
		TH1D* hist_BGR = nullptr;

		Int_t		start = 0;
		Int_t		end = 0;
		Int_t		bgrs = 0;
		Int_t		bgre = 0;
		Int_t		bgls = 0;
		Int_t		bgle = 0;
		Int_t		peak = 0;
		Int_t		bin = 0;
		Double_t	gamma = 0;
		Double_t	gammaL = 0;
		Double_t	gammaR = 0;
		Double_t	gammaP = 0;

	public :
		TH1D* hist_P = nullptr;

		void Hgate();
};
#endif

