#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) x > y ? 1 : x < y ? -1 \
                                        : 0

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
void printPolynomial(node *head);
node *polyAddition(node *poly_a, node *poly_b);

void main()
{
    int poly_array_1[][2] = {
        {1, 3},
        {3, 2},
        {2, 1},
        {7, 0},
    };

    int poly_array_2[][2] = {
        {-5, 2},
        {2, 0},
        {19, -2},
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
    printf("Number of terms in polynomial A: %d\n\n", getLength(poly_a));
    printf("\nPrinting polynomial B:\n");
    printPolynomial(poly_b);
    printf("Number of terms in polynomial B: %d\n\n", getLength(poly_b));

    node *poly_sum = polyAddition(poly_a, poly_b);
    printf("\nPrinting (A + B):\n");
    printPolynomial(poly_sum);
    printf("Number of terms in polynomial (A + B): %d\n\n", getLength(poly_sum));
}

node *createNode(int coeff, int exp)
{
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

    // make tail point to head
    node *n = head;
    while (n->next)
        n = n->next;
    n->next = head;

    return head;
}

node *createLinkedListFromUserInput()
{
    int count, power, temp, i;
    node *head;

    printf("\nEnter number of elements: ");
    scanf("%d", &count);

    i = 0;
    do
    {
        printf("Enter coefficient and power: ");
        scanf("%d %d", &temp, &power);
        if (!i)
            head = createNode(temp, power);
        else
            append(head, temp, power);
    } while (i++ < count - 1);

    // make tail point to head
    node *n = head;
    while (n->next)
        n = n->next;
    n->next = head;

    return head;
}

int getLength(node *head)
{
    node *n = head;
    int i = 1;

    while (n->next && (n = n->next) != head)
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

void printPolynomial(node *head)
{
    node *n = head;

    do
    {
        if (n->next == head || n->next->coeff < 0)
            printf("%dx^%d ", n->coeff, n->exp);
        else
            printf("%dx^%d + ", n->coeff, n->exp);
        n = n->next;
    } while (n != head);
    printf("\n");
}

node *polyAddition(node *a, node *b)
{
    int sum, changed_a = 0, changed_b = 0;
    node *a_orig = a, *b_orig = b, *result = createNode(0, 0);

    do
    {
        switch (COMPARE(a->exp, b->exp))
        {
        case 1:
            append(result, a->coeff, a->exp);
            a = a->next;
            changed_a = 1;
            break;

        case 0:
            sum = a->coeff + b->coeff;
            append(result, sum, a->exp);
            a = a->next;
            b = b->next;
            changed_a = changed_b = 1;
            break;

        case -1:
            append(result, b->coeff, b->exp);
            b = b->next;
            changed_b = 1;
            break;
        }
    } while (!(changed_a && a == a_orig) &&
             !(changed_b && b == b_orig));

    // appending remaining terms which were not common to both
    while (!changed_a || a != a_orig)
    {
        append(result, a->coeff, a->exp);
        a = a->next;
        changed_a = 1;
    }
    while (!changed_b || b != b_orig)
    {
        append(result, b->coeff, b->exp);
        b = b->next;
        changed_b = 1;
    }

    // make tail point to head
    node *n = result;
    while (n->next)
        n = n->next;
    n->next = result->next;

    return result->next;
}
