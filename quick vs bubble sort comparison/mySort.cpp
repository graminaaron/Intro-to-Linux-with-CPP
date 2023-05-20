//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 3
//  Due Date: Mon/Sept 30/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>

void swapValues(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// This quick sort function uses an array
void quicksort(int v[], int lhs, int rhs){    
    // the whole goal of quick sort is to choose a pivot and find where it belongs
    if (lhs < rhs){
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

void startsort(int v[], int thisMax){
    std::cout << "Starting Array quick sort (my sort!) with "<<thisMax<< " items\n";
    quicksort(v, 0, thisMax-1);
    std::cout << "Ending quick sort\n";
}

int main(int argc, char* argv[]){
	if (argc < 3){
		std::cout << "Please include input filename and output filename in param list.\n";
		std::cout << "Example:\n";
		std::cout << "     % mySort numbers.txt mySorted.txt\n";
		exit(EXIT_SUCCESS);
	}


	const int MAX = 1000000;
  	std::ofstream fout;
	std::ifstream fin;
	int n;
	
	int v[MAX];
	int count = 0;
	
	fin.open(argv[1]);
	while (fin >> n ){
		v[count++] = n;	// insert a number into the array and increase the index
	}

	startsort(v,count);	// call the sorting function

        fout.open(argv[2], std::ios::out | std::ios::trunc);
        for (int i = 0; i < count; i++)
		fout << v[i]<<std::endl;


        fout.close();
	fin.close();
    return 0;
}	
