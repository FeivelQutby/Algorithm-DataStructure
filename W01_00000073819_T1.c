#include <stdio.h>
#include <string.h>

void uppercase(char *lyd)
{
    int ia;
    for (ia = 0; ia < strlen(lyd); ia++)
    {
        if (lyd[ia] >= 'a' && lyd[ia] <= 'z')
        {
            lyd[ia] -= 32;
        }
    }
}

void lowercase(char *lyd)
{
    int ia;
    for (ia = 0; ia < strlen(lyd); ia++)
    {
        if (lyd[ia] >= 'A' && lyd[ia] <= 'Z')
        {
            lyd[ia] += 32;
        }
    }
}

void switching(char *lyd)
{
    int ia;
    for (ia = 0; ia < strlen(lyd); ia++)
    {
        if (lyd[ia] >= 'a' && lyd[ia] <= 'z')
        {
            lyd[ia] -= 32;
        }
        else if (lyd[ia] >= 'A' && lyd[ia] <= 'Z')
        {
            lyd[ia] += 32;
        }
    }
}

int main()
{
    int pilihan;
    char lyd[500];

    do
    {
        printf("\n1. Uppercase\n");
        printf("2. Lowercase\n");
        printf("3. Switching\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 4)
            return 0;

        getchar();
        printf("\nMasukkan kata: ");
        scanf("%[^\n]s", &lyd);

        switch (pilihan)
        {
        case 1:
            uppercase(lyd);
            printf("%s\n", lyd);
            break;
        case 2:
            lowercase(lyd);
            printf("%s\n", lyd);
            break;
        case 3:
            switching(lyd);
            printf("%s\n", lyd);
            break;
        }
    } while (pilihan != 4);
    return 0;
}