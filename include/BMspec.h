/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 09.Mar.2017, beta ver.1.2
Copyright by B. Moon
***********************************************************************************/

#ifndef BMSPEC
#define BMSPEC

//#include "TROOT.h"
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

class BMspec
{
	RQ_OBJECT("BMspec")
	private :
		vector<int> gatevalueX;
		vector<int> gatevalueY;

	public :
		TH2D* hist_Tot;
		TH1D* hist_X;
		TH1D* hist_Y;
		TH1D* hist_N;
		TH1D* hist_TY;
		TH1D* hist_P;
		TH1D* hist_D;
		TH1D* hist1;
		TH1D* hist2;
		TH1D* hist_PY;
		TH1D* hist_BGL;
		TH1D* hist_BGR;
		TH1D* hist_DX;
		TH1D* hist_L;
		TH1D* hist_R;
		TH1* gated_hist;
		TGraphErrors* graph = new TGraphErrors();
		TString direc;
		TCanvas* cvs1;
		TCanvas* cvs2;
		TLatex* gate1;
		TLatex* gate2;
		TLatex* bgl1;
		TLatex* bgl2;
		TLatex* bgr1;
		TLatex* bgr2;

//		BMspec(TString &directory, TString &openFile);
		void reset();
		void GetCoorX(Int_t event, Int_t px, Int_t, TObject *);
		void GetCoorY(Int_t event, Int_t px, Int_t, TObject *);
		void DrawInfo();
		void intro(); 
		void main(TString &directory, TString &openFile);
		void manual();
		void Hgate();
		void Htimegate(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &start, Int_t &end);
		void Hdecaygate(Int_t &tbin);
		void Hnetarea(TCanvas *tempcvs, TString &openFile);
		void Hnetarea2(TCanvas *tempcvs, TString &openFile, Int_t &tstart, Int_t &tend);
		void Htimediff(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth);
		void Htimegrow(TString &openFile, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &peak);
		void Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs);
		void peakfind(TString &openFile);
		void Hlogft(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void BGT(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit);

//	ClassDef(BMspec, 1);
};
#endif

