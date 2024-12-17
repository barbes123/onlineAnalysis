#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>

int binStart = 9201;
int binEnd = 9301;
int rebinFactor = 4;  // Example rebin factor, adjust as necessary
std::string ifile = "selected_run_125_999_eliadeS2.root";
std::string m_name = "mEnergyTimeDiffCS_DC_E_LaBr";

void mat2ascii() {

  std::cout << "Welcome to the automatic mat2ascii macro \n"
	    << "I will do ProjectionX from "<< binStart<<" to "<< binStart <<" bins "<<"\n"
	    << " on TH2F matrix"<< m_name<<" from "<<ifile <<" file."
	    << std::endl;

    // Open the ROOT file
    TFile *file = TFile::Open(Form("%s",ifile.c_str()));  // Replace with the actual path to the file
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open the file!" << std::endl;
        return;
    }

    // Get the TH2F histogram
    TH2F *hist2D = (TH2F*)file->Get(Form("%s",m_name.c_str()));  // Replace with the actual name of the histogram
    if (!hist2D) {
        std::cerr << "Error: Cannot find the histogram!" << std::endl;
        file->Close();
        return;
    }


    TH1D *projX = hist2D->ProjectionX("projX", binStart, binEnd);  // Projecting on X-axis

    // Rebin the histogram (adjust the number of bins as needed)
    if (rebinFactor > 1) projX->Rebin(rebinFactor);
    
    // Find the position of the last occurrence of ".root"
    size_t pos = ifile.find(".root");
    
    // If ".root" is found, remove it
    if (pos != std::string::npos) {
        ifile.erase(pos);  // Remove from the position of ".root" to the end of the string
    }

    // Convert the histogram to ASCII and save it to a file
    std::ofstream outfile(Form("%s_%s.dat",ifile.c_str(), m_name.c_str()));  // Output file to store the data
    if (!outfile) {
        std::cerr << Form("Error: Cannot open the output file %s_%s.dat !",ifile.c_str(), m_name.c_str()) << std::endl;
        file->Close();
        return;
    }
    
    // Write the histogram data (X and Y values) to the file
    for (int i = 1; i <= projX->GetNbinsX(); i++) {
	//        double xValue = projX->GetBinCenter(i);
        double xValue = i;
        double yValue = projX->GetBinContent(i);
        outfile << xValue << "\t" << yValue << std::endl;
    }

    std::cout << "Projection and conversion to ASCII done! \n"<< Form("Data saved to '%s_%s.dat'",ifile.c_str(), m_name.c_str()) << std::endl;

    // Clean up
    outfile.close();
    file->Close();
}

