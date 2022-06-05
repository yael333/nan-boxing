#include<stdint.h>

// type for nan boxed values
typedef uint64_t Value;
// type for types of boxed values
typedef enum {
	TypeFloat,
	TypeInt,
	TypeBool,
	TypeNull,
	TypePointer
} ValueType;


// masks for segments of a double value
#define MASK_SIGN      0x8000000000000000
#define MASK_EXPONENT  0x7ff0000000000000
#define MASK_QUIET     0x0008000000000000
#define MASK_TYPE      0x0007000000000000
#define MASK_SIGNATURE 0xffff000000000000
#define MASK_PAYLOAD_INT 0x00000000ffffffff
#define MASK_PAYLOAD_PTR 0x0000ffffffffffff

// type ids
#define MASK_TYPE_NAN     0x0000000000000000
#define MASK_TYPE_FALSE   0x0001000000000000
#define MASK_TYPE_TRUE    0x0002000000000000
#define MASK_TYPE_NULL    0x0003000000000000
#define MASK_TYPE_INTEGER 0x0004000000000000
#define MASK_TYPE_PTR     0x0005000000000000

// constant for short encoded values
#define kNaN   (MASK_EXPONENT | MASK_QUIET)
#define kFalse (kNaN | MASK_TYPE_FALSE)
#define kTrue  (kNaN | MASK_TYPE_TRUE)
#define kNull  (kNaN | MASK_TYPE_NULL)

// signatures of encoded types
#define SIGNATURE_NAN   kNaN
#define SIGNATURE_FALSE kFalse
#define SIGNATURE_TRUE  kTrue
#define SIGNATURE_NULL  kNull
#define SIGNATURE_INT   (kNaN | MASK_TYPE_INTEGER)
#define SIGNATURE_PTR   (kNaN | MASK_SIGNATURE)

Value create_float(double value) {
	return *(Value*)(&value);
}

double decode_float(Value value) {
	return *(double*)(&value);
}

Value create_int(int32_t value) {
	return SIGNATURE_INT | (uint32_t)value;
}

int32_t decode_int(Value value) {
	return value & MASK_PAYLOAD_INT;
}

Value create_pointer(void* value) {
	return SIGNATURE_PTR | (uint64_t)value;
}

void* decode_pointer(Value value) {
	return value & MASK_PAYLOAD_PTR;
}

ValueType get_type(Value value) {
	uint64_t signature = value & MASK_SIGNATURE;
	if ((~value & MASK_EXPONENT) != 0) {
		return TypeFloat;
	}
	switch (signature) {
		case SIGNATURE_NAN:   return TypeFloat;
		case SIGNATURE_FALSE: return TypeBool;
		case SIGNATURE_TRUE:  return TypeBool;
		case SIGNATURE_NULL:  return TypeNull;
		case SIGNATURE_INT:   return TypeInt;
		case SIGNATURE_PTR:   return TypePointer;
	}
	return TypeNull;
}

void print_value(Value value) {
	switch (get_type(value)) {
		case TypeInt:
			printf("%i", decode_int(value));
			break;
		
		case TypeFloat: {
			printf("%f", decode_float(value));
			break;
		}

		case TypeBool: {
			printf("%s", value == kTrue ? "true" : "false");
			break;
		}

		case TypeNull: {
			printf("null");
			break;
		}

		case TypePointer: {
			printf("0x%x", decode_pointer(value));
			break;
		}

		default: {
			printf("unknown");
		}
	}
}