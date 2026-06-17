#pragma once
#include <vector>
#include <string>
#include "MenuDatabase.h"
using namespace std;

class ImpactCalculator {
public:
    vector<MenuItem> rankByImpact(MenuDatabase db);
    string           suggestSwap(MenuItem item, MenuDatabase db);
    double           compareCO2(MenuItem a, MenuItem b);
};