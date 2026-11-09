
#include <stdio.h>

int main()
{
    int n, i, j, k;
    int a[10], b[10];
    int final[10];
    int mark[10][10];
    int changed;

    printf("Enter number of states: ");
    scanf("%d", &n);

    if (n < 1 || n > 10)
    {
        printf("Invalid number of states");
        return 0;
    }

    printf("Enter transition for input a:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter transition for input b:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);

    printf("Enter final states (1 for Final, 0 for Non-Final):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &final[i]);


    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mark[i][j] = 0;
        }
    }


    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (final[i] != final[j])
            {
                mark[i][j] = 1;
            }
        }
    }


    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (mark[i][j] == 0)
                {
                    int x = a[i], y = a[j];


                    if (x != y)
                    {
                        if (x < y)
                        {
                            if (mark[x][y])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                                continue;
                            }
                        }
                        else
                        {
                            if (mark[y][x])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                                continue;
                            }
                        }
                    }

                    x = b[i];
                    y = b[j];

                    if (x != y)
                    {
                        if (x < y)
                        {
                            if (mark[x][y])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                            }
                        }
                        else
                        {
                            if (mark[y][x])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }

    } while (changed);

    printf("\nEquivalent States:\n");

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (mark[i][j] == 0)
            {
                printf("(%d,%d)\n", i, j);
            }
        }
    }

    return 0;
}

