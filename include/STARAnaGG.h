/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 07.May.2017, beta ver.1.2
Copyright by B. Moon
***********************************************************************************/

#ifndef STARANAGG_H
#define STARANAGG_H

#include "TH1D.h"
#include "STAR.h"


class STARAnaGG : public STAR
{
	private :
		TH1D* hist_PY;
		TH1D* hist_BGL;
		TH1D* hist_BGR;

	public :
		TH1D* hist_P;

		void Hgate();
};
#endif

