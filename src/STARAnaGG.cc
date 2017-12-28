/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 10.Aug.2017, ver.1.1
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
//#include "TObjectTable.h"

using namespace std;

void STARAnaGG::Hgate(TH2D *hist_Tot, Int_t iden, Int_t &start, Int_t &end, Int_t &bgls, Int_t &bgle, Int_t &bgrs, Int_t &bgre)
{
//	gObjectTable->Print();
	if (hist_P != nullptr)	delete hist_P;
	if (iden == 0)
    {
        peak = (start+end)/2; //the peak value

        bin = hist_Tot -> GetNbinsX();
        
        hist_PY = hist_Tot -> ProjectionX("Pro_X_gate", start, end, "");
        hist_BGL = hist_Tot -> ProjectionX("Pro_BGL", bgls, bgle, "");
        hist_BGR = hist_Tot -> ProjectionX("Pro_BGR", bgrs, bgre, "");
        
//		Double_t chbin = double(int(hist_PY->GetBinCenter(bin))+1)/double(bin);
		Double_t chbin = (hist_PY->GetXaxis()->GetXmax())/double(bin);
//		cout << chbin << endl;
		hist_P = new TH1D("gated_histogram", "", bin, 0, int(hist_PY->GetBinCenter(bin))+1); //gated spectrum after removing the background
        // algorithm for making the gated spectrum
        for (Int_t i = 0; i < bin; i++)
        {
            gamma = hist_PY -> GetBinContent(i+1);
            gammaL = hist_BGL -> GetBinContent(i+1);
            gammaR = hist_BGR -> GetBinContent(i+1);
            if (i < peak)
            {
                gammaP = gamma - gammaL;
                if (gammaP > 0)	hist_P -> Fill(i*chbin, gammaP);
                else continue;
            }
            
            else
            {
                gammaP = gamma - gammaR;
                if (gammaP > 0)	hist_P -> Fill(i*chbin, gammaP);
                else continue;
            }
        }
        hist_P -> Sumw2(kFALSE);
        // saving the result data
        TFile* out = new TFile(Form("%s%.01fkeV.root", direc.Data(), peak*chbin), "RECREATE");
        out -> cd();
        hist_P -> Write();
        out -> Close();
        cout << Form("%.01fkeV.root outfile has been created.", peak*chbin) << endl;
		delete hist_PY;
		delete hist_BGL;
		delete hist_BGR;
		delete out;
    }
    
	if (iden == 1) 
	{
        peak = (start+end)/2; //the peak value
        
        bin = hist_Tot -> GetNbinsY();
        hist_P = new TH1D("gated_histogram", "", bin, 0, (hist_Tot->GetBinCenter(bin))+1); //gated spectrum after removing the background
        
        hist_PY = hist_Tot -> ProjectionY("Pro_Y_gate", start, end, "");
        hist_BGL = hist_Tot -> ProjectionY("Pro_BGL", bgls, bgle, "");
        hist_BGR = hist_Tot -> ProjectionY("Pro_BGR", bgrs, bgre, "");
        
//		Double_t chbin = double(int(hist_PY->GetBinCenter(bin))+1)/double(bin);
		Double_t chbin = (hist_PY->GetXaxis()->GetXmax())/double(bin);
//		cout << chbin << endl;
        hist_P = new TH1D("gated_histogram", "", bin, 0, (hist_PY->GetBinCenter(bin))+1); //gated spectrum after removing the background
        // algorithm for making the gated spectrum
        for (Int_t i = 0; i < bin; i++)
        {
            gamma = hist_PY -> GetBinContent(i+1);
            gammaL = hist_BGL -> GetBinContent(i+1);
            gammaR = hist_BGR -> GetBinContent(i+1);
            if (i < peak)
            {
                gammaP = gamma - gammaL;
                if (gammaP > 0)	hist_P -> Fill(i*chbin, gammaP);
                else continue;
            }
            
            else
            {
                gammaP = gamma - gammaR;
                if (gammaP > 0)	hist_P -> Fill(i*chbin, gammaP);
                else continue;
            }
        }
        hist_P -> Sumw2(kFALSE);
        
        // saving the result data
        TFile* out = new TFile(Form("%s%.01fkeV.root", direc.Data(), peak*chbin), "RECREATE");
        out -> cd();
        hist_P -> Write();
        out -> Close();
        cout << Form("%.01fkeV.root outfile has been created.", peak*chbin) << endl;
		delete hist_PY;
		delete hist_BGL;
		delete hist_BGR;
		delete out;
    }
}

