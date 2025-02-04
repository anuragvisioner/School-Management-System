
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

typedef struct {
    int rollNumber;
    char firstName[50];
    char course[50];
} Student;

// Function to add student data to the file
void addStudent() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNumber);
    printf("Enter First Name: ");
    scanf("%s", s.firstName);
    printf("Enter Course: ");
    scanf("%s", s.course);

    fprintf(file, "%d %s %s\n", s.rollNumber, s.firstName, s.course);
    fclose(file);
    printf("Student added successfully!\n");
}

// Function to find student by roll number
void findStudentByRollNumber() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    int roll;
    Student s;
    int found = 0;

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        if (s.rollNumber == roll) {
            printf("Student Found: %s, Course: %s\n", s.firstName, s.course);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (!found) {
        printf("Student not found!\n");
    }
}

// Function to find student by name
void findStudentByName() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    char name[50];
    Student s;
    int found = 0;

    printf("Enter First Name: ");
    scanf("%s", name);

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        if (strcmp(s.firstName, name) == 0) {
            printf("Student Found: Roll No: %d, Course: %s\n", s.rollNumber, s.course);
            found = 1;
        }
    }

    fclose(file);
    if (!found) {
        printf("Student not found!\n");
    }
}

// Function to find students by course
void findStudentsByCourse() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    char course[50];
    Student s;
    int found = 0;

    printf("Enter Course Name: ");
    scanf("%s", course);

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        if (strcmp(s.course, course) == 0) {
            printf("Student: %s, Roll No: %d\n", s.firstName, s.rollNumber);
            found = 1;
        }
    }

    fclose(file);
    if (!found) {
        printf("No students found in this course.\n");
    }
}

// Function to count students in the file
void countStudents() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    Student s;
    int count = 0;

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        count++;
    }

    fclose(file);
    printf("Total number of students: %d\n", count);
}

// Function to delete a student by roll number
void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    int roll;
    Student s;
    int found = 0;
    FILE *tempFile = fopen("temp.txt", "w");

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        if (s.rollNumber == roll) {
            found = 1;
        } else {
            fprintf(tempFile, "%d %s %s\n", s.rollNumber, s.firstName, s.course);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}

// Function to update student details
void updateStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    int roll;
    Student s;
    int found = 0;
    FILE *tempFile = fopen("temp.txt", "w");

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (fscanf(file, "%d %s %s", &s.rollNumber, s.firstName, s.course) != EOF) {
        if (s.rollNumber == roll) {
            printf("Enter New First Name: ");
            scanf("%s", s.firstName);
            printf("Enter New Course: ");
            scanf("%s", s.course);
            found = 1;
        }
        fprintf(tempFile, "%d %s %s\n", s.rollNumber, s.firstName, s.course);
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student updated successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nSchool Management System\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Student by Name\n");
        printf("4. Find Students by Course\n");
        printf("5. Count Students\n");
        printf("6. Delete Student\n");
        printf("7. Update Student\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: findStudentByRollNumber(); break;
            case 3: findStudentByName(); break;
            case 4: findStudentsByCourse(); break;
            case 5: countStudents(); break;
            case 6: deleteStudent(); break;
            case 7: updateStudent(); break;
            case 8: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
