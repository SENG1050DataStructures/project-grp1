#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CategoryExpense
{
    char category[20];
    float expense;
};

struct Node
{
    char month[20];
    struct CategoryExpense categories[3];
    bool deleted;
    struct Node* next;
    struct Node* prev;
};


struct Node* CreateExpense(char* month, const char* category1, float expenses1,const char* category2, float expenses2, const char* category3, float expenses3)
{
    struct Node* newExpense = (struct Node*)malloc(sizeof(struct Node));
    if (newExpense == NULL)
    {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    strncpy_s(newExpense->month, month, sizeof(newExpense->month) - 1);
    
    strncpy_s(newExpense->categories[0].category, category1, sizeof(newExpense->categories[0].category) - 1);
    newExpense->categories[0].expense = expenses1;
    strncpy_s(newExpense->categories[1].category, category2, sizeof(newExpense->categories[1].category) - 1);
    newExpense->categories[1].expense = expenses2;
    strncpy_s(newExpense->categories[2].category, category3, sizeof(newExpense->categories[2].category) - 1);
    newExpense->categories[2].expense = expenses3;
    newExpense->next = NULL;
    newExpense->prev = NULL;
    return newExpense;
}


struct Node* InsertAtEnd(struct Node* expenses, struct Node** lastExpense, char* month, const char* category1, float expenses1, const char* category2, float expenses2, const char* category3, float expenses3)
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
           
            for (int i = 0; i < 3; i++)
            {
                printf("%s\t$%.2f\n", current->categories[i].category, current->categories[i].expense);
            }
            printf("\n");
            
            return current->categories[0].expense + current->categories[1].expense + current->categories[2].expense;
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
        head = InsertAtEnd(head, &lastExpense, months[i], "Bills", 0, "Food", 0, "Entertainment", 0);
    }

    enum menuItems choice = menuNothing;
    char buf[20] = { 0 };

    do
    {
        printf("\nPlease select menu option\n");
        printf("To fill month element press 1\n");
        printf("To delete pre-existing element press 2\n");
        printf("To search for already existing element press 3\n");
        printf("To exit program press 4\n");

        fgets(buf, sizeof buf, stdin);
        for (int i = 0; i < strlen(buf); i++)
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
            fgets(inputMonth, sizeof inputMonth, stdin);

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
