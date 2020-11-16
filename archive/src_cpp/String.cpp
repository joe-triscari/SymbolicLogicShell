#include "String.h"

//
// Non-member functions.
//
inline char* strdup(const char* str) {
    char* str2 = new char[strlen(str) + 1];
    strcpy(str2, str);
    return str2;
}

bool IsNumeric(const String& s)
{
	int iLen=s.Length(), iCnt=0;
	for(int i=0; i < iLen; ++i)
		if(s._chars[i] == '.') iCnt++;
		else if(!isdigit(s._chars[i])) return false;

	return iCnt <= 1 && iLen > 0;
}

bool IsAlpha(const String& s)
{
	int iLen = s.Length();
	for(int i=0; i < iLen; ++i)
		if(!isalpha(s._chars[i])) return false;
	return true;
}

String Reverse(const String& s)
{
	int i=0, j=0, iLen=strlen(s._chars);

	String sRev(new char[iLen + 1], false);
	for(j = iLen-1; j >= 0; --j)
		sRev._chars[i++] = s._chars[j];
	
	sRev._chars[i] = '\0';

	return sRev;
}

//
// Member functions.
//
String::String() {
    _chars = strdup("");
}

String::String(const char* str) {
    _chars = strdup(str);
}

String::String(char* str, bool bCopy)
{
	if(bCopy) _chars = strdup(str);
	else _chars = str;
}

String::String(const String& s) {
    _chars = strdup(s._chars);
}

String::String(char c, unsigned int len)
{
	_chars = new char[len+1];
	memset(_chars, c, len);
	_chars[len] = '\0';
}

String::String(char c)
{
	_chars = new char[2];
	_chars[0] = c;
	_chars[1] = '\0';
}

String::String(long l)
{
	char aczBuf[32]={'\0'};

	sprintf(aczBuf, "%ld", l);

	_chars = strdup(aczBuf);
}

String::String(int i)
{
	char aczBuf[32]={'\0'};

	sprintf(aczBuf, "%ld", i);

	_chars = strdup(aczBuf);
}

String::String(double d)
{
	char aczBuf[128]={'\0'};

	sprintf(aczBuf, "%f", d);

	_chars = strdup(aczBuf);
}

String::String(float f)
{
	char aczBuf[128]={'\0'};

	sprintf(aczBuf, "%f", f);

	_chars = strdup(aczBuf);
}


String::~String() { if(_chars) delete [] _chars; }


char& String::operator[] (unsigned int i) const {
    if (i >= Length()) {
		std::cerr << "Internal error: invalid index for String::operator[]\n";
        exit(1);
    }
    return _chars[i];
}

String String::operator() (unsigned int iIdx, unsigned int iLen) const {

	unsigned int iStrLen = Length();
	if(iIdx < 0 || iIdx > iStrLen-1) return String();

	if(iLen == 0 || iIdx + iLen > iStrLen)
		iLen = iStrLen - iIdx;

	String str(new char[iLen + 1], false);
	strncpy(str._chars, &_chars[iIdx], iLen);
	str._chars[iLen] = '\0';

	return str;
}

String& String::operator=(const String& s) {
    if (&s != this) {
        delete [] _chars;
        _chars = strdup(s._chars);
    }
    return *this;
}


String String::operator+(const String& s) const {
	String str(new char[Length() + s.Length() + 1], false);

    strcpy(str._chars, _chars);
    strcat(str._chars, s._chars);
   
    return str;
}

String& String::operator+=(const String& s) {
    char* tempPtr = _chars;

    _chars = new char[Length() + s.Length() + 1];
    strcpy(_chars, tempPtr);
    strcat(_chars, s._chars);
    delete [] tempPtr;

    return *this;
}

void String::TrimLeft(char c) {
    if(*_chars == '\0') return;

    int iIdx=0;
    for(int i=0; _chars[i]==c && _chars[i]!='\0'; i++) iIdx++;

    if(iIdx > 0)
    {
	   char* ptr = strdup(&_chars[iIdx]);
       delete [] _chars;
       _chars = ptr;
    }
}

void String::TrimRight(char c) {
    if(*_chars == '\0') return;

    int iLen=Length(), i=0;

    for(i=iLen-1; i >= 0 && _chars[i]==c; i--)
        _chars[i] = '\0';

    if(i < iLen-1)
    {
	   char* ptr = strdup(_chars);
       delete [] _chars;
       _chars = ptr;
    }
}


void String::Format(const char* format, ...)  {
    va_list ap;
    va_start(ap, format);

    char buff[FORMAT_BUFF_SIZE];
    int len = vsprintf(buff, format, ap);

    va_end(ap);
  
    delete [] _chars;
    _chars = new char[len + 1];
    strcpy(_chars, buff);
}


bool String::StartsWith(const char* s) const {
    return strstr(_chars, s) == _chars;
}

bool String::EndsWith(const char* s) const {
    int i = Length() - 1;
    int j = strlen(s) - 1;

    // if s is longer than the host, then the host cannot end with s
    if(j > i) return false;

    for(; j >= 0; i--, j--)
        if(_chars[i] != s[j])
            return false;

    return true;
}

/*
bool String::Contains(const String& s) const {
    return strstr(_chars, s._chars) != NULL;
}

int String::InStr(const char c) const {
	unsigned int iLen=Length();
	for(unsigned int i=0; i < iLen; ++i)
		if(c == _chars[i]) return i;

	return -1;
}
*/
int String::Replace(char c1, char c2)
{
   unsigned int iCount=0, iLen=Length();
   for(unsigned int i=0; i < iLen; ++i)
      if(_chars[i] == c1) 
          { _chars[i] = c2; ++iCount; }

   return iCount;
}

bool String::Replace(int iStrt, int iLen, const char* sczRepl)//const String& sRepl)
{
	if(iStrt < 0 || iLen < 0) false;
	
	int iStrLen = strlen(_chars);

	if(iStrt > iStrLen-1) 
	{
		iStrt = iStrLen;
		iLen = 0;
	}
	if(iStrt + iLen > iStrLen) iLen = iStrLen - iStrt;

	char* newChars = new char[iStrLen - iLen + strlen(sczRepl)/*strlen(sRepl._chars)*/ + 1];
	newChars[0] = '\0';

	strncat(newChars, _chars, iStrt);
	strcat(newChars, sczRepl); //sRepl._chars);
	strcat(newChars, &_chars[iStrt+iLen]);

	delete [] _chars;
	_chars = newChars;

	return true;
}

int String::Pos(const char* str, int iStrt) const
{
	int iLen=Length();
	char* ptr= nullptr;

	if(iStrt < 0 || iStrt > iLen-1) return -1;

	ptr = strstr(&_chars[iStrt], str);
	if(!ptr) return -1;

	return (ptr - _chars) / sizeof(char);
}

String String::Right(int n) const
{
	if(n < 1) return String();

	int iLen=Length();
	if(n > iLen) n = iLen;

	String str(new char[n + 1], false);
	strcpy(str._chars, &_chars[iLen - n]);

	return str;
}

String String::Left(int n) const
{
	if(n < 1) return String();

	int iLen=Length();
	if(n > iLen) n = iLen;

	String str(new char[n + 1], false);
	strncpy(str._chars, _chars, n);
	str._chars[n] = '\0';

	return str;
}

int String::RemoveChar(const char c)
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

void String::Upper() {
    for (char *cp = _chars; *cp != '\0'; cp++)
        *cp = toupper(*cp);
}

void String::Lower() {
    for (char *cp = _chars; *cp != '\0'; cp++)
        *cp = tolower(*cp);
}

void String::Capitalize() {
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

char* String::_tokenStr = nullptr;

String String::FirstToken(const char* boundaryChars) const {
    if(_tokenStr != nullptr) delete [] _tokenStr;
    _tokenStr = strdup(_chars);
    
	char* result = strtok(_tokenStr, boundaryChars);
    if (result == nullptr)
        return String("");
    else
        return String(result);
}

String String::NextToken(const char* boundaryChars) {
    char* result = strtok(nullptr, boundaryChars);
    if (result == nullptr)
        return String("");
    else
        return String(result);
}

String operator+(const char c, const String& str) {
	String sTmp(new char[str.Length() + 2], false);
   
	sTmp._chars[0] = c;
	strcpy(&sTmp._chars[1], str._chars);

	return sTmp;
}

String operator+(const char* LHS, const String& RHS) {
	String sTmp(new char[strlen(LHS) + RHS.Length() + 1], false);

	strcpy(sTmp._chars, LHS);
	strcat(sTmp._chars, RHS._chars);

	return sTmp;
} 
