#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


#define N 100
#define RANDOM_RANGE 100000
#define NTHREAD 10
#define VECTOR_LENGTH_PER_THREAD (N/NTHREAD)

static int matrice_a[N][N];
static int matrice_b[N][N];
static int matrice_c[N][N];
static pthread_mutex_t mutex_matrice_mul;

static void init(void)
{

        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        matrice_a[i][j] = matrice_b[i][j] = random() % RANDOM_RANGE;
                }
        }
}

static void *process(void *arg)
{
        uintptr_t offset;
        long i, start, end, k, j;
        long sum;

        offset = (uintptr_t) arg;
        start = offset * VECTOR_LENGTH_PER_THREAD;
        end = start + VECTOR_LENGTH_PER_THREAD;

        for (i = start; i < end; i++) {
                for (j = 0; j < N; j++) {
                        sum = 0;
                        for (k = 0; k < N; k++) {
                                sum += matrice_a[i][k] * matrice_b[k][j];
                        }
                        pthread_mutex_lock(&mutex_matrice_mul);
                        matrice_c[i][j] = sum;
                        pthread_mutex_unlock(&mutex_matrice_mul);
                }
        }

        pthread_exit(NULL);
}

static void print_matrice(void)
{
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        printf("%d  ", matrice_c[i][j]);
                }
                printf("\n");
        }
}


int main(void)
{
        uintptr_t i;

        pthread_t threads[NTHREAD];
        init();
        pthread_mutex_init(&mutex_matrice_mul, NULL);

        for (i = 0; i < NTHREAD; i++)
                pthread_create(&threads[i], NULL, process, (void *) i);

        for (i = 0; i < NTHREAD; i++)
                pthread_join(threads[i], NULL);

        print_matrice();
        pthread_mutex_destroy(&mutex_matrice_mul);
        exit(EXIT_SUCCESS);
}
