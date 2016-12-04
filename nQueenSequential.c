/*include when running vs
#include "stdafx.h"
#include<iostream> 
*/
#include <stdio.h> 
#include <time.h> 

#define TRUE 1
#define FALSE 0
#define N 8

int totalSolutions = 0;

int noConflicts(int q[], int n);
void queens(int q[], int n);

int main(void) {
   clock_t start, finish, time_in_seconds;

   int i;
   int board[N];

   start = clock();
   queens(board, 0);
   finish = clock();
   unsigned long millis = (finish - start) * 1000 / CLOCKS_PER_SEC;
   printf("\nTotal Number of Solutions: %d\nRun Time: %lu\n\n", totalSolutions, millis);
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
