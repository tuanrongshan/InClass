/* include all the headers you need */

/* Please try to figure out how to design the parameter interface of your functions by observing the given bozo sort function */
/* Otherwise, you might suffer from rewriting your code to meet the final requirements */

int isSorted(int *idx, int *value, int len) {
    while (--len >= 1 ) {
        if (value[idx[len]] < value[idx[len-1]]) return 0;
    }
    return 1;
}

void bozo_sort(int *idx, int *value, int len) {
    while(!isSorted(idx, value, len)) {
        int l = rand() % len;
        int r = rand() % len;
        int t = idx[l];
        idx[l] = idx[r];
        idx[r] = t;
    }
}

void bubble_sort(int *idx, int *value, int len) {
	for(int i=len-1;i>=0;i--){
		for(int j=0;j<i;j++){
			if (value[idx[j+1]] < value[idx[j]]){
				int t = idx[j];
				idx[j] = idx[j+1];
				idx[j+1] = t;
			}
		}
	}
}

void partition(int *idx, int *value, int l, int r) {
    if(l >= r) return;

    int pivot = l;
    int ptrl = l+1, ptrr = r;
    while(ptrl <= ptrr) {
        if(value[idx[pivot]] > value[idx[ptrl]]) {
            ptrl++;
        }
        if(value[idx[pivot]] <= value[idx[ptrr]]) {
            ptrr--;
        }
        else if(value[idx[pivot]] <= value[idx[ptrl]] && value[idx[pivot]] > value[idx[ptrr]]) {
            // swap
            int t = idx[ptrl];
            idx[ptrl] = idx[ptrr];
            idx[ptrr] = t;
            ptrl++;
            ptrr--;
        }
    }
    // swap r pivot
    int t = idx[ptrr];
    idx[ptrr] = idx[pivot];
    idx[pivot] = t;

    partition(idx, value, l, ptrr-1);
    partition(idx, value, ptrr+1, r);
    return;
}

void quick_sort(int *idx, int *value, int len) {
    partition(idx, value, 0, len-1);
    return;
}

void bucket_sort() {}