/*******************************************
 * File: TokenStream.hpp                   *
 * Author: S. Blythe                       *
 * Date: 1/2025                            *
 * PURPOSE: defines a stream of tookens    *
 *   that can be read from or put back to *
 *******************************************/
#ifndef _TOKEN_STREAM_
#define _TOKEN_STREAM_

#include <iostream>
#include <list>

#include "Token.hpp"

class TokenStream
{
private:
  std::list<Token> _stream; // the list of avaialable tokens 
  std::istream& _istr;      // istream tokens are pulled from when needed
public:
  TokenStream(std::istream &is) : _stream(), _istr(is) {}

  Token get();  // get next token

  void ungetRear(const Token &tok);  // put a token back at (reader) end
  void ungetFront(const Token &tok); // put a token back at (writer) end
  
  void unget(const Token &tok) {ungetRear(tok);} // put token back
};

#endif
