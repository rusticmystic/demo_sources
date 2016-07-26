#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "main.h"

// Constructor of the application
bool Demo::Init() {

    // Initialise the video and allocate the screen
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    Screen = SDL_SetVideoMode(WindowWidth, WindowHeight, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !Screen )
    {
        printf("Unable to set %dx%d video: %s w\n", WindowWidth,WindowHeight ,SDL_GetError());
        return false;
    }

    // Load bmp
    SDL_Surface* bmp = SDL_LoadBMP("./cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return false;
    }

    // Initialise Joystick
    Joy = SDL_JoystickOpen( 0 );

    //If there's a problem opening the joystick
    if( Joy == NULL )
    {
        printf("Error Opening Joystick %s",SDL_GetError());
        // fallback to keyboard controls
        // return false;
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

    SDL_BlitSurface(bmp,0,Screen,0);
    SDL_FillRect(Screen, 0, SDL_MapRGB(Screen->format, x, y, (x+y)/2));

    SDL_Flip(Screen);
    //  SDL_Delay(2000);
}

void Demo::Cleanup()
{

    SDL_FreeSurface(bmp);
    if(Joy) SDL_JoystickClose( Joy );
    SDL_Quit();
}

int main ( int argc, char** argv )
{

    Demo D = Demo(640,480);

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

    if(sym == SDLK_1)
    {
// demo try to blit an image
        printf("Key 1 Pressed. Show Image\n");
//SDL_Surface *s = SDL_SetVideoMode(WindowWidth, WindowHeight, 32,SDL_SWSURFACE|SDL_DOUBLEBUF);
        SDL_Surface *i = SDL_LoadBMP("cb.bmp");

        SDL_BlitSurface(i,NULL,Screen,NULL);
        SDL_Flip(Screen);
        SDL_Delay(5000);
//SDL_FreeSurface(s);
    }
    if (sym == SDLK_ESCAPE)
        Running = false;


}


void Demo::OnJoyButtonDown(Uint8 which, Uint8 button)
{
    printf("SDD: JoyStick Button which %d button %d\n",which, button);



}

