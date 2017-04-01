#include <stdio.h>
#define M 50
#define P 500

int arr[M][P];
int mem[M];
int page[P];
int blocks;
int pages;

void init(void)
{
    int i, j;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < P; ++j) {
            arr[i][j] = 0;
        }
    }
    for (i = 0; i < M; ++i) {
        mem[i] = 0;
    }
}

void get_page(void)
{
    int i;
    printf("Please input the number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Please input the number of pages: ");
    scanf("%d", &pages);
    puts("Please input page numbers: ");
    for (i = 0; i < pages; ++i) {
        scanf("%d", &page[i]);
    }
}

int find(int key)
{
    int i;
    for (i = 0; i < blocks; ++i) {
        if (mem[i] == key) {
            break;
        }
    }
    return i;
}

void copy_to_arr(int index)
{
    int i, j;
    for (i = 0; i < blocks; ++i) {
        arr[i][index] = mem[i];
    }
}

void shift_right(int max)
{
    int i;
    for (i = max; i > 0; --i) {
        mem[i] = mem[i-1];
    }
}

int FIFO(void)
{
    int i, count, times;
    times = 0;
    for (i = 0, count = 0; count < blocks; ++i) {
        if (find(page[i]) >= blocks) {
            shift_right(blocks-1);
            count++;
            mem[0] = page[i];
        } else {
            ++times;
        }
        copy_to_arr(i);
    }
    for (; i < pages; ++i) {
        if (find(page[i]) >= blocks) {
            shift_right(blocks-1);
            mem[0] = page[i];
        } else {
            ++times;
        }
        copy_to_arr(i);
    }
    return times;
}

int LRU(void)
{
    int i, count, index, times;
    int temp;
    times = 0;
    for (i = 0, count = 0; count < blocks; ++i) {
        if ((index = find(page[i])) < blocks) {
            temp = mem[index];
            shift_right(index);
            mem[0] = temp;
            ++times;
        } else {
            shift_right(blocks-1);
            count++;
            mem[0] = page[i];
        }
        copy_to_arr(i);
    }
    for (; i < pages; ++i) {
        if ((index = find(page[i])) < blocks) {
            temp = mem[index];
            shift_right(index);
            mem[0] = temp;
            ++times;
        } else {
            shift_right(blocks-1);
            mem[0] = page[i];
        }
        copy_to_arr(i);
    }
    return times;
}

void show_arr(void)
{
    int i, j;
    printf("----------------------------------------\n");
    for (i = 0; i < blocks; ++i) {
        for (j = 0; j < pages; ++j) {
            printf("%d  ", arr[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

int main(void)
{
    int rate;
    get_page();
    init();
    rate = FIFO();
    show_arr();
    printf("Hit Rate: %d/%d\n", rate, pages);
    init();
    rate = LRU();
    show_arr();
    printf("Hit Rate: %d/%d\n", rate, pages);
    return 0;
}
