// header files
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// types
typedef char BYTE;

// prototypes
bool connected(void);
void error(unsigned short code);
void freedir(struct dirent** namelist, int n);
void handler(int signal);
char* htmlspecialchars(const char* s);
char* indexes(const char* path);
void interpret(const char* path, const char* query);
void list(const char* path);
bool load(FILE* file, BYTE** content, size_t* length);
char* lookup(char* path);
bool parse(const char* line, char* path, char* query);
const char* reason(unsigned short code);
void redirect(const char* uri);
bool request(char** message, size_t* length);
void respond(int code, const char* headers, const char* body, size_t length);
void start(short port, const char* path);
void stop(void);
void transfer(const char* path, const char* type);
char* urldecode(const char* s);



int main(void)
{

    char* abs_path =malloc(sizeof (LimitRequestLine) + 1);
    char* query =malloc(sizeof (LimitRequestLine) + 1);
    if (parse("GET / HTTP/1.1/r/n", abs_path, query))
    printf("\nRETURNED TRUE \n query:_%s \n abs path:_%s\n", query ,abs_path );
    else
    printf("\nRETURNED FALSE \n query:_%s \n abs path:_%s\n", query ,abs_path );
    return 1;
}

bool parse(const char* line, char* abs_path, char* query)
{

    
    //malloc space for ptr array
    char* token[5];
    for (int i=0; i<5; i++)
    {
      token[i] = malloc(LimitRequestFieldSize); 
    }
    
    //copy line and prepare to parse
    char* lineCopy = malloc (LimitRequestLine);
    strcpy(lineCopy, line);
    char* startPtr = lineCopy;
    char* nextStop = strchr(startPtr, ' ');
    
    //INPUT CHECKS - TODO
    //make sure 2 spaces exist before a "\r\n" (all within limit request line)
    if ( strstr(lineCopy, " ")  == NULL || strstr(nextStop, " ") == NULL || strstr(nextStop, "\r\n") == NULL )
        {
            //respond to the browser with 400 Bad Request and return false.
        }
    
    //Parsing time :)
    for (int i=0; i<3; i++)
    {
        //get section between pointers
        strncpy(token[i], startPtr, (nextStop - startPtr) );
        
        //null terminate
        *( token[i] + (nextStop - startPtr) ) = '\0';
        
        //advance start pointer past last space, and find next stop for stop pointer (if any)
        startPtr = (strchr(startPtr, ' ') + 1);
        if (i == 0) //if request target next
            nextStop = strchr(startPtr, ' ');
        else if (i == 1) //if version next
            nextStop = strstr(startPtr, "/r/n");
            //(strchr(startPtr, '\r') - 1 );


    }
    
//if method [0] is not GET, respond to the browser with 405 Method Not Allowed and return false;
if (strcmp(token[0],"GET") != 0)  
   {
    //respond(405, "Method Not Allowed", NULL, 0);
    return false;
   }
//if request-target [1] does not begin with /, respond to the browser with 501 Not Implemented and return false;
if (strncmp(token[1],"/",1) != 0) 
   {
    //respond(501, "Not Implemented", NULL, 0);
    return false;
   }  

//if request-target [1] contains a ", respond to the browser with 400 Bad Request and return false;
if ( strstr(token[1], "\"")  != NULL )
   {
    //respond(400, "Bad Request", NULL, 0);
    return false;
   }  
//if HTTP-version [2] is not HTTP/1.1, respond to the browser with 505 HTTP Version Not Supported and return false;
if (strcmp(token[2],"HTTP/1.1") != 0)  
   {
    //respond(505, "HTTP Version Not Supported", NULL, 0);
    return false;
   }  
    
//Parse request target into abs-path [3] and query [4]

startPtr = token[1];

//check for query text
if ( strchr(startPtr, '?') != NULL && *( strchr(startPtr, '?') +1 ) != '\0')
    {
        nextStop = strchr(startPtr, '?');
        //copy abs path
        strncpy(token[3], startPtr, (nextStop - startPtr) );
        
        //zero terminate
        *( token[3] + (nextStop - startPtr) ) = '\0';
        
        //move pointer to start of query
        startPtr = nextStop + 1;
        
        //copy query
        strcpy(token[4], startPtr);
    }
//if no query or empty query
else
    {
        //eliminate ? if empty query
        if ( strchr(startPtr, '?') != NULL)
        
        //null terminate 
        *(strchr(startPtr, '?')) = '\0';
        
        strcpy(token[3], startPtr);
        token[4][0]= '\0';
    }

//check that query does not contain "
if ( strstr(token[4], "\"")  != NULL )
    {
        //respond(400, "Bad Request", NULL, 0);
        return false;
    }    

    //DEBUG
    printf("parsed: /n meth %s\n req %s\n ver %s\n abspath %s \n Query %s \n", token[0], token[1], token[2], token[3], token[4]);

//write  abs path [3] and Query [4] to passed pointers
strcpy(abs_path, token[3]);
strcpy(query, token[4]);

//FREE memory
for (int i=0; i<5; i++)
    {free(token[i]);}
    
// th-th-th-that's all, folks!
return true;

}

bool load(FILE* file, BYTE** content, size_t* length)                           //LOAD !!!!!!!!!!!!!!!!!!!
{
    // TODO
    return false;
}