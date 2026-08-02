#include <stdbool.h>

#include "lib.h"

void sort(int arr[ARR_SIZE])
{
    for(int i=1; i<ARR_SIZE; i++)
    {
        bool flag = false;

        for(int j=0; j<ARR_SIZE - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                flag = true;
            }
        }

        if(!flag)
            break;
    }
}
