#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

struct Record {
    int id;
    char name[50];
    int age;

};

void addRecord(struct Record database[], int *count) {
    if (*count < MAX_RECORDS) {
        struct Record newRecord;

        printf("Enter ID: ");
        scanf("%d", &newRecord.id);


        for (int i = 0; i < *count; i++) {
            if (database[i].id == newRecord.id) {
                printf("Error: ID already exists. Please choose a unique ID.\n");
                return;
            }
        }

        printf("Enter Name: ");
        scanf(" %[^\n]s", newRecord.name);

        printf("Enter Age: ");
        scanf("%d", &newRecord.age);

        database[*count] = newRecord;
        (*count)++;
        printf("Record added successfully.\n");
    } else {
        printf("Error: Database is full. Cannot add more records.\n");
    }
}

void viewRecords(struct Record database[], int count) {
    if (count > 0) {
        printf("\n----- Records -----\n");
        for (int i = 0; i < count; i++) {
            printf("ID: %d, Name: %s, Age: %d\n", database[i].id, database[i].name, database[i].age);
        }
    } else {
        printf("No records found.\n");
    }
}


void searchRecord(struct Record database[], int count) {
    int searchID;
    printf("Enter ID to search: ");
    scanf("%d", &searchID);

    for (int i = 0; i < count; i++) {
        if (database[i].id == searchID) {
            printf("Record found:\n");
            printf("ID: %d, Name: %s, Age: %d\n", database[i].id, database[i].name, database[i].age);
            return;
        }
    }

    printf("Record not found.\n");
}


void updateRecord(struct Record database[], int count) {
    int updateID;
    printf("Enter ID to update: ");
    scanf("%d", &updateID);

    for (int i = 0; i < count; i++) {
        if (database[i].id == updateID) {
            printf("Enter new Name: ");
            scanf(" %[^\n]s", database[i].name);

            printf("Enter new Age: ");
            scanf("%d", &database[i].age);

            printf("Record updated successfully.\n");
            return;
        }
    }

    printf("Record not found.\n");
}


void deleteRecord(struct Record database[], int *count) {
    int deleteID;
    printf("Enter ID to delete: ");
    scanf("%d", &deleteID);

    for (int i = 0; i < *count; i++) {
        if (database[i].id == deleteID) {
            for (int j = i; j < *count - 1; j++) {
                database[j] = database[j + 1];
            }
            (*count)--;
            printf("Record deleted successfully.\n");
            return;
        }
    }

    printf("Record not found.\n");
}

void saveToFile(struct Record database[], int count) {
    FILE *file = fopen("records.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d %s %d\n", database[i].id, database[i].name, database[i].age);
        }
        fclose(file);
        printf("Records saved to file successfully.\n");
    } else {
        printf("Error: Could not open the file for writing.\n");
    }
}

void loadFromFile(struct Record database[], int *count) {
    FILE *file = fopen("records.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %[^\n]s %d", &database[*count].id, database[*count].name, &database[*count].age) == 3) {
            (*count)++;
            if (*count >= MAX_RECORDS) {
                printf("Warning: Maximum record limit reached. Some records may not be loaded.\n");
                break;
            }
        }
        fclose(file);
        printf("Records loaded from file successfully.\n");
    } else {
        printf("Note: No existing records file found. Continue with a new database.\n");
    }
}

int main() {
    struct Record database[MAX_RECORDS];
    int recordCount = 0;
    loadFromFile(database, &recordCount);

    int choice;
    do {
        printf("\n----- Database Management System -----\n");
        printf("1. Add Record\n");
        printf("2. View Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Save to File\n");
        printf("7. Load from File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(database, &recordCount);
                break;
            case 2:
                viewRecords(database, recordCount);
                break;
            case 3:
                searchRecord(database, recordCount);
                break;
            case 4:
                updateRecord(database, recordCount);
                break;
            case 5:
                deleteRecord(database, &recordCount);
                break;
            case 6:
                saveToFile(database, recordCount);
                break;
            case 7:
                loadFromFile(database, &recordCount);
                break;
            case 8:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}
