Stack::Stack (int size, char* var_name) :
	canary_1(CANARY_1),
	canary_2(CANARY_2),
	data_ (),
	canary_3(CANARY_3),
	size_ (0),  
	capacity_(size),
	errors_(0),
	do_push(false),
	push_value(0),
	var_name_(new char [255]),
	canary_4(CANARY_4)
	{
		var_name_ = var_name;
		data_.resize(size);
	}
	



Stack::Stack (const Stack& that) try:
	canary_1(CANARY_1),
        canary_2(CANARY_2),
        data_ (that.data_),
        canary_3(CANARY_3),
        size_ (that.size_),
        capacity_(that.size_),
	errors_(that.errors_),
	do_push(that.do_push),
	push_value(that.push_value),
        canary_4(CANARY_4)
	{}
	catch (std::bad_alloc) {
		printf("Error data allocation\n");
	}

Stack::~Stack () {
}


#define RETURN_OK(x) if (!Ok()) {\
                PrintError();\
                return x;\
        }


void Stack::Push (double value) {
	if (!Ok()) {
		do_push = true;
		push_value = value;
		PrintError();
		return;
	}
	data_[size_++] = value;
}

double Stack::Pop () {
	RETURN_OK(0)
	if (!size_) {
		printf("Nothing to pop\n");
		return 0;
	}
	return data_[--size_];
}

bool Stack::Empty () {
	RETURN_OK(0)
	return !size_;
} 

void Stack::Clear () {
	RETURN_OK()
	if (!Empty()) {
		while (size_) {
			data_[--size_] = 0;
		}
	}
}

int Stack::Size () {
	RETURN_OK(0)
	return size_;
}

int Stack::Capacity () {
	RETURN_OK(0)
	return capacity_;
}

#undef RETURN_OK

bool Stack::Ok () const {
	return (this&&((!data_.empty()&&capacity_&&size_<capacity_)||(data_.empty()&&!capacity_&&!size_))
		&&(canary_1==CANARY_1&&canary_2==CANARY_2&&canary_3==CANARY_3&&canary_4==CANARY_4));
}

void Stack::Dump () const {
	if (!data_.empty()) {
		if (var_name_ != NULL) {
			printf("Var name: %s\n", var_name_); 
		} else {
			printf("No var name.\n");
		}
		if (size_) {
			size_t i = size_;
			printf("Capacity: %d \n", capacity_);
			printf("Size: %d \n", size_);
			printf("Canary #1: %d \n", canary_1);
			printf("Canary #2: %g \n", canary_2);
			printf("Canary #3: %g \n", canary_3);
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

#define ERRORS(statement, value) if (statement) {\
                        errors_ |= value;\
                } else

int Stack::CheckErrors () {
	if (!Ok()) {
		ERRORS ((size_>=capacity_), CAPACITY_SIZE_ERR) 
		ERRORS ((this == NULL), NO_STACK_ERR)
		if (data_.empty()) {
			if (capacity_) {
				errors_ |= WR_CAPACITY_ERR;
			} else if (size_) {
				errors_ |= WR_SIZE_ERR;
			}
		} else if (!data_.empty()) {
			if (capacity_ == 0) {
				errors_ |= NO_CAPACITY_ERR;
			}
		} else 
		ERRORS ((canary_1 != CANARY_1), CANARY_1_ERR)
		ERRORS ((canary_2 != CANARY_2), CANARY_2_ERR)
                ERRORS ((canary_3 != CANARY_3), CANARY_3_ERR)
                ERRORS ((canary_3 != CANARY_3), CANARY_3_ERR)
               	{}
		return 1;
	}
	return 0;
} 

#undef ERRORS

#define CHECK_ERROR(error_name, message) case error_name:\
                        printf message;\
                        errors_ = errors_&&(!(1 << i));\
                        break;
 

void Stack::PrintError() {
	if  (CheckErrors()) {
	for (size_t i = 0; i < 8*sizeof(int); i++) {
		switch ((int)(errors_&&(1 << i))) {
		case CAPACITY_SIZE_ERR:
			printf("Error code: size > capacity\n");
			if (round(SIZE_INC*data_.size())>MAX_STACK_CAPACITY) {
				printf("Message: the MAX_STACK_CAPACITY reached, stack will not be increased\n");
				do_push = false;
			} else {
				data_.resize(round(data_.size()*SIZE_INC));
				capacity_ = data_.size();  
				printf("Message: stack capacity was increased\n");
				if (do_push) data_[size_++] = push_value;
				do_push = false;
				push_value = 0;
			}
			errors_ = errors_&&(!(1 << i)); 
			break;
		CHECK_ERROR(NO_STACK_ERR, ("Error code: no stack\n"))
		CHECK_ERROR(WR_CAPACITY_ERR, ("Error code: wrong capacity\n"))
		CHECK_ERROR(WR_SIZE_ERR, ("Error code: wrong size\n"))
		CHECK_ERROR(NO_CAPACITY_ERR, ("Error code: stack with no capacity\n"))
		CHECK_ERROR(CANARY_1_ERR, ("Error code: canary #1 changed\n"))
		CHECK_ERROR(CANARY_2_ERR, ("Error code: canary #2 changed\n"))
		CHECK_ERROR(CANARY_3_ERR, ("Error code: canary #3 changed\n"))
		CHECK_ERROR(CANARY_4_ERR, ("Error code: canary #4 changed\n"))

		}
	}
	}
	Dump();
	errors_ = 0;
}

#undef CHECK_ERROR
