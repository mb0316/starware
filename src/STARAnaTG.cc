/***********************************************************************************
***************************STARWARE CLASS SOURCE FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 10.Aug.2017, ver.1.1
Copyright. 2017. B. Moon
***********************************************************************************/
#include "TF1.h"
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
#include "STARAnaTG.h"
#include "TObject.h"


using namespace std;

void STARAnaTG::Htimegate(TH2D *hist_Tot, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &start, Int_t &end)
{
	if (hist_TY != nullptr)	delete hist_TY;
    if (timeaxis1 == 0 && timeaxis2 == 1)
    {
        hist_TY = hist_Tot -> ProjectionY("Pro_Y_time", start, end, ""); // singles spectrum with the time interval
		Double_t chbin = (hist_Tot->GetXaxis()->GetXmax())/(hist_Tot->GetNbinsX());
		cout << chbin << endl;

        cout << "Input the start value of the gate : " << int(start*chbin)+1 << endl; //gate start
        cout << "Input the end value of the gate : " << int(end*chbin)+1 << endl; //gate end
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dto%d_spectrum.root", direc.Data(), int(start*chbin)+1, int(end*chbin)+1), "RECREATE");
        out -> cd();
        hist_TY -> Write();
        out -> Close();
        cout << int(start*chbin)+1 << "to" << int(end*chbin)+1 << "_spectrum.root outfile has been created." << endl;
		delete out;
    }
    if (timeaxis1 == 1 && timeaxis2 == 0)
    {
        hist_TY = hist_Tot -> ProjectionX("Pro_X_time", start, end, ""); // singles spectrum with the time interval
		Double_t chbin = (hist_Tot->GetYaxis()->GetXmax())/(hist_Tot->GetNbinsY());

		cout << chbin << endl;
        cout << "Input the start value of the gate : " << int(start*chbin)+1 << endl; //gate start
        cout << "Input the end value of the gate : " << int(end*chbin)+1 << endl; //gate end
        
        // saving the result data
        TFile* out = new TFile(Form("%s%dto%d_spectrum.root", direc.Data(), int(start*chbin)+1, int(end*chbin)+1), "RECREATE");
        out -> cd();
        hist_TY -> Write();
        out -> Close();
        cout << int(start*chbin)+1 << "to" << int(end*chbin)+1 << "_spectrum.root outfile has been created." << endl;
		delete out;
    }
    if ((timeaxis1 == 0 && timeaxis2 == 0) || (timeaxis1 == 1 && timeaxis2 == 1))
    {
        cout << "Error : The time axis is not properly setted. Please check again." << endl;
        hist_TY = new TH1D();
    }
    
}

void STARAnaTG::Hnetarea(TH2D *hist_Tot, Int_t iden, Int_t start, Int_t end, TCanvas *tempcvs, TString &openFile)
{
    
	cout << start << " " << end << endl;

	if (hist_N != nullptr)	delete hist_N;

	if (openFile.Length() == 0)
	{
		cout << "The efficiency data has not been loaded. The netarea will be calculated without an efficiency calibration." << endl;    

		if (iden == 0)
		{
			hist_N = hist_Tot -> ProjectionX("Pro_X_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev;
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);

			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}

		if (iden == 1)
		{
			hist_N = hist_Tot -> ProjectionY("Pro_Y_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev;
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}
	}

	if (openFile.Length() >= 1)
	{
		if (iden == 0)
		{
			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get(eff_read->GetListOfKeys()->At(0)->GetName());

			hist_N = hist_Tot -> ProjectionX("Pro_X_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
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
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}

		if (iden == 1)
		{
			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get(eff_read->GetListOfKeys()->At(0)->GetName());

			hist_N = hist_Tot -> ProjectionY("Pro_Y_net1");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
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
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}
	}
}

void STARAnaTG::Hnetarea2(TH2D *hist_Tot, Int_t iden, Int_t start, Int_t end, TCanvas *tempcvs,TString &openFile, Int_t &tstart, Int_t &tend)
{
	if (hist_N != nullptr)	delete hist_N;
 
	if (openFile.Length() == 0)
	{
		cout << "The efficiency data has not been loaded. The netarea will be calculated without an efficiency calibration." << endl;    

		if (iden == 0)
		{
			hist_N = hist_Tot -> ProjectionX("Pro_X_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev;
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}

		if (iden == 1)
		{
			hist_N = hist_Tot -> ProjectionY("Pro_Y_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
			ampl = hist_N -> GetMaximum();
			gaussian -> SetParameters(ampl, peak, dev, -1, 0);
			hist_N -> Fit(gaussian, "MQN", "", start, end);
			peaks = gaussian -> GetParameter(1);
			peakerror = gaussian -> GetParError(1);
			ampl = gaussian -> GetParameter(0);
			dev = gaussian -> GetParameter(2);
			amplerror = (gaussian -> GetParError(0))/ampl;
			deverror = (gaussian -> GetParError(2))/dev;
			netcount = sqrt(2*pi)*ampl*dev;
			neterror = sqrt(amplerror*amplerror + deverror*deverror)*netcount;
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}
	}

	if (openFile.Length() >= 1)
	{
		if (iden == 0)
		{
			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get(eff_read->GetListOfKeys()->At(0)->GetName());

			hist_N = hist_Tot -> ProjectionX("Pro_X_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
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
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}

		if (iden == 1)
		{
			//loading the efficiency data
			TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
			TF1* fcn = (TF1*) eff_read -> Get(eff_read->GetListOfKeys()->At(0)->GetName());

			hist_N = hist_Tot -> ProjectionY("Pro_Y_net2", tstart, tend, "");

			//algorithm for the calculation of the netarea
			Double_t peaks;
			Double_t netcount;
			Double_t neterror;
			Double_t peakerrors;
			Double_t peak, ampl, peakerror, amplerror, deverror;
			Double_t dev = 1.0;
			TF1* gaussian = new TF1("gaussian", "gaus(0) + [3]*x + [4]", start, end);
			Double_t pi = TMath::Pi();
			hist_N -> GetXaxis() -> SetRangeUser(start-10, end+10);
			peak = hist_N->GetBinCenter(hist_N-> GetMaximumBin());
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
			peakerrors = sqrt(peakerror*peakerror + dev*dev/netcount);
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;

			// showing the result
			TF1* gaussian_fit = new TF1("gau", "gaus(0)", start, end);
			TF1* back_fit = new TF1("back_fit", "[0]*x + [1]", start, end);

			gaussian_fit -> SetParameters(gaussian -> GetParameter(0), gaussian -> GetParameter(1), gaussian -> GetParameter(2));
			back_fit -> SetParameters(gaussian -> GetParameter(3), gaussian -> GetParameter(4));

			tempcvs -> cd();
			hist_N -> Draw();
			gaussian -> Draw("same");
			gaussian_fit -> Draw("same");
			back_fit -> Draw("same");

			gaussian_fit ->SetLineStyle(2);
			gaussian_fit ->SetLineColor(4);
			back_fit ->SetLineStyle(5);
			back_fit ->SetLineColor(6);


			// represent total results for the request
			cout << peaks << " +- " << peakerrors << " keV : "  << netcount << " +- " << neterror << endl;
		}
	}
}
/*
void STARAnaTG::Htimegrow(TString &openFile, Int_t &timeaxis1, Int_t &timeaxis2, Int_t &peak)
{
	if (openFile.Length() == 0)
	{
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
			Double_t pi = TMath::Pi();
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
				netcount[i] = sqrt(2*pi)*ampl*dev;
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

	if (openFile >= 1)
	{
		// loading the efficiency data
		TFile* eff_read = new TFile(Form("%s", openFile.Data()), "READ"); //eff_data_gc.root : for gecluster, eff_data_add.root : for addback
		TF1* fcn = (TF1*) eff_read -> Get(eff_read->GetListOfKeys()->At(0)->GetName());


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
			Double_t pi = TMath::Pi();
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
}
*/
