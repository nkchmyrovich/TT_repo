int cmpstr (void const *a, void const *b) { 
	if (!a || !b) {
		printf("Comparator: nullptr in cmp\n");
		return 1;
	}
    return wcscmp(((Line*)a)->str, ((Line*)b)->str);
}

int cmpstrrev (void const *a, void const *b) {
	if (!a || !b) {
		printf("Comparator: nullptr in cmp\n");
		return 1;
	}
	int result = wcscmp(_wcsrev(((Line*)a)->str), _wcsrev(((Line*)b)->str));
	_wcsrev(((Line*)a)->str);
	_wcsrev(((Line*)b)->str);
	return result;
}

size_t FileSize (char* file_name) {
	if (!file_name) {
		printf("FileSize: no file name received\n");
		return 1;
	}
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		printf("FileSize: error while openning file\n");
		return 0;
	}
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fclose(file);
	return file_size;
}

wchar_t* ReadFromFile (char* file_name) {
	if (!file_name) {
		printf("ReadFromFile: no file name received\n");
		return NULL;
	}
	size_t file_size = FileSize(file_name);
	FILE* file = fopen(file_name, "r");
	wchar_t* file_vec = (wchar_t*)calloc(file_size, sizeof(wchar_t));//freed
	fwscanf(file, L"%[^\0]", file_vec);
	fclose(file);
	return file_vec;
}

Line* DivideToLines (wchar_t* file_vec, size_t file_size) {
	if (!file_vec) {
		printf("DivideToLines: no str received\n");
		return NULL;
	}
	Line* lines = (Line*)calloc(file_size, sizeof(Line));//freed
	if (!lines) {
		printf("DivideToLines: lines memory is not allocated\n");
		return NULL;
	}
	lines[0].line_ptr = file_vec;
	lines[0].str = (wchar_t*) calloc(file_size, sizeof(wchar_t));//freed
	size_t line_count = 0;
	size_t buf_char = 0;
	
	bool exit = false;
	bool low_reg = false;
	
	for (size_t i = 0; i < file_size; i++) {
		if ((file_vec[i] == L'\n')||(exit = (file_vec[i] == L'\0'))) {
			if (exit) break;
			line_count++;
			while (file_vec[i] == L'\n' || file_vec[i] == L'\r') {
				file_vec[i] = L'\0';
				i++;
			}
			lines[line_count].line_ptr = file_vec + i;
			lines[line_count].str = (wchar_t*)calloc(file_size, sizeof(wchar_t));//freed
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

size_t LineCount (wchar_t* file_vec) {
	if (!file_vec) {
		printf("LineCount: no str received\n");
		return 1;
	}
	size_t line_count = 0;
	size_t i = 0;
	while (file_vec[i] != '\0') {
		if (file_vec[i] == '\n') {
			line_count++;
			while (file_vec[i] == L'\n') {
				i++;
			}
		} else {
			i++;
		}
	}
	return line_count;
}

void Sorting (Line* lines, size_t line_count) {
	if (!lines) {
		printf("Sorting: no lines received\n");
		return;
	}
	
	qsort(lines, line_count, sizeof(Line), cmpstrrev);
	
	FILE* file_out = fopen(file_out_name, "w");
	if (file_out == NULL) {
		printf("Sorting: file out was not opened.");
		return; 
	}
	for(size_t i = 0; i < line_count; i++) {
		fwprintf(file_out, L"%s\n", lines[i].line_ptr);
		wprintf(L"%s\n", lines[i].line_ptr);
	}
	fclose(file_out);
}