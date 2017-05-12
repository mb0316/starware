// Mainframe macro generated from application: /Users/MoonByul/root/bin/root.exe
// By ROOT version 6.08/00 on 2016-12-20 20:20:27
/***********************************************************************************
*************************STARWARE GUI CONSTRUCTOR FILE******************************
Made by Byul Moon from Korea University
GUI constructor for STARWARE program.
Last refine : 07.May.2017, ver.1.2
Copyright 2017. B. Moon
***********************************************************************************/
#include "TGDockableFrame.h"
#include "TGMenu.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGHtml.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGFSContainer.h"
#include "TGuiBldEditor.h"
#include "TGColorSelect.h"
#include "TGButton.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGView.h"
#include "TRootGuiBuilder.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGSplitter.h"
#include "TGTextView.h"
#include "TGStatusBar.h"
#include "TGListTree.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolTip.h"
#include "TGToolBar.h"
#include "TGuiBldDragManager.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLabel.h"
#include "TGFileDialog.h"
#include "TRootHelpDialog.h"

#include "Riostream.h"
#include <stdio.h>
#include <vector>
#include "TStyle.h"
#include "TCanvas.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <arpa/inet.h>
#include <algorithm>

#include "TApplication.h"
#include "TSystem.h"
#include "TGClient.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "STARGui.h"
#include "STAR.h"
#include "STARAnaGG.h"
#include "STARAnaTG.h"
#include "STARAnaDC.h"
#include "STARAnaDis.h"
#include "STARCal.h"
#include "Rtypes.h"
#include "TString.h"


const char gAboutSTARWARE[] = "\
			STARWARE\n\
STARWARE(SpecTroscopy Analysis for gamma-Ray softWARE)\n\
is an analysis tool dedicated for gamma-ray spectroscopy based on ROOT.\n\
This program operates with a GUI system.\n\
STARWARE only accepts the data format with ~.mat.\n\
\n\
Since Jan. 2016.\n\
Current Version : Beta ver.1.2\n\
Last Update : 8.Mar.2017.\n\
By Byul Moon from Korea University\n\
alpha ver.1.2 Update News 1 : The decaygate function now contains the elimination of the background.\n\
alpha ver.1.2 Update News 2 : The decaygate function now asks the degree of the data compression(the bin size).\n\
alpha ver.1.3 Update News 1 : The netarea function now uses the gaussian fitting to get the exact net area including the error.\n\
alpha ver.1.4 Update News 1 : The netarea function now does not remove the background by using TSpectrum. Instead, now the function fits the background with the linear function to remove the background.\n\
alpha ver.1.5 Update News 1 : This program now performs the efficiency calibration by using the external data file.\n\
alpha ver.2.0 Update News 1 : Now this program works with its own CLASS header file.\n\
alpha ver.2.1 Update News 1 : The timegrow function now works with the fit process not using TSpectrum anymore.\n\
alpha ver.3.0 Update News 1 : Now you can use the mouse double-click to set the gate condition. If you want to set the gate, please zoom in the spectrum and double-click the bin point.\n\
alpha ver.3.0 Update News 2 : Now this program works with RADWARE data foramt(.mat).\n\
alpha ver.3.1 Update News 1 : Now this program provides halflife measurement using gamma-rays.\n\
alpha ver.4.0 Update News 1 : Now this program is based on the GUI system.\n\
beta ver.1.0 Update News 1 (09.Jan.2017) : The interface for STARWARE is now fixed.\n\
beta ver.1.1 Update News 1 (22.Feb.2017) : The analysis for the half-life of the daughter nucleus has been added.\n\
beta ver.1.2 Update News 1 (08.Mar.2017) : The logft calculation has been added.\n\
beta ver.1.2 Update News 2 (13.Mar.2017) : The reduced matrix element calculation has been added.\n\
";

const char gCOPYRIGHT[] = "\
			STARWARE COPYRIGHT\n\
STARWARE is made by Byul Moon from Korea University.\n\
\n\
Copyright 2017. B. Moon\n\
";

const char gMANUAL[] ="\
			STARWARE MANUAL\n\
To be announced.\n\
";

const char gCONTACT[] ="\
			STARWARE CONTACT INFORMATION\n\
Please contact via the following e-mail address.\n\
mb0316@nuclear.korea.ac.kr\n\
";


enum EMyMessageTypes
{
	M_FILE_OPEN,
	M_FILE_EXIT,
	M_HELP_ABOUT,
	M_HELP_COPYRIGHT,
	M_HELP_MANUAL,
	M_HELP_CONTACT
};

using namespace std;
STARGui::STARGui()
{
	gStyle -> SetPadLeftMargin(0.13);
	gStyle -> SetPadRightMargin(0.06);
	gStyle -> SetPadTopMargin(0.15);
	gStyle -> SetPadBottomMargin(0.15);
	gStyle -> SetTitleOffset(1.0, "x");
	gStyle -> SetTitleOffset(0.8, "y");
	gStyle -> SetTitleOffset(0.5, "z");
	gStyle -> SetTextFont(132);
	gStyle -> SetTextSize(0.070);
	gStyle -> SetTitleSize(0.07, "");
	gStyle -> SetTitleSize(0.07, "x");
	gStyle -> SetTitleSize(0.07, "y");
	gStyle -> SetTitleSize(0.07, "z");
	gStyle -> SetLabelSize(0.07, "x");
	gStyle -> SetLabelSize(0.07, "y");
	gStyle -> SetLabelSize(0.07, "z");
	gStyle -> SetTitleFont(132, "");
	gStyle -> SetTitleFont(132, "x");
	gStyle -> SetTitleFont(132, "y");
	gStyle -> SetTitleFont(132, "z");
	gStyle -> SetLabelFont(132, "x");
	gStyle -> SetLabelFont(132, "y");
	gStyle -> SetLabelFont(132, "z");
	gStyle -> SetOptStat(0);

    // main frame
    TGMainFrame *fMainFrame1073 = new TGMainFrame(gClient->GetRoot(),1200,650,kMainFrame | kVerticalFrame);
    fMainFrame1073->SetName("STARWARE");
    fMainFrame1073->SetLayoutBroken(kTRUE);

	TGMenuBar* fMenuBar = new TGMenuBar(fMainFrame1073, 1200, 25, kHorizontalFrame);
	TGPopupMenu* fMenuFile = new TGPopupMenu(gClient->GetRoot());
	fMenuFile->AddEntry(" &Open", M_FILE_OPEN, 0, gClient->GetPicture("bld_open.png")); 
	fMenuFile->AddSeparator();
	fMenuFile->AddEntry(" E&xit", M_FILE_EXIT, 0, gClient->GetPicture("bld_exit.png"));
	fMenuFile->Connect("Activated(Int_t)", "STARGui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&File", fMenuFile, new TGLayoutHints(kLHintsTop|kLHintsLeft, 0, 4, 0, 0));

	TGPopupMenu* fMenuHelp = new TGPopupMenu(gClient->GetRoot());
	fMenuHelp->AddEntry(" &About STARWARE", M_HELP_ABOUT, 0, gClient->GetPicture("about.xpm"));
	fMenuHelp->AddEntry(" &STARWARE Copyright", M_HELP_COPYRIGHT);
	fMenuHelp->AddEntry(" &STARWARE Manual", M_HELP_MANUAL);
	fMenuHelp->AddEntry(" &STARWARE Contact Info.", M_HELP_CONTACT);
	fMenuHelp->Connect("Activated(Int_t)", "STARGui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsLeft));

	fMainFrame1073 -> AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));
	fMenuBar->MoveResize(0,0,1200,25);

	Int_t parts[] = {45, 15, 10, 30};
	fStatusBar = new TGStatusBar(fMainFrame1073, 50, 10, kVerticalFrame);
	fStatusBar->SetParts(parts, 4);
	fStatusBar->Draw3DCorner(kFALSE);
	fMainFrame1073->AddFrame(fStatusBar, new TGLayoutHints(kLHintsExpandX, 0, 0, 10, 0));
	fStatusBar->MoveResize(20,590,1000,20);

    TGLabel *lCOPY = new TGLabel(fMainFrame1073, "Copyright 2017. B. Moon");
    lCOPY-> SetTextJustify(kTextLeft);
    lCOPY-> SetMargins(0, 0, 0, 0);
    lCOPY-> SetWrapLength(-1);
    fMainFrame1073 -> AddFrame(lCOPY, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lCOPY-> MoveResize(1050, 590, 200, 20);

    // tab widget
    TGTab *fTab1 = new TGTab(fMainFrame1073, 1180, 550);

    // container of "Tab1"
    TGCompositeFrame *fCompositeFrame1;
    fCompositeFrame1 = fTab1 -> AddTab("Projected Spectra");
    fCompositeFrame1 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame1));
    fCompositeFrame1 ->SetLayoutBroken(kTRUE);
    
    TGTextButton *GATE = new TGTextButton(fCompositeFrame1,"GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    GATE -> Connect("Clicked()", "STARGui", this, "gate()");
    GATE->SetTextJustify(36);
    GATE->SetMargins(0,0,0,0);
    GATE->SetWrapLength(-1);
    GATE->Resize(100,35);
    fCompositeFrame1->AddFrame(GATE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    GATE->MoveResize(1030,30,100,35);
    
    TGLabel *lTIMEBIN = new TGLabel(fCompositeFrame1, "Input the time bin size.");
    lTIMEBIN -> SetTextJustify(kTextLeft);
    lTIMEBIN -> SetMargins(0, 0, 0, 0);
    lTIMEBIN -> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lTIMEBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lTIMEBIN -> MoveResize(1030, 75, 170, 20);
    
    TGNumberEntryField *fTIMEBIN = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fTIMEBIN->MoveResize(1030,100,100,20);
    fCompositeFrame1->AddFrame(fTIMEBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTIMEBIN -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetTimeBin(const Char_t *)");
    
    TGTextButton *DECAYGATE = new TGTextButton(fCompositeFrame1,"DECAY GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    DECAYGATE -> Connect("Clicked()", "STARGui", this, "decaygate()");
    DECAYGATE->SetTextJustify(36);
    DECAYGATE->SetMargins(0,0,0,0);
    DECAYGATE->SetWrapLength(-1);
    DECAYGATE->Resize(100,35);
    fCompositeFrame1->AddFrame(DECAYGATE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    DECAYGATE->MoveResize(1030,125,100,35);
    
    TGTextButton *NETAREA = new TGTextButton(fCompositeFrame1,"NET AREA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    NETAREA -> Connect("Clicked()", "STARGui", this, "netarea()");
    NETAREA->SetTextJustify(36);
    NETAREA->SetMargins(0,0,0,0);
    NETAREA->SetWrapLength(-1);
    NETAREA->Resize(100,35);
    fCompositeFrame1->AddFrame(NETAREA, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    NETAREA->MoveResize(1030,170,100,35);
    
    TGLabel *lSTARTBIN = new TGLabel(fCompositeFrame1, "Input the start time value.");
    lSTARTBIN -> SetTextJustify(kTextLeft);
    lSTARTBIN-> SetMargins(0, 0, 0, 0);
    lSTARTBIN-> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lSTARTBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lSTARTBIN-> MoveResize(1030, 215, 170, 20);
    
    TGNumberEntryField *fTSTARTBIN = new TGNumberEntryField(fCompositeFrame1, 1, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fTSTARTBIN->MoveResize(1030,240,100,20);
    fCompositeFrame1->AddFrame(fTSTARTBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTSTARTBIN -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetTimeStart(const Char_t *)");
    
    TGLabel *lENDBIN = new TGLabel(fCompositeFrame1, "Input the end time value.");
    lENDBIN -> SetTextJustify(kTextLeft);
    lENDBIN-> SetMargins(0, 0, 0, 0);
    lENDBIN-> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lENDBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lENDBIN-> MoveResize(1030, 265, 170, 20);
    
    TGNumberEntryField *fTENDBIN = new TGNumberEntryField(fCompositeFrame1, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fTENDBIN->MoveResize(1030,290,100,20);
    fCompositeFrame1->AddFrame(fTENDBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTENDBIN -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetTimeEnd(const Char_t *)");
    
    TGTextButton *TIMEGATE = new TGTextButton(fCompositeFrame1,"TIME GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TIMEGATE -> Connect("Clicked()", "STARGui", this, "timegate()");
    TIMEGATE->SetTextJustify(36);
    TIMEGATE->SetMargins(0,0,0,0);
    TIMEGATE->SetWrapLength(-1);
    TIMEGATE->Resize(100,35);
    fCompositeFrame1->AddFrame(TIMEGATE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TIMEGATE->MoveResize(1030,315,100,35);
    
    TGLabel *lTGROW = new TGLabel(fCompositeFrame1, "Input the peak value.");
    lTGROW -> SetTextJustify(kTextLeft);
    lTGROW-> SetMargins(0, 0, 0, 0);
    lTGROW-> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lTGROW, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lTGROW-> MoveResize(1030, 360, 170, 20);
    
    TGNumberEntryField *fTGROW = new TGNumberEntryField(fCompositeFrame1, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fTGROW->MoveResize(1030,385,100,20);
    fCompositeFrame1->AddFrame(fTGROW, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTGROW -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetTimeGrow(const Char_t *)");
    
    TGTextButton *TIMEGROW = new TGTextButton(fCompositeFrame1,"TIME GROW",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TIMEGROW -> Connect("Clicked()", "STARGui", this, "timegrow()");
    TIMEGROW->SetTextJustify(36);
    TIMEGROW->SetMargins(0,0,0,0);
    TIMEGROW->SetWrapLength(-1);
    TIMEGROW->Resize(100,35);
    fCompositeFrame1->AddFrame(TIMEGROW, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TIMEGROW->MoveResize(1030,410,100,35);

    TGLabel *lCheck = new TGLabel(fCompositeFrame1, "Axis for the time.");
    lCheck -> SetTextJustify(kTextLeft);
    lCheck-> SetMargins(0, 0, 0, 0);
    lCheck-> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lCheck, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lCheck-> MoveResize(1030, 455, 200, 20);
    
    TGCheckButton *fCheckTX = new TGCheckButton(fCompositeFrame1,"x");
    fCheckTX->Connect("Toggled(Bool_t)", "STARGui", this, "checktimetox(Bool_t)");
    fCheckTX->SetTextJustify(kTextLeft);
    fCheckTX->SetMargins(0,0,0,0);
    fCheckTX->SetWrapLength(-1);
    fCompositeFrame1->AddFrame(fCheckTX, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fCheckTX->Move(1030,485);
    
    TGCheckButton *fCheckTY = new TGCheckButton(fCompositeFrame1,"y");
    fCheckTY->Connect("Toggled(Bool_t)", "STARGui", this, "checktimetoy(Bool_t)");
    fCheckTY->SetTextJustify(kTextLeft);
    fCheckTY->SetMargins(0,0,0,0);
    fCheckTY->SetWrapLength(-1);
    fCompositeFrame1->AddFrame(fCheckTY, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fCheckTY->MoveResize(1080,485);
    
    // embedded canvas
    TRootEmbeddedCanvas *ProjectedSpectrum_X = new TRootEmbeddedCanvas(0,fCompositeFrame1,1000,250,kSunkenFrame);
    ProjectedSpectrum_X->SetName("ProjectedSpectrum_X");
    Int_t wProjectedSpectrum_X = ProjectedSpectrum_X->GetCanvasWindowId();
    cvs1 = new TCanvas("cvs1", 10, 10, wProjectedSpectrum_X);
    ProjectedSpectrum_X->AdoptCanvas(cvs1);
    fCompositeFrame1->AddFrame(ProjectedSpectrum_X, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    ProjectedSpectrum_X->MoveResize(10,10,1000,250);

    TRootEmbeddedCanvas *ProjectedSpectrum_Y = new TRootEmbeddedCanvas(0,fCompositeFrame1,1000,250,kSunkenFrame);
    ProjectedSpectrum_Y->SetName("ProjectedSpectrum_Y");
    Int_t wProjectedSpectrum = ProjectedSpectrum_Y->GetCanvasWindowId();
    cvs2 = new TCanvas("cvs2", 10, 10, wProjectedSpectrum);
    ProjectedSpectrum_Y->AdoptCanvas(cvs2);
    fCompositeFrame1->AddFrame(ProjectedSpectrum_Y, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    ProjectedSpectrum_Y->MoveResize(10,270,1000,250);

    // container of "Tab2"
    TGCompositeFrame *fCompositeFrame2;
    fCompositeFrame2 = fTab1 -> AddTab("Gated Spectrum");
    fCompositeFrame2 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame2));
    fCompositeFrame2 ->SetLayoutBroken(kTRUE);
        
    TGTextButton *OPENSPECTRUM = new TGTextButton(fCompositeFrame2,"OPEN SPEC.",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    OPENSPECTRUM -> Connect("Clicked()", "STARGui", this, "gatedspectrum()");
    OPENSPECTRUM->SetTextJustify(36);
    OPENSPECTRUM->SetMargins(0,0,0,0);
    OPENSPECTRUM->SetWrapLength(-1);
    OPENSPECTRUM->Resize(100,35);
    fCompositeFrame2->AddFrame(OPENSPECTRUM, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    OPENSPECTRUM->MoveResize(1050,300,100,35);
 
    // embedded canvas
    TRootEmbeddedCanvas *gated_spec = new TRootEmbeddedCanvas(0,fCompositeFrame2,1000,250,kSunkenFrame);
    gated_spec->SetName("Gated Spectrum");
    Int_t wgated_spec = gated_spec->GetCanvasWindowId();
    cvs3 = new TCanvas("cvs3", 10, 10, wgated_spec);
    cvs3 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    gated_spec->AdoptCanvas(cvs3);
    fCompositeFrame2->AddFrame(gated_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    gated_spec->MoveResize(10,10,1000,250);

    TRootEmbeddedCanvas *gated_decay = new TRootEmbeddedCanvas(0,fCompositeFrame2,1000,250,kSunkenFrame);
    gated_decay->SetName("Gated Decay Curve");
    Int_t wgated_decay = gated_decay->GetCanvasWindowId();
    cvs4 = new TCanvas("cvs4", 10, 10, wgated_decay);
    cvs4 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    gated_decay->AdoptCanvas(cvs4);
    fCompositeFrame2->AddFrame(gated_decay, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    gated_decay->MoveResize(10,270,1000,250);
   
    // container of "Tab3"
    TGCompositeFrame *fCompositeFrame3;
    fCompositeFrame3 = fTab1 -> AddTab("T.Gated Spectrum");
    fCompositeFrame3 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame3));
    fCompositeFrame3 ->SetLayoutBroken(kTRUE);
    
    TGLabel *lDFIRST = new TGLabel(fCompositeFrame3, "1st Spectrum");
    lDFIRST-> SetTextJustify(kTextLeft);
    lDFIRST-> SetMargins(0, 0, 0, 0);
    lDFIRST-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDFIRST, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDFIRST-> MoveResize(1050, 30, 100, 20);
    
    TGLabel *lDSTARTBIN1 = new TGLabel(fCompositeFrame3, "start");
    lDSTARTBIN1-> SetTextJustify(36);
    lDSTARTBIN1-> SetMargins(0, 0, 0, 0);
    lDSTARTBIN1-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDSTARTBIN1, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDSTARTBIN1-> MoveResize(1050, 55, 40, 20);
    
    TGLabel *lDENDBIN1 = new TGLabel(fCompositeFrame3, "end");
    lDENDBIN1-> SetTextJustify(36);
    lDENDBIN1-> SetMargins(0, 0, 0, 0);
    lDENDBIN1-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDENDBIN1, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDENDBIN1-> MoveResize(1100, 55, 40, 20);
    
    TGNumberEntryField *fDSTARTBIN1 = new TGNumberEntryField(fCompositeFrame3, 1, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fDSTARTBIN1->MoveResize(1050,80,40,20);
    fCompositeFrame3->AddFrame(fDSTARTBIN1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fDSTARTBIN1 -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetDiffStart1(const Char_t *)");
    
    TGNumberEntryField *fDENDBIN1 = new TGNumberEntryField(fCompositeFrame3, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fDENDBIN1->MoveResize(1100,80,40,20);
    fCompositeFrame3->AddFrame(fDENDBIN1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fDENDBIN1 -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetDiffEnd1(const Char_t *)");
    
    TGLabel *lDSECOND = new TGLabel(fCompositeFrame3, "2nd Spectrum");
    lDSECOND-> SetTextJustify(kTextLeft);
    lDSECOND-> SetMargins(0, 0, 0, 0);
    lDSECOND-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDSECOND, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDSECOND-> MoveResize(1050, 115, 100, 20);
    
    TGLabel *lDSTARTBIN2 = new TGLabel(fCompositeFrame3, "start");
    lDSTARTBIN2-> SetTextJustify(36);
    lDSTARTBIN2-> SetMargins(0, 0, 0, 0);
    lDSTARTBIN2-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDSTARTBIN2, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDSTARTBIN2-> MoveResize(1050, 140, 40, 20);
    
    TGLabel *lDENDBIN2 = new TGLabel(fCompositeFrame3, "end");
    lDENDBIN2-> SetTextJustify(36);
    lDENDBIN2-> SetMargins(0, 0, 0, 0);
    lDENDBIN2-> SetWrapLength(-1);
    fCompositeFrame3 -> AddFrame(lDENDBIN2, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDENDBIN2-> MoveResize(1100, 140, 40, 20);
    
    TGNumberEntryField *fDSTARTBIN2 = new TGNumberEntryField(fCompositeFrame3, 1, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fDSTARTBIN2->MoveResize(1050,165,40,20);
    fCompositeFrame3->AddFrame(fDSTARTBIN2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fDSTARTBIN2 -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetDiffStart2(const Char_t *)");
    
    TGNumberEntryField *fDENDBIN2 = new TGNumberEntryField(fCompositeFrame3, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fDENDBIN2->MoveResize(1100,165,40,20);
    fCompositeFrame3->AddFrame(fDENDBIN2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fDENDBIN2 -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetDiffEnd2(const Char_t *)");
    
    TGTextButton *TDIFF = new TGTextButton(fCompositeFrame3,"TIME DIFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TDIFF -> Connect("Clicked()", "STARGui", this, "timediff()");
    TDIFF->SetTextJustify(36);
    TDIFF->SetMargins(0,0,0,0);
    TDIFF->SetWrapLength(-1);
    TDIFF->Resize(100,35);
    fCompositeFrame3->AddFrame(TDIFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TDIFF->MoveResize(1050,190,100,35);
    
    TGTextButton *NETAREA2 = new TGTextButton(fCompositeFrame3,"NET AREA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    NETAREA2 -> Connect("Clicked()", "STARGui", this, "netarea2()");
    NETAREA2->SetTextJustify(36);
    NETAREA2->SetMargins(0,0,0,0);
    NETAREA2->SetWrapLength(-1);
    NETAREA2->Resize(100,35);
    fCompositeFrame3->AddFrame(NETAREA2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    NETAREA2->MoveResize(1050,250,100,35);
    
    TGTextButton *EFFOPEN = new TGTextButton(fCompositeFrame3,"EFF. OPEN",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    EFFOPEN -> Connect("Clicked()", "STARGui", this, "openeff()");
    EFFOPEN->SetTextJustify(36);
    EFFOPEN->SetMargins(0,0,0,0);
    EFFOPEN->SetWrapLength(-1);
    EFFOPEN->Resize(100,35);
    fCompositeFrame3->AddFrame(EFFOPEN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    EFFOPEN->MoveResize(1050,300,100,35);
    
    // embedded canvas
    TRootEmbeddedCanvas *tgated_spec = new TRootEmbeddedCanvas(0,fCompositeFrame3,1000,250,kSunkenFrame);
    tgated_spec->SetName("T.Gated Spectrum");
    Int_t wtgated_spec = tgated_spec->GetCanvasWindowId();
    cvs5 = new TCanvas("cvs5", 10, 10, wtgated_spec);
    tgated_spec->AdoptCanvas(cvs5);
    cvs5 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "GetCoorY(Int_t, Int_t, Int_t, TObject*)");
    cvs5 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    fCompositeFrame3->AddFrame(tgated_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    tgated_spec->MoveResize(10,10,1000,250);

    TRootEmbeddedCanvas *tdiff_spec = new TRootEmbeddedCanvas(0,fCompositeFrame3,1000,250,kSunkenFrame);
    tdiff_spec->SetName("Time Difference");
    Int_t wtdiff_spec = tdiff_spec->GetCanvasWindowId();
    cvs6 = new TCanvas("cvs6", 10, 10, wtdiff_spec);
    cvs6 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    tdiff_spec->AdoptCanvas(cvs6);
    fCompositeFrame3->AddFrame(tdiff_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    tdiff_spec->MoveResize(10,270,1000,250);
    
    // container of "Tab4"
    TGCompositeFrame *fCompositeFrame4;
    fCompositeFrame4 = fTab1 -> AddTab("Time Growing");
    fCompositeFrame4 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame4));
    fCompositeFrame4 ->SetLayoutBroken(kTRUE);
    
    // embedded canvas
    TRootEmbeddedCanvas *tgrow = new TRootEmbeddedCanvas(0,fCompositeFrame4,1000,500,kSunkenFrame);
    tgrow->SetName("Time Growing");
    Int_t wtgrow = tgrow->GetCanvasWindowId();
    cvs7 = new TCanvas("cvs7", 10, 10, wtgrow);
    tgrow->AdoptCanvas(cvs7);
    fCompositeFrame4->AddFrame(tgrow, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    tgrow->MoveResize(10,10,1000,500);
    
    // container of "Tab5"
    TGCompositeFrame *fCompositeFrame5;
    fCompositeFrame5 = fTab1 -> AddTab("Half-life Measurement");
    fCompositeFrame5 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame5));
    fCompositeFrame5 ->SetLayoutBroken(kTRUE);
    
    TGLabel *lHALF = new TGLabel(fCompositeFrame5, "Input the peak value.");
    lHALF -> SetTextJustify(kTextLeft);
    lHALF -> SetMargins(0, 0, 0, 0);
    lHALF -> SetWrapLength(-1);
    fCompositeFrame5 -> AddFrame(lHALF, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lHALF -> MoveResize(1020, 40, 170, 20);
    
    TGNumberEntryField *fSETPEAK = new TGNumberEntryField(fCompositeFrame5, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fSETPEAK->MoveResize(1020,65,40,20);
    fCompositeFrame5->AddFrame(fSETPEAK, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fSETPEAK -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetPeakValue(const Char_t *)");
    
    TGTextButton *TSETPEAK = new TGTextButton(fCompositeFrame5,"SET PEAK",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TSETPEAK -> Connect("Clicked()", "STARGui", this, "setpeaks()");
    TSETPEAK->SetTextJustify(36);
    TSETPEAK->SetMargins(0,0,0,0);
    TSETPEAK->SetWrapLength(-1);
    TSETPEAK->Resize(100,35);
    fCompositeFrame3->AddFrame(TSETPEAK, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TSETPEAK->MoveResize(1020,90,100,35);
    
    TGTextButton *TGETHALF = new TGTextButton(fCompositeFrame5,"GET HALFLIFE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TGETHALF-> Connect("Clicked()", "STARGui", this, "halflife()");
    TGETHALF->SetTextJustify(36);
    TGETHALF->SetMargins(0,0,0,0);
    TGETHALF->SetWrapLength(-1);
    TGETHALF->Resize(100,35);
    fCompositeFrame3->AddFrame(TGETHALF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TGETHALF->MoveResize(1020,130,100,35);
 
	TGLabel *lCheck_half = new TGLabel(fCompositeFrame5, "Types of decay");
    lCheck_half -> SetTextJustify(kTextLeft);
    lCheck_half-> SetMargins(0, 0, 0, 0);
    lCheck_half-> SetWrapLength(-1);
    fCompositeFrame5 -> AddFrame(lCheck_half, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lCheck_half-> MoveResize(1020, 180, 200, 20);

	TGComboBox *fTYPE_DECAY = new TGComboBox(fCompositeFrame5,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTYPE_DECAY->SetName("Types of decay");
	fTYPE_DECAY->AddEntry("Parent",0);
	fTYPE_DECAY->AddEntry("Daughter",1);
	fTYPE_DECAY->Resize(100,20);
	fTYPE_DECAY->Select(-1);
	fCompositeFrame5->AddFrame(fTYPE_DECAY, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTYPE_DECAY->MoveResize(1020,210,100,20);
	fTYPE_DECAY->Connect("Selected(Int_t)", "STARGui", this, "checkhalftype(Int_t)");

    TGNumberEntryField *fHALF_P = new TGNumberEntryField(fCompositeFrame5, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
    fHALF_P->MoveResize(1020,280,100,20);
    fCompositeFrame5->AddFrame(fHALF_P, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fHALF_P -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetHalfLife(const Char_t *)");
  
	TGLabel *lHalf_P = new TGLabel(fCompositeFrame5, "half-life of parent");
    lHalf_P -> SetTextJustify(kTextLeft);
    lHalf_P-> SetMargins(0, 0, 0, 0);
    lHalf_P-> SetWrapLength(-1);
    fCompositeFrame5 -> AddFrame(lHalf_P, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lHalf_P-> MoveResize(1020, 250, 200, 20);
    
    // embedded canvas
    TRootEmbeddedCanvas *thalf = new TRootEmbeddedCanvas(0,fCompositeFrame5,1000,250,kSunkenFrame);
    thalf->SetName("Half-life Curve");
    Int_t wthalf = thalf->GetCanvasWindowId();
    cvs8 = new TCanvas("cvs8", 10, 10, wthalf);
    thalf->AdoptCanvas(cvs8);
    fCompositeFrame5->AddFrame(thalf, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    thalf->MoveResize(10,10,1000,500);


	// container of "Tab6"
	TGCompositeFrame *fCompositeFrame6;
	fCompositeFrame6 = fTab1 -> AddTab("Calculations");
	fCompositeFrame6 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame6));
	fCompositeFrame6 ->SetLayoutBroken(kTRUE);
   
	TGLabel *lP_LOGFT = new TGLabel(fCompositeFrame6, "LOGFT Calculation");
    lP_LOGFT -> SetTextJustify(kTextLeft);
    lP_LOGFT-> SetMargins(0, 0, 0, 0);
    lP_LOGFT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lP_LOGFT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lP_LOGFT-> MoveResize(100, 10, 500, 20);
  
	TGLabel *lP_INFO = new TGLabel(fCompositeFrame6, "Parent Information");
    lP_INFO -> SetTextJustify(kTextLeft);
    lP_INFO-> SetMargins(0, 0, 0, 0);
    lP_INFO-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lP_INFO, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lP_INFO-> MoveResize(100, 40, 500, 20);
     
	TGLabel *lZ_PARENT = new TGLabel(fCompositeFrame6, "Z");
    lZ_PARENT -> SetTextJustify(kTextLeft);
    lZ_PARENT-> SetMargins(0, 0, 0, 0);
    lZ_PARENT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lZ_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lZ_PARENT-> MoveResize(100, 70, 100, 20);
     
    TGNumberEntryField *fZ_PARENT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 113);
    fZ_PARENT->MoveResize(250,70,100,20);
    fCompositeFrame6->AddFrame(fZ_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fZ_PARENT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetZParent(const Char_t *)");
  
	TGLabel *lHALFLIFE_PARENT = new TGLabel(fCompositeFrame6, "Halflife");
    lHALFLIFE_PARENT -> SetTextJustify(kTextLeft);
    lHALFLIFE_PARENT-> SetMargins(0, 0, 0, 0);
    lHALFLIFE_PARENT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lHALFLIFE_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lHALFLIFE_PARENT-> MoveResize(100, 100, 100, 20);
     
    TGNumberEntryField *fHALFLIFE_PARENT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 10000);
    fHALFLIFE_PARENT->MoveResize(250,100,100,20);
    fCompositeFrame6->AddFrame(fHALFLIFE_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fHALFLIFE_PARENT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetHalfParent(const Char_t *)");
  
	TGLabel *lUNIT_PARENT = new TGLabel(fCompositeFrame6, "Units");
    lUNIT_PARENT -> SetTextJustify(kTextLeft);
    lUNIT_PARENT-> SetMargins(0, 0, 0, 0);
    lUNIT_PARENT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lUNIT_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lUNIT_PARENT-> MoveResize(100, 130, 100, 20);
 
	TGComboBox *fUNIT_PARENT = new TGComboBox(fCompositeFrame6,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fUNIT_PARENT->SetName("Units");
	fUNIT_PARENT->AddEntry("Year",0);
	fUNIT_PARENT->AddEntry("Day",1);
	fUNIT_PARENT->AddEntry("H",2);
	fUNIT_PARENT->AddEntry("M",3);
	fUNIT_PARENT->AddEntry("s",4);
	fUNIT_PARENT->AddEntry("ms",5);
	fUNIT_PARENT->AddEntry("us ",6);
	fUNIT_PARENT->Resize(100,20);
	fUNIT_PARENT->Select(-1);
	fCompositeFrame6->AddFrame(fUNIT_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fUNIT_PARENT->MoveResize(250,130,100,20);
	fUNIT_PARENT->Connect("Selected(Int_t)", "STARGui", this, "SetUnit(Int_t)");
  
	TGLabel *lQ_PARENT = new TGLabel(fCompositeFrame6, "Q-value (MeV)");
    lQ_PARENT -> SetTextJustify(kTextLeft);
    lQ_PARENT-> SetMargins(0, 0, 0, 0);
    lQ_PARENT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lQ_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lQ_PARENT-> MoveResize(100, 160, 100, 20);
     
    TGNumberEntryField *fQ_PARENT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 100);
    fQ_PARENT->MoveResize(250,160,100,20);
    fCompositeFrame6->AddFrame(fQ_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fQ_PARENT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetQParent(const Char_t *)");
    
	TGLabel *lE_PARENT = new TGLabel(fCompositeFrame6, "Level Energy (keV)");
    lE_PARENT -> SetTextJustify(kTextLeft);
    lE_PARENT-> SetMargins(0, 0, 0, 0);
    lE_PARENT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lE_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lE_PARENT-> MoveResize(100, 190, 120, 20);
     
    TGNumberEntryField *fE_PARENT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 10000);
    fE_PARENT->MoveResize(250,190,100,20);
    fCompositeFrame6->AddFrame(fE_PARENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fE_PARENT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetEParent(const Char_t *)");
      
	TGLabel *lD_INFO = new TGLabel(fCompositeFrame6, "Daughter Information");
    lD_INFO -> SetTextJustify(kTextLeft);
    lD_INFO-> SetMargins(0, 0, 0, 0);
    lD_INFO-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lD_INFO, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lD_INFO-> MoveResize(600, 40, 500, 20);
     
	TGLabel *lE_DAUT = new TGLabel(fCompositeFrame6, "Level Energy (keV)");
    lE_DAUT -> SetTextJustify(kTextLeft);
    lE_DAUT-> SetMargins(0, 0, 0, 0);
    lE_DAUT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lE_DAUT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lE_DAUT-> MoveResize(600, 70, 120, 20);
     
    TGNumberEntryField *fE_DAUT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 10000);
    fE_DAUT->MoveResize(750,70,100,20);
    fCompositeFrame6->AddFrame(fE_DAUT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fE_DAUT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetEDaut(const Char_t *)");
      
	TGLabel *lP_DAUT = new TGLabel(fCompositeFrame6, "Intensity (0 to 1)");
    lP_DAUT -> SetTextJustify(kTextLeft);
    lP_DAUT-> SetMargins(0, 0, 0, 0);
    lP_DAUT-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lP_DAUT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lP_DAUT-> MoveResize(600, 100, 100, 20);
     
    TGNumberEntryField *fP_DAUT = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 1);
    fP_DAUT->MoveResize(750,100,100,20);
    fCompositeFrame6->AddFrame(fP_DAUT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fP_DAUT -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetPDaut(const Char_t *)");
       
	TGLabel *lDECAYTYPE = new TGLabel(fCompositeFrame6, "Decay Type");
    lDECAYTYPE -> SetTextJustify(kTextLeft);
    lDECAYTYPE-> SetMargins(0, 0, 0, 0);
    lDECAYTYPE-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lDECAYTYPE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lDECAYTYPE-> MoveResize(600, 130, 100, 20);
 
	TGComboBox *fDECAYTYPE = new TGComboBox(fCompositeFrame6,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fDECAYTYPE->SetName("Decay Type");
	fDECAYTYPE->AddEntry("Beta-",0);
	fDECAYTYPE->AddEntry("Beta+",1);
	fDECAYTYPE->AddEntry("EC",2);
	fDECAYTYPE->Resize(100,20);
	fDECAYTYPE->Select(-1);
	fCompositeFrame6->AddFrame(fDECAYTYPE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fDECAYTYPE->MoveResize(750,130,100,20);
	fDECAYTYPE->Connect("Selected(Int_t)", "STARGui", this, "SetUnit(Int_t)");
 
    TGTextButton *LOGFT = new TGTextButton(fCompositeFrame6,"Get LOGFT",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    LOGFT -> Connect("Clicked()", "STARGui", this, "logft()");
    LOGFT->SetTextJustify(36);
    LOGFT->SetMargins(0,0,0,0);
    LOGFT->SetWrapLength(-1);
    LOGFT->Resize(100,35);
    fCompositeFrame6->AddFrame(LOGFT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    LOGFT->MoveResize(600,180,100,35);
     
    TGTextButton *BGT = new TGTextButton(fCompositeFrame6,"Get B(GT)",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    BGT -> Connect("Clicked()", "STARGui", this, "bgt()");
    BGT->SetTextJustify(36);
    BGT->SetMargins(0,0,0,0);
    BGT->SetWrapLength(-1);
    BGT->Resize(100,35);
    fCompositeFrame6->AddFrame(BGT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    BGT->MoveResize(750,180,100,35);
   
	TGLabel *lB_INFO = new TGLabel(fCompositeFrame6, "Reduced Matrix Element Calculation");
    lB_INFO -> SetTextJustify(kTextLeft);
    lB_INFO-> SetMargins(0, 0, 0, 0);
    lB_INFO-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lB_INFO, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lB_INFO-> MoveResize(100, 230, 500, 20);
     
	TGLabel *lB_TYPE = new TGLabel(fCompositeFrame6, "Multipole");
    lB_TYPE -> SetTextJustify(kTextLeft);
    lB_TYPE-> SetMargins(0, 0, 0, 0);
    lB_TYPE-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lB_TYPE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lB_TYPE-> MoveResize(100, 260, 100, 20);
 
	TGComboBox *fTYPE_MUL = new TGComboBox(fCompositeFrame6,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTYPE_MUL->SetName("Multipole");
	fTYPE_MUL->AddEntry("E1",0);
	fTYPE_MUL->AddEntry("M1",1);
	fTYPE_MUL->AddEntry("E2",2);
	fTYPE_MUL->AddEntry("M2",3);
	fTYPE_MUL->AddEntry("E3",4);
	fTYPE_MUL->AddEntry("M3",5);
	fTYPE_MUL->Select(-1);
	fCompositeFrame6->AddFrame(fTYPE_MUL, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTYPE_MUL->MoveResize(250,260,100,20);
	fTYPE_MUL->Connect("Selected(Int_t)", "STARGui", this, "SetMulti(Int_t)");
   
	TGLabel *lB_E = new TGLabel(fCompositeFrame6, "Energy (keV)");
    lB_E -> SetTextJustify(kTextLeft);
    lB_E-> SetMargins(0, 0, 0, 0);
    lB_E-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lB_E, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lB_E-> MoveResize(600, 260, 100, 20);
  
    TGNumberEntryField *fB_E = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 10000);
    fB_E->MoveResize(750,260,100,20);
    fCompositeFrame6->AddFrame(fB_E, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fB_E -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetBEnergy(const Char_t *)");
 
	TGLabel *lVAL_HALF = new TGLabel(fCompositeFrame6, "Half-life");
    lVAL_HALF -> SetTextJustify(kTextLeft);
    lVAL_HALF-> SetMargins(0, 0, 0, 0);
    lVAL_HALF-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lVAL_HALF, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lVAL_HALF-> MoveResize(100, 290, 100, 20);
   
    TGNumberEntryField *fVAL_HALF = new TGNumberEntryField(fCompositeFrame6, 0, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 10000);
    fVAL_HALF->MoveResize(250,290,100,20);
    fCompositeFrame6->AddFrame(fVAL_HALF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fVAL_HALF -> Connect("TextChanged(const Char_t *)", "STARGui", this, "SetBHalf(const Char_t *)");
  
	TGLabel *lUNIT_HALF = new TGLabel(fCompositeFrame6, "Units");
    lUNIT_HALF -> SetTextJustify(kTextLeft);
    lUNIT_HALF-> SetMargins(0, 0, 0, 0);
    lUNIT_HALF-> SetWrapLength(-1);
    fCompositeFrame6 -> AddFrame(lUNIT_HALF, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lUNIT_HALF-> MoveResize(600, 290, 100, 20);
 
	TGComboBox *fUNIT_HALF = new TGComboBox(fCompositeFrame6,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fUNIT_HALF->SetName("Units");
	fUNIT_HALF->AddEntry("s",0);
	fUNIT_HALF->AddEntry("ms",1);
	fUNIT_HALF->AddEntry("us",2);
	fUNIT_HALF->AddEntry("ns",3);
	fUNIT_HALF->AddEntry("ps",4);
	fUNIT_HALF->Resize(100,20);
	fUNIT_HALF->Select(-1);
	fCompositeFrame6->AddFrame(fUNIT_HALF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fUNIT_HALF->MoveResize(750,290,100,20);
	fUNIT_HALF->Connect("Selected(Int_t)", "STARGui", this, "SetHalfUnit(Int_t)");
 
    TGTextButton *BMUL = new TGTextButton(fCompositeFrame6,"Calculate",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    BMUL -> Connect("Clicked()", "STARGui", this, "bmulti()");
    BMUL->SetTextJustify(36);
    BMUL->SetMargins(0,0,0,0);
    BMUL->SetWrapLength(-1);
    BMUL->Resize(100,35);
    fCompositeFrame6->AddFrame(BMUL, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    BMUL->MoveResize(900,260,100,35);
     
 

     

 
    fTab1 -> SetTab(0);
    fTab1->Resize(fTab1->GetDefaultSize());
    fMainFrame1073->AddFrame(fTab1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTab1->MoveResize(10,25,1180,560);
    
    fMainFrame1073->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
    fMainFrame1073->MapSubwindows();
    
    fMainFrame1073->Resize(fMainFrame1073->GetDefaultSize());
    fMainFrame1073->MapWindow();
    fMainFrame1073->Resize(1200,620);

	fMainFrame1073->SetWindowName("STARWARE Beta Ver.1.2");
	fMainFrame1073->MapSubwindows();
	fMainFrame1073->Connect("CloseWindow()", "STARGui", this, "TerminatePro()");

	intro();
}

void STARGui::main(TString &directory, TString &openFile)
{
	STAR::main(directory, openFile);
	stargg.hist_Tot = hist_Tot;
	stargg.direc = direc;
	startg.hist_Tot = hist_Tot;
	startg.direc = direc;
	stardc.hist_Tot = hist_Tot;
	stardc.direc = direc;
	stardis.hist_Tot = hist_Tot;
	stardis.direc = direc;
}

void STARGui::clearall()
{
    cvs1 -> Disconnect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)");
    cvs2 -> Disconnect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)");
    cvs1 -> Clear();
    cvs2 -> Clear();
    cvs3 -> Clear();
    cvs4 -> Clear();
    cvs5 -> Clear();
    cvs6 -> Clear();
    cvs7 -> Clear();
    cvs8 -> Clear();
    
    cvs1 -> Modified();
    cvs1 -> Update();
    cvs2 -> Modified();
    cvs2 -> Update();
    cvs3 -> Modified();
    cvs3 -> Update();
    cvs4 -> Modified();
    cvs4 -> Update();
    cvs5 -> Modified();
    cvs5 -> Update();
    cvs6 -> Modified();
    cvs6 -> Update();
    cvs7 -> Modified();
    cvs7 -> Update();
    cvs8 -> Modified();
    cvs8 -> Update();
}

void STARGui::openfile()
{
    clearall();
    
    TGFileInfo fileInfo;
    const Char_t *fileType[4] = {"Matrix File", "*.mat", 0, 0};
    fileInfo.fFileTypes = fileType;
    new TGFileDialog(gClient -> GetRoot(), 0, kFDOpen, &fileInfo);
    
    // If user clicks cancel, do nothing.
    if (fileInfo.fFilename == NULL)
        return;
    
    // Get the file name with path
    TString filenameWithPath = fileInfo.fFilename;
    TObjArray *decomposedFileNameWithPath = filenameWithPath.Tokenize("/");
    TString openingFile = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    TString directory = filenameWithPath.ReplaceAll(openingFile, "");
    
    main(directory, openingFile);
    cvs1 -> cd();
    cvs1 -> ToggleEventStatus();
    hist_X -> Draw();
    cvs1 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "GetCoorX(Int_t, Int_t, Int_t, TObject*)");
    cvs1 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    cvs1 -> Modified();
    cvs1 -> Update();
    cvs2 -> cd();
    cvs2 -> ToggleEventStatus();
    hist_Y -> Draw();
    cvs2 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "GetCoorY(Int_t, Int_t, Int_t, TObject*)");
    cvs2 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "STARGui", this, "EventInfo(Int_t, Int_t, Int_t, TObject*)");
    cvs2 -> Modified();
    cvs2 -> Update();
    
    manual();
    
    delete decomposedFileNameWithPath;
}

void STARGui::openeff()
{
    TGFileInfo effInfo;
    const Char_t *effType[4] = {"ROOT File", "*.root", 0, 0};
    effInfo.fFileTypes = effType;
    new TGFileDialog(gClient -> GetRoot(), 0, kFDOpen, &effInfo);
    
    // If user clicks cancel, do nothing.
    if (effInfo.fFilename == NULL)
	{
        return;
    }

    //Get the file name with path
    if (effInfo.fFilename != NULL)
	{
    	effdatafile = effInfo.fFilename;
		cout << "The efficiency data file has been successfully read." << endl;
	}

}

void STARGui::gatedspectrum()
{
	TGFileInfo gateInfo;
	const Char_t *gateType[4] = {"ROOT File", "*.root", 0, 0};
	gateInfo.fFileTypes = gateType;
	new TGFileDialog(gClient -> GetRoot(), 0, kFDOpen, &gateInfo);
    
    // If user clicks cancel, do nothing.
    if (gateInfo.fFilename == NULL)
        return;
    
    //Get the file name with path
    if (gateInfo.fFilename != NULL)
	{
		cout << "The gated spectrum data file has been successfully read." << endl;
		gatedatafile = gateInfo.fFilename;
		stardis.peakfind(gatedatafile);
		cvs4 -> cd();
		stardis.gated_hist -> Draw();
		cvs4 -> Update();
		cvs4 -> Modified();
	}
}

void STARGui::gate()
{
	for (Int_t i = 0; i < int(gatevalueX.size()); i++)
	{
		stargg.gatevalueX.push_back(gatevalueX[i]);
	}
	for (Int_t i = 0; i < int(gatevalueY.size()); i++)
	{
		stargg.gatevalueY.push_back(gatevalueY[i]);
	}
	
    stargg.Hgate();
	reset();
	cvs1 -> Modified();
	cvs1 -> Update();
    cvs2 -> Modified();
	cvs2 -> Update();
    
    cvs3 -> cd();
    cvs3 -> ToggleEventStatus();
    stargg.hist_P -> Draw();
    cvs3 -> Modified();
    cvs3 -> Update();
}

void STARGui::timegate()
{
    startg.Htimegate(timeaxis1, timeaxis2, tstart, tend);
    
    cvs5 -> cd();
    cvs5 -> ToggleEventStatus();
    startg.hist_TY -> Draw();
    cvs5 -> Modified();
    cvs5 -> Update();
}

void STARGui::decaygate()
{
	for (Int_t i = 0; i < int(gatevalueX.size()); i++)
	{
		stardc.gatevalueX.push_back(gatevalueX[i]);
	}
	for (Int_t i = 0; i < int(gatevalueY.size()); i++)
	{
		stardc.gatevalueY.push_back(gatevalueY[i]);
	}
	
    stardc.Hdecaygate(tbin);

	reset();
   	cvs1 -> Modified();
	cvs1 -> Update();
    cvs2 -> Modified();
	cvs2 -> Update();

    cvs4 -> cd();
    cvs4 -> ToggleEventStatus();
    stardc.hist_D -> Draw();
    cvs4 -> Modified();
    cvs4 -> Update();
}

void STARGui::netarea()
{
	for (Int_t i = 0; i < int(gatevalueX.size()); i++)
	{
		startg.gatevalueX.push_back(gatevalueX[i]);
	}
	for (Int_t i = 0; i < int(gatevalueY.size()); i++)
	{
		startg.gatevalueY.push_back(gatevalueY[i]);
	}
	
	startg.Hnetarea(cvs3, effdatafile);
	reset();
	cvs1 -> Modified();
	cvs1 -> Update();
    cvs2 -> Modified();
	cvs2 -> Update();


	cvs3 -> Modified();
	cvs3 -> Update();
}

void STARGui::netarea2()
{
	for (Int_t i = 0; i < int(gatevalueX.size()); i++)
	{
		startg.gatevalueX.push_back(gatevalueX[i]);
	}
	for (Int_t i = 0; i < int(gatevalueY.size()); i++)
	{
		startg.gatevalueY.push_back(gatevalueY[i]);
	}
	
	startg.Hnetarea2(cvs3, effdatafile, tstart, tend);

	reset();
	cvs1 -> Modified();
	cvs1 -> Update();
    cvs2 -> Modified();
	cvs2 -> Update();

	cvs3 -> Modified();
	cvs3 -> Update();
}

void STARGui::timediff()
{
    stardis.Htimediff(timeaxis1, timeaxis2, dstart1, dend1, dstart2, dend2);
    
    cvs6 -> cd();
    cvs6 -> ToggleEventStatus();
    stardis.hist1 -> Draw();
    stardis.hist2 -> Draw("same");
    cvs6 -> Modified();
    cvs6 -> Update();
}

void STARGui::timegrow()
{
	startg.Htimegrow(effdatafile, timeaxis1, timeaxis2, tgrow);

	cvs7 -> cd();
	cvs7 -> ToggleEventStatus();
	startg.graph -> Draw();
	cvs7 -> Modified();
	cvs7 -> Update();
}

void STARGui::halflife()
{
    stardc.Hhalflife(halftype, half_parent, peaksvalue, cvs8);
    
    cvs8 -> Modified();
    cvs8 -> Update();
    
    peaksvalue.clear();
}

void STARGui::setpeaks()
{
    peaksvalue.push_back(halfpeak);
    
    cout << halfpeak << " keV has ben saved." << endl;
}

void STARGui::SetTimeBin(const Char_t *value)
{
    tbin = atoi(value);
} 

void STARGui::SetTimeStart(const Char_t *value)
{
    tstart = atoi(value);
} 

void STARGui::SetTimeEnd(const Char_t *value)
{
    tend = atoi(value);
} 

void STARGui::SetDiffStart1(const Char_t *value)
{
    dstart1 = atoi(value);
} 

void STARGui::SetDiffEnd1(const Char_t *value)
{
    dend1 = atoi(value);
} 

void STARGui::SetDiffStart2(const Char_t *value)
{
    dstart2 = atoi(value);
} 

void STARGui::SetDiffEnd2(const Char_t *value)
{
    dend2 = atoi(value);
} 

void STARGui::SetTimeGrow(const Char_t *value)
{
    tgrow = atoi(value);
}

void STARGui::SetPeakValue(const Char_t *value)
{
    halfpeak = atoi(value);
}

void STARGui::SetHalfLife(const Char_t *value)
{
    half_parent = atoi(value);
}

void STARGui::checktimetox(Bool_t value)
{
    if (value==0)
    {
        timeaxis1 = 1;
    }
    if (value==1)
    {
        timeaxis1 = 0;
    }
}

void STARGui::checktimetoy(Bool_t value)
{
    if (value==0)
    {
        timeaxis2 = 1;
    }
    if (value==1)
    {
        timeaxis2 = 0;
    }
}

void STARGui::checkhalftype(Int_t value)
{	
    if (value==0)
    {
        halftype = 1;
    }
    if (value==1)
    {
        halftype = 0;
    }
}


void STARGui::EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected)
{

	const char *text0, *text1, *text3;
	char text2[50];
	text0 = selected->GetTitle();
	SetStatusText(text0,0);
	text1 = selected->GetName();
	SetStatusText(text1,1);
	if (event == kKeyPress)
		sprintf(text2, "%c", (char) px);
	else
		sprintf(text2, "%d,%d", px, py);
	SetStatusText(text2,2);
	text3 = selected->GetObjectInfo(px,py);
	SetStatusText(text3,3);
}

void STARGui::SetStatusText(const char *text, Int_t pi)
{
	fStatusBar->SetText(text, pi);
}

void STARGui::HandleMenu(Int_t menu_id)
{
	// Handle menu events.
	TRootHelpDialog *hd;
	switch (menu_id) {
		case M_FILE_EXIT:
			// close the window and quit application
			gApplication->Terminate(0);
			break;
		case M_FILE_OPEN:
			openfile();
			break;
		case M_HELP_ABOUT:
			hd = new TRootHelpDialog(0, "About STARWARE", 550, 250);
			hd->SetText(gAboutSTARWARE);
			hd->Popup();
			break;
		case M_HELP_COPYRIGHT:
			hd = new TRootHelpDialog(0, "STARWARE Copyright", 550, 250);
			hd->SetText(gCOPYRIGHT);
			hd->Popup();
			break;
		case M_HELP_MANUAL:
			hd = new TRootHelpDialog(0, "STARWARE Manual", 550, 250);
			hd->SetText(gMANUAL);
			hd->Popup();
			break;
		case M_HELP_CONTACT:
			hd = new TRootHelpDialog(0, "STARWARE Contact Information", 550, 250);
			hd->SetText(gCONTACT);
			hd->Popup();
			break;
	}
}

void STARGui::TerminatePro()
{
	gApplication->Terminate(0);
}

void STARGui::SetZParent(const Char_t *value)
{
	ZParent = atoi(value);
}

void STARGui::SetHalfParent(const Char_t *value)
{
	HalfParent = atof(value);
}

void STARGui::SetQParent(const Char_t *value)
{
	QParent = atof(value);
}

void STARGui::SetEParent(const Char_t *value)
{
	EParent = atof(value);
}

void STARGui::SetEDaut(const Char_t *value)
{
	EDaut = atof(value);
}

void STARGui::SetPDaut(const Char_t *value)
{
	PDaut = atof(value);
}

void STARGui::SetUnit(Int_t value)
{
	if (value == 0) //year
	{
		unit = 31536000;
	}
	
	if (value == 1) //day
	{
		unit = 86400;
	}

	if (value == 2) //hour
	{
		unit = 3600;
	}
	
	if (value == 3) //minute
	{
		unit = 60;
	}

	if (value == 4) //second
	{
		unit = 1;
	}
	
	if (value == 5) //ms
	{
		unit = 1.0E-3;
	}

	if (value == 6) //us
	{
		unit = 1.0E-6;
	}
}

void STARGui::SetDecayType(Int_t value)
{
	if (value == 0)	DecayType = 0;
	if (value == 1)	DecayType = 1;
	if (value == 2)	DecayType = 2;
}

void STARGui::logft()
{
	starcal.Hlogft(DecayType, ZParent, HalfParent, QParent, EParent, EDaut, PDaut, unit);
}
	
void STARGui::bgt()
{
	starcal.BGT(DecayType, ZParent, HalfParent, QParent, EParent, EDaut, PDaut, unit);
}

void STARGui::SetMulti(Int_t value)
{
	multitype = value;
}

void STARGui::SetBEnergy(const Char_t *value)
{
	benergy = atof(value);
}

void STARGui::SetBHalf(const Char_t *value)
{
	bhalf = atof(value);
}

void STARGui::SetHalfUnit(Int_t value)
{
	if (value == 0)
	{
		bunit = 1;
	}
	if (value == 1)
	{
		bunit = 1E-3;
	}
	if (value == 2)
	{
		bunit = 1E-6;
	}
	if (value == 3)
	{
		bunit = 1E-9;
	}
	if (value == 4)
	{
		bunit = 1E-12;
	}
}

void STARGui::bmulti()
{
	starcal.HBMUL(multitype, benergy, bhalf, bunit);
}

