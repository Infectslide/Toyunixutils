#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFSIZE 100

int updcount(char* , int* , int* , int*, char* , int);
char buff[BUFFSIZE];

int main(int argc, char *argv[argc+1]){
    int l,w,c, tl, tw, tc;
    int wf,cf,lf;
    FILE* fp;
    int bread = 0;
    char wcond = 0;
    l = w = c = tl= tw = tc = wf = cf = lf = 0;
    if(argc == 1){
        while((bread = read(STDIN_FILENO, buff, BUFFSIZE)) > 0){
            updcount(buff, &l, &w, &c, &wcond, bread);
        }
        printf("%7d %7d %7d\n", l , w , c);
    }
    else {
        for (char** clarg = argv + 1;--argc > 0; clarg++){
            l = w = c = wcond = 0;
            if(**(clarg) == '-'){
                if(!(*((*clarg)+1))){
                    while((bread = read(STDIN_FILENO, buff, BUFFSIZE)) > 0){
                        updcount(buff, &l, &w, &c, &wcond, bread);
                    }
                    printf("%d %d %d -\n", l , w , c);
                }
                else {
                    for(char* clopt = *clarg; *clopt != '\0'; clopt++){
                        switch(*clopt){
                        case 'l':
                            lf = 1;
                            break;
                        case 'w':
                            wf = 1;
                            break;
                        case 'c':
                            cf = 1;
                            break;
                        default:
                            fprintf(stderr, "Invalid Option\n");
                            break;
                        }
                    }
                }
            }
            else {
                fp = fopen(*clarg , "r");
                if(fp){
                    while((bread = read(fp->_fileno, buff, BUFFSIZE)) > 0){
                        updcount(buff, &l, &w, &c, &wcond, bread);
                    }
                    printf("%d %d %d %s\n", l , w , c, *clarg);
                }
                else {
                    fprintf(stderr, "%s: %s: No such file or directory\n",argv[0], *clarg);
                }
            }
            tl += l;
            tw += w;
            tc += c;
        }
        printf("%d %d %d total\n", tl , tw , tc);
    }
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
