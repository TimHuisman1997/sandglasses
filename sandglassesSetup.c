/* sandglassSetup.c, 24 February 2018
 * 
 * This is the setup for the practical assignment Sandglasses.
 * As such, it is an incomplete program: it does compile, but it does not work properly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* First the type definitions.
 */

typedef struct State { /* a state contains a time and the states of the two sandglasses */
  int time;
  int sg1, sg2;
} State;

typedef struct ListNode *List;  /* List is the type of lists of states */

struct ListNode {
  State item;
  List next;
};

typedef struct Queue { /* a queue is a list and a pointer to the last node */
  List list;
  List lastNode;
} Queue;

/* We use the functions on lists as defined in 1.3 of the lecture notes.
 */

List newEmptyList() {
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

/* We define some functions on queues, based on the definitions in 1.3.1 of the
 * lecture notes. Integers are replaced by states, and enqueue has output type void here.
 */

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
}

/* The function action generates a new state from an existing state.
 */

State action(State s /* , ... */ ) {
  /* ... */
}

/* The function timeable checks whether a given time can be determined
 * exactly by two sandglasses with given capacities.
 */

int timeable(int cap1, int cap2, int goalTime) { 
  /* ... */
}

/* main performs a dialogue with the user. The user is repeatedly asked to provide three numbers: 
 * the (positive) capacities of the sandglasses and the goal time (>= 0).
 * The program indicates whether the goal time can be determined exactly. 
 * The dialogue is ended by the input '0'.
 */

int main(int argc, char *argv[]){
  int cap1, cap2, goalTime; 
  printf("give the capacities and the goal time: ");
  scanf("%d",&cap1);
  while ( cap1 > 0 ) {
    scanf("%d",&cap2);
    assert( cap2 > 0 );
    scanf("%d",&goalTime);
    assert( goalTime >= 0 );
    if ( timeable(cap1,cap2,goalTime) ) {
      printf("%d and %d can time %d\n", cap1, cap2, goalTime);
    } else {
      printf("%d and %d cannot time %d\n", cap1, cap2, goalTime);
    }
    printf("give the capacities and the goal time: ");
    scanf("%d",&cap1);
  }  
  printf("good bye\n");
  return 0;
}
