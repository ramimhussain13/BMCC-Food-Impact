#pragma once
#include <string>
#include "EnvironmentalImpact.h"
using namespace std;

class MenuItem {
public:
    string              name;
    double              price;
    int                 category;   // <-- new: 0=Breakfast, 1=Lunch, etc.
    EnvironmentalImpact impact;

    MenuItem(string name, double price, int category, EnvironmentalImpact impact);
};