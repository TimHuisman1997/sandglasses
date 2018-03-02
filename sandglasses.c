#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "queues.h"

int timestep(int bottom, int cap){
	if(cap==bottom){
		return cap;
	} else {
		return (cap-bottom);
	}
}

// returns 1 if time <= goalTime, else return 0
int checkGoal(int time, int goalTime){
	if(time<=goalTime){
		return 1;
	}
	//printf("x");
	return 0;
}


void turnA(State s, int cap1, int cap2, Queue *qp, int goalTime){
	int nextTimestep = timestep(s.sg1, cap1);
	if((cap2-s.sg2<nextTimestep)&&(cap2-s.sg2!=0)){
		nextTimestep=cap2-s.sg2;
		s.sg1=nextTimestep;
	} else {
		s.sg2+=nextTimestep;
	}
	s.time +=nextTimestep;	
	if(checkGoal(s.time, goalTime)){
		enqueue(s, qp);
	}
}

void turnB(State s, int cap1, int cap2, Queue *qp, int goalTime){
	int nextTimestep = timestep(s.sg2, cap2);
	s.time+=nextTimestep;
	s.sg1 +=nextTimestep;
	if((cap1-s.sg1)<cap1){
		s.sg1=cap1;
	}	
	if(checkGoal(s.time, goalTime)){
		enqueue(s, qp);
	}
}



void turnBoth(){

}

void doNothing(){
	
}


State action(State s, int cap1, int cap2, int goalTime) {
  Queue q = newEmptyQueue();
  do{
	printf("%d %d %d\n", s.time, s.sg1, s.sg2);
	turnA(s, cap1, cap2, &q, goalTime);
    turnB(s, cap1, cap2, &q, goalTime);
	//turnBoth();
	//if(){
		//doNothing();
	//}
	if(isEmptyQueue(q)) return s;
	s = dequeue(&q);	
	} while (s.time!=goalTime);
	//printf("%d ", s.time);
	return s;
}

int timeable(int cap1, int cap2, int goalTime) { 
  State s;
  s.time=0;
  s.sg1=cap1;
  s.sg2=cap2;
  
  s = action(s, cap1, cap2, goalTime);
  
  // if goaltime can be timed return 1, else return 0;
  if(s.time==goalTime){
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
