int projection(void){
  int board;
  int ch;
  //TH1F *hch[6][16];
  //  std::vector<TH1D*> hch;
  TH1D *htmp = new TH1D("htmp","temporary hist",4000,0,4000);

  TH1D *hch[6][16];
  
  for(board=4;board<=4;board++){
    for(ch=0;ch<1;ch++){
      //      cout << Form("h%d_%02d", board,ch) << endl;
      hch[board][ch] = new TH1D(Form("h%d_%02d", board,ch),Form("h%d_%02d", board,ch),4000,0,4000);
      mDelila_raw->ProjectionY(hch[board][ch]->GetName(),board*16+ch,board*16+ch+1);
      //      mDelila_raw->ProjectionY(Form("h%d_%02d", board,ch),board*16+ch,board*16+ch+1);

      //      hch[board][ch] = htmp;
      //      hch.push_back(htmp);
    }
  }

  return 0;
}
