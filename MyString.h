//code by Angel Dimitriev: https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2009/MyString%20(with%20move)/MyString.h
//changes made - added functions for writing and reading in binary files


#pragma once
#include <iostream>
#include <fstream>

class MyString
{
	char* _data;
	size_t _length;

	void copyFrom(const MyString& data);
	void free();

	explicit MyString(size_t capacity); //for memory allocation. How much bytes to allocate
public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	size_t length() const;
	MyString& operator+=(const MyString& other);

	MyString substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream&, MyString& str);

	std::ofstream& writeString(std::ofstream& output) const; //writes string into binary file
	std::ifstream& readString(std::ifstream& input); //reads a string from binary file
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);

