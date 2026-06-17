#include "WaterImpact.h"

WaterImpact::WaterImpact(double co2, double water, double land)
    : EnvironmentalImpact(co2, water, land)
{
}

// Scores by water (liters per kg) on the same 0-10 scale
int WaterImpact::getScore() {
    if (waterLiters >= 5000) return 10;
    if (waterLiters >= 3000) return 8;
    if (waterLiters >= 1500) return 7;
    if (waterLiters >= 800)  return 5;
    if (waterLiters >= 400)  return 4;
    if (waterLiters >= 150)  return 2;
    return 1;
}