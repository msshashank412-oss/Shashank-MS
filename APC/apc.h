#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 1
#define FAILURE 0

#define POSITIVE 0
#define NEGATIVE 1

#define SAME 0
#define OPERAND1 1
#define OPERAND2 -1

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

int addition(node *tail1, node *tail2, node **headR, node **tailR);
int subtraction(node *tail1, node *tail2, node **headR, node **tailR);
int multiplication(node *tail1, node *tail2,
                   node **headR, node **tailR);
int division(node *head1, node *head2, node *tail2,
             node **headR, node **tailR);

int cla_validation(int argc, char *argv[]);
int get_sign(char **str);

int create_list(char *opr, node **head, node **tail);
int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail);
void print_list(node *head);
void remove_pre_zeros(node **head);

int compare_list(node *head1, node *head2);
int is_zero_list(node *head);

int handle_addition(node *head1, node *tail1,
                    node *head2, node *tail2,
                    node **headR, node **tailR,
                    int sign1, int sign2);

int handle_subtraction(node *head1, node *tail1,
                       node *head2, node *tail2,
                       node **headR, node **tailR,
                       int sign1, int sign2);

#endif