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
		{
			onOutOfMemory();
		}
		
		int size = aSize + 6;
		int index = *(unsigned short*)&MM_pool;
		int inUse = *(unsigned short*)&MM_pool[2];

		*(unsigned short *)&MM_pool[index] = aSize;
		if(inUse != 0)
		{
			*(unsigned short*)&MM_pool[index + 2] = inUse;
			*(unsigned short*)&MM_pool[inUse + 4] = index;
		}

		*(unsigned short*)&MM_pool[2] = index;
		*(unsigned short*)&MM_pool = index + size;
		return (void*)&MM_pool[index+6];
	}

	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		int cur = (char*)(aPointer) - MM_pool - 6;
		int prev = *(unsigned short*)&MM_pool[cur+4];
		int next = *(unsigned short*)&MM_pool[cur+2];
		int usedMem = *(unsigned short*)&MM_pool[4];

		if (next != 0)
		{
			*(unsigned short*)&MM_pool[next+4] = prev;
		}
		if (prev != 0)
		{
			*(unsigned short*)&MM_pool[prev+2] = next;
		}
		if (cur == *(unsigned short*)&MM_pool[2])
		{
			*(unsigned short*)&MM_pool[2] = next;
		}
		if (usedMem != 0)
		{
			*(unsigned short*)&MM_pool[usedMem+4] = cur;
		}
		*(unsigned short*)((char*)(aPointer) - 4) = usedMem;
		*(unsigned short*)&MM_pool[4] = cur;
	}

	int size(void *ptr)
	{
		// int result = (char*)(ptr);
		// return sizeof(result);
		// int length = sizeof(ptr)/sizeof(int);
		int length = 0;
		cout << endl;
		cout << "DEBUG: address of the void pointer: " << *(char*)ptr << endl;
		cout << "DEBUG: length of the void pointer: " << *(unsigned short*)((char*)(ptr)) << endl;
		cout << "DEBUG: What is this?: " << MM_POOL_SIZE - *(unsigned short*)((char*)(ptr))<< endl;
		return 0;
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
		int nextMemUsed = *(unsigned short*)&MM_pool[4];
		int memoryUsed = 0;
		while (nextMemUsed != 0)
		{
			memoryUsed += *(unsigned short*)&MM_pool[nextMemUsed] + 6;
			nextMemUsed = *(unsigned short*)&MM_pool[nextMemUsed+2];
		}
		return memoryUsed;
	}

	// Will scan the memory pool and return the total in use memory - memory being curretnly used
	int inUseMemory(void)
	{
		int nextMemInUse = *(unsigned short*)&MM_pool[2];
		int memoryInUse = 0;
		while(nextMemInUse != 0)
		{
			memoryInUse += *(unsigned short*)&MM_pool[nextMemInUse] + 6;
			nextMemInUse = *(unsigned short*)&MM_pool[nextMemInUse+2];
		}

		return memoryInUse;
	}

	// helper function to see the InUse list in memory
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

	//Helper function to see the Used list in memory
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
