#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "YUVFrame.h"

void ShowHelp() {
    std::cout << "Help: " << std::endl;
    std::cout << "-i InputFileName [upto 50 char]" << std::endl;
    std::cout << "-w Width" << std::endl;
    std::cout << "-h Height" << std::endl;
    std::cout << "-n [0|1 -->O for yuv420p,    1 for nv12]" << std::endl;
    std::cout << "-p cropped Width" << std::endl;
    std::cout << "-q cropped Height" << std::endl;
    std::cout << "-d filename" << std::endl;
}

int main(int arg, char *argv[]) {

    //Basic Variables
    int opt;
    char  InputFilename[50];
    char  OutputFilename[50];
    int   Width, Height;
    int   cropWidth=0;
    int   cropHeight=0;
    int   nv12 = 0;
    int   interlaced=0;
    int   dump = 0;

    //Get Name of File and width and Height and type of YUV

    while((opt=getopt(arg,argv,"i:w:h:n:p:q:d:"))!=-1) {
        switch(opt) {
        case 'i':
            sprintf((char *)&InputFilename[0],"%s",optarg);
            break;
        case 'w':
            Width = atoi(optarg);
            break;
        case 'h':
            Height = atoi(optarg);
            break;
        case 'n':
            nv12 = atoi(optarg);
            break;
        case 'x':
            interlaced = atoi(optarg);
            break;
        case 'p':
            cropWidth = atoi(optarg);
            break;
        case 'q':
            cropHeight = atoi(optarg);
            break;
        case 'd':
            sprintf((char *)&OutputFilename[0],"%s",optarg);
            printf ("Output: %s \n",OutputFilename);
            dump = 1;
            break;
        default:
            ShowHelp();
            return -1;
            break;
        }
    }

    //
    if(!InputFilename || !OutputFilename) {
        ShowHelp();
        return 0;
    }

    //Open the file , allocate a buffer and put the width height in local variables
    char * temp = NULL;
    FILE* Fd;
    FILE* Fp = fopen(InputFilename,"rb+");
    if(!Fp) {
        std::cout << "Can't Open File" << std::endl;
        ShowHelp();
        return -1;
    }

    if(dump) {
        Fd = fopen(OutputFilename,"wb");
        if(!Fd) {
            std::cout << "Can't Open File" << std::endl;
            ShowHelp();
            return -1;
        }
    }

    //Estimate the number of frames and file size
    //Go to end
    fseek(Fp,0L, SEEK_END);
    int FileSize = ftell(Fp);
    //Seek to Start
    fseek(Fp,0L, SEEK_SET);
    int NoOFFrames  = FileSize / (Width * Height* 1.5);


    temp = (char *)malloc(Width * Height* 1.5);
    YUVFrame *F1 = new YUVFrame(Width, Height);

    std::cout << "File ptr is  " << Fp<< " temp " << temp <<"\n\n" <<std::endl;
    if(cropHeight &&  cropWidth) {
        std::cout << "Cropping to  WxH:" << cropWidth<< "x" << cropHeight <<"\n\n" <<std::endl;
    }

    for(int i=0; i <NoOFFrames; i ++) {

        //Read the Frame  and calculate CRC
        fread(temp,Width * Height* 1.5,1,Fp);
        if(temp) {
            if(!nv12) {
                F1->fill420p(temp);
            }
            else {
                F1->fillnv12(temp);
            }

            // cropped dump
            if(cropWidth && cropHeight)
            {
                YUVFrame *F2 = F1->crop(cropWidth,cropHeight,0,0);

                std::cout << "Frame No: " << i<< std::endl;

                unsigned char * buff = F2->read420p();
                fwrite(buff,cropWidth*cropHeight,1,Fd);

                
            }

        }
    }

    delete F1;
 //   free(temp);

    return 0;
}


