/** extMath.h

    This extention for math library itself contains math.h
	Provides more methods for arithmetic processing

	@docdate 10/11/2015
    @author phamtri2395@gmail.com
*/

#ifndef _EXTMATH_
#define _EXTMATH_

#include <math.h>

/* Global function prototypes */
double stod(char*);




/* Implementations */
double stod(char* s) {
	double temp = 0.0;
	bool flag_point = false;
	long count = 0;
	double multiplier = 10.0;

	/* Only digits and '+' and '-' allowed at s[0] */
	if ((s[count] < '*') || (s[count] > '9') || (s[count] == '*') || (s[count] == '/') || (s[count] == ',') || (s[count] == '.')) return NAN;
	if ((s[count] == '-') || (s[count] == '+')) count++;

	while (s[count] != '\0') {
		/* Won't allow any character except digits and '.' */
		if ((s[count] >= '0') || (s[count] <= '9') || (s[count] == '.')) {
			if (s[count] == '.') {
				if (flag_point) return NAN; /* If there was a '.' return NaN */
				flag_point = true; /* If there wasn't a '.' then turn flag on */
				multiplier = 1.0/10.0;
				count++;
				continue;
			}
			if (!flag_point) {
				temp *= multiplier;
				temp += double(s[count] - '0');
			} else {
				temp += (double(s[count] - '0') * multiplier);
				multiplier *= 0.1;
			}
		}
		else return NAN;
		count++;
	}

	return temp;
}
#endif