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
node *delete(node *head, int index);
void append(node *head, int item);
void traverseLinkedList(node *head);
node *insertRear(node *head, int item);
node *deleteRear(node *head);
node *insertBeforeNode(node *head, int temp_bf_af, int temp);
node *insertAfterNode(node *head, int temp_bf_af, int temp);
node *reverseDoublyLinkedList(node *head);

void main()
{
    int opt = 0,
        temp,
        pos,
        temp_bf_af;

    // int test_array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5};
    int test_array[] = {50, 20, 30};
    // int test_array[] = {-3};

    // creating
    node *list = createLinkedListFromArray(
        sizeof(test_array) / sizeof(test_array[0]),
        test_array);
    // node *list = createLinkedListFromUserInput();

    while (opt != 9)
    {
        traverseLinkedList(list);

        printf("Available options:\n\
        1 Insert at rear end\n\
        2 Delete tail\n\
        3 Insert an element at a given position\n\
        4 Delete an element from a given position\n\
        5 Insert an element before another element\n\
        6 Insert an element after another element\n\
        7 Traverse the list\n\
        8 Reverse the list\n\
        9 Exit\n");
        printf("Enter option: ");
        scanf("%d", &opt);

        switch (opt)
        {

        case 1:
            printf("Enter element to insert at rear: \n");
            scanf("%d", &temp);
            list = insertRear(list, temp);
            printf("List after tail insertion:\n");
            break;

        case 2:
            list = deleteRear(list);
            printf("List after tail deletion:\n");
            break;

        case 3:
            printf("Enter element: \n");
            scanf("%d", &temp);
            printf("Enter position to insert at: \n");
            scanf("%d", &pos);
            list = insert(list, pos - 1, temp);
            printf("List after insertion:\n");
            break;

        case 4:
            printf("Enter position of element to delete: ");
            scanf("%d", &pos);
            list = delete (list, pos - 1);
            printf("List after deletion:\n");
            break;

        case 5:
            printf("Enter element to insert: ");
            scanf("%d", &temp);
            printf("Enter element to insert before: ");
            scanf("%d", &temp_bf_af);
            list = insertBeforeNode(list, temp_bf_af, temp);
            printf("List after insertion:\n");
            break;

        case 6:
            printf("Enter element to insert: ");
            scanf("%d", &temp);
            printf("Enter element to insert after: ");
            scanf("%d", &temp_bf_af);
            list = insertAfterNode(list, temp_bf_af, temp);
            printf("List after insertion:\n");
            break;

        case 7:
            printf("\nTraversing linked list:\n");
            traverseLinkedList(list);
            break;

        case 8:
            list = reverseDoublyLinkedList(list);
            printf("\nAfter reversing:\n");
            break;

        case 9:
            printf("Exiting\n");
            break;

        default:
            printf("Invalid option: %d\n\n", opt);
        }
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
    node *n = head;
    int i = 1;

    if (index == 0)
    {
        node *newNode = createNode(head->prev, item);
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

node *delete(node *head, int index)
{
    node *n = head, *toBeDeleted;
    int i = 0, len = getLength(head);

    if (len < 1)
    {
        free(head);
        return NULL;
    }
    if (index == 0)
    {
        toBeDeleted = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
        free(toBeDeleted);
        return head;
    }
    else if (index <= len)
    {
        while (i++ < index)
            n = n->next;

        printf("gonna del %d", n->data);

        toBeDeleted = n;
        n->next->prev = n->prev;
        n->prev->next = n->next;
        free(toBeDeleted);
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
        return;
    node *n = head;

    int i = 0;
    do
    {
        printf("%d ", n->data);
        n = n->next;
    } while (n != head && i++ < 10);
    printf("\n\n");
}

node *insertRear(node *head, int item)
{
    if (head == NULL)
    {
        node *new = createNode(NULL, item);
        new->next = new;
        new->prev = new;
        return new;
    }
    else
    {
        node *tail = head->prev, *new = createNode(tail, item);
        tail->next = new;
        new->next = head;
        head->prev = new;
        return head;
    }
}

node *deleteRear(node *head)
{
    if (getLength(head) < 2)
        return NULL;

    node *newTail = head->prev->prev, *deleted = head->prev;
    newTail->next = head;
    head->prev = newTail;
    free(deleted);
    return head;
}

node *insertBeforeNode(node *head, int temp_bf_af, int temp)
{
    node *n = head;

    do
    {
        if (n->data == temp_bf_af)
            break;
        n = n->next;
    } while (n != head);

    node *new = createNode(n->prev, temp);
    new->prev->next = new;
    new->next = n;
    new->next->prev = new;

    if (n == head)
        return new;
    return head;
}

node *insertAfterNode(node *head, int temp_bf_af, int temp)
{
    node *n = head;

    do
    {
        if (n->data == temp_bf_af)
            break;
        n = n->next;
    } while (n != head);

    printf("%d\n", n->data);

    node *new = createNode(n, temp);
    new->next = n->next;
    new->next->prev = new;
    n->next = new;
    printf("%d\n", new->data);

    return head;
}

node *reverseDoublyLinkedList(node *head)
{
    node *n = head, *temp;

    int i = 0;
    do
    {
        i++;
        temp = n->next;
        n->next = n->prev;
        n = n->prev = temp;
    } while (n != head);
    head = n->next;

    return head;
}
