#include "apc.h"

int cla_validation(int argc, char *argv[])
{
    int i;
    int start;

    if (argc != 4)
    {
        printf("Invalid Command line arguments\n");
        printf("Usage: ./apc <operand1> <operator> <operand2>\n");
        return FAILURE;
    }

    start = 0;

    if (argv[1][0] == '+' || argv[1][0] == '-')
        start = 1;

    if (argv[1][start] == '\0')
        return FAILURE;

    for (i = start; argv[1][i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)argv[1][i]))
            return FAILURE;
    }

    if (strlen(argv[2]) != 1)
        return FAILURE;

    if (argv[2][0] != '+' &&
        argv[2][0] != '-' &&
        argv[2][0] != 'x' &&
        argv[2][0] != 'X' &&
        argv[2][0] != '/')
        return FAILURE;

    start = 0;

    if (argv[3][0] == '+' || argv[3][0] == '-')
        start = 1;

    if (argv[3][start] == '\0')
        return FAILURE;

    for (i = start; argv[3][i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)argv[3][i]))
            return FAILURE;
    }

    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    node *new_node;

    if (head == NULL || tail == NULL)
        return FAILURE;

    new_node = malloc(sizeof(node));

    if (new_node == NULL)
        return FAILURE;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        new_node->prev = *tail;
        (*tail)->next = new_node;
        *tail = new_node;
    }

    return SUCCESS;
}

int insert_first(node **head, node **tail, int data)
{
    node *new_node;

    if (head == NULL || tail == NULL)
        return FAILURE;

    new_node = malloc(sizeof(node));

    if (new_node == NULL)
        return FAILURE;

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }

    return SUCCESS;
}

int create_list(char *opr, node **head, node **tail)
{
    if (opr == NULL || head == NULL || tail == NULL)
        return FAILURE;

    while (*opr != '\0')
    {
        if (insert_last(head, tail, *opr - '0') == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(head, tail);
            return FAILURE;
        }

        opr++;
    }

    return SUCCESS;
}

void print_list(node *head)
{
    while (head != NULL && head->data == 0 && head->next != NULL)
    {
        head = head->next;
    }

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

int compare_list(node *head1, node *head2)
{
    int len1 = 0;
    int len2 = 0;
    node *temp;

    temp = head1;

    while (temp != NULL)
    {
        len1++;
        temp = temp->next;
    }

    temp = head2;

    while (temp != NULL)
    {
        len2++;
        temp = temp->next;
    }

    if (len1 > len2)
        return OPERAND1;

    if (len2 > len1)
        return OPERAND2;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return OPERAND1;

        if (head2->data > head1->data)
            return OPERAND2;

        head1 = head1->next;
        head2 = head2->next;
    }

    return SAME;
}

int delete_list(node **head, node **tail)
{
    node *temp;

    if (head == NULL || tail == NULL)
        return FAILURE;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;

    return SUCCESS;
}

void remove_pre_zeros(node **head)
{
    node *temp;

    if (head == NULL || *head == NULL)
        return;

    while ((*head)->next != NULL && (*head)->data == 0)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

int is_zero_list(node *head)
{
    if (head == NULL)
        return 1;

    while (head != NULL)
    {
        if (head->data != 0)
            return 0;

        head = head->next;
    }

    return 1;
}

int get_sign(char **str)
{
    if (str == NULL || *str == NULL)
        return POSITIVE;

    if (**str == '-')
    {
        (*str)++;
        return NEGATIVE;
    }

    if (**str == '+')
        (*str)++;

    return POSITIVE;
}

int handle_addition(node *head1,
                    node *tail1,
                    node *head2,
                    node *tail2,
                    node **headR,
                    node **tailR,
                    int sign1,
                    int sign2)
{
    int result_sign = POSITIVE;
    int status;

    if (sign1 == POSITIVE && sign2 == POSITIVE)
    {
        status = addition(tail1, tail2, headR, tailR);
        result_sign = POSITIVE;
    }
    else if (sign1 == NEGATIVE && sign2 == NEGATIVE)
    {
        status = addition(tail1, tail2, headR, tailR);
        result_sign = NEGATIVE;
    }
    else if (sign1 == POSITIVE && sign2 == NEGATIVE)
    {
        if (compare_list(head1, head2) == OPERAND1 ||
            compare_list(head1, head2) == SAME)
        {
            status = subtraction(tail1, tail2, headR, tailR);
            result_sign = POSITIVE;
        }
        else
        {
            status = subtraction(tail2, tail1, headR, tailR);
            result_sign = NEGATIVE;
        }
    }
    else
    {
        if (compare_list(head2, head1) == OPERAND1 ||
            compare_list(head2, head1) == SAME)
        {
            status = subtraction(tail2, tail1, headR, tailR);
            result_sign = POSITIVE;
        }
        else
        {
            status = subtraction(tail1, tail2, headR, tailR);
            result_sign = NEGATIVE;
        }
    }

    if (status == FAILURE)
        return FAILURE;

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
            return FAILURE;
    }

    if (is_zero_list(*headR))
        result_sign = POSITIVE;

    printf("Result = ");

    if (result_sign == NEGATIVE)
        printf("-");

    print_list(*headR);

    return SUCCESS;
}

int handle_subtraction(node *head1,
                       node *tail1,
                       node *head2,
                       node *tail2,
                       node **headR,
                       node **tailR,
                       int sign1,
                       int sign2)
{
    int result_sign = POSITIVE;
    int comparison;
    int status;

    if (sign1 == POSITIVE && sign2 == POSITIVE)
    {
        comparison = compare_list(head1, head2);

        if (comparison == OPERAND1 || comparison == SAME)
        {
            status = subtraction(tail1, tail2, headR, tailR);
            result_sign = POSITIVE;
        }
        else
        {
            status = subtraction(tail2, tail1, headR, tailR);
            result_sign = NEGATIVE;
        }
    }
    else if (sign1 == POSITIVE && sign2 == NEGATIVE)
    {
        status = addition(tail1, tail2, headR, tailR);
        result_sign = POSITIVE;
    }
    else if (sign1 == NEGATIVE && sign2 == POSITIVE)
    {
        status = addition(tail1, tail2, headR, tailR);
        result_sign = NEGATIVE;
    }
    else
    {
        comparison = compare_list(head2, head1);

        if (comparison == OPERAND1 || comparison == SAME)
        {
            status = subtraction(tail2, tail1, headR, tailR);
            result_sign = POSITIVE;
        }
        else
        {
            status = subtraction(tail1, tail2, headR, tailR);
            result_sign = NEGATIVE;
        }
    }

    if (status == FAILURE)
        return FAILURE;

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
            return FAILURE;
    }

    if (is_zero_list(*headR))
        result_sign = POSITIVE;

    printf("Result = ");

    if (result_sign == NEGATIVE)
        printf("-");

    print_list(*headR);

    return SUCCESS;
}