#include "apc.h"

int subtraction(node *tail1,
                node *tail2,
                node **headR,
                node **tailR)
{
    int borrow = 0;

    if (headR == NULL || tailR == NULL)
    {
        return FAILURE;
    }

    *headR = NULL;
    *tailR = NULL;

    while (tail1 != NULL || tail2 != NULL)
    {
        int digit1 = 0;
        int digit2 = 0;
        int result;

        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        digit1 -= borrow;

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result = digit1 - digit2;

        if (insert_first(headR, tailR, result) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            return FAILURE;
        }
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