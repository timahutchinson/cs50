#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Required number of arguments is exactly one.\n");
        return 1;
    }
    else
    {
        int m = 0;
        int k = 0;
        int klen = strlen(argv[1]);

        for (int i = 0; i < klen; i++)
        {
            if (isdigit(argv[1][i]))
            {
                printf("Keyword can only contain letters.\n");
                return 1;
            }
        }

        string s = get_string("plaintext: ");

        printf("ciphertext: ");
        for (int i = 0, n = strlen(s), j = 0; i < n; i++)
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
                k = toupper(argv[1][j % klen]) - 65;
                printf("%c", (((s[i] - m + k) % 26) + m));
                j++;
            }
            else
            {
                printf("%c", s[i]);
            }
        }
        printf("\n");
    }
}
