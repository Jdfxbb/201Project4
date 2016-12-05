/*********************************************

Name: Joshua Ford
Course: CS 201R
Program: Program 4 Library Users
Due Date: 20 March 2016
Description: Process a database of library users and handle checkins and checkouts.
Inputs:	users.txt, checkins.txt, checkouts.txt
Outputs: Users2.txt
Algorithm:
1. While reading Users.txt
	a. Add user ID and name to dynamic user array
	b. add books to user's book array
	c. move to next spot in array
2. While reading checkouts.txt
	a. find user in array
	b. add book to user's book array
3. While reading checkins.txt
	a. find user with book checked out
	b. remove book from user's array
4. Write User information and list of books to Users2.txt

*********************************************/

#include <iostream>
#include <fstream>
#include "User.h"
using namespace std;

// prototype for dynamic array expansion
unsigned int expandArray(User* &arr, unsigned int arrSize);

void main()
{
	// open input
	ifstream fin;
	fin.open("users.txt");

	// array variables
	unsigned int n = 0; // after userArr is created, n will represent end of array
	unsigned int arrSize = 2;

	// temp variables
	unsigned int IDNum;
	string ItemNum;
	
	// dynamic array
	User* UserArr = new User[arrSize];

	// get first user
	fin >> UserArr[n];

	// continue reading to eof
	while (fin.good())
	{
		n++;

		// check array size after incrementing n
		if (n == arrSize)
			arrSize = expandArray(UserArr, arrSize);

		// get next user 
		fin >> UserArr[n];
	}
	
	// close and open next file
	fin.close();
	fin.open("checkouts.txt");

	// get first pair 
	fin >> IDNum >> ItemNum;

	while (fin.good())
	{
		// attempt to find user
		try
		{
			unsigned int i = 0;
			while (i != n - 1)
			{
				if (IDNum == UserArr[i].GetIDNumber())
				{
					UserArr[i].CheckOut(ItemNum);
					break;
				}
				i++;
				if (i == n - 1 && IDNum != UserArr[i].GetIDNumber())
					throw UserException("No user can be found with this ID number: ");
			}
		}
		catch (UserException e)
		{
			cerr << e.what() << IDNum << "\n";
		}

		// get next pair
		fin >> IDNum >> ItemNum;
	}

	// close and open next file
	fin.close();
	fin.open("checkins.txt");

	// get first item
	fin >> ItemNum;

	while (fin.good())
	{
		unsigned int i = 0; // for iterating
		int checkinCount = 0; // for checking multiple checkouts
		unsigned int firstUser = 0; // remember first user in cases of multiple checkouts

		// try to find user
		try
		{
			while (i != n - 1)
			{
				// check multiple checkouts condition
				try
				{
					if (UserArr[i].HasCheckedOut(ItemNum))
					{
						checkinCount++;

						// check if more than one user with same book
						if (checkinCount > 1)
						{
							throw UserException(" is checked out by more than one user : ");
						}

						// remember first user and check in book
						if (firstUser == 0)
							firstUser = i;
						UserArr[i].CheckIn(ItemNum);
					}
				}
				catch (UserException e)
				{
					// output item number and error
					cerr << ItemNum << e.what() << "\n";

					// output first user at top of list
					cerr << UserArr[firstUser].GetIDNumber() << "\n";

					// find rest of users with book checked out
					for (unsigned int i = 0; i < n - 1; i++)
					{
						if (UserArr[i].HasCheckedOut(ItemNum))
						{
							cerr << UserArr[i].GetIDNumber() << "\n";
							UserArr[i].CheckIn(ItemNum);
						}
					}
				}
				i++;

				// if we're checking the last user in UserArr and no user has checked in the book yet
				if (i == n - 1 && !UserArr[i].HasCheckedOut(ItemNum) && checkinCount == 0)
					throw UserException("No user can be found with this item checked out: ");
			}
		}
		catch (UserException e)
		{
			cerr << e.what() << ItemNum << "\n";
		}

		// get next item to be checked in
		fin >> ItemNum;
	}

	// close file
	fin.close();

	try
	{
		// create output stream
		ofstream fout;
		fout.open("Users2.txt");

		// output list of users and checked out books
		for (unsigned int i = 0; i < n - 1; i++)
			fout << UserArr[i];
		fout.close();
	}
	catch (UserException e)
	{
		cerr << e.what() << "\n";
	}

}

unsigned int expandArray(User* &arr, unsigned int arrSize)
{
	unsigned int newSize = arrSize * 2;
	User* newArr = new User[newSize];

	// copy old array
	for (unsigned int x = 0; x < arrSize; x++)
		newArr[x] = arr[x];

	// delete old array
	delete[] arr;
	arr = newArr;

	return newSize;
}