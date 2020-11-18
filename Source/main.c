/* Show the CGI (Common Gateway Interface) environment variables */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Print a basic HTTP header. */

static void
print_http_header (const char * content_type)
{
    printf ("Content-Type: %s\n\n", content_type);
}

void print_file(FILE *file){
    int c;
    if (file){
        while((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}

int 
main ()
{
    print_http_header ("text/html");
   
    FILE* table = fopen("/usr/lib/cgi-bin/Source/Main.html", "r");
    print_file(table);

    char *content = getenv("CONTENT_LENGTH");
    
    if(content)
    {
        int len = atoi(content);
        char input[len + 1];
            
        printf("<p> lengte: %s </p>",content);
        fgets(input,sizeof(input), stdin);
        printf("<p> input data string: %s </p>", input);

        char *ptr = strtok(input,"&=");
        ptr = strtok(NULL,"&=");
        char *Voornaam = ptr;
        ptr = strtok(NULL,"&=");
        ptr = strtok(NULL,"&=");
        char *Naam = ptr;
        ptr = strtok(NULL,"&=");
        ptr = strtok(NULL,"&=");
        char *inputTime = ptr;

        system("truncate -s-2 /var/www/html/Info.json");

        FILE *json = fopen("/var/www/html/Info.json", "a");
        fprintf(json, ",\n\t{\n\t\t\"Voornaam\": \"%s\",\n\t\t\"Naam\": \"%s\",\n\t\t\"Tijd\": \"%s\"\n\t}\n]",Voornaam,Naam,inputTime);

    }

    return 0;
}