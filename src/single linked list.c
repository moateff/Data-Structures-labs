#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};
struct list{
    struct node *head;
    int size;
};

void add (struct list *List ,int x){
    struct node *newnode;
    newnode = malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;
    if(List->head == NULL){
        List->head = newnode;
    }
    else{
        struct node *current ;
        current = List->head;
        while(current->next != NULL)
            current = current->next;
        current->next = newnode;
    }
    List->size++;
}
void StgToList(char stg[100], struct list* List){
    int x, i = 0;
    int num = 0, sign = 1;
    if(!(strcmp(stg,"[]\n")))
        return ;
    else {
        while (stg[i] != '\n'){
            if ((stg[i] == ' ')||(stg[i] == '[')){
                i++;
                continue;
            }
            else if (stg[i] == '-')
                sign = -1;
            else if ((stg[i] == ',')||(stg[i] == ']')){
                x = sign * num;
                add(List,x);
                sign = 1;
                num = 0;
            }
            else
                num = num * 10 + (stg[i] - '0');
            i++;
        }
    }
}
void print(struct list* List){
    if(isEmpty(List))
        printf("[]");
    else{
        struct node *current;
        current = List->head;
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

int size (struct list *List){
    return (List->size);
}

void addToIndex (struct list *List ,int index,int x){
    if((index > List->size)||(index < 0)){
        printf("Error");
        exit(0);
    }
    else if(index==0 && List->size == 0){
        add(List, x);
        List->size++;
    }
    else{
        int i;
        struct node *current, *newnode;
        newnode = malloc(sizeof(struct node));
        newnode->data = x;
        if(index==0){
            newnode->next = List->head;
            List->head = newnode;
        }
        else{
            current = List->head;
            for(i = 0 ; i < index-1 ; i++)
                current = current->next;
            newnode->next = current->next;
            current->next = newnode;
        }
        List->size++;
    }
}
int get(struct list *List ,int index){
    if((index >= List->size)||(index < 0)){
        printf("Error");
        exit(0);
    }
    else{
        int i;
        struct node *current;
        current = List->head;
        for(i = 1; i <= index ; i++)
            current = current->next;
        return current->data;
    }
}
int isEmpty (struct list *List){
    return(List->size==0);
}
void clear(struct list* List){
    if(isEmpty(List)){
        return;
    }
    else{
        struct node *current, *temp;
        current = List->head;
        while(current->next != NULL){
          temp = current;
          current = current->next;
          free(temp);
        }
    List->head = NULL;
    List->size = 0;
    }
}
void removedata(struct list* List,int index){
    if((index >= List->size)||(index < 0))
        printf("Error");
    else{
        struct node *current, *temp ;
        int i;
        current = List->head;
        if(index == 0){
            temp = current->next;
            List->head = temp;
            free(current);
        }
        else{
            for(i = 0; i < index-1 ; i++)
                current = current->next;
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        print(List);
        List->size--;
    }
}
void sublist(struct list* List,int start,int end){
    if(start>end ){
        printf("Error");
        exit(0);
    }
    else if ((start >= List->size)||(start < 0)||(end>=List->size)||(end < 0)){
        printf("Error");
        exit(0);
    }
    else{
        struct list Listtemp;
        Listtemp.head = NULL;
        Listtemp.size = 0;
        int i;
        struct node *current ;
        current = List->head;
        for(i = 0; i < List->size ; i++){
            if(i>=start && i<=end){
                add(&Listtemp,current->data);
            }
            current = current->next;
        }
        print(&Listtemp);
    }
}
int contains(struct list* List,int x){
    struct node *current;
    current = List->head;
    while(current != NULL){
        if(current->data == x)
            return 1;
        current = current->next;
    }
    return 0;
}
void set(struct list* List,int index,int x){
    if((index >= List->size)||(index < 0)){
        printf("Error");
        exit(0);
    }
    else{
        int i;
        struct node *current ;
        current = List->head;
        for(i = 0; i < index ; i++)
            current = current->next;
        current->data = x;
    }
}
int main(){
    struct list List;
    List.head = NULL;
    List.size = 0;
    char stg[100];
    char operation[15];
    fgets(stg,100,stdin);
    scanf("%s",operation);
    StgToList(stg,&List);
    if(!(strcmp(operation,"print"))){
        print(&List);
    }
    else if(!(strcmp(operation,"add"))){
        int x;
        scanf("%d",&x);
        add(&List,x);
        print(&List);
    }
    else if(!(strcmp(operation,"addToIndex"))){
        int index;
        int x;
        scanf("%d",&index);
        scanf("%d",&x);
        addToIndex(&List,index,x);
        print(&List);
    }
    else if(!(strcmp(operation,"get"))){
        int index;
        scanf("%d",&index);
        printf("%d",get(&List,index));
    }
    else if(!(strcmp(operation,"set"))){
        int index;
        int x;
        scanf("%d",&index);
        scanf("%d",&x);
        set(&List,index,x);
        print(&List);
    }
    else if(!(strcmp(operation,"clear"))){
        clear(&List);
        print(&List);
    }
    else if(!(strcmp(operation,"size"))){
        printf("%d",size(&List));
    }
    else if(!(strcmp(operation,"isEmpty"))){
        if(isEmpty(&List))
            printf("True");
        else
            printf("False");
    }
    else if(!(strcmp(operation,"remove"))){
        int index;
        scanf("%d",&index);
        removedata(&List,index);
    }
    else if(!(strcmp(operation,"sublist"))){
        int start, end;
        scanf("%d",&start);
        scanf("%d",&end);
        sublist(&List,start,end);
    }
    else if(!(strcmp(operation,"contains"))){
        int x;
        scanf("%d",&x);
        if(contains(&List,x))
            printf("True");
        else
            printf("False");
    }
    else
        printf("Error");
    return 0;
}
