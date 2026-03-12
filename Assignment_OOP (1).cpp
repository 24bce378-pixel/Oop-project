#include <bits/stdc++.h>
using namespace std;

// ==================== Base Class: Person ====================
class Person {
protected:
    string name;
    int id;

public:
    Person(string n, int i) : name(n), id(i) {}
    virtual void displayDetails() = 0;
    string getName() { return name; }
    int getId() { return id; }
    virtual ~Person() {}
};

// ==================== Driver Class ====================
class Driver : public Person {
private:
    double rating;
    int totalRides;

public:
    Driver(string n, int i, double r = 5.0)
        : Person(n, i), rating(r), totalRides(0) {}

    void updateRating(double newRating) {
        rating = (rating * totalRides + newRating) / (totalRides + 1);
        totalRides++;
    }

    void completeRide() { totalRides++; }

    double getRating() { return rating; }
    int getTotalRides() { return totalRides; }

    void displayDetails() override {
        cout << "Driver Name: " << name
             << " | ID: " << id
             << " | Rating: " << fixed << setprecision(1) << rating
             << " | Rides: " << totalRides << endl;
    }
};

// ==================== Rider Class ====================
class Rider : public Person {
public:
    Rider(string n, int i) : Person(n, i) {}
    void displayDetails() override {
        cout << "Rider Name: " << name << " | ID: " << id << endl;
    }
};

// ==================== Ride Class ====================
class Ride {
private:
    Rider rider;
    Driver* driver;
    double distance;
    int numRiders;
    double fare;

public:
    Ride(Rider r, Driver* d, double dist, int num)
        : rider(r), driver(d), distance(dist), numRiders(num) {
        calculateFare();
    }

    // ---- Friend Function Declaration ----
    friend double operator+(const Ride &r1, double distanceFare);

    // ---- Fare Calculation ----
    void calculateFare() {
        double costPerKm = 15;     
        double distanceFare = distance * costPerKm;

        // Using overloaded + operator for base fare + distance fare
        fare = *this + distanceFare;

        // Group surcharge: 20% for 2–4 riders
        if (numRiders >= 2 && numRiders <= 4)
            fare *= 1.2;

        // Apply 5% tax
        fare *= 1.05;
    }

    void startRide() {
        cout << "\nRide started...\n";
        driver->completeRide();
    }

    void showSummary() {
        cout << "\n=== RIDE SUMMARY ===\n";
        rider.displayDetails();
        driver->displayDetails();
        cout << "Number of Riders: " << numRiders << endl;
        cout << "Distance Travelled: " << distance << " km\n";
        cout << "Base Fare: Rs.10\n";
        cout << "Distance Fare (Rs.15/km): Rs." << distance * 15 << endl;

        if (numRiders >= 2 && numRiders <= 4)
            cout << "Group Surcharge (20%): Applied\n";
        else
            cout << "Group Surcharge: None\n";

        cout << "Taxes (5%): Included\n";
        cout << "Total Fare: Rs." << fixed << setprecision(2) << fare << endl;
    }

    void updateDriverRating() {
        double userRating;
        cout << "\nPlease rate your driver (1 to 5): ";
        cin >> userRating;

        while (userRating < 1 || userRating > 5) {
            cout << "Invalid rating! Enter a value between 1 and 5: ";
            cin >> userRating;
        }

        driver->updateRating(userRating);
        cout << "Driver's new average rating: " << fixed << setprecision(1)
             << driver->getRating() << endl;
    }

    void saveToFile() {
        ofstream file("RideHistory.txt", ios::app);
        if (file.is_open()) {
            file << "Rider: " << rider.getName()
                 << " | Driver: " << driver->getName()
                 << " | Fare: Rs." << fare
                 << " | Riders: " << numRiders
                 << " | Distance: " << distance << " km"
                 << " | Driver Rating: " << driver->getRating() << "\n";
            file.close();
        }
    }
};

// ---- Friend Function Definition ----
double operator+(const Ride &r1, double distanceFare) {
    double baseFare = 10;
    return baseFare + distanceFare;
}

// ==================== Utility Function ====================
void viewRideHistory() {
    ifstream file("RideHistory.txt");
    string line;
    cout << "\n=== RIDE HISTORY ===\n";
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
    } else {
        cout << "No ride history found.\n";
    }
    file.close();
}

// ==================== Main Menu ====================
int main() {
    srand((unsigned)time(0));
    vector<Driver*> drivers = {
        new Driver("Amit", 101),
        new Driver("Sneha", 102),
        new Driver("Vikram", 103),
        new Driver("Priya", 104),
        new Driver("Rahul", 105)
    };

    int option;
    do {
        cout << "\n=== RIDE BOOKING SYSTEM MENU ===\n";
        cout << "1. Book a Ride\n";
        cout << "2. View Ride History\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore();

        switch(option) {
            case 1: {
                string riderName;
                cout << "\nEnter Rider Name: ";
                getline(cin, riderName);
                Rider rider(riderName, rand() % 1000 + 1);

                double distance;
                int numRiders;
                cout << "Enter distance of the ride (in km): ";
                cin >> distance;

                cout << "Enter number of riders (max 4): ";
                cin >> numRiders;
                while (numRiders < 1 || numRiders > 4) {
                    cout << "Invalid number of riders! Please enter 1 to 4: ";
                    cin >> numRiders;
                }

                cout << "\nSearching for nearby drivers...\n";

                Driver* selectedDriver = drivers[rand() % drivers.size()];
                cout << "\nDriver Found:\n";
                selectedDriver->displayDetails();

                char choice;
                cout << "\nDo you want to cancel the ride? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "\nRide cancelled. No charges applied.\n";
                    break;
                }

                Ride ride(rider, selectedDriver, distance, numRiders);
                ride.startRide();
                ride.showSummary();
                ride.updateDriverRating();
                ride.saveToFile();

                cout << "\nRide details saved to 'RideHistory.txt'.\n";
                cout << "Thank you for riding with us, " << riderName << "!\n";
                break;
            }
            case 2:
                viewRideHistory();
                break;
            case 3:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
        }

    } while(option != 3);

    for (auto d : drivers) delete d;
    return 0;
}
