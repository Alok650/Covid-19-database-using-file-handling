#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "patient.h"
#include "functions1.h"
#define MAX 256


//functions 4-7
void Ascending(int s);
void descending(int h);
void gender();
void sortFemale();
void sort_1();
void sort_2();
void sort_3();
void sort_4();
void sort_5();
void sort_6();
void sort_7();
void catergory_rep(int l);
void func_A();
void func_B(int f);
void func_C(int d);
void count_Rec();

//Display functions
int menu();
void readFile(char* file);

int main()
{
    char file_name[20] = "Record.txt";
    char file_name1[20] = "record_1.txt";
    char file_name2[20] = "record_2.txt";
    char file_name3[20] = "record_3.txt";
    readFile(file_name);
    while (1) {
        int t = menu();
        switch (t) {
        case 1: {
            int a = addFile();
            if (a == 2) {
                printf("\n\t\t\t Record added!!\n");
            }
            else {
                printf("\n\t\t\t Error! Please repeat");
            }
            readFile(file_name);
            break;
        }
        case 2: {
            char p[10];
            printf("\nEnter patient ID to be del. : ");
            scanf("%s", p);
            delRec(p);
            readFile(file_name);
            break;
        }

        case 3: {
            char p[10];
            printf("\nEnter patient ID to be updated : ");
            scanf("%s", p);
            update(p);
            readFile(file_name);
            break;
        }

        case 4: {
            count_Rec();
            break;
        }

        case 5: {

            int l;

            printf("enter your choice :");

            scanf("%d", &l);

            Ascending(l);

            readFile(file_name);

            break;
        }

        case 6: {

            int l;

            printf("enter your choice :");

            scanf("%d", &l);

            descending(l);

            readFile(file_name);

            break;
        }

        case 7: {

            int l;

            printf("enter your choice :");

            scanf("%d", &l);

            catergory_rep(l);

            readFile(file_name);

            break;
        }

        case 8: {

            gender();

            readFile(file_name1);

            printf("\n");

            readFile(file_name2);

            printf("\n");

            readFile(file_name3);

            printf("\n");

            break;
        }

        case 9: {

            return 0;

            break;
        }

        default:
            printf("\t\t\tPLEASE SELECT PROPER CHOICE!!!");
        }
    }

    return 0;
}

void readFile(char* file)
{

    char g[20];

    struct patients p1;

    FILE* fptr;

    fptr = fopen(file, "r+");

    printf("\n");

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        short int x = p1.gender;
        if (x == 0) {
            strcpy(g, "transgender");
        }

        else if (x == 1) {

            strcpy(g, "male");
        }

        else if (x == 2) {

            strcpy(g, "female");
        }

        else {

            strcpy(g, "--------");
        }

        printf("|\t%s\t|\t%s\t|\t%s\t|\t%d\t|\t%d %d %d\t|\t%d %d %d\t|\t%s\t|\t%d\t|\n", p1.patientCode, p1.firstName, p1.lastName, p1.age, p1.admission.day, p1.admission.month, p1.admission.year, p1.discharge.day, p1.discharge.month, p1.discharge.year, g, p1.area);
        printf("\n");
    }

    fclose(fptr);
}

int menu()
{

    int x;
    printf("\n\t\t\tMenu\n");
    printf("1.ADD A RECORD\n");
    printf("2.DELETE A RECORD\n");
    printf("3.MODIFY A RECORD\n");

    printf("\n4.Reports:\n\tA. DISPLAY COUNT OF PATIENTS \n\tB. DISPLAY COUNT OF PATIENTS BASED ON THE GENDER \n\tC. DISPLAY AGE WISE COUNT OF PATIENTS \n\tD. DIPSPLAY THE COUNT OF PATIENTS AREA WISE\n");

    printf("\n5.LIST ALL RECORDS IN AscendingING ORDER\n");

    printf("\n6.LIST ALL RECORDS IN DESCENDING ORDER\n");

    printf("7.LIST ALL RECORD OF FILE FOR SPECIFIC RANGE: \n\tA.Patient first name starts from your first name letter to next 10 letters \n\tB. Admission date(till next 10 days) \n\tC. Admission month from user given month to next 5 months \n");

    printf("8.Male and Female records.\n");
    printf("9.EXIT\n");

    printf("\nENTER YOUR CHOICE :");

    scanf("%d", &x);

    return x;
}

void count_Rec()
{
    int arr[MAX];
    struct patients p1;
    struct patients p2;
    char ch;
    int count = 0;
    int countGM = 0;
    int countGF = 0;
    int countGT = 0;
    int countA = 1;
    FILE* fptr;
    fptr = fopen("Record.txt", "r");
    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        if (p1.patientCode) {
            count++;
        }
    }
    rewind(fptr);
    printf("\nTotal number of patients are :%d \n", count);
    if (count > 0) {
        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (p1.gender == 0) {
                countGT++;
            }
            if (p1.gender == 1) {
                countGM++;
            }
            if (p1.gender == 2) {
                countGF++;
            }
        }
        rewind(fptr);
        printf("\n\tMALE : (%d)\n\tFEMALE : (%d)\n\tOTHERS :(%d)\n", countGM, countGF, countGT);
        int i = 0;
        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            arr[i] = p1.age;
            i++;
        }
        rewind(fptr);
        for (i = 0; i < count; i++) {
            if (arr[i]) {
                for (int j = i + 1; j < count; j++) {
                    if (arr[j]) {
                        if (arr[i] == arr[j]) {
                            countA++;
                            arr[j] = 0;
                        }
                    }
                }

                printf("\nNumber of patients of age :%d is :(%d)\n", arr[i], countA);

                countA = 1;
            }
        }

        rewind(fptr);

        i = 0;

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            arr[i] = p1.area;

            i++;
        }

        rewind(fptr);

        for (i = 0; i < count; i++) {

            if (arr[i]) {

                for (int j = i + 1; j < count; j++) {

                    if (arr[j]) {

                        if (arr[i] == arr[j]) {

                            countA++;

                            arr[j] = 0;
                        }
                    }
                }

                printf("\nNumber of patients of same area:%d is :(%d)\n", arr[i], countA);

                countA = 1;
            }
        }
    }
    else {

        printf("\nNo record found!!!!\n");
    }

    fclose(fptr);
}

void catergory_rep(int l)
{

    switch (l) {

    case 1: {

        func_A();

        break;
    }

    case 2: {

        int k;

        printf("Enter the date :");

        scanf("%d", &k);

        func_B(k);

        break;
    }

    case 3: {

        int k;

        printf("Enter the month :");

        scanf("%d", &k);

        func_C(k);

        break;
    }

    default:
        printf("Invalid selection\n");
    }
}

void Ascending(int s)
{

    switch (s) {

    case 1: {

        sortFemale();

        break;
    }

    case 2: {

        sort_1();

        break;
    }

    case 3: {

        sort_2();

        break;
    }

    case 4: {

        sort_3();

        break;
    }

    default:
        printf("\n Invalid selection\n");
    }
}

void descending(int h)
{

    switch (h) {

    case 1: {

        sort_4();

        break;
    }

    case 2: {

        sort_5();

        break;
    }

    case 3: {

        sort_6();

        break;
    }

    case 4: {

        sort_7();

        break;
    }

    default:
        printf("ENTER PROPER CHOICE!!!!!\n");
    }
}

/* Ascendinging start */

void sortFemale()
{

    struct patients p1;

    char fname[MAX][20];

    char fname1[20];

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        strcpy(fname[i], p1.firstName);

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (strcmp(fname[i], fname[j]) > 0) {

                strcpy(fname1, fname[j]);

                strcpy(fname[j], fname[i]);

                strcpy(fname[i], fname1);
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (strcmp(fname[i], p1.firstName) == 0) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_1()
{

    struct patients p1;

    char fname[MAX][20];

    char fname1[20];

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        strcpy(fname[i], p1.lastName);

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (strcmp(fname[i], fname[j]) > 0) {

                strcpy(fname1, fname[j]);

                strcpy(fname[j], fname[i]);

                strcpy(fname[i], fname1);
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (strcmp(fname[i], p1.lastName) == 0) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_2()
{

    struct patients p1;

    int fage[20];

    int fage1;

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        fage[i] = p1.age;

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (fage[i] > fage[j]) {

                fage1 = fage[j];

                fage[j] = fage[i];

                fage[i] = fage1;
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (p1.age == fage[i]) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_3()
{

    struct patients p1;

    int fday[MAX], temp;

    int fmonth[MAX];

    int fyear[MAX];

    int fsum[MAX];

    int i = 0;

    int count = 0;

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        fday[i] = p1.admission.day;
        fmonth[i] = p1.admission.month;
        fyear[i] = p1.admission.year;

        fsum[i] = fyear[i] * 10000 + fmonth[i] * 100 + fday[i];
        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (fsum[i] > fsum[j]) {

                temp = fsum[i];

                fsum[i] = fsum[j];

                fsum[j] = temp;
            }
        }
    }

    for (i = 0; i < count; i++) {

        fyear[i] = fsum[i] / 10000;
    }

    for (i = 0; i < count; i++) {

        fmonth[i] = (fsum[i] - fyear[i] * 10000) / 100;
    }

    for (i = 0; i < count; i++) {

        fday[i] = fsum[i] - fyear[i] * 10000 - fmonth[i] * 100;
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (p1.admission.year == fyear[i] && p1.admission.month == fmonth[i]

                && p1.admission.day == fday[i]) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

/* Ascendinging ends*/

/* descending start*/

void sort_4()
{

    struct patients p1;

    char fname[MAX][20];

    char fname1[20];

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        strcpy(fname[i], p1.firstName);

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (strcmp(fname[i], fname[j]) < 0) {

                strcpy(fname1, fname[j]);

                strcpy(fname[j], fname[i]);

                strcpy(fname[i], fname1);
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (strcmp(fname[i], p1.firstName) == 0) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_5()
{

    struct patients p1;

    char fname[MAX][20];

    char fname1[20];

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        strcpy(fname[i], p1.lastName);

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (strcmp(fname[i], fname[j]) < 0) {

                strcpy(fname1, fname[j]);

                strcpy(fname[j], fname[i]);

                strcpy(fname[i], fname1);
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (strcmp(fname[i], p1.lastName) == 0) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_6()
{

    struct patients p1;

    int fage[20];

    int fage1;

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    int i = 0;

    int count = 0;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        fage[i] = p1.age;

        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (fage[i] < fage[j]) {

                fage1 = fage[j];

                fage[j] = fage[i];

                fage[i] = fage1;
            }
        }
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (p1.age == fage[i]) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

void sort_7()
{

    struct patients p1;

    int fday[MAX], temp;

    int fmonth[MAX];

    int fyear[MAX];

    int fsum[MAX];

    int i = 0;

    int count = 0;

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    FILE* fptr1;

    fptr1 = fopen("re.txt", "w");

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        fday[i] = p1.discharge.day;
        fmonth[i] = p1.discharge.month;
        fyear[i] = p1.discharge.year;

        fsum[i] = fyear[i] * 10000 + fmonth[i] * 100 + fday[i];
        i++;

        count++;
    }

    rewind(fptr);

    for (i = 0; i < count; i++) {

        for (int j = i + 1; j < count; j++) {

            if (fsum[i] < fsum[j]) {

                temp = fsum[i];

                fsum[i] = fsum[j];

                fsum[j] = temp;
            }
        }
    }

    for (i = 0; i < count; i++) {

        fyear[i] = fsum[i] / 10000;
    }

    for (i = 0; i < count; i++) {

        fmonth[i] = (fsum[i] - fyear[i] * 10000) / 100;
    }

    for (i = 0; i < count; i++) {

        fday[i] = fsum[i] - fyear[i] * 10000 - fmonth[i] * 100;
    }

    i = 0;

    while (count--) {

        while (fread(&p1, sizeof(struct patients), 1, fptr)) {
            if (p1.discharge.year == fyear[i] && p1.discharge.month == fmonth[i]

                && p1.discharge.day == fday[i]) {

                fwrite(&p1, sizeof(struct patients), 1, fptr1);

                i++;
            }
        }

        rewind(fptr);
    }

    fclose(fptr);

    fclose(fptr1);

    remove("Record.txt");

    rename("re.txt", "Record.txt");
}

/* descending end*/

void func_A()
{

    struct patients p1;

    char g[20];

    FILE* fptr;

    fptr = fopen("Record.txt", "r");

    char* j;

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        j = p1.firstName;

        if ((*j >= 109 && *j <= 118) || (*j >= 77 && *j <= 86)) {

            short int x = p1.gender;

            if (x == 0) {

                strcpy(g, "transgender");
            }
            else if (x == 1) {

                strcpy(g, "male");
            }
            else if (x == 2) {

                strcpy(g, "female");
            }
            else {

                strcpy(g, "--------");
            }

            printf("\t%s\t|\t%s\t|\t%s\t|\t%d\t|\t%d %d %d\t|\t%d %d %d\t|\t%s\t|\t%d\t|\n", p1.patientCode, p1.firstName, p1.lastName, p1.age, p1.admission.day, p1.admission.month, p1.admission.year, p1.discharge.day, p1.discharge.month, p1.discharge.year, g, p1.area);

            printf("\n");
        }
    }

    fclose(fptr);
}

void func_B(int f)
{

    struct patients p1;

    FILE* fptr;

    char g[20];

    fptr = fopen("Record.txt", "r");
    while (fread(&p1, sizeof(struct patients), 1, fptr)) {

        if (p1.admission.day >= f || p1.admission.day < (f + 10) % 32) {
            short int x = p1.gender;

            if (x == 0) {

                strcpy(g, "transgender");
            }
            else if (x == 1) {

                strcpy(g, "male");
            }
            else if (x == 2) {

                strcpy(g, "female");
            }
            else {

                strcpy(g, "--------");
            }

            printf("\t%s\t|\t%s\t|\t%s\t|\t%d\t|\t%d %d %d\t|\t%d %d %d\t|\t%s\t|\t%d\t|\n", p1.patientCode, p1.firstName, p1.lastName, p1.age, p1.admission.day, p1.admission.month, p1.admission.year, p1.discharge.day, p1.discharge.month, p1.discharge.year, g, p1.area);

            printf("\n");
        }
    }

    fclose(fptr);
}

void func_C(int d)
{

    struct patients p1;

    FILE* fptr;

    char g[20];

    fptr = fopen("Record.txt", "r");
    while (fread(&p1, sizeof(struct patients), 1, fptr)) {

        if (p1.admission.month >= d || p1.admission.month < (d + 5) % 13) {
            short int x = p1.gender;

            if (x == 0) {

                strcpy(g, "transgender");
            }
            else if (x == 1) {

                strcpy(g, "male");
            }
            else if (x == 2) {

                strcpy(g, "female");
            }
            else {

                strcpy(g, "--------");
            }

            printf("\n\t%s\t|\t%s\t|\t%s\t|\t%d\t|\t%d %d %d\t|\t%d %d %d\t|\t%s\t|\t%d\t|\n", p1.patientCode, p1.firstName, p1.lastName, p1.age, p1.admission.day, p1.admission.month, p1.admission.year, p1.discharge.day, p1.discharge.month, p1.discharge.year, g, p1.area);

            printf("\n");
        }
    }

    fclose(fptr);
}

void gender()
{

    struct patients p1;

    FILE* fptr;

    FILE* fptr1;

    FILE* fptr2;

    FILE* fptr3;

    fptr = fopen("Record.txt", "r");
    fptr1 = fopen("record_1.txt", "w");
    fptr2 = fopen("record_2.txt", "w");
    fptr3 = fopen("record_3.txt", "w");
    while (fread(&p1, sizeof(struct patients), 1, fptr)) {

        if (p1.gender == 1) {

            fwrite(&p1, sizeof(struct patients), 1, fptr1);
        }
    }
}