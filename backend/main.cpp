#include <iostream>
#include <string>
#include <vector>
#include "fooditems.h"
#include "csvfile.h"
#include "topRank.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    
    if (argc == 3 && string(argv[1]) == "--lookup") {
        string targetId = argv[2];
        vector<FoodItem> data = loadFoodData("food.csv");
        for (const auto& item : data) {
            if (to_string(item.id) == targetId) {
                cout << item.category << endl;
                return 0;
            }
        }
        cerr << "Food ID not found.\n";
        return 1;
    }
    float protein = stof(argv[1]);
    float sugar = stof(argv[2]);
    float fiber = stof(argv[3]);
    int k = stoi(argv[4]);

    vector<FoodItem> foodDatabase = loadFoodData("food.csv");

    TopKResult result = runTopKSearch(
        foodDatabase,
        protein,
        sugar,
        fiber,
        k
    );

    json output;
    output["k"] = k;
    output["heap_time"] = result.heap_time_ms;
    output["sort_time"] = result.sort_time_ms;

    for (int i = 0; i < result.heap_results.size(); ++i) {
        const auto& item = result.heap_results[i];
        output["heap_results"][i]["id"] = item.id;
        output["heap_results"][i]["protein"] = item.protein;
        output["heap_results"][i]["fiber"] = item.fiber;
        output["heap_results"][i]["sugar"] = item.sugar;
        output["heap_results"][i]["fat"] = item.fatGrams;
        output["heap_results"][i]["score"] = item.healthScore();
    }

    cout << output.dump() << endl;
    return 0;
}
