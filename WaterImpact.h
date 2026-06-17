#pragma once
#include "EnvironmentalImpact.h"

// Scores an item by its water usage instead of carbon
class WaterImpact : public EnvironmentalImpact {
public:
    WaterImpact(double co2, double water, double land);

    int getScore() override;   // overrides the base carbon scoring
};