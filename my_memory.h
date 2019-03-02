/* Steven Santana CSCI 335 */
#ifndef MY_MEMORY_H
#define MY_MEMORY_H

/** Notes
	* Due to the challenges presented by seperating the declaration 
		and implementation of a template class, I've had to explicitly
		declare what data types will use the class in the implementation
		file. 
**/

/** Bugs
	* Both pointer acquisition constructors are likely affected
		by the same issue, that the pointer brought into the
		function is a mere copy, and not actually the pointer
		itself. Therefore, cannot set passed in pointer to nullptr.
**/

template<class T>
class UPtr
{
	private:
	T* mem_ptr; 
	
	public:
	
	// Default constructor
	UPtr();
	
	// Pointer Acquisition Constructor
	UPtr(T* new_ptr); 
	
	// Move Constructor
	UPtr(UPtr<T> &&rhs); 
	
	// Copy Constr dead.
	UPtr(const UPtr<T>&) = delete;
	
	//Destructor
	~UPtr(); 
	
	// Dereference Operator
	T& operator* (); 
	
	// -> Operator
	T* operator->();
	
	// Move Assignment Operator
	UPtr<T>& operator=(UPtr<T> &&rhs);

	// Copy Assignment Operator REMOVE
	UPtr<T>& operator=(const UPtr<T> &nUPtr) = delete;
};

template<class T>
class SPtr
{
	private:
		T* mem_ptr;
		int* count; 
		
	// Deletes Pointer Memory
	void deleter();
	
	public:
	
	// Default Constructor
	SPtr();
	
	// Pointer Acquisition Constructor
	SPtr(T* new_mem); =
	
	// Copy Constructor
	SPtr(const SPtr &rhs);
	
	// Move Constructor
	SPtr(SPtr &&rhs); 
	
	// Destructor
	~SPtr();
	
	// Dereference Operator
	T& operator*(); 

	// -> Operator
	T* operator->();
	
	// Copy Assignment Operator
	SPtr<T>& operator=(const SPtr &rhs); 
	
	// Move Assignment Operator
	SPtr<T>& operator=(SPtr &&rhs);  

};


//#include "my_memory.cpp"
#endif