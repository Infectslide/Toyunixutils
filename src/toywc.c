#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#define BUFFSIZE 100

int updcount(char* , int* , int* , int*, char* , int);
char buff[BUFFSIZE];

int main(int argc, char *argv[argc+1]){
    int l,w,c;
    int bread = 0;
    char wcond = 0;
    l = w = c = 0;
    if(argc == 1){
        while((bread = read(STDIN_FILENO, buff, BUFFSIZE)) > 0){
            updcount(buff, &l, &w, &c, &wcond, bread);
        }
    }
    printf("%7d %7d %7d\n", l , w , c);
}

int updcount(char* s, int* l, int* w, int* c,char* wcond, int bread){
    int nl,nw,nc;
    nl = nc = nw = 0;
    for(int i = 0; i < bread; s++,i++){
        if(isspace(*s)){
            nc++;
            *wcond = 0;
            if(*s == '\n'){
                nl++;
            }
        }
        else if(!isspace(*s)){
            nc++;
            if(!(*wcond)){
                nw++;
            }
            *wcond = 1;
        }
    }
    *l += nl;
    *w += nw;
    *c += nc;
    return 0;
}
