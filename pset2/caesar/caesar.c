#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You may only specify one argument.\n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        string s = get_string("plaintext: ");
        int m = 0;

        printf("ciphertext: ");
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (isupper(s[i]))
            {
                m = 65;
            }
            else
            {
                m = 97;
            }

            if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
            {
                printf("%c", (((s[i] - m + k) % 26) + m));
            }
            else
            {
                printf("%c", s[i]);
            }
        }
    }
    printf("\n");
}
