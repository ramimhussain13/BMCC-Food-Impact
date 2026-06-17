#include "EnvironmentalImpact.h"

EnvironmentalImpact::EnvironmentalImpact(double co2, double water, double land) {
    co2Kg       = co2;
    waterLiters = water;
    landM2      = land;
}

string EnvironmentalImpact::getImpactLabel() {
    if (co2Kg > 10) return "High";
    if (co2Kg >= 3) return "Medium";
    return "Low";
}

// Scores the carbon footprint on a 0-10 scale
int EnvironmentalImpact::getScore() {
    if (co2Kg >= 30)  return 10;
    if (co2Kg >= 15)  return 8;
    if (co2Kg >= 10)  return 7;
    if (co2Kg >= 5)   return 5;
    if (co2Kg >= 3)   return 4;
    if (co2Kg >= 1.5) return 2;
    return 1;
}