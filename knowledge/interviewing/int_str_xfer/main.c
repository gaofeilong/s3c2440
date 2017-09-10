#include <stdio.h>      // for printf
#include <string.h>     // for memset
#define  LEN    10

int atoi(const char *str)
{
        int i, num = 0;
        for (i = 0; str[i] != '\0' && str[i] >= '0' && str[i] <= '9'; i++) {
                num = num * 10 + str[i] - '0'; 
        }
        return num;
}

char *itoa(char str[], int num)
{
        int r, i, j = 0;
        do {
                r = num % 10; 
                num /= 10;
                str[j++] = r + '0';
        } while (num != 0);
        str[j] = '\0';

        for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
                str[i] ^= str[j];
                str[j] ^= str[i];
                str[i] ^= str[j];
        }
        return str;
}

int main()
{
        int a = 0;
        int b = 1324;
        char str1[LEN] = "ab123";
        char str2[LEN] = "123ab";
        char buf[LEN];


        printf("%d\n", atoi(str1));
        printf("%d\n", atoi(str2));
        printf("%s\n", itoa(buf, a));
        printf("%s\n", itoa(buf, b));


        return 0;
}
