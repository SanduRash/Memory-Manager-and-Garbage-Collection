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

//to check if a variable is in the linked list
bool memoryList::checkIsThere(string name) {
    variable* curr = _root;
    while (curr != nullptr) {
        for (const string& existingName : curr->varnames()) {
            if (existingName == name) {
	      return true; // if the name is inside of linked list then return true
            }
        }
        curr = curr->next();
    }
    return false;
}


//free a block
 void memoryList::free(string name)
  {
    variable* curr = _root;
    while (curr != nullptr) {
      vector<string>& names = curr->varnames(); // Reference to the name list
      auto it = find(names.begin(), names.end(), name);
      if (it != names.end()) {
	// Name found — remove it
	names.erase(it);  // if you find the name for freeing a block, then erase the name
	
	
	// Decrease refcount
	curr->refcount() -= 1;  //Also decrease a refference count by 1
	break;
	    }
      curr = curr->next();
    }     
  }


//Allocate a space for a variable.
    void memoryList::alloc(string name, int size) {
      variable* newVar;
      variable* prev=_root;

      if(checkIsThere(name))   // if we reassign the space for a same variable, first free the space, then reallocate.
	{
	  //Delete that variable first
	  free(name);
	}

      variable* curr = _root; ///Then find a block with enough size to allocate.
      //Once you found, break the linked list. create a new node. then place that new node in between splited linked list.
        while (curr != nullptr) {
	  if(curr->varsize()>=size && curr->refcount() == 0)
	    {
	      newVar = new variable(name, curr->address(), size, 1);
	      curr->address() = curr->address() + size;
	      curr->varsize() = curr->varsize() - size;
	      break;
	    }
	  prev = curr;
	  curr = curr->next();
        }

	newVar->next() = curr;
	prev->next() = newVar;
    }

 void memoryList::assign(string lhs, string rhs){
   if(lhs != rhs){            //if the left hand and the right hand have the same variable name, then do not do anything
     if(checkIsThere(lhs))    // if they are different, free the space of left hand side variable before reassigning.
	{
	  //Delete that variable first
	  //cout<<"this var is already there"<<endl;
	  free(lhs);
	}

      variable* curr = _root;
      while (curr != nullptr) {
	vector<string>& names = curr->varnames(); // Reference to the name list
	auto it = find(names.begin(), names.end(), rhs);
	if (it != names.end()) {
	  // Name found — remove it           //Since we assigning varibles each other, they will take the same space. 
	  names.push_back(lhs);
	  
	  // Decrease refcount
	curr->refcount() += 1;
	break;
	}
      curr = curr->next();
      }
   }

       
  }


void memoryList::dump(){

    vector<string> freeList;
    cout<<"Variables:"<<endl;
      variable* curr = _root;
      while (curr != nullptr) {

	if(curr->refcount() > 0)
	  {
	    vector<string>& names = curr->varnames(); // Reference to the name list
	    for (const string& name : names) {
	      cout<<name<<":"<< curr->address() << "(" << curr->varsize() << ") [" << curr->refcount() << "]" << endl; //Print variables
	    }
	    
	  }
	else if(curr->refcount() == 0)
	  {
	   string slot = to_string(curr->address()) + "(" + to_string(curr->varsize()) + ") [" + to_string(curr->refcount()) + "]";

	   freeList.push_back(slot);  //collect free spaces first.
	  }
	curr = curr->next();
      }

	cout<<"Free List:"<<endl;
	
	for (size_t i = 0; i < freeList.size(); ++i) {
	  cout << freeList[i];
	  if (i != freeList.size() - 1) cout << ", ";  // Now print free spaces.
	}
	cout<<endl;
	cout <<"================================================================================"<< endl;
	
	
      }

void memoryList::compress(){
  variable* curr = _root->next();
  variable* prev = _root;
      while (curr != nullptr) {

        if(curr->refcount() == 0 && prev->refcount() ==0 && (prev->address() + prev->varsize() == curr->address()))
	  {
	    prev->varsize() = prev->varsize() + curr->varsize();
	    prev->next() = curr->next();

	    curr = prev->next();
	  }
	else
	  {
	    prev = curr;
	    curr = curr->next(); 
	  }
	
      }
}
