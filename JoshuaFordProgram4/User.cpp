#include "User.h"

User::User() // default
{
	ID = 0;
	first = "";
	last = "";
	arr = nullptr;
}

User::User(unsigned int inID, string inLast, string inFirst)
{
	ID = inID;
	first = inFirst;
	last = inLast;
	arr = nullptr;
}

User::~User() // destructor
{
	if (arr != nullptr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

const User& User::operator = (const User& rhs) // copy
{
	// avoid self assignment
	if (this != &rhs)
	{
		// clean dynamic array
		if (arr != nullptr)
		{
			delete[] arr;
			arr = nullptr;
		}

		// copy static variables
		ID = rhs.ID;
		first = rhs.first;
		last = rhs.last;
		arrSize = rhs.arrSize;
		booksOut = rhs.booksOut;

		// copy dynamic data
		if (arrSize > 0)
		{
			arr = new string[arrSize];
			for (unsigned int i = 0; i < booksOut; i++)
			{
				arr[i] = rhs.arr[i];
			}
		}
	}
	return *this;
}

// getters
int User::GetIDNumber() const
{
	return ID;
}

string User::GetFirstName() const
{
	return first;
}

string User::GetLastName() const
{
	return last;
}

string User::GetFullName() const
{
	return last +  ", " + first;
}

// settters
void User::SetIDNumber(unsigned int NewNumber)
{
	// check ID parameters, ignore if out of bounds
	if (NewNumber < 1000000 && NewNumber >= 100)
		ID = NewNumber;
}

void User::SetFirstName(string NewFirst)
{
	first = NewFirst;
}

void User::SetLastName(string NewLast)
{
	last = NewLast;
}

// functions
int User::CheckoutCount() const
{
	return booksOut;
}

bool User::CheckOut(const string& BookIDCode)
{
	// check if memory allocated
	if (arr == nullptr)
	{
		arr = new string[5];
		arrSize = 5;
	}

	// check if array is full
	else if (booksOut == arrSize)
	{
		try
		{
			ResizeArray();
		}
		catch (UserException e)
		{
			cerr << e.what() << ID << "\n";
			return false;
		}
	}

	try
	{
		// check if book already checked out
		for (unsigned int i = 0; i < booksOut; i++)
		{
			if (arr[i] == BookIDCode)
				throw UserException(" has already checked out item: ");
		}
	}
	catch (UserException e)
	{
		cerr << ID << e.what() << BookIDCode << "\n";
		return false;
	}

	// add book to array
	arr[booksOut] = BookIDCode;
	booksOut++;

	return true;
}

bool User::CheckIn(const string& BookIDCode)
{
	for (unsigned int i = 0; i < booksOut; i++)
	{
		// find book
		if (arr[i] == BookIDCode)
		{
			// move last book in array to location. clear last spot
			arr[i] = arr[booksOut - 1];
			arr[booksOut - 1] = "";
			booksOut--;

			// check if array is empty
			if (booksOut == 0)
			{
				delete[] arr;
				arr = nullptr;
			}
			return true;
		}
	}
	return false;
}

bool User::HasCheckedOut(const string& BookIDCode) const
{
	for (unsigned int i = 0; i < booksOut; i++)
	{
		if (arr[i] == BookIDCode)
			return true;
	}
	return false;
}

void User::Clear()
{
	ID = 0;
	first = "";
	last = "";
	booksOut = 0;
	arrSize = 0;
	if (arr != nullptr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

bool User::ResizeArray()
{
	// double array size
	arrSize *= 2;

	try
	{
		//create new temp array
		string* newArr = new string[arrSize];

		// copy array
		for (unsigned int i = 0; i < arrSize / 2; i++)
			newArr[i] = arr[i];

		// delete old array
		delete[] arr;

		// reassign pointer
		arr = newArr;
	}
	catch (...)
	{
		throw UserException("Array could not be resized for user: ");
	}
	return true;
}

const User User::operator + (const string& rhs) const
{
	// create new user with book checked out
	User newUser(ID, last, first);
	newUser.CheckOut(rhs);
	return newUser;
}

void User::operator += (const string& rhs)
{
	User::CheckOut(rhs);
}

bool User::operator == (const User& rhs) const
{
	return ID == rhs.GetIDNumber();
}

bool User::operator != (const User& rhs) const
{
	return ID != rhs.GetIDNumber();
}

void operator << (ostream& out, const User& rhs)
{
	if (out.fail())
		throw UserException("output failed");

	// output to ostream in format
	// ID First Last
	// # of books checkout out
	// book codes if any
	out << rhs.ID << " " << rhs.first << " " << rhs.last << '\n';
	out << rhs.booksOut << '\n';
	if (rhs.booksOut > 0)
	{
		for (unsigned int i = 0; i < rhs.booksOut; i++)
			out << rhs.arr[i] << " ";
		out << '\n';
	}
}

void operator >> (istream& in, User& rhs)
{
	if (in.fail())
		throw UserException("input failed");

	// make sure rhs is empty User
	rhs.Clear();

	// set data
	in >> rhs.ID >> rhs.first >> rhs.last >> rhs.booksOut;

	// if User has books checked out, read them in
	if (rhs.booksOut > 0)
	{
		rhs.arr = new string[rhs.booksOut];
		rhs.arrSize = rhs.booksOut;
		for (unsigned int i = 0; i < rhs.booksOut; i++)
		{
			in >> rhs.arr[i];
		}
	}
}