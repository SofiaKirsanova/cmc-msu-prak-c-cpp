#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define N 5 // количество философов
#define THINKING 0 // думает
#define HUNGRY 1 // голодный
#define EATING 2 // кушает
#define LEFT (i - 1) % N // номер левого соседа для i-го философа
#define RIGHT (i + 1) % N // номер правого соседа для i-го философа
struct sembuf up_mutex = {0, 1, 0};
struct sembuf down_mutex = {0, -1, 0};

int mutex;
int semid;
int state[N]; // массив состояний каждого из философов, заполненный нулями


void Think(int);
void Take_Forks(int);
void Eat(int i);
void Put_Forks(int);
void Test(int);

void down (int i)
{
    struct sembuf P = {i, -1, 0};
    semop(semid, &P, 1);
}


void up (int i)
{
    struct sembuf V = {i, 1, 0};
    semop(semid, &V, 1);
}

void Philosopher(int i)
{
    signal(SIGINT,SIG_DFL);
    while(1)
    {
        Think(i); // меняем статус текущего философа на статус думает
        Take_Forks(i); // берем обе вилки
        Eat(i); // кушает
        Put_Forks(i);
    }
}

void Think(int i)
{
    state[i] = THINKING;
    sleep(1);
    printf("Number : %d and State : %d\n", i, state[i]);

}

void Eat(int i)
{
    sleep(1);
    printf("Number : %d and State : %d\n", i, state[i]);
}

void Take_Forks(int i)
{
//входим в критическую секцию
    semop(mutex, &down_mutex, 1);
    state[i] = HUNGRY;
    printf("Number : %d and State : %d\n", i, state[i]);
    Test(i);
    printf("Number : %d and State : %d\n", i, state[i]);
//выходим из критической секции
    semop(mutex, &up_mutex, 1);// производимая операция
    down(i); // опускаем семафор, если философ поел
}

void Put_Forks(int i)
{
//входим в критическую секцию
    semop(mutex, &down_mutex, 1);
    Test(LEFT); //делаем проверку на то свободная ли левая вилка или нет
    Test(RIGHT); ////делаем проверку на то свободная ли правая вилка или нет
//выходим из критической секции
    semop(mutex, &up_mutex, 1);// производимая операция
}

void Test(int i) // проверяем занята ли вилка соседом
{
    if((state[i] == HUNGRY) && (state[LEFT] != EATING) && (state[RIGHT] != EATING))
    {
        state[i] = EATING;
        up(i);
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT,SIG_IGN);
    int key, i;
    key = ftok(argv[0], 0);
    semid = semget(key, N, IPC_CREAT | 0666);
    if(semid == -1)
    {
        perror("ERROR\n"); //на случай ошибки
        exit(1);
    }
    for(i = 0; i < N; i++)
    {
        semctl(semid, i, SETVAL, (int) 0);
    }
    key = ftok(argv[0], 1);
    mutex = semget(key, 1, IPC_CREAT | 0666);
    semctl(mutex, 0, SETVAL, (int) 1);
    for(i = 0; i < N; i++)
    {
        if(fork() == 0)
        {
            Philosopher(i);
        }
    }
    for(i = 0; i < N; i++)
    {
        wait(NULL);
    }
    semctl(mutex, 0, IPC_RMID, (int) 0);
    semctl(semid, 0, IPC_RMID, (int) 0);
    printf("\n");
    return 0;
}
