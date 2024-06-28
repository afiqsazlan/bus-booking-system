#include <iostream>
#include <string>
using namespace std;

const int maxBookings = 100;

struct Booking {
    string destination;
    string time;
    int seats;
    bool insurance;
    double totalPrice;
};

const string destinations[] = {"Johor", "Melaka", "Pahang", "Kedah", "Perak"};
const int numDestinations = 5;
const string times[] = {"10am", "11am", "12pm", "1pm", "2pm", "3pm", "4pm", "5pm", "6pm", "7pm", "8pm", "9pm", "10pm"};
const int numTimes = 13;
const double prices[] = {35, 10, 10, 46, 27};
int seatsAvailable[numDestinations][numTimes] = {
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10},  // johor
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10},  // melaka
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10},  // pahang
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10},  // kedah
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10}   // perak
};

class BookingSystem {
private:
    string name;
    string icNumber;
    string destination;
    string time;
    double price;
    int seatsAvailable;
    string insuranceOption;
    int seats;
    double totalPrice;
    Booking bookings[maxBookings];
    int bookingCount;

    int getDestinationIndex() {
        for (int i = 0; i < numDestinations; ++i) {
            if (destination == destinations[i]) {
                return i;
            }
        }
        return -1; // Invalid destination
    }

    int getTimeIndex() {
        for (int i = 0; i < numTimes; ++i) {
            if (time == times[i]) {
                return i;
            }
        }
        return -1; // Invalid time
    }

    void recordBooking() {
        if (bookingCount < maxBookings) {
            bookings[bookingCount++] = {destination, time, seats, (insuranceOption == "yes"), totalPrice};
        } else {
            cout << "Booking record is full!\n";
        }
    }

public:
    BookingSystem() : price(0.0), seatsAvailable(0), totalPrice(0.0), bookingCount(0) {}

    void displayDestinations() {
            cout << "\nInsert your name: ";
            getline(cin, name);

            bool validIC = false;
                while (!validIC) {
                    cout << "\nInsert your IC number: ";
                    cin >> icNumber;

                    if (icNumber.length() == 12) {
                        validIC = true;
                    } else {
                        cout << "Invalid IC number. It must contain exactly 12 characters. Please try again.\n";
                    }
                }
            cout << "Destinations available: Johor, Melaka, Pahang, Perak, Kedah\n";
    }

    void insertDestination() {
        bool validInput = false;
        while (!validInput) {

            cout << "\nChoose your destination: ";
            cin >> destination;
            int index = getDestinationIndex();
            if (index != -1) {
                price = prices[index];
                validInput = true;
            } else {
                cout << "Wrong input, please try again\n\n";
            }
        }
    }

    void displayPriceAndTimes() {
        cout << "Price: RM" << price << endl;
        cout << "\nAvailable times:\n";
        for (const string& t : times) {
            cout << t << ", ";
        }
        cout << "\n\n";
    }

    void insertTime() {
        bool validInput = false;
        while (!validInput) {
            cout << "Enter Time: ";
            cin >> time;
            int index = getTimeIndex();
            if (index != -1) {
                int destIndex = getDestinationIndex();
                seatsAvailable = ::seatsAvailable[destIndex][index];
                validInput = true;
            } else {
                cout << "Wrong input, please try again\n\n";
            }
        }
    }

    void displayRemainingSeats() {
        bool validInput = false;
        string book;
        while (!validInput) {
            cout << "\nSeats available: " << seatsAvailable << endl;
            cout << "Do you want to choose another destination or time? (yes or no): ";
            cin >> book;
            if (book == "yes") {
                insertDestination();
                displayPriceAndTimes();
                insertTime();
                continue;
            } else if (book == "no") {
                return;
            } else {
                cout << "Wrong input, please try again\n\n";
            }
        }
    }

    void insertSeatToBook() {
        if (seatsAvailable == 0) {
            cout << "\nNo seats available to book.\n";
            return;
        }
        bool validInput = false;
        do {
            cout << "\nEnter number of seats to book: ";
            cin >> seats;
            if (seats <= seatsAvailable) {
                seatsAvailable -= seats;
                cout << seats << " seats successfully booked.\n";
                cout << "Remaining seat available: " << seatsAvailable << endl;
                validInput = true;
            } else {
                cout << "Not enough available seats!\n";
            }
        } while (!validInput);
    }

    void displayInsuranceOptions() {
        cout << "\nDo you want to include insurance coverage? (RM0.50 per head): Yes or No \n";
    }

    void insertInsuranceOption() {
        cout << "Enter Insurance Option (yes/no): ";
        cin >> insuranceOption;
        if (insuranceOption == "yes") {
            totalPrice = (0.5 * seats) + (seats * price);
        } else if (insuranceOption == "no") {
            totalPrice = seats * price;
        } else {
            cout << "Invalid Option!\n";
            insuranceOption = "";
        }
    }

    void displayTotal() {
        if (destination.empty() || time.empty()) {
            cout << "Booking details are incomplete.\n";
            return;
        }
        recordBooking();
        cout << "\nSummary of Booking:\n";
        cout << "Name: " << name << endl;
        cout << "IC Number: " << icNumber << endl;
        cout << "Destination: " << destination << endl;
        cout << "Time: " << time << endl;
        cout << "Price: RM" << totalPrice << endl;
        cout << "Insurance: " << (insuranceOption == "yes" ? "Included" : "Not Included") << endl;
        cout << "\nEnjoy your trip !\n";
    }

};

int main() {
    BookingSystem system;
    cout << "Welcome to TBS e-Book Bus Ticketing\n";
    system.displayDestinations();
    system.insertDestination();
    system.displayPriceAndTimes();
    system.insertTime();
    system.displayRemainingSeats();
    system.insertSeatToBook();
    system.displayInsuranceOptions();
    system.insertInsuranceOption();
    system.displayTotal();

    return 0;
}
