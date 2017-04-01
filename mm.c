/**
 * 给最爱的小仙女，我要你天天开心
 * BY Yotta Liu, 2016.12.28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct node {
    int start;
    int length;
    char tag[20];
} job;

job used[MAX], unused[MAX];
int num_used, num_unused;

void quicksort(job *a, int left, int right, int (*a_less_than_b)(job *a, job *b), int (*a_greater_than_b)(job *a, job *b))
{
    int i, j;
    job temp, t;
    if (left > right)
        return;
    i = left;
    j = right;
    temp = a[left];
    while (i < j)
    {
        while (i < j && !a_less_than_b(&a[j], &temp))
            --j;
        while (i < j && !a_greater_than_b(&a[i], &temp))
            ++i;
        if (i < j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[left] = a[i];
    a[i] = temp;
    quicksort(a, left, i-1, a_less_than_b, a_greater_than_b);
    quicksort(a, i+1, right, a_less_than_b, a_greater_than_b);
}

int start_a_less_than_b(job *a, job *b)
{
    return a->start < b->start;
}

int start_a_greater_than_b(job *a, job *b)
{
    return a->start > b->start;
}

int length_a_less_than_b(job *a, job *b)
{
    return a->length < b->length;
}

int length_a_greater_than_b(job *a, job *b)
{
    return a->length > b->length;
}

void sort_by_start_asc(job *a, int n)
{
    quicksort(a, 0, n-1, start_a_less_than_b, start_a_greater_than_b);
}

void sort_by_length_asc(job *a, int n)
{
    quicksort(a, 0, n-1, length_a_less_than_b, length_a_greater_than_b);
}

void sort_by_length_desc(job *a, int n)
{
    quicksort(a, 0, n-1, length_a_greater_than_b, length_a_less_than_b);
}

void merge(void)
{
    int i, j, m, num;
    sort_by_start_asc(unused, num_unused);
    num = num_unused;
    for (m =0; m < num - 1; ++m) {
        for (i = 1; i < num_unused; ++i) {
            if (unused[i-1].start + unused[i-1].length == unused[i].start) {
                unused[i-1].length += unused[i].length;
                for (j = i; j < num_unused-1; ++j) {
                    unused[j] = unused[j+1];
                }
                num_unused--;
            }
        }
    }
}

void create_table(void)
{
    FILE *fp;
    char *fname = "mm_table.txt";
    int start, length, i;
    if ((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "Can't open the file \"%s\"!\n", fname);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < MAX; ++i) {
        fscanf(fp, "%d,%d", &start, &length);
        if (feof(fp))
            break;
        unused[i].start = start;
        unused[i].length = length;
        strcpy(unused[i].tag, "unused");
    }
    num_unused = i;
    merge();
    fclose(fp);
}

void show_status(void)
{
    int i, total;
    sort_by_start_asc(unused, num_unused);
    puts("used:");
    if (num_used) {
        puts("start\tlength\ttag");
    }
    total = 0;
    for (i = 0; i < num_used; ++i) {
        printf("%d\t%d\t%s\n", used[i].start, used[i].length, used[i].tag);
        total += used[i].length;
    }
    printf("total length: %d\n\n", total);

    puts("unused:");
    if (num_unused) {
        puts("start\tlength\ttag");
    }
    total = 0;
    for (i = 0; i < num_unused; ++i) {
        printf("%d\t%d\t%s\n", unused[i].start, unused[i].length, unused[i].tag);
        total += unused[i].length;
    }
    printf("total length: %d\n\n", total);
}

int get_job(job *one)
{
    int sel;
    printf("Please input job name which will be created (0 to end, 4 to release): ");
    scanf("%s", one->tag);
    if (!strcmp(one->tag, "0")) {
        return 0;
    } else if (!strcmp(one->tag, "4")) {
        return 4;
    }
    printf("Please input job size: ");
    scanf("%d", &one->length);
    printf("Please choose a algorithm (1. first fit, 2. best fit, 3. worst fit): ");
    scanf("%d", &sel);
    return sel;
}

int fit(job *one)
{
    int i, j;
    for (i = 0; i < num_unused; ++i) {
        if (unused[i].length >= one->length) {
            break;
        }
    }
    if (i == num_unused) {
        return 0;
    } else {
        one->start = unused[i].start;
        used[num_used++] = *one;
        if (unused[i].length == one->length) {
            for (j = i+1; j < num_unused; ++j) {
                unused[j-1] = unused[j];
            }
            num_unused--;
        } else {
            unused[i].start += one->length;
            unused[i].length -= one->length;
        }
        return 1;
    }
}


int first_fit(job *one)
{
    sort_by_start_asc(unused, num_unused);
    return fit(one);
}

int best_fit(job *one)
{
    sort_by_length_asc(unused, num_unused);
    return fit(one);
}

int worst_fit(job *one)
{
    sort_by_length_desc(unused, num_unused);
    return fit(one);
}

int search_by_tag(job *a, int n, char *tag)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (!strcmp(a[i].tag, tag)) {
            break;
        }
    }
    return i;
}

int search_by_start(job *a, int n, int start)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (a[i].start == start) {
            break;
        }
    }
    return i;
}

int search_by_stop(job *a, int n, int stop)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (a[i].start + a[i].length == stop) {
            break;
        }
    }
    return i;
}

void release(void)
{
    char name[20];
    int i, j, m, n;
back:
    printf("Please input job name which will be released (0 to cancel): ");
    scanf("%s", name);
    if (!strcmp(name, "0")) {
        return;
    }
    i = search_by_tag(used, num_used, name);
    if (i >= num_used) {
        puts("The job not found. Try again!");
        goto back;
    } else {
        m = search_by_start(unused, num_unused, used[i].start + used[i].length);
        n = search_by_stop(unused, num_unused, used[i].start);
        strcpy(used[i].tag, "unused");
        if (m >= num_unused) {
            if (n >= num_unused) {
                unused[num_unused++] = used[i];
            } else {
                unused[n].length += used[i].length;
            }
        } else {
            unused[m].start = used[i].start;
            unused[m].length += used[i].length;
        }
        for (j = i+1; j < num_used; ++j) {
            used[j-1] = used[j];
        }
        num_used--;
    }
}

int main(void)
{
    job one;
    int sel;
    int (*func)(job *one);
    num_used = 0;
    num_unused = 0;
    create_table();
    show_status();
    while (sel = get_job(&one)) {
        printf("\n");
        if (sel == 4) {
            release();
            show_status();
            continue;
        }
        switch (sel) {
        case 1:
            func = first_fit;
            break;
        case 2:
            func = best_fit;
            break;
        case 3:
            func = worst_fit;
            break;
        default:
            continue;
        }
        if (func(&one)) {
            show_status();
        } else {
            fprintf(stderr, "Can't alloc!\n");
        }
    }
    return 0;
}
