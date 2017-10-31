#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <new>
#include <vector>
#include <math.h>

const int MAX_STACK_CAPACITY = 10000;
const int MIN_STACK_CAPACITY = 2;
const float SIZE_INC = 1.5;
unsigned int SEED = 42;


const int CANARY_1 = rand_r(&SEED);
const int CANARY_2 = rand_r(&SEED);
const int CANARY_3 = rand_r(&SEED);
const int CANARY_4 = rand_r(&SEED);

enum STACK_ERRORS {
        CAPACITY_SIZE_ERR = 1 << 0,
        NO_STACK_ERR = 1 << 1, 
        WR_CAPACITY_ERR = 1 << 2,
        WR_SIZE_ERR = 1 << 3,
        NO_CAPACITY_ERR = 1 << 4,
        CANARY_1_ERR = 1 << 5,
        CANARY_2_ERR = 1 << 6,
        CANARY_3_ERR = 1 << 7,
        CANARY_4_ERR = 1 << 8
};

class Stack {
private:
	int canary_1;
	double canary_2;
	std::vector<double> data_;
	double canary_3;
	int size_;
	int capacity_;
	int errors_;
	bool do_push;
	double push_value;
	char* var_name_;
	void PrintError();
	bool Ok() const;
	bool Empty();
	int canary_4;
public:
	void Push (double value);
	double Pop();
	void Clear();
	int Size();
	int Capacity();
	void Dump() const;
	Stack (int size, char* var_name);
	Stack (const Stack& that, char* var_name);
	~Stack();
	int CheckErrors();
};

#include "stack.cpp"  
