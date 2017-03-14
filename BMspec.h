/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 09.Mar.2017, beta ver.1.2
Copyright by B. Moon
***********************************************************************************/

//#ifdef BMSPEC_H
//#define BMSPEC_H

#include "TROOT.h"
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


class BMspec
{
	RQ_OBJECT("BMspec")
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
		void Htimegrow(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &peak);
		void Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs);
		void peakfind(TString &openFile);
		void Hlogft(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void BGT(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit);
		void HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit);
//	ClassDef(BMspec, 1);
};
//#endif

using namespace std;

vector<int> gatevalueX;
vector<int> gatevalueY;
TGraphErrors* singledecay;
//TGraphErrors* singledecay = new TGraphErrors();

void MLM1(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
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

void MLM2(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
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

void BMspec::reset()
{
    gatevalueX.clear();
    gatevalueY.clear();
    cout << "gate information has been deleted." << endl;
}

void BMspec::GetCoorX(Int_t event, Int_t px, Int_t, TObject *)
{
    TCanvas *c = (TCanvas *) gTQSender;
    TPad *pad = (TPad *) c->GetSelectedPad();
    if (!pad) return;
    if (event == kButton1Double)
    {
        Int_t x = pad->AbsPixeltoX(px);
        x = pad->PadtoX(x);
        gatevalueX.push_back(x);
        if (gatevalueX.size() == 1)
        {
            cout << "Starting point of gate : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 2)
        {
            cout << "End point of gate : " << x << endl;
            cout << "If you want to use 'NETAREA', please click 'NETAREA' button." << endl;
            cout << "If you want to use 'GATE' or 'DECAYGATE', please keep setting the background condition." << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 3)
        {
            cout << "Starting point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 4)
        {
            cout << "End point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 5)
        {
            cout << "Starting point of right sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 6)
        {
            cout << "End point of right sided bg : " << x << endl;
            cout << "If you want to set the gate with above information, please click 'GATE' for gg coincidence, 'DECAY GATE' for decay curve." << endl;
            cout << "If you want to set the gate condition again, just double click on the canvas." << endl;
            DrawInfo();
        }
        
        if (gatevalueX.size() > 6)
        {
            cout << "Error : overflow. gate information has been deleted." << endl;
            gatevalueX.clear();
			gate1 -> Delete();
			gate2 -> Delete();
			bgl1 -> Delete();
			bgl2 -> Delete();
			bgr1 -> Delete();
			bgr2 -> Delete();
			cvs1 -> Modified();
			cvs1 -> Update();
			cvs2 -> Modified();
			cvs2 -> Update();
		}
    }
}


void BMspec::GetCoorY(Int_t event, Int_t px, Int_t, TObject *)
{
    TCanvas *c = (TCanvas *) gTQSender;
    TPad *pad = (TPad *) c->GetSelectedPad();
    if (!pad) return;
    if (event == kButton1Double)
    {
        Int_t x = pad->AbsPixeltoX(px);
        x = pad->PadtoX(x);
        gatevalueY.push_back(x);
        if (gatevalueY.size() == 1)
        {
            cout << "Starting point of gate : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 2)
        {
            cout << "End point of gate : " << x << endl;
            cout << "If you want to use 'NETAREA', please click 'NETAREA' button." << endl;
            cout << "If you want to use 'GATE' or 'DECAYGATE', please keep setting the background condition." << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 3)
        {
            cout << "Starting point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 4)
        {
            cout << "End point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 5)
        {
            cout << "Starting point of right sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 6)
        {
            cout << "End point of right sided bg : " << x << endl;
            cout << "If you want to set the gate with above information, please click 'GATE' for gg coincidence, 'DECAY GATE' for decay curve." << endl;
            cout << "If you want to set the gate condition again, just double click on the canvas." << endl;
            DrawInfo();
        }
        
        if (gatevalueY.size() > 6)
        {
            cout << "Error : overflow. gate information has been deleted." << endl;
			gatevalueY.clear();
			gate1 -> Delete();
			gate2 -> Delete();
			bgl1 -> Delete();
			bgl2 -> Delete();
			bgr1 -> Delete();
			bgr2 -> Delete();
			cvs1 -> Modified();
			cvs1 -> Update();
			cvs2 -> Modified();
			cvs2 -> Update();
        }
    }
}

void BMspec::DrawInfo()
{
    if (gatevalueX.size() == 1)
    {
        cvs1 -> cd();
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %d", gatevalueX[0]));
        
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 2)
    {
        cvs1 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %d", gatevalueX[1]));
        gate2 -> SetNDC();
        gate2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 3)
    {
        cvs1 -> cd();
        bgl1 = new TLatex(0.2, 0.7, Form("#color[2]{BGL1 : %d}", gatevalueX[2]));
        bgl1 -> SetNDC();
        bgl1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 4)
    {
        cvs1 -> cd();
        bgl2 = new TLatex(0.2, 0.65, Form("#color[2]{BGL2 : %d}", gatevalueX[3]));
        bgl2 -> SetNDC();
        bgl2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 5)
    {
        cvs1 -> cd();
        bgr1 = new TLatex(0.2, 0.6, Form("#color[4]{BGR1 : %d}", gatevalueX[4]));
        bgr1 -> SetNDC();
        bgr1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 6)
    {
        cvs1 -> cd();
        bgr2 = new TLatex(0.2, 0.55, Form("#color[4]{BGR2 : %d}", gatevalueX[5]));
        bgr2 -> SetNDC();
        bgr2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    
    if (gatevalueY.size() == 1)
    {
        cvs2 -> cd();
        
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %d", gatevalueY[0]));
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 2)
    {
        cvs2 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %d", gatevalueY[1]));
        gate2 -> SetNDC();
        gate2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 3)
    {
        cvs2 -> cd();
        bgl1 = new TLatex(0.2, 0.7, Form("#color[2]{BGL1 : %d}", gatevalueY[2]));
        bgl1 -> SetNDC();
        bgl1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 4)
    {
        cvs2 -> cd();
        bgl2 = new TLatex(0.2, 0.65, Form("#color[2]{BGL2 : %d}", gatevalueY[3]));
        bgl2 -> SetNDC();
        bgl2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 5)
    {
        cvs2 -> cd();
        bgr1 = new TLatex(0.2, 0.6, Form("#color[4]{BGR1 : %d}", gatevalueY[4]));
        bgr1 -> SetNDC();
        bgr1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 6)
    {
        cvs2 -> cd();
        bgr2 = new TLatex(0.2, 0.55, Form("#color[4]{BGR2 : %d}", gatevalueY[5]));
        bgr2 -> SetNDC();
        bgr2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    
}

void BMspec::intro()
{
    cout << "-----------------------------STARWARE(SpecTroscopy Analysis for gamma-Ray softWARE)---------------------------------" << endl;
    cout << "------------------------------------------Byul means 'star' in Korean.----------------------------------------------" << endl;
    cout << "-------------------------------Gamma-ray Spectroscopy Analysis Tool Beta Ver.1.2------------------------------------" << endl;
    cout << "The Data analysis from coincidence event matrices." << endl;
    cout << "Made by Byul Moon(B.Moon) from Korea University" << endl;
    cout << "Since Jan. 2016." << endl;
    cout << "Latest Update : Mar. 2017." << endl;
} 

void BMspec::main(TString &directory, TString &openFile)
{
   
    Int_t xnch = 4096;
    Int_t ynch = 4096; //xnch : channel number of x, ynch : channel number of y
    FILE *read;
    read = fopen(Form("%s%s", directory.Data(), openFile.Data()), "rb");
    
    direc = directory;
    
    hist_Tot = new TH2D("hist", "", xnch, 0, xnch, ynch, 0, ynch);
    Int_t temp[4096] = {0};
    
    for (Int_t i = 0; i < xnch; i++)
    {
        fread(temp, sizeof(int), xnch, read);
        for (Int_t j = 0; j < 4096; j++)
        {
            hist_Tot -> SetBinContent(i+1, j+1, temp[j]);
        }
    }
    
    hist_X = hist_Tot -> ProjectionX("pro_X");
    hist_Y = hist_Tot -> ProjectionY("pro_Y");
}

void BMspec::Hgate()
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
    
    gate1 -> Delete();
    gate2 -> Delete();
    bgl1 -> Delete();
    bgl2 -> Delete();
    bgr1 -> Delete();
    bgr2 -> Delete();
    cvs1 -> Modified();
    cvs1 -> Update();
    cvs2 -> Modified();
    cvs2 -> Update();
}

void BMspec::Htimegate(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &start, Int_t &end)
{
    if (timeaxis1 == 0 && timeaxis2 == 1)
    {
        cout << "Input the start value of the gate : " << start << endl; //gate start
        cout << "Input the end value of the gate : " << end << endl; //gate end
        
        hist_TY = hist_Tot -> ProjectionY("Pro_Y_time", start, end, ""); // singles spectrum with the time interval
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dto%dmsspectrum.root", direc.Data(), start, end), "RECREATE");
        out -> cd();
        hist_TY -> Write();
        out -> Close();
        cout << start << "to" << end << "msspectrum.root outfile has been created." << endl;
    }
    if (timeaxis1 == 1 && timeaxis2 == 0)
    {
        cout << "Input the start value of the gate : " << start << endl; //gate start
        cout << "Input the end value of the gate : " << end << endl; //gate end
        
        hist_TY = hist_Tot -> ProjectionX("Pro_X_time", start, end, ""); // singles spectrum with the time interval
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dto%dmsspectrum.root", direc.Data(), start, end), "RECREATE");
        out -> cd();
        hist_TY -> Write();
        out -> Close();
        cout << start << "to" << end << "msspectrum.root outfile has been created." << endl;
    }
    if ((timeaxis1 == 0 && timeaxis2 == 0) || (timeaxis1 == 1 && timeaxis2 == 1))
    {
        cout << "Error : The time axis is not properly setted. Please check again." << endl;
        hist_TY = new TH1D();
    }
    
}

void BMspec::Hdecaygate(Int_t &tbin)
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
    
    gate1 -> Delete();
    gate2 -> Delete();
    bgl1 -> Delete();
    bgl2 -> Delete();
    bgr1 -> Delete();
    bgr2 -> Delete();
    cvs1 -> Modified();
    cvs1 -> Update();
    cvs2 -> Modified();
    cvs2 -> Update();
}

void BMspec::Hnetarea(TCanvas *tempcvs, TString &openFile)
{
    
    Int_t start, end;

	if (openFile == NULL)
	{
		cout << "The efficiency data has not been loaded. Please load the efficiency data file." << endl;    
	}

	if (openFile != NULL)
	{

		if (gatevalueX.size() > 0 && gatevalueY.size() == 0)
		{
			start = gatevalueX[0];
			end = gatevalueX[1];

			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get("emp");

			hist_N = hist_Tot -> ProjectionX("Pro_X_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", 0, 3000);
			Double_t pi = 3.14;
			hist_N -> GetXaxis() -> SetRange(start, end);
			peak = hist_N-> GetMaximumBin();
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev*(100/(fcn -> Eval(peak)));
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", 0, 3000);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", 0, 3000);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			// represent total results for the request
			cout << peaks << " +- " << peakerror << " keV : "  << netcount << " +- " << neterror << endl;
			//		cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
			gatevalueX.clear();
		}

		if (gatevalueY.size() > 0 && gatevalueX.size() == 0)
		{
			start = gatevalueY[0];
			end = gatevalueY[1];

			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get("emp");

			hist_N = hist_Tot -> ProjectionY("Pro_Y_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", 0, 3000);
			Double_t pi = 3.14;
			hist_N -> GetXaxis() -> SetRange(start, end);
			peak = hist_N-> GetMaximumBin();
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev*(100/(fcn -> Eval(peak)));
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", 0, 3000);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", 0, 3000);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			// represent total results for the request
			cout << peaks << " +- " << peakerror << " keV : "  << netcount << " +- " << neterror << endl;
			//		cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
			gatevalueY.clear();
		}

		gate1 -> Delete();
		gate2 -> Delete();
		cvs1 -> Modified();
		cvs1 -> Update();
		cvs2 -> Modified();
		cvs2 -> Update();
	}
}

void BMspec::Hnetarea2(TCanvas *tempcvs,TString &openFile, Int_t &tstart, Int_t &tend)
{
    
    Int_t start, end;
 
	if (openFile == NULL)
	{
		cout << "The efficiency data has not been loaded. Please load the efficiency data file." << endl;    
	}

	if (openFile != NULL)
	{

		if (gatevalueX.size() > 0 && gatevalueY.size() == 0)
		{
			start = gatevalueX[0];
			end = gatevalueX[1];

			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get("emp");

			hist_N = hist_Tot -> ProjectionX("Pro_X_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", 0, 3000);
			Double_t pi = 3.14;
			hist_N -> GetXaxis() -> SetRange(start, end);
			peak = hist_N-> GetMaximumBin();
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev*(100/(fcn -> Eval(peak)));
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", 0, 3000);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", 0, 3000);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			// represent total results for the request
			cout << peaks << " +- " << peakerror << " keV : "  << netcount << " +- " << neterror << endl;
			//		cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
			gatevalueX.clear();
		}

		if (gatevalueY.size() > 0 && gatevalueX.size() == 0)
		{
			start = gatevalueY[0];
			end = gatevalueY[1];

			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get("emp");

			hist_N = hist_Tot -> ProjectionY("Pro_Y_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", 0, 3000);
			Double_t pi = 3.14;
			hist_N -> GetXaxis() -> SetRange(start, end);
			peak = hist_N-> GetMaximumBin();
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev*(100/(fcn -> Eval(peak)));
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", 0, 3000);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", 0, 3000);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			// represent total results for the request
			cout << peaks << " +- " << peakerror << " keV : "  << netcount << " +- " << neterror << endl;
			//		cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
			gatevalueY.clear();
		}

		gate1 -> Delete();
		gate2 -> Delete();
		cvs1 -> Modified();
		cvs1 -> Update();
		cvs2 -> Modified();
		cvs2 -> Update();
	}
}

void BMspec::Htimediff(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &first, Int_t &second, Int_t &third, Int_t &forth)
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

void BMspec::Htimegrow(Int_t &timeaxis1, Int_t &timeaxis2, Int_t &peak)
{
    // loading the efficiency data
    TFile* eff_read = new TFile("eff_data_add.root", "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
    TF1* fcn = (TF1*) eff_read -> Get("emp");
    
    
    TH1D* hist[10]; //setting 10 histograms to store 10 different spectra for different time interval
    Int_t time[10] = {50, 100, 200, 300, 400, 500, 700, 1000, 1500, 2000}; //for short lived isotopes
    
    // making 10 different spectra
    if (timeaxis1 == 0 && timeaxis2 == 1)
    {
        for (Int_t i = 0; i < 10; i++)
        {
            hist[i] = hist_Tot -> ProjectionY(Form("hist_grow%d", i), 0, time[i], "");
        }
    }
    if (timeaxis1 == 1 && timeaxis2 == 0)
    {
        for (Int_t i = 0; i < 10; i++)
        {
            hist[i] = hist_Tot -> ProjectionX(Form("hist_grow%d", i), 0, time[i], "");
        }
    }
    //algorithm for the calculation of the netarea
    if ((timeaxis1 == 0 && timeaxis2 == 1) || (timeaxis1 == 1 && timeaxis2 == 0))
    {
        Double_t netcount[10];
        Double_t neterror[10];
        Double_t ampl, peakerror, amplerror, deverror;
        Double_t dev = 1.0;
        TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", 0, 3000);
        Double_t pi = 3.14;
        for (Int_t i = 0; i < 10; i++)
        {
            ampl = hist[i] -> GetBinContent(peak+1);
            gaussian -> SetParameters(ampl, peak, dev, 0, 0);
            gaussian -> SetParLimits(0, 1.0, ampl+20);
            gaussian -> SetParLimits(2, 0.5, 1.5);
            hist[i] -> Fit(gaussian, "MQN", "", peak-3, peak+5);
            ampl = gaussian -> GetParameter(0);
            dev = gaussian -> GetParameter(2);
            amplerror = (gaussian -> GetParError(0))/ampl;
            deverror = (gaussian -> GetParError(2))/dev;
            netcount[i] = sqrt(2*pi)*ampl*dev*(100/(fcn -> Eval(peak)));
            neterror[i] = sqrt(amplerror*amplerror + deverror*deverror)*netcount[i];
            ampl = 0;
            amplerror = 0;
            deverror = 0;
            dev = 1.0;
        }    
        
        
        // algorithm for the time growing curve
        for (Int_t i = 0; i < 10; i++)
        {
            graph -> SetPoint(i, time[i], netcount[i]);
            graph -> SetPointError(i, 0, neterror[i]);
        }
        
        // fitting the time growing curve
        TF1* ftn = new TF1("time growing", "[0]*(1-exp(-x/[1]))", 200, 2000);
        ftn -> SetParameters(1000.000, 550.000);
        graph -> Fit(ftn, "M");
    }
    
    if ((timeaxis1 == 0 && timeaxis2 == 0) || (timeaxis1 == 1 && timeaxis2 == 1))
    {
        cout << "Error : The time axis is not properly setted. Please check again." << endl;
    }
    
}

void BMspec::manual()
{
    cout << "-------------------------------------------------------------Simple Manual---------------------------------------------------------------------" << endl;
    cout << "If you want to use 'GAMMA GATE' function, please double-click the bin point for the gate condition and background levels then click 'GATE' button." <<endl;
    cout << "If you want to use 'TIME GAMMA GATE' function, please input start and end time then click 'TIME GATE' button." << endl;
    cout << "If you want to use 'TIME DECAY GATE' function, please double-click the bin point for the gate condition and background levels then click 'DECAY GATE' button." << endl;
    cout << "If you want to use 'NETAREA CALCULATION' function, please double-click the bin point for the gate condition then click 'NETAREA' button." << endl;
    cout << "If you want to use 'TIME DIFFERENCE SPECTUM' function, please input start and end time for each spectrum then click 'TIME DIFF' button." << endl;
    cout << "If you want to use 'TIME GROWING' function, please input the peak value then click 'TIME GROW' button." << endl;
    cout << "If you want to use 'HALFLIFE MEASUREMENT' function, please input the peak value and click 'SET PEAK' button then click 'HALFLIFE' button." << "	**The gated decaycurve files must exist.**" << endl;
}

void BMspec::Hhalflife(Int_t &halftype, Int_t &half_parent, vector <int> &peaksvalue, TCanvas *tempcvs)
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
		fitter -> SetFCN(MLM1);
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
		fitter -> SetFCN(MLM2);
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

void BMspec::peakfind(TString &openFile)
{
	TFile* open = new TFile(Form("%s", openFile.Data()), "read");
	gated_hist = (TH1*) open -> Get("gated_histogram");
}
	
Double_t flogf(Int_t &ZParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut)
{
	Double_t E0 = QParent + EParent*0.001 - EDaut*0.001;
	Double_t logf = 4.0*log10(E0) + 0.78 + 0.02*(ZParent+1) - 0.005*(ZParent)*log10(E0);
	return logf;
}
	
Double_t flogt(Double_t &HalfParent, Double_t &PDaut, Double_t &unit)
{
	Double_t logt = log10(HalfParent*unit/PDaut);
	return logt;
}

void BMspec::Hlogft(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit)
{
	Double_t logf = flogf(ZParent, QParent, EParent, EDaut);
	Double_t logt = flogt(HalfParent, PDaut, unit);

	Double_t logft = logf + logt; 

	cout << "Z of Parent : " << ZParent << endl;
	cout << "Halflife of Parent : " << HalfParent*unit << " s" << endl;
	cout << "Energy of Parent : " << EParent << " keV"<< endl;
	cout << "Q-value of Parent : " << QParent << " MeV"<< endl;
	cout << "Energy of Daughter : " << EDaut << " keV"<< endl;
	cout << "Intensity of Level : " << PDaut*100 << " %"<< endl;
	cout << "logf : " << logf << endl;
	cout << "logt : " << logt << endl;
	cout << "logft : " << logft << endl;
}

void BMspec::BGT(Int_t &ZParent, Double_t &HalfParent, Double_t &QParent, Double_t &EParent, Double_t &EDaut, Double_t &PDaut, Double_t &unit)
{
	Double_t logft = flogf(ZParent, QParent, EParent, EDaut) + flogt(HalfParent, PDaut, unit);
	Double_t Bgt = (1/TMath::Power(10, logft))*(6147/TMath::Power(1.262, 2));

	cout << "B(GT) value : " << Bgt << endl;
}

void BMspec::HBMUL(Int_t &Multitype, Double_t &Energy, Double_t &Halflife, Double_t &unit)
{
	Energy = Energy*(1.0E-3);
	Halflife = log(2)/(Halflife*unit);
	Double_t bmulti = 0;
	if (Multitype == 0)
	{
		bmulti = Halflife/((1.587E15)*TMath::Power(Energy, 3));
		cout << "B(E1) = " << bmulti << " " << "e^2fm^2" << endl;
	}
	if (Multitype == 1)
	{
		bmulti = Halflife/((1.779E13)*TMath::Power(Energy, 3));
		cout << "B(M1) = " << bmulti << " " << "(ehbar2Mc)^2" << endl;
	}
	if (Multitype == 2)
	{
		bmulti = Halflife/((1.223E9)*TMath::Power(Energy, 5));
		cout << "B(E2) = " << bmulti << " " << "e^2fm^4" << endl;
	}
	if (Multitype == 3)
	{
		bmulti = Halflife/((1.371E7)*TMath::Power(Energy, 5));
		cout << "B(M2) = " << bmulti << " " << "(ehbar2Mc)^2fm^2" << endl;
	}
	if (Multitype == 4)
	{
		bmulti = Halflife/((5.698E2)*TMath::Power(Energy, 7));
		cout << "B(E3) = " << bmulti << " " << "e^2fm^6" << endl;
	}
	if (Multitype == 5)
	{
		bmulti = Halflife/((6.387)*TMath::Power(Energy, 7));
		cout << "B(M3) = " << bmulti << " " << "(ehbar2Mc)^2fm^4" << endl;
	}
}

	
