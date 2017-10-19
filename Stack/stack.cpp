Stack::Stack (size_t size) :
	data_ (),
	capacity_ (size),
	size_ (0),  
	last_error_ (0),
	canary_1(CANARY_1),
	canary_2(CANARY_2),
	canary_3(CANARY_3),
	canary_4(CANARY_4)
	{
		data_.resize(size);
	}
	

Stack::Stack (const Stack& that) try:
	data_ (),
	capacity_ (that.capacity_),
	size_ (0),
	last_error_ (0),
	canary_1(CANARY_1),
        canary_2(CANARY_2),
        canary_3(CANARY_3),
        canary_4(CANARY_4)
	{}
	catch (std::bad_alloc) {
		printf("Error data allocation\n");
	}

Stack::~Stack () {
	size_ = NULL;
	capacity_ = NULL;
	last_error_ = NULL;
}



void Stack::Push (double value) {
	if (!Ok()) {
		PrintError();
		return;
	}
	data_[size_++] = value;
}

double Stack::Pop () {
	if (!Ok()) {
		PrintError();
		return 0;
	}
	if (!size_) {
		printf("Nothing to pop\n");
		return 0;
	}
	return data_[--size_];
}

bool Stack::Empty () {
	if (!Ok()) {
		PrintError();
		return 0;
	}
	return !size_;
} 

void Stack::Clear () {
	if (!Ok()) {
		PrintError();
		return;
	}
	if (!Empty()) {
		while (size_) {
			data_[--size_] = 0;
		}
	}
}

int Stack::Size () {
	if (!Ok()) {
		PrintError();
		return 0;
	}
	return size_;
}

int Stack::Capacity () {
	if (!Ok()) {
		PrintError();
		return 0;
	}
	return capacity_;
}

bool Stack::Ok () {
	return (((!data_.empty()&&capacity_&&size_<capacity_)||(data_.empty()&&!capacity_&&!size_))
		&&this&&(canary_1==CANARY_1&&canary_2==CANARY_2&&canary_3==CANARY_3&&canary_4==CANARY_4));
}

void Stack::Dump () {
	if (!data_.empty()) {
		if (size_) {
			size_t i = size_;
			printf("Capacity: %d \n", capacity_);
			printf("Size: %d \n", size_);
			printf("Canary #1: %d \n", canary_1);
			printf("Canary #2: %d \n", canary_2);
			printf("Canary #3: %d \n", canary_3);
			printf("Canary #4: %d \n", canary_4);
			printf("Stack data: \n");

			while (i--) {
				printf("	%g \n", data_[i]);
			}
		} else {
			printf("Empty stack\n");
		}
	} else {
		printf("No data\n");
	}
}

size_t Stack::CheckErrors () {
	if (!Ok()) {
		if (size_>=capacity_) {
			last_error_ = CAPACITY_SIZE_ERR;
		} else if (this == NULL) {
			last_error_ = NO_STACK_ERR;
		} else if (data_.empty()) {
			if (capacity_) {
				last_error_ = WR_CAPACITY_ERR;
			} else if (size_) {
				last_error_ = WR_SIZE_ERR;
			}
		} else if (!data_.empty()) {
			if (capacity_ == 0) {
				last_error_ = NO_CAPACITY_ERR;
			}
		} else if (canary_1 != CANARY_1) {
			last_error_ = CANARY_1_ERR;
		} else if (canary_2 != CANARY_2) {
                        last_error_ = CANARY_2_ERR;
                } else if (canary_3 != CANARY_3) {
                        last_error_ = CANARY_3_ERR;
                } else if (canary_3 != CANARY_3) {
                        last_error_ = CANARY_3_ERR;
                } 
		return 1;
	}
	return 0;
} 

void Stack::PrintError() {
	if  (CheckErrors()) {
		switch (last_error_) {
		case CAPACITY_SIZE_ERR:
			printf("Error code: %d, size > capacity\n", last_error_);
			if (round(SIZE_INC*data_.size())>MAX_STACK_CAPACITY) {
				printf("Message: the MAX_STACK_CAPACITY reached, stack will not be increased\n");
			} else {
				data_.resize(round(data_.size()*SIZE_INC));
				capacity_ = data_.size();  
				printf("Message: stack capacity was increased\n");
			} 
			break;
		case NO_STACK_ERR:
			printf("Error code: %d, no stack\n", last_error_);
			break;
		case WR_CAPACITY_ERR:
			printf("Error code: %d, wrong capacity\n", last_error_);
			break;
		case WR_SIZE_ERR:
			printf("Error code: %d, wrong size\n", last_error_);
			break;
		case NO_CAPACITY_ERR:
			printf("Error code: %d, stack with no capacity\n", last_error_);
			break;
		case CANARY_1_ERR:
			printf("Error code: %d, canary #1 changed\n", last_error_);
			break;
		case CANARY_2_ERR:
                        printf("Error code: %d, canary #2 changed\n", last_error_);
                        break;
		case CANARY_3_ERR:
                        printf("Error code: %d, canary #3 changed\n", last_error_);
                        break;
		case CANARY_4_ERR:
                        printf("Error code: %d, canary #4 changed\n", last_error_);
                        break;

		}
	}
	Dump();
}
