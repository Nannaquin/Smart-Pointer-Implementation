/* Steven Santana CSCI 335 */
#include "my_memory.h"
#include <utility>
#include <iostream>
//using namespace std;

/** See header file for notes and bugs. */


/** ************** ***
    Unique Pointer 
*** ************** **/

// Default Constructor
template<class T>
UPtr<T>::UPtr(): mem_ptr(nullptr) { }

// Pointer acquisition Constructor
/** It copies the pointer instead of actually
passing the address. Its the only way it will
compile. Have tried T**, T*&, and T& to no avail.
Hence, it doesnt actually takes ownership entirely. */
template<class T>
UPtr<T>::UPtr(T* new_ptr): mem_ptr(new_ptr) 
{	
	new_ptr = nullptr;
	if(new_ptr != nullptr) std::cerr << "ERROR\n";
}
// Move Constructor
template<class T>
UPtr<T>::UPtr(UPtr<T> &&rhs):mem_ptr(rhs.mem_ptr)
{
	rhs.mem_ptr = nullptr;	
}

// Destruct
template<class T>
UPtr<T>::~UPtr() 
{	
	if(mem_ptr != nullptr)
	{
		delete [] mem_ptr;
		mem_ptr = nullptr;
	}
}

// deref
template<class T>
T& UPtr<T>::operator*() { return *mem_ptr; }

// ->
template<class T>
T* UPtr<T>::operator->() { return mem_ptr; }

// move =
template<class T>
UPtr<T>& UPtr<T>::operator=(UPtr<T> &&rhs)
{
	swap(mem_ptr, rhs.mem_ptr);
	return *this;
}


/** ************** ***
    Shared Pointer 
*** ************** **/

// Default Constructor`
template<class T>
SPtr<T>::SPtr():mem_ptr(nullptr), count(new int {0}) { }

// Pointer Acquisition Constructor
template<class T>
SPtr<T>::SPtr(T* new_mem):mem_ptr(new_mem) 
{
	count = new int {1};
}

// Copy Constructor
template<class T>
SPtr<T>::SPtr(const SPtr<T> &rhs):mem_ptr(rhs.mem_ptr)
{
	count = rhs.count;
	*count+=1;
}

// Move constructor
template<class T>
SPtr<T>::SPtr(SPtr<T> &&rhs):mem_ptr(rhs.mem_ptr)
{
	count = rhs.count;
	rhs.mem_ptr = nullptr;
	rhs.count = nullptr;
}

// Destructor
template<class T>
SPtr<T>::~SPtr()
{
	
	if(count != nullptr)
	{
		*count-=1;
		if(*count <= 0)
		{
			deleter();
		}
	}
}

// Deref Op
template<class T>
T& SPtr<T>::operator*() { return *mem_ptr; }

// -> Op
template<class T>
T* SPtr<T>::operator->() { return mem_ptr; }

// Copy Assignment Op
template<class T>
SPtr<T>& SPtr<T>::operator=(const SPtr<T> &rhs)
{ 
	if(count != nullptr)
	{
		*count-=1;
		if(*count <= 0) deleter();
	}
	
	mem_ptr = rhs.mem_ptr;
	count = rhs.count;
	*count+= 1;
	
	return *this;
}

// Move Assignment Op
template<class T>
SPtr<T>& SPtr<T>::operator=(SPtr<T> &&rhs)
{
	if(count != nullptr)
	{
		*count-=1;
		if(*count <= 0) deleter();
	}
	
	swap(mem_ptr,rhs.mem_ptr);
	swap(count, rhs.count);
	return *this;
}

// Function that deletes the targets of both pointers.
/** Only called when deref'd count is actually zero or less */
template<class T>
void SPtr<T>::deleter()
{
	if(mem_ptr != nullptr)
	{
		delete mem_ptr;
		mem_ptr = nullptr;
	}
	if(count != nullptr)
	{
		delete count;
		count = nullptr;
	}
}

template class UPtr<int>;
template class SPtr<int>;