#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>   

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};


void loading(const char *msg) {
    printf("\n%s", msg);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(500);   
    }
    printf("\n");
}


void progressBar() {
    printf("\nProcessing: ");
    for (int i = 0; i < 20; i++) {
        printf("#");
        fflush(stdout);
        Sleep(80);
    }
    printf(" Done!\n");
}


int loginSystem();
void adminMenu();
void userMenu();
void addStudent();
void viewStudents();


int main() {
    printf("============ SRMS ============\n");

    int role = loginSystem();

    if (role == 1) {
        loading("Opening Admin Dashboard");
        adminMenu();
    } else if (role == 2) {
        loading("Opening User Dashboard");
        userMenu();
    } else {
        printf("\nLogin Failed. Exiting...\n");
    }

    return 0;
}


int loginSystem() {
    char username[20], password[20];
    char fileUser[20], filePass[20], fileRole[10];

    printf("\n============ Login Screen ============\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    loading("Verifying credentials");

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) != EOF) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {

            fclose(fp);

            if (strcmp(fileRole, "ADMIN") == 0)
                return 1;   
            else
                return 2;   
        }
    }

    fclose(fp);
    return 0;
}


void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                progressBar();
                addStudent();
                break;

            case 2:
                progressBar();
                viewStudents();
                break;

            case 3:
                loading("Logging out");
                return;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
}


void userMenu() {
    int choice;

    do {
        printf("\n===== USER MENU =====\n");
        printf("1. View Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                progressBar();
                viewStudents();
                break;

            case 2:
                loading("Logging out");
                return;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 2);
}


void addStudent() {
    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp) {
        printf("Error opening students.txt!\n");
        return;
    }

    struct Student s;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("\n✔ Student added successfully!\n");
}

void viewStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("Error: students.txt not found!\n");
        return;
    }

    struct Student s;

    printf("\n========= STUDENT RECORDS =========\n");
    printf("%-10s %-15s %-10s %-10s\n", "Roll", "Name", "Marks", "Result");
    printf("-----------------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {

        
        char result[5];
        if (s.marks >= 40)
            strcpy(result, "PASS");
        else
            strcpy(result, "FAIL");

        printf("%-10d %-15s %-10.2f %-10s\n",
               s.roll, s.name, s.marks, result);
    }

    fclose(fp);
}
