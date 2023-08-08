/*
    v1 creates array of roll numbers from the students array,
    sorts and then loops through the sorted rolls array,
    simultaneously looping through the students array,
    printing the record on roll match

    v2 sorts the students array after making a copy
    and simply prints the new sorted array as is
*/

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

void display_st(struct student st)
{
    printf("%d\t|\t", st.roll);
    printf("%s\t|\t", st.name);
    printf("%c\t|", st.grade);
    printf("\n");
}

void display_students(int count, struct student st_array[])
{
    printf("Roll\t|\tName\t|\tGrade\t|\n");
    for (int i = 0; i < count; i++)
        display_st(st_array[i]);
    printf("\n");
}

void copy_struct_array(int count, struct student st_array[], struct student st_array_new[])
{
    for (int i = 0; i < count; i++)
        st_array_new[i] = st_array[i];
}

void sort_struct_array(int count, struct student st_array[])
{
    // insertion sort
    struct student key;
    int j;
    for (int i = 1; i < count; i++)
    {
        key = st_array[i];
        for (j = i; st_array[j - 1].roll > key.roll && j >= 1; j--)
            st_array[j] = st_array[j - 1];
        st_array[j] = key;
    }
}

int main()
{
    // printf("\nEnter sub string to delete: ");
    // gets(sub);

    int NUM_STUDENTS = 3;
    struct student students[NUM_STUDENTS];

    // sample records
    struct student s1 = {100, "Shaun", 'A'};
    struct student s2 = {2, "Rohan", 'C'};
    struct student s3 = {30, "Karan", 'D'};
    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    // read_students(NUM_STUDENTS, students);

    printf("# Printing student details:\n");
    display_students(NUM_STUDENTS, students);

    struct student students_sorted[NUM_STUDENTS];
    copy_struct_array(NUM_STUDENTS, students, students_sorted);
    sort_struct_array(NUM_STUDENTS, students_sorted);

    printf("# Printing student details sorted by roll number:\n");
    display_students(NUM_STUDENTS, students_sorted);
}
