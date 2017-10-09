#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

const wchar_t* file_out_name = "text_file_out.txt";

//Настоящие джентельмены делают main() сверху)
//И раздельную компиляцию по файлам

typedef struct {
	void* line_ptr;
	wchar_t* str;
} Line;

void strreverse (char* str) {
	//1) если str = NULL?
	//2) ты приводишь тип wchar_t* к char*. Хотя 1 = sizeof(char) != sizeof(wchar_t) = 2
	//3) есть стандартная функция strrev()
	char buf;
	for (size_t i = 0; i < strlen(str)/2; i++) {
		buf = str[i];
		str[i] = str[strlen(str)-i-1];
		str[strlen(str)-i-1] = buf;
	}
	return;
}

int cmpstr (void const *a, void const *b) { 
	//a = null = b ?
	//strcmp работает с char*, поэтому и неправильно компарирует
	//для wchar_t есть int wcscmp(const wchar_t *string1, const wchar_t *string2);
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

//космос уважаешь? не жалей пустых строк
//а то сложно читать
wchar_t* ReadFromFile (char* file_name) {
	//file_name = null ?
	
	FILE* file = fopen(file_name, "r"); //"rb"
	if (file == NULL) {
		printf("Error while openning file");
		return 0;
	}
	
	fseek(file, 0, SEEK_END);		//можно в отдельную функцию
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	wchar_t* file_vec = (wchar_t*) malloc(sizeof(wchar_t) * file_size); // 2 строчки = calloc()
	memset(file_vec, '\0', file_size);
	//file_vec = null? 
	//free() нет в main'e
	
	fwscanf(file, L"%[^\0]", file_vec);
	
	fclose(file);
	return file_vec;
}

size_t FileSize (char* file_name) {
	//file_name = null?
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		printf("Error while openning file");
		return 0;
	}
	
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	
	fclose(file);
	return file_size;
}

Line* DivideToLines (wchar_t* file_vec, size_t file_size) {
	//file_vec = null? 
	Line* lines = (Line*)calloc(file_size, sizeof(Line));
	//lines = null?
	
	lines[0].line_ptr = file_vec;
	lines[0].str = (wchar_t*) calloc(file_size, sizeof(wchar_t)); // а память на нулевой символ в конце?
	//lines[0].str = null?
	
	size_t line_count = 0;
	size_t buf_char = 0;
	bool exit = false;
	bool low_reg = false;
	
	//можно переписать гораздо короче и быстрее на strchr()
	for (size_t i = 0; i < file_size; i++) {
		if ((file_vec[i] == L'\n') || (exit = (file_vec[i] == L'\0'))) {
			line_count++;
			if (exit) break;
			file_vec[i] = L'\0';
			lines[line_count].line_ptr = file_vec + i + 1;
			lines[line_count].str = (wchar_t*) calloc(file_size, sizeof(wchar_t));
			//lines[line_count].str = null?
			i++;
			buf_char = 0;
		}
		//для английский букв есть isalpha(), сделай свою isrusalpha()
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

size_t LineCount (wchar_t* file_vec) {
	//file_vec = null?
	//юзай strlen
	size_t line_count = 0;
	size_t i = 0;
	while (file_vec[i] != '\0') {
		if (file_vec[i] == '\n') line_count++;
		i++;
	}
	line_count++;
	return line_count;
}

void Sorting (Line* lines, size_t line_count) {
	//lines = null?
	qsort(lines, line_count, sizeof(Line*), cmpstr);
	
	FILE* file_out = fopen(file_out_name, "w");
	//file_out = null?
	for(size_t i = 0; i < line_count; i++) {
		fwprintf(file_out, L"%s\n", lines[i].str);
		wprintf(L"%s\n", lines[i].str);
	}
	fclose(file_out);
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	wchar_t* file_str = ReadFromFile("text_file.txt");
	
	size_t line_count = LineCount(file_str);
	
	Line* lines = DivideToLines(file_str, FileSize("text_file.txt"));
	
	Sorting(lines, line_count);
	
	//free()? у тебя было (line_count + 1) calloc'ов и ни одного free()
	system("PAUSE");
	return 0;
}
