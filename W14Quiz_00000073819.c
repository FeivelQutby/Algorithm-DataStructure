#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 40
#define MAX_MAJOR_LENGTH 40

struct Student
{
    char name[MAX_NAME_LENGTH];
    char major[MAX_MAJOR_LENGTH];
    int task;
};

int compareNames(const void *a, const void *b)
{
    const struct Student *studentA = (const struct Student *)a;
    const struct Student *studentB = (const struct Student *)b;
    return strcmp(studentA->name, studentB->name);
}

int binarySearch(const struct Student database[], int low, int high, const char *key)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(database[mid].name, key);

        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

void displayStudents(const struct Student database[], int numstudents)
{
    printf("                           List of Students Informations                       \n");
    printf("-------------------------------------------------------------------------------\n");
    printf("| No. |               Name                 |           Major          | Score |\n");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < numstudents; i++)
    {
        printf("| %-3d ", i + 1);
        printf("| %-34s ", database[i].name);
        printf("| %-24s ", database[i].major);
        printf("| %-5d |\n", database[i].task);
    }
    printf("-------------------------------------------------------------------------------\n");
}

int readStudentDatabase(const char *filename, struct Student database[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file.\n");
        return 0;
    }

    int numstudents = 0;
    char line[MAX_NAME_LENGTH + MAX_MAJOR_LENGTH + 10];

    while (fgets(line, sizeof(line), fp) && numstudents < MAX_STUDENTS)
    {
        sscanf(line, "%[^😭]😭%[^😭]😭%d\n", database[numstudents].name, database[numstudents].major, &database[numstudents].task);
        numstudents++;
    }

    fclose(fp);
    return numstudents;
}

int main()
{
    struct Student database[MAX_STUDENTS];
    int numstudents;

    numstudents = readStudentDatabase("database_nilai.txt", database);
    if (numstudents == 0)
        return 1;

    while (1)
    {
        printf("Welcome to the simple student database (%d/%d)\n", numstudents, MAX_STUDENTS);
        printf("1. Show all students\n");
        printf("2. Search student\n");
        printf("3. Exit\n");
        printf("Choose: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            qsort(database, numstudents, sizeof(struct Student), compareNames);
            displayStudents(database, numstudents);
            printf("Press ENTER key to continue\n");
            getchar();
            break;

        case 2:
        {
            char key[MAX_NAME_LENGTH];
            printf("Enter the name of the student to search: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = '\0';

            qsort(database, numstudents, sizeof(struct Student), compareNames);

            int index = binarySearch(database, 0, numstudents - 1, key);

            if (index != -1)
            {
                printf("Student found!\n");
                printf("Name  : %s\n", database[index].name);
                printf("Major : %s\n", database[index].major);
                printf("Score : %d\n", database[index].task);
            }
            else
            {
                printf("Student not found.\n");
            }

            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }

        case 3:
            printf("Exiting program.\n");
            return 0;

        default:
            break;
        }
    }
}
