//////////////////////////////////////////
//Sandu Galbokka Hewa
//System II Project 3
//April, 17 2025
/////////////////////////////////////////

#include "MemoryList.hpp"
#include "Variable.hpp"

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void variable::addName(const string& name) {
        _varname.push_back(name);
        _refcount++;
    }

std::ostream& variable::print(std::ostream &toStream) const {
    //for (const string& name : _varname) {
      toStream << _address << "(" << _varsize << ") [" << _refcount << "]" << endl;
      //}
    return toStream;
  }
