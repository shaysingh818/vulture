#include <stdio.h>
#define MAX_LEN 128

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];

    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

int main(void)
{
    char *filename = "image.txt";
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }

    print_image(fptr);

    fclose(fptr);

    printf("\n \n"); 

    int logOption; 

    while(true){

        printf("Array based logging y/n? "); 
        scanf("%d", &logOption);  

        
        
    }

    return 0;
}
