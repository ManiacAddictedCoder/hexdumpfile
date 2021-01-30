/* Initialize the Preprocessor Directives. */
#include <stdio.h>      //  I/O Stream.  
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>
/* End Directive. */

/* Functions Fields. */
int calLenFunc(const void *filename)
{
    FILE *fp = fopen(filename, "r+");
    int length = 0, c;
    while((c = fgetc(fp)) > 0)
    {
        length++;
    }
    int offset = 0;
    if(length % 16 == 0)
    {
        return length;
    }
    else
    {
        if(length < 16)
        {
            offset = 16 % length; 
            length += offset;
            return length;
        }
        else
        {
            int compared = 16;
            while(length > compared)
            {
                compared += 16;
            }
            offset = compared % length;
            length += offset;
            return length;
        }
    }
}

void HexDump(const void *data, size_t size)
{
    FILE *fp = fopen(data, "r+");
    int c, i = 0, count = 0;
    char buffer[17];
    buffer[16] = '\0';
    while(i < size && (c = fgetc(fp)) != 0)
    {
        if(i == 0 || i % 16 == 0)
        {
            printf("| %08X |", count);
            count++;
        }        
        if(c > 0 && c != 32)
        {
            printf("%3X", c);
            buffer[i % 16] = (unsigned char)c;
        }
        else if (c == -1 || c == 32)
        {
            printf(" %02X", 0);
            buffer[i % 16] = '.';
        }
        if((i + 1) % 16 == 0 && (i + 1) != size)
        {
            printf(" | %s \n", buffer);
        }
        else if((i + 1) == size)
        {
            printf(" | %s", buffer);
        }
        ++i;
    }
}
/* End functions. */


/* Main function. */
int main(int argc, char*argv[])
{
    int length = calLenFunc(argv[1]);
    HexDump(argv[1], length);
    return 0;
}