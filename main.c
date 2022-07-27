#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

struct InputBuffer {
	char* buffer;
	size_t buffer_length;
	size_t input_length;
};

typedef struct InputBuffer InputBuffer;

void print_prompt();
InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* buffer);
void read_input(InputBuffer* input_buffer);

int main(int argc, char** argv) {
	InputBuffer* input_buffer = new_input_buffer();

	while (1) {
		print_prompt();
		read_input(input_buffer);

		if (strcmp(input_buffer->buffer, ".exit")) {
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		}
		else {
			printf("Unrecognized command %s\n", input_buffer->buffer);
		}
	}
}

void print_prompt() {
	printf("Sql>> ");
}

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;
	return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
	// adding & at the end of the buffer to change the value of the pointer 
	// inside of the struct to make it point to the new address
	getline(&input_buffer->buffer, &input_buffer->input_length, stdin);
}

void close_input_buffer(InputBuffer* buffer) {
	free(buffer->buffer);
	free(buffer);
}