

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

struct Node 
{
    char month[20];
    float expenses;
    struct Node* next;
    struct Node* prev;
};
struct Node* createExpense(char month,float expenses){
    struct Node* newExpense = (struct Node*)malloc(sizeof(struct Node));
    if(Node == NULL){
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    Node->month = month;
    Node->expenses = expenses;
    Node->next = NULL;
    Node->prev = NULL;
    return newExpense;
}
struct Node* InsertNewExpense(struct Node* headExpenses,struct Node** lastExpense,char* month,float expenese){
    struct Node* newExpense = CreateExpense(month,expense);
    if (headExpenses == NULL || strcmp(headExpenses->month, month) > 0) {
        *lastExpense = newExpense;
        return newExpense;
    }
    struct Node* currentExpense = headExpenses;
    while (currentExpense->next != NULL && strcmp(currentExpense->next->month, month) < 0) { 
        currentExpense = currentExpense->next;
    }
    newExpense->next = currentExpense->next;
    currentExpense->next = newExpense;
    newExpense->prev = currentExpense;
    if (newExpense->next != NULL) {
        newExpense->next->prev = newExpense;
    } else {
        *lastExpense = newExpense;
    }
    return headExpenses;
}
struct Node* InsertAtEnd(struct Node* expenses,struct Node** lastExpense,char* month,float expenese){
    struct Node* newExpense = CreateExpense(month,expense);
    if(lastExpense == NULL){
        printf("No Memory");
        exit(EXIT_FAILURE);
    }
    newExpense->month = month;
    newExpense->expense = expense;
    newExpense->next = NULL;
}

float searchMonthExpenses(struct Node* head, char* target_month) 
{
    struct Node* current = head;

    
    while (current != NULL)
    {
        
        if (strcmp(current->month, target_month) == 0) 
        {
            
            return current->expenses;
        }
       
        current = current->next;
    }

   
    return -1; 
}

int main(void) 
{
    
    struct Node* head = NULL;

    
    char months[12][20] = { "January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December" };

    float dummy_expenses = 1000.0;

    for (int i = 0; i < 12; i++) 
    {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        strcpy(new_node->month, months[i]);
        new_node->expenses = dummy_expenses * (i + 1); 
        new_node->next = NULL;
        new_node->prev = NULL;

        if (head == NULL) 
        {
            head = new_node;
        }
        else 
        {
            struct Node* current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_node;
            new_node->prev = current;
        }
    }

    
    char input_month[20];
    printf("Enter a month to search for: ");
    scanf("%s", input_month);

   
    float expenses = searchMonthExpenses(head, input_month);

    if (expenses != -1) 
    {
        printf("Expenses for %s: $%.2f\n", input_month, expenses);
    }
    else 
    {
        printf("Month of %s is not found.\n", input_month);
    }

   

    return 0;
}
