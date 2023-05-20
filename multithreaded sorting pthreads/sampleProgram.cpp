//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 3
//  Due Date: Mon/Sept 30/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

// Create a structure to pass parameters to print_message in pthread_create
struct message{
    char *quote; // character pointer - null terminated character array
    int index;
    int wait;
};
// This is the function that will be called in pthread_create.
// Notice this returns a void pointer
void *print_message(void *ptr )
{
    message *arg = (message *) ptr;
    cout << "-->Entering Thread "<<arg->index<<endl;
    cout << arg->quote<<endl;
    cout << "<--Exiting Thread "<<arg->index<<endl;
    return NULL;
}
char quotes[][10] = {"there", "is", "no","spoon"};
int main()
{
    message argList[4]; // array of arguments to pass to each thread
    for (int i=0; i<4; i++)
    {
        argList[i].quote = quotes[i];
        argList[i].index = i;
        argList[i].wait = rand()%5;
    }

    pthread_t thread0, thread1, thread2, thread3;
    int iret0, iret1, iret2, iret3;
    /* Create independent threads each of which will execute function */
    iret0 = pthread_create( &thread0, NULL, print_message, (void*)&argList[0]);
    iret1 = pthread_create( &thread1, NULL, print_message, (void*)&argList[1]);
    iret2 = pthread_create( &thread2, NULL, print_message, (void*)&argList[2]);
    iret3 = pthread_create( &thread3, NULL, print_message, (void*)&argList[3]);
    // The return value of pthread_create is 0 if successful and non-zero if there is a problem
    
    cout << "Thread 0 returns:"<<iret0<<endl;
    cout << "Thread 1 returns:"<<iret1<<endl;
    cout << "Thread 2 returns:"<<iret2<<endl;
    cout << "Thread 3 returns:"<<iret3<<endl;
    
    /* Wait till threads are complete before main continues. Unless we */
    /* wait we run the risk of executing an exit which will terminate */
    /* the process and all threads before the threads have completed. */

    pthread_join( thread0, NULL);
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    pthread_join( thread3, NULL);

    return 0;
}