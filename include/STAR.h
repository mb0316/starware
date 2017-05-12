/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STAR_H
#define STAR_H

#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"
#include <RQ_OBJECT.h>
#include <vector>
#include "Rtypes.h"
#include "TObject.h"
#include "TString.h"

using namespace std;


class STAR
{
	RQ_OBJECT("STARAna")
	public :
		TH2D* hist_Tot;
		TString direc;
		vector<int> gatevalueX;
		vector<int> gatevalueY;

		void reset();
		void GetCoorX(Int_t event, Int_t px, Int_t, TObject *);
		void GetCoorY(Int_t event, Int_t px, Int_t, TObject *);
		void DrawInfo();
		void intro(); 
		void main(TString &directory, TString &openFile);
		void manual();

	protected :
		TH1D* hist_X = nullptr;
		TH1D* hist_Y = nullptr;
		TCanvas* cvs1 = nullptr;
		TCanvas* cvs2 = nullptr;
		TLatex* gate1 = nullptr;
		TLatex* gate2 = nullptr;
		TLatex* bgl1 = nullptr;
		TLatex* bgl2 = nullptr;
		TLatex* bgr1 = nullptr;
		TLatex* bgr2 = nullptr;
};
#endif

