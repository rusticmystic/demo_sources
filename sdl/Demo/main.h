#include <iostream>

#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include "event.h"
//#include "SDL_ttf.h"


class Demo : public DemoEvent {
    SDL_Surface *Screen;
    SDL_Surface *bmp;
    bool Running;
    int WindowWidth;
    int WindowHeight;
    SDL_Event event;
    int x,y;

    // Add a joystick
    SDL_Joystick *Joy;

public:
    // Constructor
    Demo(int W=640,int H=480) : WindowHeight(H),WindowWidth(W),Screen(0),bmp(0),x(0),y(0) {
        // Let us set this variable;
        Running = true;
    }

    // Destructor

    // Methods
    bool Init();
    void HandleEvent(SDL_Event* Event);
    void Execute();
    void Loop();
    void Render();
    void Cleanup();

    // Actions onn event
    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
    void OnExit();
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnJoyButtonDown(Uint8 which, Uint8 button);




};

// Make the gam eusing this tutorial
// http://www.sdltutorials.com/sdl-net-part-1-user-tutorial
// uses
class DemoSoundBank {

};

// uses SDL Image
class DemoImageBank {

public:
SDL_Surface * LoadImage(char * file);
void Clean();

};

// uses SDL TTF
class DemoFont {


};