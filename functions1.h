#include <stdio.h>

int addFile()
{
    FILE* myFile;
    myFile = fopen("Record.txt", "a");
    if (myFile == NULL) {
        printf("file NOT found!\n");
        return 1;
    }
    else {
        struct patients p1;
        printf("\nEnter patient code: ");
        scanf("%s", p1.patientCode);
        printf("\nEnter first name: ");
        scanf("%s", p1.firstName);
        printf("\nEnter lastname: ");
        scanf("%s", p1.lastName);
        printf("\nEnter AGE: ");
        scanf("%d", &p1.age);
        printf("\n Enter admission date: ");
        scanf("%d %d %d ", &p1.admission.day, &p1.admission.month, &p1.admission.year);
        printf("\n Enter the discharge date: ");
        scanf(" %d %d %d ", &p1.discharge.day, &p1.discharge.month, &p1.discharge.year);
        printf("\n Enter gender (0 for transgender/1 for male / 2 for female): ");
        scanf(" %d ", p1.gender);
        printf("\nEnter pin-code: ");
        scanf("%d", p1.area);
        fwrite(&p1, sizeof(struct patients), 1, myFile);
        fclose(myFile);
        return 2;
    }
}

void delRec(char* p)
{
    struct patients p1;
    FILE *fptr, *fptr1, *fptr2, *fptr3;
    fptr = fopen("Record.txt", "r+");
    fptr1 = fopen("p.txt", "w");
    if (fptr == NULL || fptr1 == NULL) {
        printf("Error");
        return;
    }

    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        if (strcmp(p1.patientCode, p)) {
            fwrite(&p1, sizeof(struct patients), 1, fptr1);
        }
    }
    fclose(fptr);
    fclose(fptr1);
    remove("Record.txt");
    rename("p.txt", "Record.txt");
}

void update(char* a)
{
    struct patients p1;
    FILE *fptr, *fptr1;
    fptr = fopen("Record.txt", "r+");
    fptr1 = fopen("ascend.txt", "w");
    if (fptr == NULL || fptr1 == NULL) {
        printf("\nError !!!");
        return;
    }
    while (fread(&p1, sizeof(struct patients), 1, fptr)) {
        int x = strcmp(p1.patientCode, a);
        if (x == 0) {
            printf("\n Enter patient code: ");
            scanf("%s", p1.patientCode);
            printf("\nEnter the First name of patient: ");
            scanf("%s", p1.firstName);
            printf("\nEnter the last name of patient: ");
            scanf("%s", p1.lastName);
            printf("\nEnter age of patient: ");
            scanf("%d", &p1.age);
            printf("\nEnter the admission date of patient: ");
            scanf("%d %d %d ", &p1.admission.day, &p1.admission.month, &p1.admission.year);

            printf("\n Enter date of discharge: ");
            scanf("%d %d %d ", &p1.discharge.day, &p1.discharge.month, &p1.discharge.year);

            printf("\n Enter gender (0: Others, 1:Male, 2:Female) : ");

            scanf("%d", p1.gender);

            printf("\n Enter pin code: ");
            scanf("%d", &p1.area);
        }
        fwrite(&p1, sizeof(struct patients), 1, fptr1);
    }
    fclose(fptr);
    fclose(fptr1);
    remove("Record.txt");
    rename("abs.txt", "Record.txt");
}