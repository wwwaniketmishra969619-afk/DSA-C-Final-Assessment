#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_LEN 300

typedef struct {
    char items[MAX_TOKENS];
    int top;
} CharStack;

void push_char(CharStack *s, char val) {
    s->items[++(s->top)] = val;
}

char pop_char(CharStack *s) {
    return s->items[(s->top)--];
}

char peek_char(CharStack *s) {
    return s->items[s->top];
}

int is_empty_char(CharStack *s) {
    return s->top == -1;
}

typedef struct {
    long long items[MAX_TOKENS];
    int top;
} NumStack;

void push_num(NumStack *s, long long val) {
    s->items[++(s->top)] = val;
}

long long pop_num(NumStack *s) {
    return s->items[(s->top)--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

typedef struct {
    int is_num;
    long long num;
    char op;
} Token;

int parse_and_eval(char *line) {
    Token tokens[MAX_TOKENS];
    int token_count = 0;
    
    char *p = line;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        if (*p == '\0') break;

        if (isdigit(*p)) {
            long long val = 0;
            while (isdigit(*p)) {
                val = val * 10 + (*p - '0');
                p++;
            }
            tokens[token_count].is_num = 1;
            tokens[token_count].num = val;
            token_count++;
        } else if (*p == '(' || *p == ')' || is_operator(*p)) {
            tokens[token_count].is_num = 0;
            tokens[token_count].op = *p;
            token_count++;
            p++;
        } else {
            p++;
        }
    }

    Token postfix[MAX_TOKENS];
    int postfix_count = 0;
    CharStack op_stack;
    op_stack.top = -1;

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].is_num) {
            postfix[postfix_count++] = tokens[i];
        } else if (tokens[i].op == '(') {
            push_char(&op_stack, '(');
        } else if (tokens[i].op == ')') {
            while (!is_empty_char(&op_stack) && peek_char(&op_stack) != '(') {
                Token t;
                t.is_num = 0;
                t.op = pop_char(&op_stack);
                postfix[postfix_count++] = t;
            }
            if (is_empty_char(&op_stack)) {
                printf("ERROR: UNBALANCED\n");
                return 0;
            }
            pop_char(&op_stack);
        } else if (is_operator(tokens[i].op)) {
            while (!is_empty_char(&op_stack) && peek_char(&op_stack) != '(' &&
                   precedence(peek_char(&op_stack)) >= precedence(tokens[i].op)) {
                Token t;
                t.is_num = 0;
                t.op = pop_char(&op_stack);
                postfix[postfix_count++] = t;
            }
            push_char(&op_stack, tokens[i].op);
        }
    }

    while (!is_empty_char(&op_stack)) {
        if (peek_char(&op_stack) == '(') {
            printf("ERROR: UNBALANCED\n");
            return 0;
        }
        Token t;
        t.is_num = 0;
        t.op = pop_char(&op_stack);
        postfix[postfix_count++] = t;
    }

    NumStack num_stack;
    num_stack.top = -1;

    for (int i = 0; i < postfix_count; i++) {
        if (postfix[i].is_num) {
            push_num(&num_stack, postfix[i].num);
        } else {
            long long b = pop_num(&num_stack);
            long long a = pop_num(&num_stack);
            char op = postfix[i].op;
            
            if (op == '/' && b == 0) {
                printf("ERROR: DIV BY ZERO\n");
                return 0;
            }

            long long res = 0;
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') res = a / b;

            push_num(&num_stack, res);
        }
    }

    printf("%lld\n", pop_num(&num_stack));
    return 0;
}

int main(void) {
    char line[MAX_LEN];
    if (fgets(line, sizeof(line), stdin) != NULL) {
        parse_and_eval(line);
    }
    return 0;
}