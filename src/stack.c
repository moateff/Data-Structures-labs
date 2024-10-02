#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node *next;
};

struct stack{
    struct node *top;
    int size;
};

void InitializeStack(struct stack* pstack){
    pstack->top = NULL;
    pstack->size = 0;
}

int isEmpty (struct stack* pstack){
    return pstack->top==NULL;
}

void push (struct stack* pstack ,int x){
    struct node* pnewnode = malloc(sizeof(struct node));
    pnewnode->data = x;
    pnewnode->next = pstack->top;
    pstack->top = pnewnode;
    pstack->size++;
}

void pop (struct stack* pstack ,int* x){
    struct node* current;
    *x = pstack->top->data;
    current = pstack->top;
    pstack->top = pstack->top->next;
    free(current);
    pstack->size--;
}

void peek (struct stack* pstack ,int* x){
    *x = pstack->top->data;
}

void StgToStack(char stg[50], struct stack* pstackA){
    int x, i = 0;
    int num = 0, sign = 1;
    if(!(strcmp(stg,"[]\n")))
        return;
    else {
        struct stack temp;
        InitializeStack(&temp);
        while (stg[i] != '\n'){
            if ((stg[i] == ' ')||(stg[i] == '[')){
                i++;
                continue;
            }
            else if (stg[i] == '-')
                sign = -1;
            else if ((stg[i] == ',')||(stg[i] == ']')){
                x = sign * num;
                push(&temp,x);
                sign = 1;
                num = 0;
            }
            else
                num = num * 10 + (stg[i] - '0');
            i++;
        }
        while(!(isEmpty(&temp))){
            pop(&temp, &x);
            push(pstackA, x);
        }
    }
}

void print(struct stack* pstack){
    if(isEmpty(pstack))
        printf("[]");
    else{
        struct node* current;
        current = pstack->top;
        printf("[");
        while(current != NULL){
            if(current->next == NULL)
                printf("%d",current->data);
            else
                printf("%d, ",current->data);
            current = current->next;
        }
        printf("]");
    }
}

int size (struct stack* pstack){
    return pstack->size;
}

int main(){
    struct stack stackA;
    char stg[100];
    char operation[20];
    int x;
    fgets(stg,100,stdin);
    InitializeStack(&stackA);
    StgToStack(stg,&stackA);
    while (true){    
        scanf("%s",operation);
        if(!(strcmp(operation,"print"))){
            print(&stackA);
        }
        else if(!(strcmp(operation,"push"))){
            scanf("%d",&x);
            push(&stackA,x);
            print(&stackA);
        }
        else if(!(strcmp(operation,"peek"))){
            if (isEmpty(&stackA))
                printf("Error");
            else{
                peek(&stackA,&x);
                printf("%d",x);
            }
        }
        else if(!(strcmp(operation,"pop"))){
            if (isEmpty(&stackA))
                printf("Error");
            else{
                pop(&stackA,&x);
                print(&stackA);
            }
        }
        else if(!(strcmp(operation,"isEmpty"))){
            if(isEmpty(&stackA))
                printf("True");
            else
                printf("False");
        }
        else if(!(strcmp(operation,"size"))){
            printf("%d",size(&stackA));
        }
        else
            printf("Error");
        printf("\n");
    }
    return 0;
}