//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Proj 6
//  Due Date: Mon/Nov 9/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

#include <string>
#include <regex>

#include <map>
#include <unordered_set>

std::string makeLowercase(std::string& s)
{
    std::string ns = "";
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        if('A' <= ch && ch <= 'Z')
        {
            ch = ch - 'A' + 'a';
            ns = ns + ch;
        }
        else
        {
            ns = ns + ch;
        }
    }
    return ns;
}
    

int main(int argc, char* argv[]){
	if (argc < 4){
		std::cout << "Please include input filename and output filename in param list.\n";
		std::cout << "Example:\n";
		std::cout << "     \% spellChecker dictionary.txt words.txt output.out\n";
		exit(EXIT_SUCCESS);
	}

    std::unordered_set<std::string> dictionary;
    //std::unordered_set<std::string> words;
    std::map<std::string, int> misspelled;

    std::ofstream fout;
	std::ifstream fin;

    std::string word;
    std::locale loc;

    //load all dictionary words into the set 
	fin.open(argv[1]);
    
    while (fin >> word)
	{   
        word = makeLowercase(word);
		dictionary.insert(word);		
	}
    fin.close();

    /*
    fin.open(argv[2]);
    while (fin >> word)
	{
		word = makeLowercase(word);
        words.insert(word);	
	}
    fin.close();
    
    for(auto iter = dictionary.begin(); iter != dictionary.end(); iter++)
    {
        std::cout << *iter << std::endl; //Debug
    }
    */
    std::cout << "Spell Checking... " << std::endl;
    fin.open(argv[2]);
    //std::cout << "Misspelled words:" << std::endl;
    while (fin >> word)
	{
        word = makeLowercase(word);
        //std::cout << word << std::endl; Debug
        std::smatch m;
        std::regex reg("[a-z]+[\']?[-]*[a-z]*[-]*[a-z]*");

        bool missed = true;
        //std::cout << word << std::endl; //Debug
        regex_search(word,m,reg);
        //std::cout << m.str(0) << std::endl; //Debug

        if(m.str(0).length()) { // if there is a result of smatch 
            //std::cout << "checkpoint 1" << std::endl; //Debug
            if(dictionary.count(m.str(0)))
            {
                //std::cout << "checkpoint 2" << std::endl; //Debug
                missed = false; 
                //break; //...move to the next word
            }

            if (missed)
            {
                //std::cout << "checkpoint 3" << std::endl; //Debug
                misspelled[m.str(0)] = misspelled[m.str(0)] + 1; //...add to list of misspelt words
            }
            /*
            for(auto iter = dictionary.begin(); iter != dictionary.end(); iter++)
            {
                if (m.str(0) == *iter) // if the result of smatch exists in the dictionary...
                {
                    missed = false; 
                    break; //...move to the next word
                }
            }

            if (missed) // if smatch is not in the dictionary...
            {
                misspelled[m.str(0)] = misspelled[m.str(0)] + 1; //...add to list of misspelt words
            }
            */
        }   
	}
    fin.close();
    int total_missed = misspelled.size();
    //std::cout << "Words Misspelt: " << total_missed << std::endl;
    fout.open(argv[3], std::ios::out | std::ios::trunc);
    fout << "Misspelled words:" << std::endl;
    fout << "Words Misspelt: " << total_missed << std::endl;
    for(auto iter = misspelled.begin(); iter !=misspelled.end(); iter++)
    {
        //std::cout << iter->first << ":" << iter->second << std::endl; //
        fout << iter->first << ":" << iter->second << std::endl;
    }
    //std::cout << "Words Misspelt: " << total_missed << std::endl;
    fout << "Words Misspelt: " << total_missed << std::endl;
    fout.close();
    
    return 0;
}	
