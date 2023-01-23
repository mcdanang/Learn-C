#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function prototype
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Gets some text from user
    string text = get_string("Text: ");

    // Calculate L (the average number of letters per 100 words in the text)
    float L = (float) count_letters(text) / count_words(text) * 100.0;

    // Calculate S (the average number of sentences per 100 words in the text)
    float S = (float) count_sentences(text) / count_words(text) * 100.0;

    // Calculate Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print out the grade level as defined by the Coleman-Liau index
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Function to count letters
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Function to count words
int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}

// Function to count sentences
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}