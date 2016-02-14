#include <stdio.h>
#include "SDL.h" // include SDL header

#
int main() {

    FILE *fp = fopen("a.yuv","rb");
    char * iter;
    int i,j;

    int width, height;

    if(!fp)
        perror("No File");

    width = 640;
    height = 480;

    printf(" Width %d Height %d \n",width,height);

    unsigned char *y = new unsigned char[width * height *1.5];
    int usize = width * height /4 ;

    unsigned  char *u = new unsigned char[usize];
    unsigned  char* v = new unsigned char[usize];

    unsigned char *u_iter = u;
    unsigned char *v_iter = v;


    int  k=fread(y,1,width*height *1.5,fp);
    printf(" %x %x %d\n",y[0],y[1],k);
    // for chroma
    for (int i=0; i < width *height /4; i+=2)
    {
        fread(u_iter++,1,1,fp);

        fread(v_iter++,1,1,fp);
        //printf(" %x %x\n",*u_iter,*v_iter);

    }


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
    window = SDL_CreateWindow("YUV Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

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
                  SDL_PIXELFORMAT_IYUV,
                  SDL_TEXTUREACCESS_STREAMING,
                  width,
                  height
              );
    if (!texture) {
        fprintf(stderr, "SDL: could not create texture - exiting\n");
        exit(1);
    }
    // Cretae window and surface

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
