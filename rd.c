/* include all the headers you need */

/* Please try to figure out how to design the parameter interface of your functions by observing the given bozo sort function */
/* Otherwise, you might suffer from rewriting your code to meet the final requirements */
#define BUCKETCOUNT 100005
#define PERBUCKET 1000
#define DEBUG

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
    while(ptrl < ptrr) {
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
    if(value[idx[pivot]]>value[idx[ptrr]]){
	    int t = idx[ptrr];
	    idx[ptrr] = idx[pivot];
	    idx[pivot] = t;
	}
	else{
		ptrr=l;
	}

    partition(idx, value, l, ptrr-1);
    partition(idx, value, ptrr+1, r);
    return;
}

void quick_sort(int *idx, int *value, int len) {
    partition(idx, value, 0, len-1);
    return;
}

// Structure of a node in linked lists
typedef struct Node {
    int idx;
    struct Node *next;
} Node;

void bucket_sort(int *idx, int *value, int len) {
    // Create buckets
    Node *buckets[BUCKETCOUNT];
    // Initialize buckets
    for(int i = 0; i< BUCKETCOUNT; i++) {
        buckets[i] = NULL;
    }
    // Insert elements into buckets
    for(int i = 0; i< len; i++) {
        // Create node
        int bucket_num = value[idx[i]] / PERBUCKET;
        Node *new = malloc(sizeof(Node));
        new->idx = idx[i]; new->next = NULL;
        // Insert node
        Node *tmp = buckets[bucket_num];
        buckets[bucket_num] = new;
        new->next = tmp;
    }

    // Sort the elements in each linked list
    for(int bucket_num = 0; bucket_num< BUCKETCOUNT; bucket_num++) {
        Node *ptr = buckets[bucket_num];
        while(ptr != NULL) {
            // Swap the values of the two nodes if they are out of order
            Node *nxt = ptr->next;
            while(nxt != NULL) {
                // Swap the values of the two nodes if they are out of order
                if(value[ptr->idx] > value[nxt->idx]) {
                    int tmp = ptr->idx;
                    ptr->idx = nxt->idx;
                    nxt->idx = tmp;
                }
                nxt = nxt->next;
            }
            ptr = ptr->next;
        }
    }

    // Copy the sorted elements back into the original array
    int index = 0;
    for (int i = 0; i< BUCKETCOUNT; i++) {
        Node *currentNode = buckets[i];
        while(currentNode != NULL) {
            idx[index++] = currentNode->idx;
            currentNode = currentNode->next;
        }
    }

    return;
}

int main() {
    int idx = [0, 1, 2, 3, 4, 5];
    int value = [5, 4, 3, 2, 1, 0];
    int len = 6;

}