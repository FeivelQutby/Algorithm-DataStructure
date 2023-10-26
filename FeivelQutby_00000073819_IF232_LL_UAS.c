#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Nama : Feivel Qutby
NIM : 00000073819
Kelas : L
Nilai : (kosongkan)
*/

#define MAX_LIBRARY_SIZE 100
#define MAX_LENGTH 100
#define FILE_NAME "database-musik.txt"

struct Song
{
    char title[MAX_LENGTH];
    char artist[MAX_LENGTH];
    char album[MAX_LENGTH];
    int year;
};

struct MusicLibrary
{
    struct Song songs[MAX_LIBRARY_SIZE];
    int numSongs;
};

void displayMenu();
void sortLibrary(struct MusicLibrary *library);
void sortByTitle(struct MusicLibrary *library);
void sortByYear(struct MusicLibrary *library);
void searchLibrary(struct MusicLibrary *library);
int binarySearch(struct MusicLibrary *library, const char *searchTitle);
void initializeLibrary(struct MusicLibrary *library);
void loadSongsFromFile(struct MusicLibrary *library);
void addSong(struct MusicLibrary *library, const char *title, const char *artist, const char *album, int year);
void displayLibrary(struct MusicLibrary *library);
void searchByYear(struct MusicLibrary *library);

int main()
{
    struct MusicLibrary library;
    initializeLibrary(&library);
    loadSongsFromFile(&library);

    int choice;
    do
    {
        displayMenu();
        printf("Masukkan Pilihan mu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            sortLibrary(&library);
            break;
        case 2:
            searchLibrary(&library);
            break;
        case 3:
            searchByYear(&library);
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}

void displayMenu()
{
    printf("\n--- * Music Library Menu * ---\n");
    printf("1. Sort library\n");
    printf("2. Search library by title\n");
    printf("3. Search library by year\n");
    printf("4. Exit\n");
}

void sortLibrary(struct MusicLibrary *library)
{
    int sortChoice;

    printf("\n--- Sort Options ---\n");
    printf("1. Sort by title\n");
    printf("2. Sort by year\n");
    printf("Masukkan Pilihan mu: ");
    scanf("%d", &sortChoice);

    switch (sortChoice)
    {
    case 1:
        sortByTitle(library);
        displayLibrary(library);
        break;
    case 2:
        sortByYear(library);
        displayLibrary(library);
        break;
    default:
        printf("Invalid sort cuy. kembali ke main menu.\n");
        break;
    }
}

void sortByTitle(struct MusicLibrary *library)
{
    int i, j;
    struct Song tempSong;

    for (i = 0; i < library->numSongs - 1; i++)
    {
        for (j = 0; j < library->numSongs - i - 1; j++)
        {
            if (strcmp(library->songs[j].title, library->songs[j + 1].title) > 0)
            {
                tempSong = library->songs[j];
                library->songs[j] = library->songs[j + 1];
                library->songs[j + 1] = tempSong;
            }
        }
    }

    printf("Library sorted by title.\n");
}

void sortByYear(struct MusicLibrary *library)
{
    int i, j;
    struct Song tempSong;

    for (i = 0; i < library->numSongs - 1; i++)
    {
        for (j = 0; j < library->numSongs - i - 1; j++)
        {
            if (library->songs[j].year > library->songs[j + 1].year)
            {
                tempSong = library->songs[j];
                library->songs[j] = library->songs[j + 1];
                library->songs[j + 1] = tempSong;
            }
        }
    }

    printf("Library sorted by year.\n");
}

void searchLibrary(struct MusicLibrary *library)
{
    char searchTitle[MAX_LENGTH];
    printf("Enter the title to search for: ");
    scanf(" %[^\n]s", searchTitle);

    sortByTitle(library);
    int index = binarySearch(library, searchTitle);

    if (index != -1)
    {
        printf("ketemu cuy!\n");
        printf("Title : %s\n", library->songs[index].title);
        printf("Artist: %s\n", library->songs[index].artist);
        printf("Album : %s\n", library->songs[index].album);
        printf("Year  : %d\n", library->songs[index].year);
    }
    else
    {
        printf("Lagu tidak ditemukan.\n");
    }
}

int binarySearch(struct MusicLibrary *library, const char *searchTitle)
{
    int low = 0;
    int high = library->numSongs - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int compare = strcmp(library->songs[mid].title, searchTitle);

        if (compare == 0)
        {
            return mid;
        }
        else if (compare < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

void initializeLibrary(struct MusicLibrary *library)
{
    library->numSongs = 0;
}

void loadSongsFromFile(struct MusicLibrary *library)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Failed to open file '%s'. Exiting.\n", FILE_NAME);
        exit(1);
    }

    char title[MAX_LENGTH];
    char artist[MAX_LENGTH];
    char album[MAX_LENGTH];
    int year;

    while (fscanf(file, "%[^*]*%[^*]*%[^*]*%d\n", title, artist, album, &year) == 4)
    {
        addSong(library, title, artist, album, year);
    }

    fclose(file);
}

void addSong(struct MusicLibrary *library, const char *title, const char *artist, const char *album, int year)
{
    if (library->numSongs == MAX_LIBRARY_SIZE)
    {
        printf("Library is full. Cannot add more songs.\n");
        return;
    }

    strcpy(library->songs[library->numSongs].title, title);
    strcpy(library->songs[library->numSongs].artist, artist);
    strcpy(library->songs[library->numSongs].album, album);
    library->songs[library->numSongs].year = year;
    library->numSongs++;
}

void displayLibrary(struct MusicLibrary *library)
{
    printf("\n                                                    Music Library                                                       \n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("| No. |                 Title                  |       Artist        |                   Album                    | Year |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < library->numSongs; i++)
    {
        printf("| %-3d ", i + 1);
        printf("| %-38s ", library->songs[i].title);
        printf("| %-19s ", library->songs[i].artist);
        printf("| %-42s ", library->songs[i].album);
        printf("| %-5d |\n", library->songs[i].year);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
}

void searchByYear(struct MusicLibrary *library)
{
    int searchYear;
    printf("Enter the year to search for: ");
    scanf("%d", &searchYear);

    sortByYear(library);
    int found = 0;

    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("|                 Title                  |       Artist        |                   Album                    | Year |\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < library->numSongs; i++)
    {
        if (library->songs[i].year == searchYear)
        {
            if (!found)
            {
                found = 1;
            }
            printf("| %-38s ", library->songs[i].title);
            printf("| %-19s ", library->songs[i].artist);
            printf("| %-42s ", library->songs[i].album);
            printf("| %-4d |\n", library->songs[i].year);
        }
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    if (!found)
    {
        printf("No songs found for the year %d\n", searchYear);
    }
}
