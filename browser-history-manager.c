#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char month[20];
    float expenses[3];
    bool deleted;
    struct Node* next;
    struct Node* prev;
};


struct Node* CreateExpense(char* month, float expenses[3])
{
    struct Node* newExpense = (struct Node*)malloc(sizeof(struct Node));
    if (newExpense == NULL)
    {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    strncpy_s(newExpense->month, month, sizeof(newExpense->month) - 1);
    newExpense->next = NULL;
    newExpense->prev = NULL;
    return newExpense;
}


struct Node* InsertAtEnd(struct Node* expenses, struct Node** lastExpense, char* month, float expensesArray[3])
{
    struct Node* newExpense = CreateExpense(month, expensesArray);
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
    const char* categories[3] = { "Bills", "Food", "Entertainment" };
        while (current != NULL)
        {
            if (strcmp(current->month, targetMonth) == 0)
            {
                monthFound = true;
                printf("Expenses for %s:\n", targetMonth);
                printf("Category\tExpense\n");
                printf("------------------------\n");

                for (int i = 0; i < 3; i++)
                {
                    printf("%s\t$%.2f\n", categories[i], current->expenses[i]);
                }
                printf("\n");

                return current->expenses[0] + current->expenses[1] + current->expenses[2];;
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
    float expenses[3] = {};
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
    float expenses[3] = {};
    const char* categories[3] = { "Bills", "Food", "Entertainment" };
    char months[12][20] = { "January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December" };
    
    for (int i = 0; i < 12; i++)
    {
        head = InsertAtEnd(head, &lastExpense, months[i], expenses);
    }
    

    enum menuItems choice = menuNothing;
    char buf[20] = {};

    do
    {
        printf("\nPlease select menu option\n");
        printf("To fill month element press 1\n");
        printf("To delete pre-existing element press 2\n");
        printf("To search for already existing element press 3\n");
        printf("To exit program press 4\n");

        fgets(buf, sizeof buf, stdin);
        for (int i = 0; i < sizeof(buf); i++)
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
            float expenses[3] = {};
            struct Node* toInsert = SearchDeletedNode(head);
            if (toInsert != NULL)
            {

                for (int i = 0; i < 3; i++)
                {
                    printf("For the month of %s\n", toInsert->month);
                    printf("Enter the expense for %s: ", toInsert->categories[i].category);
                    fgets(buf, sizeof buf, stdin);
                    expenses[i] = atof(buf);
                }


                for (int i = 0; i < 3; i++)
                {
                    toInsert->categories[i].expense = expenses[i];
                }

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

            for (int i = 0; i < strlen(month); i++)
            {
                if (month[i] == '\n')
                {
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
            fgets(inputMonth, sizeof(inputMonth), stdin);

            for (int i = 0; i < strlen(inputMonth); i++)
            {
                if (inputMonth[i] == '\n')
                {
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
