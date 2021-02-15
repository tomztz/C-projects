#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
struct listset *result;
result=malloc(sizeof(struct listset));
result->head=NULL;
return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
	struct listnode *p;
	for(p=this->head;p!=NULL;p=p->next){
	if(strcmp(p->str,item)==0){
	return 1;
}
}
	return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
	if(listset_lookup(this,item)==0){
	struct listnode *node;
	node=malloc(sizeof(struct listnode));
	node->str=item;
	node->next=this->head;
	this->head=node;
}
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
	struct listnode *p;
	struct listnode *temp0;
	struct listnode *temp1;

	if(this->head!=NULL){
	if(strcmp(this->head->str,item)==0){
	temp0=this->head;
	this->head=this->head->next;
	free(temp0);
	return;
}
	for(p=this->head;p->next!=NULL;p=p->next){
	if(strcmp(p->next->str,item)==0){
	temp1=p->next;
	p->next=p->next->next;
	free(temp1);
	return;
}

}
}
}

// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
	struct listnode *p;
	for(p=src1->head;p!=NULL;p=p->next){
	 listset_add(dest,p->str);
}
	for(p=src2->head;p!=NULL;p=p->next){
	listset_add(dest,p->str);
}
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
	struct listnode *p,*q;
	for(p=src1->head;p!=NULL;p=p->next){
	for(q=src2->head;q!=NULL;q=q->next){
	if(strcmp(p->str,q->str)==0){
	listset_add(dest,p->str);
}
}
}

}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
	int count=0;
	struct listnode *p;
	for(p=this->head;p!=NULL;p=p->next){
	count++;
}
return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
