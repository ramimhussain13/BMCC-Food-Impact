#include "ImpactCalculator.h"
#include <algorithm>
#include <string>

// Comparator for sort: higher CO2 comes first
bool compareByCO2(MenuItem a, MenuItem b) {
    return a.impact.co2Kg > b.impact.co2Kg;
}

// Returns all items ordered from highest to lowest footprint
vector<MenuItem> ImpactCalculator::rankByImpact(MenuDatabase db) {
    vector<MenuItem> sorted = db.items;
    sort(sorted.begin(), sorted.end(), compareByCO2);
    return sorted;
}

// Suggests a lower-impact item from the same category, or general advice
string ImpactCalculator::suggestSwap(MenuItem item, MenuDatabase db) {
    // find the lowest-impact item in the same category
    MenuItem *best = nullptr;
    for (size_t i = 0; i < db.items.size(); i++) {
        if (db.items[i].category == item.category) {
            if (best == nullptr || db.items[i].impact.co2Kg < best->impact.co2Kg) {
                best = &db.items[i];
            }
        }
    }

    // if a meaningfully greener option exists in the category, name it
    if (best != nullptr && best->impact.co2Kg < item.impact.co2Kg - 1.0) {
        double saved = item.impact.co2Kg - best->impact.co2Kg;
        return "Try " + best->name + " instead - saves about "
               + to_string((int)saved) + " kg CO2 per kg.";
    }

    // otherwise fall back to general advice by impact level
    if (item.impact.co2Kg > 10)
        return "High impact. Look for a lighter option in this category.";
    if (item.impact.co2Kg >= 3)
        return "Moderate impact. A reasonable everyday choice.";
    return "Low impact - one of the greener choices on the menu.";
}

// Difference in footprint; positive means a is worse than b
double ImpactCalculator::compareCO2(MenuItem a, MenuItem b) {
    return a.impact.co2Kg - b.impact.co2Kg;
}