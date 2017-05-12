/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 07.May.2017, beta ver.1.2
Copyright by B. Moon
***********************************************************************************/

#ifndef STAR_H
#define STAR_H

#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TFitter.h"
#include <iostream>
#include "TPad.h"
#include "TLatex.h"
#include "TMath.h"
#include <RQ_OBJECT.h>
#include <vector>
#include "Rtypes.h"
#include "TObject.h"

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

