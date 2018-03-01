#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queues.h"


State action(State s, int cap1, int cap2 ) {
  List li = newList();
   
}

int timeable(int cap1, int cap2, int goalTime) { 
  State s;
  s.time=goalTime;
  s.sg1=cap1;
  s.sg2=cap2;
  
  
  
  // if goaltime can be timed return 1, else return 0;
  if(){
	  return 1;
  }
  return 0;
}

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
