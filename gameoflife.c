#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define BOARD_WIDTH	79
#define BOARD_HEIGHT	24

struct barrier {
	int count;
	sem_t mutex;
	sem_t turnstile;
	sem_t turnstile2;
};

struct barrier obj;

void init(struct barrier* obj)
{
	obj->count=0;
	sem_init(&obj->mutex, 0, 1);
	sem_init(&obj->turnstile, 0, 0);
	sem_init(&obj->turnstile2, 0, 0);
}

void wait1(struct barrier* obj){
	sem_wait(&obj->mutex);
	obj->count++;
	if(obj->count==BOARD_HEIGHT){
		for(int i=0; i<BOARD_HEIGHT; i++)
			sem_post(&obj->turnstile);
	}
	sem_post(&obj->mutex);
	sem_wait(&obj->turnstile);
}

void wait2(struct barrier* obj){
	sem_wait(&obj->mutex);
	obj->count--;
	if(obj->count==0){
		for(int i=0; i<BOARD_HEIGHT; i++)
			sem_post(&obj->turnstile2);
	}
	sem_post(&obj->mutex);
	sem_wait(&obj->turnstile2);
}

void initialize_board (int** board) {
	int	i, j; 
    srand(time(NULL)); 
	for (i=0; i<BOARD_WIDTH; i++){ 
		for (j=0; j<BOARD_HEIGHT; j++){
			board[i][j] = rand() % 2;
		}
	}
}

int xadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_WIDTH;
	while (i >= BOARD_WIDTH) i -= BOARD_WIDTH;
	return i;
}

int yadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_HEIGHT;
	while (i >= BOARD_HEIGHT) i -= BOARD_HEIGHT;
	return i;
}

int adjacent_to (int** board, int i, int j) {
	int	k, l, count;
	count = 0;
	for (k=-1; k<=1; k++) for (l=-1; l<=1; l++)
		if (k || l)
			if (board[xadd(i,k)][yadd(j,l)]) count++;
	return count;
}

struct NB{
	int** board;
	int thread;
};

void* play (void* param) {
	struct NB tempBoard = *(struct NB*)param;
	int	i, j, a, newboard[BOARD_WIDTH][BOARD_HEIGHT];
	i = tempBoard.thread;
	for (j=0; j<BOARD_WIDTH; j++) {
		a = adjacent_to (tempBoard.board, j, i);
		if (a == 2) newboard[j][i] = tempBoard.board[j][i];
		if (a == 3) newboard[j][i] = 1;
		if (a < 2) newboard[j][i] = 0;
		if (a > 3) newboard[j][i] = 0;
	}
	wait1(&obj);
	for (j=0; j<BOARD_WIDTH; j++) 
	{
		tempBoard.board[j][i] = newboard[j][i];
	}
	wait2(&obj);
	pthread_exit(0);
}

void print (int** board) {
	int	i, j;
	for (j=0; j<BOARD_HEIGHT; j++) {
		for (i=0; i<BOARD_WIDTH; i++) {
			printf ("%c", board[i][j] ? 'x' : ' ');
		}
		printf ("\n");
	}
}

int main () {
	int**board, i, j;
	pthread_t tid[BOARD_HEIGHT];
	struct NB nb[BOARD_HEIGHT];
		
	board = malloc(sizeof(int*)*BOARD_WIDTH);
	for(int i=0; i<BOARD_WIDTH; i++)
		board[i]=malloc(sizeof(int)*BOARD_HEIGHT);
		
	initialize_board (board);
	init(&obj);
	
	
	for (i=0; i<100; i++) 
	{
		for(j = 0; j<BOARD_HEIGHT; j++)
		{
			nb[j].board = board;
			nb[j].thread = j;
			pthread_create(&tid[j], NULL, &play, &nb[j]);
		}
		
		for(j=0; j<BOARD_HEIGHT; j++)
		{
			pthread_join(tid[j], NULL);
		}
		
		print (board);
		sleep(2);
		puts ("\033[H\033[J");
	}
}

