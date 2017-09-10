//
// quick sort, time complexity: O(nlogn)
//

void Qsort(int *base, int beg, int end)
{
        int l = beg;
        int h = end;
        int key = base[l];

        while (l < h) {
                while (l < h && base[h] >= key) {
                        --h; 
                }
                base[l] = base[h];
                while (l < h && base[l] <= key) {
                        ++l; 
                }
                base[h] = base[l];
        }
        base[l] = key;

        if (beg < l - 1) {
                Qsort(base, beg, l - 1); 
        }
        if (l + 1 < end) {
                Qsort(base, l + 1, end); 
        }
        return;
}
