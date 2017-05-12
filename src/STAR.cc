/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
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

using namespace std;

void STAR::main(TString &directory, TString &openFile)
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

void STAR::reset()
{
    gatevalueX.clear();
    gatevalueY.clear();
    cout << "gate information has been deleted." << endl;
	if (gate1 != nullptr)
	{
		gate1 -> Delete();
		gate1 = nullptr;
	}
	if (gate2 != nullptr)
	{
		gate2 -> Delete();
		gate2 = nullptr;
	}
	if (bgl1 != nullptr)
	{
		bgl1 -> Delete();
		bgl1 = nullptr;
	}
	if (bgl2 != nullptr)
	{
		bgl2 -> Delete();
		bgl2 = nullptr;
	}
	if (bgr1 != nullptr)
	{
		bgr1 -> Delete();
		bgr1 = nullptr;
	}
	if (bgr2 != nullptr)
	{
		bgr2 -> Delete();
		bgr2 = nullptr;
	}
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

void STAR::intro()
{
    cout << "-----------------------------STARWARE(SpecTroscopy Analysis for gamma-Ray softWARE)---------------------------------" << endl;
    cout << "------------------------------------------Byul means 'star' in Korean.----------------------------------------------" << endl;
    cout << "----------------------------------Gamma-ray Spectroscopy Analysis Tool Ver.1.2--------------------------------------" << endl;
    cout << "The Data analysis from coincidence event matrices." << endl;
    cout << "Made by Byul Moon(B.Moon) from Korea University" << endl;
    cout << "Since Jan. 2016." << endl;
    cout << "Latest Update : May. 2017." << endl;
} 

void STAR::manual()
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

