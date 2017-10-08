#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <new>

enum STACK_ERRORS {
	CAPACITY_SIZE_ERR = 1,
	NO_STACK_ERR = 2,
	WR_CAPACITY_ERR = 3,
	WR_SIZE_ERR = 4,
	NO_CAPACITY_ERR = 5
};

class Stack {
private:
	double * data_;
	size_t size_;
	size_t capacity_;
	size_t last_error_;
	bool Ok();
	bool Empty();
public:
	FILE* file_dump;
	void Dump(FILE* file_dump);
	void Push (double value);
	double Pop();
	void Clear();
	int Size();
	int Capacity();
	void PrintError();
	Stack(size_t size);
	Stack (const Stack& that);
	~Stack();
	size_t CheckErrors();
};

#include "Stack.cpp"  
#include "ASM.cpp"
#include "CPU.cpp"


#endif