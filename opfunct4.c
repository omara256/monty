#include "monty.h"

/**
 * rotr - Rotates the stack to the bottom
 * @stack: Pointer to pointer to first node of linked list
 * @line_number: the line number in the file
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	(void)line_number;

	if ((*stack) && (*stack)->next)
	{
		tmp = *stack;
		while (tmp->next->next)
			tmp = tmp->next;
		(*stack)->prev = tmp->next;
		tmp->next->prev = NULL;
		tmp->next->next = *stack;
		tmp->next = NULL;
		*stack = (*stack)->prev;
	}
}

/**
 * push_q - Adds a new node at the end of a list
 * @stack: Pointer to pointer of first node
 * @line_number: Current line number
 */
void push_q(stack_t **stack, unsigned int line_number)
{
	stack_t *new, *current;

	current = *stack;
	new = malloc(sizeof(stack_t));
	if (!new)
		error_handle(stack, line_number, 2);

	new->n = globals.data;
	new->next = NULL;
	if (!*stack)
	{
		new->prev = NULL;
		*stack = new;
	}
	else
	{
		while (current->next)
			current = current->next;
		new->prev = current;
		current->next = new;
	}
}
