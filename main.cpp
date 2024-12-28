#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Passenger
{
public:
    string name;
    int trainNumber;
    string destination;
    int ticketId;

    void display() const
    {
        cout << left << setw(10) << ticketId 
             << setw(15) << name
             << setw(10) << trainNumber
             << setw(15) << destination << endl;
    }
};

class ReservationSystem
{
private:
    vector<Passenger> passengers;
    int nextticketId = 1;

public:
    void bookTicket()
    {
        Passenger p;
        cout << "Enter Name: ";
        cin >> p.name;
        cout << "Enter Train Number: ";
        cin >> p.trainNumber;
        cout << "Enter Destination: ";
        cin >> p.destination;
        p.ticketId = nextticketId++;
        passengers.push_back(p);

        cout << "Ticket Booked Successfully! Ticket ID is: " << p.ticketId << endl;
        saveToFile();
    }

    void cancelTicket()
    {
        int id;
        cout << "Enter Ticket ID to Cancel: ";
        cin >> id;

        for (auto it = passengers.begin(); it != passengers.end(); ++it)
        {
            if (it->ticketId == id)
            {
                passengers.erase(it);
                cout << "Ticket Cancelled Successfully!" << endl;
                saveToFile();
                return;
            }
        }
        cout << "Seat Number Not Found!" << endl;
    }

    void displayPassengers()
    {
        if (passengers.empty())
        {
            cout << "No Reservations Found!" << endl;
            return;
        }

        cout << left << setw(10) << "Ticket ID" 
             << setw(15) << "Name"
             << setw(10) << "Train No"
             << setw(15) << "Destination"<< endl;

        for (const auto &p : passengers)
        {
            p.display(); 
        }
    }

    void saveToFile()
    {
        ofstream outFile("./reservations.txt");
        for (const auto &p : passengers)
        {
            outFile << p.ticketId << " "
                    << p.trainNumber << " "
                    << p.destination << " "
                    << p.name << endl;
        }
    }

    void loadFromFile()
    {
        ifstream inFile("reservations.txt");
        Passenger p;
        while (inFile >> p.ticketId >> p.trainNumber >> p.destination >> p.name)
        {
            passengers.push_back(p);
            nextticketId = p.ticketId + 1;
        }
    }
};

int main()
{
    ReservationSystem system;
    system.loadFromFile();
    int choice;

    do
    {
        cout << "\nRailway Reservation System\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Display Passengers\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.bookTicket();
            break;
        case 2:
            system.cancelTicket();
            break;
        case 3:
            system.displayPassengers();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
