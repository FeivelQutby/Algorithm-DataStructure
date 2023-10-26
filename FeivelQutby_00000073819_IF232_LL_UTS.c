#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 200

/*
Nama  : Feivel Qutby
NIM   : 00000073819
Kelas : LL
Nilai :
*/

typedef struct library
{
    char title[max];
    char author[max];
    int year;
    char publisher[max];
    char genre[max];
    struct library *next;
} book;

void display_library(book *head)
{
    if (head == NULL)
    {
        printf("No book!\n");
    }
    else
    {
        book *curr = head;
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("|          Title           |         Author          |  Year  |     Publisher     |     Genre     |\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        while (curr != NULL)
        {
            printf("| %-24s ", curr->title);
            printf("| %-23s ", curr->author);
            printf("| %-5d  ", curr->year);
            printf("| %-17s ", curr->publisher);
            printf("| %-13s |\n", curr->genre);
            curr = curr->next;
        }
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("Press ENTER key to continue");
        getchar();
    }
}

void add_book(book **head)
{
    book *new_release = (book *)malloc(sizeof(book));
    printf("=============================================\n");
    printf("Book Title    : ");
    scanf(" %[^\n]", new_release->title);
    getchar();
    printf("Author        : ");
    scanf(" %[^\n]", new_release->author);
    getchar();
    printf("Year Released : ");
    scanf("%d", &new_release->year);
    printf("Publisher     : ");
    scanf(" %[^\n]", new_release->publisher);
    getchar();
    printf("Genre         : ");
    scanf(" %[^\n]", new_release->genre);
    getchar();
    new_release->next = NULL;

    if (*head == NULL)
    {
        *head = new_release;
    }
    else
    {
        book *curr = *head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new_release;
    }

    printf("'%s' added to the library.\n", new_release->title);
    printf("Press ENTER key to continue");
    getchar();
}

void removeBook(book **head)
{
    if (*head == NULL)
    {
        printf("No books!\n");
        return;
    }

    book *temp = *head;
    *head = (*head)->next;
    printf("'%s' removed from library.\n", temp->title);
    free(temp);
    printf("Press ENTER key to continue");
    getchar();
}

void displayTotalBooks(book *head)
{
    int count = 0;
    book *curr = head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    printf("Total books: %d\n", count);
}

void searchBook(book *head)
{
    if (head == NULL)
    {
        printf("No book in the library!\n");
    }
    else
    {
        char query[max];
        printf("Search: ");
        scanf(" %[^\n]", query);
        getchar();
        book *curr = head;
        int found = 0;
        while (curr != NULL)
        {
            if (strcmp(curr->title, query) == 0)
            {
                printf("Book founded:\n");
                printf("---------------------------------------------------------------------------------------------------\n");
                printf("|          Title           |         Author          |  Year  |     Publisher     |     Genre     |\n");
                printf("---------------------------------------------------------------------------------------------------\n");
                printf("| %-24s ", curr->title);
                printf("| %-23s ", curr->author);
                printf("| %-5d  ", curr->year);
                printf("| %-17s ", curr->publisher);
                printf("| %-13s |\n", curr->genre);
                printf("---------------------------------------------------------------------------------------------------\n");
                found = 1;
                break;
            }
            curr = curr->next;
            printf("Press ENTER key to continue");
            getchar();
        }

        if (!found)
        {
            printf("'%s' not found.\n", query);
            printf("Press ENTER key to continue");
            getchar();
        }
    }
}

int main()
{
    int choice;
    book *head = NULL;

    FILE *fp = fopen("library.txt", "r");
    if (fp != NULL)
    {
        char buffer[max];
        while (fgets(buffer, max, fp))
        {
            book *new_release = (book *)malloc(sizeof(book));
            sscanf(buffer, "%[^,],%[^,],%d,%[^,],%[^,],\n", new_release->title, new_release->author, &new_release->year, new_release->publisher, new_release->genre);
            new_release->next = NULL;

            if (head == NULL)
            {
                head = new_release;
            }
            else
            {
                book *curr = head;
                while (curr->next != NULL)
                {
                    curr = curr->next;
                }
                curr->next = new_release;
            }
        }
        fclose(fp);
    }

    do
    {
        // system("clear"); /Hilangin comment kalau diplay di console, kalau di vscode biarkan karena vscode terminalny bakal rusak
        printf("\n==========================================\n");
        printf("         Cuman Sekedar Perpustakaan       \n");
        printf("==========================================\n");
        printf("1. Show books\n");
        printf("2. Add book\n");
        printf("3. Remove first book\n");
        printf("4. Books total\n");
        printf("5. Search books\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            display_library(head);
            break;
        case 2:
            add_book(&head);
            break;
        case 3:
            removeBook(&head);
            break;
        case 4:
            displayTotalBooks(head);
            break;
        case 5:
            searchBook(head);
            break;
        default:
            break;
        }
    } while (choice != 6);

    fp = fopen("library.txt", "w");
    if (fp != NULL)
    {
        book *curr = head;
        while (curr != NULL)
        {
            fprintf(fp, "%s,%s,%d,%s,%s,\n", curr->title, curr->author, curr->year, curr->publisher, curr->genre);
            curr = curr->next;
        }
        fclose(fp);
    }

    while (head != NULL)
    {
        book *temp = head;
        head = head->next;
        free(temp);
    }
    printf("Exiting Program.");
    return 0;
}