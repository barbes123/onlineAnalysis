// ROOT macro to generate calibration parameter file
// from Dmitry's LookUpTable

#include <fstream>
#include <iostream>
#include <vector>
#include <array>


struct calPar
{
public:
  double offset;
  double slope;
};

void GenCalPar()
{
  //auto fileName = "./LUT_DELILA_09_03_22.dat";
  auto fileName = "./input.dat";
  std::ifstream fin(fileName);

  constexpr int nMods = 10;
  constexpr int nChs = 16;
  std::array<std::array<calPar, nChs>, nMods> par;
  for(auto iMod = 0; iMod < nMods; iMod++) {
    for(auto iCh = 0; iCh < nChs; iCh++) {
      par[iMod][iCh].offset = 0.;
      par[iMod][iCh].slope = 1.;
    }
  }
  
  std::string buf;
  while(std::getline(fin, buf)){
    // # is commen line
    if(buf[0] == std::string("#")) continue;
    std::cout << buf << std::endl;
    std::stringstream ss(buf);

    // The first element is id (digitizer number * 100 + channel)
    int id;
    ss >> id;
    int mod = id / 100;
    int ch = id - (mod * 100);

    // last and second last is the parameter
    double tmp;
    std::vector<double> parVec;
    while(ss >> tmp) parVec.push_back(tmp);    
    par[mod][ch].slope = parVec[parVec.size() - 1];  
    par[mod][ch].offset = parVec[parVec.size() - 2];

    std::cout << id <<" "<< mod <<" "<< ch <<" "<< std::fixed << std::setprecision(6)
	      << par[mod][ch].offset <<" "<< par[mod][ch].slope << std::endl;  
  }
  
  fin.close();

  std::ofstream fout("calibration.dat");
  for(auto iMod = 0; iMod < nMods; iMod++) {
    for(auto iCh = 0; iCh < nChs; iCh++) {
      fout << iMod <<" "
           << iCh <<" "
	   << std::fixed << std::setprecision(6)
           << par[iMod][iCh].offset <<" "
           << par[iMod][iCh].slope << std::endl;
    }
  }
  fout.close();
  
}
