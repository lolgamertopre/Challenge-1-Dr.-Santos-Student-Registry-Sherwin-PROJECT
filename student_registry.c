
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50
#define MAJOR_LEN 50


typedef struct {
    int id;
    char name[NAME_LEN];
    char major[MAJOR_LEN];
    float gpa;
    int credits;
} Student;


Student students[MAX_STUDENTS];
int studentCount = 0;

/* ------------------- Function Prototypes ------------------- */
void showMenu(void);
void addStudent(void);
void displayAllStudents(void);
void searchById(void);
void searchByGpaThreshold(void);
void searchByMajor(void);
void printStudentHeader(void);
void printStudentRow(Student s);
void clearInputBuffer(void);

int main(void) {
    int choice;

    printf("======================================\n");
    printf(" Welcome to Dr. Santos' Student Registry\n");
    printf("======================================\n");

    do {
        showMenu();
        printf("Enter your choice: ");

        /* Guard against non-numeric input */
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchById();
                break;
            case 4:
                searchByGpaThreshold();
                break;
            case 5:
                searchByMajor();
                break;
            case 0:
                printf("Goodbye, Dr. Santos!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void showMenu(void) {
    printf("\n--------------------------------------\n");
    printf("1. Add new student\n");
    printf("2. Display all students\n");
    printf("3. Search for student by ID\n");
    printf("4. Find students with GPA >= threshold\n");
    printf("5. Find students by major (with count)\n");
    printf("0. Exit\n");
    printf("--------------------------------------\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}
void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Registry is full (max %d).\n", MAX_STUDENTS);
        return;
    }

    Student newStudent;

    printf("\n-- Add New Student --\n");

    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);
    clearInputBuffer();

    /* Basic duplicate ID check */
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id) {
            printf("A student with ID %d already exists. Student not added.\n", newStudent.id);
            return;
        }
    }

    printf("Enter Full Name: ");
    fgets(newStudent.name, NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; /* strip newline */

    printf("Enter Major: ");
    fgets(newStudent.major, MAJOR_LEN, stdin);
    newStudent.major[strcspn(newStudent.major, "\n")] = '\0';

    printf("Enter GPA (0.0 - 4.0): ");
    scanf("%f", &newStudent.gpa);
    clearInputBuffer();

    printf("Enter Credits Taken: ");
    scanf("%d", &newStudent.credits);
    clearInputBuffer();

    students[studentCount] = newStudent;
    studentCount++;

    printf("Student '%s' added successfully! (%d/%d students in registry)\n",
           newStudent.name, studentCount, MAX_STUDENTS);
}


void printStudentHeader(void) {
    printf("%-6s %-25s %-20s %-6s %-8s\n", "ID", "Name", "Major", "GPA", "Credits");
    printf("--------------------------------------------------------------------\n");
}

/* Prints one student's data as a formatted row. */
void printStudentRow(Student s) {
    printf("%-6d %-25s %-20s %-6.2f %-8d\n", s.id, s.name, s.major, s.gpa, s.credits);
}

void displayAllStudents(void) {
    printf("\n-- All Students (%d total) --\n", studentCount);

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printStudentHeader();
    for (int i = 0; i < studentCount; i++) {
        printStudentRow(students[i]);
    }
}


void searchById(void) {
    int searchId;
    int found = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);
    clearInputBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            printf("\n-- Student Found --\n");
            printf("ID:      %d\n", students[i].id);
            printf("Name:    %s\n", students[i].name);
            printf("Major:   %s\n", students[i].major);
            printf("GPA:     %.2f\n", students[i].gpa);
            printf("Credits: %d\n", students[i].credits);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with ID %d.\n", searchId);
    }
}


void searchByGpaThreshold(void) {
    float threshold;
    int matches = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter minimum GPA threshold: ");
    scanf("%f", &threshold);
    clearInputBuffer();

    printf("\n-- Students with GPA >= %.2f --\n", threshold);
    printStudentHeader();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].gpa >= threshold) {
            printStudentRow(students[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("(No students met this GPA threshold.)\n");
    } else {
        printf("--------------------------------------------------------------------\n");
        printf("%d student(s) found.\n", matches);
    }
}


void searchByMajor(void) {
    char searchMajor[MAJOR_LEN];
    int matches = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter major to search for: ");
    fgets(searchMajor, MAJOR_LEN, stdin);
    searchMajor[strcspn(searchMajor, "\n")] = '\0';

    printf("\n-- Students in '%s' --\n", searchMajor);
    printStudentHeader();

    for (int i = 0; i < studentCount; i++) {
        /* Case-sensitive exact match on the major string */
        if (strcmp(students[i].major, searchMajor) == 0) {
            printStudentRow(students[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("(No students found in this major.)\n");
    } else {
        printf("--------------------------------------------------------------------\n");
        printf("Total students in '%s': %d\n", searchMajor, matches);
    }
}
