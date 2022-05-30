// ROOT macro to check the spectrum etc.
void check(void){
  TCanvas *can;
  can = new TCanvas("canvas","Monitor to check the histogram", 1200,800);

  can->Draw();
  can->Divide(3,2);

  can->cd(1);
  can->cd(1)->SetLogz(1);
  h2calib->GetYaxis()->SetRangeUser(1000,20000);
  h2calib->Draw("colz");

  can->cd(4);
  can->cd(4)->SetLogz(1);
  h2kine->GetXaxis()->SetRangeUser(30,50);
  h2kine->GetYaxis()->SetRangeUser(1000,25000);
  h2kine->Draw("colz");

  can->cd(2);
  can->cd(2)->SetLogz(0);
  h_rear->Draw("colz");

  can->cd(5);
  can->cd(5)->SetLogz(0);
  h_front->Draw("colz");

  can->cd(3);
  can->cd(3)->SetLogz(1);
  h2AmaxEne_f->SetTitle("Amax vs Energy (Front)");
  h2AmaxEne_f->Draw("colz");

  can->cd(6);
  can->cd(6)->SetLogz(1);
  h2AmaxEne_r->SetTitle("Amax vs Energy (Rear)");
  h2AmaxEne_r->Draw("colz");
}
