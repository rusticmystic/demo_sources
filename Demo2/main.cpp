#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "main.h"


void Demo::CallMe() {
    printf("I am called\n");


    Rectangle R(200,200);
    R.Fill(0,255,255);
    //SDL_Surface *k = SDL_SetVideoMode(400, 400, 32,SDL_SWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface *S = R.GetSurface();

    printf("SD: %s",Screen);
    SDL_BlitSurface(S,0,Screen,0);
    SDL_Flip(Screen);
    SDL_Delay(2000);
}

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

    TopRow[0].Fill(05,200,250);
    TopRow[0].SetPos(0,0);
    SDL_BlitSurface(TopRow[0].GetSurface(),0,Screen,TopRow[0].GetRect());

    TopRow[1].Fill(20,100,180);
    TopRow[1].SetPos(160,0);
    SDL_BlitSurface(TopRow[1].GetSurface(),0,Screen,TopRow[1].GetRect());

    TopRow[2].Fill(250,133,190);
    TopRow[2].SetPos(2*160,0);
    SDL_BlitSurface(TopRow[2].GetSurface(),0,Screen,TopRow[2].GetRect());

    TopRow[3].Fill(32,200,100);
    TopRow[3].SetPos(3*160,0);
    SDL_BlitSurface(TopRow[3].GetSurface(),0,Screen,TopRow[3].GetRect());

    // Uncommentit and move to the class
    LowerRow->Fill(x,y,(x+y)/2);
    LowerRow->SetPos(0,120);
    SDL_BlitSurface(LowerRow->GetSurface(),0,Screen,LowerRow->GetRect());

    //  SDL_BlitSurface(Screen,0,bmp,&dstrect);
    if( (x < 160) && !( x > 160)  && y < 120 )
    {
    // Blit dhoni
    dhoni D;
    D.Origin(0,120);
    SDL_BlitSurface(D.GetSurface(),0,Screen,D.GetRect());

    }
    else if( (x > 320) && y < 120 ) {
    sachin s;
    s.Origin(0,120);
    SDL_BlitSurface(s.GetSurface(),0,Screen,s.GetRect());
    }


    SDL_Flip(Screen);
    SDL_Delay(2);

    // Need to free Surfaces, try to include some other ref counting smart pointer class

}

void Demo::Cleanup()
{

    SDL_FreeSurface(bmp);
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
    //    printf("SDD: Mouse Moves x=%d y=%d\n",x,y);
}

void Demo::OnExit() {

    Running = false;
}

void Demo::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

    if (sym == SDLK_ESCAPE)
        Running = false;

    if (sym == SDLK_1)
        CallMe();
}




