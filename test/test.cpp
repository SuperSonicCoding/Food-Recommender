#define CATCH_CONFIG_MAIN
#include "header/catch.hpp"
#include "../src/restaurant.hpp"
#include "../src/functions.hpp"

Restaurant r = {1, "Example", Type::Mexican, 1.2, "01/02/2003", "Food", "City", "ST"};
Restaurant r2 = {2, "Another", Type::Japanese, 3.4, "04/05/2006", "Drink", "County", "TS"};

TEST_CASE("Getting day works", "[integer]") {
    REQUIRE(r.getDay() == 2);
}

TEST_CASE("Getting month works", "[integer]") {
    REQUIRE(r.getMonth() == 1);
}

TEST_CASE("Getting year works", "[integer]") {
    REQUIRE(r.getYear() == 2003);
}

TEST_CASE("Extracting enum works", "[type]") {
    REQUIRE(getType("Mexican") == Type::Mexican);
}

TEST_CASE("Getting restaurants from input file works", "[restaurant]") {
    vector<Restaurant> restaurants = readInputFile();
    REQUIRE(restaurants[0].name == "Golden Dragon");
    REQUIRE(restaurants[0].type == Type::Chinese);
    REQUIRE(restaurants[0].rating == 4.27f); // f is at end of number to make it a float
    REQUIRE(restaurants[0].dateLastVisit == "01/16/2026");
    REQUIRE(restaurants[0].favItem == "Honey Chicken");
    REQUIRE(restaurants[0].city == "Raleigh");
    REQUIRE(restaurants[0].state == "NC");
}

TEST_CASE("Alphabetically boolean check works", "[alphabet]") {
    // r.name = "Example", r2.name = "Another"; for reference
    REQUIRE(sortAlphabetically(r, r2, true) == false);
    REQUIRE(sortAlphabetically(r2, r, true) == true);
    REQUIRE(sortAlphabetically(r, r2, false) == true);
    REQUIRE(sortAlphabetically(r2, r, false) == false);
}

TEST_CASE("Rating boolean check works", "[alphabet]") {
    // r.rating = 1.2, r2.rating = 3.4; for reference
    REQUIRE(sortRating(r, r2, true) == true);
    REQUIRE(sortRating(r2, r, true) == false);
    REQUIRE(sortRating(r, r2, false) == false);
    REQUIRE(sortRating(r2, r, false) == true);
}

TEST_CASE("Date boolean check works", "[alphabet]") {
    // r.dateLastVisited = "01/02/2003", r2.dateLastVisited = "04/05/2006"; for reference
    REQUIRE(sortDate(r, r2, true) == true);
    REQUIRE(sortDate(r2, r, true) == false);
    REQUIRE(sortDate(r, r2, false) == false);
    REQUIRE(sortDate(r2, r, false) == true);
}

TEST_CASE("Merge sort works", "[merge]") {
    /**
     * Date for reference:
     * 1,Golden Dragon,Chinese,4.27,01/16/26,Honey Chicken,Raleigh,NC
     * 2,Iso Iso Ramen,Japanese,4.15,12/04/25,Black Ramen,Raleigh,NC
     * 3,Daniel's,Italian,4.02,05/07/25,,Apex,NC
     * 4,Dos Amigos,Mexican,4.12,01/06/26,Carnitas,Boone,NC
     */
    vector<Restaurant> arr = readInputFile();
    int n = arr.size();
    mergeSort(arr, 0, n-1, Sort::Alphabetical_Ascending);
    REQUIRE(arr[0].name == "Daniel's");
    REQUIRE(arr[1].name == "Dos Amigos");
    REQUIRE(arr[2].name == "Golden Dragon");
    REQUIRE(arr[3].name == "Iso Iso Ramen");

    mergeSort(arr, 0, n-1, Sort::Alphabetical_Descending);
    REQUIRE(arr[3].name == "Daniel's");
    REQUIRE(arr[2].name == "Dos Amigos");
    REQUIRE(arr[1].name == "Golden Dragon");
    REQUIRE(arr[0].name == "Iso Iso Ramen");

    mergeSort(arr, 0, n-1, Sort::Rating_Ascending);
    REQUIRE(arr[0].rating == 4.02f);
    REQUIRE(arr[1].rating == 4.12f);
    REQUIRE(arr[2].rating == 4.15f);
    REQUIRE(arr[3].rating == 4.27f);

    mergeSort(arr, 0, n-1, Sort::Rating_Descending);
    REQUIRE(arr[3].rating == 4.02f);
    REQUIRE(arr[2].rating == 4.12f);
    REQUIRE(arr[1].rating == 4.15f);
    REQUIRE(arr[0].rating == 4.27f);

    mergeSort(arr, 0, n-1, Sort::Date_Ascending);
    REQUIRE(arr[0].dateLastVisit == "05/07/2025");
    REQUIRE(arr[1].dateLastVisit == "12/04/2025");
    REQUIRE(arr[2].dateLastVisit == "01/06/2026");
    REQUIRE(arr[3].dateLastVisit == "01/16/2026");

    mergeSort(arr, 0, n-1, Sort::Date_Descending);
    REQUIRE(arr[3].dateLastVisit == "05/07/2025");
    REQUIRE(arr[2].dateLastVisit == "12/04/2025");
    REQUIRE(arr[1].dateLastVisit == "01/06/2026");
    REQUIRE(arr[0].dateLastVisit == "01/16/2026");
}

TEST_CASE("Adding new restaurant", "[post]") {
    Restaurant r = {5, "Another", Type::Japanese, 3.4, "04/05/2006", "Drink", "County", "TS"};
    addNewRestaurant(r);
    vector<Restaurant> list = readInputFile();
    int n = list.size();
    REQUIRE(list[n-1].id == 5);
    REQUIRE(list[n-1].name == "Another");
    REQUIRE(list[n-1].type == Type::Japanese);
    REQUIRE(list[n-1].rating == 3.4f); // f is at end of number to make it a float
    REQUIRE(list[n-1].dateLastVisit == "04/05/2006");
    REQUIRE(list[n-1].favItem == "Drink");
    REQUIRE(list[n-1].city == "County");
    REQUIRE(list[n-1].state == "TS");
}

TEST_CASE("Removing restaurant with id", "[delete]") {
    // Removes the added restaurant from the adding restaurant test case
    vector<Restaurant> list = readInputFile();
    REQUIRE(list.size() == 5);
    removeRestaurant(5);
    list = readInputFile();
    REQUIRE(list.size() == 4);
}

TEST_CASE("Writing to output file", "[write]") {
    vector<Restaurant> list = readInputFile();
    vector<Restaurant> tempList;
    tempList.push_back(r);
    writeOutputFile(tempList);
    vector<Restaurant> newList = readInputFile();
    REQUIRE(newList.size() == 1);
    writeOutputFile(list);
    newList = readInputFile();
    REQUIRE(newList.size() == 4);
}

TEST_CASE("Sorting by type, city, and state ", "[category]") {
    vector<Restaurant> list = readInputFile();
    vector<Restaurant> newList = sortCategory(list, Sort::FoodType, Type::Mexican);
    REQUIRE(newList.size() == 1);
    REQUIRE(newList[0].type == Type::Mexican);
    REQUIRE(newList[0].name == "Dos Amigos");

    newList = sortCategory(list, Sort::City, "Raleigh");
    REQUIRE(newList.size() == 2);
    REQUIRE(newList[0].city == "Raleigh");
    REQUIRE(newList[1].city == "Raleigh");

    newList = sortCategory(list, Sort::State, "NC");
    REQUIRE(newList.size() == 4);
    REQUIRE(newList[0].state == "NC");
    REQUIRE(newList[1].state == "NC");
    REQUIRE(newList[2].state == "NC");
    REQUIRE(newList[3].state == "NC");
}