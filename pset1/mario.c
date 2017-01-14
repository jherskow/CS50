#include <stdio.h>
#include <cs50.h>

int main(void)
{

  
      int height;

do {
    printf("Height:\n");
    height = GetInt();
}  while(height < 0 || height > 23);

    int row;
    int a;
    int b;
       
    for( row = 1; (row) <= height; row = row + 1 ){
       
    
             for( a = (height - row); a > 0 ; a = a - 1 ){ 
                printf(" ");
             }
          
            for( b = 1; b <= (row+1); b = b + 1 ){ 
                printf("#");
            }
            
     printf("\n");
   }
   
   /* we want to print in each line :
   height - (a+1) spaces and then (a+1 spaces
    so if height 3: row 2 we want 2-1 spaces
    (row minus 1 spaces) and 
    row plus one X's (x plus one x's)
    
    height is 4
    row 1 - 3 space
    row 2 - 2 space
    row 3 - 1 space
    row 4 - 0 space
    
    so for each row spaces are height - row

   XX
  XXX  
 XXXX
XXXXX


*/
   
}