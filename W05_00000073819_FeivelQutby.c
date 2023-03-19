#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song
{
    char singer[100];
    char album[100];
    char title[100];
    int year;
    struct Song *prev;
    struct Song *next;
} Song;

void displayPlaylist(Song *head)
{
    Song *current = head;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|         Singer           |            Song Title           |             Album             |   Year   |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    while (current != NULL)
    {
        printf("| %-24s ", current->singer);
        printf("| %-31s ", current->title);
        printf("| %-29s ", current->album);
        printf("| %-7d  |\n", current->year);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------------------------------\n");
}

void addSong(Song **head_ref)
{
    Song *newSong = (Song *)malloc(sizeof(Song));
    printf("Singer : ");
    scanf("%[^\n]s", newSong->singer);
    getchar();
    printf("Album  : ");
    scanf("%[^\n]s", newSong->album);
    getchar();
    printf("Title  : ");
    scanf("%[^\n]s", newSong->title);
    getchar();
    printf("Released Year : ");
    scanf("%d", &newSong->year);
    getchar();
    newSong->prev = NULL;
    newSong->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newSong;
    }
    else
    {
        Song *current = *head_ref;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newSong;
        newSong->prev = current;
    }
    printf("Data Added!\n");

    FILE *fp = fopen("playlist.txt", "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s*%s*%s*%d\n", newSong->singer, newSong->album, newSong->title, newSong->year);
        fclose(fp);
    }
}

void removeSong(Song **head_ref)
{
    if (*head_ref == NULL)
    {
        printf("Playlist is empty\n");
        return;
    }
    Song *current = *head_ref;
    while (current->next != NULL)
    {
        current = current->next;
    }
    printf("%s removed.\n", current->title);
    if (current->prev != NULL)
    {
        current->prev->next = NULL;
    }
    else
    {
        *head_ref = NULL;
    }
    free(current);

    FILE *fp = fopen("playlist.txt", "w");
    if (fp != NULL)
    {
        Song *current = *head_ref;
        while (current != NULL)
        {
            fprintf(fp, "%s*%s*%s*%d\n", current->singer, current->album, current->title, current->year);
            current = current->next;
        }
        fclose(fp);
    }
}

int main()
{
    Song *head = NULL;
    FILE *fp = fopen("playlist.txt", "r");
    if (fp != NULL)
    {
        char line[400];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char singer[100], album[100], title[100];
            int year;

            sscanf(line, "%[^*]*%[^*]*%[^*]*%d", singer, album, title, &year);

            Song *newSong = (Song *)malloc(sizeof(Song));
            strcpy(newSong->singer, singer);
            strcpy(newSong->album, album);
            strcpy(newSong->title, title);
            newSong->year = year;
            newSong->prev = NULL;
            newSong->next = NULL;

            if (head == NULL)
            {
                head = newSong;
            }
            else
            {
                Song *current = head;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newSong;
                newSong->prev = current;
            }
        }
        fclose(fp);
    }

    int choice = 0, loop = 1;
    while (loop)
    {
        printf("\nMenu :\n");
        printf("1. Show playlist\n");
        printf("2. Add song\n");
        printf("3. Remove song\n");
        printf("4. Exit\n");
        printf("Choose : ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            displayPlaylist(head);
            break;
        case 2:
            addSong(&head);
            break;
        case 3:
            removeSong(&head);
            break;
        case 4:
            loop = 0;
            Song *current = head;
            while (current != NULL)
            {
                Song *temp = current;
                current = current->next;
                free(temp);
            }
        }
    }
    return 0;
}