#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *pre;
};
struct list{
    struct node *head;
    struct node *tail;
    int size;
};
void add (struct list *List ,int x){
     struct node *newnode;
    newnode = malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;
    if(List->head == NULL){
        List->head = newnode;
        List->tail= newnode;
    }
    else{
        List->tail->next=newnode;
        newnode->pre=List->tail;
        List->tail=newnode;
    }
    List->size++;
}

//-------------------------------------------------------------------------

void StgToList(char stg[100], struct list* List){
    int x;
    int i = 1, j = 0;
    int num = 0, sign = 1;
    while (stg[i] != ']'){
        if (stg[i] == ' '){
            i++;
            continue;}
        else if (stg[i] == '-')
            sign = -1;
        else if (stg[i] == ','){
            x = sign * num;
            add(List,x);
            sign = 1;
            num = 0;
            j++;}
        else
            num = num * 10 + (stg[i] - '0');
        i++;
    }
    x = sign * num;
    add(List,x);
}

void print(struct list* List){
    if(List->head == NULL)
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

//-----------------------------------------------------------------

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
        newnode->data =x;
        if(index==0){
            newnode->next = List->head;
            newnode->pre=NULL;
            List->head = newnode;
        }
        else if(index==List->size)
        {
        newnode->pre=List->tail;
        newnode->next=NULL;
        List->tail->next=newnode;
        List->tail=newnode;
        }
        
        else{
            current = List->head;
            for(i = 0 ; i < index-1 ; i++)
            {
              current = current->next;  
            }
                
            newnode->next = current->next;
            newnode->pre=current;
            current->next = newnode;
        }
        List->size++;
    
    }
}

//----------------------------------------------------------------


int get(struct list *List ,int index){
    if((index >= List->size)||(index < 0)){
        printf("Error");
        exit(0);
    }
    else if(index==List->size-1)
    {
        struct node *current;
        current = List->tail;
        return current->data;
    }
    else{
        int i;
        struct node *current;
        current = List->head;
        for(i = 0; i <= index-1 ; i++)
            current = current->next;
        return current->data;
    }
}

//------------------------------------------------------------------


int isEmpty (struct list *List){
    return(List->size==0);
}

//-------------------------------------------------------------------

void clear(struct list* List){
    if(isEmpty(List))
    {
        return;
    }
    struct node *current, *temp;
    current = List->head;
    while(current->next != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    List->head = NULL;
    List->tail = NULL;
    List->size = 0;
}

//----------------------------------------------------------------------


void removedata(struct list* List,int index){
    if((index >= List->size)||(index < 0))
    {
        printf("Error");
    }
        
    else{
        struct node *current, *temp ;
        int i;
        current = List->head;
        if(index == 0){
            temp = current->next;
            List->head = temp;
            temp->pre=NULL;
            current->next=NULL;
        }
        else if(index==List->size-1)
        {
            struct node *endnode;
            endnode=List->tail;
            endnode=endnode->pre;
            endnode->next=NULL;
        }
        
        else{
            struct node  *temp2 ;
            for(i = 0; i < index-1 ; i++)
            current = current->next;
            temp = current->next;
            temp2=temp->next;
            temp2->pre=current;
            current->next = current->next->next;
            free(temp);
        }
        print(List);
        List->size--;
    }
}

//-------------------------------------------------------------------

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
        Listtemp.tail =NULL;
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

//---------------------------------------------------------------------

int contains(struct list* List,int x){
    struct node *current;
    current = List->head;
    if(List->tail->data==x)
    {
        return 1;
    }
    else{
        while(current->next != NULL){
            if(current->data == x)
                return 1;
            current = current->next;
        }
    }
    return 0;
}


//----------------------------------------------------------------

void set(struct list* List,int index,int x){
    if((index >= List->size)||(index < 0)){
        printf("Error");
        exit(0);
    }
    else if(index==List->size-1)
    {
        struct node *current ;
        current = List->tail;
        current->data = x;
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
    List.tail=NULL;
    List.size = 0;
    char stg[100];
    char operation[15];
    scanf("%[^\n]",stg);
    scanf("%*[\n]");
    scanf("%s",operation);
    if(stg[1]!=']'){
        StgToList(stg,&List);
    }
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
