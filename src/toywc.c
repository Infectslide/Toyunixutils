#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFSIZE 100
int l ,w ,c;
int tl, tw, tc;
int updcount(char* , int* , int* , int*, char* , int);
void printwc(int , int , int);
void printtwc(int, int, int);
char buff[BUFFSIZE];

int main(int argc, char *argv[argc+1]){
    int wf,cf,lf;
    FILE* fp;
    int bread = 0;
    char wcond = 0;
    l = w = c = tl= tw = tc = wf = cf = lf = 0;
    if(argc == 1){
        while((bread = read(STDIN_FILENO, buff, BUFFSIZE)) > 0){
            updcount(buff, &l, &w, &c, &wcond, bread);
        }
        printwc(lf, wf, cf);
        printf("\n");
    }
    else {
        for (char** clarg = argv + 1;--argc > 0; clarg++){
            l = w = c = wcond = 0;
            if(**(clarg) == '-'){
                if(!(*((*clarg)+1))){
                    while((bread = read(STDIN_FILENO, buff, BUFFSIZE)) > 0){
                        updcount(buff, &l, &w, &c, &wcond, bread);
                    }
                    printwc(lf, wf, cf);
                    printf(" -\n");
                }
                else {
                    for(char* clopt = *clarg + 1; *clopt != '\0'; clopt++){
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
                    printwc(lf, wf, cf);
                    printf(" %s\n", *clarg);
                }
                else {
                    fprintf(stderr, "%s: %s: No such file or directory\n",argv[0], *clarg);
                }
            }
            tl += l;
            tw += w;
            tc += c;
        }
        printtwc(lf,wf,cf);
        printf(" total\n");
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

void printwc(int fl, int fw, int fc){
    if((fl && fw && fc) || !(fl || fw || fc)){
        printf("%7d %7d %7d", l, w ,c);
    }
    else if(fl && fw){
        printf("%7d %7d", l , w);
    }
    else if(fl && fc){
        printf("%7d %7d", l, c);
    }
    else if(fw && fc){
        printf("%7d %7d", w, c);
    }
    else if(fw){
        printf("%7d", w);
    }
    else if(fc){
        printf("%7d", c);
    }
    else if(fl){
        printf("%7d", l);
    }
}

void printtwc(int fl, int fw, int fc){
    if((fl && fw && fc) || !(fl || fw || fc)){
        printf("%7d %7d %7d", tl, tw ,tc);
    }
    else if(fl && fw){
        printf("%7d %7d", tl , tw);
    }
    else if(fl && fc){
        printf("%7d %7d", tl, tc);
    }
    else if(fw && fc){
        printf("%7d %7d", tw, tc);
    }
    else if(fw){
        printf("%7d", tw);
    }
    else if(fc){
        printf("%7d", tc);
    }
    else if(fl){
        printf("%7d", tl);
    }
}
