#include "restaurant.hpp"
#include<vector>
#include <iomanip>

// Width of the name field when listed
const int NAME_WIDTH = 25;

// Width of the type field when listed
const int TYPE_WIDTH = 15;

// Width of the rating field when listed
const int RATING_WIDTH = 6;

// Width of the date field when listed
const int DATE_WIDTH = 13;

// Width of the favorite item field when listed
const int FAV_ITEM_WIDTH = 25;

// Width of the city field when listed
const int CITY_WIDTH = 20;

// Width of the state field when listed
const int STATE_WIDTH = 5;

Type getType(string type);

bool sortAlphabetically(Restaurant one, Restaurant two, bool ascending);

bool sortRating(Restaurant one, Restaurant two, bool ascending);

bool sortDate(Restaurant one, Restaurant two, bool ascending);

vector<Restaurant> sortCategory(vector<Restaurant>& list, Sort sort, Type type);
vector<Restaurant> sortCategory(vector<Restaurant>& list, Sort sort, string category);

void merge(vector<Restaurant>& arr, int left, int mid, int right, Sort sort);

void mergeSort(vector<Restaurant>& arr, int left, int right, Sort sort);

vector<Restaurant> readInputFile();

void addNewRestaurant(Restaurant r);

void removeRestaurant(int id);

void writeOutputFile(vector<Restaurant> list);

void listRestaurants(vector<Restaurant> list);

void promptUser(string infoMessage, int threshold, string prompt, string warning, string& field);
