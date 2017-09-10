//
// binary search
//

int *Bsearch(int *base, int beg, int end, int key)
{
        int mid;
        while (beg <= end) {
                mid = (beg + end) / 2; 
                if (key > base[mid]) {
                        beg = mid + 1; 
                } else if (key < base[mid]) {
                        end = mid - 1; 
                } else {
                        return base + mid; 
                }
        }

        return NULL;
}
