#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    int data;
    node *next;
};

node *createNode(int data);
node *createLinkedListFromArray(int length, int array[]);
node *createLinkedListFromUserInput();
int getLength(node *head);
node *insert(node *head, int index, int item);
void append(node *head, int item);
void traverseLinkedList(node *head);
node *insertBeforeNode(node *head, int before, int data);
node *insertAfterNode(node *head, int after, int data);
node *delete(node *head, int query);
node *reverseLinkedList(node *head);
void sortLinkedList(node *head);
int getItemAtIndex(node *head, int index);
void setItemAtIndex(node *head, int index, int data);
node *insertWhileSorted(node *head, int item);
void deleteAlternateNode(node *head);

void main()
{
    int opt = 0,
        temp,
        temp_bf_af;

    int test_array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5};
    // int test_array[] = {50, 40, 30, -5, 20};
    // int test_array[] = {-3};

    // creating
    node *list = createLinkedListFromArray(
        sizeof(test_array) / sizeof(test_array[0]),
        test_array);
    // node *list = createLinkedListFromUserInput();

    printf("\nTraversing linked list:\n");
    printf("Length of linked list: %d\n", getLength(list));
    traverseLinkedList(list);

    while (opt != 9)
    {
        printf("Available options:\n\
        1 Insert an element before another element in the existing list\n\
        2 Insert an element after another element in the existing list\n\
        3 Delete a given element from the list\n\
        4 Traverse the list\n\
        5 Reverse the list\n\
        6 Sort the list\n\
        7 Delete every alternate node in the list\n\
        8 Insert an element in a sorted list such that the order is maintained\n\
        9 Exit\n");
        printf("Enter option: ");
        scanf("%d", &opt);
        printf("\n");

        switch (opt)
        {
        case 1:
            printf("Enter element to insert before: ");
            scanf("%d", &temp_bf_af);
            printf("Enter element to insert: ");
            scanf("%d", &temp);
            list = insertBeforeNode(list, temp_bf_af, temp);
            break;

        case 2:
            printf("Enter element to insert after: ");
            scanf("%d", &temp_bf_af);
            printf("Enter element to insert: ");
            scanf("%d", &temp);
            list = insertAfterNode(list, temp_bf_af, temp);
            break;

        case 3:
            printf("Enter element to delete: ");
            scanf("%d", &temp);
            list = delete (list, temp);
            break;

        case 4:
            printf("\nTraversing linked list:\n");
            traverseLinkedList(list);
            break;

        case 5:
            list = reverseLinkedList(list);
            printf("\nAfter reversing:\n");
            traverseLinkedList(list);
            break;

        case 6:
            sortLinkedList(list);
            printf("\nAfter sorting:\n");
            traverseLinkedList(list);
            break;

        case 7:
            deleteAlternateNode(list);
            printf("\nAfter deleting every alternate node:\n");
            traverseLinkedList(list);
            break;

        case 8:
            printf("Enter element to insert: ");
            scanf("%d", &temp);
            list = insertWhileSorted(list, temp);
            printf("\nAfter inserting element while order is maintained:\n");
            traverseLinkedList(list);
            break;

        case 9:
            printf("Exiting\n");
            break;

        default:
            printf("Invalid option: %d\n", opt);
        }
    }
}

node *createNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));

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

    node *head = createNode(array[0]);

    for (int i = 1; i < length; i++)
        append(head, array[i]);

    return head;
}

node *createLinkedListFromUserInput()
{
    int n, temp;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    scanf("%d", &temp);
    node *head = createNode(temp);

    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &temp);
        append(head, temp);
    }

    return head;
}

int getLength(node *head)
{
    node *n = head;
    int i = 1;

    while ((n = n->next) != NULL)
        i++;

    return i;
}

node *insert(node *head, int index, int item)
{
    node *n = head;
    int i = 1;
    node *newNode = createNode(item);

    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        while (i++ < index)
            n = n->next;

        newNode->next = n->next;
        n->next = newNode;
    }

    return head;
}

void append(node *head, int item)
{
    insert(head, getLength(head), item);
}

void traverseLinkedList(node *head)
{
    node *n = head;

    while (n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n\n");
}

node *insertBeforeNode(node *head, int before, int data)
{
    // searching for before
    node *n = head;
    int found = 0;

    if (n->data == before)
        found = 1;
    else
    {
        do
        {
            if (n->next->data == before)
            {
                found = 1;
                break;
            }
            n = n->next;
        } while ((n->next->next) != NULL);

        if (!found && n->next->data == before)
            found = 1;
    }

    if (found)
    {
        node *new = createNode(data);

        if (n == head)
        {
            new->next = n;
            head = new;
        }
        else
        {
            new->next = n->next;
            n->next = new;
        }
    }
    else
        printf("%d NOT found\n", before);

    return head;
}

node *insertAfterNode(node *head, int after, int data)
{
    // searching for after
    node *n = head;
    int i = 0, found = 0;

    do
    {
        if (n->data == after)
        {
            found = 1;
            break;
        }
        n = n->next;
    } while ((n->next) != NULL);
    if (!found && n->data == after)
        found = 1;

    if (found)
    {
        node *new = createNode(data);
        new->next = n->next;
        n->next = new;
    }
    else
        printf("%d NOT found\n", after);

    return head;
}

node *delete(node *head, int query)
{
    node *n = head, *toBeDeleted;
    int found = 0;

    // checking head
    if (n->data == query)
    {
        found = 1;
        head = n->next;
        free(n);
    }
    else
    {
        do
        {
            if (n->next->data == query)
            {
                found = 1;
                toBeDeleted = n->next;
                n->next = n->next->next;
                free(toBeDeleted);
                break;
            }
            n = n->next;
        } while (n->next->next != NULL);

        // checking tail
        if (!found && n->next->data == query)
        {
            found = 1;
            toBeDeleted = n->next;
            n->next = NULL;
            free(toBeDeleted);
        }
    }

    if (!found)
        printf("%d NOT found in list\n", query);

    return head;
}

int getItemAtIndex(node *head, int index)
{
    node *n = head;
    int i = 0;

    if (index == 0)
        return head->data;
    else
        while (++i <= index)
            n = n->next;

    return n->data;
}

void setItemAtIndex(node *head, int index, int data)
{
    node *n = head;
    int i = 0;

    if (index == 0)
        head->data = data;
    else
        while (++i <= index)
            n = n->next;

    n->data = data;
}

node *reverseLinkedList(node *head)
{
    node *n = head, *prev = NULL, *next;

    while (n != NULL)
    {
        next = n->next;
        n->next = prev;
        prev = n;
        n = next;
    }

    return prev;
}

void sortLinkedList(node *head)
{
    node *n = head;
    int count, key, j;
    count = getLength(head);

    for (int i = 1; i < count; i++)
    {
        key = getItemAtIndex(head, i);
        for (j = i; getItemAtIndex(head, j - 1) > key && j >= 1; j--)
            setItemAtIndex(head, j, getItemAtIndex(head, j - 1));
        setItemAtIndex(head, j, key);
    }
}

node *insertWhileSorted(node *head, int item)
{
    node *n = head, *newNode = createNode(item);

    if (n->data < item)
    {
        do
        {
            if (n->next->data > item)
                break;
            n = n->next;
        } while (n->next != NULL);

        newNode->next = n->next;
        n->next = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }

    return head;
}

void deleteAlternateNode(node *head)
{
    node *n = head;
    int len = getLength(head);

    if (len == 2)
    {
        n->next = NULL;
        return;
    }
    else if (len < 2)
        return;

    while (n != NULL && n->next != NULL && n->next->next != NULL)
    {
        node *toBeDeleted = n->next;
        n->next = n->next->next;
        if (n->next->next != NULL)
            n = n->next;
        free(toBeDeleted);
    }
}
