#include <stdio.h>
#include "SDL.h" // include SDL header



#pragma pack(push)
#pragma pack(2)
typedef struct                       /**** BMP file header structure ****/
{
    unsigned short bfType;           /* Magic number for file */
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;
;

typedef struct                       /**** BMP file info structure ****/
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct {
    unsigned char r,g,b,junk;
} COLOURINDEX;
// IiiHHIIiiII"

int main() {

    FILE *fp = fopen("a.bmp","rb");
    char * iter;
    int i,j;


    BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
    COLOURINDEX Pixel;

    int width, height;

    if(!fp)
        perror("No File");


    fread(&BFH,sizeof(BFH),1,fp);
    fread(&BIH,sizeof(BIH),1,fp);

    width = BIH.biWidth;
    height = BIH.biHeight;

    int channels = 3; // for a RGB image
    char* pixels = new char[width * height * channels];

    iter = pixels;

   
    // READING BMP image data to pixels
    // BMP is stored inverted with lasts pixel first
    // Call these in a while loop , and run upto height x width
#ifdef PIXEL_BY_PIXEL_FOR_DEMO
    for (i =0; i <= height; i ++)
        for (j=0; j< width; j++)
        {
            fread(iter,4,1,fp);
    //printf("R %d, G %d B %d %d\n",Pixel.r,Pixel.g,Pixel.b, Pixel.junk);
        iter+=4;
        }
#else
    fread(iter,4,width*height,fp);
#endif

    // init SDL
    SDL_Surface *screen; // even with SDL2, we can still bring ancient code back
    SDL_Window *window;
    SDL_Surface *image;

        SDL_Renderer *renderer;
    SDL_Texture *texture;

    SDL_Init(SDL_INIT_VIDEO); // init video

    // create the window like normal
    window = SDL_CreateWindow("BMP Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

    // but instead of creating a renderer, we can draw directly to the screen
    screen = SDL_GetWindowSurface(window); 
    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (!renderer) {
        fprintf(stderr, "SDL: could not create renderer - exiting\n");
        exit(1);
    }

    // Allocate a place to put our YUV image on that screen
    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_YV12,
            SDL_TEXTUREACCESS_STREAMING,
            pCodecCtx->width,
            pCodecCtx->height
        );
    if (!texture) {
        fprintf(stderr, "SDL: could not create texture - exiting\n");
        exit(1);
    } 


    // Cretae window and surface
    
    
    image = SDL_CreateRGBSurfaceFrom((void*)pixels,
                width,
                height,
                channels * 8,          // bits per pixel = 24
                width * channels,  // pitch
                0x0000FF,              // red mask
                0x00FF00,              // green mask
                0xFF0000,              // blue mask
                0);                    // alpha mask (none)

    SDL_BlitSurface(image, NULL, screen, NULL); 
   
   
    SDL_FreeSurface(image);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(8000);
    SDL_DestroyWindow(window);
    SDL_Quit();
// 


return 0;
}
