//////////////////////////////////////////
//Sandu Galbokka Hewa
//System II Project 3
//April, 17 2025
/////////////////////////////////////////

#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class variable {     // Class called info which is about each client's information.
private:
  vector<string> _varname;
  int _address;
  int _varsize;
  int _refcount;
  variable* _next;

public:
  variable(): _address(0),_varsize(0), _refcount(0), _next(nullptr)  {_varname.push_back("hhh");}
  variable(string varname,int address, int varsize, int refcount): _address(address),_varsize(varsize), _refcount(refcount), _next(nullptr)  {_varname.push_back(varname);}

  vector<string> varnames() const { return _varname; }
  vector<string>& varnames() { return _varname; }

  void addName(const string& name);

  int address() const{return _address;}
  int& address() {return _address;}

  int varsize() const{return _varsize;}
  int& varsize() {return _varsize;}

  int refcount() const{return _refcount;}
  int& refcount() {return _refcount;}
  
  variable* next() const { return _next; }
  variable*& next() { return _next; }
  
  std::ostream& print(std::ostream &toStream) const;
  
};

#endif
