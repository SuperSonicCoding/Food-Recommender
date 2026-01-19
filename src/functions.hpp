#include "restaurant.hpp"
#include<vector>

Type getType(string type);

vector<Restaurant> readInputFile();

bool sortAlphabetically(Restaurant one, Restaurant two, bool ascending);

bool sortRating(Restaurant one, Restaurant two, bool ascending);

bool sortDate(Restaurant one, Restaurant two, bool ascending);

void merge(vector<Restaurant>& arr, int left, int mid, int right, Sort sort);

void mergeSort(vector<Restaurant>& arr, int left, int right, Sort sort);
