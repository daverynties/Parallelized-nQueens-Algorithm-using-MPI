//#include "stdafx.h"
//#include <iostream>
#include <stdio.h> 
#include <time.h>

#define TRUE 1
#define FALSE 0
#define N 13

int totalSolutions = 0;

int noConflicts(int q[], int n);
void queens(int q[], int n);
void staticQueensMPI(int q[], int n);

int main(void) {
   clock_t start, finish, time_in_seconds;

   int i;
   int board[N];

   start = clock();
   staticQueensMPI(board, 1);
   finish = clock();
   unsigned long millis = (finish - start) * 1000 / CLOCKS_PER_SEC;
   printf("count: %d\ntime: %lu\n\n", totalSolutions, millis);

   //system("pause");
   return 0;
}

void staticQueensMPI(int board[], int currentRow) {

   int i;
   if (currentRow == N) {
      totalSolutions++;
   } else {
      board[0] = 8; //set static for parallelization
      for (i = 0; i < N; i++) {
         board[currentRow] = i;
         if (noConflicts(board, currentRow))
            staticQueensMPI(board, currentRow + 1);
      }
   }
}

void queens(int board[], int currentRow) {

   int i;
   if (currentRow == N) {
      totalSolutions++;
   } else {
      for (i = 0; i < N; i++) {
         board[currentRow] = i;
         if (noConflicts(board, currentRow))
            queens(board, currentRow + 1);
      }
   }
}

int noConflicts(int board[], int currentRow) {

   int i;
   for (i = 0; i < currentRow; i++) {
      if (board[i] == board[currentRow])
         return FALSE; // same column
      if (abs(board[i] - board[currentRow]) == (currentRow - i))
         return FALSE; // same diagonal
   }
   return TRUE;
}
