//
// merge sort, time complexity: O(nlogn)
//

Merge(int *base, int beg, int mid, int end)
{
        int beg1 = beg, end1 = mid;
        int beg2 = mid + 1, end2 = end;
        int len  = end - beg + 1;
        int arr[len];
        int i = 0;

        while (beg1 <= end1 && beg2 <= end2) {
                if (base[beg1] < base[beg2]) {
                        arr[i++] = base[beg1++];
                } else {
                        arr[i++] = base[beg2++]; 
                }
        }
        while (beg1 <= end1) {
                arr[i++] = base[beg1++]; 
        }
        while (beg2 <= end2) {
                arr[i++] = base[beg2++]; 
        }

        beg1 = beg;
        for (i = 0; i < len; ++i) {
                base[beg1++] = arr[i];
        }

        return;
}

Msort(int *base, int beg, int end)
{
        int mid;
        if (beg < end) {
                mid = (beg + end) / 2; 
                Msort(base, beg, mid);
                Msort(base, mid + 1, end);
                Merge(base, beg, mid, end);
        }

        return;
}
