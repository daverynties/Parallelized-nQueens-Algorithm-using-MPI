#include <stdio.h> 
#include <time.h>
   //uncomment for visual studio
   //#include<iostream>
#define TRUE 1
#define FALSE 0
#define N 13

int counter = 0;

int placeQueen(int q[], int n);
void queenLogic(int q[], int n);

int main(void) {
   clock_t start, finish, time_in_seconds;

   int i;
   int queen[N];

   start = clock();
   queenLogic(queen, 0);
   finish = clock();
   unsigned long millis = (finish - start) * 1000 / CLOCKS_PER_SEC;
   printf("count: %d\ntime: %lu\n\n", counter, millis);
   //visual studio pause for console viewing upon completion
   //system("pause");
   return 0;
}

void queenLogic(int qu[], int n) {

   int i;
   if (n == N) {
      counter++;
   } else {
      for (i = 0; i < N; i++) {
         qu[n] = i;
         if (placeQueen(qu, n))
            queenLogic(qu, n + 1);
      }
   }
}

int placeQueen(int q[], int n) {

   int i;
   for (i = 0; i < n; i++) {
      if (q[i] == q[n])
         return FALSE; // same column
      if (abs(q[i] - q[n]) == (n - i))
         return FALSE; // same diagonal
   }
   return TRUE;
}
