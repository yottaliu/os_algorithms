#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define READY 0
#define RUNNING 1
#define FINISH 2

typedef struct node
{
    char name[10];              /* 进程标识符 */
    int prio;                   /* 进程优先数 */
    int round;                  /* 进程时间轮转时间片 */
    int cputime;                /* 进程占用 CPU 时间*/
    int needtime;               /* 进程到完成还需要的时间*/
    int count;                  /* 计数器*/
    char state;                 /* 进程的状态*/
    struct node *next;          /*链指针*/
} PCB;

int tick;

PCB* make_ready()
{
    PCB *head, *prev, *curr;
    char name[10];
    int time;
    head = NULL;
    printf("Please input process name (0 to end): ");
    //fgets(name, 10, stdin);
    scanf("%s", name);
    while (strcmp(name, "0") != 0) {
    	printf("Please input process time: ");
        scanf("%d", &time);
        curr = (PCB *)malloc(sizeof(PCB));
        strcpy(curr->name, name);
        curr->prio = 0;
        curr->round = (time+tick-1) / tick;
        curr->cputime = 0;
        curr->needtime = time;
        curr->count = 0;
        curr->state = READY;
        curr->next = NULL;
        if (head) {
            prev->next = curr;
        } else {
            head = curr;
        }
        prev = curr;
        printf("Please input process name (0 to quit): ");
        //fgets(name, 10, stdin);
        scanf("%s", name);
    }
    return head;
}

int get_menu(void)
{
    int sel;
    printf("Please select a algorithm (1. RR, 2. FCFS): ");
    scanf("%d", &sel);
    return sel;
}

void delay(int seconds)
{
    clock_t start = clock();
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;

    while ((clock()-start) < lay)
        continue;
}

void show_list(PCB *list)
{
    while (list) {
        printf("%s\t%d\t%d\t%d\t%d\t\t%d\t",
               list->name,
               list->prio,
               list->round,
               list->cputime,
               list->needtime,
               list->count);
        switch (list->state) {
        case READY:
            printf("READY");
            break;
        case RUNNING:
            printf("RUNNING");
            break;
        case FINISH:
            printf("FINISH");
            break;
        }
        printf("\n");
        list = list->next;
    }
}

PCB* find_tail(PCB *list)
{
    PCB *tail = list;
    if (tail) {
        while (tail->next) {
            tail = tail->next;
        }
    }
    return tail;
}


void free_list(PCB *list)
{
    PCB *next;
    while (list) {
        next = list->next;
        free(list);
        list = next;
    }
}

void RR(PCB *ready)
{
    PCB *running, *finish, *tail;
    running = NULL;
    finish = NULL;
    if (ready) {
        running = ready;
        ready = ready->next;
        running->state = RUNNING;
        running->next = NULL;
    } else {
        running = NULL;
    }
    while (running) {
        printf("name\tprio\tround\tcputime\tneedtime\tcount\tstate\n");
        show_list(running);
        show_list(ready);
        show_list(finish);
        printf("\n");
        running->cputime += tick;
        running->needtime -= tick;
        running->count += 1;
        if (running->needtime <= 0) {
            running->cputime += running->needtime;
            running->needtime = 0;
            running->state = FINISH;
            tail = find_tail(finish);
            if (tail) {
                tail->next = running;
            } else {
                finish = running;
            }
        } else {
            running->state = READY;
            tail = find_tail(ready);
            if (tail) {
                tail->next = running;
            } else {
                ready = running;
            }
        }
        if (ready) {
            running = ready;
            ready = ready->next;
            running->state = RUNNING;
            running->next = NULL;
        } else {
            running = NULL;
        }
        delay(1);
    }
    printf("name\tprio\tround\tcputime\tneedtime\tcount\tstate\n");
    show_list(running);
    show_list(ready);
    show_list(finish);
    printf("\n");
    free_list(finish);
}

void FCFS(PCB *ready)
{
    PCB *running, *finish, *tail;
    running = NULL;
    finish = NULL;
    if (ready) {
        running = ready;
        ready = ready->next;
        running->state = RUNNING;
        running->next = NULL;
    }
    while (running) {
        printf("name\tprio\tround\tcputime\tneedtime\tcount\tstate\n");
        show_list(running);
        show_list(ready);
        show_list(finish);
        printf("\n");
        running->cputime += tick;
        running->needtime -= tick;
        running->count += 1;
        if (running->needtime <= 0) {
            running->cputime += running->needtime;
            running->needtime = 0;
            running->state = FINISH;
            tail = find_tail(finish);
            if (tail) {
                tail->next = running;
            } else {
                finish = running;
            }
            if (ready) {
                running = ready;
                ready = ready->next;
                running->state = RUNNING;
                running->next = NULL;
            } else {
                running = NULL;
            }
        }
        delay(1);
    }
    printf("name\tprio\tround\tcputime\tneedtime\tcount\tstate\n");
    show_list(running);
    show_list(ready);
    show_list(finish);
    printf("\n");
    free_list(finish);
}

PCB* copy_list(PCB *list)
{
    PCB *head, *prev, *curr;
    head = NULL;
    while (list) {
        curr = (PCB *)malloc(sizeof(PCB));
        *curr = *list;
        if (head) {
            prev->next = curr;
        } else {
            head = curr;
        }
        prev = curr;
        list = list->next;
    }
    return head;
}

int main(void)
{
    PCB *ready, *temp;
    int sel;
    ready = NULL;
    printf("Please input tick time: ");
    scanf("%d", &tick);
    ready = make_ready();
    /*
    curr = ready;
    while (curr) {
        puts(curr->name);
        curr = curr->next;
    }
    */
back:
    sel = get_menu();
    temp = copy_list(ready);
    switch (sel) {
    case 1:
        RR(temp);
        break;
    case 2:
        FCFS(temp);
        break;
    default:
        goto back;
    }
    return 0;
}
