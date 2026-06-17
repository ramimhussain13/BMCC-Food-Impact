#pragma once
#include "EnvironmentalImpact.h"

// Scores an item by its land use instead of carbon
class LandImpact : public EnvironmentalImpact {
public:
    LandImpact(double co2, double water, double land);

    int getScore() override;   // overrides the base carbon scoring
};