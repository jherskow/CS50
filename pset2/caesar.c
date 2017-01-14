#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{

    if (argc != 2)     //(check for legal command like agument)
    {
    printf("DAMMIT USER YOU HAD ONE JOB!!!!!\n");
    return 1;
    }

int k = atoi(argv[1]);          // convert argument to int k
char* text = NULL;              //declare string

    do {
        //printf("Your text:\n");
        text = GetString();
    }while (text == NULL);

for (int i = 0, n = strlen(text); i < n; i++)
{
    if (isalpha(text[i])&&isupper(text[i]))     //math for upper letters
    {
    text[i] = ((((text[i]-'A') + k) % 26)+'A');
    }
    else if (isalpha(text[i])&&islower(text[i]))     //math for lower letters
    {
    text[i] = ((((text[i]-'a') + k) % 26)+'a');
    }
}

printf("%s\n" , text); //print text
return 0;
    
    
   /*  implemetation: 
    
   count chars in string
   for is alpha = convert each car
   if not alpha do not
   wrap around z-a
         
         
    */
    
}