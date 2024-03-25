#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 100

// Stack structure
typedef struct {
    int top;
    char items[STACK_SIZE];
} Stack;

// Function declarations
void push(Stack *s, char c);
char pop(Stack *s);
char peek(Stack *s);
int is_operator(char c);
int precedence(char c);

int main() {
    char infix[STACK_SIZE];
    Stack operator_stack;
    operator_stack.top = -1;

    printf("\nEnter the infix expression: ");
    fgets(infix, STACK_SIZE, stdin);

    printf("\nThe RPN expression is: ");

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) { // If token is an operand
            printf("%c", token);
        } else if (token == '(') { // If token is '('
            push(&operator_stack, token);
        } else if (token == ')') { // If token is ')'
            while (peek(&operator_stack) != '(') {
                printf("%c", pop(&operator_stack));
            }
            pop(&operator_stack); // Discard '('
        } else if (is_operator(token)) { // If token is an operator
            while (precedence(token) <= precedence(peek(&operator_stack))) {
                printf("%c", pop(&operator_stack));
            }
            push(&operator_stack, token);
        }
    }

    // Pop remaining operators from the stack
    while (operator_stack.top != -1) {
        printf("%c", pop(&operator_stack));
    }

    return 0;
}

// Function to push element onto the stack
void push(Stack *s, char c) {
    if (s->top == STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = c;
}

// Function to pop element from the stack
char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to return the top element of the stack
char peek(Stack *s) {
    if (s->top == -1) {
        return '\0';
    }
    return s->items[s->top];
}

// Function to check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Function to determine precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/' || c == '%') {
        return 2;
    } else {
        return 0; // Parentheses have the lowest precedence
    }
}
