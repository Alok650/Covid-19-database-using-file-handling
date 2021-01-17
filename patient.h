#include <stdio.h>

struct date {
    int day;
    int month;
    int year;
};

struct patients {
    char patientCode[10];
    char firstName[20];
    char lastName[20];
    int age;
    int gender;
    struct date discharge;
    struct date admission;
    int area;
};