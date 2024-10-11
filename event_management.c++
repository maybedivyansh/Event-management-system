#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Event {
private:
    string eventName;
    string eventDate;
    int eventCapacity;
    int attendees;
    vector<string> customerTickets;
    vector<string> crewMembers;

public:
    Event(string name, string date, int capacity) {
        eventName = name;
        eventDate = date;
        eventCapacity = capacity;
        attendees = 0;
    }

    string getEventName() {
        return eventName;
    }

    string getEventDate() {
        return eventDate;
    }

    int getEventCapacity() {
        return eventCapacity;
    }

    int getAttendees() {
        return attendees;
    }

    void addAttendee(string attendeeName, string role) {
        if (attendees < eventCapacity) {
            if (role == "Customer") {
                string ticketNumber = generateTicketNumber();
                customerTickets.push_back(ticketNumber);
                attendees++;
                cout << attendeeName << " (Customer) has been added to " << eventName << " with Ticket Number: " << ticketNumber << endl;
            } else if (role == "Crew") {
                crewMembers.push_back(attendeeName);
                cout << attendeeName << " (Crew) has been added to " << eventName << endl;
            }
        } else {
            cout << "Event is fully booked!" << endl;
        }
    }

    void removeAttendee(string attendeeName, string role) {
        if (role == "Customer") {
            if (!customerTickets.empty()) {
                customerTickets.pop_back(); // Removes the last ticket (for simplicity)
                attendees--;
                cout << attendeeName << " (Customer) has been removed from " << eventName << endl;
            } else {
                cout << "No customers to remove!" << endl;
            }
        } else if (role == "Crew") {
            auto it = find(crewMembers.begin(), crewMembers.end(), attendeeName);
            if (it != crewMembers.end()) {
                crewMembers.erase(it);
                cout << attendeeName << " (Crew) has been removed from " << eventName << endl;
            } else {
                cout << "No crew member found with this name!" << endl;
            }
        }
    }

    string generateTicketNumber() {
        // Generate a random ticket number based on time
        time_t now = time(0);
        string ticketNumber = "T" + to_string(now % 100000);
        return ticketNumber;
    }
};

class Venue {
private:
    string venueName;
    int venueCapacity;

public:
    Venue(string name, int capacity) {
        venueName = name;
        venueCapacity = capacity;
    }

    string getVenueName() {
        return venueName;
    }

    int getVenueCapacity() {
        return venueCapacity;
    }
};

class EventManager {
private:
    vector<Event> events;
    vector<Venue> venues;

public:
    void addEvent() {
        string eventName, eventDate;
        int eventCapacity;
        cout << "Enter event name: ";
        cin >> ws;  // To clear the newline character from the buffer
        getline(cin, eventName);
        cout << "Enter event date (YYYY-MM-DD): ";
        cin >> eventDate;
        cout << "Enter event capacity: ";
        cin >> eventCapacity;
        
        Event event(eventName, eventDate, eventCapacity);
        events.push_back(event);
        cout << "Event " << eventName << " has been added!" << endl;
    }

    void addVenue() {
        string venueName;
        int venueCapacity;
        cout << "Enter venue name: ";
        cin >> ws;
        getline(cin, venueName);
        cout << "Enter venue capacity: ";
        cin >> venueCapacity;

        Venue venue(venueName, venueCapacity);
        venues.push_back(venue);
        cout << "Venue " << venueName << " has been added!" << endl;
    }

    void displayEvents() {
        cout << "Events:" << endl;
        for (Event& event : events) {
            cout << "  - " << event.getEventName() << " on " << event.getEventDate() << " (Capacity: " << event.getEventCapacity() << ")" << endl;
        }
    }

    void displayVenues() {
        cout << "Venues:" << endl;
        for (Venue& venue : venues) {
            cout << "  - " << venue.getVenueName() << " with capacity " << venue.getVenueCapacity() << endl;
        }
    }

    void bookEvent(string eventName, string attendeeName, string role) {
        for (Event& event : events) {
            if (event.getEventName() == eventName) {
                event.addAttendee(attendeeName, role);
                return;
            }
        }
        cout << "Event not found!" << endl;
    }

    void cancelEvent(string eventName, string attendeeName, string role) {
        for (Event& event : events) {
            if (event.getEventName() == eventName) {
                event.removeAttendee(attendeeName, role);
                return;
            }
        }
        cout << "Event not found!" << endl;
    }
};

int main() {
    EventManager manager;

    int choice;
    do {
        cout << "\nEvent Management System" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Add Venue" << endl;
        cout << "3. Display Events" << endl;
        cout << "4. Display Venues" << endl;
        cout << "5. Book Event (Customer or Crew)" << endl;
        cout << "6. Cancel Booking (Customer or Crew)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addEvent();
                break;
            case 2:
                manager.addVenue();
                break;
            case 3:
                manager.displayEvents();
                break;
            case 4:
                manager.displayVenues();
                break;
            case 5: {
                string eventName, attendeeName, role;
                cout << "Enter event name: ";
                cin >> ws;
                getline(cin, eventName);
                cout << "Enter attendee name: ";
                getline(cin, attendeeName);
                cout << "Enter role (Customer/Crew): ";
                getline(cin, role);
                manager.bookEvent(eventName, attendeeName, role);
                break;
            }
            case 6: {
                string eventName, attendeeName, role;
                cout << "Enter event name: ";
                cin >> ws;
                getline(cin, eventName);
                cout << "Enter attendee name: ";
                getline(cin, attendeeName);
                cout << "Enter role (Customer/Crew): ";
                getline(cin, role);
                manager.cancelEvent(eventName, attendeeName, role);
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
