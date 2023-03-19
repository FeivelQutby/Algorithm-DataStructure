#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int queue[MAX_SIZE];
int front = 0;
int rear = -1;
int itemCount = 0;
int firstInput = 0;

void enqueue(int data)
{
    if (rear == MAX_SIZE - 1)
    {
        printf("Queue is full\n");
        return;
    }
    rear++;
    queue[rear] = data;
    itemCount++;
}

void dequeue(int data)
{
    if (itemCount == 0)
    {
        printf("Queue is empty\n");
        return;
    }
    if (data > itemCount)
    {
        printf("Queue does not have that many items\n");
        return;
    }
    itemCount -= data;
    printf("Current queue is: ");
    for (int i = front; i <= rear; i++)
    {
        if (i < front + itemCount)
        {
            printf("%d ", queue[i]);
        }
        else
        {
            break;
        }
    }
    printf("\n");
    front += data;
}

int main()
{
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    firstInput = num;
    for (int i = 0; i < num; i++)
    {
        enqueue(num);
        printf("%d ", num);
    }
    printf("\n");
    while (1)
    {
        int input;
        printf("Enter number: ");
        scanf("%d", &input);
        if (input < firstInput)
        {
            dequeue(input);
        }
        else if (input > firstInput)
        {
            for (int i = firstInput + 1; i <= input; i++)
            {
                enqueue(i);
                printf("%d ", i);
            }
            printf("\n");
            firstInput = input;
        }
        else
        {
            for (int i = 0; i < num; i++)
            {
                printf("%d ", num);
            }
            printf("\n");
        }
    }
    return 0;
}