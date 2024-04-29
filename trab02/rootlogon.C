#include <iostream>
#include "TStyle.h"
#include "TROOT.h"
#include "TSystem.h"
#include "Getline.h"

void rootlogon()
{
    std::cout << "Running rootlogon.C ..." << std::endl;
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(1111);
    gStyle->SetOptTitle(1);
    gStyle->SetOptFit(1111);
    gStyle->SetPalette(1);
    

    gSystem->CompileMacro("TGraphsMacro.C", "k O");
    gROOT->ProcessLine("TGraphsMacro()");
}