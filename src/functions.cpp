#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Returns the enum type based on string
 * @param type enum type as a string
 * @return enum type
 */
Type getType(string type) {
    if (type.compare("Chinese") == 0) {
        return Type::Chinese;
    } else if (type.compare("Japanese") == 0) {
        return Type::Japanese;
    } else if (type.compare("Italian") == 0) {
        return Type::Italian;
    } else if (type.compare("Mexican") == 0) {
        return Type::Mexican;
    } else {
        return Type::None;
    }
}

/**
 * Compares the two different restaurants by name.
 * @param one first restaurant
 * @param two second restaurant
 * @param ascending true if ascending order, false if not
 * @return true or false depending on ascending order
 *          if ascending true, then true means one is before two
 *          if ascending false, then true means two is before one
 */
bool sortAlphabetically(Restaurant one, Restaurant two, bool ascending) {
    if (ascending) {
        if (one.name.compare(two.name) < 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if (one.name.compare(two.name) > 0) {
            return true;
        } else {
            return false;
        }
    }
}

/**
 * Compares the two different restaurants by rating.
 * @param one first restaurant
 * @param two second restaurant
 * @param ascending true if ascending order, false if not
 * @return true or false depending on ascending order
 *          if ascending true, then true means one is before two
 *          if ascending false, then true means two is before one
 */
bool sortRating(Restaurant one, Restaurant two, bool ascending) {
    if (ascending) {
        if (one.rating < two.rating) {
            return true;
        } else {
            return false;
        }
    } else {
        if (one.rating > two.rating) {
            return true;
        } else {
            return false;
        }
    }
}

/**
 * Compares the two different restaurants by date.
 * @param one first restaurant
 * @param two second restaurant
 * @param ascending true if ascending order, false if not
 * @return true or false depending on ascending order
 *          if ascending true, then true means one is before two
 *          if ascending false, then true means two is before one
 */
bool sortDate(Restaurant one, Restaurant two, bool ascending) {
    if (ascending) {
        if (one.getYear() < two.getYear()) {
            return true;
        } else if (one.getYear() > two.getYear()) {
            return false;
        } else {
            if (one.getMonth() < two.getMonth()) {
                return true;
            } else if (one.getMonth() > two.getMonth()) {
                return false;
            } else {
                if (one.getDay() < two.getDay()) {
                    return true;
                } else if (one.getDay() > two.getDay()) {
                    return false;
                }
            }
        }
    } else {
        if (one.getYear() > two.getYear()) {
            return true;
        } else if (one.getYear() < two.getYear()) {
            return false;
        } else {
            if (one.getMonth() > two.getMonth()) {
                return true;
            } else if (one.getMonth() < two.getMonth()) {
                return false;
            } else {
                if (one.getDay() > two.getDay()) {
                    return true;
                } else if (one.getDay() < two.getDay()) {
                    return false;
                }
            }
        }
    }

    return false;
}

/**
 * Returns a new list that only includes the type of food
 * @param list list of restaurants 
 * @param sort sorting method (type)
 * @param category the type of food used to sort
 * @return new list of only restaurants from that have that food type
 */
vector<Restaurant> sortCategory(vector<Restaurant>& list, Sort sort, Type type) {
    vector<Restaurant> newList;
    int n = list.size();
    if (sort == Sort::FoodType) {
        for (int i = 0; i < n; i++) {
            if (list[i].type == type) {
                newList.push_back(list[i]);
            }
        }
    }
    return newList;
}

/**
 * Returns a new list that only includes the city or state
 * @param list list of restaurants 
 * @param sort sorting method (city or state)
 * @param category the city or state being used to sort
 * @return new list of only restaurants from that city or state
 */
vector<Restaurant> sortCategory(vector<Restaurant>& list, Sort sort, string category) {
    vector<Restaurant> newList;
    int n = list.size();
    switch(sort) {
        case(Sort::City):
            for (int i = 0; i < n; i++) {
                if (list[i].city.compare(category) == 0) {
                    newList.push_back(list[i]);
                }
            }
            break;
        case(Sort::State):
            for (int i = 0; i < n; i++) {
                if (list[i].state.compare(category) == 0) {
                    newList.push_back(list[i]);
                }
            }
            break;
        default:
            exit(1);
    }

    return newList;
}

/**
 * Merges two vectors together.
 * @param arr array being sorted with the merging
 * @param left index of start of left array
 * @param mid index imbetween left and right array
 * @param right index of end of right array
 * @param sort sorting method used when merging
 */
void merge(vector<Restaurant>& arr, int left, int mid, int right, Sort sort) {
    int n1 = mid - left + 1; // length of first subarray
    int n2 = right - mid; // length of the second subarray

    // Temporary vectors
    vector<Restaurant> L(n1), R(n2);

    // Copying the data to the temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0; // reset i and j to use in next while loop
    int k = left; // have k = left so that it get placed correctly within the orginial array
    
    // Merge the temporary vectors back into the arr
    while (i < n1 && j < n2) {
        // true if taken from left array, false if taken from right array
        bool leftArray;
        switch(sort) {
            case (Sort::Alphabetical_Ascending):
                leftArray = sortAlphabetically(L[i], R[j], true);
                break;
            case (Sort::Alphabetical_Descending):
                leftArray = sortAlphabetically(L[i], R[j], false);
                break;
            case (Sort::Rating_Ascending):
                leftArray = sortRating(L[i], R[j], true);
                break;
            case (Sort::Rating_Descending):
                leftArray = sortRating(L[i], R[j], false);
                break;
            case (Sort::Date_Ascending):
                leftArray = sortDate(L[i], R[j], true);
                break;
            case (Sort::Date_Descending):
                leftArray = sortDate(L[i], R[j], false);
                break;
            default:
                leftArray = false;
        }

        if (leftArray) { 
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining element of L[] if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining element of L[] if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Sorting algorithm that splits vectors then merges them back together.
 * @param arr vector being sorted
 * @param left index of beginning of left array
 * @param right index of end of right array
 * @param sort sorting method used when splitting and merging
 */
void mergeSort(vector<Restaurant>& arr, int left, int right, Sort sort) {
    // if left index greater than or equal to right, stop immediately
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, sort);
    mergeSort(arr, mid + 1, right, sort);
    merge(arr, left, mid, right, sort);
}

/**
 * Reads the restaurants.csv file
 * @return list of restaurants from input file
 */
vector<Restaurant> readInputFile() {
    ifstream input("restaurants.csv");
    // Checks if input file was opened.
    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
        exit(1);
    }

    // Line being read
    string line;
    // Value being read from the line
    string value;
    // List of restaurants, vector is used since it is dynamic
    vector<Restaurant> restaurants;
    while (getline(input, line)) {
        vector<string> values;
        stringstream linestream(line);
        // Uses comma delimiter to extract data
        while (getline(linestream, value, ',')) {
            values.push_back(value);
        }
        int id = stoi(values[0]);
        Type type = getType(values[2]);
        float rating = stof(values[3]);
        // Adds restaurant to list
        restaurants.push_back({id, values[1], type, rating, values[4], values[5], values[6], values[7]});
    }

    return restaurants;
}

/**
 * Writes restaurants to the restaurants.csv file.
 * This is used when removing a restaurant and when editing parts of a restaurant.
 * @param list list of restaurants being written to output file
 */
void writeOutputFile(vector<Restaurant> list) {
    ofstream output("restaurants.csv");
    if (!output.is_open()) {
        cerr << "Error opening output file!" << endl;
        exit(1);
    }
    int n = list.size();
    for (int i = 0 ; i < n; i++) {
        output << list[i].outputString() << endl;
    }
}

/**
 * Adds a new restaurant to the restaurants.csv file
 * @param r restaurant being added
 */
void addNewRestaurant(Restaurant r) {
    ofstream output("restaurants.csv", std::ios::app); 
        // "std::ios::app" tells it to add to the end of the file
    if (!output.is_open()) {
        cerr << "Error opening output file!" << endl;
        exit(1);
    }
    output << r.outputString();
}

/**
 * Removes a restaurant from the list by rewriting restaurants.csv without the restaurant.
 * @param removeId id of the restaurant being removed
 */
void removeRestaurant(int removeId) {
    ifstream input("restaurants.csv");
    // Checks if input file was opened.
    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
        exit(1);
    }

    // Line being read
    string line;
    // Value being read from the line
    string value;
    // List of restaurants, vector is used since it is dynamic
    vector<Restaurant> restaurants;
    int interval = 0;
    while (getline(input, line)) {
        vector<string> values;
        stringstream linestream(line);
        // Uses comma delimiter to extract data
        while (getline(linestream, value, ',')) {
            values.push_back(value);
        }
        int id = stoi(values[0]) - interval;
        if (id == removeId) {
            interval = 1;
            continue;
        }
        Type type = getType(values[2]);
        float rating = stof(values[3]);
        // Adds restaurant to list
        restaurants.push_back({id, values[1], type, rating, values[4], values[5], values[6], values[7]});
    }

    writeOutputFile(restaurants);
}