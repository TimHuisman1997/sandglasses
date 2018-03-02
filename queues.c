#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "queues.h"

Queue newEmptyQueue () {
  Queue q;
  q.list = newEmptyList();
  q.lastNode = NULL;
  return q;
}

int isEmptyQueue (Queue q) {
  return isEmptyList(q.list);
}

void queueEmptyError () {
  printf("queue empty\n");
  exit(0);
}

void enqueue (State s, Queue *qp) {
  if ( isEmptyList(qp->list) ) {
    qp->list = addItem(s,NULL);
    qp->lastNode = qp->list;
  } else {
    (qp->lastNode)->next = addItem(s,NULL);
    qp->lastNode = (qp->lastNode->next);
  }
}

State dequeue(Queue *qp) {
  State s;
  if ( isEmptyQueue(*qp) ) {
    queueEmptyError();
  }
  s = firstItem(qp->list);
  qp->list = removeFirstNode(qp->list);
  if ( isEmptyList(qp->list) )  {
    qp->lastNode = NULL;
  }
  return s;
}

void freeQueue (Queue q) {
	freeList(q.list);
}List newEmptyList() {
  return NULL;
}

int isEmptyList (List li) {
  return ( li==NULL );
}

void listEmptyError() {    
  printf("list empty\n");
  abort();
}

List addItem(State s, List li) {
  List newList = malloc(sizeof(struct ListNode));
  assert(newList!=NULL);
  newList->item = s;
  newList->next = li;
  return newList;
}

State firstItem(List li) {
  if ( li == NULL ) {
    listEmptyError();
  }
  return li->item;
}

List removeFirstNode(List li) {
  List returnList;
  if ( li == NULL ) {
    listEmptyError();
  }
  returnList = li->next;
  free(li);
  return returnList;
}

void freeList(List li) {
  List li1;
  while ( li != NULL ) {
    li1 = li->next;
    free(li);
    li = li1;
  }
  return;
}
