#include "restaurant.hpp"
#include "functions.hpp"

/**
 * Main function.
 */
int main() {
    vector<Restaurant> list = readInputFile();
    int n = list.size();
    mergeSort(list, 0, n-1, Sort::Alphabetical_Ascending);
    listRestaurants(list);
    cout << endl << "Welcome to Food Recommender! What would you like to do?" << endl;
    cout << "Options:" << endl;
    cout << "   Add Restaurant" << endl;
    cout << "   Edit Restaurant" << endl;
    cout << "   Remove Restaurant" << endl;
    cout << "   Sort Restaurants" << endl;
    cout << "   Quit" << endl << endl;
    
    string input;
    while (cin >> input) {
        if (input.find("add") >= 0 || input.find("Add") >= 0) {
            string name, type, rating, date, favItem, city, state;
            cout << "Please fill out these fields:" << endl;

            // cout << "Max name length is " << NAME_WIDTH << ".\n";
            // cout << setw(15) << "Name:" << " ";
            // cin >> name;
            // if (name.length() > NAME_WIDTH) {
            //     cout << "Name too long. Please try again.";
            // }
            promptUser("Max name length is: ", NAME_WIDTH, "Name:", "Name too long. Please try again.", name);
            promptUser("Max type length is: ", TYPE_WIDTH, "Food Type:", "Food type too long. Please try again.", type)
            
        } else if (input.find("edit") >= 0 || input.find("Edit") >= 0) {

        } else if (input.find("remove") >= 0 || input.find("Remove") >= 0) {

        } else if (input.find("sort") >= 0 || input.find("Sort") >= 0) {

        } else if (input.find("quit") >= 0 || input.find("Quit") >= 0) {
            break;
        } else {
            cout << endl << "Sorry I couldn't interpret that. Please type out your option again." << endl << endl;
        }
    }
    return 0;
}