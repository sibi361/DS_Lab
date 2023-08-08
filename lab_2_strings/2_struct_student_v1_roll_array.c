#include <stdio.h>

struct student
{
    int roll;
    char name[1000];
    char grade;
};

void read_students(int count, struct student st_array[])
{
    printf("\n# Reading student details from user\n");
    printf("Enter <roll number> <name> <grade>\n");
    for (int i = 0; i < count; i++)
    {
        printf("Student %d: ", i + 1);
        scanf("%d %s %c", &st_array[i].roll, st_array[i].name, &st_array[i].grade);
        printf("\n");
    }
}

void display_student(struct student st)
{
    printf("%d\t|\t", st.roll);
    printf("%s\t|\t", st.name);
    printf("%c", st.grade);
    printf("\n");
}

void display_students(int count, struct student st_array[])
{
    printf("# Printing student details:\n");
    printf("Roll\t|\tName\t|\tGrade\n");
    for (int i = 0; i < count; i++)
        display_student(st_array[i]);
    printf("\n");
}

void insertion_sort(int len, int *array)
{
    int key, j;
    for (int i = 1; i < len; i++)
    {
        key = array[i];
        for (j = i; array[j - 1] > key && j >= 1; j--)
            array[j] = array[j - 1];
        array[j] = key;
    }
}

void display_students_sorted_by_roll(int count, struct student st_array[])
{
    // adding all rolls to array
    int rolls[count];
    for (int i = 0; i < count; i++)
        rolls[i] = st_array[i].roll;

    // sorting rolls
    insertion_sort(count, rolls);

    printf("# Printing student details sorted by roll number:\n");
    printf("Roll\t|\tName\t|\tGrade\n");
    int key;
    for (int i = 0; i < count; i++)
    {
        key = rolls[i];
        for (int j = 0; j < count; j++)
            if (st_array[j].roll == key)
                display_student(st_array[j++]);
    }
}

int main()
{
    // printf("\nEnter sub string to delete: ");
    // gets(sub);

    int NUM_STUDENTS = 3;
    struct student students[NUM_STUDENTS];

    // sample details
    struct student s1 = {100, "Shaun", 'A'};
    struct student s2 = {2, "Rohan", 'C'};
    struct student s3 = {30, "Karan", 'D'};
    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    // read_students(NUM_STUDENTS, students);

    display_students(NUM_STUDENTS, students);

    display_students_sorted_by_roll(NUM_STUDENTS, students);
}
