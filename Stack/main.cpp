#include "stack.h"

#define VAR_NAME(x) #x

int main () {
	Stack stack(10, (char*)VAR_NAME(stack));
	for (size_t i = 0; i < 16; i++) {
		stack.Push(i);
	}
	Stack s1(10, (char*)VAR_NAME(s1));
	
	printf("============\n");
	s1.Dump();
	printf("============\n");
	stack.Push(123);
	stack.Dump();
	return 0;
}
