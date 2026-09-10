#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL;
    node *tail1 = NULL;
    node *head2 = NULL;
    node *tail2 = NULL;
    node *headR = NULL;
    node *tailR = NULL;

    int sign1;
    int sign2;
    int status;

    if (cla_validation(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    sign1 = get_sign(&argv[1]);
    sign2 = get_sign(&argv[3]);

    if (create_list(argv[1], &head1, &tail1) == FAILURE)
    {
        return FAILURE;
    }

    if (create_list(argv[3], &head2, &tail2) == FAILURE)
    {
        delete_list(&head1, &tail1);
        return FAILURE;
    }

    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    switch (argv[2][0])
    {
        case '+':
            status = handle_addition(head1, tail1,
                                     head2, tail2,
                                     &headR, &tailR,
                                     sign1, sign2);
            break;

        case '-':
            status = handle_subtraction(head1, tail1,
                                        head2, tail2,
                                        &headR, &tailR,
                                        sign1, sign2);
            break;

        case 'x':
        case 'X':
            status = multiplication(tail1, tail2,
                                     &headR, &tailR);

            if (status == SUCCESS)
            {
                if (!is_zero_list(headR) &&
                    sign1 != sign2)
                {
                    printf("Result = -");
                }
                else
                {
                    printf("Result = ");
                }

                print_list(headR);
            }
            break;

        case '/':
            status = division(head1, head2, tail2,
                              &headR, &tailR);

            if (status == SUCCESS)
            {
                if (!is_zero_list(headR) &&
                    sign1 != sign2)
                {
                    printf("Quotient = -");
                }
                else
                {
                    printf("Quotient = ");
                }

                print_list(headR);
            }
            break;

        default:
            status = FAILURE;
            break;
    }

    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return status == SUCCESS ? SUCCESS : FAILURE;
}