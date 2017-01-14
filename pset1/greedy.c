#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
int main(void)
{

  
      float change;

    do {
     printf("Change:\n");
     change = GetFloat();
    }  while(change < 0);

    int coinCount = 0;
    int changeCount = (int) round(change * 100);

     
    while(changeCount >= 25) { // quarter
        coinCount = (coinCount + 1);
        changeCount = (changeCount -25);
    }

    while(changeCount >= 10) { //dime
        coinCount = (coinCount + 1);
        changeCount = (changeCount -10);
    }
    
    while(changeCount >= 5) { //nickel
        coinCount = (coinCount + 1);
        changeCount = (changeCount -5);
    }
    
    while(changeCount >= 1) { //pennies
        coinCount = (coinCount + 1);
        changeCount = (changeCount -1);
    }
    
     printf("%i\n" , coinCount);
     
/* COMMENT ZONE
4
4
1
5
*/
   
}