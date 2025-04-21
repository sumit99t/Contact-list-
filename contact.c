#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
} Contact;

void addContact() {
    FILE *fp = fopen("contacts.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    Contact c;
    getchar(); // clear buffer
    printf("Enter name: ");
    fgets(c.name, MAX_NAME_LEN, stdin);
    strtok(c.name, "\n");

    printf("Enter phone: ");
    fgets(c.phone, MAX_PHONE_LEN, stdin);
    strtok(c.phone, "\n");

    printf("Enter email: ");
    fgets(c.email, MAX_EMAIL_LEN, stdin);
    strtok(c.email, "\n");

    fprintf(fp, "%s|%s|%s\n", c.name, c.phone, c.email);
    fclose(fp);
    printf("Contact added successfully.\n");
}

void viewContacts() {
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    Contact c;
    printf("\n%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");
    while (fscanf(fp, "%99[^|]|%14[^|]|%99[^\n]\n", c.name, c.phone, c.email) == 3) {
        printf("%-20s %-15s %-30s\n", c.name, c.phone, c.email);
    }

    fclose(fp);
}

void searchContact() {
    char keyword[MAX_NAME_LEN];
    getchar(); // clear newline
    printf("Enter name to search: ");
    fgets(keyword, MAX_NAME_LEN, stdin);
    strtok(keyword, "\n");

    FILE *fp = fopen("contacts.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    Contact c;
    int found = 0;
    while (fscanf(fp, "%99[^|]|%14[^|]|%99[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strstr(c.name, keyword)) {
            printf("Found: %s | %s | %s\n", c.name, c.phone, c.email);
            found = 1;
        }
    }

    if (!found)
        printf("No matching contact found.\n");

    fclose(fp);
}

void deleteContact() {
    char phone[MAX_PHONE_LEN];
    getchar();
    printf("Enter phone number to delete: ");
    fgets(phone, MAX_PHONE_LEN, stdin);
    strtok(phone, "\n");

    FILE *fp = fopen("contacts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening files.\n");
        return;
    }

    Contact c;
    int found = 0;
    while (fscanf(fp, "%99[^|]|%14[^|]|%99[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strcmp(c.phone, phone) != 0) {
            fprintf(temp, "%s|%s|%s\n", c.name, c.phone, c.email);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        printf("Contact deleted successfully.\n");
    else
        printf("Contact not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n=== Contact List Manager ===\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact by Name\n");
        printf("4. Delete Contact by Phone\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}