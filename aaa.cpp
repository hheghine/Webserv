
#include <strings.h>
#include <sstream>
#include <ios>
#include <iostream>
#include <fstream>

// int main()
// {
// 	std::string a = "www/favicon.ico";
// 	std::ifstream b;
// 	std::stringstream ss;

// 	// ss << barev.rdbuf();
// 	std::cout << ss.str() << std::endl;
// 	return (0);
// }
using namespace std; 
  
int main() 
{ 
    // Open the file "abc.txt" for reading 
    ifstream inputFile("abc.txt"); 
  
    // Variable to store each line from the file 
    string line; 
  
    // Read each line from the file and print it 
    while (getline(inputFile, line)) { 
        // Process each line as needed 
        cout << line << endl; 
    } 
  
    // Always close the file when done 
    inputFile.close(); 
  
    return 0; 
}