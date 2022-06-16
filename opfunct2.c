#include "monty.h"

/**
 * swap - Swaps the top two elements of the stack
 * @stack: pointer to a pointer of first node
 * @line_number: the line number in the file.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int num;
	stack_t *tmp;

	if (!*stack || !(*stack)->next)
		error_handle(stack, line_number, 5);
	num = (*stack)->n;
	tmp = (*stack)->next;

	(*stack)->n = tmp->n;
	tmp->n = num;
}

/**
 * add - Adds the top two elements of the stack
 * @stack: Pointer to pointer to first node of linked list
 * @line_number: the line number in the file
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!*stack || !(*stack)->next)
		error_handle(stack, line_number, 6);
	tmp = *stack;
	*stack = (*stack)->next;

	(*stack)->n += tmp->n;
	free(tmp);
	(*stack)->prev = NULL;
}

/**
 * nop - The opcode nop doesnt do anything.
 * @stack: Pointer to pointer of first node.
 * @line_number: the line number in the file.
 *
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)**stack;
	(void)line_number;
}

/**
 * sub - subtracts the top element of the stack from the second top element.
 * @stack: Pointer to pointer to first node of linked list
 * @line_number: the line number in the file
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!*stack || !(*stack)->next)
		error_handle(stack, line_number, 7);
	tmp = *stack;
	*stack = (*stack)->next;

	(*stack)->n -= tmp->n;
	free(tmp);
	(*stack)->prev = NULL;
}

/**
 * divide - divides the second top node by the top node of the stack.
 * @stack: Pointer to pointer to first node of linked list
 * @line_number: the line number in the file
 */
void divide(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!*stack || !(*stack)->next)
		error_handle(stack, line_number, 8);
	if ((*stack)->n == 0)
		error_handle(stack, line_number, 9);
	tmp = *stack;
	*stack = (*stack)->next;

	(*stack)->n /= tmp->n;
	free(tmp);
	(*stack)->prev = NULL;
}
