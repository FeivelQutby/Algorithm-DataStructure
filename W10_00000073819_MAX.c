#include <stdio.h>
#include <stdlib.h>

typedef struct MaxHeap
{
    int *harr;
    int capacity;
    int heapsize;
} MaxHeap;

MaxHeap createHeap(int cap)
{
    MaxHeap newHeap;
    newHeap.heapsize = 0;
    newHeap.capacity = cap;
    newHeap.harr = malloc(sizeof(int) * cap);

    for (int i = 0; i < cap; i++)
    {
        newHeap.harr[i] = INT_MIN;
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

void insertkey(MaxHeap *mHeap, int k)
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

    while (i != 0 && mHeap->harr[parent(i)] < mHeap->harr[i])
    {
        swap(&mHeap->harr[i], &mHeap->harr[parent(i)]);
        i = parent(i);
    }
}

void maxheapify(MaxHeap *mHeap, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < mHeap->heapsize && mHeap->harr[l] > mHeap->harr[i])
        largest = l;
    if (r < mHeap->heapsize && mHeap->harr[r] > mHeap->harr[largest])
        largest = r;
    if (largest != i)
    {
        swap(&mHeap->harr[i], &mHeap->harr[largest]);
        maxheapify(mHeap, largest);
    }
}

int extractmax(MaxHeap *mHeap)
{
    if (mHeap->heapsize <= 0)
        return INT_MIN;
    if (mHeap->heapsize == 1)
    {
        mHeap->heapsize--;
        return mHeap->harr[0];
    }
    int max = mHeap->harr[0];
    mHeap->harr[0] = mHeap->harr[mHeap->heapsize - 1];
    mHeap->heapsize--;
    maxheapify(mHeap, 0);

    return max;
}

int getmax(MaxHeap *mHeap)
{
    return mHeap->harr[0];
}

void increasekey(MaxHeap *mHeap, int i, int newvalue)
{
    mHeap->harr[i] = newvalue;
    while (i != 0 && mHeap->harr[parent(i)] < mHeap->harr[i])
    {
        swap(&mHeap->harr[i], &mHeap->harr[parent(i)]);
        i = parent(i);
    }
}

void deletekey(MaxHeap *mHeap, int i)
{
    printf("Current Heap Size = %d\n\n", mHeap->heapsize);
    printf("Deleting index %d from heap\n", i);
    increasekey(mHeap, i, INT_MAX);
    extractmax(mHeap);
}

void printheap(MaxHeap mHeap)
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
    MaxHeap mHeap;
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
    printf("\nMax Value in Heap: %d \n", getmax(&mHeap));

    extractmax(&mHeap);
    printf("Extracting Max Value\n");
    printheap(mHeap);

    deletekey(&mHeap, 1);
    printheap(mHeap);

    return 0;
}