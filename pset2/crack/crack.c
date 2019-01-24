#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[0])
{
    if (argc != 2)
    {
        printf("Exactly one argument required.\n");
        return 1;
    }
    else
    {
        string lets = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string hash = argv[1];
        int nlets = 53;

        char salt[3];
        memcpy(salt, hash, 2);
        salt[2] = '\0';
        char candidate[6] = "\0\0\0\0\0\0";

        for (int five = 0; five < nlets; five++)
        {
            for (int four = 0; four < nlets; four++)
            {
                for (int three = 0; three < nlets; three++)
                {
                    for (int two = 0; two < nlets; two++)
                    {
                        for (int one = 0; one < nlets; one++)
                        {
                            candidate[0] = lets[one];
                            candidate[1] = lets[two];
                            candidate[2] = lets[three];
                            candidate[3] = lets[four];
                            candidate[4] = lets[five];

                            if (strcmp(crypt(candidate, salt), hash) == 0)
                            {
                                printf("%s\n", candidate);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}
