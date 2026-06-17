#pragma once
#include <string>
using namespace std;

class EnvironmentalImpact {
public:
    double co2Kg;
    double waterLiters;
    double landM2;

    EnvironmentalImpact(double co2, double water = 0, double land = 0);
    virtual ~EnvironmentalImpact() {}          // virtual destructor for a base class

    string         getImpactLabel();
    virtual int    getScore();                 // virtual: subclasses can override this
};