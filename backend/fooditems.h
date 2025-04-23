#ifndef FOODITEMS_H
#define FOODITEMS_H

#include <string>
using namespace std;

struct FoodItem {
    int id;
    string category;
    float protein;
    float fiber;
    float sugar;
    float fatGrams;

    float healthScore() const {
        return (protein * 4 + fiber * 3) - (sugar * 2 + fatGrams);
    }
};

#endif
