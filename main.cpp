#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ====================== FLIGHT CLASS ======================
class Flight {
private:
    int flightNo;
    string destination;
    string departureTime;
    int seats;

public:
    Flight() {}

    Flight(int f, string d, string t, int s) {
        flightNo = f;
        destination = d;
        departureTime = t;
        seats = s;
    }

    void displayFlight() const {
        cout << "Flight No: " << flightNo
             << " | Destination: " << destination
             << " | Time: " << departureTime
             << " | Seats Left: " << seats << endl;
    }

    int getFlightNo() const { return flightNo; }
    string getDestination() const { return destination; }
    string getTime() const { return departureTime; }
    int getSeats() const { return seats; }

    bool bookSeat() {
        if(seats > 0) {
            seats--;
            return true;
        }
        return false;
    }
};

// ====================== TICKET CLASS ======================
class Ticket {
private:
    string passengerName;
    int passengerAge;
    Flight bookedFlight;
    bool booked;

public:
    Ticket() { booked = false; }

    void bookTicket(Flight flight) {
        cin.ignore();
        cout << "\nEnter Passenger Name: ";
        getline(cin, passengerName);

        cout << "Enter Passenger Age: ";
        cin >> passengerAge;

        bookedFlight = flight;
        booked = true;

        // Save only ticket info to file (append mode)
        ofstream file("booked_tickets.txt", ios::app);
        if(file) {
            file << "Passenger Name: " << passengerName << endl;
            file << "Passenger Age: " << passengerAge << endl;
            file << "Flight No: " << bookedFlight.getFlightNo() << endl;
            file << "Destination: " << bookedFlight.getDestination() << endl;
            file << "Departure Time: " << bookedFlight.getTime() << endl;
            file << "---------------------------\n";
        }
        file.close();

        cout << "\n? Ticket Booked Successfully & Saved to booked_tickets.txt!\n";
    }

    void showTicket() const {
        if(booked) {
            cout << "\n------ TICKET DETAILS ------\n";
            cout << "Passenger Name: " << passengerName << endl;
            cout << "Passenger Age: " << passengerAge << endl;
            cout << "Flight No: " << bookedFlight.getFlightNo() << endl;
            cout << "Destination: " << bookedFlight.getDestination() << endl;
            cout << "Departure Time: " << bookedFlight.getTime() << endl;
        } 
        else {
            cout << "\nNo Ticket Booked Yet!\n";
        }
    }

    bool isBooked() const { return booked; }
};

// ====================== AIRPORT SYSTEM CLASS ======================
class AirportSystem {
private:
    Flight flights[3];
    Ticket ticket;

public:
    AirportSystem() {
        // Hard-coded flight data: NEVER changes
        flights[0] = Flight(101, "Karachi", "10:00 AM", 50);
        flights[1] = Flight(202, "Lahore", "02:30 PM", 40);
        flights[2] = Flight(303, "Islamabad", "07:45 PM", 60);
    }

    void menu() {
        int choice;
        do {
            cout << "\n======= AIRPORT TICKET SYSTEM =======";
            cout << "\n1. View Available Flights";
            cout << "\n2. Book a Ticket";
            cout << "\n3. Display Booked Ticket";
            cout << "\n4. Exit";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    viewFlights();
                    break;

                case 2:
                    bookTicket();
                    break;

                case 3:
                    ticket.showTicket();
                    break;

                case 4:
                    cout << "\nThank you for using the system!\n";
                    break;

                default:
                    cout << "\nInvalid Choice. Try Again!\n";
            }

        } while(choice != 4);
    }

    void viewFlights() {
        cout << "\n------ AVAILABLE FLIGHTS ------\n";
        for(int i = 0; i < 3; i++)
            flights[i].displayFlight();

        char again;
        cout << "\nDo you want to continue? (y/n): ";
        cin >> again;

        if(again == 'n' || again == 'N') {
            cout << "\nGoodbye!\n";
            exit(0);
        }
    }

    void bookTicket() {
        int fNo;
        cout << "\nEnter Flight Number to Book: ";
        cin >> fNo;

        bool found = false;
        for(int i = 0; i < 3; i++) {
            if(flights[i].getFlightNo() == fNo) {
                found = true;

                if(flights[i].bookSeat()) {
                    ticket.bookTicket(flights[i]);

                    char show;
                    cout << "\nDo you want to display the ticket now? (y/n): ";
                    cin >> show;

                    if(show == 'y' || show == 'Y')
                        ticket.showTicket();
                }
                else {
                    cout << "\nNo Seats Available!\n";
                }
                break;
            }
        }

        if(!found)
            cout << "\nInvalid Flight Number!\n";
    }
};

// ====================== MAIN FUNCTION ======================
int main() {
    AirportSystem system;
    system.menu();
    return 0;
}
