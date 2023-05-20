echo "Compiling..."
time c++ spellChecker.cpp -o spellChecker
time spellChecker american-english flatland.txt misspellings.out 
head -n 20 misspellings.out 