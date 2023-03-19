#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 30
#define MAX_MAJOR_LENGTH 30
#define STUDNUM 12

struct Student
{
    char name[MAX_NAME_LENGTH];
    char major[MAX_MAJOR_LENGTH];
    char studnumber[STUDNUM];
    struct Student *next;
};

void delay(int sec)
{
    int millisec = 1000 * sec;
    clock_t start_time = clock();
    while (clock() < start_time + millisec)
        ;
}

void add(struct Student **head_ref)
{
    char studnumber[STUDNUM];
    char name[MAX_NAME_LENGTH];
    char major[MAX_MAJOR_LENGTH];

    printf("NIM   : ");
    scanf("%s", studnumber);
    printf("Name  : ");
    scanf(" %[^\n]s", name);
    printf("Major : ");
    scanf(" %[^\n]s", major);

    struct Student *new_node = (struct Student *)malloc(sizeof(struct Student));
    strcpy(new_node->studnumber, studnumber);
    strcpy(new_node->name, name);
    strcpy(new_node->major, major);
    new_node->next = NULL;

    printf(" Inserting Data.\n");
    delay(1);

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
    }

    else
    {
        struct Student *last_node = *head_ref;
        while (last_node->next != NULL)
        {
            last_node = last_node->next;
        }
        last_node->next = new_node;
    }

    printf("Data Added.\n");
}

void displaystudent(struct Student *node)
{
    if (node == NULL)
    {
        printf("Linked list empty.\n");
    }
    else
    {
        printf("-----------------------------------------------------------------------\n");
        printf("|         Name           |           Major          |       NIM       |\n");
        printf("-----------------------------------------------------------------------\n");
        while (node != NULL)
        {
            printf("| %-22s ", node->name);
            printf("| %-24s ", node->major);
            printf("| %-15s |\n", node->studnumber);
            node = node->next;
        }
        printf("-----------------------------------------------------------------------\n");
    }
}

void deleteall(struct Student **head_ref)
{
    struct Student *current = *head_ref;
    struct Student *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
    printf("All data deleted.\n");
}

void deletefirstdata(struct Student **head_ref)
{
    if (*head_ref == NULL)
    {
        printf("Linked list empty.\n");
    }
    else
    {
        struct Student *temp = *head_ref;
        *head_ref = temp->next;
        free(temp);
        printf("First data deleted.\n");
    }
}

void delnim(struct Student **head_ref)
{
    char studnumber[STUDNUM];
    printf("NIM   : ");
    scanf("%s", studnumber);
    struct Student *current = *head_ref;
    struct Student *prev = NULL;

    if (current != NULL && strcmp(current->studnumber, studnumber) == 0)
    {
        *head_ref = current->next;
        free(current);
        printf("Data with the NIM %s deleted.\n", studnumber);
        return;
    }

    while (current != NULL && strcmp(current->studnumber, studnumber) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Data with the NIM %s is not in the list.\n", studnumber);
        return;
    }
    prev->next = current->next;
    free(current);
    printf("Data with the NIM %s deleted.\n", studnumber);
}

int main()
{
    struct Student *head = NULL;
    int choice, loop = 1;
    while (loop)
    {
        printf("Menu:\n");
        printf("1. Insert new node\n");
        printf("2. Print linked list\n");
        printf("3. Delete all data\n");
        printf("4. Delete first data\n");
        printf("5. Delete data by NIM\n");
        printf("0. Exit\n");
        printf("Choose : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add(&head);
            break;
        case 2:
            displaystudent(head);
            break;
        case 3:
            deleteall(&head);
            break;
        case 4:
            deletefirstdata(&head);
            break;
        case 5:
            delnim(&head);
            break;
        case 0:
            loop = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}