#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    int coeff; // coefficient
    int exp;   // exponent
    node *next;
};

node *createNode(int coeff, int exp);
node *createLinkedListFromArray(int length, int array[][2]);
node *createLinkedListFromUserInput();
int getLength(node *head);
node *insert(node *head, int index, int coeff, int exp);
void append(node *head, int coeff, int exp);
void appendNode(node *head, node *new);
void printPolynomial(node *head);
node *findNodeWithGivenExpo(node *head, int exp);
node *polyMultiply(node *poly_a, node *poly_b);

void main()
{
    // int poly_array_1[][2] = {
    //     {1, 3},
    //     {3, 2},
    // };

    // int poly_array_2[][2] = {
    //     {-5, 2},
    //     {2, 1},
    // };

    int poly_array_1[][2] = {
        {3, 1},
        {6, 0},
    };

    int poly_array_2[][2] = {
        {5, 2},
        {3, 1},
        {10, 0},
    };

    // creating
    node *poly_a = createLinkedListFromArray(
        sizeof(poly_array_1) / sizeof(poly_array_1[0]),
        poly_array_1);
    node *poly_b = createLinkedListFromArray(
        sizeof(poly_array_2) / sizeof(poly_array_2[0]),
        poly_array_2);

    // node *poly_a = createLinkedListFromUserInput();
    // node *poly_b = createLinkedListFromUserInput();

    // traversing
    printf("\nPrinting polynomial A:\n");
    printPolynomial(poly_a);
    printf("\nPrinting polynomial B:\n");
    printPolynomial(poly_b);

    node *poly_multiplied = polyMultiply(poly_a, poly_b);
    printf("\nPrinting (A + B):\n");
    printPolynomial(poly_multiplied);

    printf("\n");
}

node *createNode(int coeff, int exp)
{
    /*
    unlike local variables, variables initialised with malloc()
    are not destroyed after function exit
    they also have new memory addresses as compared to doing:
    node temp;
    */
    node *temp = (node *)malloc(sizeof(node));

    temp->coeff = coeff;
    temp->exp = exp;
    temp->next = NULL;
    return temp;
}

node *createLinkedListFromArray(int length, int array[][2])
{
    if (length < 0)
    {
        printf("Array should have at least one element\n");
        exit(0);
    }

    node *head = createNode(array[0][0], array[0][1]);

    for (int i = 1; i < length; i++)
        append(head, array[i][0], array[i][1]);

    return head;
}

node *createLinkedListFromUserInput()
{
    int n, power, temp, i;
    node *head;

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    i = 0;
    do
    {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &temp, &power);
        if (!i)
            head = createNode(temp, power);
        else
            append(head, temp, power);
    } while (i++ < n - 1);

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

node *insert(node *head, int index, int coeff, int exp)
{
    // returns pointer to head just in case element inserted at head

    if (index < 0 || index > getLength(head))
    {
        printf("Given index %d outside range\n", index);
        exit(0);
    }

    node *n = head;
    int i = 1;
    node *newNode = createNode(coeff, exp);

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

void append(node *head, int coeff, int exp)
{
    insert(head, getLength(head), coeff, exp);
}

void appendNode(node *head, node *new)
{
    node *n = head;

    while (n->next != NULL)
        n = n->next;

    n->next = new;
}

void printPolynomial(node *head)
{
    node *n = head;

    while (n != NULL)
    {
        if (n->next == NULL || n->next->coeff < 0)
            printf("%dx^%d ", n->coeff, n->exp);
        else
            printf("%dx^%d + ", n->coeff, n->exp);

        n = n->next;
    }
    printf("\n");
}

node *findNodeWithGivenExpo(node *head, int exp)
{
    node *n = head;
    if (n->next == NULL)
        return NULL;
    else
        // skip initial placeholder 0x^0 node
        n = n->next;

    do
        if (n->exp == exp)
            return n;
    while ((n = n->next) != NULL);

    return NULL;
}

node *polyMultiply(node *a, node *b)
{
    int sum;
    node *b_orig = b, *result = createNode(0, 0), *new, *expoPresentInResult;

    while (a != NULL && b != NULL)
    {
        node *new = createNode(a->coeff * b->coeff, a->exp + b->exp);
        expoPresentInResult = findNodeWithGivenExpo(result, new->exp);

        if (expoPresentInResult != NULL)
            expoPresentInResult->coeff += new->coeff;
        else
            appendNode(result, new);

        b = b->next;
        if (b == NULL)
        {
            a = a->next;
            b = b_orig;
        }
    }

    // skip initial placeholder
    return result->next;
}
