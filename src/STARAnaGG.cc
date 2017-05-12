/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
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
#include "STARAnaGG.h"
#include "TObject.h"


using namespace std;

void STARAnaGG::Hgate()
{
    Int_t start, end;
    Int_t bgrs, bgre, bgls, bgle; //background ranges

    if (gatevalueX.size() > 0 && gatevalueY.size() == 0)
    {
        start = gatevalueX[0];
        end = gatevalueX[1];
        bgls = gatevalueX[2];
        bgle = gatevalueX[3];
        bgrs = gatevalueX[4];
        bgre = gatevalueX[5];
        Int_t peak = (start+end)/2; //the peak value

		cout << start << " " << end << " " <<  bgls << " " << bgle << " " << bgrs << " " << bgre << endl;
        
        Int_t bin = hist_Tot -> GetNbinsX();
        hist_P = new TH1D("gated_histogram", "Gated Spectrum; Energy (keV); Counts;", bin, 0, bin); //gated spectrum after removing the background
        
        hist_PY = hist_Tot -> ProjectionX("Pro_X_gate", start, end, "");
        hist_BGL = hist_Tot -> ProjectionX("Pro_BGL", bgls, bgle, "");
        hist_BGR = hist_Tot -> ProjectionX("Pro_BGR", bgrs, bgre, "");
        
        // algorithm for making the gated spectrum
        Double_t gamma, gammaL, gammaR, gammaP;
        for (Int_t i = 0; i < bin; i++)
        {
            gamma = hist_PY -> GetBinContent(i+1);
            gammaL = hist_BGL -> GetBinContent(i+1);
            gammaR = hist_BGR -> GetBinContent(i+1);
            if (i < peak)
            {
                gammaP = gamma - gammaL;
                if (gammaP > 0)	hist_P -> Fill(i, gammaP);
                else continue;
            }
            
            else
            {
                gammaP = gamma - gammaR;
                if (gammaP > 0)	hist_P -> Fill(i, gammaP);
                else continue;
            }
        }
        hist_P -> Sumw2(kFALSE);
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dkeV.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_P -> Write();
        out -> Close();
        cout << peak << "keV.root outfile has been created." << endl;
        gatevalueX.clear();
    }
    
    if (gatevalueY.size() > 0 && gatevalueX.size() == 0)
    {
        start = gatevalueY[0];
        end = gatevalueY[1];
        bgls = gatevalueY[2];
        bgle = gatevalueY[3];
        bgrs = gatevalueY[4];
        bgre = gatevalueY[5];
        Int_t peak = (start+end)/2; //the peak value
        
        Int_t bin = hist_Tot -> GetNbinsX();
        hist_P = new TH1D("gated_histogram", "Gated Spectrum; Energy (keV); Counts;", bin, 0, bin); //gated spectrum after removing the background
        
        hist_PY = hist_Tot -> ProjectionY("Pro_Y_gate", start, end, "");
        hist_BGL = hist_Tot -> ProjectionY("Pro_BGL", bgls, bgle, "");
        hist_BGR = hist_Tot -> ProjectionY("Pro_BGR", bgrs, bgre, "");
        
        // algorithm for making the gated spectrum
        Double_t gamma, gammaL, gammaR, gammaP;
        for (Int_t i = 0; i < bin; i++)
        {
            gamma = hist_PY -> GetBinContent(i+1);
            gammaL = hist_BGL -> GetBinContent(i+1);
            gammaR = hist_BGR -> GetBinContent(i+1);
            if (i < peak)
            {
                gammaP = gamma - gammaL;
                if (gammaP > 0)	hist_P -> Fill(i, gammaP);
                else continue;
            }
            
            else
            {
                gammaP = gamma - gammaR;
                if (gammaP > 0)	hist_P -> Fill(i, gammaP);
                else continue;
            }
        }
        hist_P -> Sumw2(kFALSE);
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dkeV.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_P -> Write();
        out -> Close();
        cout << peak << "keV.root outfile has been created." << endl;
        gatevalueY.clear();
    }
}

