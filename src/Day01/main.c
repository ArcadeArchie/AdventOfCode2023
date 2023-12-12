#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILE_LENGTH 1000
#define MAX_LINE_LENGTH 60

void get_lines(FILE *file_ptr, char *lines[])
{
    // allocate memory
    for (int i = 0; i < FILE_LENGTH; i++)
    {
        lines[i] = malloc(MAX_LINE_LENGTH);
    }

    char current_line[MAX_LINE_LENGTH];
    int index = 0;
    while (fgets(current_line, sizeof(current_line), file_ptr))
    {
        int end_line = 0;
        for (end_line; end_line < MAX_LINE_LENGTH && current_line[end_line] != '\n'; end_line++)
        {
        }
        strncpy(lines[index], current_line, end_line);
        index++;
    }
}

int sum_array(char *array[])
{
    int sum = 0;

    for (int i = 0; i < FILE_LENGTH; i++)
    {
        int firstDigit = -1, lastDigit = -1;
        for (int j = 0; j < strlen(array[i]); j++)
        {
            if (isdigit(array[i][j]) && firstDigit < 0)
                firstDigit = array[i][j] - '0';
            if (isdigit(array[i][j]))
                lastDigit = array[i][j] - '0';
        }
        sum += firstDigit * 10 + lastDigit;
    }

    return sum;
}

int sum_spelled(char *array[])
{
    int sum = 0;
    for (int i = 0; i < FILE_LENGTH; i++)
    {
        int first = 0, last;
        for (int j = 0; j < strlen(array[i]); j++)
        {
            switch (array[i][j])
            {
            case 'o':
                if (array[i][j + 1] == 'n' && array[i][j + 2] == 'e')
                    array[i][j] = '1';
                break;
            case 't':
                if (array[i][j + 1] == 'w' && array[i][j + 2] == 'o')
                    array[i][j] = '2';
                if (array[i][j + 1] == 'h' && array[i][j + 2] == 'r' && array[i][j + 3] == 'e' && array[i][j + 4] == 'e')
                    array[i][j] = '3';
                break;
            case 'f':
                if (array[i][j + 1] == 'o' && array[i][j + 2] == 'u' && array[i][j + 3] == 'r')
                    array[i][j] = '4';
                if (array[i][j + 1] == 'i' && array[i][j + 2] == 'v' && array[i][j + 3] == 'e')
                    array[i][j] = '5';
                break;
            case 's':
                if (array[i][j + 1] == 'i' && array[i][j + 2] == 'x')
                    array[i][j] = '6';
                if (array[i][j + 1] == 'e' && array[i][j + 2] == 'v' && array[i][j + 3] == 'e' && array[i][j + 4] == 'n')
                    array[i][j] = '7';
                break;
            case 'e':
                if (array[i][j + 1] == 'i' && array[i][j + 2] == 'g' && array[i][j + 3] == 'h' && array[i][j + 4] == 't')
                    array[i][j] = '8';
                break;
            case 'n':
                if (array[i][j + 1] == 'i' && array[i][j + 2] == 'n' && array[i][j + 3] == 'e')
                    array[i][j] = '9';
                break;
            }
            if (isdigit(array[i][j]) && first == 0)
            {
                first = array[i][j] - '0';
            }
            if (isdigit(array[i][j]))
            {
                last = array[i][j] - '0';
            }
        }
        sum += (first * 10 + last);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filepath>\n", argv[0]);
        return -1;
    }
    FILE *input_ptr;
    errno_t res = fopen_s(&input_ptr, argv[1], "r");
    if (res != 0)
    {
        printf("Could not open %s, please check if the file path is valid.\n", argv[1]);
        return -1;
    }

    char *lines[FILE_LENGTH];
    get_lines(input_ptr, lines);

    // for (int i = 0; i < FILE_LENGTH; i++)
    // {
    printf("Sum of all values from input file: %d\n", sum_array(lines));
    printf("Sum of all spelled values from input file: %d\n", sum_spelled(lines));
    // }

    _fcloseall();
    for (int i = 0; i < FILE_LENGTH; i++)
    {
        free(lines[i]);
    }
    return 0;
}