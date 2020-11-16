/*********************************************************/
/****  CString.h                                      ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class definition for  ****/
/****    CString.                                     ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#ifndef __CString_h__
#define __CString_h__

#include <iostream.h>
#include <stdlib.h>
#include <stdarg.h>

#define FORMAT_BUFF_SIZE 256

class CString {
    friend CString spaces(unsigned int);
    friend CString str(char, unsigned int);
    friend unsigned int len(CString);
    friend CString operator+(const char, const CString&);
    friend CString operator+(const char*, const CString&);
    //friend CString& operator+=(const CString&, const char&);
 public:
    CString();                      // initialize to empty Cstring
    CString(const char* s);         // initialize to a copy of s
    CString(const CString& s);          // initialize as a copy of s

    ~CString();

    unsigned int length() const;
                                // returns length of string (excluding
                                // terminal null character)
    char* chars() const;  // returns simple C++ character string
    CString::operator char *() const;
    char& operator[] (unsigned int i) const;
                                // returns reference to ith character
                                // in string
    CString operator() (int, int) const;
                                // retruns substring
    // These assignment operators have the same semantics as the
    // corresponding constructors.
    CString& operator = (const char*);
    CString& operator = (const char);
    CString& operator = (const CString&);

    // The addition operators each return a String that is the
    // concatenation of the host Str and the argument.  They do not
    // modify either the host Str or the argument.
    CString operator + (const char*) const ;
    CString operator + (char) const ;
    CString operator + (const CString&) const ;
    CString& operator+=(const CString&);
 
    // compare performs a lexicographic comparison of the host string
    // with its argument.  It returns -1 if the host string is
    // lexicographically less than the argument, returns 0 if they are
    // equal, and returns 1 if the host is greater than the argument.
    // The overloaded operators also do lexicographic comparison.
    int compare(const CString&) const;
    short operator == (const CString&) const;
    short operator != (const CString&) const;
    short operator <  (const CString&) const;
    short operator <= (const CString&) const;
    short operator >  (const CString&) const;
    short operator >= (const CString&) const;

    void trimLeft();                  // Removes leading spaces
    void trimRight();                 // Removes trailing spaces
    void trim();                      // Removes trailing and leading spaces
    void format(const char* format, ...);    // Formats string like sprintf

    short startsWith(const CString& s) const;
                                // return true if the host starts with s
    short endsWith(const CString& s) const;
                                // returns true if the host ends with s
    short contains(const CString& s) const;
                                // returns true if the host contains s
    int inStr(const char c) const;
                               // returns the index of first occurence of
                               // 'c' in the string if it exists, -1 otherwise
    int removeChar(const char c);
                               // removes all occurences of c. Returns
                               //non-negative int if c was in host, 
                               // negative otherwise.
    int replace(char c1, char c2);
                              // replaces all occurences of c1 with c2 and
                              // returns the number of occurences.

        // The following three functions perform case manipulations on
        //strings.
    void upcase();
        // upcase makes all alphabetic characters upper-case.
    void downcase();
        // downcase makes all alphabetic characters lower-case.
    void capitalize();
        // If the first character of a word is alphabetic, capitalize makes
        // it upper-case. All other alphabetic characters are made
        // lower-case.  A word is any string separated by whitespace
        // (you can use the isspace() function to determine if a character
        // is whitespace).

    // The firstToken and nextToken functions are used to break a
    // string into separate tokens.  The boundaryChars argument is
    // a string containing all characters that act as dividers between
    // tokens.  Both functions return a zero-length string when there are
    
CString firstToken(const CString& boundaryChars) const;
        // makes a hidden copy of the host object and returns another
        // String object containing the first token in the host object.
    static CString nextToken(const CString& boundaryChars);
        // Working with the hidden string copy created by firstToken,
        // returns the next token in the string.  Returns an empty
        // (zero-length) string when there are no more tokens.
private:
    char* _chars;
    static char* _tokenStr;
};

inline ostream& operator << (ostream& os, const CString& s) {
    os << s.chars();
    return(os);
}

// The input operator reads an entire line (without the terminating
// newline) from the istream "is".
inline istream& operator >> (istream& is, CString& s) {
    char buf[1024];
    //is.getline(buf, 1023, '\n');
    is >> buf;
    s = buf;
    return(is);
}

inline CString::operator char *() const {
    return _chars;
}

//inline short CString::getline(istream& is)
//{
//   char buf[1024];
//   if(is.getline(buf, 1023, '\n'))
//   {
//      delete [] _chars;
//      _chars = new char[strlen(buf) + 1];
//      strcpy(_chars, buf);
//      return (short)1;
//   }
//   else return (short)0;
//}

#endif 
