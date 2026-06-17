#include "LandImpact.h"

LandImpact::LandImpact(double co2, double water, double land)
    : EnvironmentalImpact(co2, water, land)
{
}

// Scores by land use (m2 per kg) on the same 0-10 scale
int LandImpact::getScore() {
    if (landM2 >= 100) return 10;
    if (landM2 >= 50)  return 8;
    if (landM2 >= 20)  return 7;
    if (landM2 >= 8)   return 5;
    if (landM2 >= 3)   return 4;
    if (landM2 >= 1)   return 2;
    return 1;
}