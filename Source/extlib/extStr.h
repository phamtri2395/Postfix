/** extStr.h

    Self-Defined string type
	Provides more methods for string handling

	@docdate 10/11/2015
    @author phamtri2395@gmail.com
*/

#ifndef _EXTSTR_
#define _EXTSTR_

#include "extlib/extList.h"

/* Define */
#define MAX_LENGTH 1001
#define MAX_ERRORS 5
enum errors {non_exp_char, multi_space, start_end_non_exp, brackets_error, space_between};

class extStr {
private:
	char* s; /* Variables */
public:
	/* Constructors & Destructors */
	extStr();
	extStr(const char*);

	~extStr();
	void Dispose(); // Free memory

	/* Operators overloading */
	extStr& operator =(const char*);
	extStr operator +(const char*);
	extStr operator +(const char);

	/* Function prototypes */
	char& at(long); /* Index */
	void Verify(bool[MAX_ERRORS]); /*Verify the string and return error codes to an array*/
	void removeSpace(); /* Remove spaces */
	char* toString(); /* Convert to char* */
};

/* Implementations */

extStr::extStr() {
	s = new char[MAX_LENGTH];
	s[0] = '\0';
}
extStr::extStr(const char* str) {
	s = new char[MAX_LENGTH];

	long count = 0;
	while ((str[count] != '\0') && (count < MAX_LENGTH)) {
		s[count] = str[count];
		count++;
	}
	s[count] = '\0';
}
extStr::~extStr() {
	//delete s;
}
void extStr::Dispose() {
	delete s;
}

extStr& extStr::operator =(const char* str) {
	long count = 0;
	while ((str[count] != '\0') && (count < MAX_LENGTH)) {
		s[count] = str[count];
		count++;
	}
	s[count] = '\0';

	return *this;
}
extStr extStr::operator+(const char* other) {
	char* temp = new char[MAX_LENGTH];
	long count_a = 0;
	while (s[count_a] != '\0') {
		temp[count_a] = s[count_a];
		count_a++;
	}
	long count_b = 0;
	while ((other[count_b] != '\0') && (count_a + count_b < MAX_LENGTH)) {
		temp[count_a + count_b] = other[count_b];
		count_b++;
	}
	temp[count_a + count_b] = '\0';

	return extStr(temp);
}
extStr extStr::operator+(const char chr) {
	char* temp = new char[MAX_LENGTH];
	long count = 0;
	while (s[count] != '\0') {
		temp[count] = s[count];
		count++;
	}
	if (count < MAX_LENGTH - 1) {
		temp[count] = chr;
		temp[++count] = '\0';
	}

	return extStr(temp);
}

char& extStr::at(long index) {
	return s[index];
}
void extStr::Verify(bool a[MAX_ERRORS]) {
	/* Initialize false value to array */
	for (int i = 0; i < MAX_ERRORS; i++)
		a[i] = false;

	long count = 0;
	bool flag = false;
	/* Check for allowed characters */
	while (s[count] != '\0') {
		if (!((s[count] >= '(') && (s[count] <= '9') || (s[count] == ' '))) {
			a[non_exp_char] = flag = true;
			break;
		}
		if (flag) break;
		count++;
	}

	count = 0;
	flag = false;
	/* Check for multi contiguous space */
	while (s[count] != '\0') {
		if (s[count] == ' ') {
			if (flag == false) {
				flag = true;
			}
			else {
				a[multi_space] = true;
				break;
			}
		}
		else { flag = false; }
		count++;
	}

	count = 0;
	/* Check for starting or ending with non-expression character */
	while (s[count] != '\0') {
		if (s[count] != ' ') {
			if ((s[count] < '(') || (s[count] > '9') || (s[count] == ',') || (s[count] == '.'))
				a[start_end_non_exp] = true;
			break;
		}			
		count++;
	}
	count = 0;
	while (s[count] != '\0') count++;
	count--;
	while (count >= 0) {
		if (s[count] != ' ') {
			if ((s[count] < '(') || (s[count] > '9') || (s[count] == ',') || (s[count] == '.') || (s[count] == '+') || (s[count] == '-') || (s[count] == '*') || (s[count] == '/'))
				a[start_end_non_exp] = true;
			break;
		}
		count--;
	}

	count = 0;
	Stack<char> stack;
	/* Check for single bracket */
	while (s[count] != '\0') {
		if (s[count] == '(') stack.push('(');
		if (s[count] == ')')
			if (!stack.isEmpty()) {
				if (stack.peek() == '(')
					stack.pop();
				else stack.push(')');
			}
			else stack.push(')');
		count++;
	}
	if (!stack.isEmpty()) a[brackets_error] = true;

	count = 0;
	flag = false;
	bool flag_space = false;
	/* Check for spaces between digits */
	while (s[count] != '\0') {
		if ((s[count] >= '0') && (s[count] <= '9')) {
			if (flag && flag_space) {
				a[space_between] = true;
				break;
			}
			else flag = true;
			count++;
			continue;
		}
		if (s[count] == ' ') {
			flag_space = true;
			count++;
			continue;
		}
		flag = false;
		flag_space = false;
		count++;
	}

}
void extStr::removeSpace() {
	long count = 0;
	long current = 0;
	while (s[count] != '\0') {
		s[current] = s[count];
		if (s[count] != ' ') current++;
		count++;
	}
	s[current] = s[count];
}
char* extStr::toString() { return s; }
#endif