#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === CONSTANTS === */
#define MAX_SUBJECTS 10
#define UNITS_PER_SUBJECT 3
#define TOTAL_UNITS

/* COURSE CODES */
#define COURSE_BSIT 1
#define COURSE_BSCS 2
#define COURSE_BSCE 3
#define COURSE_BSEE 4
#define COURSE_BSECE 5
#define COURSE_BSME 6
#define COURSE_BSARCH 7
#define COURSE_BSA 8

/* === FUNCTION DECLARATIONS === */
void getStudentInfo(void);
void calculateFees(char id[], char first[], char last[],
                   char middle[], char gender[], int course,
                   int year, int subjects);
int getMaxYearLevel(int courseCode);

/* === MAIN === */
int main(void) {
    char repeat;
    do {
        getStudentInfo();

        printf("\nProcess another student? (Y/N): ");
        scanf(" %c", &repeat);
        while (getchar() != '\n');
    } 
    while (repeat == 'Y' || repeat == 'y');

    printf("\nThank you for using the Student Accounting System (UC-MAIN).\n");
    return 0;
}

/* === INPUT FUNCTION === */
void getStudentInfo(void) {
    char id[20], first[50], last[50], middle[50], gender[20];
    int course, year, subjects;
    int maxYear;

    printf("\nSTUDENT ACCOUNTING SYSTEM (UC-MAIN)\n");

    printf("Enter ID Number: ");
    scanf("%s", id);
    while (getchar() != '\n');

    printf("Enter First Name: ");
    fgets(first, sizeof(first), stdin);
    first[strcspn(first, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(last, sizeof(last), stdin);
    last[strcspn(last, "\n")] = 0;

    printf("Enter Middle Name: ");
    fgets(middle, sizeof(middle), stdin);
    middle[strcspn(middle, "\n")] = 0;

    printf("Enter Gender: ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = 0;

    /* COURSE */
    do {
        printf("\n1=BSIT 2=BSCS 3=BSCE 4=BSEE\n");
        printf("5=BSECE 6=BSME 7=BSARCH 8=BSA\n");
        printf("Enter Course Code: ");
        scanf("%d", &course);
        while (getchar() != '\n');

        if (course < 1 || course > 8)
            printf("Invalid Course Code. Try again.\n");

    } while (course < 1 || course > 8);

    /* YEAR LEVEL */
    maxYear = getMaxYearLevel(course);
    do {
        printf("Enter Year Level (1-%d): ", maxYear);
        scanf("%d", &year);
        while (getchar() != '\n');

        if (year < 1 || year > maxYear)
            printf("Invalid Year Level. Try again.\n");

    } while (year < 1 || year > maxYear);

    /* SUBJECT COUNT */
    do {
        printf("Enter Number of Subjects (1-%d): ", MAX_SUBJECTS);
        scanf("%d", &subjects);
        while (getchar() != '\n');

        if (subjects < 1 || subjects > MAX_SUBJECTS)
            printf("Invalid number of subjects. Try again.\n");

    } while (subjects < 1 || subjects > MAX_SUBJECTS);

    /* SHOW INPUT BEFORE COMPUTATION */
    printf("\n========== ENTERED INFORMATION ==========\n");
    printf("ID Number   : %s\n", id);
    printf("First Name  : %s\n", first);
    printf("Last Name   : %s\n", last);
    printf("Middle Name : %s\n", middle);
    printf("Gender      : %s\n", gender);
    printf("Course Code : %d\n", course);
    printf("Year Level  : %d\n", year);

    /* CALCULATE FEES */
    calculateFees(id, first, last, middle, gender, course, year, subjects);
}

/* === MAX YEAR LEVEL PER COURSE === */
int getMaxYearLevel(int courseCode) {
    if (courseCode == COURSE_BSCE ||
        courseCode == COURSE_BSME ||
        courseCode == COURSE_BSARCH)
        return 5;

    return 4;
}

/* === FEE COMPUTATION === */
void calculateFees(char id[], char first[], char last[],
                   char middle[], char gender[], int courseCode,
                   int yearLevel, int numSubjects) 
{
    char courseDesc[100];
    float tuitionPerUnit, regFee, miscFee, labFee;
	/* COURSE FEES */
    switch (courseCode) {
        case COURSE_BSIT:
            strcpy(courseDesc, "BSIT - Information Technology");
            tuitionPerUnit = 356.75; miscFee = 1295.45; labFee = 1568.75; break;

        case COURSE_BSCS:
            strcpy(courseDesc, "BSCS - Computer Science");
            tuitionPerUnit = 357.75; miscFee = 1050.35; labFee = 1920.20; break;

        case COURSE_BSCE:
            strcpy(courseDesc, "BSCE - Civil Engineering");
            tuitionPerUnit = 345.94; miscFee = 1100.25; labFee = 1939.65; break;

        case COURSE_BSEE:
            strcpy(courseDesc, "BSEE - Electrical Engineering");
            tuitionPerUnit = 312.62; miscFee = 1150.15; labFee = 1959.10; break;

        case COURSE_BSECE:
            strcpy(courseDesc, "BSECE - Electronics Engineering");
            tuitionPerUnit = 378.44; miscFee = 1200.05; labFee = 1978.55; break;

        case COURSE_BSME:
            strcpy(courseDesc, "BSME - Mechanical Engineering");
            tuitionPerUnit = 326.11; miscFee = 1249.95; labFee = 1998.00; break;

        case COURSE_BSARCH:
            strcpy(courseDesc, "BSARCH - Architecture");
            tuitionPerUnit = 310.45; miscFee = 1299.85; labFee = 2017.45; break;

        case COURSE_BSA:
            strcpy(courseDesc, "BSA - Accountancy");
            tuitionPerUnit = 399.79; miscFee = 1349.75; labFee = 2036.90; break;
    }

    regFee = 500;

    int totalUnits = numSubjects * UNITS_PER_SUBJECT;
    float totalTuition = totalUnits * tuitionPerUnit;
    float totalFees = totalTuition + regFee + miscFee + labFee;

    float prelim = totalFees * 0.53;
    float midterm = totalFees * 0.64;
    float semifinal = totalFees * 0.75;
    float finalFee = totalFees;

    /* DISPLAY RESULTS */
    printf("\n========== ASSESSMENT SUMMARY ==========\n");
    printf("Course Description : %s\n", courseDesc);
    printf("Total Units        : %d\n", totalUnits);
    printf("Total Tuition      : %.2f\n", totalTuition);
    printf("Registration Fee   : %.2f\n", regFee);
    printf("Miscellaneous Fee  : %.2f\n", miscFee);
    printf("Laboratory Fee     : %.2f\n", labFee);
    printf("--------------------------------------\n");
    printf("Total Fees         : %.2f\n", totalFees);
    printf("--------------------------------------\n");
    printf("Prelim Assessment  : %.2f\n", prelim);
    printf("Midterm Assessment : %.2f\n", midterm);
    printf("Semi-Final Assess. : %.2f\n", semifinal);
    printf("Final Assessment   : %.2f\n", finalFee);
}
