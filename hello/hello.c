#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt name from user
    string name = get_string("What's your name? ");
    //print your name
    printf("hello, %s\n", name);
}