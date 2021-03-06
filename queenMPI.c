#include <stdio.h> 
#include <time.h>
#include <mpi.h>
#include <unistd.h>

#define MASTER 0
#define TRUE 1
#define FALSE 0
#define N 14

int totalSolutions = 0;

int noConflicts(int q[], int n);
void staticQueensMPI(int q[], int n, int queenValue);

int main(int argc, char * argv[]) {

    double start, finish, total_time;
    int my_rank, source, num_nodes;
    int board[N];
    int i;

    MPI_Init( & argc, & argv);
    MPI_Comm_rank(MPI_COMM_WORLD, & my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, & num_nodes);

    if (my_rank != MASTER) {
        staticQueensMPI(board, 1, my_rank -1);
        MPI_Send( & totalSolutions, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        start = MPI_Wtime();
        for (source = 0; source < num_nodes - 1; source++) {
            int answerFromWorker;
            MPI_Recv( & answerFromWorker, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSolutions += answerFromWorker;
        }
        finish = MPI_Wtime();
        total_time = finish - start;
        printf("\nTotal Solutions: %d\nRun Time: %lf\n", totalSolutions, total_time);
    }

    //system("pause");
    MPI_Finalize();
    return 0;
}

void staticQueensMPI(int board[], int currentRow, int queenValue) {

    int i;
    if (currentRow == N) {
        totalSolutions++;
    } else {
        board[0] = queenValue; //set static for parallelization
        for (i = 0; i < N; i++) {
            board[currentRow] = i;
            if (noConflicts(board, currentRow))
                staticQueensMPI(board, currentRow + 1, queenValue);
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
