#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "main.h"

// Constructor of the application
bool Demo::Init() {

    // Initialise the video and allocate the screen
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    Screen = SDL_SetVideoMode(WindowWidth, WindowHeight, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !Screen )
    {
        printf("Unable to set %dx%d video: %s w\n", WindowWidth,WindowHeight ,SDL_GetError());
        return false;
    }

    // Load bmp
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Demo::HandleEvent(SDL_Event* Event) {

    OnEvent(Event);

}

void Demo::Execute() {

    if(Init() == false) {
        return ;
    }

    // Handle Event
    Loop();

}

void Demo::Loop() {

    while (Running)
    {
        // message processing loop
        while(SDL_PollEvent(&event)) {
            HandleEvent(&event);
        }

        Render();
    }
}

void Demo::Render()
{

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;

    SDL_FillRect(Screen, 0, SDL_MapRGB(Screen->format, x, y, (x+y)/2));
    //    SDL_BlitSurface(Screen,0,bmp,&dstrect);
    SDL_Flip(Screen);
}

void Demo::Cleanup()
{

    SDL_FreeSurface(bmp);
    SDL_Quit();
}

int main ( int argc, char** argv )
{

    Demo D = Demo(320,240);

    D.Execute();

    return 0;
}

// Actions on Events
void Demo::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    x = mX;
    y = mY;
    printf("SDD: Mouse Moves x=%d y=%d\n",x,y);
}

void Demo::OnExit() {

Running = false;
}

void Demo::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

if (sym == SDLK_ESCAPE)
                Running = false;

}


