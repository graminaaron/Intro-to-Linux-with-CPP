#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

 // bubble sort using a vector
void bubble(vector<int> &v)
{

	cout << "Starting Vector bubble sort with "<<v.size()<< " items\n";

	for (int i=0; i<v.size()-1; i++)
		for(int j=0; j<v.size()-1-i; j++)
			if (v[j] > v[j+1])
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
		cout << "Please enter the input file and output file name in parameter list.\n";
		cout << "Example:\n";
		cout << "     % mySortV numbers.txt sortedV.txt\n";
		exit(EXIT_SUCCESS);
	}

  	ofstream fout;
	ifstream fin;
	int n;
	
	vector<int> v;
	
	int i = 0;
	//cout << "CP2\n";
	fin.open(argv[1]);
	while (fin >> n)     // red until no numbers left in input file
	{
		v.push_back(n);   // add nuw number to back of vector
	}

	bubble(v); // call bubble sort

        fout.open(argv[2], ios::out | ios::trunc);
        for (int i = 0; i < v.size(); i++)
		fout << v[i]<<endl;


        fout.close();
	fin.close();
        return 0;
}	
