#include <stdio.h>
#include <stdlib.h>

struct Time
{
    int hour, min, sec;
};

struct Time read_time(int hour, int min, int sec)
{
    struct Time t;
    int valid = 0;

    if (hour < 0 || hour > 23)
        printf("Invalid hour\n");
    else if (min < 0 || min > 60)
        printf("Invalid minute\n");
    else if (sec < 0 || sec > 60)
        printf("Invalid second\n");
    else
        valid = 1;

    if (valid == 1)
    {
        t.hour = hour, t.min = min, t.sec = sec;
        return t;
    }
    else
        exit(0);
}

void print_time(struct Time t)
{
    printf("%d:%d:%d\n", t.hour, t.min, t.sec);
}

struct Time add_time(struct Time t1, struct Time t2)
{
    int sec_1, sec_2, sec_sum, h, m, s;

    sec_1 = t1.hour * 3600 + t1.min * 60 + t1.sec;
    sec_2 = t2.hour * 3600 + t2.min * 60 + t2.sec;

    sec_sum = sec_1 + sec_2;
    if (sec_sum > 86400)
        sec_sum %= 86400;

    h = sec_sum / 3600;
    m = sec_sum % 3600 / 60;
    s = sec_sum % 3600 - m * 60;

    struct Time t_new = {h, m, s};
    return t_new;
};

struct Time subtract_time(struct Time t1, struct Time t2)
{
    int sec_1, sec_2, sec_diff, h, m, s;

    sec_1 = t1.hour * 3600 + t1.min * 60 + t1.sec;
    sec_2 = t2.hour * 3600 + t2.min * 60 + t2.sec;

    sec_diff = sec_1 - sec_2;

    h = sec_diff / 3600;
    m = sec_diff % 3600 / 60;
    s = sec_diff % 3600 - m * 60;

    struct Time t_new = {h, m, s};
    return t_new;
};

void main()
{
    int hour, minute, second;

    printf("Enter time as <hour> <min> <second>:\n");
    // printf("Enter time 1: ");
    // scanf("%d %d %d", &hour, &minute, &second);
    // struct Time user_time_1 = read_time(hour, minute, second);
    // printf("Enter time 2: ");
    // scanf("%d %d %d", &hour, &minute, &second);
    // struct Time user_time_2 = read_time(hour, minute, second);

    struct Time user_time_1 = read_time(10, 30, 15);
    struct Time user_time_2 = read_time(2, 5, 10);

    printf("\nTime 1: ");
    print_time(user_time_1);
    printf("\nTime 2: ");
    print_time(user_time_2);

    struct Time added_time = add_time(user_time_1, user_time_2);
    printf("\nTime 1 + Time 2: ");
    print_time(added_time);

    struct Time sub_time = subtract_time(user_time_1, user_time_2);
    printf("\nTime 1 - Time 2: ");
    print_time(sub_time);

    printf("\n");
}
