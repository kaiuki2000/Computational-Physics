#ifndef __FUNC1D_H__
#define __FUNC1D_H__

#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

class Func1D
{
public:
    //Constructors and destructor
    Func1D(const TF1 *Argf = nullptr);
    Func1D(const TF1 &);
    virtual ~Func1D();

    //Draw method
    void Draw() const;

    //Evaluate
    double Eval(double) const;

protected:
    void Settings();
    TF1 *f;
};
#endif // __FUNC1D_H__