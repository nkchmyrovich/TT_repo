#include <sorting.h>

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	wchar_t* file_str = ReadFromFile("text_file.txt");
	
	size_t line_count = LineCount(file_str);
	
	Line* lines = DivideToLines(file_str, FileSize("text_file.txt"));
	
	Sorting(lines, line_count);
	
	free(file_str);
	
	for (size_t i = 0; i < line_count; i++) {
			free(lines[i].str);
	}
	
	free(lines);
	system("PAUSE");
	return 0;
}
