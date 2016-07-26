/* Write a gam viewer utilty s*/

#include <stdio.h>
#include "SDL.h" // include SDL header




#define PIXEL_BY_PIXEL_FOR_DEMO 1

#pragma pack(2)
typedef struct GamPictureHeader_s
{
    unsigned short HeaderSize;
    unsigned short Signature;
    unsigned short Type; /* enum gamfile_type */
    unsigned short Properties;
    unsigned int   PictureWidth; /* For 4:2:0 R2B this is a OR between Pitch
                                    and Width */
    unsigned int   PictureHeight;
    unsigned int   LumaSize;
    unsigned int   ChromaSize;
} GamPictureHeader_t;

typedef struct {
    unsigned char r,g,b,junk;
} COLOURINDEX;
// IiiHHIIiiII"

int main() {

    FILE *fp = fopen("a.gam","rb");
    char * iter;
    int i,j;
 
     
    GamPictureHeader_t G;

    int width, height;

    if(!fp)
        perror("No File");


    fread(&G,sizeof(G),1,fp);

    width = G.PictureWidth;
    height = G.PictureHeight;

    printf(" Width %d Height %d \n",width,height);
    height = 736;
    int channels = 3; // for a RGB image
    char* pixels = new char[width * height * channels];
    
    unsigned char *y = new unsigned char[width * height ];
    int usize = width * height /4 ;
    
    unsigned  char *u = new unsigned char[usize];
    unsigned  char* v = new unsigned char[usize];
    iter = pixels;


    unsigned char *u_iter = u;
    unsigned char *v_iter = v;
   
    // READING BMP image data to pixels
    // BMP is stored inverted with lasts pixel first
    // Call these in a while loop , and run upto height x width
#ifdef PIXEL_BY_PIXEL_FOR_DEMO
   
            fread(y,width*height,1,fp);
            printf(" %x %x\n",y[0],y[1]);
	    // for chroma
	    for (int i=0;i < width *height /4; i+=2)
            {
	    fread(u_iter++,1,1,fp);
	    
	    fread(v_iter++,1,1,fp);
	    //printf(" %x %x\n",*u_iter,*v_iter);
	    
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

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
    fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
    exit(1);
  }
    // create the window like normal
    window = SDL_CreateWindow("BMP Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

    // but instead of creating a renderer, we can draw directly to the screen
    //screen = SDL_GetWindowSurface(window); 
  
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "SDL: could not create renderer - exiting\n");
        exit(1);
    }

    // Allocate a place to put our YUV image on that screen
    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_YV12,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
        );
    if (!texture) {
        fprintf(stderr, "SDL: could not create texture - exiting\n");
        exit(1);
    }
    // Cretae window and surface
    
#if 0 
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
#endif

   SDL_UpdateYUVTexture(
                        texture,
                        NULL,
                        (unsigned char *)y,
                        width,
                        u,
                        width/2,
                        v,
                        width/2
                    );

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);


    SDL_Delay(8000);
    SDL_DestroyWindow(window);
    SDL_Quit();
// 


return 0;
}
