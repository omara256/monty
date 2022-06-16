#include "monty.h"

/**
 * error_handle - handle error message.
 * @stack: pointer to a pointer of first node
 * @line_number: the line number in the file.
 * @error_type: value specifying error type.
 */
void error_handle(stack_t **stack, unsigned int line_number, int error_type)
{
	if (error_type == 0)
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
	else if (error_type == 1)
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, globals.token);
	else if (error_type == 2)
		fprintf(stderr, "Error: malloc failed\n");
	else if (error_type == 3)
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
	else if (error_type == 4)
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
	else if (error_type == 5)
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
	else if (error_type == 6)
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
	else if (error_type == 7)
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
	else if (error_type == 8)
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
	else if (error_type == 9)
		fprintf(stderr, "L%d: division by zero\n", line_number);
	else if (error_type == 10)
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
	else if (error_type == 11)
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
	else if (error_type == 12)
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
	else if (error_type == 13)
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
	free(globals.lineptr);
	free_stack(*stack);
	fclose(globals.fp);
	exit(EXIT_FAILURE);
}

/**
 * check_op - function determines  which opcodes should be called.
 * @stack: pointer to a pointer of first node
 * @line_number: the line number in the file.
 */
void check_op(stack_t **stack, unsigned int line_number)
{
	instruction_t opcodes[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", divide},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	int i;

	for (i = 0; opcodes[i].opcode; ++i)
	{
		if (!strcmp(globals.token, opcodes[i].opcode))
		{
			globals.token = strtok(NULL, " \n");
			opcodes[i].f(stack, line_number);
			break;
		}
	}
	if (!opcodes[i].opcode)
		error_handle(stack, line_number, 1);
}

/**
 * parse_arg - parse the arguments.
 * @argc: numbers of arguments.
 * @argv: pointer to an array of string.
 */
void parse_arg(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	globals.fp = fopen(argv[1], "r");
	if (!globals.fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
}

/**
 * read_line - read and parse lines from a file.
 * @stack: pointer to a pointer of first node.
 */
void read_line(stack_t **stack)
{
	int len, dtype;
	unsigned int line_number;
	size_t n;

	len = dtype = line_number = n = 0;
	globals.lineptr = NULL;
	while ((len = getline(&globals.lineptr, &n, globals.fp)) != EOF)
	{
		++line_number;
		globals.token = strtok(globals.lineptr, " \n");
		if (!globals.token || globals.token[0] == '#')
			continue;
		if (!strcmp(globals.token, "stack"))
		{
			dtype = 0;
			continue;
		}
		else if (!strcmp(globals.token, "queue"))
		{
			dtype = 1;
			continue;
		}
		if (!strcmp(globals.token, "push"))
		{
			globals.token = strtok(NULL, " \n");
			if (globals.token)
			{
				parse_num(stack, line_number);
				globals.data = atoi(globals.token);
				if (!dtype)
					push(stack, line_number);
				else
					push_q(stack, line_number);
				continue;
			}
			else
				error_handle(stack, line_number, 0);
		}
		check_op(stack, line_number);
	}
}

/**
 * parse_num - Checks if string contains number
 * @stack: pointer to a pointer of first node
 * @line_number: the line number in the file.
 */
void parse_num(stack_t **stack, unsigned int line_number)
{
	int i;

	for (i = 0; globals.token[i]; ++i)
	{
		if (i == 0 && globals.token[0] == '-')
			++i;
		if (globals.token[i] < '0' || globals.token[i] > '9')
			error_handle(stack, line_number, 0);
	}
}
