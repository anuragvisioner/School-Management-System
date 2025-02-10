
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

typedef struct {
    char course[50];
    int rollNumber;
    char firstName[50];
    char lastName[50];
    
} Student;

// structure to store search data
typedef struct {
    char firstName[50];
    char course[50];
    int rollNumber;
} StudentRecord;

// Function to add student data to the file
void addStudent() {
    FILE *file = fopen(FILE_NAME, "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("Enter Course: ");
    scanf("%s", s.course);

    while (1) {
        int duplicate = 0;
        printf("Enter Roll Number Between (1 - 50): ");
        scanf("%d", &s.rollNumber);

        if (s.rollNumber > 0 && s.rollNumber <= 50) {
            rewind(file);
            Student temp;
            while (fscanf(file, "%s %d %s %s", temp.course, &temp.rollNumber, temp.firstName, temp.lastName) != EOF) {
                if (strcmp(temp.course, s.course) == 0 && temp.rollNumber == s.rollNumber) {
                    printf("Roll number already exists in this course. Please enter a different roll number.\n");
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) {
                break;
            }
        } else {
            printf("Invalid roll number.\n");
        }
    }

    printf("Enter First Name: ");
    scanf("%s", s.firstName);
    printf("Enter Last Name: ");
    scanf("%s", s.lastName);

    fprintf(file, "%s %d %s %s \n", s.course, s.rollNumber, s.firstName, s.lastName);
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
    StudentRecord students[100]; // Array to store matching student records
    int count = 0;

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    char course[50], firstName[50], lastName[50];
    int rollNumber;
    
    while (fscanf(file, "%s %d %s %s", course, &rollNumber, firstName, lastName) != EOF) {
        if (rollNumber == roll) {
            if (count < 100) {
                strcpy(students[count].firstName, firstName);
                strcpy(students[count].course, course);
                count++;
            }
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Student not found!\n");
    } else {
        printf("Matching Students:\n");
        for (int i = 0; i < count; i++) {
            printf("Name: %s, Course: %s\n", students[i].firstName, students[i].course);
        }
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
    StudentRecord students[100]; // Array to store matching student records
    int count = 0;

    printf("Enter First Name: ");
    scanf("%s", name);

    char course[50], firstName[50], lastName[50];
    int rollNumber;
    
    while (fscanf(file, "%s %d %s %s", course, &rollNumber, firstName, lastName) != EOF) {
        if (strcmp(firstName, name) == 0) {
            if (count < 100) {
                strcpy(students[count].firstName, firstName);
                strcpy(students[count].course, course);
                students[count].rollNumber = rollNumber;
                count++;
            }
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Student not found!\n");
    } else {
        printf("Matching Students:\n");
        for (int i = 0; i < count; i++) {
            printf("Roll No: %d, Name: %s, Course: %s\n", students[i].rollNumber, students[i].firstName, students[i].course);
        }
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

    while (fscanf(file, "%s %d %s %s",s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
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

    while (fscanf(file, "%s %d %s %s",s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
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
    Student students[50];
    int count = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    // Collect all students with the given roll number

    Student s;
    while (fscanf(file, "%s %d %s %s", s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
        if (s.rollNumber == roll) {
            students[count++] = s;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("No student found with this roll number.\n");
        return;
    }

    int selectedIndex = 0;
    if (count > 1) {
        printf("Multiple students found with roll number %d:\n", roll);
        for (int i = 0; i < count; i++) {
            printf("%d. %s %s (%s)\n", i + 1, students[i].firstName, students[i].lastName, students[i].course);
        }
        printf("Select the student to delete (1-%d): ", count);
        scanf("%d", &selectedIndex);
        selectedIndex--; // Convert to 0-based index
        if (selectedIndex < 0 || selectedIndex >= count) {
            printf("Invalid selection.\n");
            return;
        }
    }

    // Rewrite the file excluding the selected student
    
    file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%s %d %s %s", s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
        if (!(strcmp(s.course, students[selectedIndex].course) == 0 &&
              s.rollNumber == students[selectedIndex].rollNumber &&
              strcmp(s.firstName, students[selectedIndex].firstName) == 0 &&
              strcmp(s.lastName, students[selectedIndex].lastName) == 0)) {
            fprintf(tempFile, "%s %d %s %s\n", s.course, s.rollNumber, s.firstName, s.lastName);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    printf("Student deleted successfully!\n");
}

// Function to update student details
// Function to update student details
void updateStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No data found!\n");
        return;
    }

    Student students[100], s;
    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }

    int roll, count = 0, choice;
    
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    // Read file and store matching students
    while (fscanf(file, "%s %d %s %s", s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
        if (s.rollNumber == roll) {
            students[count++] = s;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("Student not found!\n");
        fclose(tempFile);
        remove("temp.txt");
        return;
    }

    // If multiple students found, ask user to choose
    if (count > 1) {
        printf("Multiple students found with roll number %d:\n", roll);
        for (int i = 0; i < count; i++) {
            printf("%d. %s %s (%s)\n", i + 1, students[i].firstName, students[i].lastName, students[i].course);
        }
        printf("Choose the correct student by number: ");
        scanf("%d", &choice);
        choice--;  // Adjust for 0-based indexing
    } else {
        choice = 0;
    }

    // Store old details before modification
    int originalRoll = students[choice].rollNumber;
    char originalCourse[50], originalFirstName[50], originalLastName[50];
    strcpy(originalCourse, students[choice].course);
    strcpy(originalFirstName, students[choice].firstName);
    strcpy(originalLastName, students[choice].lastName);

    // Get updated data
    printf("Enter New First Name: ");
    scanf("%s", students[choice].firstName);
    printf("Enter New Last Name: ");
    scanf("%s", students[choice].lastName);
    printf("Enter New Course: ");
    scanf("%s", students[choice].course);

    // Rewrite file, updating only the selected student
    file = fopen(FILE_NAME, "r");
    while (fscanf(file, "%s %d %s %s", s.course, &s.rollNumber, s.firstName, s.lastName) != EOF) {
        if (s.rollNumber == originalRoll &&
            strcmp(s.course, originalCourse) == 0 &&
            strcmp(s.firstName, originalFirstName) == 0 &&
            strcmp(s.lastName, originalLastName) == 0) {

            // Write updated details
            fprintf(tempFile, "%s %d %s %s\n", students[choice].course, students[choice].rollNumber, students[choice].firstName, students[choice].lastName);
        } else {
            // Write original details
            fprintf(tempFile, "%s %d %s %s\n", s.course, s.rollNumber, s.firstName, s.lastName);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    printf("Student updated successfully!\n");
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
