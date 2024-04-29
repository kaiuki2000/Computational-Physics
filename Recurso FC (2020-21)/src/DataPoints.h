#ifndef __DATAPOINTS_H__
#define __DATAPOINTS_H__

#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"

#include "TTimer.h"
#include "Getline.h"
#include "TSystem.h"
#include <cstdio>
#include "TLegend.h"
#include "TText.h"

class DataPoints
{
public:
    //Constructors and destructor
    DataPoints();
    DataPoints(int, double *, double *);
    virtual ~DataPoints();

    //Additional methods
    virtual double Interpolate(double x) { return 0.; }
    virtual void Draw();
    virtual const TGraph &GetGraph() const;
    virtual void Print(std::string filename = ""); //What exactly is this method supposed to do?
                                                   //For now it simply prints the arrays' values in the terminal...

    //Friend methods
    //friend std::ostream &operator<<(std::ostream &, const DataPoints &); //Don't really know what this is supposed to do...

protected:
    int N;           //Number of data points
    double *x, *y;   //Arrays
    TGraph *gPoints; //Graph with data points
    static int NPlots;
};

#endif // __DATAPOINTS_H__
