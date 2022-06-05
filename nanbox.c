#include "nanbox.h"

void main() {
	Value f = create_float(3.141);
	Value i = create_int(4);
	Value p = create_pointer(0xCAFEBEEF);
	Value a = kTrue;
	Value b = kFalse;
	Value n = kNull;

	print_value(f);
	printf("\n");

	print_value(i);
	printf("\n");

	print_value(p);
	printf("\n");

	print_value(a);
	printf("\n");

	print_value(b);
	printf("\n");

	print_value(n);
	printf("\n");
}