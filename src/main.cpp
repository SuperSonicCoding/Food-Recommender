#include "restaurant.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Type getType(string type) {
    if (type.compare("Chinese") == 0) {
        return Type::Chinese;
    } else if (type.compare("Japanese") == 0) {
        return Type::Japanese;
    } else if (type.compare("Italian") == 0) {
        return Type::Italian;
    } else if (type.compare("Mexican") == 0) {
        return Type::Mexican;
    }
}

vector<Restaurant> readInputFile() {
    ifstream input("restaurants.csv");
    // Checks if input file was opened.
    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
    }

    string line;
    string value;
    vector<Restaurant> restaurants;
    while (getline(input, line)) {
        vector<string> values;
        stringstream linestream(line);
        // string name;
        // Type type;
        // float rating;
        // string date;
        // string favItem;
        // string city;
        // string state;
        while (getline(linestream, value, ',')) {
            values.push_back(value);
        }
        Type type = Type::values[1]
        Restaurant r = {values[0], values[1], values[2], values[3], values[4], values[5]};
        restaurants.push_back({values[0], values[1], values[2], values[3], values[4], values[5]})
    }
}

int main() {
    return 0;
}