/***********************************************************************************
***************************STARWARE CLASS HEADER FILE*******************************
Made by Byul Moon from Korea University
All functions are contained for STARWARE.
Last refine : 12.May.2017, ver.1.0
Copyright. 2017. B. Moon
***********************************************************************************/

#ifndef STAR_H
#define STAR_H

#include "TH2S.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"
#include <RQ_OBJECT.h>
#include <vector>
#include "Rtypes.h"
#include "TObject.h"
#include "TString.h"

using namespace std;


class STAR
{
	RQ_OBJECT("STARAna")
	public :
		TH2S* hist_Tot = nullptr;				//2D histogram built by MAT data
		TString direc;				//Directory of the current work in the string form
		vector<int> gatevalueX;		//Gate value for x axis; 0 : gate_start, 1 : gate_end, 2 : left_bg_start, 3 : left_bg_end, 4 : right_bg_start, 5 : right_bg_end;
		vector<int> gatevalueY;		//Gate value for x axis; 0 : gate_start, 1 : gate_end, 2 : left_bg_start, 3 : left_bg_end, 4 : right_bg_start, 5 : right_bg_end;

		void reset();												//Reset all information
		void GetCoorX(Int_t event, Int_t px, Int_t, TObject *);		//Get x value from the x projected histogram
		void GetCoorY(Int_t event, Int_t px, Int_t, TObject *);		//Get x value from the y projected histogram
		void DrawInfo();											//Represent gate information on the canvas
		void intro(); 												//Print out the intro information
		void main(TString &directory, TString &openFile);			//Main function for the program
//		void manual();												//Print out the simple manual

	protected :
		TH1D* hist_X = nullptr;		//x projected histogram
		TH1D* hist_Y = nullptr;		//y projected histogram
		TCanvas* cvs1 = nullptr;	//A canvas for x projected histogram
		TCanvas* cvs2 = nullptr;	//A canvas for y projected histogram
		TLatex* gate1 = nullptr;	
		TLatex* gate2 = nullptr;
		TLatex* bgl1 = nullptr;
		TLatex* bgl2 = nullptr;
		TLatex* bgr1 = nullptr;
		TLatex* bgr2 = nullptr;
};
#endif

