#include <stdio.h>
#include <string.h>

char buf[200];
char *field[20];

char* unquote(char* p)
{
    if (p[0] == '"')
    {
        if (p[strlen(p) - 1] == '"')
            p[strlen(p) - 1] = '\0';
        ++p;
    }

    return p;
}

int csvgetline(FILE* fin)
{
    int nfield;
    char *p, *q;

    if (fgets(buf, sizeof(buf), fin) == NULL)
        return -1;

    nfield = 0;
    for (q = buf; (p = strtok(q, ",\r\n")) != NULL; q = NULL)
        field[nfield++] = unquote(p);

    return nfield;
}


int main(int args, char** argv)
{
    int i, nf;

    while ((nf = csvgetline(stdin)) != -1)
    {
        for (int i = 0; i < nf; ++i)
            printf("field[%d] = '%s'\n", i, field[i]);
    }

    return 0;
}