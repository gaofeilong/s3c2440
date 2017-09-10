//
// select sort, time complexity: O(n*n)
//

void Ssort(int *base, int beg, int end)
{
        int i, j, idx, temp;
        
        for (i = beg; i <= end; ++i) {
                for (j = i + 1, idx = i; j <= end; ++j) {
                        if (base[j] < base[idx]) {
                                idx = j; 
                        } 
                }
                temp = base[i];
                base[i] = base[idx];
                base[idx] = temp;
        }

        return;
}
