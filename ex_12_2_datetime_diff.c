/*
Exercise 12-2: Design a structure to store time and date. Write a function to find
the difference between two times in minutes.
*/

#include <stdio.h>
#include <math.h>

/**
 * @brief Structure to hold date and time information.
 *
 * Design:
 *   - year: Full year (e.g., 2024)
 *   - month: 1-12
 *   - day: 1-31 (depending on month)
 *   - hour: 0-23 (24-hour format)
 *   - minute: 0-59
 *   - second: 0-59
 */
struct date_time {
    int year;
    int month;      /* 1-12 */
    int day;        /* 1-31 */
    int hour;       /* 0-23 */
    int minute;     /* 0-59 */
    int second;     /* 0-59 */
};

typedef struct date_time DateTime;

/* ---------------------- Validation Functions ---------------------- */

/**
 * @brief Check if a year is a leap year.
 *
 * A leap year is divisible by 4, except for years divisible by 100
 * (which are not leap years), except for years divisible by 400
 * (which are leap years).
 *
 * @param year The year to check.
 * @return 1 if leap year, 0 otherwise.
 */
int is_leap_year(int year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

/**
 * @brief Get the number of days in a given month.
 *
 * @param month Month (1-12).
 * @param year  Year (needed to check for leap years in February).
 * @return Number of days in the month.
 */
int days_in_month(int month, int year)
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return (month >= 1 && month <= 12) ? days[month] : 0;
}

/**
 * @brief Validate a DateTime structure.
 *
 * @param dt Pointer to the DateTime to validate.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_datetime(const DateTime *dt)
{
    if (dt == NULL) return 0;

    /* Year sanity check (allow reasonable range) */
    if (dt->year < 1900 || dt->year > 2100) return 0;

    /* Month check */
    if (dt->month < 1 || dt->month > 12) return 0;

    /* Day check */
    int max_days = days_in_month(dt->month, dt->year);
    if (dt->day < 1 || dt->day > max_days) return 0;

    /* Time checks */
    if (dt->hour < 0 || dt->hour > 23) return 0;
    if (dt->minute < 0 || dt->minute > 59) return 0;
    if (dt->second < 0 || dt->second > 59) return 0;

    return 1;
}

/* ---------------------- Calculation Functions ---------------------- */

/**
 * @brief Calculate the number of days from a reference date (Jan 1, 1900).
 *
 * This converts a date to an absolute day number, allowing easy date arithmetic.
 *
 * @param dt Pointer to the DateTime.
 * @return Number of days since Jan 1, 1900.
 */
long days_since_epoch(const DateTime *dt)
{
    long days = 0;
    int year = 1900;

    /* Add days for complete years */
    while (year < dt->year) {
        days += is_leap_year(year) ? 366 : 365;
        year++;
    }

    /* Add days for complete months in the current year */
    for (int month = 1; month < dt->month; ++month) {
        days += days_in_month(month, dt->year);
    }

    /* Add remaining days */
    days += dt->day - 1;  /* -1 because we count from day 0 */

    return days;
}

/**
 * @brief Convert a DateTime to total minutes since epoch.
 *
 * Epoch is defined as Jan 1, 1900, 00:00:00.
 *
 * @param dt Pointer to the DateTime.
 * @return Total minutes since epoch.
 */
long datetime_to_minutes(const DateTime *dt)
{
    if (!is_valid_datetime(dt)) {
        return -1;  /* Invalid datetime */
    }

    long total_minutes = 0;

    /* Add minutes for days since epoch */
    total_minutes += days_since_epoch(dt) * 24 * 60;

    /* Add minutes for hours and minutes of the day */
    total_minutes += dt->hour * 60;
    total_minutes += dt->minute;

    return total_minutes;
}

/**
 * @brief Calculate the difference between two DateTimes in minutes.
 *
 * The difference is always positive (absolute value).
 *
 * @param dt1 Pointer to the first DateTime.
 * @param dt2 Pointer to the second DateTime.
 * @return The absolute difference in minutes, or -1 if either DateTime is invalid.
 */
long datetime_difference_minutes(const DateTime *dt1, const DateTime *dt2)
{
    if (!is_valid_datetime(dt1) || !is_valid_datetime(dt2)) {
        return -1;
    }

    long minutes1 = datetime_to_minutes(dt1);
    long minutes2 = datetime_to_minutes(dt2);

    if (minutes1 < 0 || minutes2 < 0) {
        return -1;
    }

    return labs(minutes1 - minutes2);
}

/**
 * @brief Convert minutes to a human-readable format (days, hours, minutes).
 *
 * @param total_minutes Total minutes to convert.
 * @param days Output pointer for days.
 * @param hours Output pointer for hours (0-23).
 * @param minutes Output pointer for minutes (0-59).
 */
void minutes_to_readable(long total_minutes, long *days, int *hours, int *minutes)
{
    *days = total_minutes / (24 * 60);
    total_minutes %= (24 * 60);

    *hours = total_minutes / 60;
    *minutes = total_minutes % 60;
}

/* ---------------------- Print Functions ---------------------- */

/**
 * @brief Print a DateTime in a formatted string.
 *
 * @param dt Pointer to the DateTime.
 */
void print_datetime(const DateTime *dt)
{
    if (!is_valid_datetime(dt)) {
        printf("(invalid datetime)\n");
        return;
    }

    printf("%04d-%02d-%02d %02d:%02d:%02d",
           dt->year, dt->month, dt->day,
           dt->hour, dt->minute, dt->second);
}

/**
 * @brief Print a DateTime with label and validation status.
 *
 * @param label A descriptive label.
 * @param dt Pointer to the DateTime.
 */
void print_labeled_datetime(const char *label, const DateTime *dt)
{
    printf("%-20s: ", label);
    print_datetime(dt);

    if (!is_valid_datetime(dt)) {
        printf(" (INVALID)");
    }

    printf("\n");
}

/**
 * @brief Print the difference between two DateTimes in human-readable format.
 *
 * @param dt1 Pointer to the first DateTime.
 * @param dt2 Pointer to the second DateTime.
 */
void print_datetime_difference(const DateTime *dt1, const DateTime *dt2)
{
    long diff_minutes = datetime_difference_minutes(dt1, dt2);

    if (diff_minutes < 0) {
        printf("(Cannot calculate difference: invalid datetime)\n");
        return;
    }

    long days;
    int hours, minutes;
    minutes_to_readable(diff_minutes, &days, &hours, &minutes);

    printf("Difference: %ld days, %d hours, %d minutes (%ld total minutes)\n",
           days, hours, minutes, diff_minutes);
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_difference(const char *label, const DateTime *dt1, const DateTime *dt2,
                     long expected_minutes)
{
    long result = datetime_difference_minutes(dt1, dt2);
    tests_run++;

    int pass = (result == expected_minutes);

    printf("%-50s\n", label);
    printf("  DateTime 1: ");
    print_datetime(dt1);
    printf("\n");

    printf("  DateTime 2: ");
    print_datetime(dt2);
    printf("\n");

    printf("  Difference: %ld minutes (Expected: %ld minutes) -> %s\n",
           result, expected_minutes, pass ? "PASS" : "FAIL");

    if (pass) {
        tests_passed++;
    }

    printf("\n");
}

int main(void)
{
    printf("=== Date/Time Structure and Difference Calculator ===\n\n");

    /* Test 1: Same time (difference should be 0) */
    printf("--- Test 1: Same DateTime ---\n");
    DateTime dt1 = {2024, 1, 15, 14, 30, 45};
    DateTime dt2 = {2024, 1, 15, 14, 30, 45};

    print_labeled_datetime("DateTime 1", &dt1);
    print_labeled_datetime("DateTime 2", &dt2);
    print_datetime_difference(&dt1, &dt2);

    test_difference("Same datetime", &dt1, &dt2, 0);

    /* Test 2: Difference within the same day */
    printf("--- Test 2: Same Day, Different Times ---\n");
    DateTime dt3 = {2024, 1, 15, 8, 0, 0};
    DateTime dt4 = {2024, 1, 15, 10, 30, 0};
    /* Difference: 2 hours 30 minutes = 150 minutes */

    print_labeled_datetime("DateTime 1", &dt3);
    print_labeled_datetime("DateTime 2", &dt4);
    print_datetime_difference(&dt3, &dt4);

    test_difference("2.5 hours difference", &dt3, &dt4, 150);

    /* Test 3: Difference across days */
    printf("--- Test 3: Different Days ---\n");
    DateTime dt5 = {2024, 1, 15, 22, 0, 0};
    DateTime dt6 = {2024, 1, 16, 10, 0, 0};
    /* Difference: 12 hours = 720 minutes */

    print_labeled_datetime("DateTime 1", &dt5);
    print_labeled_datetime("DateTime 2", &dt6);
    print_datetime_difference(&dt5, &dt6);

    test_difference("12 hours across days", &dt5, &dt6, 720);

    /* Test 4: Difference across months */
    printf("--- Test 4: Different Months ---\n");
    DateTime dt7 = {2024, 1, 31, 0, 0, 0};
    DateTime dt8 = {2024, 2, 1, 0, 0, 0};
    /* Difference: 1 day = 1440 minutes */

    print_labeled_datetime("DateTime 1", &dt7);
    print_labeled_datetime("DateTime 2", &dt8);
    print_datetime_difference(&dt7, &dt8);

    test_difference("1 day across months", &dt7, &dt8, 1440);

    /* Test 5: Difference across years */
    printf("--- Test 5: Different Years ---\n");
    DateTime dt9 = {2023, 12, 31, 23, 0, 0};
    DateTime dt10 = {2024, 1, 1, 0, 0, 0};
    /* Difference: 1 hour = 60 minutes */

    print_labeled_datetime("DateTime 1", &dt9);
    print_labeled_datetime("DateTime 2", &dt10);
    print_datetime_difference(&dt9, &dt10);

    test_difference("1 hour across years", &dt9, &dt10, 60);

    /* Test 6: Leap year handling */
    printf("--- Test 6: Leap Year (Feb 28 to Mar 1) ---\n");
    DateTime dt11 = {2024, 2, 29, 0, 0, 0};  /* 2024 is a leap year */
    DateTime dt12 = {2024, 3, 1, 0, 0, 0};
    /* Difference: 1 day = 1440 minutes */

    print_labeled_datetime("DateTime 1", &dt11);
    print_labeled_datetime("DateTime 2", &dt12);
    print_datetime_difference(&dt11, &dt12);

    test_difference("Leap year day difference", &dt11, &dt12, 1440);

    /* Test 7: Invalid DateTimes */
    printf("--- Test 7: Invalid DateTime Handling ---\n");
    DateTime invalid1 = {2024, 2, 30, 10, 0, 0};  /* Feb 30 doesn't exist */
    DateTime valid = {2024, 3, 1, 10, 0, 0};

    print_labeled_datetime("Invalid DateTime", &invalid1);
    print_labeled_datetime("Valid DateTime", &valid);

    long result = datetime_difference_minutes(&invalid1, &valid);
    printf("Difference result: %ld (expected -1 for invalid) -> %s\n",
           result, result == -1 ? "PASS" : "FAIL");

    tests_run++;
    if (result == -1) tests_passed++;

    printf("\n");

    /* Test 8: Reverse order (should give same absolute difference) */
    printf("--- Test 8: Reverse Order (Commutative) ---\n");
    DateTime dt13 = {2024, 1, 15, 8, 0, 0};
    DateTime dt14 = {2024, 1, 15, 12, 30, 0};

    long diff_forward = datetime_difference_minutes(&dt13, &dt14);
    long diff_backward = datetime_difference_minutes(&dt14, &dt13);

    printf("Forward:  ");
    print_datetime(&dt13);
    printf(" to ");
    print_datetime(&dt14);
    printf(" = %ld minutes\n", diff_forward);

    printf("Backward: ");
    print_datetime(&dt14);
    printf(" to ");
    print_datetime(&dt13);
    printf(" = %ld minutes\n", diff_backward);

    int pass = (diff_forward == diff_backward && diff_forward == 270);
    printf("Result: %s (both should be 270 minutes)\n\n", pass ? "PASS" : "FAIL");

    tests_run++;
    if (pass) tests_passed++;

    /* Test 9: Exact minute difference */
    printf("--- Test 9: Exact Minute Calculation ---\n");
    DateTime dt15 = {2024, 1, 1, 0, 0, 0};
    DateTime dt16 = {2024, 1, 2, 0, 0, 0};
    /* Exactly 1 day = 1440 minutes */

    print_labeled_datetime("DateTime 1", &dt15);
    print_labeled_datetime("DateTime 2", &dt16);
    print_datetime_difference(&dt15, &dt16);

    test_difference("Exactly 1 day", &dt15, &dt16, 1440);

    printf("\n=== Test Summary ===\n");
    printf("Passed: %d / %d tests\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
