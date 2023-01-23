#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(string text, string key);

int main(int argc, string argv[])
{
    // Remind the user how to use the program if command-line argument not right
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Accepted command-line argument
    else
    {
        string key = argv[1];

        // Check the validity of the key argument
        bool is26char = strlen(key) == 26;
        bool isalphabetic = true;
        bool isunique = true;

        int char_count[26] = {0};
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            // Check if the key is containing only alphabetic character
            if (!isalpha(key[i]))
            {
                isalphabetic = false;
            }

            // Check if the key is containing each letter exactly once
            int ascii = tolower(key[i]) - 97;
            if (char_count[ascii] == 0)
            {
                char_count[ascii] = 1;
            }
            else
            {
                isunique = false;
            }
        }

        // Remind the user to provide a valid key
        if (!is26char || !isalphabetic || !isunique)
        {
            printf("Key must contain 26 characters, containing only alphabetic character, and containing each letter exactly once.\n");
            return 1;
        }

        // Accepted valid key
        else
        {
            // Get plaintext from user
            string plaintext = get_string("plaintext:  ");

            // Print out the ciphertext
            printf("ciphertext: ");
            encrypt(plaintext, key);
            printf("\n");
            return 0;
        }
    }
}

// Function to encrypt the plain text into ciphertext using given key
void encrypt(string text, string key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int dec;

        // Encrypt & print lowercase char
        if (islower(text[i]))
        {
            dec = tolower(key[text[i] - 97]);
            printf("%c", dec);

        }

        // Encrypt & print uppercase char
        else if (isupper(text[i]))
        {
            dec = toupper(key[text[i] - 65]);
            printf("%c", dec);
        }

        // Print non-alphabetic char
        else
        {
            printf("%c", text[i]);
        }
    }
}