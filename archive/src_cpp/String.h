#ifndef __String_h__
#define __String_h__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define FORMAT_BUFF_SIZE 256

class String {
    friend String operator+(const char, const String&);
    friend String operator+(const char*, const String&);

	// String functions.
	friend bool IsNumeric(const String&);
	friend bool IsAlpha(const String&);
	friend String Reverse(const String&);
    inline friend String Spaces(int);
    inline friend int Len(const String&);
	inline friend String Upper(const String&);
	inline friend String Lower(const String&);
 public:
    String();                      // initialize to empty String
    String(const char* s);         // initialize to a copy of s
    String(const String& s);          // initialize as a copy of s
	String(char, unsigned int);
	String(char);
	String(long);
	String(double);
	String(int);
	String(float);

    ~String();

    unsigned int Length() const { return strlen(_chars); }
                                // returns length of string (excluding
                                // terminal null character)
    const char* Chars() const { return _chars; }  // returns simple C++ character string


    operator const char *() const { return _chars; }
    char& operator[] (unsigned int i) const;
    String operator() (unsigned int, unsigned int) const;
    String& operator = (const String&);

    // The addition operators each return a String that is the
    // concatenation of the host Str and the argument.  They do not
    // modify either the host Str or the argument.
    String operator + (const String&) const ;
    String& operator+=(const String&);
 
    // compare performs a lexicographic comparison of the host string
    // with its argument.  It returns -1 if the host string is
    // lexicographically less than the argument, returns 0 if they are
    // equal, and returns 1 if the host is greater than the argument.
    // The overloaded operators also do lexicographic comparison.
    int Compare(const String& s) const { return strcmp(_chars, s._chars); }
    bool operator == (const String& s) const { return Compare(s) == 0; }
    bool operator != (const String& s) const { return Compare(s) != 0; }
    bool operator <  (const String& s) const { return Compare(s) <  0; }
    bool operator <= (const String& s) const { return Compare(s) <= 0; }
    bool operator >  (const String& s) const { return Compare(s) >  0; }
    bool operator >= (const String& s) const { return Compare(s) >= 0; }

    void TrimLeft(char c=' ');                  // Removes leading spaces
    void TrimRight(char c=' ');                 // Removes trailing spaces
    void Trim(char c=' ') { TrimLeft(c); TrimRight(c); }    // Removes trailing and leading spaces
    void Format(const char* format, ...);    // Formats string like sprintf

    bool StartsWith(const char*) const; //const String& s) const;
                                // return true if the host starts with s
    bool EndsWith(const char*) const; //const String& s) const;
                                // returns true if the host ends with s
    //bool Contains(const String& s) const;
                                // returns true if the host contains s
    //int InStr(const char c) const;
                               // returns the index of first occurence of
                               // 'c' in the string if it exists, -1 otherwise
	bool Replace(int, int, const char*);//const String&);
	int Replace(char c1, char c2);
                              // replaces all occurences of c1 with c2 and
                              // returns the number of occurences.

    int RemoveChar(const char c);
                               // removes all occurences of c. Returns
                               //non-negative int if c was in host, 
                               // negative otherwise.
	int Pos(const char* /*const String&*/, int=0) const;
	String Right(int) const;
	String Left(int) const;

        // The following three functions perform case manipulations on
        //strings.
    void Upper();
        // upcase makes all alphabetic characters upper-case.
    void Lower();
        // downcase makes all alphabetic characters lower-case.
    void Capitalize();
        // If the first character of a word is alphabetic, capitalize makes
        // it upper-case. All other alphabetic characters are made
        // lower-case.  A word is any string separated by whitespace
        // (you can use the isspace() function to determine if a character
        // is whitespace).

    // The firstToken and nextToken functions are used to break a
    // string into separate tokens.  The boundaryChars argument is
    // a string containing all characters that act as dividers between
    // tokens.  Both functions return a zero-length string when there are
    
	String FirstToken(const char* boundaryChars) const; //const String& boundaryChars) const;
        // makes a hidden copy of the host object and returns another
        // String object containing the first token in the host object.
    static String NextToken(const char* boundaryChars); //const String& boundaryChars);
        // Working with the hidden string copy created by firstToken,
        // returns the next token in the string.  Returns an empty
        // (zero-length) string when there are no more tokens.
private:
	String::String(char*, bool);
    char* _chars;
    static char* _tokenStr;
};

inline std::ostream& operator << (std::ostream& os, const String& s) {
    os << s.Chars();
    return(os);
}

// The input operator reads an entire line (without the terminating
// newline) from the istream "is".
inline std::istream& operator >> (std::istream& is, String& s) {
    char buf[1024];
    //is.getline(buf, 1023, '\n');
    is >> buf;
    s = buf;
    return(is);
}

inline String Spaces(int n) { return String(' ', n); }
inline int Len(const String& s) { return s.Length(); }
inline String Upper(String s) { s.Upper(); return s; }
inline String Lower(String s) { s.Lower(); return s; }

#endif 
