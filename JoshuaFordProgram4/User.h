#include <iostream>
#include <string>
using namespace std;

#ifndef _USER
#define _USER

class User
{
private:
	unsigned int ID;
	string first;
	string last;
	unsigned int booksOut;
	unsigned int arrSize = 0;
	string* arr;
	bool ResizeArray();

public:
	// constructor/destructor/copy
	User();

	User(unsigned int inID, string inLast, string inFirst);
	//PRE: int, string, string defined
	//POST: User created
	//RETURNS: None
	~User();
	//PRE: None
	//POST: User destroyed
	//RETURNS: None
	const User& operator = (const User& rhs);
	//PRE: another User object exists
	//POST: rhs is equal to User
	//RETURNS: pointer to this

	// getters
	int GetIDNumber() const;
	//PRE: None
	//POST: None
	//RETURNS: ID
	string GetFirstName() const;
	//PRE: None
	//POST: None
	//RETURNS: first
	string GetLastName() const;
	//PRE: None
	//POST: None
	//RETURNS: last
	string GetFullName() const;
	//PRE: None
	//POST: None
	//RETURNS: last ", " first

	//setters
	void SetIDNumber(unsigned int NewNumber);
	//PRE: unsigned int defined
	//POST: 
	//RETURNS: None
	void SetFirstName(string NewFirst);
	//PRE:
	//POST:
	//RETURNS: 
	void SetLastName(string NewLast);
	//PRE:
	//POST:
	//RETURNS: 

	// functions
	int CheckoutCount() const;
	//PRE:
	//POST:
	//RETURNS: 
	bool CheckOut(const string& BookIDCode);
	//PRE:
	//POST:
	//RETURNS: 
	bool CheckIn(const string& BookIDCode);
	//PRE:
	//POST:
	//RETURNS: 
	bool HasCheckedOut(const string& BookIDCode) const;
	//PRE:
	//POST:
	//RETURNS: 
	void Clear();
	//PRE:
	//POST:
	//RETURNS: 

	// overload 
	friend void operator << (ostream& out, const User& rhs);
	//PRE:
	//POST:
	//RETURNS: 
	friend void operator >> (istream& in, User& rhs);
	//PRE:
	//POST:
	//RETURNS: 
	const User operator+(const string& rhs) const;
	//PRE:
	//POST:
	//RETURNS: 
	void operator +=(const string& rhs);
	//PRE:
	//POST:
	//RETURNS: 
	bool operator ==(const User& rhs) const;
	//PRE:
	//POST:
	//RETURNS: 
	bool operator != (const User& rhs) const;
	//PRE:
	//POST:
	//RETURNS: 
};
#endif

// exception class
#ifndef _USEREXCEPTION
#define _USEREXCEPTION

class UserException
{
private:
	string errMsg;

public:
	UserException(){ errMsg = "exception in user class"; }
	//PRE:
	//POST:
	//RETURNS: 
	UserException(const string& error) { errMsg = error; }
	//PRE:
	//POST:
	//RETURNS: 
	const string what() { return errMsg; }
	//PRE:
	//POST:
	//RETURNS: 
};
#endif