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
    // }

    _fcloseall();
    for (int i = 0; i < FILE_LENGTH; i++)
    {
        free(lines[i]);
    }
    return 0;
}