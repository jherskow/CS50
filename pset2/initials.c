#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

char* name; //stores name
bool flag = true; //indicates next char is initial
int i; // loop counter
int n; // loop counter


    do {
        //printf("Your name:\n");
        name = GetString();
    }while (name == NULL);

     for( i = 0, n = (strlen(name)); i < n; i++)
        {
        
            if (flag == true)
            {   
                printf("%c" , toupper(name[i]));
                flag = false;
            }
            
            else if (name[i] == ' ')     //checks if character is a space, and flags it as an initial.
            flag = true;
        }
    
    printf("\n");
   
   
    /*
    
    implemetation: 
    
    while (count string length ++), initialise x as true
        while x true  , 
             do (print current letter capitalised (note :may already be cap!)
             turn X to untrue
         if current char is space - X = true
    
    
    */
    
}