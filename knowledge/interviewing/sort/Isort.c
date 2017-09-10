//
// insert sort, time complexity:O(n*n)
//
void Isort(int *base, int beg, int end)
{
        int i, j, temp;
        for (i = beg + 1; i <= end; ++i) {
                temp = base[i];
                for (j = i - 1; j >= beg && base[j] > temp; --j) {
                        base[j + 1] = base[j]; 
                } 
                base[j + 1] = temp;
        }

        return;
}
