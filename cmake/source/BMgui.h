// Mainframe macro generated from application: /Users/MoonByul/root/bin/root.exe
// By ROOT version 6.08/00 on 2016-12-20 20:20:27
/***********************************************************************************
*************************STARWARE GUI CONSTRUCTOR FILE******************************
Made by Byul Moon from Korea University
GUI constructor for STARWARE program.
Last refine : 13.Mar.2017, ver.1.2
Copyright by B. Moon
***********************************************************************************/

#ifndef BMGUI
#define BMGUI

#include "TGStatusBar.h"
#include "Riostream.h"
#include "BMspec.h"
#include <stdio.h>
#include <vector>
#include "TStyle.h"
#include "TCanvas.h"
#include <cmath>
#include <cstdlib>
#include <fstream>

#include "TApplication.h"
#include "TSystem.h"
#include "TGClient.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "Rtypes.h"

class BMgui
{
	private :
		BMspec star;
		vector <int> peaksvalue;
		TCanvas* cvs3;
		TCanvas* cvs4;
		TCanvas* cvs5;
		TCanvas* cvs6;
		TCanvas* cvs7;
		TCanvas* cvs8;

		Int_t tbin;
		Int_t tstart;
		Int_t tend;
		Int_t dstart1;
		Int_t dend1;
		Int_t dstart2;
		Int_t dend2;
		Int_t tgrow;
		Int_t halfpeak;
		Int_t half_parent;
		TString effdatafile;
		TString gatedatafile;
		Int_t timeaxis1=1;
		Int_t timeaxis2=1; //timeaxis1 : x axis is time, timeaxis2: y axis is time; 0 : enable, 1 : unable
		Int_t halftype=1; //halftype=1 : mother nucleus decay, halftype=0 : daughter nucleus decay

		Int_t ZParent;
		Double_t HalfParent;
		Double_t QParent;
		Double_t EParent;
		Double_t EDaut;
		Double_t PDaut;
		Double_t unit;

		Int_t multitype;
		Double_t benergy;
		Double_t bhalf;
		Double_t bunit;

		TGStatusBar* fStatusBar;



	public :
		BMgui();
//		void starware();
		void clearall();
		void openfile();
		void openeff();
		void gatedspectrum();
		void gate();
		void timegate();
		void decaygate();
		void netarea();
		void netarea2();
		void timediff();
		void timegrow();
		void halflife();
		void setpeaks();
		void SetTimeBin(const Char_t *value);
		void SetTimeStart(const Char_t *value);
		void SetTimeEnd(const Char_t *value);
		void SetDiffStart1(const Char_t *value);
		void SetDiffEnd1(const Char_t *value);	
		void SetDiffStart2(const Char_t *value);
		void SetDiffEnd2(const Char_t *value);
		void SetTimeGrow(const Char_t *value);
		void SetPeakValue(const Char_t *value);
		void SetHalfLife(const Char_t *value);
		void checktimetox(Bool_t value);
		void checktimetoy(Bool_t value);
		void checkhalftype(Int_t value);
		void EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected);
		void SetStatusText(const char *text, Int_t pi);
		void HandleMenu(Int_t menu_id);
		void TerminatePro();
		void SetZParent(const Char_t *value);
		void SetQParent(const Char_t *value);
		void SetHalfParent(const Char_t *value);
		void SetEParent(const Char_t *value);
		void SetEDaut(const Char_t *value);
		void SetPDaut(const Char_t *value);
		void logft();
		void bgt();
		void SetUnit(Int_t value);
		void SetMulti(Int_t value);
		void SetBEnergy(const Char_t *value);
		void SetBHalf(const Char_t *value);
		void SetHalfUnit(Int_t value);
		void bmulti();

//	ClassDef(BMgui, 1);
};
#endif

