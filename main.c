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

int showList(){
    FILE *fptr;
    fptr = fopen("list.txt", "r");
    char line[100];

    if(fptr == NULL){
        printf("File list.txt not found. Exiting...\n");
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
    fptr = fopen("list.txt", "a");

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
    fptr = fopen("list.txt", "r");
    if (fptr == NULL){
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    tempFile = fopen(temp, "w"); // open the temporary file in write mode 
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
        remove("list.txt");  		// remove the original file 
        rename(temp, "list.txt"); 	// rename the temporary file to original name
    return 1;
}

int deleteLineString(){
    return 0;
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
            result = deleteLineString();
        }
    }else if(strcmp(argv[1],"show") == 0){
        result = showList();
    }else{
        printf("Wrong operator. Available operators: new / delete / show");
        return 0;
    }



    return result;
}