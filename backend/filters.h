#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "fooditems.h"
using namespace std;

inline string normalize(const string& str) {
    string s = str;
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

inline vector<FoodItem> filterData(
    const vector<FoodItem>& input,
    
    float minProtein,
    float maxSugar,
    float minFiber
) {
    vector<FoodItem> result;

    for (const auto& item : input) {
        
        if (item.protein < minProtein) continue;
        if (item.sugar > maxSugar) continue;
        if (item.fiber < minFiber) continue;

        result.push_back(item);
    }

    return result;
}

#endif
