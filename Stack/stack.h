#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <new>
#include <vector>
#include <math.h>

size_t MAX_STACK_CAPACITY = 10000;
size_t MIN_STACK_CAPACITY = 2;
float SIZE_INC = 1.5;
unsigned int SEED = 42;


int CANARY_1 = rand_r(&SEED);
int CANARY_2 = rand_r(&SEED);
int CANARY_3 = rand_r(&SEED);
int CANARY_4 = rand_r(&SEED);

enum STACK_ERRORS {
	CAPACITY_SIZE_ERR = 1,
	NO_STACK_ERR = 2,
	WR_CAPACITY_ERR = 3,
	WR_SIZE_ERR = 4,
	NO_CAPACITY_ERR = 5,
	CANARY_1_ERR = 6,
	CANARY_2_ERR = 7,
	CANARY_3_ERR = 8,
	CANARY_4_ERR = 9
};

class Stack {
private:
	int canary_1;
	int canary_2;
	std::vector<double> data_;
	int canary_3;
	size_t size_;
	size_t capacity_;
	size_t last_error_;
	bool Ok();
	void Dump();
	bool Empty();
	void Increase();
	int canary_4;
public:
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

#include "stack.cpp"  
