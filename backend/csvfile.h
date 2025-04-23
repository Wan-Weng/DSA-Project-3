#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "fooditems.h"
using namespace std;

inline vector<FoodItem> loadFoodData(const string& filename) {
    vector<FoodItem> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        vector<string> columns;
        string cell;
        bool inQuotes = false;
        stringstream current;

        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                columns.push_back(current.str());
                current.str("");
                current.clear();
            } else {
                current << c;
            }
        }
        columns.push_back(current.str());

        if (columns.size() < 25) {
            continue;
        }

        FoodItem item;
        bool valid = true;

        try {
            item.category = columns[0];
            item.category.erase(remove_if(item.category.begin(), item.category.end(), ::isspace), item.category.end());
            transform(item.category.begin(), item.category.end(), item.category.begin(), ::tolower);

            const string& idStr = columns[2];
            if (all_of(idStr.begin(), idStr.end(), ::isdigit)) {
                item.id = stoi(idStr);
            } else {
                cerr << "Skipping row due to bad value in column 2: '" << idStr << "' (Non-numeric ID)\n";
                continue;
            }

            item.fiber    = stof(columns[9]);
            item.protein  = stof(columns[13]);
            item.sugar    = stof(columns[17]);
            item.fatGrams = stof(columns[23]);

        } catch (const exception& e) {
            cerr << "Skipping row due to parsing error: " << e.what() << endl;
            valid = false;
        }

        if (valid) {
            data.push_back(item);
        }
    }

    file.close();

    if (getenv("LOOKUP_MODE") == nullptr) {
        cerr << "Loaded " << data.size() << " valid food items.\n";
    }

    return data;
}

#endif
