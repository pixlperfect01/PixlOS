#define isdigit(c) (c >= '0' && c <= '9')

double atof(const char *s)
{
  // This function stolen from either Rolf Neugebauer or Andrew Tolmach. 
  // Probably Rolf.
  double a = 0.0;
  int e = 0;
  int c;
  while ((c = *s++) != '\0' && isdigit(c)) {
    a = a*10.0 + (c - '0');
  }
  if (c == '.') {
    while ((c = *s++) != '\0' && isdigit(c)) {
      a = a*10.0 + (c - '0');
      e = e-1;
    }
  }
  if (c == 'e' || c == 'E') {
    int sign = 1;
    int i = 0;
    c = *s++;
    if (c == '+')
      c = *s++;
    else if (c == '-') {
      c = *s++;
      sign = -1;
    }
    while (isdigit(c)) {
      i = i*10 + (c - '0');
      c = *s++;
    }
    e += i*sign;
  }
  while (e > 0) {
    a *= 10.0;
    e--;
  }
  while (e < 0) {
    a *= 0.1;
    e++;
  }
  return a;
}

int atoi(const char *str)
{
    int acc = 0;

    for(; str && isdigit(*str); ++str) {
        acc *= 10;
        acc += *str - 0x30;
    }

    return acc;
}

long int
atol(string)
    register char *string;	/* String of ASCII digits, possibly
				 * preceded by white space.  For bases
				 * greater than 10, either lower- or
				 * upper-case digits may be used.
				 */
{
    register long int result = 0;
    register unsigned int digit;
    int sign;

    /*
     * Skip any leading blanks.
     */

    while (*string == ' ') {
	string += 1;
    }

    /*
     * Check for a sign.
     */

    if (*string == '-') {
	sign = 1;
	string += 1;
    } else {
	sign = 0;
	if (*string == '+') {
	    string += 1;
	}
    }

    for ( ; ; string += 1) {
	digit = *string - '0';
	if (digit > 9) {
	    break;
	}
	result = (10*result) + digit;
    }

    if (sign) {
	return -result;
    }
    return result;
}




#undef isdigit
