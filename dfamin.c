#include <stdio.h>

#define MAX 20

int n, m;
char symbol[MAX];
int trans[MAX][MAX];
int final[MAX];
int group[MAX], newGroup[MAX];

int main()
{
    int i, j, k, changed;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols: ");
    for(i = 0; i < m; i++)
        scanf(" %c", &symbol[i]);

    printf("\nEnter transition table:\n");
    for(i = 0; i < n; i++)
    {
        printf("State q%d:\n", i);
        for(j = 0; j < m; j++)
        {
            printf("On %c -> ", symbol[j]);
            scanf("%d", &trans[i][j]);
        }
    }

    printf("\nEnter final states (1 for final, 0 otherwise):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    // Initial partition
    for(i = 0; i < n; i++)
    {
        if(final[i])
            group[i] = 1;
        else
            group[i] = 0;
    }

    do
    {
        changed = 0;

        for(i = 0; i < n; i++)
            newGroup[i] = -1;

        int groupNo = 0;

        for(i = 0; i < n; i++)
        {
            if(newGroup[i] != -1)
                continue;

            newGroup[i] = groupNo;

            for(j = i + 1; j < n; j++)
            {
                if(group[i] == group[j])
                {
                    int same = 1;

                    for(k = 0; k < m; k++)
                    {
                        if(group[trans[i][k]] != group[trans[j][k]])
                        {
                            same = 0;
                            break;
                        }
                    }

                    if(same)
                        newGroup[j] = groupNo;
                }
            }

            groupNo++;
        }

        for(i = 0; i < n; i++)
        {
            if(group[i] != newGroup[i])
            {
                changed = 1;
                break;
            }
        }

        for(i = 0; i < n; i++)
            group[i] = newGroup[i];

    } while(changed);

    printf("\nEquivalent State Groups:\n");

    int printed[MAX] = {0};

    for(i = 0; i < n; i++)
    {
        if(printed[group[i]])
            continue;

        printf("Group %d : ", group[i]);

        for(j = 0; j < n; j++)
        {
            if(group[j] == group[i])
            {
                printf("q%d ", j);
                printed[group[j]] = 1;
            }
        }

        printf("\n");
    }

    printf("\nMinimized DFA Transition Table\n");

    printf("Group\t");

    for(i = 0; i < m; i++)
        printf("%c\t", symbol[i]);

    printf("\n");

    for(i = 0; i < n; i++)
    {
        if(printed[group[i]] == 2)
            continue;

        printed[group[i]] = 2;

        printf("%d\t", group[i]);

        for(j = 0; j < m; j++)
            printf("%d\t", group[trans[i][j]]);

        printf("\n");
    }

    return 0;
}
