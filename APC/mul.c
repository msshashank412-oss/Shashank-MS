#include "apc.h"

int multiplication(node *tail1,
                   node *tail2,
                   node **headR,
                   node **tailR)
{
    node *temp2;
    node *partial_head = NULL;
    node *partial_tail = NULL;
    node *shift_head = NULL;
    node *shift_tail = NULL;

    int carry;
    int product;
    int shift = 0;

    if (headR == NULL || tailR == NULL)
    {
        return FAILURE;
    }

    *headR = NULL;
    *tailR = NULL;

    temp2 = tail2;

    while (temp2 != NULL)
    {
        node *temp1 = tail1;

        carry = 0;
        partial_head = NULL;
        partial_tail = NULL;

        while (temp1 != NULL)
        {
            product = (temp1->data * temp2->data) + carry;
            carry = product / 10;
            product %= 10;

            if (insert_first(&partial_head, &partial_tail, product) == FAILURE)
            {
                printf("Memory allocation failed\n");
                delete_list(&partial_head, &partial_tail);
                delete_list(&shift_head, &shift_tail);
                delete_list(headR, tailR);
                return FAILURE;
            }

            temp1 = temp1->prev;
        }

        if (carry != 0)
        {
            if (insert_first(&partial_head, &partial_tail, carry) == FAILURE)
            {
                printf("Memory allocation failed\n");
                delete_list(&partial_head, &partial_tail);
                delete_list(&shift_head, &shift_tail);
                delete_list(headR, tailR);
                return FAILURE;
            }
        }

        for (int i = 0; i < shift; i++)
        {
            if (insert_last(&partial_head, &partial_tail, 0) == FAILURE)
            {
                printf("Memory allocation failed\n");
                delete_list(&partial_head, &partial_tail);
                delete_list(&shift_head, &shift_tail);
                delete_list(headR, tailR);
                return FAILURE;
            }
        }

        if (*headR == NULL)
        {
            *headR = partial_head;
            *tailR = partial_tail;
        }
        else
        {
            if (addition(*tailR,
                         partial_tail,
                         &shift_head,
                         &shift_tail) == FAILURE)
            {
                delete_list(&partial_head, &partial_tail);
                delete_list(&shift_head, &shift_tail);
                delete_list(headR, tailR);
                return FAILURE;
            }

            delete_list(headR, tailR);
            delete_list(&partial_head, &partial_tail);

            *headR = shift_head;
            *tailR = shift_tail;

            shift_head = NULL;
            shift_tail = NULL;
        }

        shift++;
        temp2 = temp2->prev;
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}