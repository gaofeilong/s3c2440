//
// heap sort, time complexity: O(nlogn)
//

void Heap(int *base, int index, int len)
{
        int c, temp;
        c = 2 * index + 1;

        while (c < len) {
                if (c + 1 < len && base[c + 1] > base[c]) {
                        c += 1;
                } 
                if (base[c] > base[index]) {
                        temp = base[index];
                        base[index] = base[c];
                        base[c] = temp;
                        index = c;
                        c = 2 * index + 1;
                } else {
                        break; 
                }
        }

        return;
}

void Hsort(int *base, int len)
{
        int i, temp;
        for (i = len / 2; i >= 0; --i) {
                Heap(base, i, len); 
        }
        for (i = 0; i < len; ++i) {
                temp = base[len - i - 1];                         
                base[len - i - 1] = base[0];
                base[0] = temp;
                Heap(base, 0, len - i - 1);
        }

        return;
}
