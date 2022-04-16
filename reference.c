#include <stdlib.h>

#define VARIETY_OBJECT_INTEGER 0
#define VARIETY_OBJECT_LIST 1

struct Callstack;
struct Executable;
struct ListElement;
struct Object;
struct Operation;
struct Process;
struct SliceOfObjects;
struct Frame;

struct Callstack {
	size_t capacity;
	struct Frame *data;
	size_t length;
};

struct Executable {
	size_t capacity;
	struct Operation *data;
	size_t length;
};

struct Frame {
	struct SliceOfObjects borrowed, collected;
	size_t cursor;
	struct Executable executable;
	struct SliceOfObjects owned;
};

struct ListElement {
	struct ListElement *next;
	struct Object *value;
};

struct Object {
	size_t counter;
	int integer;
	struct ListElement *list_element;
	unsigned char variety;
};

struct Operation {
	struct Executable *executable;
	unsigned char keyword, variety;
};

struct Process {
	struct Callstack callstack;
};

struct SliceOfObjects {
	size_t capacity;
	struct Object *data;
	size_t length;
};

struct Callstack append_callstack(struct Callstack callstack, struct Frame frame) {
	if (callstack.capacity == callstack.length) {
		callstack.capacity *= 2;
		struct Frame *new = malloc(callstack.capacity * sizeof(struct Frame));

		for (size_t iterator = 0; iterator < callstack.length; iterator++) {
			new[iterator] = callstack.data[iterator];
		}

		free(callstack.data);
		callstack.data = new;
	}

	callstack.data[callstack.length] = frame;
	callstack.length++;
	return callstack;
}

struct Executable append_executable(struct Executable executable, struct Operation operation) {
	if (executable.capacity == executable.length) {
		executable.capacity *= 2;
		struct Operation *new = malloc(executable.capacity * sizeof(struct Operation));

		for (size_t iterator = 0; iterator < executable.length; iterator++) {
			new[iterator] = executable.data[iterator];
		}

		free(executable.data);
		executable.data = new;
	}

	executable.data[executable.length] = operation;
	executable.length++;
	return executable;
}

struct SliceOfObjects append_slice_of_objects(struct SliceOfObjects slice_of_objects, struct Object object) {
	if (slice_of_objects.capacity == slice_of_objects.length) {
		slice_of_objects.capacity *= 2;
		struct Object *new = malloc(slice_of_objects.capacity * sizeof(struct Object));

		for (size_t iterator = 0; iterator < slice_of_objects.length; iterator++) {
			new[iterator] = slice_of_objects.data[iterator];
		}

		free(slice_of_objects.data);
		slice_of_objects.data = new;
	}

	slice_of_objects.data[slice_of_objects.length] = object;
	slice_of_objects.length++;
	return slice_of_objects;
}

//struct Slice processes;

void execute(void) {
}

void link_list_element(struct ListElement *before, struct ListElement *after) {
	before->next = after;
}

int main(void) {
}
