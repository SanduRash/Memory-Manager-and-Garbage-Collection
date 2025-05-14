//////////////////////////////////////////
//Sandu Galbokka Hewa
//System II Project 3
//April, 17 2025
/////////////////////////////////////////

/***************************************************************/
/*  FILE: Grammar.cpp                                          */
/*  AUTHOR: S. Blythe                                          */
/*  DATE: 3/2025                                               */
/*  PURPOSE: Implementation of recursive descent parser rules  */
/***************************************************************/
#include "Grammar.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include "MemoryList.hpp"
#include "Variable.hpp"

using namespace std;

string leftidforAssign;

// <prog> -> <slist> rule
string prog(TokenStream &ts)
{
  return slist(ts);
}

// <slist> -> [VARIOUS - see code] rule
string slist(TokenStream &ts)
{
  // see if there is a statement ...
  string stmtstr = stmt(ts);

  // if no statemnt, it's OK, we matched the epsilon rule
  //  i.e. we just atched the <slist> -> epsilon   rule
  if (stmtstr=="")
    return "";

  // we got a statement ... so a semicolon should come next
  Token sc = ts.get();

  // if no semicolon, something is wrong ...
  if (sc!=SEMICOLON)
  {
    cerr << "  Expected ';', got:" << sc << endl;
    ts.unget(sc);
  }

  // we have   <stmt> ;     so far ... we now need anther <slist> 
  string stmtliststr = slist(ts);

  // now we've matched    <slist> -> <stmt> ; <slist> 
  return stmtstr + ";\n" + stmtliststr;
}

// <stmt> -> [VARIOUS - see code]
string stmt(TokenStream &ts)
{
  // all statements start with an ID
  Token id = ts.get();
  string startID = id.value();

  // if no ID, we didn't have a statement. 
  if (id.type()!=ID)
  {
    // better unget the part we read - it belongs to something else. 
    ts.unget(id);
    return "";
  }

  // next token could be aan LPAREN or an = 
  Token next=ts.get();
  if (next==LPAREN) // function call
  {
    // if LPAREN we have a function call 
    Token rparen; 
    Token optArg=ts.get();
    string arg;
    if (optArg==ID) // we have an argument  (so must be a free call)
    {
      arg=optArg.value();
      //////it should be free(var)
      // cout<<"it should be free(var) "<<optArg.value()<<endl;
      newMemory.free(optArg.value());
      rparen = ts.get();
    }
    else //  could be either compress() or dump() - check the ID to decide
    {
      
      if(startID =="dump")
	{//cout<<"Do dump"<<endl;
	  newMemory.dump();
	}
      
      if(startID =="compress")
	{
	  //cout<<"Do compress"<<endl;
	newMemory.compress();
	}
      rparen = optArg; 
    }

    // didn't get an RPAREN ... something is wrong. 
    if (rparen!=RPAREN) 
    {
      cerr << "Unexpected token:'" << rparen << "' found on line "
           << rparen.lineNumber() << endl;
      ts.unget(rparen);
      return "";
    }

    return id.value() + "( " + arg + " )";
  }
  else if (next==ASSIGNOP) // <stmt> -> ID ASSIGNOP <rhs> 
  {
    // already have "ID = " ... need to get <rhs>
    leftidforAssign = startID;
    //cout<<startID<< " ";
    string rhsstring = rhs(ts);
    return id.value() + " = " + rhsstring;
  }

  // if we get here, it's an unknown stmt. 
  cerr << "ERROR: expected stmt not found near line "
       <<  next.lineNumber() << endl;
  return "";
}

// <rhs> -> [VARIOUS - see code] 
string rhs(TokenStream &ts)
{
  // all rhs options start with an ID
  Token id = ts.get();
  if (id != ID) 
  {
    cerr << "Expected ID not found near line " << id.lineNumber() << endl; 
    return "";
  }
  
  // we might or might not be a function call
  Token next = ts.get();
  if (next!=LPAREN) // not a function call <stmt> -> ID
  {
    // unget the attempted start of a function call (
    ts.unget(next);
    //////////This is about something like  a = b
    //cout<<"REFERRENCING left of "<<leftidforAssign<< " with rhs of "<<id.value()<<endl;
    newMemory.assign(leftidforAssign,id.value());
    return id.value();
  }

  // we are a function call <stmt> -> ID LPAREN NUM_INT <RPAREN> 
  Token arg = ts.get();
  //cout<<arg<<"DO allocation here for "<<leftidforAssign<<endl;
  newMemory.alloc(leftidforAssign, stoi(arg.value()));
  if (arg!=NUM_INT)
  {
    cerr << "Expected NUM_INT not found near line " << id.lineNumber() << endl; 
    return "";
  }

  // we've got     ID ( NUM_INT     so far ... need the )
  Token rparen = ts.get();
  if (rparen!=RPAREN)
  {
    cerr << "Expected ')' not found near line " << rparen.lineNumber() << endl;
    ts.unget(rparen);
  }
  return id.value() + "( " + arg.value()  + " )" ;
}
