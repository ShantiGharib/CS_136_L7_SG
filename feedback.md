**4/23/2025**
*  **feedback.md is for instructor use only. DO NOT change the feedback.md**; make a copy if needed
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* member variables should be defined and initialized on separate lines; one per line -2
* units taken should be int or unsigned short int, not size_t ; size_t is for holding size of objects in memory -1;  
*  unsigned long long unitsTaken{0}; waste of memory; are you expecting a student to take over a million units in their lifetime at one institution? (unsigned long long int in C++ is from 0 to 18,446,744,073,709,551,615 (264 - 1)); institutions keep student records forever and have thousands and thousands of students  -2
* data should be displayed in a table format with column headings whenever possible; text entries should be left aligned; and numerical entries should be right aligned with the same number of decimal places -2
* notDefault{false}  what for?
* poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”, e.g., MAX_TERMS, PRINT_RECORDS; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ; do not use IDs that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious -1
```text
notDefault{false}
```
* #44   do all hashtable objects must be of the same size?
* inadequate and/ insufficient test data/ not all possible scenarios and edge cases have been tested; e.g., each record has 4 pieces of data; pow(2,4)->16  possible combinations of valid/invalid and only one of them is a valid record; all menu options should be tested;  no zeros, negative numbers, etc -5
* 305, 306 – what if copy process fails? -5



**4/8/2025**
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary 
*  **DO NOT change the feedback.md**; make a copy if needed
* member variables should be defined on separate lines; one per line
* initialized{false}, #53 – what for? -2
* should initialize all variables, members or not, to appropriate default values at the time of definition; improves readability, in case of member variables, helps to avoid initialization lists, helps with the exception handling and providing a strong exception guarantee; strings should be initialized to something other than “” n/a for example -2
* 195-207  why so many blank lines? It requires  more scrolling yet does not offer any advantage
* units taken should be int or unsigned short int, not size_t ; size_t is for holding size of objects in memory -1; 
*  #293, 342  does not provide a strong exception guarantee: clears the Left bHash Table (LeftHashTable=RightHashTatble)  before ensuring that the copy process was completed; should have attempted to copy first and deallocate only if the copy process was completed successfully;  if copy process failed should have deallocated all newly created nodes and left the LeftHashTable in the original state; see assignment  -5
* #301 let the calling place to decide what to do with  in case of unsuccessful memory allocation -2
* #320 -328 if you do the same thing twice, make it a function; you can call the same function multiple times -2
* #336 allocation is not successful, should deallocate here, set member variables to defaults if needed and let the user know -2
* #448 improper/poor use of try/catch;  should be used  to separate the successful path of execution from the error path of execution; in other words,  “if everything goes well” code goes into the try block -2
* #465  it's kind of hard to delete the memory; it is much easier to free it  -1
* #492 what if the numbers change? If it is not one or zero, make it a constant -2;
* #83-85  no need for word print, it is redundant ‘ “Search by ID” is clear enough-1
* some function can be streamlined
* hard to read menu in the code, see  example below -1
```
cout << "\n\nMenu:\n”
    “1. Encrypt\n”
            “2. Decrypt\n”
           “3. Quit\n"<<endl;
//<< not needed between strings
```
