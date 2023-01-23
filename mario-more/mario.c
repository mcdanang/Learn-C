#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt user for height of pyramids (only accept number 1 to 8)
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //create pyramids
    for (int i = 0; i < height; i++)
    {
        //create left spaces
        for (int j = i; j < height - 1; j++)
        {
            printf(" ");
        }

        //create left bricks
        for (int j = height - i; j <= height; j++)
        {
            printf("#");
        }

        //create middle spaces
        printf("  ");

        //create right bricks
        for (int j = height - i; j <= height; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}