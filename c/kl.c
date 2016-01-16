#include <stdio.h>
#include <unistd.h>

int main() {
    FILE *f,*g;
    char * buffer="This is data";
    f=fopen("1.txt","w+");
    g=fopen("2.txt","wb");
    fwrite(buffer,10,1,f);
    fwrite(buffer,10,1,g);

    return 0;
}
