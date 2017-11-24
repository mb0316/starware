/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 16.Aug.2017, ver.1.2
Copyright. 2017. B. Moon
***********************************************************************************/
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
		cout << "Selected data filee : MAT type!!" << endl;
		struct stat file_stat;
		stat(Form("%s%s", directory.Data(), openFile.Data()), &file_stat);
		ULong64_t filesize = (ULong64_t) file_stat.st_size;

		FILE *read;
		read = fopen(Form("%s%s", directory.Data(), openFile.Data()), "rb");

		direc = directory;

		hist_Tot = new TH2D("hist", "", 4096, 0, 4096, 4096, 0, 4096);

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
	}

	if (filetype == "root")
	{
		cout << "Selected data filee : ROOT type!!" << endl;
		TFile* file = new TFile(Form("%s%s", directory.Data(), openFile.Data()), "READ");
		hist_Tot = (TH2D*) file -> Get(file->GetListOfKeys()->At(0)->GetName());
		hist_X = hist_Tot -> ProjectionX("pro_X");
		hist_Y = hist_Tot -> ProjectionY("pro_Y");
	}

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
        Int_t x = pad->AbsPixeltoX(px);
        x = pad->PadtoX(x);
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
        Int_t x = pad->AbsPixeltoX(px);
        x = pad->PadtoX(x);
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
        Int_t x = pad->AbsPixeltoX(px);
        x = pad->PadtoX(x);
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

void STAR::DrawInfo2()
{
    
    if (gatevalueY.size() == 1)
    {
        cvs5 -> cd();
        
        gate1 = new TLatex(0.2, 0.8, Form("Gate1 : %d", gatevalueY[0]));
        gate1 -> SetNDC();
        gate1 -> Draw("same");
        cvs5 -> Modified();
        cvs5 -> Update();
    }
    if (gatevalueY.size() == 2)
    {
        cvs5 -> cd();
        gate2 = new TLatex(0.2, 0.75, Form("Gate2 : %d", gatevalueY[1]));
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
    cout << "-----------------------------------Gamma-ray Spectroscopy Analysis Tool v1.4----------------------------------------" << endl;
    cout << "The Data analysis from coincidence event matrices." << endl;
    cout << "Made by Byul Moon(B.Moon) from Korea University" << endl;
    cout << "Since Jan. 2016." << endl;
    cout << "Latest Update : Oct. 2017." << endl;
} 

