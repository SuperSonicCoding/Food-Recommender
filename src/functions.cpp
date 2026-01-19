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
        Type type = getType(values[1]);
        float rating = stof(values[2]);
        // Adds restaurant to list
        restaurants.push_back({values[0], type, rating, values[3], values[4], values[5], values[6]});
    }

    return restaurants;
}