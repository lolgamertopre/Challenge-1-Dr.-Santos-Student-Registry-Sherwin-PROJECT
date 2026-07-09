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

typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} Registry;

void showMenu(void);
void addStudent(Registry *reg);
void displayAllStudents(const Registry *reg);
void searchById(const Registry *reg);
void searchByGpaThreshold(const Registry *reg);
void searchByMajor(const Registry *reg);
void printStudentHeader(void);
void printStudentRow(Student s);
void clearInputBuffer(void);

int main(void) {
    Registry reg = { .count = 0 };
    int choice;

    printf("======================================\n");
    printf(" Welcome to Dr. Santos' Student Registry\n");
    printf("======================================\n");

    do {
        showMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent(&reg);
                break;
            case 2:
                displayAllStudents(&reg);
                break;
            case 3:
                searchById(&reg);
                break;
            case 4:
                searchByGpaThreshold(&reg);
                break;
            case 5:
                searchByMajor(&reg);
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
    while ((c = getchar()) != '\n' && c != EOF);
}

void addStudent(Registry *reg) {
    if (reg->count >= MAX_STUDENTS) {
        printf("Cannot add more students. Registry is full (max %d).\n", MAX_STUDENTS);
        return;
    }

    Student newStudent;

    printf("\n-- Add New Student --\n");

    while (1) {
        printf("Enter Student ID: ");
        if (scanf("%d", &newStudent.id) == 1 && newStudent.id > 0) {
            clearInputBuffer();
            break;
        }
        printf("Invalid ID. Please enter a positive integer.\n");
        clearInputBuffer();
    }

    for (int i = 0; i < reg->count; i++) {
        if (reg->students[i].id == newStudent.id) {
            printf("A student with ID %d already exists. Student not added.\n", newStudent.id);
            return;
        }
    }

    printf("Enter Full Name: ");
    fgets(newStudent.name, NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter Major: ");
    fgets(newStudent.major, MAJOR_LEN, stdin);
    newStudent.major[strcspn(newStudent.major, "\n")] = '\0';

    while (1) {
        printf("Enter GPA (0.0 - 4.0): ");
        if (scanf("%f", &newStudent.gpa) == 1 && newStudent.gpa >= 0.0f && newStudent.gpa <= 4.0f) {
            clearInputBuffer();
            break;
        }
        printf("Invalid entry. ");
        clearInputBuffer();
    }

    while (1) {
        printf("Enter Credits Taken: ");
        if (scanf("%d", &newStudent.credits) == 1 && newStudent.credits >= 0) {
            clearInputBuffer();
            break;
        }
        printf("Invalid entry. ");
        clearInputBuffer();
    }

    reg->students[reg->count] = newStudent;
    reg->count++;

    printf("Student '%s' added successfully! (%d/%d students in registry)\n",
           newStudent.name, reg->count, MAX_STUDENTS);
}

void printStudentHeader(void) {
    printf("%-6s %-25s %-20s %-6s %-8s\n", "ID", "Name", "Major", "GPA", "Credits");
    printf("--------------------------------------------------------------------\n");
}

void printStudentRow(Student s) {
    printf("%-6d %-25s %-20s %-6.2f %-8d\n", s.id, s.name, s.major, s.gpa, s.credits);
}

void displayAllStudents(const Registry *reg) {
    printf("\n-- All Students (%d total) --\n", reg->count);

    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printStudentHeader();
    for (int i = 0; i < reg->count; i++) {
        printStudentRow(reg->students[i]);
    }
}

void searchById(const Registry *reg) {
    int searchId;
    int found = 0;

    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);
    clearInputBuffer();

    for (int i = 0; i < reg->count; i++) {
        if (reg->students[i].id == searchId) {
            printf("\n-- Student Found --\n");
            printf("ID:      %d\n", reg->students[i].id);
            printf("Name:    %s\n", reg->students[i].name);
            printf("Major:   %s\n", reg->students[i].major);
            printf("GPA:     %.2f\n", reg->students[i].gpa);
            printf("Credits: %d\n", reg->students[i].credits);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with ID %d.\n", searchId);
    }
}

void searchByGpaThreshold(const Registry *reg) {
    float threshold;
    int matches = 0;

    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter minimum GPA threshold: ");
    scanf("%f", &threshold);
    clearInputBuffer();

    printf("\n-- Students with GPA >= %.2f --\n", threshold);
    printStudentHeader();

    for (int i = 0; i < reg->count; i++) {
        if (reg->students[i].gpa >= threshold) {
            printStudentRow(reg->students[i]);
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

void searchByMajor(const Registry *reg) {
    char searchMajor[MAJOR_LEN];
    int matches = 0;

    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter major to search for: ");
    fgets(searchMajor, MAJOR_LEN, stdin);
    searchMajor[strcspn(searchMajor, "\n")] = '\0';

    printf("\n-- Students majoring in '%s' --\n", searchMajor);
    printStudentHeader();

    for (int i = 0; i < reg->count; i++) {
        if (strstr(reg->students[i].major, searchMajor) != NULL) {
            printStudentRow(reg->students[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("(No students found with this major.)\n");
    } else {
        printf("--------------------------------------------------------------------\n");
        printf("%d student(s) found.\n", matches);
    }
}