#include "restaurant.hpp"
#include<vector>

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
