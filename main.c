#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Command List:
        new String
        delete String
        delete -i Int
        show
*/

#define MAX 256 
#define FILE_RELATIVE_PATH "C:\\Users\\monni\\OneDrive\\Documenti\\GitHub\\ToDo-C\\"

int length(char *str);
int showList();
int newLine(char *text);
int deleteLineInt(int lnum);
int deleteLineString(char *delete);

int showList(){
    FILE *fptr;
    char filePath[MAX];
    snprintf(filePath, MAX, "%slist.txt", FILE_RELATIVE_PATH);
    fptr = fopen(filePath, "r");
    char line[100];

    if(fptr == NULL){
        printf("File list.txt not found. If it's the first time try adding a new element to the list with todo add \"item\" Exiting...\n");
        return 0;
    }

    int i = 1;
    while(fgets(line,100,fptr)){
        printf("[%d] - %s",i, line);
        i++;
    }

    fclose(fptr);

    return 1;
}

int newLine(char *text){
    FILE *fptr;
    char filePath[MAX];
    snprintf(filePath, MAX, "%slist.txt", FILE_RELATIVE_PATH);
    fptr = fopen(filePath, "a");

    fprintf(fptr,"%s\n",text);
    fclose(fptr);
    return 1;
}

int deleteLineInt(int lnum){
    if(lnum < 1)
        return 0;

    FILE *fptr, *tempFile;
    char str[MAX], temp[] = "temp.txt";
    int currentLine = 0;
    char filePath[MAX], tempFilePath[MAX];
    snprintf(filePath, MAX, "%slist.txt", FILE_RELATIVE_PATH);
    snprintf(tempFilePath, MAX, "%stemp.txt", FILE_RELATIVE_PATH);

    fptr = fopen(filePath, "r");
    if (fptr == NULL){
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    tempFile = fopen(tempFilePath, "w"); // open the temporary file in write mode 
    if (tempFile == NULL) 
    {
            printf("Unable to open a temporary file to write!!\n");
            fclose(fptr);
            return 0;
    }
    while (!feof(fptr)) 
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr);
            if (!feof(fptr)) 
            {
                currentLine++;
                if (currentLine != lnum) 
                {
                    fprintf(tempFile, "%s", str);
                }
            }
        }
        fclose(fptr);
        fclose(tempFile);
        remove(filePath);  		// remove the original file 
        rename(tempFilePath, filePath); 	// rename the temporary file to original name
    return 1;
}

int deleteLineString(char *delete){
    FILE *fptr, *tempFile;
    int found = 0;
    char str[MAX], temp[] = "temp.txt";
    char filePath[MAX], tempFilePath[MAX];
    snprintf(filePath, MAX, "%slist.txt", FILE_RELATIVE_PATH);
    snprintf(tempFilePath, MAX, "%stemp.txt", FILE_RELATIVE_PATH);
    fptr = fopen(filePath, "r");
    if (fptr == NULL){
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    tempFile = fopen(tempFilePath, "w"); // open the temporary file in write mode 
    if (tempFile == NULL) 
    {
            printf("Unable to open a temporary file to write!!\n");
            fclose(fptr);
            return 0;
    }
    while (fgets(str, MAX, fptr) != NULL) 
    {
        // Remove newline character from the line if present
        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, delete) == 0) 
        {
            found = 1; // Mark as found
        } 
        else 
        {
            fprintf(tempFile, "%s\n", str); // Write non-matching lines
        }
    }
    if (!found)
        printf("Element not found in the list\n");
        fclose(fptr);
        fclose(tempFile);
        remove(filePath);  		// remove the original file 
        rename(tempFilePath, filePath); 	// rename the temporary file to original name
    return 1;
}

int length(char *str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int main(int argc, char* argv[]){
    int result = 0;
    if(argv[1] == NULL){
        printf("You have to select the command. Available operators: new / delete / show");
        return 0;
    }

    if(argv[2] == NULL && strcmp(argv[1],"show") != 0){
        printf("Missing Arguments: Text or number needed");
        return 0;
    }

    if(strcmp(argv[1],"new") == 0){
        result = newLine(argv[2]);
    }else if(strcmp(argv[1],"delete") == 0){
        if(strcmp(argv[2],"-i") == 0 && argv[3] != NULL){
            result = deleteLineInt(atoi(argv[3]));
        } else {
            result = deleteLineString(argv[2]);
        }
    }else if(strcmp(argv[1],"show") == 0){
        result = showList();
    }else{
        printf("Wrong operator. Available operators: new / delete / show");
        return 0;
    }



    return result;
}