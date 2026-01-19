#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<string>
#include<ctime>

using namespace std;

/**
 * The different ways to sort the list of restaurants.
 */
enum class Sort {
    Alphabetical_Ascending,
    Alphabetical_Descending,
    Rating_Ascending,
    Rating_Descending,
    Date_Ascending,
    Date_Descending,
    FoodType,
    City,
    State,
};

/**
 * The type of food the restaurant serves.
 *      !!! Add more later
 */
enum class Type {
    Chinese,
    Italian,
    Japanese,
    Mexican,
    None,
};

/**
 * Uses to represent a restaurant. 
 */
struct Restaurant {
    // Name of restaurant
    string name;
    // Type of food at restaurant
    Type type;
    // Personal rating of restaruant
    float rating;
    // Date since last visit
    string dateLastVisit;
    // Favorite item at restaurant
    string favItem;
    // City where restaurant is
    string city;
    // State where restaurant is
    string state;

    int getDay() {
        return stoi(dateLastVisit.substr(3));
    }

    int getMonth() {
        return stoi(dateLastVisit.substr(0,2));
    }

    int getYear() {
        return stoi(dateLastVisit.substr(6));
        // time_t now = time(0);
        // tm* ltm = localtime(&now);
        // cout << "Time: " << nowLocal << endl;
        // return 0;
    };

    string typeToString() {
        switch(type) {
            case Type::Chinese:
                return "Chinese";
                break;
            case Type::Japanese:
                return "Japanese";
                break;
            case Type::Italian:
                return "Italian";
                break;
            case Type::Mexican:
                return "Mexican";
                break;
            default:
                return "none";
        }
    }

    string toString() {
        return "Name: " + name + "\nType: " + typeToString() + "\nRating: " + to_string(rating) +
                "\nDate: " + dateLastVisit + "\nFav: " + favItem + "\nCity and State: " + city + ", " + state;
    }
};

#endif
