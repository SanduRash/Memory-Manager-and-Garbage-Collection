//////////////////////////////////////////
//Sandu Galbokka Hewa
//System II Project 3
//April, 17 2025
/////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  
#include "Grammar.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include "MemoryList.hpp"
#include "Variable.hpp"

using namespace std;

#include "MemoryList.hpp"

memoryList newMemory(0); // will set actual heap size later

int main(int argc, char *argv[])
{
  int heapSize;
  cout<<"Please enter the initial freelist (heap) size: ";
  cin>>heapSize;

  newMemory = memoryList(heapSize); // assign heap size globally
  newMemory.root() = new variable("dummy", -1, 0, -1);
  
  variable* fullSpace = new variable("", 0, heapSize, 0);
  newMemory.root()->next() = fullSpace;

 

  string fileName;
  cout<<"Please enter the name of an input file: ";
  cin>>fileName;


  // open input file
  ifstream ifile(fileName);

  // my stream of input tokens to pick from
  TokenStream tokens(ifile);

  prog(tokens);

  return 0;
}
