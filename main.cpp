/* 
 * Title: Goat Manager 3001 
 * Description: Converted Lab 23 to a std::set.
 * Author: Talha Ahmed 
 * Lab: 24
 * Class: COMSC-210 
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set> //change to set 
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

//reorganize for readability <updated function prototypes>
void add_goat(set<Goat> &trip, string names[], string colors[], int name_count, int color_count);
void delete_goat(set<Goat> &trip);
void display_trip(set<Goat> &trip);
int main_menu();

int main() {
    srand(static_cast<unsigned int>(time(0)));
    set<Goat> trip; //list to store goat objects <changed from list to set>
    string names[SZ_NAMES];
    string colors[SZ_COLORS];
    int name_count = 0, color_count = 0;
    
    ifstream fin("names.txt");
    if (!fin) {
        cout << "Error" << endl;
        return 1;
    }
    while (name_count < SZ_NAMES && fin >> names[name_count]) {
        name_count++;
    }
    fin.close();

   ifstream fin1("colors.txt");
    if (!fin1) {
        cout << "Error" << endl;
        return 1;
    }
    while (color_count < SZ_NAMES && fin1 >> colors[color_count]) {
        color_count++;
    } 
    fin1.close();

    //checked to see if names and colors have been loaded
    if (name_count ==0 || color_count == 0) {
        cout << "Error" << endl;
        return 1;
    }
    //menu loop
    int choice;
    do {
        choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors, name_count, color_count);
                break;        
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                cout << "Exit program" << endl;
                break;
            default:
                cout << "Invalid choice. "<< endl;
        }  
    } while (choice !=4);

     return 0;
}

//menu function
int main_menu() {
    int choice;
    bool valid = false;
    
while(!valid) {
    cout << "\n*** Goat Manager 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(1000, '\n'); //ignore invalid input
        cout << "Invalid input. Enter # from 1-4.\n";
    } else {
        valid = true;
    }
}
   return choice;
}

void add_goat(set<Goat> &trip, string names[], string colors[], int name_count, int color_count) {
    int rand_name = rand() % name_count;
    int rand_color = rand() % color_count;
    int age = rand() % (MAX_AGE + 1);

    //create new goat object
    Goat new_goat(names[rand_name], age, colors[rand_color]);
   
    auto result = trip.insert(new_goat);
    if (result.second) {
        cout << "\nGoat added: " << names[rand_name] << ", Color: " << colors[rand_color] << ", Age: " << age;
    } else {
        cout << "\nDuplicate goat not added.\n";
    }
    cout << "\nTotal goats: " << trip.size() << "\n";
}

//function to delete goat from list
void delete_goat(set<Goat> &trip) {
    if(trip.empty()) {
        cout << "No goat to delete.\n";
        return;
    }
    //display the goats
    int count = 1;
    for (const auto &goat : trip) {
        cout << "[" << count << "] " << goat.get_name() 
            << "( " << goat.get_age() << ", " << goat.get_color() << ")\n";
        count++;
    }
    
    int index;
    cout << "Enter how many goats to delete";
    cin >> index;

    //validate input (copied code from above)
    if (cin.fail() || index < 1 || index >= count) {
        cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Invalid input.\n";
        return;
    }

    auto it = trip.begin();
    advance(it, index - 1);
    trip.erase(it);
    cout << "Goat deleted";
}

void display_trip(set<Goat> &trip) {
    if(trip.empty()) {
        cout << "No goats in the trip";
        return;
    }
    int count = 1;
    for(const auto &goat : trip) {
        cout << "[" << count << "] " << goat.get_name() 
             << " (" << goat.get_age() << ", " << goat.get_color() << ")\n";
        count++;
    }
    cout << "Total number of goats: " << count << "\n";
}