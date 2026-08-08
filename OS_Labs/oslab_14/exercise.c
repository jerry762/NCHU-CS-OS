#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define PAGE_NO_SIZE 3
#define MEMORY_SIZE 16
#define OFFSET_SIZE 2

static char *logi_mem_A[PAGE_NO_SIZE] = {"ab", "ef", "cd"};
static int page_table_A[PAGE_NO_SIZE];

static char *logi_mem_B[PAGE_NO_SIZE] = {"rx", "yy", "zz"};
static int page_table_B[PAGE_NO_SIZE];

typedef enum process_no
{
    A, B
} process_no;

void print_logi_mem(process_no pcn);
void print_page_table(process_no pcn);
void print_phy_mem();

#pragma region Free_Frame_List declare

// data structure: free frame list(queue)

// op: push, pop, check_dup, print_list;

static int free_frame_list[MEMORY_SIZE];
static int list_cur_size = 0;

int pop_list();
int push_list(int num);
bool check_dup_list(int num);
void print_list();

#pragma endregion


int main()
{
    srand(time(NULL));

    // init free frame list
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        int num = rand() % MEMORY_SIZE;

        if (!check_dup_list(num))
        {
            push_list(num);
        }
        else
        {
            i--;
        }
    }

    // init process's page table
    for (int i = 0; i < PAGE_NO_SIZE; i++)
    {
        page_table_A[i] = pop_list();
        page_table_B[i] = pop_list();
    }
    
    print_logi_mem(A);
    print_page_table(A);

    printf("\n");

    print_logi_mem(B);
    print_page_table(B);

    printf("\n");

    print_phy_mem();

    printf("\n");

    print_list();

    return 0;
}

void print_phy_mem()
{
    printf("physical memory :\n");

    printf("%s\t%s\t%s\n", "frame", "offset", "data:");

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        bool found = false;

        for (int j = 0; j < PAGE_NO_SIZE; j++)
        {
            if (page_table_A[j] == i)
            {
                found = true;

                for (int k = 0; k < OFFSET_SIZE; k++)
                {
                    printf("%d\t%d\t%c\n", i, k, logi_mem_A[j][k]);
                }
                break;
            }
            
            if (page_table_B[j] == i)
            {
                found = true;

                for (int k = 0; k < OFFSET_SIZE; k++)
                {
                    printf("%d\t%d\t%c\n", i, k, logi_mem_B[j][k]);
                }
                break;
            }
        }

        if (!found)
        {
            for (int j = 0; j < OFFSET_SIZE; j++)
            {
                printf("%d\t%d\t%c\n", i, j, ' ');
            }
        }
    }
}

void print_logi_mem(process_no pcn)
{
    if (pcn == A)
    {
        printf("process A's logical memory:\n");

        for (int i = 0; i < PAGE_NO_SIZE; i++)
        {
            printf("%d\t%s\n", i, logi_mem_A[i]);
        }
    }
    else if (pcn == B)
    {
        printf("process B's logical memory:\n");

        for (int i = 0; i < PAGE_NO_SIZE; i++)
        {
            printf("%d\t%s\n", i, logi_mem_B[i]);
        }
    }
}

void print_page_table(process_no pcn)
{
    if (pcn == A)
    {
        printf("process A's page table:\n");

        for (int i = 0; i < PAGE_NO_SIZE; i++)
        {
            printf("%d\t%d\n", i, page_table_A[i]);
        }
    }
    else if (pcn == B)
    {
        printf("process B's page table:\n");

        for (int i = 0; i < PAGE_NO_SIZE; i++)
        {
            printf("%d\t%d\n", i, page_table_B[i]);
        }
    }
}


#pragma region Free_Frame_List impl

int pop_list()
{
    if (list_cur_size == 0)
    {
        printf("free_frame_list already empty!\n");
        return -1;
    }

    int pop_num = free_frame_list[0];
    list_cur_size--;

    for (int i = 0; i < list_cur_size; i++)
    {
        free_frame_list[i] = free_frame_list[i + 1];
    }

    return pop_num;
}

int push_list(int num)
{
    if (list_cur_size == MEMORY_SIZE)
    {
        printf("free_frame_list is full!\n");
        return -1;
    }

    free_frame_list[list_cur_size++] = num;

    return 0;
}

bool check_dup_list(int num)
{
    bool isDup = false;

    for (int i = 0; i < list_cur_size; i++)
    {
        if (free_frame_list[i] == num)
        {
            isDup = true;
            break;
        }
    }

    return isDup;
}

void print_list()
{
    printf("free frame table:\n");

    for (int i = 0; i < list_cur_size; i++)
    {
        printf("%d ", free_frame_list[i]);
    }
    printf("\n");
}

#pragma endregion
