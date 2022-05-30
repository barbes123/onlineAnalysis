int Fit_3alpha_calib(int brd, int chn)
{
  TFile *fin=new TFile(Form("../selector_files/sum_selected_run_2087_0_100.root"),"READ");
  TH2F *h2d = (TH2F*)fin->Get("mDelila_raw");

  TTree *tree=(TTree*)fin->Get("tree");

  TCanvas *c=new TCanvas("c","c");

  //tree->GetBranchAddress("ADC_col",&ADC_col);
  
  //ofstream ofs("calib2.dat");
  TSpectrum *s = new TSpectrum(4);

  //  vector<vector<double>> mean(16,vector<double>(3));
  double  mean[6][16][3]; // board, channel, peak
  double  sigma[6][16][3]; // board, channel, peak
  TH1D *h[16];
  for(Int_t i=0;i<16;i++){
    h[i]=new TH1D(Form("h_%d",i),Form("h_%d",i),1000,2000,4000);
  }
  double *xpeaks;
  int board;
  int channel;
  for(board=brd;board<=brd;board++){
    //    for(channel=0; channel<=16; channel++){
    for(channel=chn; channel<=chn; channel++){
      h2d->ProjectionY(h[channel]->GetName(),board*16+channel+1,board*16+channel+1);
      s->Search(h[channel],20,"new",0.1);
      if(s->GetNPeaks()!=3 && channel!=0 && channel!=1){
	std::cout << s->GetNPeaks() << std::endl;
	std::cout << "board: " << board << ", channel: " << channel << std::endl;
      }
      xpeaks=s->GetPositionX();
      for(int i=0;i<3;i++){
	mean[board][channel][i]=xpeaks[i];
      }
    }
  }
  for(board=brd;board<=brd;board++){
    //for(channel=0;channel<16;channel++){
    for(channel=chn;channel<=chn;channel++){
     for(int i=0;i<3;i++){
       for(int j=i+1;j<3;j++){
	 if(mean[board][channel][i]>mean[board][channel][j]){
	   double tmp=mean[board][channel][i];
	   mean[board][channel][i]=mean[board][channel][j];
	   mean[board][channel][j]=tmp;
	 }
       }
     }
    }
  }
  // std::cout<< mean[brd][2][0] <<" "
  // 	   << mean[brd][2][1] <<" "
  // 	   << mean[brd][2][2]
  // 	   <<std::endl;

  //  h[2]->Draw("colz");
  
  TF1 *f[16][3];
  board = brd;
  //  for(channel=0; channel<16; channel++){
  for(channel=chn; channel<=chn; channel++){
    for(int i=0; i<3; i++){
      f[channel][i] = new TF1(Form("f%d_%d",channel,i),"gaus",
			    mean[board][channel][i]-20,mean[board][channel][i]+20);
      f[channel][i]->SetParameters(100,mean[board][channel][i],5);
    }
  }

  //  for(channel=0; channel<16; channel++){
  for(channel=chn; channel<=chn; channel++){
    for(int i=0;i<3;i++){
      h[channel]->Fit(Form("f%d_%d",channel,i),"+","",
		      mean[board][channel][i]-20,mean[board][channel][i]+20);
      mean[board][channel][i]=f[channel][i]->GetParameter(1);
      sigma[board][channel][i]=f[channel][i]->GetParameter(2);
    }
  }

  
  TFile *fout=new TFile(Form("calib_board%d_result.root",brd),"RECREATE");
  //  for(channel=0; channel<16; channel++){
  for(channel=chn; channel<=chn; channel++){
    h[channel]->Write();
    std::cout << mean[board][channel][0] << " "
	      << mean[board][channel][1] << " "
	      << mean[board][channel][2] << " "
	      << sigma[board][channel][0] << " "
	      << sigma[board][channel][1] << " "
	      << sigma[board][channel][2] <<std::endl; 
  }
  fout->Close();

  return 0;
}
