//
// Bubble sort, time complexity: O(n*n)
//

void Bsort(int *base, int beg, int end)
{
        int i, j, temp;
        for (i = beg; i <= end; i++) {
                for (j = i + 1; j <= end; j++) {
                        if (base[j] < base[i]) {
                                temp = base[j];
                                base[j] = base[i];
                                base[i] = temp;
                        } 
                } 
        }
        
        return;
}
