//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 4
//  Due Date: Mon/Oct 19/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>

bool verifySort(int* arr, int len)
{
    for(int i = 0; i < len-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]){
	if (argc < 1){
		std::cout << "Please include input filename in param list.\n";
		std::cout << "Example:\n";
		std::cout << "     % \\verifySort mySorted.txt\n";
		exit(EXIT_SUCCESS);
	}


  	std::ofstream fout;
	std::ifstream fin;
	int n;
	
    const int MAX = 1000000;

	int v[MAX];
	int count = 0;
	
    //load the file into memory
	fin.open(argv[1]);
	while (fin >> n ){
		v[count++] = n;	// insert a number into the array and increase the index
	}

    bool is_sorted = verifySort(v, MAX);
	
    std::cout << "Numbers in the file: "<< count <<std::endl;
    if (is_sorted)
    {
        std::cout << "The file is sorted!" <<std::endl;
    }
    else
    {
        std::cout << "The file is NOT sorted!" <<std::endl;
    }

    /*
    fout.open(argv[2], std::ios::out | std::ios::trunc);
    for (int i = 0; i < count; i++)
	    fout << v[i]<<std::endl;

    fout.close();
    */
	fin.close();
    return 0;


}	
