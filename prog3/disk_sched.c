#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void generateRequests()
{
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < 1000; i++)
    {
        requests[i] = rand() % CYLINDERS;
    }
}

int main(int argc, char** argv)
{

}
