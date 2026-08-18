/*
Exercise 12-4: Write a program that lists all the planes that leave from two
airports specified by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>

#define AIRPORT_CODE_LEN 3
#define MAX_FLIGHTS      10

/**
 * @brief Represents time of day and date for flight scheduling.
 */
typedef struct tm FlightTime;

/**
 * @brief Operational status of a reservation record.
 */
typedef enum {
    FLIGHT_STATUS_SCHEDULED,
    FLIGHT_STATUS_BOARDING,
    FLIGHT_STATUS_IN_FLIGHT,
    FLIGHT_STATUS_ARRIVED,
    FLIGHT_STATUS_CANCELLED,
    FLIGHT_STATUS_DELAYED
} FlightStatus;

/**
 * @brief Primary Airline Reservation Data Structure.
 */
typedef struct {
    FlightTime departure_time;  /* Departure timestamp */
    FlightTime arrival_time;    /* Arrival timestamp   */
    
    uint16_t   flight_number;   /* Flight number */
    
    char origin[AIRPORT_CODE_LEN + 1];      /* 3-letter IATA code + '\0' */
    char destination[AIRPORT_CODE_LEN + 1]; /* 3-letter IATA code + '\0' */
    
    FlightStatus status;        /* Current flight status */
} FlightReservation;

/* ---------------------- Helper Functions ---------------------- */

/**
 * @brief Converts a string to uppercase in place.
 */
static void normalize_airport_code(char *str) {
    for (; *str != '\0'; str++) {
        *str = (char)toupper((unsigned char)*str);
    }
}

/**
 * @brief Displays a single flight reservation cleanly.
 */
void print_flight(const FlightReservation *flight) {
    if (flight == NULL) return;

    char dep_buf[32];
    char arr_buf[32];

    strftime(dep_buf, sizeof(dep_buf), "%Y-%m-%d %H:%M", &flight->departure_time);
    strftime(arr_buf, sizeof(arr_buf), "%Y-%m-%d %H:%M", &flight->arrival_time);

    printf("Flight #%-5u | %s -> %s | Dep: %s | Arr: %s\n",
           flight->flight_number,
           flight->origin,
           flight->destination,
           dep_buf,
           arr_buf);
}

/**
 * @brief Scans a schedule and prints all flights departing from origin1 OR origin2.
 *
 * @param schedule Array of flight reservations.
 * @param count Number of flights in the schedule array.
 * @param origin1 First airport IATA code to check.
 * @param origin2 Second airport IATA code to check.
 * @return Number of matching flights found.
 */
int list_flights_from_airports(const FlightReservation schedule[], 
                               size_t count, 
                               const char *origin1, 
                               const char *origin2) {
    if (schedule == NULL || origin1 == NULL || origin2 == NULL) {
        return 0;
    }

    /* Local normalized copies for comparison */
    char code1[AIRPORT_CODE_LEN + 1];
    char code2[AIRPORT_CODE_LEN + 1];

    strncpy(code1, origin1, AIRPORT_CODE_LEN);
    code1[AIRPORT_CODE_LEN] = '\0';
    normalize_airport_code(code1);

    strncpy(code2, origin2, AIRPORT_CODE_LEN);
    code2[AIRPORT_CODE_LEN] = '\0';
    normalize_airport_code(code2);

    printf("\n=== Flights Departing From [%s] or [%s] ===\n\n", code1, code2);

    int matches = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(schedule[i].origin, code1) == 0 || 
            strcmp(schedule[i].origin, code2) == 0) {
            print_flight(&schedule[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("No matching departing flights found.\n");
    }

    printf("\nTotal matching flights: %d\n", matches);
    printf("===================================================\n");

    return matches;
}

/* ---------------------- Main Execution ---------------------- */

int main(void) {
    /* Sample flight database */
    FlightReservation flight_db[MAX_FLIGHTS] = {
        { .flight_number = 101, .origin = "TLV", .destination = "JFK",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 8,  .tm_min = 30 } },
        { .flight_number = 204, .origin = "JFK", .destination = "LHR",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 12, .tm_min = 0  } },
        { .flight_number = 305, .origin = "LHR", .destination = "CDG",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 14, .tm_min = 15 } },
        { .flight_number = 402, .origin = "TLV", .destination = "CDG",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 17, .tm_min = 45 } },
        { .flight_number = 512, .origin = "LAX", .destination = "JFK",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 21, .tm_min = 10 } },
        { .flight_number = 618, .origin = "JFK", .destination = "TLV",
          .departure_time = { .tm_year = 126, .tm_mon = 8, .tm_mday = 15, .tm_hour = 23, .tm_min = 30 } }
    };
    size_t db_size = 6;

    char airport1[16];
    char airport2[16];

    printf("=== Airline Departure Query System ===\n\n");

    printf("Enter first airport code (e.g. TLV): ");
    if (scanf("%15s", airport1) != 1) {
        fprintf(stderr, "Error reading airport input.\n");
        return 1;
    }

    printf("Enter second airport code (e.g. JFK): ");
    if (scanf("%15s", airport2) != 1) {
        fprintf(stderr, "Error reading airport input.\n");
        return 1;
    }

    /* Execute search query */
    list_flights_from_airports(flight_db, db_size, airport1, airport2);

    return 0;
}
