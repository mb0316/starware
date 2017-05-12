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

