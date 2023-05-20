//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 7
//  Due Date: Wed/Dec 7/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include "MemoryManager.h"

#include <iomanip>
#include <iostream>
using namespace std;

namespace MemoryManager
{
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT 
	//
	// This is the only static memory that you may use, no other global variables may be
	// created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT


	const int MM_POOL_SIZE = 65536;
	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use
	void memView(int start, int end)
	{

		const unsigned int SHIFT = 8;
		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << endl; // start on a new line
		cout << "               Pool                     Unsignd  Unsigned " << endl;
		cout << "Mem Add        indx   bits   chr ASCII#  short      int    " << endl;
		cout << "-------------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)
		{
			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal
			cout << '[' << setw(2) << i << ']';				// the index into MM_pool

			value = MM_pool[i];
			cout << " ";
			for (int j = 1; j <= SHIFT; j++)		// the bit sequence for this byte (8 bits)
			{
				cout << ((value & MASK) ? '1' : '0');
				value <<= 1;
			}
			cout << " ";

            if (MM_pool[i] < 32)   // non-printable character so print a blank
            	cout << '|' << ' ' << "| (";	
            else                    // characger is printable so print it
				cout << '|' << *(char*)(MM_pool + i) << "| (";		// the ASCII character of the 8 bits (1 byte)

			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";	// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";	// the unsigned short value of 16 bits (2 bytes)
			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)

																				//  cout << (*(unsigned int*)(MM_pool+i)) << "|";	// the unsigned int value of 32 bits (4 bytes)

			cout << endl;
		}
	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{

		int freeHead = 0; // starting index of the freelist
		int inUseHead = 2; // starting index of the inUselist
		int usedHead = 4; // starting index for the used list - deallocated memory

		int nextLink = 2; // offset index of the next link
		int prevLink = 4; // offset index for the prev link

		*(unsigned short*)(MM_pool + freeHead) = 6; // freelist starts at byte 6
		*(unsigned short*)(MM_pool + inUseHead) = 0;	// nothing in the inUse list yet
		*(unsigned short*)(MM_pool + usedHead) = 0; // nothing in the used list yet

	}

	// return a pointer inside the memory pool
	void* allocate(int aSize)
	{
		// If no chunk can accommodate aSize call onOutOfMemory()
		if ((int)(*(unsigned short*)(MM_pool)) + aSize + 6 > 65536)
			onOutOfMemory();

		int vSize = aSize + 6; //variable size = byte array size + node size
		int currentFreeHead = *(unsigned short*)&MM_pool[0];
		int currentInUseHead = *(unsigned short*)&MM_pool[2];
		//reserve MM_pool space by updating the head values
		int newFreeHead = vSize+currentFreeHead; //
		int newInUseHead = currentFreeHead;

		*(unsigned short*)&MM_pool[newInUseHead] = aSize;
		if(currentInUseHead != 0)
		{
			//update "prev array" node of the current variable
			*(unsigned short*)&MM_pool[newInUseHead+2] = currentInUseHead;
			//update "next array" node of the previous variable
			*(unsigned short*)&MM_pool[currentInUseHead+4] = newInUseHead;
		}
		*(unsigned short*)&MM_pool[2] = newInUseHead;
		//int newFreeHead = vSize + currentFreeHead;
		*(unsigned short*)&MM_pool[0] = newFreeHead;
		
		return (void*)&MM_pool[newInUseHead+6];
	}

	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		/*
		Created a table to determine which vars
		*(unsigned short*)&MM_pool[nextVar]; //Start of the next variable's node (size)
		*(unsigned short*)&MM_pool[nextVar+2]; //Next variables next
		*(unsigned short*)&MM_pool[nextVar+4]; //Next variables prev

		*(unsigned short*)&MM_pool[prevVar]; //Start of the previous variable's node (size)
		*(unsigned short*)&MM_pool[prevVar+2]; //Previous variables next
		*(unsigned short*)&MM_pool[prevVar+4]; //Previous variables prev

		*(unsigned short*)&MM_pool[currentVar]; //Start of the next variable's node (size)
		*(unsigned short*)&MM_pool[currentVar+2]; //Current variables next
		*(unsigned short*)&MM_pool[currentVar+4]; //Current variables prev
		*/

		int aSize = *(unsigned short*)&MM_pool[((char*)aPointer-MM_pool-6)];
		int prevVar = *(unsigned short*)&MM_pool[((char*)aPointer-MM_pool-4)];
		int nextVar = *(unsigned short*)&MM_pool[((char*)aPointer-MM_pool-2)];
		int currentVar = ((char*)aPointer-MM_pool-6);

		int currentUsedHead = *(unsigned short*)&MM_pool[4];
		int newUsedHead = currentVar;

		//std::cout << nextVar << std::endl;
		//std::cout << prevVar << std::endl;
		//std::cout << currentVar << std::endl;

		//Previous variables next = Next variable
		*(unsigned short*)&MM_pool[prevVar+4] = nextVar; //Previous variables next = //Next variables prev
		//Next variables next = Previous variables
		*(unsigned short*)&MM_pool[nextVar+2] = prevVar; 

		//update "next array" node of the current deallocated variable
		*(unsigned short*)&MM_pool[currentVar+2] = currentUsedHead; 		
		//wipe "prev array" node of the current deallocated variable
		*(unsigned short*)&MM_pool[currentVar+4] = 0;
		//update "prev variable" node with the current deallocated node
		*(unsigned short*)&MM_pool[currentUsedHead+4] = currentVar;
		//update new used head
		*(unsigned short*)&MM_pool[4] = newUsedHead; 
		
	}

	int size(void *ptr)
	{
		int aSize = *(unsigned short*)&MM_pool[((char*)ptr-MM_pool-6)];
		return aSize;
	}
	
	//---
	//--- support routines
	//--- 

	// Will scan the memory pool and return the total free space remaining
	int freeMemory(void)
	{
		return MM_POOL_SIZE - inUseMemory() - usedMemory() - 6;
	}


	// Will scan the memory pool and return the total used memory - memory that has been deallocated
	int usedMemory(void)
	{
		int usedIncrementer = *(unsigned short*)&MM_pool[4];
		int totalMem = 0;
		while (usedIncrementer != 0)
		{
			//array size + node
			int vSize = *(unsigned short*)&MM_pool[usedIncrementer]+6;
			//add up total
			totalMem = totalMem+vSize;
			//Go to next variable
			usedIncrementer = *(unsigned short*)&MM_pool[usedIncrementer+2];
		}
		return totalMem;
	}

	// Will scan the memory pool and return the total in use memory - memory being curretnly used
	int inUseMemory(void)
	{
		int inUseIncrementer = *(unsigned short*)&MM_pool[2];
		int totalMem = 0;
		while (inUseIncrementer != 0)
		{
			//array size + node
			int vSize = *(unsigned short*)&MM_pool[inUseIncrementer]+6;
			//add up total
			totalMem = totalMem + vSize;
			//Go to next variable
			inUseIncrementer = *(unsigned short*)&MM_pool[inUseIncrementer+2];
		}
		return totalMem;
	}

	// helper function to see teh InUse list in memory
	void traverseInUse()
	{
		int cur = *(unsigned short*)&MM_pool[2];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur+2];
		int prev = *(unsigned short*)&MM_pool[cur+4];
		cout << "\nTraversing InUse Memory....";
		cout << "\n      InUse Head:"<<cur;
		while (cur != 0)
		{
			cout << "\n        Index:"<<cur<<" Size:"<<size<<" Next:"<<next<<" Prev:"<<prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur+2];
			prev = *(unsigned short*)&MM_pool[cur+4];
		}
	}

	//Helper function to seet eh Used list in memory
	void traverseUsed()
	{
		int cur = *(unsigned short*)&MM_pool[4];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur+2];
		int prev = *(unsigned short*)&MM_pool[cur+4];
		cout << "\nTraversing Used Memory....";
		cout << "\n      Used Head:"<<cur;
		while (cur != 0)
		{
			cout << "\n        Index:"<<cur<<" Size:"<<size<<" Next:"<<next<<" Prev:"<<prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur+2];
			prev = *(unsigned short*)&MM_pool[cur+4];
		}
		
	}


	// this is called from Allocate if there is no more memory availalbe
	void onOutOfMemory(void)
  	{
    	std::cout << "\nMemory pool out of memory\n" << std::endl;
    	std::cout << "\n---Press \"Enter\" key to end program---:";

		cin.get();

    	exit( 1 );
  }
}
