/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 07.May.2017, beta ver.1.2
Copyright by B. Moon
***********************************************************************************/
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
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <arpa/inet.h>
#include "Rtypes.h"
#include "STAR.h"
#include "STARAnaDis.h"
#include "TObject.h"


using namespace std;

void STARAnaDis::Htimediff(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth)
{
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
	TFile* open = new TFile(Form("%s", openFile.Data()), "read");
	gated_hist = (TH1*) open -> Get("gated_histogram");
}

