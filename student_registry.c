#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50
#define MAJOR_LEN 50
#define MIN_GPA 0.0f
#define MAX_GPA 4.0f

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

/* ------------------- Function Prototypes ------------------- */
void showMenu(void);
void addStudent(Registry *reg);
void displayAllStudents(const Registry *reg);
void searchById(const Registry *reg);
void searchByGpaThreshold(const Registry *reg);
void searchByMajor(const Registry *reg);
void showStatistics(const Registry *reg);
void printStudentHeader(void);
void printStudentRow(Student s);
void clearInputBuffer(void);
int readInt(const char *prompt, int min, int allowMin, int max, int allowMax);
float readFloat(const char *prompt, float min, float max);
void readLine(const char *prompt, char *buffer, int len);
int strcaseequal(const char *a, const char *b);

int main(void) {
    Registry reg = { .count = 0 };
    int choice;

    printf("======================================\n");
    printf(" Welcome to Dr. Santos' Student Registry\n");
    printf("======================================\n");

    do {
        showMenu();
        printf("Enter your choice: ");
        int result = scanf("%d", &choice);
        if (result == EOF) {
            printf("\nInput stream closed unexpectedly. Exiting.\n");
            break;
        }
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addStudent(&reg);           break;
            case 2: displayAllStudents(&reg);   break;
            case 3: searchById(&reg);           break;
            case 4: searchByGpaThreshold(&reg); break;
            case 5: searchByMajor(&reg);        break;
            case 6: showStatistics(&reg);       break;
            case 0: printf("Goodbye, Dr. Santos!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
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
    printf("6. Show class statistics\n");
    printf("0. Exit\n");
    printf("--------------------------------------\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Case-insensitive string equality helper (avoids relying on non-standard strcasecmp). */
int strcaseequal(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

/*
 * Reads an integer with a validated range, re-prompting on bad input.
 * If allowMin/allowMax is 0, that bound is not enforced (pass anything for min/max then).
 */
int readInt(const char *prompt, int min, int allowMin, int max, int allowMax) {
    int value;
    for (;;) {
        printf("%s", prompt);
        int result = scanf("%d", &value);
        if (result == EOF) {
            printf("\nInput stream closed unexpectedly. Exiting.\n");
            exit(1);
        }
        if (result != 1) {
            printf("Invalid input. Please enter a whole number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        if (allowMin && value < min) {
            printf("Value must be at least %d.\n", min);
            continue;
        }
        if (allowMax && value > max) {
            printf("Value must be at most %d.\n", max);
            continue;
        }
        return value;
    }
}

/* Reads a float within [min, max], re-prompting on bad input. */
float readFloat(const char *prompt, float min, float max) {
    float value;
    for (;;) {
        printf("%s", prompt);
        int result = scanf("%f", &value);
        if (result == EOF) {
            printf("\nInput stream closed unexpectedly. Exiting.\n");
            exit(1);
        }
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        if (value < min || value > max) {
            printf("Value must be between %.2f and %.2f.\n", min, max);
            continue;
        }
        return value;
    }
}

/* Reads a non-empty line of text into buffer, stripping the trailing newline. */
void readLine(const char *prompt, char *buffer, int len) {
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, len, stdin)) {
            buffer[0] = '\0';
            return;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0') {
            printf("This field cannot be empty. Please try again.\n");
            continue;
        }
        return;
    }
}

void addStudent(Registry *reg) {
    if (reg->count >= MAX_STUDENTS) {
        printf("Cannot add more students. Registry is full (max %d).\n", MAX_STUDENTS);
        return;
    }

    Student newStudent;
    printf("\n-- Add New Student --\n");

    newStudent.id = readInt("Enter Student ID: ", 1, 1, 0, 0);

    for (int i = 0; i < reg->count; i++) {
        if (reg->students[i].id == newStudent.id) {
            printf("A student with ID %d already exists. Student not added.\n", newStudent.id);
            return;
        }
    }

    readLine("Enter Full Name: ", newStudent.name, NAME_LEN);
    readLine("Enter Major: ", newStudent.major, MAJOR_LEN);
    newStudent.gpa = readFloat("Enter GPA (0.0 - 4.0): ", MIN_GPA, MAX_GPA);
    newStudent.credits = readInt("Enter Credits Taken: ", 0, 1, 0, 0);

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
    int found = 0;
    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }
    int searchId = readInt("Enter Student ID to search: ", 1, 1, 0, 0);
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
    int matches = 0;
    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }
    float threshold = readFloat("Enter minimum GPA threshold: ", MIN_GPA, MAX_GPA);
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
    readLine("Enter major to search for: ", searchMajor, MAJOR_LEN);
    printf("\n-- Students majoring in '%s' --\n", searchMajor);
    printStudentHeader();
    /* Case-insensitive match so "computer science" finds "Computer Science" */
    for (int i = 0; i < reg->count; i++) {
        if (strcaseequal(reg->students[i].major, searchMajor)) {
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

/* Quick class-wide statistics (average GPA, highest/lowest GPA, total credits). */
void showStatistics(const Registry *reg) {
    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }
    float sumGpa = 0.0f;
    int totalCredits = 0;
    const Student *highest = &reg->students[0];
    const Student *lowest = &reg->students[0];

    for (int i = 0; i < reg->count; i++) {
        sumGpa += reg->students[i].gpa;
        totalCredits += reg->students[i].credits;
        if (reg->students[i].gpa > highest->gpa) highest = &reg->students[i];
        if (reg->students[i].gpa < lowest->gpa)  lowest = &reg->students[i];
    }

    printf("\n-- Class Statistics --\n");
    printf("Total students:   %d\n", reg->count);
    printf("Average GPA:      %.2f\n", sumGpa / reg->count);
    printf("Total credits:    %d\n", totalCredits);
    printf("Highest GPA:      %.2f (%s)\n", highest->gpa, highest->name);
    printf("Lowest GPA:       %.2f (%s)\n", lowest->gpa, lowest->name);
}