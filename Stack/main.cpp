#include "stack.h"

#define VAR_NAME(x) #x

int main () {
	Stack s(100, (char*)VAR_NAME(s));
	for (size_t i = 0; i < 16; i++) {
		s.Push(i);
	}
	s.Push(123);
	s.Dump();
	return 0;
}
