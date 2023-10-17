#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    node *prev;
    int data;
    node *next;
};

node *createNode(node *prev, int data);
node *createLinkedListFromArray(int length, int array[]);
node *createLinkedListFromUserInput();
int getLength(node *head);
node *insert(node *head, int index, int item);
void append(node *head, int item);
node *delete (node *head, int item);
void traverseLinkedList(node *head);
node *findElement(node *head, int item);

void main()
{
    int opt = 0,
        temp,
        pos;

    // int test_array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5};
    int test_array[] = {50, 20, 30};
    // int test_array[] = {-3};

    // creating
    node *list = createLinkedListFromArray(
        sizeof(test_array) / sizeof(test_array[0]),
        test_array);
    // node *list = createLinkedListFromUserInput();

    printf("List at beginning:\n");
    traverseLinkedList(list);

    while (opt != 3)
    {
        printf("Available options:\n\
        1 Insert\n\
        2 Delete\n\
        3 Exit\n");
        printf("Enter option: ");
        scanf("%d", &opt);

        switch (opt)
        {

        case 1:
            printf("Enter position to insert at: \n");
            scanf("%d", &pos);
            printf("Enter element: \n");
            scanf("%d", &temp);
            list = insert(list, pos, temp);
            printf("List after insertion:\n");
            traverseLinkedList(list);
            break;

        case 2:
            printf("Enter element to delete: ");
            scanf("%d", &temp);
            list = delete (list, temp);
            printf("\nList after deletion:\n");
            traverseLinkedList(list);
            break;

        case 3:
            printf("Exiting\n");
            break;

        default:
            printf("Invalid option: %d\n\n", opt);
            break;
        }

        // break;
    }
}

node *createNode(node *prev, int data)
{
    /*
    unlike local variables, variables initialised with malloc()
    are not destroyed after function exit
    they also have new memory addresses as compared to doing:
    node temp;
    */
    node *temp = (node *)malloc(sizeof(node));

    temp->prev = prev;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

node *createLinkedListFromArray(int length, int array[])
{
    if (length == 0)
    {
        printf("Array should have at least one element\n");
        exit(0);
    }

    node *head = createNode(NULL, array[0]);

    for (int i = 1; i < length; i++)
        append(head, array[i]);

    node *n = head;
    while (n->next != NULL)
        n = n->next;
    n->next = head;
    head->prev = n;

    return head;
}

node *createLinkedListFromUserInput()
{
    int count, temp;
    printf("Enter number of elements: ");
    scanf("%d", &count);

    printf("Enter elements:\n");
    scanf("%d", &temp);
    node *head = createNode(NULL, temp);

    for (int i = 0; i < count - 1; i++)
    {
        scanf("%d", &temp);
        append(head, temp);
    }

    node *n = head;
    while (n->next != NULL)
        n = n->next;
    n->next = head;
    head->prev = n;

    return head;
}

int getLength(node *head)
{
    node *n = head;
    int length = 1;

    if (n == NULL)
        return 0;

    while (n->next && (n = n->next) != head)
        length++;

    return length;
}

node *insert(node *head, int index, int item)
{
    node *n = head, *newNode;
    int i = 1;

    if (!head)
    {
        newNode = createNode(NULL, item);
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }
    else if (index == 0)
    {
        newNode = createNode(head->prev, item);
        newNode->next = head;
        head->prev->next = newNode;
        head = newNode;
    }
    else if (index <= getLength(head))
    {
        while (i++ < index)
            n = n->next;

        node *newNode = createNode(n, item);
        newNode->next = n->next;
        n->next = newNode;
    }
    else
        printf("\nGiven index is greater than maximum index\n\n");

    return head;
}

void append(node *head, int item)
{
    insert(head, getLength(head), item);
}

void traverseLinkedList(node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n\n");
        return;
    }
    node *n = head;

    if (n == NULL)
        return;

    do
        printf("%d ", n->data);
    while ((n = n->next) != head);
    printf("\n\n");
}

node *delete (node *head, int item)
{
    node *n, *toBeDeleted;
    int i = 1, len = getLength(head);

    n = findElement(head, item);

    if (n == NULL)
    {
        printf("%d not found in doubly linked list\n\n", item);
        return head;
    }

    else if (n == head && len == 1)
        return NULL;

    else if (n == head && len < 1)
    {
        printf("Doubly linked list is empty\n");
        return NULL;
    }

    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        toBeDeleted = n;
        n = n->next;
        free(toBeDeleted);
        return n;
    }
}

node *findElement(node *head, int item)
{

    if (head == NULL)
        return NULL;
    node *n = head;

    do
    {
        if (n->data == item)
            return n;
    } while ((n = n->next) != head);

    return NULL;
}
