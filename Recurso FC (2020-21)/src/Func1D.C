#include "Func1D.h"

//Constructors
//Constructor 1
Func1D::Func1D(const TF1 *Argf) : f(nullptr)
{
    if (Argf)
    {
        f = new TF1(*Argf);
        Settings();
    }
}

//Constructor 2
Func1D::Func1D(const TF1 &Argf) : Func1D(&Argf) { ; }

//Destructor
Func1D::~Func1D()
{
    if (f)
        delete f;
}

//Additional methods
//Draw method
void Func1D::Draw() const
{
    TApplication A("A", 0, 0);
    TCanvas C1("C1", "Func1D Canvas", 450, 100, 1000, 800);
    f->Draw();
    C1.Update();
    A.Run();
}

//Evaluate method
double Func1D::Eval(double Argx) const
{
    return f->Eval(Argx);
}

//Settings method (protected method)
void Func1D::Settings()
{
    f->SetNpx(1000);
    f->SetLineColor(38);
    f->SetLineWidth(4);
}
