/***********************************************************************************
*************************STARWARE GUI CONSTRUCTOR FILE******************************
Made by Byul Moon from Korea University
GUI constructor for STARWARE program.
Last refine : 25.Oct.2017, ver.1.4
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STARGUI_H
#define STARGUI_H

#include "TGStatusBar.h"
#include "Riostream.h"
#include "STAR.h"
#include "STARAnaGG.h"
#include "STARAnaTG.h"
#include "STARAnaDC.h"
#include "STARAnaDis.h"
#include "STARCal.h"
//#include <stdio.h>
#include <vector>
#include "TStyle.h"
#include "TCanvas.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include "TSystem.h"
#include "TRint.h"
#include "TGTextView.h"
#include <Getline.h>
#include "TString.h"

#include "TApplication.h"
#include "TSystem.h"
#include "TGClient.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "Rtypes.h"

class STARGui : public STAR
{
	private :
		STARAnaGG stargg;
		STARAnaTG startg;
		STARAnaDC stardc;
		STARAnaDis stardis;
		STARCal starcal;
		vector <int> peaksvalue;
		TCanvas* cvs3;
		TCanvas* cvs4;
//		TCanvas* cvs5;
		TCanvas* cvs6;
//		TCanvas* cvs7;
		TCanvas* cvs8;

		Int_t tbin = 0;
		Int_t tstart = 0;
		Int_t tend = 0;
		Int_t dstart1 = 0;
		Int_t dend1 = 0;
		Int_t dstart2 = 0;
		Int_t dend2 = 0;
//		Int_t tgrow = 0;
		Int_t halfpeak = 0;
		Int_t half_parent = 0;
		TString effdatafile;
		TString gatedatafile;
		Int_t timeaxis1 = 1;
		Int_t timeaxis2 = 1; //timeaxis1 : x axis is time, timeaxis2: y axis is time; 0 : enable, 1 : unable
		Int_t halftype = 1; //halftype=1 : mother nucleus decay, halftype=0 : daughter nucleus decay

		Int_t ZParent = 0;
		Double_t HalfParent = 0;
		Double_t QParent = 0;
		Double_t EParent = 0;
		Double_t EDaut = 0;
		Double_t PDaut = 0;
		Double_t unit = 0;
		Int_t DecayType = 0;

		Int_t multitype = 0;
		Double_t benergy = 0;
		Double_t bhalf = 0;
		Double_t bunit = 0;
		Int_t bmass = 0;

		TGStatusBar* fStatusBar;
		TGTextView* fTextView;

	public :
		STARGui();
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
//		void timegrow();
		void halflife();
		void setpeaks();
		void SetTimeBin(const Char_t *value);
		void SetTimeStart(const Char_t *value);
		void SetTimeEnd(const Char_t *value);
		void SetDiffStart1(const Char_t *value);
		void SetDiffEnd1(const Char_t *value);	
		void SetDiffStart2(const Char_t *value);
		void SetDiffEnd2(const Char_t *value);
//		void SetTimeGrow(const Char_t *value);
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
		void SetDecayType(Int_t value);
		void logft();
		void bgt();
		void SetUnit(Int_t value);
		void SetMulti(Int_t value);
		void SetBEnergy(const Char_t *value);
		void SetBHalf(const Char_t *value);
		void SetBMass(const Char_t *value);
		void SetHalfUnit(Int_t value);
		void bmulti();

};
#endif

