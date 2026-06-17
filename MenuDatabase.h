#pragma once
#include <vector>
#include <string>
#include "MenuItem.h"
using namespace std;

class MenuDatabase {
public:
    vector<MenuItem> items;

    void addItem(MenuItem item);
    int  count();
    bool loadFromJson(string path);
};