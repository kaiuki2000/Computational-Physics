void rootlogon()
{
    printf("Running my rootlogon...\n");
    gInterpreter->AddIncludePath("../src/");
    gSystem->CompileMacro("../src/DataReader.C", "k O");
    gSystem->CompileMacro("../src/DataManip.C", "k O");
    gSystem->CompileMacro("macro1.C", "k O");
    gSystem->CompileMacro("macro2.C", "k O");
    gSystem->CompileMacro("macro3.C", "k O");
    gSystem->CompileMacro("macro4.C", "k O");
}