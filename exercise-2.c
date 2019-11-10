#include <stdio.h>
#include <string.h>


int main() {
 
    char secret[100] = "exercise failed";
    char buf[16];
 
    printf("Enter your name:\n");
    gets(buf);
 
    printf(secret);
    printf("\n");
}

