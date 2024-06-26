#include <iostream>
#include <string>
#include <iomanip>
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
const string departureTimes[] = {
    "10am", "11am", "12pm", "1pm", "2pm", "3pm", "4pm", "5pm", "6pm", "7pm", "8pm", "9pm", "10pm"
};
const int numTimes = 13;
const double prices[] = {35, 10, 10, 46, 27};
int seatsAvailable[numDestinations][numTimes] = {
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10}, // johor
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10}, // melaka
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10}, // pahang
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10}, // kedah
    {6, 8, 3, 30, 32, 5, 10, 6, 18, 2, 6, 24, 10} // perak
};

const double INSURANCE_COST_PER_SEAT = 5.00;

bool isReadyForCheckout = false;

template<typename T, size_t N>
int findIndex(const T (&array)[N], const T &value) {
    for (size_t i = 0; i < N; ++i) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Invalid index
}

class BookingSystem {
private:
    string name;
    string icNumber;
    string destination;
    string time;
    double price;
    int seatsAvailableForBooking;
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
            if (time == departureTimes[i]) {
                return i;
            }
        }
        return -1; // Invalid time
    }


    double calculateTotalInsurance() {
        double total = 0.00;
        if (insuranceOption == "y" || insuranceOption == "Y") {
            total = (INSURANCE_COST_PER_SEAT * seats);
        }
        return total;
    }

    void recordBooking() {
        if (bookingCount < maxBookings) {
            bookings[bookingCount++] = {destination, time, seats, (insuranceOption == "yes"), totalPrice};
        } else {
            cout << "Booking record is full!\n";
        }
    }


    void setIsReadyForCheckout() {
        isReadyForCheckout = true;
    }

public:
    BookingSystem() : price(0.0), seatsAvailableForBooking(0), totalPrice(0.0), bookingCount(0) {
    }

    void displayGreetings() {
        cout << "Welcome to TBS e-Book Bus Ticketing" << endl;
    }

    void requestPassengerDetails() {
        cout << "\nInsert your name: ";
        getline(cin, name);

        bool validIC = false;
        while (!validIC) {
            cout << "\nInsert your IC number: ";
            cin >> icNumber;

            if (icNumber.length() == 12) {
                validIC = true;
            } else {
                cout << "Invalid IC number length:" << icNumber.length() <<
                        ". It must contain exactly 12 characters. Please try again.\n";
            }
        }
    }

    void displayAvailableDestinations() {
        cout << "-----------------------" << endl;
        cout << "Available Destinations:" << endl;
        for (int i = 0; i < destinations->length(); i++) {
            cout << i + 1 << ". " << destinations[i] << endl;
        }
        cout << endl;
    }

    void requestDesiredDestination() {
        bool validInput = false;
        while (!validInput) {
            cout << "Choose your destination (enter a number): ";
            int destinationNumber;
            cin >> destinationNumber;
            if (destinationNumber >= 1 && destinationNumber <= numDestinations) {
                destination = destinations[destinationNumber - 1];
                validInput = true;
            } else {
                cout << "Wrong input, please try again\n\n";
            }
        }
    }

    void displayTicketPrice() {
        int index = findIndex(destinations, destination);

        price = prices[index];

        cout << "Ticket Price: RM" << price << endl;
    }

    void displayAvailableDepartureTimes() {
        int row = 1;

        cout << "-----------------------" << endl;
        cout << "Available Departure Times:" << endl;

        for (const string &departureTime: departureTimes) {
            cout << row << ". " << departureTime << endl;
            row++;
        }
        cout << endl;
    }

    void requestDesiredDepartureTime() {
        bool validInput = false;

        while (!validInput) {
            cout << "Choose a departure time (enter a number): ";
            int timeNumber;
            cin >> timeNumber;

            if (timeNumber >= 1 && timeNumber <= numTimes) {
                time = departureTimes[timeNumber - 1];
                validInput = true;
            } else {
                cout << "Wrong input, please try again\n\n";
            }
        }
    }


    void displayAvailableSeatsCount() {
        int destIndex = findIndex(destinations, destination);
        int timeIndex = findIndex(departureTimes, time);
        seatsAvailableForBooking = seatsAvailable[destIndex][timeIndex];

        if (seatsAvailableForBooking > 0) {
            cout << "Available seats: " << seatsAvailableForBooking << " seats" << endl;
        } else {
            cout << "\nNo seats available to book.\n";
        }
    }

    void requestNumberOfSeatsToBook() {
        bool validInput = false;
        while (!validInput) {
            cout << "\nEnter number of seats to book: ";
            cin >> seats;
            if (seats <= seatsAvailableForBooking) {
                seatsAvailable[findIndex(destinations, destination)][findIndex(departureTimes, time)] -= seats;
                cout << seats << " seats successfully booked.\n";
                cout << "Remaining seats available: " << seatsAvailableForBooking << endl;
                validInput = true;
            } else {
                cout << "Not enough available seats!\n";
            }
        }
    }

    void requestInsuranceAddon() {
        cout << "Do you want to include insurance coverage? (RM " << INSURANCE_COST_PER_SEAT << " per seat)" << endl;
        cout << "Enter Y (Yes) or N (No)" << endl;
        cin >> insuranceOption;
        while (insuranceOption != "y" && insuranceOption != "Y" && insuranceOption != "n" && insuranceOption != "N") {
            cout << "Invalid Option! Please enter Y (Yes) or N (No)." << endl;
            cin >> insuranceOption;
        }
    }

    void calculateTotalPrice() {
        totalPrice = (seats * price) + calculateTotalInsurance();
    }

    void requestBookingConfirmation() {

        displayBookingSummary("Review Booking");

        char confirmBooking;
        cout << endl << "Do you wish to confirm your booking?" << endl;
        cout << "Enter Y (Yes) or N (No): ";
        cin >> confirmBooking;

        if (confirmBooking == 'Y' || confirmBooking == 'y') {
            setIsReadyForCheckout();
            recordBooking();
            displayBookingConfirmation();
        } else {
            cout << "Returning to main menu." << endl;
        }
    }

    void displayBookingSummary(string title = "") {
        cout << "---------------------" << endl;
        cout << endl << title << endl;
        cout << "---------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "IC Number: " << icNumber << endl;
        cout << "Destination: " << destination << endl;
        cout << "Time: " << time << endl;
        cout << "Total Price: RM" << fixed << setprecision(2) << totalPrice << endl;
        cout << "Insurance: " << (insuranceOption == "y" || insuranceOption == "Y" ? "Included" : "Not Included") <<
                endl;
    }

    void displayBookingConfirmation() {
        displayBookingSummary("Booking Summary");
        cout << endl << "Booking confirmed. Enjoy your trip!" << endl;
    }
};

int main() {
    BookingSystem system;

    system.displayGreetings();
    system.requestPassengerDetails();

    while (!isReadyForCheckout) {
        system.displayAvailableDestinations();
        system.requestDesiredDestination();
        system.displayTicketPrice();
        system.displayAvailableDepartureTimes();
        system.requestDesiredDepartureTime();
        system.displayAvailableSeatsCount();
        system.requestNumberOfSeatsToBook();
        system.requestInsuranceAddon();
        system.calculateTotalPrice();
        system.requestBookingConfirmation();
    }

    system.displayBookingConfirmation();

    return 0;
}
