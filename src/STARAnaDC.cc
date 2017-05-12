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
#include "STARAnaDC.h"
#include "TObject.h"

using namespace std;

TGraphErrors* singledecay;

void MLM_P(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    Int_t np = singledecay -> GetN();
    f = 0;
    Double_t *x = singledecay -> GetX();
    Double_t *y = singledecay -> GetY();
    Double_t g1 = 0;
    for (Int_t i = 0; i < np; i++)
    {
        g1 = par[0]*exp(-x[i]/par[1]) + par[2];
        Double_t dg = -(y[i]*log(g1) - g1);
        f += 2.*dg;
    }
}

void MLM_D(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    Int_t np = singledecay -> GetN();
    f = 0;
    Double_t *x = singledecay -> GetX();
    Double_t *y = singledecay -> GetY();
    Double_t g1 = 0;
    for (Int_t i = 0; i < np; i++)
    {
		g1 = (par[0]*par[2]/(par[1]-par[2]))*(1-exp(-(par[1]-par[2])*x[i]))*exp(-par[2]*x[i])+par[3];
        Double_t dg = -(y[i]*log(g1) - g1);
        f += 2.*dg;
    }
}

void STARAnaDC::Hdecaygate(Int_t &tbin)
{
    
    Int_t start, end, bg_rs, bg_re, bg_ls, bg_le, nbin; // background ranges
    
    if (gatevalueX.size() > 0 && gatevalueY.size() == 0)
    {
        start = gatevalueX[0];
        end = gatevalueX[1];
        bg_ls = gatevalueX[2];
        bg_le = gatevalueX[3];
        bg_rs = gatevalueX[4];
        bg_re = gatevalueX[5];
        Int_t peak = (start+end)/2; // gated peak value
        
        nbin = tbin;
        Int_t bin = hist_Tot -> GetNbinsY();
        hist_DX = hist_Tot -> ProjectionY("Pro_Y_decay", start, end, "");
        hist_L = hist_Tot -> ProjectionY("Pro_BGl", bg_ls, bg_le, "");
        hist_R = hist_Tot -> ProjectionY("Pro_BGr", bg_rs, bg_re, "");
        hist_D = new TH1D("hist_decay", "Decay Curve; Time (ms); Counts;", bin/nbin, 0, bin); //gated time curve after removing the background
        
        Double_t gam, gamL, gamR, gamP;
        
        // algorithm for the time decay curve
        for (Int_t i = 0; i < bin; i++)
        {
            gam = hist_DX -> GetBinContent(i+1);
            gamL = hist_L -> GetBinContent(i+1);
            gamR = hist_R -> GetBinContent(i+1);
            
            gamP = gam - (gamL+gamR)/2;
            if (gamP > 0)	hist_D -> Fill(i, gamP);
            else continue;
        }
        
        hist_D -> Sumw2(kFALSE);
        
        //saving the result data
        TFile* out = new TFile(Form("%s%dkeV_decaycurve.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_D -> Write();
        out -> Close();
        cout << peak << "keV_decaycurve.root outfile has been created." << endl;
        gatevalueX.clear();
    }
    
    if (gatevalueY.size() > 0 && gatevalueX.size() == 0)
    {
        start = gatevalueY[0];
        end = gatevalueY[1];
        bg_ls = gatevalueY[2];
        bg_le = gatevalueY[3];
        bg_rs = gatevalueY[4];
        bg_re = gatevalueY[5];
        Int_t peak = (start+end)/2; // gated peak value
        
        nbin = tbin;
        
        Int_t bin = hist_Tot -> GetNbinsX();
        hist_DX = hist_Tot -> ProjectionX("Pro_X_decay", start, end, "");
        hist_L = hist_Tot -> ProjectionX("Pro_BGl", bg_ls, bg_le, "");
        hist_R = hist_Tot -> ProjectionX("Pro_BGr", bg_rs, bg_re, "");
        hist_D = new TH1D("hist_decay", "Decay Curve; Time (ms); Counts;", bin/nbin, 0, bin); //gated time curve after removing the background
        
        Double_t gam, gamL, gamR, gamP;
        
        // algorithm for the time decay curve
        for (Int_t i = 0; i < bin; i++)
        {
            gam = hist_DX -> GetBinContent(i+1);
            gamL = hist_L -> GetBinContent(i+1);
            gamR = hist_R -> GetBinContent(i+1);
            
            gamP = gam - (gamL+gamR)/2;
            if (gamP > 0)	hist_D -> Fill(i, gamP);
            else continue;
        }
        
        hist_D -> Sumw2(kFALSE);
        
        //saving the result data
        TFile* out = new TFile(Form("%s%dkeV_decaycurve.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_D -> Write();
        out -> Close();
        cout << peak << "keV_decaycurve.root outfile has been created." << endl;
        gatevalueY.clear();
    }
}

void STARAnaDC::Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs)
{
    Int_t num = peaksvalue.size();
    
    TFile* file[num];
    TH1* hist[num];
    Int_t peakfile;
	singledecay = new TGraphErrors();
    
    for (Int_t i = 0; i < num; i++)
    {
        cout << "The peak value : " << peaksvalue[i] << " done."<< endl;
        peakfile = peaksvalue[i];
        file[i] = new TFile(Form("%s%dkeV_decaycurve.root", direc.Data(), peakfile), "READ");
    }
    
    Int_t nbin;
    Double_t gamma[num];
    Double_t gamma_T = 0;
    
    for (Int_t i = 0; i < num; i++)
    {
        hist[i] = (TH1*) file[i] -> Get("hist_decay");
    }
    nbin = hist[0] -> GetNbinsX();
    TH1D* hist_tot = new TH1D("decaycurve", "", nbin, 0, 4000);
    
    for (Int_t i = 0; i < nbin; i++)
    {
        for (Int_t ihist = 0 ; ihist < num; ihist++)
        {
            gamma[ihist] = hist[ihist] -> GetBinContent(i+1);
            gamma_T = gamma_T + gamma[ihist];
        }
        hist_tot -> SetBinContent(i+1, gamma_T);
        gamma_T = 0;
    }
    
    Double_t interval = 4096/nbin;
    cout << nbin << " " << interval << endl;
    for (Int_t i = 0; i < nbin; i++)
    {
        singledecay -> SetPoint(i, (2*i*interval+interval)/2, hist_tot -> GetBinContent(i+1));
        singledecay -> SetPointError(i, interval/2, sqrt(hist_tot -> GetBinContent(i+1)));
    }

	if (halftype == 1) //halflife measurement for parent nucleus
	{
		Double_t expectedhalf = double(half_parent/log(2));
		TF1* fcn = new TF1("single_decay", "[0]*exp(-x/[1])+[2]", 0, 4000);
		TF1* exp = new TF1("decay", "[0]*exp(-x/[1])", 0, 4000);
		TF1* bg = new TF1("bg", "[0]", 0, 4000);

		TFitter* fitter = new TFitter(3);

		Double_t ini = hist_tot -> GetMaximum();
		fitter -> SetParameter(0, "amp", ini, 0.001, ini-200, ini+50);
		fitter -> SetParameter(1, "TC", expectedhalf, 0.001, 0, 0);
		fitter -> SetParameter(2, "BG", 1.200, 0.001, 0, 0);
		fitter -> SetFCN(MLM_P);
		fitter -> ExecuteCommand("MINOS", 0, 0);

		Double_t p[3] = {0};
		for (Int_t i = 0; i < 3; i++)
		{
			p[i] = fitter -> GetParameter(i);
		}

		fcn -> SetParameters(p[0], p[1], p[2]);
		exp -> SetParameters(p[0], p[1]);
		bg -> SetParameter(0, p[2]);

		tempcvs -> cd();
		TH2D* dummy = new TH2D("dummy", "Decay Curve; Time (ms); Counts;", 4000, 0, 4000, ini+int(ini/2), 0.2, ini+int(ini/2));
		dummy -> Draw();
		singledecay -> Draw("P");
		fcn -> Draw("SAME");
		exp -> Draw("SAME");
		bg -> Draw("SAME");
		exp -> SetLineStyle(3);
		bg -> SetLineStyle(5);
		Double_t error = (fitter -> GetParError(1))/p[1];
		cout << "Half-life : " << p[1]*log(2) << "(" << error*p[1]*log(2) << ")" << endl;

	}

	if (halftype == 0) //halflife measurement for daughter nucleus
	{
		Double_t expectedhalf = double(log(2)/half_parent);
		cout << expectedhalf << endl;
		TF1* fcn = new TF1("daughter_decay", "([0]*[2]/([1]-[2]))*(1-exp(-([1]-[2])*x))*exp(-[2]*x)+[3]", 0, 4000);
		TF1* curve = new TF1("daughter_decay_curve", "([0]*[2]/([1]-[2]))*(1-exp(-([1]-[2])*x))*exp(-[2]*x)", 0, 4000);	
		TF1* bg = new TF1("bg", "[0]", 0, 4000);

		TFitter* fitter = new TFitter(4);

		Double_t ini = hist_tot -> GetMaximum();
		fitter -> SetParameter(0, "amp", ini, 0.001, 0, 0);
		fitter -> SetParameter(1, "TC1", expectedhalf, 0.001, expectedhalf-5E-6, expectedhalf+5E-6);
		fitter -> SetParameter(2, "TC2", expectedhalf/2, 0.001, 0, 0);
		fitter -> SetParameter(3, "BG", 1.200, 0.001, 0, 0);
		fitter -> FixParameter(1);
		fitter -> SetFCN(MLM_D);
		fitter -> ExecuteCommand("MINOS", 0, 0);

		Double_t p[4] = {0};
		for (Int_t i = 0; i < 4; i++)
		{
			p[i] = fitter -> GetParameter(i);
		}

		fcn -> SetParameters(p[0], p[1], p[2], p[3]);
		curve -> SetParameters(p[0], p[1], p[2]);
		bg -> SetParameter(0, p[3]);

		tempcvs -> cd();
		TH2D* dummy = new TH2D("dummy", "Decay Curve; Time (ms); Counts;", 4000, 0, 4000, ini+int(ini/2), 0.2, ini+int(ini/2));
		dummy -> Draw();
		singledecay -> Draw("P");
		fcn -> Draw("SAME");
		curve -> Draw("SAME");
		bg -> Draw("SAME");
		curve -> SetLineStyle(3);
		bg -> SetLineStyle(5);
		Double_t error = (fitter -> GetParError(2))/p[2];
		cout << "Half-life for parent : " << log(2)/p[1] << endl; 
		cout << "Half-life for daughter : " << log(2)/p[2] << "(" << error*(log(2)/p[2]) << ")" << endl;


	}
}

