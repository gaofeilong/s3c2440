//
// shell sort, time complexity: O(nlogn)
//
Xsort(int *base, int beg, int end)
{
        int gap, i, j, temp; 
        int len = end - beg + 1;

        for (gap = len / 2; gap > 0; gap /= 2) {
                for (i = beg + gap; i <= end; ++i) {
                        temp = base[i];
                        for (j = i - gap; j >= beg && base[j] > temp; j -= gap) {
                                base[j + gap] = base[j];
                        }
                        base[j + gap] = temp;
                }
        }

        return;
}
