void rootlogon()
{
    std::cout << "Running rootlogon.C ..." << std::endl;
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(1111);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(1111);
    gStyle->SetPalette(1);
    gSystem->CompileMacro("Graphs.C", "k O");
}