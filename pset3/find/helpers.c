/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <math.h>


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n < 0)  // if negative number
    {
        return false;   
    }                
    
          //BINARY SEARCH
    for(int i = n/2, x = n/2, j=0; j <= n; j++) //BINARY SEARCH - the problem is the halving and the rounding.
    {
        if(values[i] == value) // if we found it
            return true;   
        
       
        else if(values[i] < value)  // if smaller make i midpoint above
        {
            i = i + lround((float)x/2.0); //round result up to avoid program getting stuck before the end
            x = x/2;
        }
        
        else if(values[i] > value)  // if bigger make i midpoint below
        {
            i = i - lround((float)x/2.0);
            x = x/2;
        }
    }
       
                /*  
    for(int i = 0; i <= n; i++)  //LINEAR SEARCH
    {
        if(values[i] == value)
            return true;   
    }           */
    
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n) //use: ./generate 1000 50 | ./find 127
{
            /*debug - list of presorted variables
        printf("--old list--\n");  
            for(int i=0;i<n;++i)
                printf("%i\n", values[i]);
        printf("--old list--\n");
            debug B4*/
            
        for(int i = 0, swap = 0; i <= n;)    // TODO: implement an O(n^2) sorting algorithm
        {
            if(values[i] > values[i + 1] && (i + 1) < n)
            {
            swap = values[i + 1];
            values[i + 1] = values[i];
            values[i] = swap;
            i = 0;    //this is inefficient because program will return to values[0] after each swap, should probably switch to boolean falg fo "wasSwap"
            }
            else
            i++;
        }   

                      /*  //debug - list of (allegedly, supposedly, hopefully) sorted variables
        printf("--new list--\n");   
            for(int i=0;i<n;++i)
                printf("%i\n", values[i]);
        printf("--new list--\n");
                        //debug after */
    return;
}