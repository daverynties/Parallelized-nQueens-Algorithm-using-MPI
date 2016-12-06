/*include when running vs
#include "stdafx.h"
#include<iostream> 
*/
#include <stdio.h> 
#include <sys/time.h> 

#define TRUE 1
#define FALSE 0
#define N 14

int totalSolutions = 0;

int noConflicts(int q[], int n);
void queens(int q[], int n);
float timedifference_msec(struct timeval start, struct timeval finish);

int main() {
   struct timeval start;
   struct timeval finish;
   float execution_time;

   int i;
   int board[N];

   gettimeofday(&start, 0);
   queens(board, 0);
   gettimeofday(&finish, 0);
   execution_time = timedifference_msec(start, finish);
   printf("\nTotal Number of Solutions: %d\nRun Time: %fms\n\n", totalSolutions, execution_time);
   //uncomment in vs
   //system("pause");
   return 0;
}

void queens(int board[], int current) {

   int i;
   if (current == N) {
      totalSolutions++;
   } else {
      for (i = 0; i < N; i++) {
         board[current] = i;
         if (noConflicts(board, current))
            queens(board, current + 1);
      }
   }
}

int noConflicts(int board[], int current) {

   int i;
   for (i = 0; i < current; i++) {
      if (board[i] == board[current])
         return FALSE; // same column
      if (abs(board[i] - board[current]) == (current - i))
         return FALSE; // same diagonal
   }
   return TRUE;
}

float timedifference_msec(struct timeval start, struct timeval finish)
{
    return (finish.tv_sec - start.tv_sec) * 1000.0f + (finish.tv_usec - start.tv_usec) / 1000.0f;
}
