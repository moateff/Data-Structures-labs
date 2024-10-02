#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MaxQueue 100

struct queue{
    int front;
    int rare;
    int size;
    int data[MaxQueue];
};

void InitializeQueue(struct queue *pQueue){
    pQueue->front = 0;
    pQueue->rare = -1;
    pQueue->size = 0;
}

int sizeQueue(struct queue *pQueue){
    return pQueue->size;
}

int isEmptyQueue(struct queue *pQueue){
    return !pQueue->size;
}

int isFullQueue(struct queue *pQueue){
    return (pQueue->size == MaxQueue);
}

void append(struct queue *pQueue , int x){
    pQueue->rare = (pQueue->rare + 1) % MaxQueue;
    pQueue->data[pQueue->rare] = x;
    pQueue->size++;
}

void serve(struct queue *pQueue , int *x){
    *x = pQueue->data[pQueue->front];
    pQueue->front = (pQueue->front + 1) % MaxQueue;
    pQueue->size--;
}

void printQueue(struct queue *pQueue){
    int pos = pQueue->rare;
    int i;
    printf("[");
    for(i=0;i<pQueue->size;i++){
        if(pos == pQueue->front)
            printf("%d",pQueue->data[pos]);
        else
            printf("%d, ",pQueue->data[pos]);
        pos = (pos - 1) % MaxQueue;
    }
    printf("]");
}

int StgToQueue(char stg[200], struct queue *pQueue){
    int x, i, j;
    i = j = 0;
    int num = 0, sign = 1, flag = 0;
    int stgNew [MaxQueue];
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
                stgNew [j] = x;
                j++;
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
    i = j - 1;
    for(i; i >= 0; i--){
        if(isFullQueue(pQueue))
            return 0;
        append(pQueue, stgNew [i]);
    }
    return 1;
}

int main(){
    char stg[200];
    char operation[20];
    int x;
    fgets(stg,200,stdin);
    struct queue queueA;
    InitializeQueue(&queueA);
    if(!StgToQueue(stg,&queueA))
        return 0;
    while(1){
        scanf ("%s", operation);
        if(!(strcmp(operation,"print"))){
            printQueue(&queueA);
        }
        else if(!(strcmp(operation,"append"))){
            scanf("%d",&x);
            if (isFullQueue(&queueA))
                printf("Error");
            else{
                append(&queueA,x);
                printQueue(&queueA);
            }
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
