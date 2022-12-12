#include <stdio.h>

char fileBuf[10000];
char *treesMat[100];

int visible[100][100];

int tokenize(char *s, char **tokens, int len)
{
    int i = 0;
    tokens[i++] = s; 
    for(char *curr = s, *end = s + len; curr < end; curr++)
    {
        if(*curr == '\n'){
            *curr = '\0';
            curr++;
            tokens[i++] = curr;
        }
    }

    return tokens[1]-tokens[0]-1;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if(!fp){
        fprintf(stderr, "Can't open: input.txt\n");
        return 1;
    }

    int charsRead = fread(fileBuf, 1, sizeof(fileBuf), fp);

    fclose(fp);

    int dim = tokenize(fileBuf, treesMat, charsRead);

 
    for(int i = 0; i < dim; i++)
    {

        //from the left
        char maxHeight = -1;
        char height;
        for(int j = 0; j < dim; j++){
            height = treesMat[i][j];
            if(height>maxHeight){
                maxHeight = height;
                visible[i][j] = 1;
            }
        }

        //from the right
        maxHeight = -1;
        for(int j = dim-1; j >= 0; j--){
            height = treesMat[i][j];
            if(height>maxHeight){
                maxHeight = height;
                visible[i][j] = 1;
            }
        }

        //from the top
        maxHeight = -1;
        for(int j = 0; j < dim; j++){
            height = treesMat[j][i];
            if(height>maxHeight){
                maxHeight = height;
                visible[j][i] = 1;
            }
        }

        //from the bottom
        maxHeight = -1;
        for(int j = dim-1; j >= 0; j--){
            height = treesMat[j][i];
            if(height>maxHeight){
                maxHeight = height;
                visible[j][i] = 1;
            }
        }

           
    }



    int ans = 0;
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            ans += visible[i][j];

    printf("%d\n", ans);
}