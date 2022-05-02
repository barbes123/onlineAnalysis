#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>


TH1D *histCut;
TH1D *histLoop;


void timeCheck()
{
   auto file = new TFile("/data/2022_w5/root_files/run410_1_ssgant1.root", "READ");
   auto tree = (TTree*)file->Get("ELIADE_Tree");
   tree->SetBranchStatus("*", kFALSE);
   
   UChar_t mod;
   tree->SetBranchStatus("Mod", kTRUE);
   tree->SetBranchAddress("Mod", &mod);

   UChar_t ch;
   tree->SetBranchStatus("Ch", kTRUE);
   tree->SetBranchAddress("Ch", &ch);

   ULong64_t timeStamp;
   tree->SetBranchStatus("TimeStamp", kTRUE);
   tree->SetBranchAddress("TimeStamp", &timeStamp);

   UShort_t ene;
   tree->SetBranchStatus("ChargeLong", kTRUE);
   tree->SetBranchAddress("ChargeLong", &ene);

   const int timeWindow = 1000;
   histCut = new TH1D("histCut", "time difference: beam pulse and trigger", timeWindow, 0.5, timeWindow + 0.5);
   histCut->SetXTitle("[ns]");
   histLoop = new TH1D("histLoop", "time difference: beam pulse and trigger", timeWindow, 0.5, timeWindow + 0.5);
   histLoop->SetXTitle("[ns]");
   
   
   const auto nEvents = tree->GetEntries();
   ULong63_t zeroTime = 0;
   for(auto iEve = 1; iEve < nEvents - 1; iEve++) {
      tree->GetEntry(iEve);
      if(ch == 13 && mod == 3)
	zeroTime = timeStamp;

      if(zeroTime > 0 && ch == 0 && mod == 0) {
	auto trgTime = (timeStamp - zeroTime);
	histCut->Fill(trgTime);
	histLoop->Fill(trgTime % timeWindow);
      }
      
   }

   auto canv = new TCanvas("canv", "test", 1600, 600);
   canv->Divide(2, 1);
   canv->cd(1);
   histLoop->Draw();
   canv->cd(2);
   histCut->Draw();
   
}
