#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

char* file_out_name = "text_file_out.txt";

typedef struct {
	void* line_ptr;
	wchar_t* str;
} Line;

#include "sorting.c"