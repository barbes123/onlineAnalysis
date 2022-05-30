int chain(int runno, int vol1, int vol2){

  TChain *chain = new TChain("ELIADE_Tree", "chain of IFIN-HH Tandem data");

  for(int i=vol1;i<=vol2;i++){
    chain->Add(Form("/data/2022_w20_kawabata/root_files/run%4d_%d_ssgant1.root", runno, i));
  }


  TFile *fout = new TFile(Form("./chain/chain%4d_%d_%d.root", runno, vol1, vol2),"RECREATE");
  fout->cd();
  chain->Write();
  fout->Close();

  return 0;
  
}
