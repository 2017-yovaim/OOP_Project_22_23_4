//note - also used in my third homework

#pragma once
#include <iostream>
#include "GlobalConstants.h"



namespace
{
	template <typename T>
	void swapT(T& lhs, T& rhs)
	{
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}


template <typename T>
class MyVector
{
private:
	T* data;
	unsigned size = 0;
	unsigned capacity = 0;

	void copyFrom(const MyVector<T>& other);
	void moveFrom(MyVector<T>&& other);
	void free();
	void resize();


public:
	MyVector();
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other);
	~MyVector();


	unsigned getSize() const;
	void push_back(const T& el);
	void push_back(T&& el);
	void insert(const T& el, unsigned index);
	void insert(T&& el, unsigned index);
	void pop_back(); //deletes last element
	void erase(unsigned index);
	void clear(); //erases all data in the vector
	bool isEmpty() const;

	bool contains(const T& el) const; //checks if an element is present in the vector
	int getIndex(const T& el) const; //returns index if el is in the vector or -1 if it isn't

	const T& operator[](unsigned index) const;
	T& operator[](unsigned index);

};

template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	this->data = new T[other.capacity];
	for (unsigned i = 0; i < other.size; i++)
	{
		this->data[i] = other.data[i];
	}
	this->size = other.size;
	this->capacity = other.capacity;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	delete[] this->data;
	this->data = other.data;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
void MyVector<T>::free()
{
	delete[] this->data;
	this->data = nullptr;
	this->size = this->capacity = 0;
}

template <typename T>
void MyVector<T>::resize()
{
	T* newData = new T[this->capacity * 2];
	for (unsigned i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity *= 2;
}

template <typename T>
MyVector<T>::MyVector()
{
	this->capacity = DEFAULT_VECTOR_CAPACITY;
	this->data = new T[this->capacity];
	this->size = 0;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	this->copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	this->moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		this->free();
		this->copyFrom(other);
	}

	return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != &other)
	{
		this->free();
		this->moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
	this->free();
}

template <typename T>
unsigned MyVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
void MyVector<T>::push_back(const T& el)
{
	if (this->size == this->capacity)
		this->resize();

	this->data[size++] = el;
}

template <typename T>
void MyVector<T>::push_back(T&& el)
{
	if (this->size == this->capacity)
		this->resize();

	this->data[size++] = std::move(el);
}

template <typename T>
void MyVector<T>::insert(const T& el, unsigned index)
{

	if (index >= this->capacity)
		throw std::invalid_argument("could not insert - no such index");

	if (this->size == this->capacity)
		this->resize();

	this->data[size] = el;
	swapT(this->data[size], this->data[index]);
	this->size++;
}

template <typename T>
void MyVector<T>::insert(T&& el, unsigned index)
{
	if (index >= this->capacity)
		throw std::invalid_argument("could not insert - no such index");


	if (this->size == this->capacity)
		this->resize();

	this->data[size] = std::move(el);
	swapT(this->data[size], this->data[index]);
	this->size++;
}

template <typename T>
void MyVector<T>::pop_back()
{
	this->size--;
}

template <typename T>
void MyVector<T>::erase(unsigned index)
{
	if (index >= this->size)
		throw std::invalid_argument("Could not erase - no element at the index");

	swapT(this->data[size - 1], this->data[index]);
	this->size--;
}

template <typename T>
void MyVector<T>::clear()
{
	delete[] this->data;
	this->data = new T[DEFAULT_VECTOR_CAPACITY];
	this->capacity = DEFAULT_VECTOR_CAPACITY;
	this->size = 0;
}

template <typename T>
bool MyVector<T>::isEmpty() const
{
	return this->size == 0;
}

template<typename T>
bool MyVector<T>::contains(const T& el) const
{
	if (this->isEmpty())
		return false;

	for (unsigned i = 0; i < this->size; i++)
	{
		if (this->data[i] == el)
			return true;
	}

	return false;
}

template <typename T>
int MyVector<T>::getIndex(const T& el) const
{
	if (this->isEmpty())
	{
		return INVALID_INDEX;
	}

	for (size_t i = 0; i < this->size; i++)
	{
		if (this->data[i] == el)
			return i;
	}

	return INVALID_INDEX;
}

template <typename T>
const T& MyVector<T>::operator[](unsigned index) const
{
	if (index >= this->size)
		throw std::invalid_argument("wrong index in []");

	return this->data[index];
}

template <typename T>
T& MyVector<T>::operator[](unsigned index)
{
	if (index >= this->size)
		throw std::invalid_argument("wrong index in []");

	return this->data[index];
}
