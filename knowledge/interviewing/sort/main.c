#include <time.h>
#include <stdio.h>
#include <stdlib.h>     // for rand() and srand()
#include <unistd.h>     // for sleep()
#define  BUFSIZE         10
//#define  BSORT
//#define  SSORT
//#define  ISORT
//#define  XSORT
//#define  HSORT
//#define  MSORT
#define  QSORT
#define  BSEARCH

static void Show(int *base, int len)
{
        int i;
        for (i = 0; i < len; ++i) {
                printf("%d ", base[i]);
        }
        printf("\n");
}

#ifdef   SSORT
#include "Ssort.c"
#endif
#ifdef   QSORT
#include "Qsort.c"
#endif
#ifdef   BSORT
#include "Bsort.c"
#endif
#ifdef   ISORT
#include "Isort.c"
#endif
#ifdef   XSORT
#include "Xsort.c"
#endif
#ifdef   MSORT
#include "Msort.c"
#endif
#ifdef   HSORT
#include "Hsort.c"
#endif
#ifdef   BSEARCH
#include "Bsearch.c"
#endif

int main()
{
        int i, key, arr[BUFSIZE];
        int *p;

        while (1) {
                srand(time(0));
                for (i = 0; i < BUFSIZE; ++i) {
                        arr[i] = rand() % 255; 
                }

                printf("before sort:\n");
                Show(arr, BUFSIZE);

#ifdef  SSORT
                Ssort(arr, 0, BUFSIZE - 1); 
                printf("after select sort:\n");
#endif
#ifdef  QSORT
                Qsort(arr, 0, BUFSIZE - 1); 
                printf("after quick sort:\n");
#endif
#ifdef  BSORT
                Bsort(arr, 0, BUFSIZE - 1); 
                printf("after bubble sort:\n");
#endif
#ifdef  ISORT
                Isort(arr, 0, BUFSIZE - 1); 
                printf("after insert sort:\n");
#endif
#ifdef  XSORT
                Xsort(arr, 0, BUFSIZE - 1); 
                printf("after shell sort:\n");
#endif
#ifdef  MSORT
                Msort(arr, 0, BUFSIZE - 1); 
                printf("after merge sort:\n");
#endif
#ifdef  HSORT
                Hsort(arr, BUFSIZE);
                printf("after heap sort:\n");
#endif
                Show(arr, BUFSIZE);
                key = arr[rand() % 10];

                p = Bsearch(arr, 0, BUFSIZE - 1, key);
                if (!p) {
                        printf("%d not fond!\n", key); 
                } else {
                        printf("fond %d at arr[%d]\n", key, p - arr);
                }
                sleep(1);
        }
        return 0;
}
