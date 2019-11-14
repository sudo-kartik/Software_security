# Gaining access to restricted file

In this we have a C program in which we can access files which are available there, but we are not allowed to access the secret_file.txt or its link.

### Source Code -
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
char *secret_file = "secret_file.txt";
 
int linksToSecret(char *fn) {
 
    char buf[512];
 
    int count = readlink(fn, buf, sizeof(buf));
    if (count > 0) {
        buf[count] = '\0';
        if (strncmp(buf, secret_file, strlen(secret_file) - 1) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
 
}
 
int main() {
 
    char input[100];
    char fileName[100];
    printf("Enter the name of the file to read from\n");
    fgets(fileName, sizeof(fileName), stdin);
 
    fileName[strlen(fileName) - 1] = '\0';
 
    if (strncmp(fileName, secret_file, strlen(secret_file)) == 0 ||
            linksToSecret(fileName) == 1) {
        printf("You are not allowed to access %s or symbolic links to it!\n", secret_file);
    } else {
        printf("Waiting for user input...\n");
        fgets(input, sizeof(input), stdin);
 
        FILE *fp = fopen(fileName, "r");
        if (fp != NULL) {
            char ch;
            while ((ch = fgetc(fp)) != EOF)
                printf("%c", ch);
            fclose(fp);
        } else {
            printf("You must provide an existing file you may access!\n");
        }
    }
 
}

```

### So First we will run the command in the terminal, the command is provided in our exercise to run the above source code -

Command -

`echo 42 > secret_file.txt && gcc exercise3.c -w -o exercise3.o && ./exercise3.o`

Screenshot-   
![Screenshot](run_pro.png)

This will create the secret_file.txt in the location were we downloded our program file which is excersie3.c

Screenshot-   
![Screenshot](secretfilecreated.png)

### Now we will take the path of the secret_file.txt -

Screenshot-   
![Screenshot](filepath.png)

as you can see we get the path of the secret_file from its properties.

### Now we take this path and provide this as the input instead of the file name -

Screenshot-   
![Screenshot](secretfileaccess.png)

As you can see that we got the expected output from the above screenshot.


## The security Bypass -

As you can see we can get the file by putting the file path instead of file name or its link, so file path is the security bypass we are using.


