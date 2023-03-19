#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int afakahvalid(char *expression)
{
    char stack[MAX_SIZE];
    int top = -1;
    int i;

    for (i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[' || expression[i] == '<')
        {
            stack[++top] = expression[i];
        }
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']' || expression[i] == '>')
        {
            if (top == -1)
            {
                return 0;
            }

            if ((expression[i] == ')' && stack[top] == '(') ||
                (expression[i] == '}' && stack[top] == '{') ||
                (expression[i] == ']' && stack[top] == '['))
            {
                top--;
            }
            else
            {
                return 0;
            }
        }
        else if ((expression[i] >= 'a' && expression[i] <= 'z') ||
                 (expression[i] >= 'A' && expression[i] <= 'Z') ||
                 (expression[i] >= '0' && expression[i] <= '0') ||
                 (expression[i] >= '0' && expression[i] <= '9') ||
                 expression[i] == '`' || expression[i] == '!' || expression[i] == '@' || expression[i] == '#' ||
                 expression[i] == '$' || expression[i] == '%' || expression[i] == '^' || expression[i] == '&' ||
                 expression[i] == '-' || expression[i] == '_' || expression[i] == '=' || expression[i] == '+' ||
                 expression[i] == ',' || expression[i] == '.' || expression[i] == '/' || expression[i] == '?' ||
                 expression[i] == ';' || expression[i] == '|' || expression[i] == ':')
        {
            return 0;
        }
    }

    if (top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char expression[MAX_SIZE];
    int loop = 1;
    while (loop)
    {
        printf("Masukkan pola (-1 exit): ");
        fgets(expression, MAX_SIZE, stdin);
        if (strcmp(expression, "-1\n") == 0)
        {
            return 0;
        }

        if (afakahvalid(expression))
        {
            printf("Valid parenthesis expression\n\n");
        }
        else
        {
            printf("Invalid parenthesis expression\n\n");
        }
    }
}