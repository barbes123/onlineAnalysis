#include <iostream>
#include <fstream>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TString.h"
void TimeAlignementTrigger(TH2 *matrix, float alignment_pos=0.)
{

  std::cout << "Welcome to the automatic TimeAlignement macro \n"
	    << "I will calculate by default the offset to put in the LookUpTable\n"
	    << "to put the coincidence peak in "<<alignment_pos <<" , except if you give a second parameter"
	    << std::endl;
  fstream outputFile;
  outputFile.open("TimeCalib.dat", ios_base::out);		    

  TString mat_name = matrix->GetName();
  Int_t nb_bin_mat  = matrix->GetYaxis()->GetNbins();
  Float_t range_min = matrix->GetYaxis()->GetXmin();
  Float_t range_max = matrix->GetYaxis()->GetXmax();

 TF1 *gaus = new TF1("gaus","gaus", 0,100e3);
 TF1 *gaus2 = new TF1("gaus","gaus", 0,100e3);
 TCanvas *c1 = new TCanvas("c1","c1");
//  TCanvas *c2 = new TCanvas("c2","c2");
 TH1D *proj_y =new TH1D("projection","proj",nb_bin_mat,range_min,range_max);
 TH1D *proj_y2 =new TH1D("projection2","proj2",nb_bin_mat,range_min,range_max);
 
 int delta = 3000;
 

   for(int jj=0 ; jj<=matrix->GetXaxis()->GetNbins() ; jj++){
    matrix->ProjectionY(proj_y->GetName(),jj,jj);    
    if (proj_y->GetEntries() == 0) continue;
    proj_y->GetXaxis()->SetRangeUser(-50e3,80e4);
    proj_y->Rebin(8);
//     proj_y2->GetXaxis()->SetRangeUser(-100e3,100e4);
    
    proj_y->SetTitle(Form("dom%i",jj));
//     proj_y2->SetTitle(Form("dom%i_precise",jj));
    int max_bin = proj_y->GetMaximumBin();
    int max_bin_pos = proj_y-> GetBinCenter(max_bin);  
    
    if (jj>30) delta = 16000;
    
    c1->cd();
    gaus->SetParameter(1,max_bin_pos);
    gaus->SetParLimits(1,max_bin_pos-2000,max_bin_pos+2000);
    proj_y->Fit(gaus,"MR","",max_bin_pos-delta,max_bin_pos+delta);
    
    gaus2->SetParameter(1,gaus->GetParameter(1));
    gaus2->SetParLimits(1,gaus->GetParameter(1) -1000,gaus->GetParameter(1) +1000);
    
    proj_y->Draw();
    
//     c2->cd();
 
//  
//     proj_y2->Fit(gaus2,"MR","",max_bin_pos-delta,max_bin_pos+delta);
//     proj_y2->Draw();
    

   std::cout<<" dom "<<jj-1<<" max_bin "<<max_bin<<" max bin "<< " max_bin_pos "<< max_bin_pos <<" gaus1 "<<gaus->GetParameter(1)<<" gaus2 "<< gaus2->GetParameter(1) <<"\n";
//    std::cout<<jj-1<<" max_bin "<<max_bin<<" max bin "<< " max_bin_pos "<< max_bin_pos <<"\n";

//    std::cout << "   Offset for domain " << j+channel_offset << "  " << gaus->GetParameter(1) << std::endl;;
    std::cout << " domain " << jj-1<<" offset " << proj_y-> GetBinCenter(max_bin) - alignment_pos << " maxbin_pos " << proj_y-> GetBinCenter(max_bin) << std::endl;;
    //outputFile << j+channel_offset-1 << "  " << gaus->GetParameter(1) <<"\n";;
    //outputFile << j+channel_offset-1 << "  " << max_value<< " offset: "<< alignment_pos - max_value <<"\n";;
//     outputFile << jj-1 << "  " << proj_y-> GetBinCenter(max_bin) - alignment_pos <<"\n";;
    outputFile << jj-1 << "  " << gaus->GetParameter(1) - alignment_pos <<"\n";;
    
    c1->WaitPrimitive();
    proj_y->Reset();
   }
    outputFile.close();
}
