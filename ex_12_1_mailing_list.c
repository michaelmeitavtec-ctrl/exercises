/*
Exercise 12-1: Design a structure to hold the data for a mailing list. Write a
function to print out the data.
*/
#include <stdio.h>
#include <string.h>

/**
 * @brief Structure to hold a single mailing list entry.
 *
 * Design rationale:
 *   - name, street, city, state: Essential address components
 *   - zip: Postal code (string to preserve leading zeros in some countries)
 *   - email: Electronic contact
 *   - phone: Telephone number (string to preserve formatting)
 *
 * String sizes are chosen to be practical (not too small to truncate real
 * data, not wastefully large for a linked-list or database of entries).
 */
struct mailing_list_entry {
    char name[50];      /* Full name */
    char street[50];    /* Street address */
    char city[30];      /* City */
    char state[3];      /* State abbreviation (2 chars + null terminator) */
    char zip[10];       /* ZIP/postal code */
    char email[50];     /* Email address */
    char phone[20];     /* Phone number (with formatting like (555) 555-1234) */
};

typedef struct mailing_list_entry MailingListEntry;

/* ---------------------- Print Functions ---------------------- */

/**
 * @brief Print a single mailing list entry in a formatted block.
 *
 * @param entry Pointer to the mailing list entry to print.
 */
void print_entry(const MailingListEntry *entry)
{
    printf("Name:   %s\n", entry->name);
    printf("Street: %s\n", entry->street);
    printf("City:   %s, %s %s\n", entry->city, entry->state, entry->zip);
    printf("Email:  %s\n", entry->email);
    printf("Phone:  %s\n", entry->phone);
}

/**
 * @brief Print a single mailing list entry in a compact one-line format.
 *
 * Useful for creating mailing labels or importing into other systems.
 *
 * @param entry Pointer to the mailing list entry to print.
 */
void print_entry_compact(const MailingListEntry *entry)
{
    printf("%-30s | %-40s | %s, %s %s\n",
           entry->name,
           entry->email,
           entry->city, entry->state, entry->zip);
}

/**
 * @brief Print a mailing address in US postal format.
 *
 * Useful for printing mailing labels or envelopes.
 *
 * @param entry Pointer to the mailing list entry to print.
 */
void print_mailing_address(const MailingListEntry *entry)
{
    printf("%s\n", entry->name);
    printf("%s\n", entry->street);
    printf("%s, %s %s\n", entry->city, entry->state, entry->zip);
}

/**
 * @brief Print a table header for mailing list entries.
 */
void print_list_header(void)
{
    printf("=========================================="
           "==========================================\n");
    printf("%-30s | %-40s | City, State ZIP\n", "Name", "Email");
    printf("=========================================="
           "==========================================\n");
}

/**
 * @brief Print a table footer.
 */
void print_list_footer(void)
{
    printf("=========================================="
           "==========================================\n");
}

/**
 * @brief Print an entire mailing list in table format.
 *
 * @param entries Array of mailing list entries.
 * @param count   Number of entries in the array.
 */
void print_mailing_list(const MailingListEntry entries[], int count)
{
    if (count <= 0) {
        printf("(empty mailing list)\n");
        return;
    }

    print_list_header();
    for (int i = 0; i < count; ++i) {
        print_entry_compact(&entries[i]);
    }
    print_list_footer();
    printf("Total entries: %d\n\n", count);
}

/* ---------------------- Test Program ---------------------- */

int main(void)
{
    printf("=== Mailing List Structure and Display ===\n\n");

    /* Create sample mailing list entries */
    MailingListEntry mailbox[] = {
        {
            .name = "Alice Johnson",
            .street = "123 Maple Street",
            .city = "Portland",
            .state = "OR",
            .zip = "97201",
            .email = "alice.johnson@email.com",
            .phone = "(503) 555-0123"
        },
        {
            .name = "Bob Smith",
            .street = "456 Oak Avenue",
            .city = "Seattle",
            .state = "WA",
            .zip = "98101",
            .email = "bob.smith@email.com",
            .phone = "(206) 555-0456"
        },
        {
            .name = "Carol Davis",
            .street = "789 Pine Road",
            .city = "San Francisco",
            .state = "CA",
            .zip = "94102",
            .email = "carol.davis@email.com",
            .phone = "(415) 555-0789"
        },
        {
            .name = "David Wilson",
            .street = "321 Elm Street",
            .city = "New York",
            .state = "NY",
            .zip = "10001",
            .email = "david.wilson@email.com",
            .phone = "(212) 555-1011"
        },
        {
            .name = "Eve Martinez",
            .street = "654 Cedar Lane",
            .city = "Austin",
            .state = "TX",
            .zip = "78701",
            .email = "eve.martinez@email.com",
            .phone = "(512) 555-1415"
        }
    };

    int list_size = sizeof(mailbox) / sizeof(mailbox[0]);

    /* Test 1: Print the entire mailing list in table format */
    printf("--- Complete Mailing List (Table Format) ---\n");
    print_mailing_list(mailbox, list_size);

    /* Test 2: Print individual entries in block format */
    printf("--- Individual Entry (Block Format) ---\n");
    printf("Entry 0:\n");
    print_entry(&mailbox[0]);
    printf("\n");

    printf("Entry 2:\n");
    print_entry(&mailbox[2]);
    printf("\n");

    /* Test 3: Print mailing addresses (for labels) */
    printf("--- Mailing Address Labels ---\n");
    for (int i = 0; i < list_size; ++i) {
        printf("Label %d:\n", i + 1);
        print_mailing_address(&mailbox[i]);
        printf("\n");
    }

    /* Test 4: Search and display a specific entry */
    printf("--- Search by Name ---\n");
    const char *search_name = "Carol Davis";
    int found = 0;

    for (int i = 0; i < list_size; ++i) {
        if (strcmp(mailbox[i].name, search_name) == 0) {
            printf("Found: %s\n\n", search_name);
            print_entry(&mailbox[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Entry not found: %s\n", search_name);
    }
    printf("\n");

    /* Test 5: Display by state */
    printf("--- Entries in California ---\n");
    int ca_count = 0;

    print_list_header();
    for (int i = 0; i < list_size; ++i) {
        if (strcmp(mailbox[i].state, "CA") == 0) {
            print_entry_compact(&mailbox[i]);
            ca_count++;
        }
    }
    print_list_footer();

    if (ca_count == 0) {
        printf("No entries found for California.\n");
    } else {
        printf("Total CA entries: %d\n", ca_count);
    }
    printf("\n");

    /* Test 6: Empty list test */
    printf("--- Empty Mailing List ---\n");
    MailingListEntry empty_list[1];
    print_mailing_list(empty_list, 0);

    return 0;
}

    return 0;
}
