/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 10.Aug.2017, ver.1.1
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TF1.h"
#include "TFile.h"
#include "TH1S.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFitter.h"
#include <iostream>
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
#include "TMath.h"

using namespace std;

TGraphErrors* singledecay = nullptr;

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

void MLM_I(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    Int_t np = singledecay -> GetN();
    f = 0;
    Double_t *x = singledecay -> GetX();
    Double_t *y = singledecay -> GetY();
    Double_t g1 = 0;
    for (Int_t i = 0; i < np; i++)
    {
		g1 = par[3]*exp(par[0]*(par[0]*par[1]*par[1]-2*(x[i]-par[2]))/2)*TMath::Erfc((par[0]*par[1]*par[1]-(x[i]-par[2]))/(TMath::Sqrt(2)*par[1])); 
        Double_t dg = -(y[i]*log(g1) - g1);
        f += 2.*dg;
    }
}

void STARAnaDC::Hdecaygate(TH2D *hist_Tot, Int_t iden, Int_t &start, Int_t &end, Int_t &bg_ls, Int_t &bg_le, Int_t &bg_rs, Int_t &bg_re, Int_t &nbin)
{
	if (hist_D != nullptr)	delete hist_D;

	if (iden == 0)
    {
        peak = (start+end)/2; // gated peak value
        
        Int_t bin = hist_Tot -> GetNbinsY();
        hist_DX = hist_Tot -> ProjectionY("Pro_Y_decay", start, end, "");
        hist_L = hist_Tot -> ProjectionY("Pro_BGl", bg_ls, bg_le, "");
        hist_R = hist_Tot -> ProjectionY("Pro_BGr", bg_rs, bg_re, "");

		Double_t chbin = double(int(hist_DX->GetBinCenter(bin))+1)/double(bin);

        hist_D = new TH1S("hist_decay", "", bin/nbin, 0, int(hist_DX->GetBinCenter(bin))+1); //gated time curve after removing the background
        
        // algorithm for the time decay curve
        for (Int_t i = 0; i < bin; i++)
        {
            gam = hist_DX -> GetBinContent(i+1);
            gamL = hist_L -> GetBinContent(i+1);
            gamR = hist_R -> GetBinContent(i+1);
            
            gamP = gam - (gamL+gamR)/2;
            if (gamP > 0)	hist_D -> Fill(i*chbin, gamP);
            else continue;
        }
        
        hist_D -> Sumw2(kFALSE);
        
        //saving the result data
        TFile* out = new TFile(Form("%s%dch_decaycurve.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_D -> Write();
        out -> Close();
        cout << peak << "ch_decaycurve.root outfile has been created." << endl;
		delete hist_DX;
		delete hist_L;
		delete hist_R;
		delete out;
    }
    
	if (iden == 1)
    {
        peak = (start+end)/2; // gated peak value
        
        Int_t bin = hist_Tot -> GetNbinsX();
        hist_DX = hist_Tot -> ProjectionX("Pro_X_decay", start, end, "");
        hist_L = hist_Tot -> ProjectionX("Pro_BGl", bg_ls, bg_le, "");
        hist_R = hist_Tot -> ProjectionX("Pro_BGr", bg_rs, bg_re, "");

		Double_t chbin = double(int(hist_DX->GetBinCenter(bin))+1)/double(bin);

        hist_D = new TH1S("hist_decay", "", bin/nbin, 0, int(hist_DX->GetBinCenter(bin))+1); //gated time curve after removing the background
        
        // algorithm for the time decay curve
        for (Int_t i = 0; i < bin; i++)
        {
            gam = hist_DX -> GetBinContent(i+1);
            gamL = hist_L -> GetBinContent(i+1);
            gamR = hist_R -> GetBinContent(i+1);
            
            gamP = gam - (gamL+gamR)/2;
            if (gamP > 0)	hist_D -> Fill(i*chbin, gamP);
            else continue;
        }
        
        hist_D -> Sumw2(kFALSE);
        
        //saving the result data
        TFile* out = new TFile(Form("%s%dch_decaycurve.root", direc.Data(), peak), "RECREATE");
        out -> cd();
        hist_D -> Write();
        out -> Close();
        cout << peak << "ch_decaycurve.root outfile has been created." << endl;
		delete hist_DX;
		delete hist_L;
		delete hist_R;
		delete out;
    }
}

void STARAnaDC::Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs, Double_t htstart, Double_t htend)
{
	if (singledecay != nullptr)	delete singledecay;
    Int_t num = peaksvalue.size();
    
    TFile* file[num];
    TH1* hist[num];
    Int_t peakfile;
	singledecay = new TGraphErrors();
    
    for (Int_t i = 0; i < num; i++)
    {
        peakfile = peaksvalue[i];
        file[i] = new TFile(Form("%s%dch_decaycurve.root", direc.Data(), peakfile), "READ");
		if (file[i]->IsOpen() ==  true)	cout << "The peak value : " << peaksvalue[i] << " keV has been successfully read." << endl;
		if (file[i]->IsOpen() == false)
		{
			cout << "Error : The peak value " << peaksvalue[i] << " keV is not exist." << endl;
			cout << "Please check the peak value and try again." << endl;
			return;
		}
    }
    
    Int_t nbin;
	Int_t MX;
    Double_t gamma[num];
    Double_t gamma_T = 0;
    for (Int_t i = 0; i < num; i++)
    {
        hist[i] = (TH1*) file[i] -> Get("hist_decay");
    }
    nbin = hist[0] -> GetNbinsX();
	MX = hist[0]->GetBinCenter(nbin)+1;
    TH1S* hist_tot = new TH1S("decaycurve", "", nbin, 0, MX);
    
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
    Double_t interval = MX/nbin;
    for (Int_t i = 0; i < nbin; i++)
    {
//        singledecay -> SetPoint(i, (2*i*interval+interval)/2, hist_tot -> GetBinContent(i+1));
        singledecay -> SetPoint(i, hist_tot->GetBinCenter(i+1), hist_tot -> GetBinContent(i+1));
        singledecay -> SetPointError(i, interval/2, sqrt(hist_tot -> GetBinContent(i+1)));
    }

	if (halftype == 0) //halflife measurement for parent nucleus
	{
		Double_t expectedhalf = double(half_parent/log(2));
		TF1* fcn = new TF1("single_decay", "[0]*exp(-x/[1])+[2]", htstart, htend);
		TF1* exp = new TF1("decay", "[0]*exp(-x/[1])", htstart, htend);
		TF1* bg = new TF1("bg", "[0]", htstart, htend);

//		TFitter* fitter = new TFitter(3);

		Double_t ini = hist_tot -> GetMaximum();
//		fcn -> SetParameter(0, "amp", ini, 0.001, ini-200, ini+50);
//		fcn -> SetParameter(1, "TC", expectedhalf, 0.001, 0, 0);
//		fcn -> SetParameter(2, "BG", 1.200, 0.001, 0, 0);
//		fitter -> SetFCN(MLM_P);
//		fitter -> ExecuteCommand("MINOS", 0, 0);
		fcn->SetParameter(0, ini);
		fcn->SetParLimits(0, ini-200, ini+50);
		fcn->SetParameter(1, expectedhalf);
		fcn->SetParameter(2, 1.0);
		hist_tot->Fit(fcn, "MLR");

		Double_t p[3] = {0};
		for (Int_t i = 0; i < 3; i++)
		{
			p[i] = fcn -> GetParameter(i);
		}

		fcn -> SetParameters(p[0], p[1], p[2]);
		exp -> SetParameters(p[0], p[1]);
		bg -> SetParameter(0, p[2]);

		tempcvs -> cd();
		TH2D* dummy = new TH2D("dummy", "", 100, 0, MX, ini+int(ini/2), 0.2, ini+int(ini/2));
		dummy -> Draw();
		singledecay -> Draw("P");
		fcn -> Draw("SAME");
		exp -> Draw("SAME");
		bg -> Draw("SAME");
		exp -> SetLineStyle(3);
		bg -> SetLineStyle(5);
		Double_t error = (fcn -> GetParError(1))/p[1];
		cout << "Half-life : " << p[1]*log(2) << "(" << error*p[1]*log(2) << ")" << endl;
//		delete fitter;
	}

	if (halftype == 1) //halflife measurement for daughter nucleus
	{
		Double_t expectedhalf = double(log(2)/half_parent);
		cout << expectedhalf << endl;
		TF1* fcn = new TF1("daughter_decay", "([0]*[2]/([1]-[2]))*(1-exp(-([1]-[2])*x))*exp(-[2]*x)+[3]", htstart, htend);
		TF1* curve = new TF1("daughter_decay_curve", "([0]*[2]/([1]-[2]))*(1-exp(-([1]-[2])*x))*exp(-[2]*x)", htstart, htend);	
		TF1* bg = new TF1("bg", "[0]", htstart, htend);

//		TFitter* fitter = new TFitter(4);

		Double_t ini = hist_tot -> GetMaximum();
/*
		fitter -> SetParameter(0, "amp", ini, 0.001, 0, 0);
		fitter -> SetParameter(1, "TC1", expectedhalf, 0.001, expectedhalf-5E-6, expectedhalf+5E-6);
		fitter -> SetParameter(2, "TC2", expectedhalf/2, 0.001, 0, 0);
		fitter -> SetParameter(3, "BG", 1.200, 0.001, 0, 0);
		fitter -> FixParameter(1);
		fitter -> SetFCN(MLM_D);
		fitter -> ExecuteCommand("MINOS", 0, 0);
*/
		fcn->SetParameter(0, ini);
		fcn->FixParameter(1, expectedhalf);
		fcn->SetParameter(2, expectedhalf/2);
		fcn->SetParameter(3, 1.0);

		fcn->SetParLimits(1, expectedhalf-5E-6, expectedhalf+5E+6);
		hist_tot->Fit(fcn, "MRL");

		Double_t p[4] = {0};
		for (Int_t i = 0; i < 4; i++)
		{
			p[i] = fcn -> GetParameter(i);
		}

		fcn -> SetParameters(p[0], p[1], p[2], p[3]);
		curve -> SetParameters(p[0], p[1], p[2]);
		bg -> SetParameter(0, p[3]);

		tempcvs -> cd();
		TH2D* dummy = new TH2D("dummy", "", 100, 0, MX, ini+int(ini/2), 0.2, ini+int(ini/2));
		dummy -> Draw();

		singledecay -> Draw("P");
		fcn -> Draw("SAME");
		curve -> Draw("SAME");
		bg -> Draw("SAME");
		curve -> SetLineStyle(3);
		bg -> SetLineStyle(5);

		Double_t error = (fcn -> GetParError(2))/p[2];
		cout << "Half-life for parent : " << log(2)/p[1] << endl; 
		cout << "Half-life for daughter : " << log(2)/p[2] << "(" << error*(log(2)/p[2]) << ")" << endl;
//		delete fitter;
	}

	if (halftype == 2) //halflife measurement for isomeric decay only with tail
	{
		Double_t expectedhalf = double(half_parent/log(2));
		TF1* fcn = new TF1("single_decay", "[0]*exp(-x/[1])", htstart, htend);

//		TFitter* fitter = new TFitter(3);

		Double_t ini = hist_tot -> GetMaximum();
//		fcn -> SetParameter(0, "amp", ini, 0.001, ini-200, ini+50);
//		fcn -> SetParameter(1, "TC", expectedhalf, 0.001, 0, 0);
//		fcn -> SetParameter(2, "BG", 1.200, 0.001, 0, 0);
//		fitter -> SetFCN(MLM_P);
//		fitter -> ExecuteCommand("MINOS", 0, 0);
		fcn->SetParameter(0, ini);
		fcn->SetParameter(1, expectedhalf);
		hist_tot->Fit(fcn, "MLR");

		Double_t p[2] = {0};
		for (Int_t i = 0; i < 2; i++)
		{
			p[i] = fcn -> GetParameter(i);
		}

		fcn -> SetParameters(p[0], p[1]);

		tempcvs -> cd();
		TH2D* dummy = new TH2D("dummy", "", 100, 0, MX, ini+int(ini/2), 0.2, ini+int(ini/2));
		dummy -> Draw();
		singledecay -> Draw("P");
		fcn -> Draw("SAME");
		Double_t error = (fcn -> GetParError(1))/p[1];
		cout << "Half-life : " << p[1]*log(2) << "(" << error*p[1]*log(2) << ")" << endl;
//		delete fitter;
	}


}

