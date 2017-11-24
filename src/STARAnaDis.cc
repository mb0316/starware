/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.Aug.2017, ver.1.1
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "STAR.h"
#include "STARAnaDis.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void STARAnaDis::Htimediff(TH2D *hist_Tot, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth)
{
	if (hist1 != nullptr)	delete hist1;
	if (hist2 != nullptr)	delete hist2;

    if (timeaxis1 == 0 && timeaxis2 == 1)
    {
        hist1 = hist_Tot -> ProjectionY("first_time", first, second, "");
        hist2 = hist_Tot -> ProjectionY("second_time", third, forth, "");
        hist2 -> SetLineColor(2);
        hist1 -> SetLineColor(4);
    }
    
    if (timeaxis1 == 1 && timeaxis2 == 0)
    {
        hist1 = hist_Tot -> ProjectionX("first_time", first, second, "");
        hist2 = hist_Tot -> ProjectionX("second_time", third, forth, "");
        hist2 -> SetLineColor(2);
        hist1 -> SetLineColor(4);
    }
    
    if ((timeaxis1 == 0 && timeaxis2 == 0) || (timeaxis1 == 1 && timeaxis2 == 1))
    {
        cout << "Error : The time axis is not properly setted. Please check again." << endl;
        hist1 = new TH1D();
        hist2 = new TH1D();
    }
}

void STARAnaDis::peakfind(TString &openFile)
{
	if (gated_hist != nullptr)	delete gated_hist;
	if (open != nullptr)	delete open;
	open = new TFile(Form("%s", openFile.Data()), "read");
	gated_hist = (TH1*) open -> Get(open->GetListOfKeys()->At(0)->GetName());
}

