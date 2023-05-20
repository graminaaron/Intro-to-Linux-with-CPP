#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// This bubble sort function uses an array
void bubble(int v[], int max)
{

	cout << "Starting Array bubble sort with "<<max<< " items\n";

	for (int i=0; i<max-1; i++)
		for(int j=0; j<max-1-i; j++)
			if (v[j] > v[j+1])   // if items are out of order, then swap.
			{
				int temp = v[j];
				v[j] = v[j+1];
				v[j+1] = temp;

			}

	cout << "Ending bubble sort\n";}


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Please include input filename and output filename in param list.\n";
		cout << "Example:\n";
		cout << "     % mySortA numbers.txt mySorted.txt\n";
		exit(EXIT_SUCCESS);
	}


	const int MAX = 1000000;
  	ofstream fout;
	ifstream fin;
	int n;
	
	int v[MAX];
	int count = 0;
	
	fin.open(argv[1]);
	while (fin >> n )
	{
		v[count++] = n;	// insert a number into the arary and increase the index
	}

	bubble(v,count);	// call the bubbleSort function

        fout.open(argv[2], ios::out | ios::trunc);
        for (int i = 0; i < count; i++)
		fout << v[i]<<endl;


        fout.close();
	fin.close();
        return 0;
}	
