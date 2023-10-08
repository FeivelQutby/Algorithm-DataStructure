#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *bil, int l, int r)
{
    int pivot = bil[r];
    int i = l - 1;

    for (int j = l; j <= r - 1; j++)
    {
        if (bil[j] <= pivot)
        {
            i++;
            swap(&bil[i], &bil[j]);
        }
    }
    swap(&bil[i + 1], &bil[r]);
    return (i + 1);
}

void quickSort(int *bil, int l, int r)
{
    if (l < r)
    {
        int pi = partition(bil, l, r);
        quickSort(bil, l, pi - 1);
        quickSort(bil, pi + 1, r);
    }
}

void merge(int *bil, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int le[n1];
    int ri[n2];
    for (j = 0; j < n2; j++)
    {
        le[i] = bil[l + i];
    }
    for (i = 0; i < n1; i++)
    {
        ri[j] = bil[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (le[i] <= ri[j])
        {
            bil[k] = le[i];
            i++;
        }
        else
        {
            bil[k] = ri[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        bil[k] = le[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        bil[k] = ri[j];
        j++;
        k++;
    }
}

void mergeSort(int *bil, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(bil, l, m);
        mergeSort(bil, m + 1, r);
        merge(bil, l, m, r);
    }
}

int main()
{
    int i, n, *bil;
    printf("Banyak bilangan: ");
    scanf("%d", &n);

    bil = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        printf("Input bilangan ke-%d: ", i + 1);
        scanf("%d", &bil[i]);
    }

    quickSort(bil, 0, n - 1);
    printf("Hasil quick sort:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", bil[i]);
    }

    mergeSort(bil, 0, n - 1);
    printf("\nHasil merge sort:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", bil[i]);
    }

    return 0;
}