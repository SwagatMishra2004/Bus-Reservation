#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUS_CAPACITY 5 // Reduced back to 5 after removing buses 106, 107, 108
#define INITIAL_PASSENGER_CAPACITY 500

// Structure Definitions
struct Bus
{
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

struct Passenger
{
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
    char email[100]; // Added email field
};

// Function Prototypes
void displayMainMenu();
void bookTicket(struct Bus *buses, int numBuses, struct Passenger *passengers, int *numPassengers, int *passengerCapacity);
void cancelTicket(struct Bus *buses, int numBuses, struct Passenger *passengers, int *numPassengers);
void checkBusStatus(struct Bus *buses, int numBuses);
void viewAllBuses(struct Bus *buses, int numBuses);
void viewAvailableSeats(struct Bus *buses, int numBuses);
void sendEmail(const char *action, const char *passengerName, int busNumber, int seatNumber, const char *email);

// Function Implementations

void displayMainMenu()
{
    printf("\n=== Bus Reservation System ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. View All Buses\n");
    printf("5. View Available Seats\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void bookTicket(struct Bus *buses, int numBuses, struct Passenger *passengers, int *numPassengers, int *passengerCapacity)
{
    int busNumber, numTickets, i, busIndex = -1;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    // Find the bus
    for (i = 0; i < numBuses; i++)
    {
        if (buses[i].busNumber == busNumber)
        {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1)
    {
        printf("Bus not found.\n");
        return;
    }

    printf("Enter the number of tickets: ");
    scanf("%d", &numTickets);

    if (buses[busIndex].availableSeats < numTickets)
    {
        printf("Sorry, only %d seats are available.\n", buses[busIndex].availableSeats);
        return;
    }

    // Passenger details
    for (i = 0; i < numTickets; i++)
    {
        if (*numPassengers >= *passengerCapacity)
        {
            *passengerCapacity *= 2;
            passengers = realloc(passengers, *passengerCapacity * sizeof(struct Passenger));
            if (passengers == NULL)
            {
                printf("Memory allocation failed.\n");
                return;
            }
        }
        printf("Enter passenger name: ");
        scanf("%s", passengers[*numPassengers].name);
        printf("Enter passenger age: ");
        scanf("%d", &passengers[*numPassengers].age);
        printf("Enter passenger email: ");
        scanf("%s", passengers[*numPassengers].email); // Get email from user
        passengers[*numPassengers].busNumber = busNumber;
        passengers[*numPassengers].seatNumber = buses[busIndex].totalSeats - buses[busIndex].availableSeats + 1;
        buses[busIndex].availableSeats--;
        (*numPassengers)++;
        printf("Ticket booked successfully! Seat number: %d\n", passengers[*numPassengers - 1].seatNumber);

        // Send email notification
        sendEmail("Booking", passengers[*numPassengers - 1].name, busNumber, passengers[*numPassengers - 1].seatNumber, passengers[*numPassengers - 1].email);
    }
}

void cancelTicket(struct Bus *buses, int numBuses, struct Passenger *passengers, int *numPassengers)
{
    char name[50];
    int i, j, found = 0;
    printf("Enter passenger name to cancel ticket: ");
    scanf("%s", name);

    for (i = 0; i < *numPassengers; i++)
    {
        if (strcmp(passengers[i].name, name) == 0)
        {
            // Find the bus
            for (j = 0; j < numBuses; j++)
            {
                if (buses[j].busNumber == passengers[i].busNumber)
                {
                    buses[j].availableSeats++;
                    break;
                }
            }
            // Send email notification
            sendEmail("Cancellation", passengers[i].name, passengers[i].busNumber, passengers[i].seatNumber, passengers[i].email);

            // Shift remaining passengers
            for (j = i; j < *numPassengers - 1; j++)
            {
                passengers[j] = passengers[j + 1];
            }
            (*numPassengers)--;
            printf("Ticket cancelled successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Passenger not found.\n");
    }
}

void checkBusStatus(struct Bus *buses, int numBuses)
{
    int busNumber, i, busIndex = -1;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    for (i = 0; i < numBuses; i++)
    {
        if (buses[i].busNumber == busNumber)
        {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1)
    {
        printf("Bus not found.\n");
        return;
    }

    printf("Bus Number: %d\n", buses[busIndex].busNumber);
    printf("Source: %s\n", buses[busIndex].source);
    printf("Destination: %s\n", buses[busIndex].destination);
    printf("Total Seats: %d\n", buses[busIndex].totalSeats);
    printf("Available Seats: %d\n", buses[busIndex].availableSeats);
    printf("Fare: %.2f\n", buses[busIndex].fare);
}

void viewAllBuses(struct Bus *buses, int numBuses)
{
    int i;
    printf("\n=== All Buses ===\n");
    for (i = 0; i < numBuses; i++)
    {
        printf("Bus Number: %d, Source: %s, Destination: %s, Available Seats: %d\n",
               buses[i].busNumber, buses[i].source, buses[i].destination, buses[i].availableSeats);
    }
}

void viewAvailableSeats(struct Bus *buses, int numBuses)
{
    int i;
    printf("\n=== Available Seats ===\n");
    for (i = 0; i < numBuses; i++)
    {
        printf("Bus Number: %d, Available Seats: %d\n", buses[i].busNumber, buses[i].availableSeats);
    }
}

void sendEmail(const char *action, const char *passengerName, int busNumber, int seatNumber, const char *email)
{
    char command[256];
    snprintf(command, sizeof(command), "node sendEmail.js \"%s\" \"%s\" %d %d \"%s\"", action, passengerName, busNumber, seatNumber, email);
    system(command);
}

int main()
{
    struct Bus buses[INITIAL_BUS_CAPACITY] = {
        {101, "Bhubaneswar", "Hydrabad", 40, 40, 1200.0},
        {102, "Hydrabad", "Bangalore", 35, 35, 1800.0},
        {103, "Bhubaneswar", "Kolkata", 50, 50, 750.0},
        {104, "Bhubaneswar", "Chhttisgarha", 45, 45, 950.0},
        {105, "Bhubaneswar", "VisahakPatnam", 30, 30, 750.0}};
    struct Passenger *passengers = malloc(INITIAL_PASSENGER_CAPACITY * sizeof(struct Passenger));

    int numBuses = INITIAL_BUS_CAPACITY;
    int numPassengers = 0;
    int passengerCapacity = INITIAL_PASSENGER_CAPACITY;
    int choice;

    do
    {
        displayMainMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Book a Ticket
            bookTicket(buses, numBuses, passengers, &numPassengers, &passengerCapacity);
            break;
        case 2: // Cancel a Ticket
            cancelTicket(buses, numBuses, passengers, &numPassengers);
            break;
        case 3: // Check Bus Status
            checkBusStatus(buses, numBuses);
            break;
        case 4: // View All Buses
            viewAllBuses(buses, numBuses);
            break;
        case 5: // View Available Seats
            viewAvailableSeats(buses, numBuses);
            break;
        case 6: // Exit
            printf("Thank You......:)\n");
            printf("Wishing you a journey filled with joy, laughter, and unforgettable adventures.!!\n");
            break;
        default:
            printf("Invalid choice. :(\n");
        }
    } while (choice != 6);

    // Free allocated memory
    free(passengers);

    return 0;
}