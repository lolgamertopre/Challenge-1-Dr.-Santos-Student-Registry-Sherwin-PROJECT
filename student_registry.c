#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50
#define MAJOR_LEN 50
<<<<<<< HEAD
#define MIN_GPA 0.0f
#define MAX_GPA 4.0f
=======
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22

typedef struct {
    int id;
    char name[NAME_LEN];
    char major[MAJOR_LEN];
    float gpa;
    int credits;
} Student;

<<<<<<< HEAD
Student students[MAX_STUDENTS];
int studentCount = 0;

/* ------------------- Function Prototypes ------------------- */
void showMenu(void);
void addStudent(void);
void displayAllStudents(void);
void searchById(void);
void searchByGpaThreshold(void);
void searchByMajor(void);
void showStatistics(void);
=======
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
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
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

<<<<<<< HEAD
        int result = scanf("%d", &choice);
        if (result == EOF) {
            printf("\nInput stream closed unexpectedly. Exiting.\n");
            break;
        }
        if (result != 1) {
=======
        if (scanf("%d", &choice) != 1) {
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
<<<<<<< HEAD
            case 1: addStudent();          break;
            case 2: displayAllStudents();  break;
            case 3: searchById();          break;
            case 4: searchByGpaThreshold();break;
            case 5: searchByMajor();       break;
            case 6: showStatistics();      break;
            case 0: printf("Goodbye, Dr. Santos!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
=======
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
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
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

<<<<<<< HEAD
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

void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) {
=======
void addStudent(Registry *reg) {
    if (reg->count >= MAX_STUDENTS) {
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
        printf("Cannot add more students. Registry is full (max %d).\n", MAX_STUDENTS);
        return;
    }

    Student newStudent;

    printf("\n-- Add New Student --\n");

<<<<<<< HEAD
    newStudent.id = readInt("Enter Student ID: ", 1, 1, 0, 0);
=======
    while (1) {
        printf("Enter Student ID: ");
        if (scanf("%d", &newStudent.id) == 1 && newStudent.id > 0) {
            clearInputBuffer();
            break;
        }
        printf("Invalid ID. Please enter a positive integer.\n");
        clearInputBuffer();
    }
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22

    for (int i = 0; i < reg->count; i++) {
        if (reg->students[i].id == newStudent.id) {
            printf("A student with ID %d already exists. Student not added.\n", newStudent.id);
            return;
        }
    }

<<<<<<< HEAD
    readLine("Enter Full Name: ", newStudent.name, NAME_LEN);
    readLine("Enter Major: ", newStudent.major, MAJOR_LEN);
    newStudent.gpa = readFloat("Enter GPA (0.0 - 4.0): ", MIN_GPA, MAX_GPA);
    newStudent.credits = readInt("Enter Credits Taken: ", 0, 1, 0, 0);
=======
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
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22

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

<<<<<<< HEAD
void searchById(void) {
=======
void searchById(const Registry *reg) {
    int searchId;
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
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

<<<<<<< HEAD
void searchByGpaThreshold(void) {
=======
void searchByGpaThreshold(const Registry *reg) {
    float threshold;
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
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

<<<<<<< HEAD
void searchByMajor(void) {
=======
void searchByMajor(const Registry *reg) {
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
    char searchMajor[MAJOR_LEN];
    int matches = 0;

    if (reg->count == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    readLine("Enter major to search for: ", searchMajor, MAJOR_LEN);

    printf("\n-- Students majoring in '%s' --\n", searchMajor);
    printStudentHeader();

<<<<<<< HEAD
    /* Case-insensitive match so "computer science" finds "Computer Science" */
    for (int i = 0; i < studentCount; i++) {
        if (strcaseequal(students[i].major, searchMajor)) {
            printStudentRow(students[i]);
=======
    for (int i = 0; i < reg->count; i++) {
        if (strstr(reg->students[i].major, searchMajor) != NULL) {
            printStudentRow(reg->students[i]);
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
            matches++;
        }
    }

    if (matches == 0) {
        printf("(No students found with this major.)\n");
    } else {
        printf("--------------------------------------------------------------------\n");
        printf("%d student(s) found.\n", matches);
    }
<<<<<<< HEAD
}

/* New: quick class-wide statistics (average GPA, highest/lowest GPA, total credits). */
void showStatistics(void) {
    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    float sumGpa = 0.0f;
    int totalCredits = 0;
    Student *highest = &students[0];
    Student *lowest = &students[0];

    for (int i = 0; i < studentCount; i++) {
        sumGpa += students[i].gpa;
        totalCredits += students[i].credits;
        if (students[i].gpa > highest->gpa) highest = &students[i];
        if (students[i].gpa < lowest->gpa)  lowest = &students[i];
    }

    printf("\n-- Class Statistics --\n");
    printf("Total students:   %d\n", studentCount);
    printf("Average GPA:      %.2f\n", sumGpa / studentCount);
    printf("Total credits:    %d\n", totalCredits);
    printf("Highest GPA:      %.2f (%s)\n", highest->gpa, highest->name);
    printf("Lowest GPA:       %.2f (%s)\n", lowest->gpa, lowest->name);
=======
>>>>>>> 3f2e8f8566d3b84538017ade8582333e3be04b22
}