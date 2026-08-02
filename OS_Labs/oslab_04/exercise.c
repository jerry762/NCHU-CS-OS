#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "lib.h"

void print_arr(int arr[ARR_SIZE]);

int main(){

    int arr[ARR_SIZE] = {0};
    
    srand(time(NULL));

    for (int i = 0; i < ARR_SIZE; i++) {
        int num;
        bool duplicate;

        do {
            num = rand() % 150 + 1;
            duplicate = false;

            for (int j = 0; j < i; j++) {
                if (arr[j] == num) {
                    duplicate = true;
                    break;
                }
            }
        } while (duplicate);

        arr[i] = num;
    }


    
    printf("Before sort: ");
    print_arr(arr);

    sort(arr);

    printf("After sort: ");
    print_arr(arr);


    return 0;
}

void print_arr(int arr[ARR_SIZE])
{
    for(int i=0; i<ARR_SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}