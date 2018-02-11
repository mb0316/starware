/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 9.Feb.2017, ver.2.0.1
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TSystem.h"
#include "TH1S.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include <iostream>
#include "TPad.h"
#include "TLatex.h"
#include <RQ_OBJECT.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <arpa/inet.h>
#include "Rtypes.h"
#include "STAR.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TString.h"
#include "TObjString.h"
#include <sys/stat.h>
#include "TGWindow.h"
#include "TGClient.h"
#include "TGLabel.h"
#include "TGNumberEntry.h"
#include "TGButton.h"
#include "TSpectrum.h"

using namespace std;

void STAR::main(TString &directory, TString &openFile)
{
	if (hist_Tot != nullptr)	delete hist_Tot;
	if (hist_X != nullptr)	delete hist_X;
	if (hist_Y != nullptr)	delete hist_Y;

	TObjArray *decomp = openFile.Tokenize(".");
	TString filetype = ((TObjString *) decomp->Last()) -> GetString();

	if (filetype == "mat")
	{
		binconfirm = false;
		cout << "Selected data file : MAT type!!" << endl;


		struct stat file_stat;
		stat(Form("%s%s", directory.Data(), openFile.Data()), &file_stat);
		filesize = (ULong64_t) file_stat.st_size;

		read = fopen(Form("%s%s", directory.Data(), openFile.Data()), "rb");

		frame = new TGMainFrame(gClient->GetRoot(),230,150,kMainFrame | kVerticalFrame);

		TGLabel *lX_SET = new TGLabel(frame, "Value/bin for X");
		lX_SET -> SetTextJustify(kTextLeft);
		lX_SET-> SetMargins(0, 0, 0, 0);
		lX_SET-> SetWrapLength(-1);
		frame-> AddFrame(lX_SET, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
		lX_SET-> MoveResize(10, 10, 100, 20);

		TGNumberEntryField *fX_SET = new TGNumberEntryField(frame, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 100);
		fX_SET->MoveResize(120, 10, 100, 20);
		frame->AddFrame(fX_SET, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fX_SET -> Connect("TextChanged(const Char_t *)", "STAR", this, "SetXBin(const Char_t *)");

		TGLabel *lY_SET = new TGLabel(frame, "Value/bin for Y");
		lY_SET -> SetTextJustify(kTextLeft);
		lY_SET-> SetMargins(0, 0, 0, 0);
		lY_SET-> SetWrapLength(-1);
		frame-> AddFrame(lY_SET, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
		lY_SET-> MoveResize(10, 50, 100, 20);

		TGNumberEntryField *fY_SET = new TGNumberEntryField(frame, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 100);
		fY_SET->MoveResize(120, 50, 100, 20);
		frame->AddFrame(fY_SET, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fY_SET -> Connect("TextChanged(const Char_t *)", "STAR", this, "SetYBin(const Char_t *)");

		TGTextButton *SET_BIN = new TGTextButton(frame,"SET",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
		SET_BIN -> Connect("Clicked()", "STAR", this, "SETBIN()");
		SET_BIN->SetTextJustify(36);
		SET_BIN->SetMargins(0,0,0,0);
		SET_BIN->SetWrapLength(-1);
		frame->AddFrame(SET_BIN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		SET_BIN->MoveResize(10,100,100,35);
		frame->MapSubwindows();
		frame->MapWindow();

		while (1)
		{
			gSystem->ProcessEvents();
			if (binconfirm == true)
			{
				break;
			}
			if (binconfirm == false)	continue;
		}


	}

	if (filetype == "root")
	{
		cout << "Selected data file : ROOT type!!" << endl;
		TFile* file = new TFile(Form("%s%s", directory.Data(), openFile.Data()), "READ");
		hist_Tot = (TH2D*) file -> Get(file->GetListOfKeys()->At(0)->GetName());
		hist_X = hist_Tot -> ProjectionX("pro_X");
		hist_Y = hist_Tot -> ProjectionY("pro_Y");

		nbinX = hist_X -> GetNbinsX();
		nbinY = hist_Y -> GetNbinsX();
		binMX = hist_X -> GetBinCenter(nbinX);
		binMY = hist_Y -> GetBinCenter(nbinY);

		chX = (double(binMX)+1)/double(nbinX);
		chY = (double(binMY)+1)/double(nbinY);

		cout << "The maximum channel for X : " << binMX << endl;
		cout << "The maximum channel for Y : " << binMY << endl;

		cout << "The number of X bin : " << nbinX << endl;
		cout << "The number of Y bin : " << nbinY << endl;

		cout << "channel per bin for X : " << chX << endl;
		cout << "channel per bin for Y : " << chY << endl;
	}
}

void STAR::SETBIN()
{
	nbinX = 4096;
	nbinY = 4096;
	binMX = nbinX*chX;
	binMY = nbinY*chY;

	hist_Tot = new TH2D("hist", "", nbinX, 0, binMX, nbinY, 0, binMY);

	UShort_t *temp1;
	temp1 = (UShort_t *) malloc(sizeof(short) *4096);

	UInt_t *temp2;
	temp2 = (UInt_t *) malloc(sizeof(int) *4096);

	for (Int_t i = 0; i < 4096; i++)
	{
		if (filesize == 32*1024*1024)	fread(temp1, 2, 4096, read);
		if (filesize == 64*1024*1024)	fread(temp2, 4, 4096, read);
		for (Int_t j = 0; j < 4096; j++)
		{
			if (filesize == 32*1024*1024)	hist_Tot -> SetBinContent(i+1, j+1, temp1[j]);
			if (filesize == 64*1024*1024)	hist_Tot -> SetBinContent(i+1, j+1, temp2[j]);
		}
	}

	hist_X = hist_Tot -> ProjectionX("pro_X");
	hist_Y = hist_Tot -> ProjectionY("pro_Y");
	free(temp1);
	free(temp2);

//	frame->DestroySubwindows();

	cout << "The maximum channel for X : " << binMX << endl;
	cout << "The maximum channel for Y : " << binMY << endl;

	cout << "The number of X bin : " << nbinX << endl;
	cout << "The number of Y bin : " << nbinY << endl;

	cout << "channel per bin for X : " << chX << endl;
	cout << "channel per bin for Y : " << chY << endl;

	binconfirm = true;

	frame->UnmapWindow();
}

void STAR::SetXBin(const Char_t *value)
{
	chX = atof(value);
}

void STAR::SetYBin(const Char_t *value)
{
	chY = atof(value);
}

void STAR::FindPeaks(TCanvas* cvs, TH1D* hist)
{
	TSpectrum* spec = new TSpectrum();

	Int_t nb = hist->GetNbinsX();
	Double_t mx = hist->GetXaxis()->GetXmax();
	Double_t chpx = nb/mx;
	Double_t source[nb], dest[nb];

	if (chpx <= 1)
	{
//		cout << "High" << endl;
		for (Int_t i = 0; i < nb; i++)	source[i] = hist->GetBinContent(i+1);
		spec->SearchHighRes(source, dest, nb, 1, 2, kTRUE, 5, kTRUE, 3);
	}

	if (1 < chpx && chpx < 5)
	{
//		cout << "Normal" << endl;
		spec->Search(hist, 0.7, "goff", 0.005);
	}

	if (chpx >= 5)
	{
//		cout << "Low" << endl;
		spec->Search(hist, 0.4, "goff", 0.01);
	}

	Double_t *xpeaks = spec->GetPositionX();

	cvs->cd();
	TLatex temp;
	temp.SetTextAlign(12);
	temp.SetTextSize(0.05);
	temp.SetTextFont(132);
	temp.SetTextColor(2);
	temp.SetTextAngle(90);
	for (Int_t i = 0; i < spec->GetNPeaks(); i++)
	{
		temp.DrawLatex(xpeaks[i], hist->GetBinContent(int(xpeaks[i]*chpx+1)), Form("%d", int(xpeaks[i])));
	}
//	delete spec;
//	delete xpeaks;
}

void STAR::reset()
{
    gatevalueX.clear();
    gatevalueY.clear();
    cout << "gate information has been deleted." << endl;
	if (gate1 != nullptr)	delete gate1;
	if (gate2 != nullptr)	delete gate2;
	if (bgl1 != nullptr)	delete bgl1;
	if (bgl2 != nullptr)	delete bgl2;
	if (bgr1 != nullptr)	delete bgr1;
	if (bgr2 != nullptr)	delete bgr2;
}

void STAR::GetCoorX(Int_t event, Int_t px, Int_t, TObject *)
{
    TCanvas *c = (TCanvas *) gTQSender;
    TPad *pad = (TPad *) c->GetSelectedPad();
    if (!pad) return;
    if (event == kButton1Double)
    {
        Double_t ex = pad->AbsPixeltoX(px);
//        x = pad->PadtoX(x);
		Int_t x = ex/chX;
        gatevalueX.push_back(x);
        if (gatevalueX.size() == 1)
        {
            //cout << "Starting point of gate : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 2)
        {
            //cout << "End point of gate : " << x << endl;
            //cout << "If you want to use 'NETAREA', please click 'NETAREA' button." << endl;
            //cout << "If you want to use 'GATE' or 'DECAYGATE', please keep setting the background condition." << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 3)
        {
            //cout << "Starting point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 4)
        {
            //cout << "End point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 5)
        {
            //cout << "Starting point of right sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueX.size() == 6)
        {
            //cout << "End point of right sided bg : " << x << endl;
            //cout << "If you want to set the gate with above information, please click 'GATE' for gg coincidence, 'DECAY GATE' for decay curve." << endl;
            //cout << "If you want to set the gate condition again, just double click on the canvas." << endl;
            DrawInfo();
        }
        
        if (gatevalueX.size() > 6)
        {
            //cout << "Error : overflow. gate information has been deleted." << endl;
            gatevalueX.clear();
			delete gate1;
			delete gate2;
			delete bgl1;
			delete bgl2;
			delete bgr1;
			delete bgr2;
			cvs1 -> Modified();
			cvs1 -> Update();
			cvs2 -> Modified();
			cvs2 -> Update();
		}
    }
}


void STAR::GetCoorY(Int_t event, Int_t px, Int_t, TObject *)
{
    TCanvas *c = (TCanvas *) gTQSender;
    TPad *pad = (TPad *) c->GetSelectedPad();
    if (!pad) return;
    if (event == kButton1Double)
    {
        Double_t ex = pad->AbsPixeltoX(px);
//        x = pad->PadtoX(x);
		Int_t x = ex/chY;
        gatevalueY.push_back(x);
        if (gatevalueY.size() == 1)
        {
            //cout << "Starting point of gate : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 2)
        {
            //cout << "End point of gate : " << x << endl;
            //cout << "If you want to use 'NETAREA', please click 'NETAREA' button." << endl;
            //cout << "If you want to use 'GATE' or 'DECAYGATE', please keep setting the background condition." << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 3)
        {
            //cout << "Starting point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 4)
        {
            //cout << "End point of left sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 5)
        {
            //cout << "Starting point of right sided bg : " << x << endl;
            DrawInfo();
        }
        if (gatevalueY.size() == 6)
        {
            //cout << "End point of right sided bg : " << x << endl;
            //cout << "If you want to set the gate with above information, please click 'GATE' for gg coincidence, 'DECAY GATE' for decay curve." << endl;
            //cout << "If you want to set the gate condition again, just double click on the canvas." << endl;
            DrawInfo();
        }
        
        if (gatevalueY.size() > 6)
        {
            //cout << "Error : overflow. gate information has been deleted." << endl;
			gatevalueY.clear();
			delete gate1;
			delete gate2;
			delete bgl1;
			delete bgl2;
			delete bgr1;
			delete bgr2;
			cvs1 -> Modified();
			cvs1 -> Update();
			cvs2 -> Modified();
			cvs2 -> Update();
        }
    }
}

void STAR::GetCoorY2(Int_t event, Int_t px, Int_t, TObject *)
{
    TCanvas *c = (TCanvas *) gTQSender;
    TPad *pad = (TPad *) c->GetSelectedPad();
    if (!pad) return;
    if (event == kButton1Double)
    {
        Int_t ex = pad->AbsPixeltoX(px);
//        x = pad->PadtoX(x);
		Int_t x = ex/chY;
        gatevalueY.push_back(x);
        if (gatevalueY.size() == 1)
        {
            //cout << "Starting point of gate : " << x << endl;
            DrawInfo2();
        }
        if (gatevalueY.size() == 2)
        {
            //cout << "End point of gate : " << x << endl;
            //cout << "If you want to use 'NETAREA', please click 'NETAREA' button." << endl;
            DrawInfo2();
        }
       
        if (gatevalueY.size() > 2)
        {
            //cout << "Error : overflow. gate information has been deleted." << endl;
			gatevalueY.clear();
			delete gate1;
			delete gate2;
			cvs5 -> Modified();
			cvs5 -> Update();
        }
    }
}

void STAR::DrawInfo()
{
    if (gatevalueX.size() == 1)
    {
        cvs1 -> cd();
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %.01f", gatevalueX[0]*chX));
        
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 2)
    {
        cvs1 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %.01f", gatevalueX[1]*chX));
        gate2 -> SetNDC();
        gate2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 3)
    {
        cvs1 -> cd();
        bgl1 = new TLatex(0.2, 0.7, Form("#color[2]{BGL1 : %.01f}", gatevalueX[2]*chX));
        bgl1 -> SetNDC();
        bgl1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 4)
    {
        cvs1 -> cd();
        bgl2 = new TLatex(0.2, 0.65, Form("#color[2]{BGL2 : %.01f}", gatevalueX[3]*chX));
        bgl2 -> SetNDC();
        bgl2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 5)
    {
        cvs1 -> cd();
        bgr1 = new TLatex(0.2, 0.6, Form("#color[4]{BGR1 : %.01f}", gatevalueX[4]*chX));
        bgr1 -> SetNDC();
        bgr1 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    if (gatevalueX.size() == 6)
    {
        cvs1 -> cd();
        bgr2 = new TLatex(0.2, 0.55, Form("#color[4]{BGR2 : %.01f}", gatevalueX[5]*chX));
        bgr2 -> SetNDC();
        bgr2 -> Draw("same");
        cvs1 -> Modified();
        cvs1 -> Update();
    }
    
    if (gatevalueY.size() == 1)
    {
        cvs2 -> cd();
        
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %.01f", gatevalueY[0]*chY));
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 2)
    {
        cvs2 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %.01f", gatevalueY[1]*chY));
        gate2 -> SetNDC();
        gate2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 3)
    {
        cvs2 -> cd();
        bgl1 = new TLatex(0.2, 0.7, Form("#color[2]{BGL1 : %.01f}", gatevalueY[2]*chY));
        bgl1 -> SetNDC();
        bgl1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 4)
    {
        cvs2 -> cd();
        bgl2 = new TLatex(0.2, 0.65, Form("#color[2]{BGL2 : %.01f}", gatevalueY[3]*chY));
        bgl2 -> SetNDC();
        bgl2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 5)
    {
        cvs2 -> cd();
        bgr1 = new TLatex(0.2, 0.6, Form("#color[4]{BGR1 : %.01f}", gatevalueY[4]*chY));
        bgr1 -> SetNDC();
        bgr1 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    if (gatevalueY.size() == 6)
    {
        cvs2 -> cd();
        bgr2 = new TLatex(0.2, 0.55, Form("#color[4]{BGR2 : %.01f}", gatevalueY[5]*chY));
        bgr2 -> SetNDC();
        bgr2 -> Draw("same");
        cvs2 -> Modified();
        cvs2 -> Update();
    }
    
}

void STAR::DrawInfo2()
{
    
    if (gatevalueY.size() == 1)
    {
        cvs5 -> cd();
        
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %.01f", gatevalueY[0]*chY));
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs5 -> Modified();
        cvs5 -> Update();
    }
    if (gatevalueY.size() == 2)
    {
        cvs5 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %.01f", gatevalueY[1]*chY));
        gate2 -> SetNDC();
        gate2 -> Draw("same");
        cvs5 -> Modified();
        cvs5 -> Update();
    }
     
}

void STAR::intro()
{
    cout << "-----------------------------STARWARE(SpecTroscopy Analysis for gamma-Ray softWARE)---------------------------------" << endl;
    cout << "------------------------------------------Byul means 'star' in Korean.----------------------------------------------" << endl;
    cout << "---------------------------------Gamma-ray Spectroscopy Analysis Tool v2.0.1----------------------------------------" << endl;
    cout << "The Data analysis from coincidence event matrices." << endl;
    cout << "Made by Byul Moon(B.Moon) from Korea University" << endl;
    cout << "Since Jan. 2016." << endl;
    cout << "Latest Update : Feb. 2018." << endl;
} 

