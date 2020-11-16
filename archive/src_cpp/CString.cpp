/*********************************************************/
/****  CString.cc                                     ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class implementation  ****/
/****    for CString.                                 ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#include <ctype.h>
#include <string.h>
#include "CString.h"

inline char* strdup(const char* str) {
    char* str2 = new char[strlen(str) + 1];
    strcpy(str2, str);
    return(str2);
}

CString spaces(unsigned int len) {
  char * s = new char[len+1];
  if(!s)
    return CString("");

  memset(s, ' ', len);
  s[len] = '\0';
  CString tmp(s);
  delete [] s;

  return tmp;
}

CString str(char c, unsigned int len) {
  char * s = new char[len+1];
  if(!s)
    return CString("");

  memset(s, c, len);
  s[len] = '\0';
  CString tmp(s);
  delete [] s;

  return tmp;
}

unsigned int len(CString s)
{
   return s.length();
}

CString::CString() {
    _chars = strdup("");
}

CString::CString(const char* str) {
    _chars = strdup(str);
}

CString::CString(const CString& s) {
    _chars = strdup(s._chars);
}

CString::~CString() { if(_chars) delete [] _chars; }

unsigned int CString::length() const {
    return(strlen(_chars));
}

char* CString::chars() const {
    return (_chars);
}

char& CString::operator[] (unsigned int i) const {
    if (i >= length()) {
        cerr << "Internal error: invalid index for CString::operator[]\n";
        exit(1);
    }
    return(_chars[i]);
}

CString CString::operator() (int index, int len) const {
  CString temp;
  char *s;

  if(index < 0 || index > length()-1)
    return temp;

  if(len == 0 || index + len > length())
    len = length() - index;

  s = new char[len + 1];
  strncpy(s, &_chars[index], len);
  s[len] = '\0';

  temp = s;
  delete [] s;

  return temp;
}

CString& CString::operator = (const CString& s) {
    if (&s != this) {
        delete [] _chars;
        _chars = strdup(s._chars);
    }
    return(*this);
}

CString& CString::operator = (const char * str) {
    delete [] _chars;
    _chars = strdup(str);
    return(*this);
}

CString& CString::operator = (const char c) {
   delete [] _chars;
   _chars = new char[2];
   _chars[0] = c;
   _chars[1] = '\0';
   return(*this);
}
  
CString CString::operator + (const CString& s) const {
    char* temp = new char[length() + s.length() + 1];
    strcpy(temp,_chars);
    strcat(temp, s._chars);
    CString s2(temp);
    delete [] temp;
    return(s2);
}

CString CString::operator + (const char * str) const {
    char* temp = new char[length() + strlen(str) + 1];
    strcpy(temp,_chars);
    strcat(temp, str);
    CString s2(temp);
    delete [] temp;
    return(s2);

}
CString CString::operator + (char c) const {
    unsigned int len = length();
    char* temp = new char[len + 2];
    strcpy(temp,_chars);
    temp[len] = c;
    temp[len+1] = '\0';
    CString s2(temp);
    delete [] temp;

    return(s2);

}
CString& CString::operator+=(const CString &right) {
    char *tempPtr = _chars;

    int len = length() + right.length();
    _chars = new char[len + 1];
    strcpy(_chars, tempPtr);
    strcat(_chars, right.chars());
    delete [] tempPtr;

    return(*this);
}

void CString::trimLeft() {
    if(*_chars == '\0') return;

    int index=0;
    char* ptr = strdup(_chars);

    for(register int ii=0; (ptr[ii] == ' ' || ptr[ii] == '\t') && ptr[ii] !=
'\0'; ii++)
        index++;

    if(index > 0)
    {
       delete [] _chars;
       _chars = strdup(&ptr[index]);
    }
    delete [] ptr;
}

void CString::trimRight() {
    if(*_chars == '\0') return;

    int len = length();
    register int ii;
    char* ptr = strdup(_chars);

    for(ii=len-1; ii >= 0 && (ptr[ii] == ' ' || ptr[ii] == '\t'); ii--)
        ptr[ii] = '\0';

    if(ii < len-1)
    {
       delete [] _chars;
       _chars = strdup(ptr);
    }
    delete [] ptr;
}

void CString::trim() {
    trimLeft();
    trimRight();
}

void CString::format(const char* format, ...)  {
    va_list ap;
    va_start(ap, format);

    char buff[FORMAT_BUFF_SIZE];
    int len = vsprintf(buff, format, ap);

    va_end(ap);
  
    delete [] _chars;
    _chars = new char[len + 1];
    strcpy(_chars, buff);
}
        
int CString::compare (const CString& s) const {
    int result = strcmp(_chars, s._chars);
    if (result < 0) return (-1);
    else if ( result > 0) return(1);
    else return(0);
}

short CString::operator == (const CString& s) const {
    return(compare(s) == 0);
}

short CString::operator != (const CString& s) const {
    return(compare(s) != 0);
}

short CString::operator < (const CString& s) const {
  return(compare(s) == -1);
}

short CString::operator <= (const CString& s) const {
  return(compare(s) <= 0);
}

short CString::operator > (const CString& s) const {
  return(compare(s) == 1);
}

short CString::operator >= (const CString& s) const {
  return(compare(s) >= 0);
}

short CString::startsWith(const CString& s) const {
    char* match = strstr(_chars,s._chars);
    return (match == _chars);
}

short CString::endsWith(const CString& s) const {
    int i = length() - 1;
    int j = s.length() - 1;

    // if s is longer than the host, then the host cannot end with s
    if (j > i)
        return (0);

    for (; j >= 0 ; i--, j--)

        if (_chars[i] != s._chars[j])
            return(0);

    return(1);
}

short CString::contains(const CString& s) const {
    return(strstr(_chars,s._chars) != NULL);
}

int CString::inStr(const char c) const {
   for(int i=0; i<length(); i++)
      if(c == _chars[i]) return i;

   return -1;
}

int CString::replace(char c1, char c2)
{
   int iCount=0;
   for(int i=0; i<length(); i++)
      if(_chars[i] == c1) 
          { _chars[i] = c2; ++iCount; }

   return iCount;
}

int CString::removeChar(const char c)
{
   char * ptr = strdup(_chars);
   int i,j,len=strlen(_chars);
   int iFnd=-1;

   for(i=j=0; i<len; i++)
     if(_chars[i] != c) 
       { ptr[j] = _chars[i]; j++; }
     else iFnd=1;

   ptr[j] = '\0';

   delete [] _chars;
   _chars = strdup(ptr);
   delete [] ptr;

   return iFnd;
}

void CString::upcase() {
    for (char *cp = _chars; *cp != '\0'; cp++)
        if (islower(*cp)) *cp = toupper(*cp);
}

void CString::downcase() {
    for (char *cp = _chars; *cp != '\0'; cp++)
        if (isupper(*cp)) *cp = tolower(*cp);
}

void CString::capitalize() {
    if (*_chars == '\0')
        return;
    char* cp = _chars;
    short wordStart = 1;
    while (*cp != '\0') {
        if (isspace(*cp))
            wordStart = 1;
        else {
            if ((wordStart == 1) && islower(*cp)) {
                *cp = toupper(*cp);
            }
            else if ((wordStart == 0) && isupper(*cp))
                *cp = tolower(*cp);
            wordStart = 0;
        }
        cp++;
    }
}

char* CString::_tokenStr = NULL;

CString CString::firstToken(const CString& boundaryChars) const {
    if (_tokenStr != NULL)
        delete [] _tokenStr;
    _tokenStr = strdup(_chars);
    char* result = strtok(_tokenStr, boundaryChars._chars);
    if (result == NULL)
        return CString("");
    else
        return CString(result);
}

CString CString::nextToken(const CString& boundaryChars) {
    char* result = strtok(NULL, boundaryChars._chars);
    if (result == NULL)
        return CString("");
    else
        return CString(result);
}

CString operator+(const char c, const CString& str) {
   char* s = new char[str.length() + 2];
   
   s[0] = c;
   strcpy(&s[1], str.chars());
    
   CString tmp(s);
   delete [] s;

   return(tmp);
}

CString operator+(const char* LHS, const CString& RHS) {
   char* s = new char[strlen(LHS) + RHS.length() + 1];

   strcpy(s, LHS);
   strcat(s, (char*)RHS);

   CString tmp(s);
   delete [] s;

   return(tmp);
} 
