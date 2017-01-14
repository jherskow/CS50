#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{

    if (argc != 2)     //(check for legal command line agument 
        {
        printf("DAMMIT USER YOU HAD ONE JOB!!!!!\n");
        return 1;
        }

char* key = argv[1];          // key = argument 1
char* text = NULL;              //declare string
int keyLen = strlen(key);  // declared outside of loop bcz is used later!
    
    for (int i = 0; i < keyLen; i++) //convery key to  list of numbers
    {
        if (isalpha(key[i])&&isupper(key[i]))     //math for upper letters
            {
            key[i] = (key[i]-'A');
            }
        else if (isalpha(key[i])&&islower(key[i]))     //math for lower letters
            {
            key[i] = (key[i]-'a');
            }
        else // if non alphabetic chars in key
            {
                printf("DAMMIT USER YOU HAD ONE JOB!!!!!\n");
                return 1;
            }
    } 

    do {
        //printf("Your text:\n");
        text = GetString();
    }while (text == NULL);

for (int i = 0, j = 0, n = strlen(text) ; i < n; i++)
{
    if (isalpha(text[i])&&isupper(text[i]))     //math for upper letters
    {
    text[i] = ((((text[i]-'A') + key[j]) % 26)+'A');
    j++;
    }
    else if (isalpha(text[i])&&islower(text[i]))     //math for lower letters
    {
    text[i] = ((((text[i]-'a') + key[j]) % 26)+'a');
    j++;
    }
    if (j == keyLen)
    {
        j = 0;
    }
}
    


printf("%s\n" , text); //print text
return 0;
    
    
   /*  implemetation: 
    
   convert key to 1-indexed numbers (or equivalent chars)
    check for non alpabet chars
    encode text as in casar, making sure to add key[] instead of k
    (make sure to loop keytext when ncesarry)
    */
    
}