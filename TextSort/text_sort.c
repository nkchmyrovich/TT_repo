#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

const wchar_t* file_out_name = "text_file_out.txt";
size_t line_count = 0;
size_t file_size = 0;

typedef struct {
	void* line_ptr;
	wchar_t* str;
} Line;

void strreverse (char* str) {
	char buf;
	for (size_t i = 0; i < strlen(str)/2; i++) {
		buf = str[i];
		str[i] = str[strlen(str)-i-1];
		str[strlen(str)-i-1] = buf;
	}
	return;
}

int cmpstr (void const *a, void const *b) { 
    return strcmp(((Line*)a)->str, ((Line*)b)->str);
}

/*void cmpstrrev (void const *a, void const *b) {
	Line* _a = a;
	Line* _b = b;
	wchar_t const *aa = *(wchar_t const **)(_a->str);
    wchar_t const *bb = *(wchar_t const **)(_b->str);
	strreverse(aa);
	strreverse(bb);
    return strcmp(aa, bb);
}*/

wchar_t* ReadFromFile (char* file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		printf("Error while openning file");
		return 0;
	}
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	wchar_t* file_vec = (wchar_t*)malloc(sizeof(wchar_t) * file_size);
	memset(file_vec, '\0', file_size);
	fwscanf(file, L"%[^\0]", file_vec);
	return file_vec;
}

Line* DivideToLines (wchar_t* file_vec) {
	Line* lines = (Line*)calloc(file_size, sizeof(Line));
	lines[0].line_ptr = file_vec;
	lines[0].str = (wchar_t*)calloc(file_size, sizeof(wchar_t));
	size_t line_count = 0;
	size_t buf_char = 0;
	bool exit = false;
	bool low_reg = false;
	for (size_t i = 0; i < file_size; i++) {
		if ((file_vec[i] == L'\n')||(exit = (file_vec[i] == L'\0'))) {
			line_count++;
			if (exit) break;
			file_vec[i] = L'\0';
			lines[line_count].line_ptr = file_vec + i + 1;
			lines[line_count].str = (wchar_t*)calloc(file_size, sizeof(wchar_t));
			i++;
			buf_char = 0;
		}
		if ((file_vec[i] >= L'А' && file_vec[i] <= L'Я') || (low_reg = (file_vec[i] >= L'а' && file_vec[i] <= L'я'))) {
			lines[line_count].str [buf_char] = file_vec[i];
			if (low_reg) {
				lines[line_count].str [buf_char] = lines[line_count].str [buf_char] - 32;
				low_reg = false;
			}
			buf_char++;
		}
		
	}
	return lines;
}

void Sorting (Line* lines) {
	qsort(lines, line_count, sizeof(Line*), cmpstr);
	FILE* file_out = fopen(file_out_name, "w");
	for(size_t i = 0; i < line_count; i++) {
		fwprintf(file_out, L"%s\n", lines[i].str);
	}
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	wchar_t* file_str = ReadFromFile("text_file.txt");
	Line* lines = DivideToLines(file_str);
	Sorting(lines);
	system("PAUSE");
	return 0;
}
