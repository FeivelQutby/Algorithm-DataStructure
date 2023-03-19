#include <stdio.h>
#include <string.h>
#include <time.h>

void delay(int sec)
{
    int millisec = 1000 * sec;
    clock_t start_time = clock();
    while (clock() < start_time + millisec)
        ;
}

struct Student
{
    char name[30];
    char major[30];
    float gpa;
};

int main()
{
    struct Student database[20];
    int numstudents = 0, loop = 1, choice;

    while (loop)
    {
        printf("Welcome to simple student database (%d/20)\n", numstudents);
        printf("1. Show all students\n");
        printf("2. Input new student\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        {
            printf("                    List of Students Informations                    \n");
            printf("---------------------------------------------------------------------\n");
            printf("| No. |         Name           |           Major          |   GPA   |\n");
            printf("---------------------------------------------------------------------\n");
            for (int i = 0; i < numstudents; i++)
                printf("| %-3d | %-22s | %-24s | %.2f    |\n", i + 1, database[i].name, database[i].major, database[i].gpa);
            printf("---------------------------------------------------------------------\n");
            printf("Press ENTER key to continue");
            getchar();
            break;
        }
        case 2:
        {
            if (numstudents >= 20)
            {
                printf("Database is full.\n");
                printf("Press ENTER key to continue");
                getchar();
                break;
            }
            char name[30];
            char major[30];
            float gpa;

            printf("   Insert Student Information   \n");
            printf("--------------------------------\n");
            printf("Name   : ");
            fgets(name, 30, stdin);
            name[strcspn(name, "\n")] = 0;
            printf("Major  : ");
            fgets(major, 30, stdin);
            major[strcspn(major, "\n")] = 0;
            printf("GPA    : ");
            scanf("%f", &gpa);
            getchar();
            printf("Inserting data\n");

            struct Student new_student;
            strcpy(new_student.name, name);
            strcpy(new_student.major, major);
            new_student.gpa = gpa;

            database[numstudents] = new_student;
            delay(1);
            printf("New student added\n");
            numstudents++;
            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }
        case 3:
        {
            printf("Exiting program.\n");
            loop = 0;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}