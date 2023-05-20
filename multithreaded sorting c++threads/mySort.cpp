//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 5
//  Due Date: Mon/Oct 24/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>


struct message{
    int *arr;
    int local_min;
    int local_max;
    int index;
    int wait;
};

void swapValues(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// This quick sort function uses an array
void quicksort(int v[], int lhs, int rhs){    
    // the whole goal of quick sort is to choose a pivot and find where it belongs
    if (lhs < rhs+1){
        //Partition:
            int &thisPivot = v[rhs];
            int r = lhs - 1; //r stands for record index offset of pivot from original index
            for (int s=lhs; s<rhs; s++){ //s stands for index for scanning
                if (v[s] < thisPivot){   // if current element is larger than the pivot, the swap
                    r = r + 1;
                    swapValues(v[r], v[s]);
                }
            } 
            swapValues(v[r + 1], thisPivot);

        //Recursion:
            //int pivotIndex = r + 1;
            quicksort(v, lhs, r); //We want pivotIndex - 1.
            quicksort(v, r + 2, rhs); //We want pivotIndex + 1
    }
}

const int MAX = 1000000;
const int TOTAL_SECTIONS = 8;
const int PER_SECTION = MAX/TOTAL_SECTIONS;


void *startsort(int arr[])
{

    //std::cout << "Starting Array quick sort (my sort!) with "<<(arg->local_max-arg->local_min)<< " items\n"; (Debug)
    quicksort(arr, 0, PER_SECTION-1);
    //std::cout << "Ending quick sort\n"; (Debug)

    return NULL;
}

//merge the 2 arrays into one large array, return
void merge(int *arr1, int *arr2, int num_elements)
{
    //std::cout << num_elements << std::endl; (Debug)
    int total_split = num_elements*2;
    int mergedArr[total_split];
    //std::cout << total_split << std::endl; (Debug)
    int i = 0;
    int j = 0;
    int k = 0;
    
    while(i<num_elements && j<num_elements)
    {
        if(arr1[i]<arr2[j])
        {
            mergedArr[k] = arr1[i];
            k++;
            i++;
        } 
        else
        {
            mergedArr[k] = arr2[j];
            k++;
            j++;
        }
    }
    
    while(i<num_elements)
    {
        mergedArr[k] = arr1[i];
        k++;
        i++;
    }
    while(j<num_elements)
    {
        mergedArr[k] = arr2[j];
        k++;
        j++;
    }
    
    //std::cout << "Merge complete. Copying..." << std::endl; (Debug)
    
    //copy the sorted elements into the original array
    for (int l = 0; l < num_elements; l++)
    {
        //std::cout << "1st Half..."<< std::endl;
        arr1[l] = mergedArr[l];
    }

    for (int m = 0; m < num_elements; m++)
    {
        //std::cout << "2nd Half..."<< std::endl;
        arr2[m] = mergedArr[m+num_elements];
    }
    
    //std::cout << "Copy complete." << std::endl; (Debug)
    
    //return this_arr[num_elements];
}


/*Start of threading*/


int main(int argc, char* argv[]){
	if (argc < 3){
		std::cout << "Please include input filename and output filename in param list.\n";
		std::cout << "Example:\n";
		std::cout << "     % mySort numbers.txt mySorted.txt\n";
		exit(EXIT_SUCCESS);
	}


  	std::ofstream fout;
	std::ifstream fin;
	int n;
	
	int v[MAX];
	int count = 0;
	
	fin.open(argv[1]);
	while (fin >> n ){
		v[count++] = n;	// insert a number into the array and increase the index
	}

	std::cout << "Quicksort!" << std::endl;

    /*Start of threading*/

    //We want to original array to stay intact. However we still want to sort it. 
    //Therefore, we will set a pointer to the starting and ending addresses of the array.
    //I will call these sub arrays "partitions"
    message argList[TOTAL_SECTIONS]; // array of arguments to pass to each thread
    for (int i=0; i<TOTAL_SECTIONS; i++)
    {
        argList[i].arr = &(v[i*PER_SECTION]);//definition of array at the 0th index in the partition
        argList[i].local_min = (i*PER_SECTION); //0th index in the partition
        argList[i].local_max = ((i+1)*PER_SECTION - 1); //124999th index in the partition
        argList[i].index = i;
        argList[i].wait = rand()%5;
    }

    // create 8 threads. threads launch a process upon creation
    // pass the function name and all parameters.
    // In this case, a function name and the array
    std::thread thread0(startsort,argList[0].arr);
    std::thread thread1(startsort,argList[1].arr);
    std::thread thread2(startsort,argList[2].arr);
    std::thread thread3(startsort,argList[3].arr);
    std::thread thread4(startsort,argList[4].arr);
    std::thread thread5(startsort,argList[5].arr);
    std::thread thread6(startsort,argList[6].arr);
    std::thread thread7(startsort,argList[7].arr);

    // force the threads to join back to the main program
    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();


    for(int j=0; j<(TOTAL_SECTIONS); j = (j+2))
    {
        //std::cout << j << std::endl; (Debug)
        //std::cout << (j+1) << std::endl; (Debug)
        merge(argList[j].arr, argList[(j+1)].arr, (PER_SECTION));
        //std::cout << "Success..."<<std::endl; (Debug)
    }
    for(int j=0; j<(TOTAL_SECTIONS); j = (j+4))
    {
        //std::cout << j << std::endl; (Debug)
        //std::cout << (j+2) << std::endl; (Debug)
        merge(argList[j].arr, argList[(j+2)].arr, ((PER_SECTION)*2));
        //std::cout << "Success..."<<std::endl; (Debug)
    }
    for(int j=0; j<(TOTAL_SECTIONS); j = (j+8))
    {
        //std::cout << j << std::endl;
        //std::cout << (j+4)<< std::endl;
        merge(argList[j].arr, argList[(j+4)].arr, ((PER_SECTION)*4));
        //std::cout << "Success..."<<std::endl; (Debug)
    }

    fout.open(argv[2], std::ios::out | std::ios::trunc);
    for (int i = 0; i < count; i++)
	    fout << v[i]<<std::endl;

    fout.close();
	fin.close();
    return 0;


}	
