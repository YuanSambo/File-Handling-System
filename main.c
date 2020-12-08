#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_SIZE 15
#define NUMBER_OF_LINES 20

void Create(char fileName[MAX_STRING_SIZE]){

    char fName[50];
    FILE *fp;


    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"w");

    printf("File succesfully created \n");
    fclose(fp);

}

void Display(char fileName[MAX_STRING_SIZE]){

    FILE *fp;
    char fName[50];
    char text[NUMBER_OF_LINES];
    int wordCount = 1,index=0;

    sprintf(fName,"%s.txt",fileName);

    fp = fopen(fName,"r");

    // Guard Clause
    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }

    printf(" --------------- CONTENTS --------------- \n");
    printf("      Name              Age           \n");

    // Reading of file
    while (fscanf(fp, "%s", text) != EOF)
    {

        // If the pointer is at the Name
        if(wordCount % 2 != 0){
            printf(" %d.  %s",index+1,text);
        }

        // If the pointer is at the Age
        else{
            index++;
            printf("\t\t\t\t%s",text);
            printf("\n");
        }

        wordCount++;
    }
    printf("   _____________________________________\n");

    fclose(fp);

}

void Add(char fileName[MAX_STRING_SIZE]){
    FILE *fp;
    char fName[50];
    char Names[NUMBER_OF_LINES][MAX_STRING_SIZE];
    char name [MAX_STRING_SIZE];
    char text[NUMBER_OF_LINES];
    int age = 0;
    int index=0,wordCount=1;



    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"r");

    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d",&age);


    //Reading of files
    while (fscanf(fp, "%s", text) != EOF)
    {
        // If the pointer is at the Name
        if(wordCount % 2 != 0){
            strcpy(Names[index], text);
        }

        // If the pointer is at the Age
        else{
            index++;

        }
        wordCount++;
    }
    fclose(fp);

    int i;

    // Checking of record if already exist.
    for(i=0;i<index;i++){

        if(!strcmp(Names[i],name)){
            printf("RECORD ALREADY EXIST\n");
            return;
        }
    }

        // Adding of record.
        fp = fopen(fName,"a");
        fprintf(fp,"%s %d\n",name,age);
        printf("Added successfully\n");
        fclose(fp);

        Display(fileName);


}

void AgeAverageCalculation(char fileName[MAX_STRING_SIZE]){
    FILE *fp;
    char fName[MAX_STRING_SIZE];
    char text[NUMBER_OF_LINES];
    int index=0,wordCount = 1,sum=0;

    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"r");

    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }
    //Reading all of the age in the file.
    while (fscanf(fp, "%s", text) != EOF)
    {
        // If the pointer is at the Age
        if(wordCount % 2 == 0){
            sum+= atoi(text);
            printf("\n");
            index++;
        }
        wordCount++;
    }
    printf("Average Age: %d \n", sum/index);
}

void SortFileContents(char fileName[MAX_STRING_SIZE]){
    FILE *fp;
    char fName[50];
    char Names[NUMBER_OF_LINES][MAX_STRING_SIZE];
    int  Age[NUMBER_OF_LINES];
    char text[NUMBER_OF_LINES];
    int index=0,wordCount = 1;

    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"r");

    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }


    // Reading all the text
    while (fscanf(fp, "%s", text) != EOF)
    {
        // If the pointer is at the Name
        if(wordCount % 2 != 0){
            strcpy(Names[index], text);
        }

        // If the pointer is at the Age
        else{
            Age[index] = atoi(text);
            index++;
        }
        wordCount++;
    }


    int temp, i, j, k,choice;
    int count = index;
    char temp2[MAX_STRING_SIZE];
    printf("Enter 1 for Ascending order\n");
    printf("Enter 2 for Descending order\n");
    scanf("%d",&choice);

    for (j = 0; j < count; ++j)
    {
        for (k = j + 1; k < count; ++k)
        {
            // Ascending Order
            if(choice  == 1){
                if (Age[j] > Age[k])
                {
                    temp = Age[j];
                    strcpy(temp2,Names[j]);

                    Age[j] = Age[k];
                    strcpy(Names[j],Names[k]);

                    Age[k] = temp;
                    strcpy(Names[k],temp2);
                }
            }

            // Descending Order
            else if (choice == 2){
                if (Age[j] < Age[k])
                {
                    temp = Age[j];
                    strcpy(temp2,Names[j]);

                    Age[j] = Age[k];
                    strcpy(Names[j],Names[k]);

                    Age[k] = temp;
                    strcpy(Names[k],temp2);
                }
            }
            else{
                printf("Invalid input");
            }

        }
    }
    fclose(fp);

    // Writing of the order in the file.
    fp = fopen(fName,"w");
    for(i=0;i<count;i++){
        fprintf(fp,"%s %d\n",Names[i],Age[i]);
    }
    fclose(fp);

    Display(fileName);

}

void RemovePerson(char fileName[MAX_STRING_SIZE]){
    FILE *fp;
    char fName[50];
    char Names[NUMBER_OF_LINES][MAX_STRING_SIZE];
    int  Age[NUMBER_OF_LINES];
    char text[NUMBER_OF_LINES];
    int index=0,wordCount=1,indexToBeRemoved;


    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"r");

    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }

    Display(fileName);
    printf("Enter the index you want to remove: ");
    scanf("%d", &indexToBeRemoved);


    //Reading of files
    while (fscanf(fp, "%s", text) != EOF)
    {
        // If the pointer is at the Name
        if(wordCount % 2 != 0){
            strcpy(Names[index], text);
        }
        // If the pointer is at the Age
        else{
            Age[index] = atoi(text);
            index++;

        }
        wordCount++;
    }
    fclose(fp);



    // Remove item from the array
    int i,size=index;

    if(indexToBeRemoved < 0 || indexToBeRemoved > size)
    {
        printf("Invalid index! Please enter position between 1 to %d \n", size);
        return;
    }

    /* Copy next element value to current element */
    for(i=indexToBeRemoved-1; i<size-1; i++)
    {
        strcpy(Names[i],Names[i+1]);
        Age[i] = Age[i + 1];
    }

    /* Decrement array size by 1 */
    size--;

    // Writing of the order in the file.
    fp = fopen(fName,"w");
    for(i=0;i<size;i++){
        fprintf(fp,"%s %d\n",Names[i],Age[i]);
    }
    printf("Removed successfully\n");
    fclose(fp);

    Display(fileName);

}

void EditName(char fileName[MAX_STRING_SIZE]){
    FILE *fp;
    char fName[50];
    char Names[NUMBER_OF_LINES][MAX_STRING_SIZE];
    char text[NUMBER_OF_LINES];
    char newName[MAX_STRING_SIZE];
    int Age[MAX_STRING_SIZE];
    int index=0,wordCount=1,indexToBeChanged;


    sprintf(fName,"%s.txt",fileName);
    fp = fopen(fName,"r");

    if(!fp){
        printf("CREATE A FILE FIRST \n");
        return;
    }

    Display(fileName);

    //Reading of files
    while (fscanf(fp, "%s", text) != EOF)
    {
        // If the pointer is at the Name
        if(wordCount % 2 != 0){
            strcpy(Names[index], text);
        }

        // If the pointer is at the Age
        else{
            Age[index] = atoi(text);
            index++;
        }
        wordCount++;
    }
    fclose(fp);





    int i,size=index;

    printf("Enter the index of the name you want to change: ");
    scanf("%d", &indexToBeChanged);


    if(indexToBeChanged < 0 || indexToBeChanged > size)
    {
        printf("Invalid index! Please enter position between 1 to %d \n", size);
        return;
    }

    printf("Enter the new name: ");
    scanf("%s",newName);

    strcpy(Names[indexToBeChanged-1],newName);


    // Writing of the order in the file.
    fp = fopen(fName,"w");
    for(i=0;i<size;i++){
        fprintf(fp,"%s %d\n",Names[i],Age[i]);
    }
    fclose(fp);

    Display(fileName);

}

int main() {

    char openedFile[MAX_STRING_SIZE];
    int choice=0;


    while( choice!=8 ) {

        printf(" --------------- MAIN MENU --------------- \n");
        printf("| 1 - File creation                       |\n");
        printf("| 2 - Display the contents of the file    |\n");
        printf("| 3 - Add information to the file         |\n");
        printf("| 4 - Age average calculation             |\n");
        printf("| 5 - Sort file contents                  |\n");
        printf("| 6 - Person Removal                      |\n");
        printf("| 7 - Correctness information analysis    |\n");
        printf("| 8 - End Program                         |\n");
        printf(" __________________________________________\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);



        // WHAT YOU CREATE WHAT YOU OPEN
        switch(choice)
        {
            case 1:
                printf("Enter the name of the file: ");
                scanf("%s",openedFile);
                Create(openedFile);
                break;
            case 2:
                Display(openedFile);
                break;
            case 3:
                Add(openedFile);
                break;
            case 4:
               AgeAverageCalculation(openedFile);
                break;
            case 5:
                SortFileContents(openedFile);
                break;
            case 6:
                RemovePerson(openedFile);
                break;
            case 7: ;
                EditName(openedFile);
                break;
            default:printf("Please input valid choice\n ");
        }
    }


    return 0;
}
