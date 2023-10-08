#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 30
#define MAX_MAJOR_LENGTH 30
#define STUDNUM 13

struct Score
{
    char studnumber[STUDNUM];
    int task;
    int mid;
    int final;
    float avg;
    char grade[3];
};

struct Student
{
    char name[MAX_NAME_LENGTH];
    char major[MAX_MAJOR_LENGTH];
    char studnumber[STUDNUM];
};

void delay(int sec)
{
    int millisec = 1000 * sec;
    clock_t start_time = clock();
    while (clock() < start_time + millisec)
        ;
}

void displayScore(struct Score datascore[], int numstudents)
{
    printf("                   List of Students Informations                 \n");
    printf("-----------------------------------------------------------------\n");
    printf("| No. |       NIM        | Task | Mid | Final | Average | Grade |\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < numstudents; i++)
    {
        printf("| %-3d ", i + 1);
        printf("| %-16s ", datascore[i].studnumber);
        printf("| %-4d ", datascore[i].task);
        printf("| %-3d ", datascore[i].mid);
        printf("| %-5d ", datascore[i].final);
        printf("| %-7.2f ", datascore[i].avg);
        printf("| %-6s|\n", datascore[i].grade);
    }
    printf("-----------------------------------------------------------------\n");
}

void displayStudents(struct Student database[], int numstudents)
{
    printf("                            List of Students Informations                          \n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("| No. |         Name           |           Major          |          NIM          |\n");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < numstudents; i++)
    {
        printf("| %-3d ", i + 1);
        printf("| %-22s ", database[i].name);
        printf("| %-24s ", database[i].major);
        printf("| %-18s    |\n", database[i].studnumber);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

void addStudent(struct Student database[], struct Score datascore[], int numstudents)
{

    char name[MAX_NAME_LENGTH];
    char major[MAX_MAJOR_LENGTH];
    char studnumber[STUDNUM];
    char grade[3];
    float avg;
    int task, mid, final;

    printf("   Insert Student Information   \n");
    printf("--------------------------------\n");
    printf("NIM    : ");
    fgets(studnumber, STUDNUM, stdin);
    studnumber[strcspn(studnumber, "\n")] = 0;
    printf("Name   : ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Major  : ");
    fgets(major, MAX_MAJOR_LENGTH, stdin);
    major[strcspn(major, "\n")] = 0;
    printf("--------------------------------\n");
    printf("Task   : ");
    scanf("%d", &task);
    getchar();
    printf("UTS    : ");
    scanf("%d", &mid);
    getchar();
    printf("UAS    : ");
    scanf("%d", &final);
    getchar();

    avg = (task + mid + final) / 3.0;

    if (avg >= 95.0)
    {
        strcpy(grade, "A+");
    }
    else if (avg >= 85.0)
    {
        strcpy(grade, "A");
    }
    else if (avg >= 80.0)
    {
        strcpy(grade, "A-");
    }
    else if (avg >= 75.0)
    {
        strcpy(grade, "B+");
    }
    else if (avg >= 70.0)
    {
        strcpy(grade, "B");
    }
    else if (avg >= 65.0)
    {
        strcpy(grade, "C");
    }
    else if (avg >= 60.0)
    {
        strcpy(grade, "C-");
    }
    else if (avg >= 55.0)
    {
        strcpy(grade, "D");
    }
    else
    {
        strcpy(grade, "E");
    }

    printf("Inserting data\n");
    delay(1);
    struct Student new_student;
    strcpy(new_student.name, name);
    strcpy(new_student.major, major);
    strcpy(new_student.studnumber, studnumber);
    database[numstudents] = new_student;

    struct Score new_score;
    strcpy(new_score.studnumber, studnumber);
    new_score.task = task;
    new_score.mid = mid;
    new_score.final = final;
    new_score.avg = avg;
    strcpy(new_score.grade, grade);
    datascore[numstudents] = new_score;

    FILE *fp = fopen("studentsdata.txt", "a");
    fprintf(fp, "%s,%s,%s\n", name, major, studnumber);
    fclose(fp);

    FILE *fp2 = fopen("studentsscore.txt", "a");
    fprintf(fp2, "%s,%d,%d,%d,%.2f,%s,\n", studnumber, task, mid, final, avg, grade);
    fclose(fp2);
}

int compareNIM(const void *a, const void *b)
{
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return strcmp(studentA->studnumber, studentB->studnumber);
}

int searchStudent(struct Student database[], int numstudents, char studnumber[])
{
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(database[i].studnumber, studnumber) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    struct Student database[MAX_STUDENTS];
    struct Score datascore[MAX_STUDENTS];
    int numstudents = 0, loop = 1, choice;
    char line[MAX_STUDENTS];

    FILE *fp = fopen("studentsdata.txt", "r");
    FILE *fp2 = fopen("studentsscore.txt", "r");
    int i = numstudents;
    while (fgets(line, sizeof(line), fp) && i < MAX_STUDENTS)
    {
        sscanf(line, "%[^,],%[^,],%s\n", database[i].name, database[i].major, database[i].studnumber);
        i++;
    }

    i = numstudents;
    while (fgets(line, sizeof(line), fp2) && i < MAX_STUDENTS)
    {
        sscanf(line, "%[^,],%d,%d,%d,%f,%[^,]\n", datascore[i].studnumber, &datascore[i].task, &datascore[i].mid, &datascore[i].final, &datascore[i].avg, datascore[i].grade);
        i++;
    }

    numstudents = i;
    fclose(fp);
    fclose(fp2);

    while (loop)
    {
        printf("Welcome to simple student database (%d/%d)\n", numstudents, MAX_STUDENTS);
        printf("1. Input new student\n");
        printf("2. Show all students information\n");
        printf("3. Show all students score\n");
        printf("4. Show student details\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 2:
        {
            displayStudents(database, numstudents);
            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }
        case 3:
        {
            displayScore(datascore, numstudents);
            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }
        case 1:
        {
            if (numstudents >= MAX_STUDENTS)
            {
                printf("Database is full.\n");
                printf("Press ENTER key to continue\n");
                getchar();
                break;
            }
            addStudent(database, datascore, numstudents);
            numstudents++;
            printf("New student added\n");
            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }
        case 5:
        {
            printf("Exiting program.\n");
            loop = 0;
            break;
        }
        case 4:
        {
            struct Student sortedDatabase[MAX_STUDENTS];
            struct Score sortedDataScore[MAX_STUDENTS];
            memcpy(sortedDatabase, database, numstudents * sizeof(struct Student));
            memcpy(sortedDataScore, datascore, numstudents * sizeof(struct Score));
            qsort(sortedDatabase, numstudents, sizeof(struct Student), compareNIM);

            printf("List of Students' NIM (in ascending order):\n");
            for (int i = 0; i < numstudents; i++)
            {
                printf("%d. %s\n", i + 1, sortedDatabase[i].studnumber);
            }

            char searchNumber[STUDNUM];
            printf("Enter student number to search: ");
            fgets(searchNumber, STUDNUM, stdin);
            searchNumber[strcspn(searchNumber, "\n")] = 0;

            int studentIndex = searchStudent(sortedDatabase, numstudents, searchNumber);
            if (studentIndex == -1)
            {
                printf("Student number not found.\n");
            }
            else
            {
                for (int i = 0; i < numstudents; i++)
                {
                    if (strcmp(database[i].studnumber, sortedDatabase[studentIndex].studnumber) == 0)
                    {
                        studentIndex = i;
                        break;
                    }
                }

                printf("-------------------------------------------------------------------------------------------------------\n");
                printf("|        Name          |          Major         |     NIM      | Task | Mid | Final | Average | Grade |\n");
                printf("-------------------------------------------------------------------------------------------------------\n");
                printf("| %-20s ", database[studentIndex].name);
                printf("| %-22s ", database[studentIndex].major);
                printf("| %-12s ", database[studentIndex].studnumber);
                printf("| %-4d ", datascore[studentIndex].task);
                printf("| %-3d ", datascore[studentIndex].mid);
                printf("| %-5d ", datascore[studentIndex].final);
                printf("| %-7.2f ", datascore[studentIndex].avg);
                printf("| %-6s|\n", datascore[studentIndex].grade);
                printf("-------------------------------------------------------------------------------------------------------\n");
            }

            printf("Press ENTER key to continue\n");
            getchar();
            break;
        }

        default:
            break;
        }
    }
    return 0;
}