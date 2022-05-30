#include <iostream>
#include <string>
#include <sstream>
#include <TCanvas.h>
#include <TEventList.h>
#include <cstdint>
#include <vector>
#include <signal.h>
#include <map>
#include <algorithm>
#include <regex>
#include <TH1F.h>
#include <TH2.h>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>

#define LENGTH 2000
#define N_BOARD 6
#define N_CH 16
#define N_CLOCK 2000


//-------------------filter-----------------------//

int move_ave(double wave[],int length,int ave_n){
  for(int j=0; j<length-ave_n; j++){
    double tmp=0;
    for(int k=0; k<ave_n; k++){
      tmp+=wave[j+k]/(ave_n);
    }
    wave[j]=tmp;
  }
  return 0;
}

int trapezoidal(double wave[],int length,int L,int G){
  for(int j=0; j<LENGTH-(2*L+G); j++){
    double tmp=0;
    for(int k=0;k<L;k++){
      tmp+=wave[j+k]*(-1/(double)L);
    }
    for(int k=0;k<G;k++){
      tmp+=wave[j+k+G]*0;
    }
    for(int k=0;k<L;k++){
      tmp+=wave[j+k+G+L]*(1/(double)L);
    }
    wave[j]=tmp;
  }
  return 0;
}



int trap(const char *run_n, int trap_L=20, int trap_G=0, int _iEventBegin = 0,
	     int _iEventEnd = -1){ 

  //  TFile *f =new TFile(Form("~/exp/SAKRA/JAEA2021Jun/ana_saka/root_file/test_%s.root",run_n));
    TFile *f =new TFile(Form("~/exp/SAKRA/JAEA2021Jun/ana_saka/root_file/fuji/data_%s.root",run_n));
  TTree *tree=(TTree*)f->Get("tree");

  vector<vector<uint16_t>> *data[N_BOARD] ={0,0,0,0,0,0};
  TBranch *branch[N_BOARD];
  for(int i=0;i<N_BOARD;++i){
    branch[i]=tree->GetBranch(Form("data_%d",i));
    branch[i]->SetAddress(&data[i]);
  }
  double Energy[N_BOARD][N_CH];
  double Energy_[N_BOARD][N_CH];
  tree->SetBranchAddress("Energy",Energy);
  
  
  //  TFile *fout = new TFile(Form("~/exp/SAKRA/JAEA2021Jun/ana_saka/macro/trap_filter/root/trap_test_%s.root",run_n),"recreate");
  TFile *fout = new TFile(Form("~/exp/SAKRA/JAEA2021Jun/ana_saka/macro/trap_filter/root/trap_%s.root",run_n),"recreate");
  TTree *trap = new TTree("trap","trap");

  double tRise[N_BOARD][N_CH];
  double Amax[N_BOARD][N_CH];
  int clkRiseBegin[N_BOARD][N_CH];
  int clkRiseEnd[N_BOARD][N_CH];
  double wave_tmp[LENGTH];

  trap->Branch("tRise",tRise,"tRise[6][16]/D");
  trap->Branch("Amax",Amax,"Amax[6][16]/D");
  trap->Branch("Energy_",Energy_,"Energy_[6][16]/D");
  trap->Branch("clkRiseBegin",clkRiseBegin,"clkRiseBegin[6][16]/I");
  trap->Branch("clkRiseEnd",clkRiseEnd,"clkRiseEnd[6][16]/I");

  int N=tree->GetEntries();
  cout << "all event :" << N << endl;  
  
  int iEventBegin = _iEventBegin <= 0 ? 0 : std::min(_iEventBegin, N);
  int iEventEnd = _iEventEnd < 0 ? N : std::min(_iEventEnd, N);
  std::cout << iEventBegin << " -- " << iEventEnd << std::endl;
  for(int i=iEventBegin;i < iEventEnd; i++){

    if(i % 1000 == 0){
      cout << "\rEvent:" << i << std::flush;
    }
    tree->GetEntry(i);


    for(int iBoard = 0; iBoard < N_BOARD; ++iBoard){
      for(int iCh = 0; iCh < N_CH; ++iCh){
      
	double baseline_cor = 0;
	double peak = 0;
	double peakClk = 0;
	clkRiseBegin[iBoard][iCh]= 0;
	clkRiseEnd[iBoard][iCh] = N_CLOCK;
	Amax[iBoard][iCh] = -1;
	tRise[iBoard][iCh] = -1;
	Energy_[iBoard][iCh]=-1;

	for(int k=0;k<LENGTH;k++){
	  wave_tmp[k]=0;
	}
	
	if(data[iBoard]->at(iCh).size()<2000){
	  continue;
	}

	Energy_[iBoard][iCh]=Energy[iBoard][iCh];
	
	
	for(int iClock=0;iClock<LENGTH;iClock++){
	  if(iBoard<5) wave_tmp[iClock] = 16000 - (double)data[iBoard]->at(iCh).at(iClock);
	  if(iBoard==5) wave_tmp[iClock] = (double)data[iBoard]->at(iCh).at(iClock);
	}
	
	for(int iClock = 300; iClock < 500; iClock++){
	  baseline_cor+=wave_tmp[iClock]/200;
	}

	for(int iClock = 500; iClock < 1500; iClock++){
	  double signal_height = wave_tmp[iClock]-baseline_cor;
	  if(peak <  signal_height){
	    peak = signal_height;
	    peakClk=iClock;
	  }
	}

	for(int iClock = 500; iClock < 1500; iClock++){
	  double signal_height = wave_tmp[iClock]-baseline_cor;
	  if(peak * 0.10 > signal_height){
	    clkRiseBegin[iBoard][iCh] = std::max(iClock, clkRiseBegin[iBoard][iCh]);
	  }
	  if(peak * 0.80 < signal_height){
	    clkRiseEnd[iBoard][iCh] = std::min(iClock, clkRiseEnd[iBoard][iCh]);
	  }
	}
	tRise[iBoard][iCh] = clkRiseEnd[iBoard][iCh] - clkRiseBegin[iBoard][iCh];

	for(int iClock=0;iClock<LENGTH;iClock++){
	  wave_tmp[iClock] = (wave_tmp[iClock]-baseline_cor)/peak;
	}
	trapezoidal(wave_tmp, LENGTH, trap_L, trap_G);

	double trap_max=0;
	double trap_min=0;
	for(int iClock = 500; iClock < 1500; iClock++){
	  double signal_height = wave_tmp[iClock];
	  if(trap_max < wave_tmp[iClock]){
	    trap_max = wave_tmp[iClock];
	  }
	  if(trap_min > wave_tmp[iClock]){
	    trap_min = wave_tmp[iClock];
	  }
	}
	Amax[iBoard][iCh]=trap_max - trap_min;	
      }
    }    
    trap->Fill();
  }
  
  trap->AutoSave();
  fout->Close();
  
  return 0;
}

