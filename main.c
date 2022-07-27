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

typedef enum {
	PREPARE_SUCCESS,
	UNRECOGNIZED_SYNTAX
} STATEMENT_PREPARE_RESULT;

typedef enum {
	INSERT,
	SELECT
} 
STATEMENT_TYPE ;

typedef struct Statement
{
	STATEMENT_TYPE type;
} Statement;

void print_prompt();
InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* buffer);
void read_input(InputBuffer* input_buffer);
int do_meta_command(InputBuffer* input_buffer);
STATEMENT_PREPARE_RESULT prepare_statement(char* buffer, Statement* statement);
void execute_statement(Statement* statement);

typedef enum MetaCommandResult
{
	META_COMMAND_SUCCESS,
	META_UNRECOGNIZED_COMMAND
} META_COMMAND_RESULT;

int main(int argc, char** argv) {
	InputBuffer* input_buffer = new_input_buffer();

	while (1) {
		print_prompt();
		read_input(input_buffer);

		if (input_buffer->buffer[0] == '.') {
			// if the type of input is meta command
			switch(do_meta_command(input_buffer))
			{
				case (META_COMMAND_SUCCESS):
					continue;
				case (META_UNRECOGNIZED_COMMAND):
					printf("Unrecognized Command '%s'\n", input_buffer->buffer);
					continue;
			}
		}
		else {
			// if it's a statement
			Statement statement;
			switch(prepare_statement(input_buffer->buffer, &statement)) {
				case PREPARE_SUCCESS:
					break;
				case UNRECOGNIZED_SYNTAX:
					printf("Unrecognoized Syntax '%s' \n", input_buffer->buffer);
					continue;
			}

			execute_statement(&statement);
			printf("Executed\n");
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
	size_t input_len = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);

    if(input_len <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = input_len - 1;
    input_buffer->buffer[input_len - 1] = 0;
}

void close_input_buffer(InputBuffer* buffer) {
	free(buffer->buffer);
	free(buffer);
}

// will execute the meta command
int do_meta_command(InputBuffer* input_buffer) {
	if(strcmp(input_buffer->buffer, ".exit") == 0) {
		close_input_buffer(input_buffer);
		exit(EXIT_SUCCESS);
		return META_COMMAND_SUCCESS;
	}
	else {
		return META_UNRECOGNIZED_COMMAND;
	}
}

// check and set the type of statement found in the input query
STATEMENT_PREPARE_RESULT prepare_statement(char* buffer, Statement* statement) {
	if(strncmp(buffer, "Insert", 6) == 0) {
		statement->type = INSERT;
		return PREPARE_SUCCESS;
	}
	else if(strcmp(buffer, "Select")) {
		statement->type = SELECT;
		return PREPARE_SUCCESS;
	}
	return UNRECOGNIZED_SYNTAX;
}

void execute_statement(Statement* statement) {
	switch(statement->type) {
		case INSERT:
			break;
		case SELECT:
			break;
	} 
}