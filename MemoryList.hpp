//////////////////////////////////////////
//Sandu Galbokka Hewa
//System II Project 3
//April, 17 2025
/////////////////////////////////////////

#ifndef _MEMORYLIST_HPP_
#define _MEMORYLIST_HPP_
#include "Variable.hpp"


#include <iostream>
#include <string>
//using namespace std;

class memoryList{     // Class called info which is about each client's information.
private:
    int _memory;
    variable* _root;

public:
  memoryList() : _memory(0), _root(nullptr) {}
  memoryList(int memory) : _memory(memory), _root(nullptr) {}
  
  int memoryLeft() const { return _memory; }
  int& memoryLeft() { return _memory; }
  
  variable* root() const { return _root; }
  variable*& root() { return _root; }
 
  bool checkIsThere(string name);
  void free(string name);    
  void alloc(string name, int size);
  void assign(string lhs, string rhs);
  void dump();
  void compress();
  
};


extern memoryList newMemory;  // declare the global variable

#endif
