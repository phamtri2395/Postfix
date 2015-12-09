/** main.cpp

    This is main file where contains entry point

	@docdate 10/10/2015
    @author phamtri2395@gmail.com
*/

/* Include files from extlib folder */
#include "extlib/extStr.h"
#include "extlib/extList.h"
#include "extlib/extMath.h"
/* C++ standard libraries */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX_DATA 100

/* Global Variables */
char operands[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char operators[][2] = { { '+', '-' }, { '*', '/' } };

/* Function prototypes */
bool isOperand(extStr&); /* Check if '0' - '9' */
bool isOperator(extStr&); /* Check if '+' or '-' or '*' or '/' */
bool isBracket(extStr&); /* Check if '(' or ')' */
int priority(char&); /* Get operator's priority */
void Split(extStr&, Queue<extStr>&); /* Split unformated string into operands & operators that stored in queue */
bool isVerified(extStr&); /* Try to verify given string. Return true if success, false if not*/
/* Convert expression string to Postfix */
bool Postfix(Queue<extStr>&);
/* Caculate an expression string in Postfix format */
double Calc(Queue<extStr>&);

int main (int argc, char* argv[]) {
	/* Get command line arguments */
	const char* f_input = "input";
	const char* f_output = "output";

	/* Variables */
	extStr data[MAX_DATA];
	int number = 0;

	/* File processing */    //READ
	fstream f;
	f.open(f_input, ios::in);
	if (f) {
		while (!f.eof()) {
			string temp;
			getline(f, temp);
			data[number++] = temp.c_str();
		}	
	}
	f.close();
	/* File processing */    //WRITE
	f.open(f_output, ios::out);

	for (int i = 0; i < number; i++) {
		extStr element = data[i];

		if (isVerified(element)) {
			Queue<extStr> raw_data;
			
			Split(element, raw_data); /* Split string into queue */
			
			if(Postfix(raw_data)) { /* Check if can convert from Infix to Postfix */
				/* Print out Postfix string and copy data */
				Queue<extStr> formated_data;
				extStr temp("");
				while(!raw_data.isEmpty()) { //Copy data
					temp = temp + raw_data.peek().toString();
					temp = temp + ' ';
					formated_data.enqueue(raw_data.dequeue());
				}
				char* temp_t = temp.toString(); // Remove last space
				long count = 0;
				while (temp_t[count] != '\0') count++;
				temp_t[--count] = '\0';
				f << temp.toString() << endl; // Print out Postfix string
				/* Print out result */
				f << Calc(formated_data);
			} 
			else {
				f << "Loi";
				continue;
			}
		}
		else f << "Loi";

		if (i != (number - 1)) f << endl;
	}

		f.close();
	/*if (isVerified(str)) {
		Queue<extStr> queue;
		Split(str, queue);

		Postfix(queue);

		double temp = Calc(queue);
	}*/
	return 0;
}

/* Implementations */

bool isOperand(extStr& str) { return ((str.at(0) >= '0') && (str.at(0) <= '9')); }
bool isOperator(extStr& str) { return ((str.at(0) == '+') || (str.at(0) == '-') || (str.at(0) == '*') || (str.at(0) == '/')); }
bool isBracket(extStr& str) { return ((str.at(0) == '(') || (str.at(0) == ')')); }
int priority(char& chr) {
	if ((chr == '+') || (chr == '-')) return 0;
	if ((chr == '*') || (chr == '/')) return 1;

	return 2;
}
void Split(extStr& str, Queue<extStr>& queue) {
	extStr* pstr = new extStr();

	int last_state = -1;
	int current_state = -1;

	long count = 0;
	while (str.at(count) != '\0') {
		/* Read current state (type of character) */
		if (((str.at(count) >= '0') && (str.at(count) <= '9')) || (str.at(count) == '.')) current_state = 0;
		else if ((str.at(count) == '+') || (str.at(count) == '-') || (str.at(count) == '*') || (str.at(count) == '/')) current_state = 1;
		else if ((str.at(count) == '(') || (str.at(count) == ')')) current_state = 2;

		/* Switching state */
		if (current_state != last_state) {
			if (last_state != -1) {
				queue.enqueue(*pstr);
				pstr = new extStr(); /* Create new sub-string */
			}
			if (current_state == 2) last_state = 3; /* Solution for multiple '(' */
			else last_state= current_state;
		} else {
		}


		(*pstr) = (*pstr) + str.at(count);

		count++;
	}
	queue.enqueue(*pstr);
}
bool isVerified(extStr& str) {
	bool errors[MAX_ERRORS];
	str.Verify(errors);

	for (int i = 0; i < MAX_ERRORS; i++)
		if ((errors[i] == true) && (i != 1)) return false;

	str.removeSpace(); /* Remove spaces */
	return true;
}
bool Postfix(Queue<extStr>& queue) {
	Stack<extStr> stack;
	Queue<extStr> result;

	try {
		while (!queue.isEmpty()) {
			/* Operands */
			if (isOperand(queue.peek())) {
				result.enqueue(queue.dequeue());
				continue;
			}
			/* Brackets */
			if (isBracket(queue.peek())) {
				if (queue.peek().at(0) == '(') stack.push(queue.dequeue());
				else {
					queue.dequeue();
					while (stack.peek().at(0) != '(')
						result.enqueue(stack.pop());
					stack.pop();
				}
				continue;
			}
			/* Operators */
			if (isOperator(queue.peek())) {
				if (!stack.isEmpty())
					if (isOperator(stack.peek())) {
						if (priority(queue.peek().at(0)) <= priority(stack.peek().at(0)))
							result.enqueue(stack.pop());
					}
				stack.push(queue.dequeue());
				continue;
			}
		}

		while (!stack.isEmpty())
			result.enqueue(stack.pop());

		/* Copy temporary data to queue */
		while (!result.isEmpty())
			queue.enqueue(result.dequeue());
	} catch (int err_code) { /* Catch exceptions */
		throw;
		return false;
	}

	return true;
}
double Calc(Queue<extStr>& queue) {
	Stack<double> result;

	while (!queue.isEmpty()) {
		/* Operands */
		if (isOperand(queue.peek())) {
			result.push(stod(queue.dequeue().toString()));
			continue;
		}
		/* Operators */
		if (isOperator(queue.peek())) {
			/* Pop out stack */
			double a = 0;
			double b = 0;
			if (!result.isEmpty()) b = result.pop(); /* Pop out b first */
			if (!result.isEmpty()) a = result.pop(); /* if stack is empty, default value will be 0 */

			switch (queue.dequeue().at(0)) {
			case '+':
				result.push(a + b);
				break;
			case '-':
				result.push(a - b);
				break;
			case '*':
				result.push(a * b);
				break;
			case '/':
				result.push(a / b);
				break;
			}
		}
	}

	return result.pop();
}