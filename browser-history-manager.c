#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)

struct Node
{
    char month[20];
    char category1[20];
    float expenses1;
    char category2[20];
    float expenses2;
    char category3[20];
    float expenses3;
    bool deleted;
    struct Node* next;
    struct Node* prev;
};

struct Node* CreateExpense(char* month, char* category1, float expenses1, char* category2, float expenses2, char* category3, float expenses3)
{
    struct Node* newExpense = (struct Node*)malloc(sizeof(struct Node));
    if (newExpense == NULL)
    {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    strcpy(newExpense->month, month);
    strcpy(newExpense->category1, category1);
    newExpense->expenses1 = expenses1;
    strcpy(newExpense->category2, category2);
    newExpense->expenses2 = expenses2;
    strcpy(newExpense->category3, category3);
    newExpense->expenses3 = expenses3;
    newExpense->next = NULL;
    newExpense->prev = NULL;
    return newExpense;
}

struct Node* InsertAtEnd(struct Node* expenses, struct Node** lastExpense, char* month, char* category1, float expenses1, char* category2, float expenses2, char* category3, float expenses3)
{
    struct Node* newExpense = CreateExpense(month, category1, expenses1, category2, expenses2, category3, expenses3);
    if (*lastExpense == NULL)
    {
        *lastExpense = newExpense;
        return newExpense;
    }
    (*lastExpense)->next = newExpense;
    newExpense->prev = *lastExpense;
    *lastExpense = newExpense;
    return expenses;
}

float SearchMonthExpenses(struct Node* head, char* targetMonth)
{
    struct Node* current = head;
    bool monthFound = false;

    while (current != NULL)
    {
        if (strcmp(current->month, targetMonth) == 0)
        {
            monthFound = true;
            printf("Expenses for %s:\n", targetMonth);
            printf("Category\tExpense\n");
            printf("------------------------\n");
            printf("%s\t$%.2f\n", current->category1, current->expenses1);
            printf("%s\t$%.2f\n", current->category2, current->expenses2);
            printf("%s\t$%.2f\n", current->category3, current->expenses3);
            printf("\n");
            return current->expenses1 + current->expenses2 + current->expenses3;
        }
        current = current->next;
    }

    if (!monthFound)
    {
        printf("Month of %s is not found.\n", targetMonth);
        return -1;
    }
}

void DeleteNode(struct Node* head, char* targetMonth)
{
    struct Node* current = head;

    while (current != NULL)
    {
        if (strcmp(current->month, targetMonth) == 0)
        {
            current->deleted = true;
            printf("Expenses for %s have been deleted.\n", targetMonth);
            return;
        }
        current = current->next;
    }
    printf("Month of %s is not found.\n", targetMonth);
}

struct Node* SearchDeletedNode(struct Node* head)
{
    struct Node* current = head;

    while (current != NULL)
    {
        if (current->deleted)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

enum menuItems
{
    menuNothing = 0,
    insertElement = 1,
    deleteElement,
    searchElement,
    menuQuit
};

int main(void)
{
    struct Node* head = NULL;
    struct Node* lastExpense = NULL;

    char months[12][20] = { "January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December" };

    
    for (int i = 0; i < 12; i++)
    {
        head = InsertAtEnd(head, &lastExpense, months[i], strdup("Bills"), 0, strdup("Food"), 0, strdup("Entertainment"), 0);
    }
    menuItems choice = menuNothing;
    char buf[20] = { 0 };

    do
    {
        printf("\nPlease select menu option\n");
        printf("To fill month element press 1\n");
        printf("To delete pre-existing element press 2\n");
        printf("To search for already existing element press 3\n");
        printf("To exit program press 4\n");

        fgets(buf, sizeof buf, stdin);
        for (int i = 0; i < sizeof buf; i++)
        {
            if (buf[i] == '\n') 
            {
                buf[i] = '\0';
                break;
            }
        }

        choice = (menuItems)atoi(buf);

        switch (choice)
        {
        case insertElement:
        {
            float expense1, expense2, expense3;
            struct Node* toInsert = SearchDeletedNode(head);

            if (toInsert != NULL)
            {

                printf("Enter the expense for %s: ", toInsert->category1);
                fgets(buf, sizeof buf, stdin);
                expense1 = atof(buf);


                printf("Enter the expense for %s: ", toInsert->category2);
                fgets(buf, sizeof buf, stdin);
                expense2 = atof(buf);

                

                printf("Enter the expense for %s: ", toInsert->category3);
                fgets(buf, sizeof buf, stdin);
                expense3 = atof(buf);

                toInsert->expenses1 = expense1;
                toInsert->expenses2 = expense2;
                toInsert->expenses3 = expense3;
                toInsert->deleted = false;
            }
            else
            {
                printf("All months have expenses.\n");
            }
            break;
        }
        case deleteElement:
        {
            char month[20];
            printf("Enter the month to delete: ");
            fgets(month, sizeof month, stdin);

            for (int i = 0; i < sizeof month; i++)
            {
                if (month[i] == '\n') {
                    month[i] = '\0';
                    break;
                }
            }

            DeleteNode(head, month);
            break;
        }
        case searchElement:
        {
            char inputMonth[20];
            printf("Enter a month to search for: ");
            fgets(inputMonth, sizeof inputMonth, stdin);

            for (int i = 0; i < sizeof inputMonth; i++)
            {
                if (inputMonth[i] == '\n') {
                    inputMonth[i] = '\0';
                    break;
                }
            }

            float expenses = SearchMonthExpenses(head, inputMonth);

            if (expenses != -1)
            {
                printf("Total expenses for %s: $%.2f\n", inputMonth, expenses);
            }
            break;
        }
        default:
        {
            printf("Please input a valid key.\n");
        }
        }
        
    } while (choice != menuQuit);

    return 0;
}


    return 0;
}
