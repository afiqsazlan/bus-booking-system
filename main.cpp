#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Define a record for a bus route
struct Route {
    int routeNumber;
    string origin;
    string destination;
    int availableSeats;
    float fare;
};

// Function declarations
vector<Route> loadRoutes();
Route *findRouteByNumber(vector<Route> &routes, int routeNumber);
void displayRoutes(const vector<Route> &routes);
void bookSeat(vector<Route> &routes, vector<Route *> &cart);
void viewCart(const vector<Route*> &cart);
void displaySectionTitle(const string &title);
void displayErrorMessage(const string &message);

enum MenuChoice {
    DISPLAY_ROUTES = 1,
    BOOK_SEAT = 2,
    VIEW_CART = 3,
    EXIT = 9
};

enum ConfirmationOption {
    CONFIRM = 1,
    CANCEL = 0
};

const map<MenuChoice, string> menuLabels = {
        {DISPLAY_ROUTES, "Display Routes"},
        {BOOK_SEAT,      "Book a Seat"},
        {VIEW_CART,      "View Cart"},
        {EXIT,           "Exit"},
};

const string currencySymbol = "MYR";

int main() {

    vector<Route> routes = loadRoutes();
    vector<Route *> cart;

    int choice;
    do {
        displaySectionTitle("Bus Booking System");

        for (const auto &item: menuLabels) {
            cout << item.first << ". " << item.second << endl;
        }
        cout << "Enter your choice:";
        cin >> choice;

        switch (choice) {
            case DISPLAY_ROUTES:
                displayRoutes(routes);
                break;
            case BOOK_SEAT:
                bookSeat(routes, cart);
                break;
            case VIEW_CART:
                viewCart(cart);
                break;
        }
    } while (choice != 9);

    return 0;
}

// Load routes
vector<Route> loadRoutes() {
    return {
            {
                    101,
                    "Shah Alam",
                    "Kuala Terengganu",
                    30,
                    55.50
            },
            {
                    102,
                    "Bandar Tasik Selatan",
                    "Kuantan",
                    30,
                    40.00
            },
            {
                    103,
                    "Bandar Tasik Selatan",
                    "Johor",
                    50,
                    30.00
            },
    };
}

void displayRoutes(const vector<Route> &routes) {
    displaySectionTitle("Available Routes");
    for (const auto &route: routes) {
        cout << "Route number: " << route.routeNumber << endl;
        cout << "Origin: " << route.origin << endl;
        cout << "Destination: " << route.destination << endl;
        cout << "Available seats: " << route.availableSeats << endl;
        cout << "Fare: " << route.fare << endl;
        cout << "-----------------" << endl;
    }
}

// Book a seat on a route
void bookSeat(vector<Route> &routes, vector<Route *> &cart) {
    int routeNumber;
    Route *route = nullptr;

    cout << "Enter route number to book a seat: ";
    cin >> routeNumber;

    route = findRouteByNumber(routes, routeNumber);

    if (route) {
        if (route->availableSeats > 0) {
            int confirmSeatBooking;
            cout << "There are " << route->availableSeats << " seats available." << endl;
            cout << "Enter " << CONFIRM << " to confirm or " << CANCEL << " to cancel: ";

            do {
                cin >> confirmSeatBooking;
                if (confirmSeatBooking != CONFIRM && confirmSeatBooking != CANCEL) {
                    cout << "Invalid option. Enter " << CONFIRM << " to confirm or " << CANCEL << " to cancel: ";
                }
            } while (confirmSeatBooking != CONFIRM && confirmSeatBooking != CANCEL);

            if (confirmSeatBooking == CONFIRM) {
                route->availableSeats--;
                cout << "Successfully booked a seat on route " << routeNumber << "." << endl;
                cart.push_back(route);
            }
        } else {
            cout << "There are no seats available for this route." << endl;
        }
    } else {
        displayErrorMessage("Route not found! Please try again.");
    }
}

void viewCart(const vector<Route*>&cart) {
    if(cart.empty()) {
        cout << "Your cart is empty." << endl;
    } else {
        displaySectionTitle("Cart: Your Booked Seats");

        for(const auto& route : cart) {
            cout << "Route Number: " << route->routeNumber << endl;
            cout << "Origin: " << route->origin << endl;
            cout << "Destination: " << route->destination << endl;
            cout << "Seats Available: " << route->availableSeats << endl;
            cout << "Fare: " << currencySymbol << " " << route->fare << endl;
            cout << "-------------------------" <<endl;
        }
    }
}

Route *findRouteByNumber(vector<Route> &routes, int routeNumber) {
    for (auto &route: routes) {
        if (route.routeNumber == routeNumber) {
            return &route;
        }
    }
    return nullptr;
}


void displaySectionTitle(const string &title) {
    cout << "================================" << endl;
    cout << title << endl;
    cout << "================================" << endl;
}


void displayErrorMessage(const string &message) {
    cout << "================================" << endl;
    cout << "!!! ERROR: " << message << endl;
    cout << "================================" << endl;
}