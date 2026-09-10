#include "apc.h"

int division(node *head1,
             node *head2,
             node *tail2,
             node **headR,
             node **tailR)
{
    node *temp;
    node *current_head = NULL;
    node *current_tail = NULL;
    int quotient = 0;

    if (head1 == NULL || head2 == NULL ||
        headR == NULL || tailR == NULL)
    {
        return FAILURE;
    }

    if (is_zero_list(head2))
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    *headR = NULL;
    *tailR = NULL;

    if (is_zero_list(head1))
    {
        return insert_last(headR, tailR, 0);
    }

    temp = head1;

    while (temp != NULL)
    {
        if (insert_last(&current_head, &current_tail, temp->data) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(&current_head, &current_tail);
            delete_list(headR, tailR);
            return FAILURE;
        }

        remove_pre_zeros(&current_head);

        while (compare_list(current_head, head2) != OPERAND2)
        {
            node *sub_head = NULL;
            node *sub_tail = NULL;

            if (subtraction(current_tail,
                            tail2,
                            &sub_head,
                            &sub_tail) == FAILURE)
            {
                delete_list(&current_head, &current_tail);
                delete_list(headR, tailR);
                return FAILURE;
            }

            delete_list(&current_head, &current_tail);

            current_head = sub_head;
            current_tail = sub_tail;

            quotient++;
        }

        if (insert_last(headR, tailR, quotient) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(&current_head, &current_tail);
            delete_list(headR, tailR);
            return FAILURE;
        }

        quotient = 0;
        temp = temp->next;
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(&current_head, &current_tail);
            return FAILURE;
        }
    }

    delete_list(&current_head, &current_tail);

    return SUCCESS;
}