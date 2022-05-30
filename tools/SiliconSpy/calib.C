double param[6][16][2] = {
  //board 4
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {1.941294491,-269.5166183},
    {1.794579292,130.527905},
    {1.81404193,116.3061687},
    {1.794294072,122.6737897},
    {1.797971079,133.5782892},
    {1.858369125,138.0838576},
    {1.865911593,106.2599234},
    {1.795777002,145.2710047},
    {1.76724457,122.8492888},
    {1.764263173,131.8657182},
    {1.83054208,109.8948107},
    {1.788191291,134.3373902},
    {1.819349944,140.6741817},
    {1.801639765,119.121586}
  },
  //board 5
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {1.855925711, 125.9377826},
    {1.8585837, 143.3168574},
    {1.855374662, 131.4200211},
    {1.799910263, 110.6724008},
    {1.985712474, 114.7101703},
    {1.85434737, 141.8536708},
    {1.808633394, 143.8537154},
    {1.828959952, 132.8941309},
    {1.85904655, 104.7790635},
    {1.889340973, 81.16302441},
    {1.896781052, 121.1868417},
    {1.965794347, 89.31107974},
    {1.82449304, 103.6796338},
    {1.891092312, 112.4854833}
  },
  //board 6		   
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {1.866113099, 124.3047643},
    {1.960157158, 71.44350657},
    {1.851404669, 207.7478081},
    {1.854148432, 117.517614 },
    {1.866935954, 112.9999019},
    {1.847160328, 114.5789919},
    {1.788437196, 113.5794746},
    {1.884088475, 84.77609051},
    {1.794600758, 136.2307164},
    {1.862223051, 97.19278111},
    {2.323384185, 99.95991145},
    {2.367861975, 128.0087576},
    {1.742960993, 141.7918281},
    {1.814115079, 128.0454084} 
  },
  //board 7
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {1.898725122, 88.26442896},
    {1.862033559, 95.33099898},
    {1.829268924, 134.9685671},
    {1.808036326, 343.1933418},
    {1.81236541, 139.9068812},
    {1.833025874, 99.96752093},
    {1.826894961, 113.3831675},
    {1.825278472, 102.6969561},
    {1.826996143, 120.4859708},
    {1.875434832, 97.57705338},
    {1.872471418, 85.66457251},
    {1.86013651, 101.5667496},
    {1.888464432, 112.6183713},
    {1.872297458, 93.11702335} 
  },
  //board 8
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {1.957556894, 111.6973272},
    {1.996799924, 90.02113688},
    {1.900372625, 88.94339082},
    {1.906456456, 83.81814212},
    {1.849253058, 108.6933009},
    {1.976384813, 71.85961684},
    {1.976472431, 75.98842347},
    {1.915958707, 92.80067438},
    {2.110493555, 98.8212839 },
    {2.062535569, 70.88901821},
    {2.238758059, 70.69046973},
    {2.094162527, 79.91195236},
    {2.037035119, 87.29481935},
    {2.079282449, 87.97388392} 
  },
  //board 9
  {
    {1.0, 0.0},
    {1.0, 0.0},
    {2.087513059,67.18796648},
    {2.024943241,73.37977616},
    {2.134134529,99.31515922},
    {2.099707861,94.95081885},
    {2.055075467,76.40606422},
    {1.981523878,41.43612956},
    {2.025879426,71.1155777},
    {2.017817809,72.86831104},
    {2.102265769,78.93878188},
    {2.033253659,67.65770306},
    {1.0, 0.0},
    {1.0, 0.0},
    {1.0, 0.0},
    {1.0, 0.0}
  }
};

#define LENGTH 800

const double s1_r1 = 48/2.0;  // inner radius
const double s1_r2 = 96/2.0;  // outer radiu
const double s1_dist = 40;

int get_front_rear(Int_t mod, Int_t ch){ // return val: 0-->front, 1-->rear, 2-->else
  if(mod<4) return 2;
  if(mod>=4 && (ch==0 || ch==1) ) return 2;
  if((mod==4 || mod==5 || mod==6 || mod==7) && ch>=2) return 0;
  if(mod==8 && ch>=2 && ch<=9) return 0;
  if(mod==8 && ch>=10) return 1;
  if(mod==9 && ch>=2)  return 1;

  return 2;
}

double get_rear_phi(Int_t mod, Int_t ch){
  int rch=-1;
  double phi=0;
  if(mod==8 && ch>=10) rch=ch-10;
  if(mod==9 && ch>=2 ) rch=ch+4;

  if(rch%2==0 && rch>=0) phi = 180 - 22.5/2.0 - 22.5*(rch+1);
  if(rch%2==1 && rch>=0) phi = 180 - 22.5/2.0 - 22.5*(rch-1);  
  return phi*TMath::DegToRad();
}

int get_front_ch_order(Int_t mod, Int_t ch){
  if(mod==4 && ch>=2) return ch-2;
  if(mod==5 && ch>=2) return ch+12;
  if(mod==6 && ch>=2) return ch+26;    
  if(mod==7 && ch>=2) return ch+40;
  if(mod==8 && ch>=2 && ch<=9) return ch+54;      
  return 100;
}

double get_front_phi(int front_ch){
  double phi=0;
  if(front_ch>=0 && front_ch<64){
    phi = 135 + 90*((int)(front_ch/16));
  }
  return phi*TMath::DegToRad();
}

double get_front_r(int front_ch){
  double strp_wid = (s1_r2 - s1_r1)/16.0;
  int section = (int)(front_ch/16);
  double r=0;
  
  if(section==0 || section==3){
    if(front_ch%2==0) r = s1_r1 + strp_wid*(1.5) + strp_wid*(front_ch%16);
    if(front_ch%2==1) r = s1_r1 + strp_wid*(0.5) + strp_wid*((front_ch%16) - 1);    
  }

  if(section==1 || section==2){
    if(front_ch%2==0) r = s1_r2 - strp_wid*(1.5) - strp_wid*(front_ch%16);
    if(front_ch%2==1) r = s1_r2 - strp_wid*(0.5) - strp_wid*((front_ch%16) - 1);    
  }
  
  return r;
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


double get_front_theta(int front_ch){
  double strp_wid = (s1_r2 - s1_r1)/16.0;
  int section = (int)(front_ch/16);
  double r=0;
  
  if(section==0 || section==3){
    if(front_ch%2==0) r = s1_r1 + strp_wid*(1.5) + strp_wid*(front_ch%16);
    if(front_ch%2==1) r = s1_r1 + strp_wid*(0.5) + strp_wid*((front_ch%16) - 1);    
  }

  if(section==1 || section==2){
    if(front_ch%2==0) r = s1_r2 - strp_wid*(1.5) - strp_wid*(front_ch%16);
    if(front_ch%2==1) r = s1_r2 - strp_wid*(0.5) - strp_wid*((front_ch%16) - 1);    
  }

//  if(section==1 || section==2){
//    if(front_ch%2==0) r = s1_r1 + strp_wid*(1.5) + strp_wid*(front_ch%16);
//    if(front_ch%2==1) r = s1_r1 + strp_wid*(0.5) + strp_wid*((front_ch%16) - 1);    
//  }
//
//  if(section==0 || section==3){
//    if(front_ch%2==0) r = s1_r2 - strp_wid*(1.5) - strp_wid*(front_ch%16);
//    if(front_ch%2==1) r = s1_r2 - strp_wid*(0.5) - strp_wid*((front_ch%16) - 1);    
//  }
  
  return atan(r/s1_dist);
}

double get_front_ex(double theta, double ene){
  const double beam_ene = 25.0;
  const double AMU = 931.4943;
  const double mass_ex_12c = 0;
  const double mass_ex_4he = 2.425;
  const double mass_ex_13c = 3.125;    

  double mass_12c = AMU*12 + mass_ex_12c;
  double mass_4he = AMU*4  + mass_ex_4he;
  double mass_13c = AMU*13 + mass_ex_13c;  
  
  double m1, m2, m3, m4;
  double E1, E3;
  double p1, p3;

  double s,t,u;
  double total_m4;
  double ex4;
  
  m1 = mass_4he;
  m2 = mass_12c;
  m3 = mass_4he;
  m4 = mass_12c;

//  m1 = mass_4he;
//  m2 = mass_13c;
//  m3 = mass_4he;
//  m4 = mass_13c;
  
  E1 = m1 + beam_ene;
  E3 = m3 + ene;  

  p1 = sqrt(E1*E1-m1*m1);
  p3 = sqrt(E3*E3-m3*m3);  
  
  s = m1*m1 + m2*m2 + 2*m2*E1;
  t = m1*m1 + m3*m3 + 2*(p1*p3*cos(theta) - E1*E3);
  u = m2*m2 + m3*m3 - 2*m2*E3;

  total_m4 = sqrt(s+t+u - m1*m1 -m2*m2 - m3*m3);
  ex4 = total_m4 - m4;

  //  printf("ex=%f\n", ex4);
  
  return ex4;
}

int calib(int runno, int vol1, int vol2, int nevt=-1){
  TFile *fin = new TFile(Form("./chain/chain%4d_%d_%d.root", runno, vol1, vol2),"READ");

  fin->cd();
  TTree *tree = (TTree*)fin->Get("ELIADE_Tree");
  int nevent = tree->GetEntries();
  if(nevt<0){
  } else {
    nevent = nevt;
  }

  UShort_t ChargeLong;
  UChar_t Mod;
  UChar_t Ch;
  // ULong64_t TimeStamp;
  Double_t FineTS;
  UShort_t Signal[LENGTH];

  Double_t clong=0;
  Int_t mod=0;
  Int_t ch=0;

  TH2D *h2raw = new TH2D("h2raw","raw", 100,100,200,1000,0,20000);
  TH2D *h2calib = new TH2D("h2calib","calib", 100,100,200,1000,0,40000);

  TH2D *h2raw2 = new TH2D("h2raw2","raw (Amax gated)", 100,100,200,1000,0,20000);
  TH2D *h2calib2 = new TH2D("h2calib2","calib (Amax gated)", 100,100,200,1000,0,40000);

  TH2D *h2ex = new TH2D("h2ex","Ex", 100,100,200, 220,-2,20);
  TH2D *h2th = new TH2D("h2th","theta",  100,100,200, 90,0,90);  

  TH2D *h2kine = new TH2D("h2kine","Ene vs theta", 45,0,90, 200,0,25000);
  h2kine->GetXaxis()->SetTitle("Scattering angle (deg)");
  h2kine->GetYaxis()->SetTitle("Energy (keV)");  

  TH2D *h2AmaxEne_f = new TH2D("h2AmaxEne_f","Amax vs Energy", 500,0,30000,500,0.7,1.3);
  h2AmaxEne_f->GetXaxis()->SetTitle("Energy(keV)");
  h2AmaxEne_f->GetYaxis()->SetTitle("Amax");  

  TH2D *h2AmaxEne_r = new TH2D("h2AmaxEne_r","Amax vs Energy", 500,0,30000,500,0.7,1.3);
  h2AmaxEne_r->GetXaxis()->SetTitle("Energy(keV)");
  h2AmaxEne_r->GetYaxis()->SetTitle("Amax");  

  TH1D *h1thgs = new TH1D("h1thgs","angle dist. of g.s.", 45,0,90);
  TH1D *h1th2p = new TH1D("h1th2p","angle dist. of 4.44 state", 45,0,90);  

  TH2D *h2exth = new TH2D("h2exth","theta vs Ex", 220,-2,20, 45,0,90);
  
  /* Define hit map histograms */
  double s1_rm = (s1_r1+s1_r2)/2.0;
  
  // Rear histogram
  TH2Poly *h_rear = new TH2Poly();
  h_rear->SetTitle("S1 Rear Hit Pattern");
  h_rear->SetName("h_rear");  

  Double_t s1r_x[20], s1r_y[20];
  
  Int_t s1r_i;
  double dtheta1r = 2*TMath::Pi()/16.0;
  double dtheta2r = dtheta1r/9.0;

  double theta_start, theta_end;
  int i;
  double tmp_theta;
  
  for(s1r_i=0; s1r_i<16; s1r_i++){
    theta_start = s1r_i*dtheta1r;
    theta_end = (s1r_i+1)*dtheta1r;    

    i=0;
    s1r_x[i] = s1_r1*cos(theta_start);
    s1r_y[i] = s1_r1*sin(theta_start);    

    // outer circle
    tmp_theta = theta_start;
    for(i=1; i<=10; i++){
      s1r_x[i] = s1_r2*cos(tmp_theta);
      s1r_y[i] = s1_r2*sin(tmp_theta);      
      tmp_theta += dtheta2r;
    }

    // inner circle
    tmp_theta = theta_end;
    for(i=11; i<20; i++){
      s1r_x[i] = s1_r1*cos(tmp_theta);
      s1r_y[i] = s1_r1*sin(tmp_theta);      
      tmp_theta -= dtheta2r;
    }
    
    h_rear->AddBin(20, s1r_x, s1r_y);
  }
  
  //  h_rear->Draw("colz");
  
  
  // Front histogram
  TH2Poly *h_front = new TH2Poly();
  h_front->SetTitle("S1 Front Hit Pattern");
  h_front->SetName("h_front");  
  
  Double_t s1f_x[80], s1f_y[80];
  int s1f_i, s1f_j;
  
  double dtheta1f = 2*TMath::Pi()/4.0;
  double dtheta2f = dtheta1f/39.0;
  
  double r_start, r_end;
  double dr = (s1_r2 - s1_r1)/16.0;
  
  for(s1f_i=0; s1f_i<4; s1f_i++){
    theta_start = s1f_i*dtheta1f;
    theta_end = (s1f_i+1)*dtheta1f;    

    for(s1f_j=0; s1f_j<16; s1f_j++){
      r_start = s1_r1 + s1f_j*dr;
      r_end = s1_r1 + (s1f_j+1)*dr;      
      
      i=0;
      s1f_x[i] = r_start*cos(theta_start);
      s1f_y[i] = r_start*sin(theta_start);    
      
      tmp_theta = theta_start;
      for(i=1; i<=40; i++){
	s1f_x[i] = r_end*cos(tmp_theta);
	s1f_y[i] = r_end*sin(tmp_theta);    	
	tmp_theta += dtheta2f;
      }
      
      // inner circle
      tmp_theta = theta_end;
      for(i=41; i<80; i++){
	s1f_x[i] = r_start*cos(tmp_theta);
	s1f_y[i] = r_start*sin(tmp_theta);      
	tmp_theta -= dtheta2f;
      }
      
      h_front->AddBin(80, s1f_x, s1f_y);
      
    }
  }


  // matrix histogram
  TH2Poly *h_matrix = new TH2Poly();
  h_matrix->SetTitle("S1 Matrix Hit Pattern");
  h_matrix->SetName("h_matrix");  

  Double_t s1m_x[20], s1m_y[20];
  Int_t s1m_i, s1m_j;

  double dtheta1m = 2*TMath::Pi()/16.0;
  double dtheta2m = dtheta1r/9.0;

  for(s1m_i=0; s1m_i<16; s1m_i++){
    theta_start = s1m_i*dtheta1m;
    theta_end = (s1m_i+1)*dtheta1m;    

    for(s1m_j=0; s1m_j<16; s1m_j++){
      r_start = s1_r1 + s1m_j*dr;
      r_end = s1_r1 + (s1m_j+1)*dr;      

      i=0;
      s1m_x[i] = r_start*cos(theta_start);
      s1m_y[i] = r_start*sin(theta_start);    
      
      tmp_theta = theta_start;
      for(i=1; i<=10; i++){
	s1m_x[i] = r_end*cos(tmp_theta);
	s1m_y[i] = r_end*sin(tmp_theta);      
	tmp_theta += dtheta2m;
      }

      // inner circle
      tmp_theta = theta_end;
      for(i=11; i<20; i++){
	s1m_x[i] = r_start*cos(tmp_theta);
	s1m_y[i] = r_start*sin(tmp_theta);      
	tmp_theta -= dtheta2m;
      }
      
      h_matrix->AddBin(20, s1m_x, s1m_y);
    }
  }
  // hit pattern histogram end


  
  tree->SetBranchAddress("ChargeLong", &ChargeLong);
  tree->SetBranchAddress("Mod", &Mod);
  tree->SetBranchAddress("Ch", &Ch);
  // tree->SetBranchAddress("TimeStamp", &TimeStamp);
  tree->SetBranchAddress("FineTS", &FineTS);
  tree->SetBranchAddress("Signal", &Signal);
  
  int fr;
  double rear_phi;
  int front_ch;
  double front_phi, front_r, front_theta;
  double front_ex;
  double tmp_ene;
  double wave_tmp[LENGTH];
  
  //  for(int i=0;i<100;i++){
  for(int i=0;i<nevent;i++){    
    tree->GetEntry(i);

    clong=(Double_t)ChargeLong;
    mod=(Int_t)Mod;
    ch=(Int_t)Ch;

    // Skip ROSPHERE event
    if(mod<4) continue;

  
    if(mod>=4 && mod<=9){
      // Amax culc.
      double baseline_cor = 0;
      double peak = 0;
      for(int k=0;k<LENGTH;k++)	wave_tmp[k]=0;
    
      for(int iClock=0;iClock<LENGTH;iClock++)  wave_tmp[iClock] = Signal[iClock];
      for(int iClock = 0; iClock < 100; iClock++) baseline_cor+=wave_tmp[iClock]/100;//baseline
    
      for(int iClock = 100; iClock < LENGTH; iClock++){//peak height 
	double signal_height = wave_tmp[iClock]-baseline_cor;
	if(peak <  signal_height){
	  peak = signal_height;
	}
      }
    
      for(int iClock=0;iClock<LENGTH;iClock++){
	wave_tmp[iClock] = (wave_tmp[iClock]-baseline_cor)/peak;
      }
      trapezoidal(wave_tmp, LENGTH, 5, 0);
    
      double trap_max=0;
      double trap_min=0;
      double Amax=0;
      for(int iClock = 0; iClock < LENGTH; iClock++){
	double signal_height = wave_tmp[iClock];
	if(trap_max < wave_tmp[iClock]){
	  trap_max = wave_tmp[iClock];
	}
	if(trap_min > wave_tmp[iClock]){
	  trap_min = wave_tmp[iClock];
	}
      }
      Amax=trap_max - trap_min;

      tmp_ene = clong*param[mod-4][ch][0]+param[mod-4][ch][1];

      h2raw->Fill(100+(mod-4)*16+ch, clong);
      h2calib->Fill(100+(mod-4)*16+ch, tmp_ene);
      if( Amax> 0.95){
	h2raw2->Fill(100+(mod-4)*16+ch, clong);
	h2calib2->Fill(100+(mod-4)*16+ch, tmp_ene);
      }

      fr = get_front_rear(mod, ch);      

      // rear
      if(fr==1){ 
	rear_phi = get_rear_phi(mod, ch);
	//if(tmp_ene>1000) h_rear->Fill(s1_rm*cos(rear_phi), s1_rm*sin(rear_phi));
	h_rear->Fill(s1_rm*cos(rear_phi), s1_rm*sin(rear_phi));	
	h2AmaxEne_r->Fill(tmp_ene,Amax);
      }

      // front
      if(fr==0){
	front_ch = get_front_ch_order(mod, ch);
	front_phi = get_front_phi(front_ch);
	front_r = get_front_r(front_ch);	
	//if(tmp_ene>1000) h_front->Fill(front_r*cos(front_phi), front_r*sin(front_phi));
	h_front->Fill(front_r*cos(front_phi), front_r*sin(front_phi));	

	front_theta = get_front_theta(front_ch);
	front_ex = get_front_ex(front_theta, tmp_ene/1000.0);
	h2ex->Fill(100+(mod-4)*16+ch, front_ex);
	h2th->Fill(100+(mod-4)*16+ch, front_theta*TMath::RadToDeg());	
	h2kine->Fill(front_theta*TMath::RadToDeg(), tmp_ene);
	if(front_ex>-2 && front_ex<2) h1thgs->Fill(front_theta*TMath::RadToDeg());
	if(front_ex> 3 && front_ex<6) h1th2p->Fill(front_theta*TMath::RadToDeg());	
	h2exth->Fill(front_ex, front_theta*TMath::RadToDeg());
	h2AmaxEne_f->Fill(tmp_ene,Amax);
      }

      // matrix
      {
	front_ch = get_front_ch_order(mod, ch);
	front_phi = get_front_phi(front_ch);
	front_r = get_front_r(front_ch);	
	rear_phi = get_rear_phi(mod, ch);

      	h_matrix->Fill(front_r*cos(rear_phi), front_r*sin(rear_phi));	
      }
      
      
    }

    if(i%100000==0) std::cout << "\rEvent: " << i << std::flush;

    
  } // event loop to here

  TFile *fout = new TFile(Form("./output/chain%4d_calib_%d_%d.root", runno, vol1, vol2),"RECREATE");
  fout->cd();

  tree->Write();

  h2raw->Write();
  h2calib->Write();
  h2raw2->Write();
  h2calib2->Write();
  h2ex->Write();
  h2th->Write();
  h2kine->Write();
  h2AmaxEne_r->Write();
  h2AmaxEne_f->Write();
  h1thgs->Write();
  h1th2p->Write();      
  h2exth->Write();
  
  h_rear->Write();
  h_front->Write();
  h_matrix->Write();
  
  fout->Close();
  fin->Close();
  
  return 0;
}
