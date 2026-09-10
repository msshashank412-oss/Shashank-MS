#include "apc.h"

int addition(node *tail1,
             node *tail2,
             node **headR,
             node **tailR)
{
    int carry = 0;
    int sum;

    if (headR == NULL || tailR == NULL)
    {
        return FAILURE;
    }

    *headR = NULL;
    *tailR = NULL;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        carry = sum / 10;
        sum = sum % 10;

        
        if (insert_first(headR, tailR, sum) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            return FAILURE;
        }
    }

    
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