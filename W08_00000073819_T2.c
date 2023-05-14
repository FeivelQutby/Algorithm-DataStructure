#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void expressionTree(char prefix[], int *index, Node **node)
{
    char c = prefix[*index];
    (*index)++;
    if (c == ' ' || c == '\0')
    {
        return;
    }
    if (!isOperator(c))
    {
        *node = createNode(c);
        return;
    }
    *node = createNode(c);
    expressionTree(prefix, index, &((*node)->left));
    expressionTree(prefix, index, &((*node)->right));
}

void inorderTraversal(Node *node)
{
    if (node)
    {
        inorderTraversal(node->left);
        printf("%c", node->data);
        inorderTraversal(node->right);
    }
}

void printInfixExpression(char prefix[])
{
    int index = 0;
    Node *root = NULL;
    expressionTree(prefix, &index, &root);
    inorderTraversal(root);
    printf("\n");
    free(root);
}

int main()
{
    int loop = 1, p;
    char prefix1[] = "-*+abcd";
    char prefix2[] = "*+ab+cd";
    char prefix3[] = "+/ab/cd";

    while (loop)
    {
        printf("\n1. -*+abcd\n");
        printf("2. *+ab+cd\n");
        printf("3. +/ab/cd\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &p);
        getchar();
        switch (p)
        {
        case 1:
            printf("ini salah    : -*+abcd\n");
            printf("Yang rillcuy : ");
            printInfixExpression(prefix1);
            break;
        case 2:
            printf("ini salah    : *+ab+cd\n");
            printf("Yang rillcuy : ");
            printInfixExpression(prefix2);
            break;
        case 3:
            printf("ini salah    : +/ab/cd\n");
            printf("Yang rillcuy : ");
            printInfixExpression(prefix3);
            break;
        case 4:
            loop = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
