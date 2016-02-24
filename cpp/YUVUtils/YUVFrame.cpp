/* Simple YUV utility library
 * It supports NV12 and YUV420p  formats
 * Added Features: Conversion NV12/yuv420p, Display Frame, Crop Frame, CRC calculation
 *
 * Author: Shivdeep Singh
 * STMicroelectronics
 * It uses SDL to display  YUV frames
 * */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "crc.h"
#include "YUVFrame.h"

//SDL
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

//Contructor
YUVFrame::YUVFrame(int w, int h)
{
    //display_width is used for CRC calculation
    display_width = width = w;
    display_height = height = h;

    y = (unsigned char *) malloc (w * h);
    u = (unsigned char *) malloc ((w * h / 2));
    v = (unsigned char *) malloc ((w * h / 2));
    
    if(!y || !u || !v) {
        printf("Could not Allocate memory for Frame\n");
        return;
    }
    //printf("Allocated y=%p,u=%p,v=%p\n",y,u,v);

    empty = 1;

    crc_luma   = 0xffffffff;
    crc_chroma = 0xffffffff;
}

int YUVFrame::show() {
    std::cout << "Show Output on SDL Overlay" <<std::endl;
    SDL_Overlay     *OV;
    SDL_Surface     *screen;
    SDL_Rect        rect;
    SDL_Event       event;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }

    // Make a screen to put our video
#ifndef __DARWIN__
    screen = SDL_SetVideoMode(width, height, 0, 0);
#else
    screen = SDL_SetVideoMode(width, height, 24, 0);
#endif

    // Allocate a place to put our YUV(420p,IYUV image on that screen
    OV = SDL_CreateYUVOverlay(width,
                               height,
                               SDL_IYUV_OVERLAY,
                               screen);

    SDL_LockYUVOverlay(OV);

    OV->pixels[0] = y;
    OV->pixels[2] = v;
    OV->pixels[1] = u;

    SDL_UnlockYUVOverlay(OV);
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    
    SDL_DisplayYUVOverlay(OV, &rect);
    // SDL_Delay(2000);
    bool MainLoop=1;

    //Quit the window pressing Escape or cross button
    while(MainLoop) {
        while(SDL_PollEvent(&event)) {

            switch(event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym=SDLK_ESCAPE)
                {
                    printf("Exit window\n");
                    MainLoop = false;
                    break;
                }
            case SDL_QUIT:
                MainLoop = false;
                break;
            }
            SDL_Delay(20);
        }
    }
    SDL_FreeYUVOverlay(OV);
}

/* Calculate CRC32 of the Frame*/
void YUVFrame::crc()
{
    crc_luma   = 0xffffffff;
    crc_chroma = 0xffffffff;
    unsigned char *y1 = y;
    unsigned char *u1 = u;
    unsigned char *v1 = v;

    //Buffer Ready, Calculate CRC
    crc_luma = DTV_crc_init();

    int skip = width - display_width;

    for (int i = 0; i < display_height; i++)
    {
        for (int j = 0; j < display_width; j++)
        {
            crc_luma = DTV_crc_luma_update(crc_luma, y1++, 1);
        }
        y1 += skip;
    }

    //chroma crc
    skip = skip / 2;
    for (int i = 0; i < display_height / 2; i++)
    {
        for (int j = 0; j < display_width / 2; j++)
        {
            crc_chroma = DTV_crc_chroma_update(crc_chroma, u1++, v1++, 1);
        }
        u1 += (skip); //is it skip/2 for CHROMA CRC
        v1 += (skip); //is it skip/2
    }

    printf("Luma CRC = %u\n", crc_luma);
    printf("Chroma CRC = %u\n", crc_chroma);
    //std::cout << " Chroma CRC: "<< crc_chroma << std::endl;
}

void YUVFrame::crc2_field(int field)
{
    crc_luma   = 0xffffffff;
    crc_chroma = 0xffffffff;
    unsigned char *y1 = y;
    unsigned char *u1 = u;
    unsigned char *v1 = v;

    //Buffer Ready, Calculate CRC
    crc_luma = DTV_crc_init();
    int lumasize =  width * height;
    
    int skip = width - display_width;

    for (int i = 0; i < display_height; i++)
    {
        if (i % 2 == field)
        {
            for (int j = 0; j < display_width; j++)
            {
                crc_luma = DTV_crc_luma_update(crc_luma, y1++, 1);
            }
        }
        else
        {
            y1 += display_width;
        }
        y1 += skip;
    }

    //chroma crc
    skip = skip / 2;
    for (int i = 0; i < display_height / 2; i++)
    {
        if (i % 2 == field)
        {
            for (int j = 0; j < display_width / 2; j++)
            {
                crc_chroma = DTV_crc_chroma_update(crc_chroma, u1++, v1++, 1);
            }
        }
        else
        {
            u1 += display_width / 2;
            v1 += display_width / 2;
        }
        u += (skip)/2; //is it skip/2
        v += (skip)/2; //is it skip/2
    }

    printf("Field	%6s Luma CRC = %15u ",field==0?"TOP":"BOTTOM",crc_luma);
    printf(" Chroma CRC = %15u\n",crc_chroma);
}

/*Calculate Filedwise CRC for Interlaced decoded YUV*/
void YUVFrame::crc_interlaced()
{
	std::cout << "\nCRC FieldWise"<< std::endl;
	crc2_field(0);
	crc2_field(1);
}

/*Fill the NV12 Buffer in YUVFrame*/
void YUVFrame::fillnv12(char *data)
{
    if(!data) {
        printf("Can't Fill Buffer. Buffer is Empty.\n");
    }

    //segregate the data into Y<U and V arrays
    int luma = width * height;
    int chroma = (width * height) / 4;
    memcpy(y, data, luma);
    data += luma;

    unsigned char *iter_u,*iter_v;
    iter_u = u;
    iter_v = v;

    unsigned int i;
    for (i = 0; i < (2 * chroma); i += 2)
    {
        *(iter_u) = *data;
        *(iter_v) = *(data+1);
        iter_u += 1;
        iter_v += 1;
        data += 2;
    }
    
    empty = 0;
}

/*Fill the I420/ yuv420p Buffer in YUVFrame*/
void YUVFrame::fill420p(char *data)
{
    if(!data) {
        printf("Can't Fill Buffer. Buffer is Empty.\n");
    }

    int i;
    int luma = width * height;
    int chroma = (width * height) / 4;

    memcpy(y, data, luma);
    //Can add a check for memcpy fail, if any

    data += luma;
    for (i = 0; i < (chroma); i++)
    {
        u[i] = data[i];
    }
    data += chroma;

    for (i = 0; i < (chroma); i++)
    {
        v[i] = data[i];
    }
    empty = 0;
}

/*  Display Height Width can be set, for CRC calculation and SHOW*/
void YUVFrame::setdisplayheight(int height)
{
    display_height = height;
}

/*  Display Height Width can be set, for CRC calculation and SHOW*/
void YUVFrame::setdisplaywidth(int width)
{
    display_width = width;
}

/* READ YUV frame data in NV12 format YYYYUVUVUV
 * It allocates a buffer and return it after filling data */
unsigned char *YUVFrame::readnv12()
{
    int luma = display_width * display_height;
    int chroma = (display_width * display_height) / 4;

    unsigned char *temp = (unsigned char *)malloc(1.5 * luma);
    unsigned char *iter;

    memcpy(temp, y, luma);
    iter = temp + luma;

    for (int i = 0; i < (chroma); i ++)
    {
        *(iter) = u[i];
        *(iter + 1) = v[i];
        iter+=2;
    }
    return temp;
}

/* READ YUV frame data in yuv420p format YYYYUVUVUV
 * It allocates a buffer and return it after filling data */
unsigned char *YUVFrame::read420p()
{
    //segregate the data into Y U and V arrays
    int luma = display_width * display_height;
    int chroma = (display_width * display_height) / 4; //HALF the width of CB or CR

    char *temp = (char *)malloc(1.5 * luma);
    char *iter;

    memcpy(temp, y, luma);
    iter = temp;
    iter+=luma;

    memcpy(iter, u,chroma);
    iter = iter + chroma;

    memcpy(iter, v,chroma);

    return (unsigned char *)temp;
}

/* Crop the frame and return a new cropped frame */
YUVFrame * YUVFrame::crop(int cwidth,int cheight,int cx,int cy)
{
    //local copies of variables
    int WIDTH = width;
    int HEIGHT = height;

    int start_x = cx;
    int start_y = cy;

    //check initial condition
    if(width < cwidth+cx) {
        std::cout << "Error: X Crop Out of Bound"<< std::endl;
        cwidth = WIDTH-cwidth+cx;
    }
    if(height < cheight+cy) {
        std::cout << "Error: Y Crop Out of Bound"<< std::endl;
        cheight = HEIGHT-cheight+cy;
    }

    //Allocate buffers for cropped frame
    YUVFrame *tempFrame = new YUVFrame(cwidth,cheight);
    unsigned char *temp_luma = (unsigned char *)calloc(cwidth*cheight,1);
    unsigned char *temp_u = (unsigned char *)calloc(cwidth*cheight/4,1);
    unsigned char *temp_v = (unsigned char *)calloc(cwidth*cheight/4,1);

    //Set iterating pointers for cropped frames
    unsigned char *temp_luma_iter;
    unsigned char *temp_u_iter;
    unsigned char *temp_v_iter;

    temp_luma_iter  = temp_luma;
    temp_u_iter = temp_u;
    temp_v_iter = temp_v;
    unsigned char **luma_matrix =(unsigned char **) &temp_luma;
    int i,j;

    unsigned char *u_i,*v_i,*y_i;

    //For Y
    y_i = y + (start_y*WIDTH + start_x);

    for(i = 0; i < cheight; i++)
    {
        memcpy(temp_luma_iter,y_i,cwidth);
        y_i += width;
        temp_luma_iter +=cwidth;
    }

    start_x = start_x / 2;
    start_y = start_y / 2;
    cheight = cheight / 2;
    cwidth  = cwidth / 2;
    //For U and V components half the WIDTH
    WIDTH   = WIDTH / 2;

    //For UV

    u_i = u + (start_y * width + start_x);
    v_i = v + (start_y * width + start_x);

    for(i = 0; i < cheight; i++)
    {

        memcpy(temp_u_iter,u_i,cwidth);
        memcpy(temp_v_iter,v_i,cwidth);
        u_i += WIDTH;
        v_i += WIDTH;
        temp_u_iter += cwidth;
        temp_v_iter += cwidth;
    }

    tempFrame->y = temp_luma;
    tempFrame->u = temp_u;
    tempFrame->v = temp_v;

    return tempFrame;
}

/*Destructor */
YUVFrame::~YUVFrame()
{
	if(y) free(y);
	if(u) free(y);
	if(v) free(y);
}

/* Write a copy contructor to copy yuv arrays and also overload = operator*/











