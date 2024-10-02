#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct stack{
    struct node *top;
    int size;
};

struct queue{
    struct node *front;
    struct node *rare;
    int size;
};

void InitializeStack(struct stack* pStack){
    pStack->top = NULL;
    pStack->size = 0;
}

void InitializeQueue(struct queue *pQueue){
    pQueue->front = NULL;
    pQueue->rare = NULL;
    pQueue->size = 0;
}

void push(struct stack* pStack ,int x){
    struct node* pNewNode = malloc(sizeof(struct node));
    pNewNode ->data = x;
    pNewNode ->next = pStack->top;
    pStack->top = pNewNode ;
    pStack->size++;
}

void pop(struct stack* pStack ,int* x){
    struct node* current;
    *x = pStack->top->data;
    current = pStack->top;
    pStack->top = pStack->top->next;
    free(current);
    pStack->size--;
}

int isEmptyStack(struct stack* pStack){
    return !pStack->top;
}

int sizeQueue(struct queue *pQueue){
    return pQueue->size;
}

int isEmptyQueue(struct queue *pQueue){
    return !pQueue->front;
}

void append(struct queue *pQueue , int x){
    struct node *pNewNode = malloc(sizeof(struct node));
    pNewNode->data = x;
    pNewNode->next = NULL;
    if(!pQueue->rare)
        pQueue->front = pNewNode;
    else
        pQueue->rare->next = pNewNode;
    pQueue->rare = pNewNode;
    pQueue->size++;
}

void serve(struct queue *pQueue , int *x){
    struct node *current = pQueue->front;
    *x = current->data;
    pQueue->front = pQueue->front->next;
    free(current);
    if(!pQueue->front)
        pQueue->rare = NULL;
    pQueue->size--;
}

void printElement (struct node *current){
    if(current){
        printElement(current->next);
        printf("%d, ", current->data);
    }
}

void printQueue(struct queue *pQueue){
    printf("[");
    if(pQueue->front){
        printElement(pQueue->front->next);
        printf("%d", pQueue->front->data);
    }
    printf("]");
}

void StgToQueue(char stg[100], struct queue *pQueue){
    int x, i = 0;
    int num = 0, sign = 1, flag = 0;
    struct stack temp;
    InitializeStack(&temp);
    while (stg[i] != '\0'){
        if ((stg[i] == ' ')||(stg[i] == '[')){
            i++;
            continue;
        }
        if (stg[i] == '-')
            sign = -1;
        else if ((stg[i] == ',')||(stg[i] == ']')){
            if(flag){
                x = sign * num;
                push(&temp, x);
                sign = 1;
                num = 0;
                flag = 0;
            }
        }
        else{
            num = num * 10 + (stg[i] - '0');
            flag = 1;
        }
        i++;
    }
    while(!isEmptyStack(&temp)){
        pop(&temp, &x);
        append(pQueue, x);
    }
}

int main(){
    char stg[100];
    char operation[20];
    int x;
    fgets(stg,100,stdin);
    struct queue queueA;
    InitializeQueue(&queueA);
    StgToQueue(stg, &queueA);
    while(1){
        scanf ("%s", operation);
        if(!(strcmp(operation,"print"))){
            printQueue(&queueA);
        }
        else if(!(strcmp(operation,"append"))){
            scanf("%d",&x);
            append(&queueA,x);
            printQueue(&queueA);
        }
        else if(!(strcmp(operation,"serve"))){
            if (isEmptyQueue(&queueA))
                printf("Error");
            else{
                serve(&queueA,&x);
                printQueue(&queueA);
            }
        }
        else if(!(strcmp(operation,"isEmpty"))){
            if(isEmptyQueue(&queueA))
                printf("True");
            else
                printf("False");
        }
        else if(!(strcmp(operation,"size"))){
            printf("%d",sizeQueue(&queueA));
        }
        else
            printf("Error");
        printf("\n");
    }
    return 0;
}
