/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h> 


int main(void)
{

    unsigned char buffer[512];
    char fileName[8];
    int i = 0;
  
      // open input file 
    FILE* inptr = fopen("card.raw", "r"); 

    
    while (fread(&buffer, 512, 1,inptr) == 1)   //some way to get number of images, or alternatively a counter of the # of blocks
    {

         
        //if header is JPG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] <= 0xef && buffer[3] >= 0xe0) )  //whole file must fit here
        {
            
            //create filename
            if (i == 0)
                sprintf(fileName,"000.jpg");
            else if (i < 10)
                sprintf(fileName,"00%d.jpg",i);
            else if (i < 100)
                sprintf(fileName,"0%d.jpg",i);
            else
                sprintf(fileName,"%d.jpg",i);
            
            FILE* outptr = fopen(fileName, "w" ); //open file with name
            
            i++; //log new file found
            
            fwrite(&buffer, 512, 1,outptr);


            while (fread(&buffer, 512, 1,inptr) == 1)
            {
                
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] <= 0xef && buffer[3] >= 0xe0) )
                {
                    fseek(inptr, -512, SEEK_CUR);
                    break;
                }
                else
                fwrite(&buffer, 512, 1,outptr);
                
            }
  
        fclose(outptr); 
        
        }
      
       
    }
     
    // close infile
    fclose(inptr);

    // that's all folks
    return 0;
}
