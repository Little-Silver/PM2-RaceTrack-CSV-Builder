#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define local macros

#define MAX_LENGTH_FILE 10000
#define MAX_LENGTH_FILENAME 100
// reset control attributes + new line
#define NEWLINE "\n"


char *readFile(char *fileName)
{
    FILE *filePointer;
    char ch;


    char code[MAX_LENGTH_FILE];
    char * fileContent = code;

    //2
    filePointer = fopen(fileName, "r");

    //3
    if (filePointer == NULL)
    {
        printf("File is <%s> not available \n", fileName);
    }
    else
    {
        int i = 0;
        //4
        while ((ch = fgetc(filePointer)) != EOF)
        {
            fileContent[i] = ch;
            i++;
        }
        printf("File <%s> was successfully read \n", fileName);
    }
    return fileContent;
}

int writeFile(char * fileName, char * content)
{
    FILE *fileAddress;
   fileAddress = fopen(fileName, "w");
   
   int i;
   int len = strlen(content);

   if (fileAddress != NULL) {
	for (i = 0; i < len; i++) {
	   // Let us use our fputc
	   fputc (content[i], fileAddress);
	}
	printf("File was <%s> successfully written!\n", fileName);
	fclose(fileAddress);		
   }
   else {
  	  printf("Unable to write file <%s>!", fileName);
   }
   return 0;
}

int writeFileWithDelimiter(char * fileName, char * content, char delimiter, int addAxis)
{

    FILE *fileAddress;
   fileAddress = fopen(fileName, "w");
   
   int i;
   int len = strlen(content);
   if (fileAddress != NULL && content != NULL && len > 0) {

        if(addAxis != 0){
            fputc(' ', fileAddress);
            fputc(delimiter, fileAddress);
            for (i = 0; i < len && content[i] != '\n'; i++)
            {
                if(content[i] == '\n'){
                    break;
                }
                fputc(i + '0', fileAddress);
                fputc(delimiter, fileAddress);
            }
            fputc('\n', fileAddress);
        }

        int is_newline = 1;
        int lineCounter = 0;
        for (i = 0; i < len; i++) {
            if(is_newline == 1 && addAxis != 0){
                fputc(lineCounter + '0', fileAddress);
                fputc(delimiter, fileAddress);
                is_newline = 0;
            }

            fputc (content[i], fileAddress);
            if(content[i] != '\n'){
                fputc (delimiter, fileAddress);
                
            }
            else{
                is_newline = 1;
                lineCounter++;
            }
        }
        printf("File was <%s> successfully written!\n", fileName);
        fclose(fileAddress);		
   }
   else {
  	  printf("Unable to write file <%s>!\n", fileName);
   }
   return 0;
}



/**
 * @brief   main function
 * @param   argc [in] number of entries in argv
 * @param   argv [in] program name plus command line arguments
 * @returns returns success if valid date is given, failure otherwise
 */
int main(int argc, const char *argv[])
{

    char iFile[MAX_LENGTH_FILENAME];
    char * inputFileName = iFile;


    if(argc == 1){
        printf("Enter your Input-File: ");
        scanf("%s", inputFileName);
    }
    else{
        sscanf(argv[1], "%s", inputFileName);
    }

    char* code = readFile(inputFileName);

    char oFile[MAX_LENGTH_FILENAME];
    char * outputFileName = oFile;

    if(argc <= 2){
        printf("Enter your Output-File: ");
        scanf("%s", outputFileName);
    }
    else{
        sscanf(argv[2], "%s", outputFileName);
    }

    int addAxis = 1;

    char axisP[5];
    char * axisParam = axisP;

    if(argc >= 3){

        if(axisParam == "-a")
        {
            printf("Added X and Y-Axis: ");
            addAxis = 1;
        }
    } 
    
    writeFileWithDelimiter(outputFileName, code, ';', addAxis);
}

