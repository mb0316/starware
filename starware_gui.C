// Mainframe macro generated from application: /Users/MoonByul/root/bin/root.exe
// By ROOT version 6.08/00 on 2016-12-20 20:20:27
/***********************************************************************************
*************************STARWARE GUI CONSTRUCTOR FILE******************************
Made by Byul Moon from Korea University
GUI constructor for STARWARE program.
Last refine : 28.12.2016, ver.4.0
Copyright by B. Moon
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

#include "Riostream.h"
#include "BMspec.h"
#include <stdio.h>
#include <vector>
#include "TStyle.h"

BMspec star;

TCanvas* cvs1;
TCanvas* cvs2;
TCanvas* cvs3;
TCanvas* cvs4;
TCanvas* cvs5;
TCanvas* cvs6;
TCanvas* cvs7;
TCanvas* cvs8;

Int_t tbin, tstart, tend, dstart1, dend1, dstart2, dend2, tgrow, halfpeak;
vector <int> peaksvalue;

Int_t timeaxis1=1, timeaxis2=1; //timeaxis1 : x axis is time, timeaxis2: y axis is time; 0 : enable, 1 : unable

void starware_gui()
{
	gStyle -> SetOptStat(0);

	// main frame
	TGMainFrame *fMainFrame1073 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
	fMainFrame1073->SetName("STARWARE");
	fMainFrame1073->SetLayoutBroken(kTRUE);

	// tab widget
	TGTab *fTab1 = new TGTab(fMainFrame1073, 1180, 570);

	// container of "Tab1"
	TGCompositeFrame *fCompositeFrame1;
	fCompositeFrame1 = fTab1 -> AddTab("Projected Spectra");
	fCompositeFrame1 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame1));
	fCompositeFrame1 ->SetLayoutBroken(kTRUE);

	TGTextButton *GATE = new TGTextButton(fCompositeFrame1,"GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	GATE -> Connect("Clicked()", 0, 0, "gate()");
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
	fTIMEBIN -> Connect("TextChanged(const Char_t *)", 0, 0, "SetTimeBin(const Char_t *)");

	TGTextButton *DECAYGATE = new TGTextButton(fCompositeFrame1,"DECAY GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	DECAYGATE -> Connect("Clicked()", 0, 0, "decaygate()");
	DECAYGATE->SetTextJustify(36);
	DECAYGATE->SetMargins(0,0,0,0);
	DECAYGATE->SetWrapLength(-1);
	DECAYGATE->Resize(100,35);
	fCompositeFrame1->AddFrame(DECAYGATE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	DECAYGATE->MoveResize(1030,125,100,35);

	TGTextButton *NETAREA = new TGTextButton(fCompositeFrame1,"NET AREA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	NETAREA -> Connect("Clicked()", 0, 0, "netarea()");
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
	fTSTARTBIN -> Connect("TextChanged(const Char_t *)", 0, 0, "SetTimeStart(const Char_t *)");

	TGLabel *lENDBIN = new TGLabel(fCompositeFrame1, "Input the end time value.");
	lENDBIN -> SetTextJustify(kTextLeft);
	lENDBIN-> SetMargins(0, 0, 0, 0);
	lENDBIN-> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lENDBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lENDBIN-> MoveResize(1030, 265, 170, 20);

	TGNumberEntryField *fTENDBIN = new TGNumberEntryField(fCompositeFrame1, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
	fTENDBIN->MoveResize(1030,290,100,20);
	fCompositeFrame1->AddFrame(fTENDBIN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTENDBIN -> Connect("TextChanged(const Char_t *)", 0, 0, "SetTimeEnd(const Char_t *)");

	TGTextButton *TIMEGATE = new TGTextButton(fCompositeFrame1,"TIME GATE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	TIMEGATE -> Connect("Clicked()", 0, 0, "timegate()");
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
	fTGROW -> Connect("TextChanged(const Char_t *)", 0, 0, "SetTimeGrow(const Char_t *)");

	TGTextButton *TIMEGROW = new TGTextButton(fCompositeFrame1,"TIME GROW",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	TIMEGROW -> Connect("Clicked()", 0, 0, "timegrow()");
	TIMEGROW->SetTextJustify(36);
	TIMEGROW->SetMargins(0,0,0,0);
	TIMEGROW->SetWrapLength(-1);
	TIMEGROW->Resize(100,35);
	fCompositeFrame1->AddFrame(TIMEGROW, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	TIMEGROW->MoveResize(1030,410,100,35);

	TGTextButton *OPEN = new TGTextButton(fCompositeFrame1,"OPEN",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	OPEN -> Connect("Clicked()", 0, 0, "openfile()");
	OPEN->SetTextJustify(36);
	OPEN->SetMargins(0,0,0,0);
	OPEN->SetWrapLength(-1);
	OPEN->Resize(100,35);
	fCompositeFrame1->AddFrame(OPEN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	OPEN->MoveResize(1030,455,100,35);

	TGLabel *lCheck = new TGLabel(fCompositeFrame1, "Axis for the time.");
	lCheck -> SetTextJustify(kTextLeft);
	lCheck-> SetMargins(0, 0, 0, 0);
	lCheck-> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lCheck, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lCheck-> MoveResize(1030, 500, 200, 20);

	TGCheckButton *fCheckTX = new TGCheckButton(fCompositeFrame1,"x");
	fCheckTX->Connect("Toggled(Bool_t)", 0, 0, "checktimetox(Bool_t)");
	fCheckTX->SetTextJustify(kTextLeft);
	fCheckTX->SetMargins(0,0,0,0);
	fCheckTX->SetWrapLength(-1);
	fCompositeFrame1->AddFrame(fCheckTX, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fCheckTX->Move(1030,525);

	TGCheckButton *fCheckTY = new TGCheckButton(fCompositeFrame1,"y");
	fCheckTY->Connect("Toggled(Bool_t)", 0, 0, "checktimetoy(Bool_t)");
	fCheckTY->SetTextJustify(kTextLeft);
	fCheckTY->SetMargins(0,0,0,0);
	fCheckTY->SetWrapLength(-1);
	fCompositeFrame1->AddFrame(fCheckTY, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fCheckTY->MoveResize(1080,525);

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
	ProjectedSpectrum_Y->MoveResize(10,280,1000,250);

	// container of "Tab2"
	TGCompositeFrame *fCompositeFrame2;
	fCompositeFrame2 = fTab1 -> AddTab("Gated Spectrum");
	fCompositeFrame2 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame2));
	fCompositeFrame2 ->SetLayoutBroken(kTRUE);

	// embedded canvas
	TRootEmbeddedCanvas *gated_spec = new TRootEmbeddedCanvas(0,fCompositeFrame2,1000,250,kSunkenFrame);
	gated_spec->SetName("Gated Spectrum");
	Int_t wgated_spec = gated_spec->GetCanvasWindowId();
	cvs3 = new TCanvas("cvs3", 10, 10, wgated_spec);
	gated_spec->AdoptCanvas(cvs3);
	fCompositeFrame2->AddFrame(gated_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	gated_spec->MoveResize(10,10,1000,250);
	TRootEmbeddedCanvas *gated_decay = new TRootEmbeddedCanvas(0,fCompositeFrame2,1000,250,kSunkenFrame);
	gated_decay->SetName("Gated Decay Curve");
	Int_t wgated_decay = gated_decay->GetCanvasWindowId();
	cvs4 = new TCanvas("cvs4", 10, 10, wgated_decay);
	gated_decay->AdoptCanvas(cvs4);
	fCompositeFrame2->AddFrame(gated_decay, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	gated_decay->MoveResize(10,280,1000,250);

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
	fDSTARTBIN1 -> Connect("TextChanged(const Char_t *)", 0, 0, "SetDiffStart1(const Char_t *)");

	TGNumberEntryField *fDENDBIN1 = new TGNumberEntryField(fCompositeFrame3, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
	fDENDBIN1->MoveResize(1100,80,40,20);
	fCompositeFrame3->AddFrame(fDENDBIN1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fDENDBIN1 -> Connect("TextChanged(const Char_t *)", 0, 0, "SetDiffEnd1(const Char_t *)");

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
	fDSTARTBIN2 -> Connect("TextChanged(const Char_t *)", 0, 0, "SetDiffStart2(const Char_t *)");

	TGNumberEntryField *fDENDBIN2 = new TGNumberEntryField(fCompositeFrame3, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
	fDENDBIN2->MoveResize(1100,165,40,20);
	fCompositeFrame3->AddFrame(fDENDBIN2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fDENDBIN2 -> Connect("TextChanged(const Char_t *)", 0, 0, "SetDiffEnd2(const Char_t *)");

	TGTextButton *TDIFF = new TGTextButton(fCompositeFrame3,"TIME DIFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	TDIFF -> Connect("Clicked()", 0, 0, "timediff()");
	TDIFF->SetTextJustify(36);
	TDIFF->SetMargins(0,0,0,0);
	TDIFF->SetWrapLength(-1);
	TDIFF->Resize(100,35);
	fCompositeFrame3->AddFrame(TDIFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	TDIFF->MoveResize(1050,190,100,35);

	TGTextButton *NETAREA2 = new TGTextButton(fCompositeFrame3,"NET AREA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	NETAREA2 -> Connect("Clicked()", 0, 0, "netarea2()");
	NETAREA2->SetTextJustify(36);
	NETAREA2->SetMargins(0,0,0,0);
	NETAREA2->SetWrapLength(-1);
	NETAREA2->Resize(100,35);
	fCompositeFrame3->AddFrame(NETAREA2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	NETAREA2->MoveResize(1050,250,100,35);

	// embedded canvas
	TRootEmbeddedCanvas *tgated_spec = new TRootEmbeddedCanvas(0,fCompositeFrame3,1000,250,kSunkenFrame);
	tgated_spec->SetName("T.Gated Spectrum");
	Int_t wtgated_spec = tgated_spec->GetCanvasWindowId();
	cvs5 = new TCanvas("cvs5", 10, 10, wtgated_spec);
	tgated_spec->AdoptCanvas(cvs5);
	BMspec* h3 = new BMspec();
	cvs5 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "BMspec", h3, "GetCoorY(Int_t, Int_t, Int_t, TObject*)");
	fCompositeFrame3->AddFrame(tgated_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	tgated_spec->MoveResize(10,10,1000,250);
	TRootEmbeddedCanvas *tdiff_spec = new TRootEmbeddedCanvas(0,fCompositeFrame3,1000,250,kSunkenFrame);
	tdiff_spec->SetName("Time Difference");
	Int_t wtdiff_spec = tdiff_spec->GetCanvasWindowId();
	cvs6 = new TCanvas("cvs6", 10, 10, wtdiff_spec);
	tdiff_spec->AdoptCanvas(cvs6);
	fCompositeFrame3->AddFrame(tdiff_spec, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	tdiff_spec->MoveResize(10,280,1000,250);

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
	lHALF -> MoveResize(1050, 40, 170, 20);

	TGNumberEntryField *fSETPEAK = new TGNumberEntryField(fCompositeFrame5, 2, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
	fSETPEAK->MoveResize(1050,65,40,20);
	fCompositeFrame5->AddFrame(fSETPEAK, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fSETPEAK -> Connect("TextChanged(const Char_t *)", 0, 0, "SetPeakValue(const Char_t *)");

	TGTextButton *TSETPEAK = new TGTextButton(fCompositeFrame5,"SET PEAK",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	TSETPEAK -> Connect("Clicked()", 0, 0, "setpeaks()");
	TSETPEAK->SetTextJustify(36);
	TSETPEAK->SetMargins(0,0,0,0);
	TSETPEAK->SetWrapLength(-1);
	TSETPEAK->Resize(100,35);
	fCompositeFrame3->AddFrame(TSETPEAK, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	TSETPEAK->MoveResize(1050,90,100,35);

	TGTextButton *TGETHALF = new TGTextButton(fCompositeFrame5,"GET HALFLIFE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
	TGETHALF-> Connect("Clicked()", 0, 0, "halflife()");
	TGETHALF->SetTextJustify(36);
	TGETHALF->SetMargins(0,0,0,0);
	TGETHALF->SetWrapLength(-1);
	TGETHALF->Resize(100,35);
	fCompositeFrame3->AddFrame(TGETHALF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	TGETHALF->MoveResize(1050,130,100,35);

	// embedded canvas
	TRootEmbeddedCanvas *thalf = new TRootEmbeddedCanvas(0,fCompositeFrame5,1000,250,kSunkenFrame);
	thalf->SetName("Half-life Curve");
	Int_t wthalf = thalf->GetCanvasWindowId();
	cvs8 = new TCanvas("cvs8", 10, 10, wthalf);
	thalf->AdoptCanvas(cvs8);
	fCompositeFrame5->AddFrame(thalf, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	thalf->MoveResize(10,10,1000,500);



	fTab1 -> SetTab(0);
	fTab1->Resize(fTab1->GetDefaultSize());
	fMainFrame1073->AddFrame(fTab1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTab1->MoveResize(5,10,1180,570);

	fMainFrame1073->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
	fMainFrame1073->MapSubwindows();

	fMainFrame1073->Resize(fMainFrame1073->GetDefaultSize());
	fMainFrame1073->MapWindow();
	fMainFrame1073->Resize(1200,600);
} 

void clearall()
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

void openfile()
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
	
	star.main(directory, openingFile);
	cvs1 -> cd();
	cvs1 -> ToggleEventStatus();
	star.hist_X -> Draw();
	BMspec* h1 = new BMspec();
	cvs1 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "BMspec", h1, "GetCoorX(Int_t, Int_t, Int_t, TObject*)");
	cvs1 -> Modified();
	cvs1 -> Update();
	cvs2 -> cd();
	cvs2 -> ToggleEventStatus();
	star.hist_Y -> Draw();
	BMspec* h2 = new BMspec();
	cvs2 -> Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "BMspec", h2, "GetCoorY(Int_t, Int_t, Int_t, TObject*)");
	cvs2 -> Modified();
	cvs2 -> Update();

	star.manual();

	delete decomposedFileNameWithPath;
}

void gate()
{
    star.Hgate();

	cvs3 -> cd();
	cvs3 -> ToggleEventStatus();
	star.hist_P -> Draw();
	cvs3 -> Modified();
	cvs3 -> Update();
}

void timegate()
{
    star.Htimegate(timeaxis1, timeaxis2, tstart, tend);

	cvs5 -> cd();
	cvs5 -> ToggleEventStatus();
	star.hist_TY -> Draw();
	cvs5 -> Modified();
	cvs5 -> Update();
}

void decaygate()
{
    star.Hdecaygate(tbin);

	cvs4 -> cd();
	cvs4 -> ToggleEventStatus();
	star.hist_D -> Draw();
	cvs4 -> Modified();
	cvs4 -> Update();
}

void netarea()
{
    star.Hnetarea(cvs3);

	cvs3 -> Modified();
	cvs3 -> Update();
}

void netarea2()
{
    star.Hnetarea2(cvs3, tstart, tend);

	cvs3 -> Modified();
	cvs3 -> Update();
}

void timediff()
{
    star.Htimediff(timeaxis1, timeaxis2, dstart1, dend1, dstart2, dend2);

	cvs6 -> cd();
	cvs6 -> ToggleEventStatus();
	star.hist1 -> Draw();
	star.hist2 -> Draw("same");
	cvs6 -> Modified();
	cvs6 -> Update();
}

void timegrow()
{
    star.Htimegrow(timeaxis1, timeaxis2, tgrow);

	cvs7 -> cd();
	cvs7 -> ToggleEventStatus();
	star.graph -> Draw();
	cvs7 -> Modified();
	cvs7 -> Update();

}

void halflife()
{
    star.Hhalflife(peaksvalue, cvs8);

	cvs8 -> Modified();
	cvs8 -> Update();

	peaksvalue.clear();
}

void setpeaks()
{
	peaksvalue.push_back(halfpeak);

	cout << halfpeak << " keV has ben saved." << endl;
}

void SetTimeBin(const Char_t *value)
{
	tbin = atoi(value);
} 

void SetTimeStart(const Char_t *value)
{
	tstart = atoi(value);
} 

void SetTimeEnd(const Char_t *value)
{
	tend = atoi(value);
} 

void SetDiffStart1(const Char_t *value)
{
	dstart1 = atoi(value);
} 

void SetDiffEnd1(const Char_t *value)
{
	dend1 = atoi(value);
} 

void SetDiffStart2(const Char_t *value)
{
	dstart2 = atoi(value);
} 

void SetDiffEnd2(const Char_t *value)
{
	dend2 = atoi(value);
} 

void SetTimeGrow(const Char_t *value)
{
	tgrow = atoi(value);
}

void SetPeakValue(const Char_t *value)
{
	halfpeak = atoi(value);
}

void checktimetox(Bool_t value)
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

void checktimetoy(Bool_t value)
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

