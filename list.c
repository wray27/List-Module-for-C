#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct node{
 struct node *next;
 struct node *prev;
 char item[];
};
typedef struct node node;

struct list{
  node *currentnodeptr;
  node *lastnodeptr;
  node *firstnodeptr;
  int itemsize;
};
list *newList(int b){

  list *l;
  node *x;

  x = malloc(sizeof(node) + b);
  l = malloc(sizeof(list));
  //memset(x,'\0',b);


  l->firstnodeptr = x;
  l->currentnodeptr = x;
  x->prev = NULL;

  l->lastnodeptr = NULL;
  x->next = l->lastnodeptr;

  l->itemsize = b;

  return l;

}
void start(list *l){
  l->currentnodeptr = l->firstnodeptr;
}
void end(list *l){
  l->currentnodeptr = l->lastnodeptr;
}
bool atStart(list *l){
  if (  l->currentnodeptr==l->firstnodeptr){
    return true;
  }
  else{
    return false;
  }
}
bool atEnd(list *l){
  if (  l->currentnodeptr==l->lastnodeptr){
    return true;
  }
  else{
    return false;
  }
}
void forward(list *l){
  if(l->currentnodeptr != l->lastnodeptr){
    l->currentnodeptr = l->currentnodeptr->next;
  }
  else{
    printf("You can not go forward you are at the last item in the list");
  }

}
void backward(list *l){
  if(l->currentnodeptr != l->firstnodeptr){
    l->currentnodeptr = l->currentnodeptr->prev;
  }
  else{
    printf("You can not go backward you are at the first item in the list");
  }
}

void insertBefore(list *l, void *p){
  node *newnode;
  char *newitem;
  //stores the new item with in the new node
  newitem = malloc(sizeof(struct node) + l->itemsize);
  newitem = p;
  newnode = malloc(sizeof(struct node) + l->itemsize);

  memcpy(newnode->item,newitem,l->itemsize);



  //adjusts the pointers to be in the right place
  node *temp;
  temp = l->currentnodeptr->prev;

  l->currentnodeptr->prev->prev->next = newnode;
  l->currentnodeptr->prev = newnode;
  newnode->next = l->currentnodeptr;
  newnode->prev = temp;


  //l->currentnodeptr = newnode;

}
void insertAfter(list *l, void *p){
  node *newnode;
  char *newitem;

  //stores the new item with in the new node
  newitem = malloc(sizeof(struct node) + l->itemsize);
  newitem = p;
  newnode = malloc(sizeof(struct node) + l->itemsize);
  memcpy(newnode->item,newitem,l->itemsize);



  //adjusts the pointers to be in the right place

  node *tempnode;
  tempnode = l->currentnodeptr->next;

  l->currentnodeptr->next = newnode;
  if (l->lastnodeptr == NULL){
      l->lastnodeptr = newnode;
      newnode->next = NULL;
  }
  else{
    tempnode->prev = newnode;
    newnode->next = tempnode;
  }

  newnode->prev = l->currentnodeptr;





}
void getBefore(list *l, void *p){
  if( atStart(l) == true){
    exit(1);
  }
  else{
    memcpy(p,l->currentnodeptr->prev->item,l->itemsize);
  }
}
void getAfter(list *l, void *p){
  if( atEnd(l) == true){
    exit(1);
  }
  else{
    memcpy(p,l->currentnodeptr->next->item,l->itemsize);
  }

}
void setBefore(list *l, void *p){
  if( atStart(l) == true){
    exit(1);
  }
  else{
    memcpy(l->currentnodeptr->prev->item,p,l->itemsize);
  }
}
void setAfter(list *l, void *p){
  if( atEnd(l) == true){
    exit(1);
  }
  else{
    memcpy(l->currentnodeptr->next->item,p,l->itemsize);
  }

}
void deleteBefore(list *l){
  if( atStart(l) == true){
    printf("error\n");
    exit(1);
  }
  node *tempnode;
  tempnode = l->currentnodeptr->prev->prev;
  l->currentnodeptr->prev = tempnode;
  tempnode->next = l->currentnodeptr;




}
void deleteAfter(list *l){
  if( atEnd(l) == true){
    printf("error\n");
    exit(1);
  }
  node *tempnode;
  tempnode = l->currentnodeptr->next->next;
  l->currentnodeptr->next = tempnode;
  tempnode->prev = l->currentnodeptr;

}

enum type { CHAR, INT, BOOL };
int eq(enum type t, int x, int y) {
    static int n = 0;
    n++;
    if (x != y) {
        if (t==CHAR) fprintf(stderr, "Test %d gives %c not %c\n", n, x, y);
        if (t==INT) fprintf(stderr, "Test %d gives %d not %d\n", n, x, y);
        if (t==BOOL && x) fprintf(stderr, "Test %d gives true not false\n", n);
        if (t==BOOL && y) fprintf(stderr, "Test %d gives false not true\n", n);
        exit(1);
    }
    return n;
}

// More specific versions of the eq function
int eqc(char x, char y) { return eq(CHAR, x, y); }
int eqi(int x, int y) { return eq(INT, x, y); }
int eqb(bool x, bool y) { return eq(BOOL, x, y); }



int testLists(){
   //creates a doubly linked list where a node can contain a payload of two bytes

   list *l;
   l = malloc(sizeof(list));
   l = newList(1);
   void *x,*y,*z,*w,*item;
   char letters[8];
   char* temp;
   letters[3]='c';
   letters[0]='a';
   letters[1]='b';
   letters[2]='d';
   letters[4]= 'y';
   letters[5]= 'x';
   item = malloc( sizeof(char));
   temp = malloc(sizeof(char));
   x = &letters[2];
   y= &letters[1];
   z= &letters[0];
   w= &letters[3];
   insertAfter(l,x);
   insertAfter(l,y);
   insertAfter(l,z);

 //test1 to see if an item is at the start of a list
   eqb(atStart(l),true);
 //test2 to see if an item is at the end of a list
   end(l);
   eqb(atEnd(l),true);
 //test3 to see if the current pointer moves forwards correctly
   start(l);
   forward(l);
   forward(l);
   eqc(*l->currentnodeptr->item,'b');
 //test4 to see if the current pointer moves backwards correctly
   backward(l);
   eqc(*l->currentnodeptr->item,'a');
 //test5 to see if the insertbefore function works correctly
   forward(l);
   forward(l);
   insertBefore(l,w);
   backward(l);
   eqc(*l->currentnodeptr->item,'c');
 //test6 to see if the insertbefore function works correctly
   backward(l);
   item = &letters[4];
   insertBefore(l,item);

   eqc(*l->currentnodeptr->prev->item,'y');
  //test7 to see if the getbefore function works correctly

   getBefore(l,item);
   temp = item;
   eqc(*temp,'y');
  //test8 to see if the getafter function works correctly
   getAfter(l,item);
   temp = item;
   eqc(*temp,'d');
   //test9 to see if the setbefore function works correctly
   temp = &letters[1];
   setBefore(l,temp);

   eqc(*temp,*l->currentnodeptr->prev->item);
   //test10 to see if the setafter function works correctly
   temp = &letters[4];
   setAfter(l,temp);
   eqc(*temp,*l->currentnodeptr->next->item);
   //test11 to see if the deleteBefore function works correctly
    char *temp2;
    temp2 = malloc(sizeof(char));
    temp2 = l->currentnodeptr->prev->item;
    temp = &letters[3];
    insertBefore(l,temp);
    deleteBefore(l);

    eqc(*temp2,*l->currentnodeptr->prev->item);
   //test12 to see if the deleteAfter function works correctly

   temp2 = l->currentnodeptr->next->item;
   temp = &letters[3];
   insertAfter(l,temp);
   deleteAfter(l);
   eqc(*temp2,*l->currentnodeptr->next->item);



   printf("Tests Passed %d!\n",eqi(0, 0) - 1);
   return 0;
}
