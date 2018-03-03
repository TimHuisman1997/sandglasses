#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "queues.c"

int turnSandglass(int cap, int bottom){
    return (cap-bottom)+(cap/bottom)*cap;
}

int topSandglass(int cap, int bottom){
    return cap-bottom;
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
    int sg1Top=turnSandglass(cap1, s.sg1);
    int sg2Top=topSandglass(cap2, s.sg2);

    if((sg1Top>=sg2Top)&&(sg2Top!=0)){
        s.time+= sg2Top;
        s.sg1 += sg2Top;
        s.sg2 = cap2;
    } else {
        s.time+=sg1Top;
        if(sg1Top!=0){
            s.sg2+=sg1Top;
        }
        s.sg1=cap1;
    }

    if(checkGoal(s.time, goalTime)){
        enqueue(s, qp);
    }
}

void turnB(State s, int cap1, int cap2, Queue *qp, int goalTime){
    int sg2Top=turnSandglass(cap2, s.sg2);
    int sg1Top=topSandglass(cap1, s.sg1);

    if((sg2Top>=sg1Top)&&(sg1Top!=0)){
        s.time+= sg1Top;
        s.sg2 += sg1Top;
        s.sg1 = cap1;
    } else {
        s.time+=sg2Top;
        if(sg2Top!=0){
            s.sg1+=sg2Top;
        }
        s.sg1=cap1;
    }

    if(checkGoal(s.time, goalTime)){
        enqueue(s, qp);
    }
}

void turnBoth(State s, int cap1, int cap2, Queue *qp, int goalTime){
    int sg1Top = turnSandglass(cap1, s.sg1);
    int sg2Top = turnSandglass(cap2, s.sg2);

    if(sg1Top>sg2Top){
        s.time += sg2Top;
        s.sg1 += sg2Top;
        s.sg2 = cap2;
    } else {
        s.time += sg1Top;
        s.sg2 += sg1Top;
        s.sg1 = cap1;
    }

    if(checkGoal(s.time, goalTime)){
        enqueue(s, qp);
    }
}

void doNothing(State s, int cap1, int cap2, Queue *qp, int goalTime){
    int sg1Top = topSandglass(cap1, s.sg1);
    int sg2Top = topSandglass(cap2, s.sg2);

    if((sg1Top<sg2Top)&&(sg1Top!=0)){
        s.time += sg1Top;
        s.sg2 += sg1Top;
        s.sg1 = cap1;
    } else if(sg1Top==0){
        s.time+=sg2Top;
        s.sg2=cap2;
    } else if(sg2Top!=0){
        s.time+=sg2Top;
        s.sg1+=sg2Top;
        s.sg2=cap2;
    } else {
        s.time += sg1Top;
        s.sg1 = cap1;
    }

    if(checkGoal(s.time, goalTime)){
        enqueue(s, qp);
    }
}


State action(State s, int cap1, int cap2, int goalTime) {
  Queue q = newEmptyQueue();
  do{
	printf("%d %d %d\n", s.time, s.sg1, s.sg2);
	turnA(s, cap1, cap2, &q, goalTime);
    turnB(s, cap1, cap2, &q, goalTime);
	turnBoth(s, cap1, cap2, &q, goalTime);
	if(cap1!=s.sg1||cap2!=s.sg2){
		doNothing(s, cap1, cap2, &q, goalTime);
	}
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
