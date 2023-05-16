#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_rand_int(int start, int end){
    int mod = end - start + 1;
    return start + rand() % mod;
}

char* get_rand_name(int len){
    char* str = malloc((len+1) * sizeof(char));

    for(int i=0; i<len; i++){
        int is_upper = rand()%2;
        if(is_upper){
            str[i] = 'A' + (rand()%26);
        }else{
            str[i] = 'a' + (rand()%26);
        }
    }
    str[len] = '\0';
    return str;
}

int main() {
    //--change here---
    int N = 5;
    int min_name_len = 6;
    int max_name_len = 15;
    int shuffle_strength = 100;
    //---------------
    char* name[5*N + 10]; //name sorted by score
    int score[5*N + 10]; //sorted
    
    //generate name for i-th student
    for(int i=1; i<=5 * N; i++){
        int len = get_rand_int(min_name_len, max_name_len);
        name[i] = get_rand_name(len);
    }
    
    //generate score for i-th student
    score[1] = 100000000;
    int inc = 100000000 / (5*N);
    for(int i=2; i<=5 * N; i++){
        score[i] = score[i-1] - get_rand_int((inc/2)+1, inc);
    }

    //sample output
    FILE *fptr = fopen("out.txt", "w");
    for(int i = 1; i <= N; i++) {
        fprintf(fptr, "Group %d:\n", i);
        fprintf(fptr, "%s %d\n", name[0*N+i], 0*N+i);
        fprintf(fptr, "%s %d\n", name[1*N+i], 1*N+i);
        fprintf(fptr, "%s %d\n", name[2*N+i], 2*N+i);
        fprintf(fptr, "%s %d\n", name[3*N+i], 3*N+i);
        fprintf(fptr, "%s %d\n\n", name[4*N+i], 4*N+i);
    }
    fclose(fptr);
    
    //define shuffle
    int shuffle[5*N];
    for(int i=1; i<=5*N; i++){
        shuffle[i] = i;
    }
    
    for(int i=0; i<shuffle_strength; i++){
        int a = get_rand_int(1, 5*N);
        int b = get_rand_int(1, 5*N);
        while(a == b) b = get_rand_int(1, 5*N);
        swap(&shuffle[a], &shuffle[b]);
    }
    FILE *fptr2 = fopen("in.txt", "w");
    fprintf(fptr2, "%d\n", N);
    for(int i=1; i<5 * N; i++){
        fprintf(fptr2, "%s %d\n", name[shuffle[i]], score[shuffle[i]]);
    }
    fclose(fptr2);

    return 0;
}
