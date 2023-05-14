#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap
{
    int *harr;
    int capacity;
    int heapsize;
} MinHeap;

MinHeap createHeap(int cap)
{
    MinHeap newHeap;
    newHeap.heapsize = 0;
    newHeap.capacity = cap;
    newHeap.harr = malloc(sizeof(int) * cap);

    for (int i = 0; i < cap; i++)
    {
        newHeap.harr[i] = 0;
    }

    return newHeap;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return (2 * i + 1);
}

int right(int i)
{
    return (2 * i + 2);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertkey(MinHeap *mHeap, int k)
{
    printf("Current Heap Size = %d\n\n", mHeap->heapsize);
    printf("Inserting %d to heap\n", k);
    if (mHeap->heapsize == mHeap->capacity)
    {
        printf("\nOverflow: Could not insertkey\n");
        return;
    }

    mHeap->heapsize++;
    int i = mHeap->heapsize - 1;
    mHeap->harr[i] = k;

    while (i != 0 && mHeap->harr[parent(i)] > mHeap->harr[i])
    {
        swap(&mHeap->harr[i], &mHeap->harr[parent(i)]);
        i = parent(i);
    }
}

void minheapify(MinHeap *mHeap, int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < mHeap->heapsize && mHeap->harr[l] < mHeap->harr[i])
        smallest = l;
    if (r < mHeap->heapsize && mHeap->harr[r] < mHeap->harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&mHeap->harr[i], &mHeap->harr[smallest]);
        minheapify(mHeap, smallest);
    }
}

int extractmin(MinHeap *mHeap)
{
    if (mHeap->heapsize <= 0)
        return INT_MAX;
    if (mHeap->heapsize == 1)
    {
        mHeap->heapsize--;
        return mHeap->harr[0];
    }

    int root = mHeap->harr[0];
    mHeap->harr[0] = mHeap->harr[mHeap->heapsize - 1];
    mHeap->heapsize--;
    minheapify(mHeap, 0);

    return root;
}

int getmin(MinHeap *mHeap)
{
    return mHeap->harr[0];
}

void decreasekey(MinHeap *mHeap, int i, int newvalue)
{
    mHeap->harr[i] = newvalue;
    while (i != 0 && mHeap->harr[parent(i)] > mHeap->harr[i])
    {
        swap(&mHeap->harr[i], &mHeap->harr[parent(i)]);
        i = parent(i);
    }
}

void deletekey(MinHeap *mHeap, int i)
{
    printf("Current Heap Size = %d\n\n", mHeap->heapsize);
    printf("Deleting index %d from heap\n", i);
    decreasekey(mHeap, i, INT_MIN);
    extractmin(mHeap);
}

void printheap(MinHeap mHeap)
{
    printf("Current heap : ");
    for (int i = 0; i < mHeap.heapsize; i++)
    {
        printf("%d ", mHeap.harr[i]);
    }
    printf("\n");
}

int main()
{
    MinHeap mHeap;
    mHeap = createHeap(11);

    printheap(mHeap);
    insertkey(&mHeap, 3);
    printheap(mHeap);
    insertkey(&mHeap, 2);
    printheap(mHeap);
    deletekey(&mHeap, 1);
    printheap(mHeap);
    insertkey(&mHeap, 15);
    printheap(mHeap);
    insertkey(&mHeap, 5);
    printheap(mHeap);
    insertkey(&mHeap, 4);
    printheap(mHeap);
    insertkey(&mHeap, 45);
    printheap(mHeap);
    printf("\nMin Value in Heap: %d \n", getmin(&mHeap));

    extractmin(&mHeap);
    printf("Extracting Min Value\n");
    printheap(mHeap);

    deletekey(&mHeap, 1);
    printheap(mHeap);

    return 0;
}