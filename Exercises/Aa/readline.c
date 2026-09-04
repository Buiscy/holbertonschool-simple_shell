#include "main.h"

int main(int ac, char **av);
{
    printf("$");
    
	(void)ac;
    while(*av != NULL)
    {
        printf("%s", *av);
        ++av;
    }
    return(0);
}