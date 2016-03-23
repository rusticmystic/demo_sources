SDL 1.2 Notes.

**************
There are SDL extension libraries which extend the functionality of SDL to make a good game/graphics software.
Mixer, Image, TTF, gfx




*************SDL******************************
1. Initialise SDL.
   SDL_Init( SDL_INIT_VIDEO );
   (For joy stick the flag can be ORed with the above flag)

2. Making a Window surface which serves as a main window.
    Screen = SDL_SetVideoMode(WindowWidth, WindowHeight, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);

    // Clean up
    SDL_FreeSurface(Screen)

3. Loading a bmp and showing it.
    Make a surface and load bmp into it.
        SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    Blit the bmp surface onto window sureface.
        SDL_BlitSurface(bmp,0,Screen,0)

4. Fill the screen surface with a colour.

    SDL_FillRect(Screen, 0, SDL_MapRGB(Screen->format,R_value ,G_value ,B_value);

5. Making a rectangle and blitting it.

    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;

     // create a surface
     s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
     SDL_FillRect(s, 0, SDL_MapRGB(s->format,R_value ,G_value ,B_value);

6. BMP and WAV can be read direcly using SDL.




If we need sound in our program. We need to init SDL with audio
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC | SDL_INIT_AUDIO);
          -->  If you want to specify which driver SDL uses for audio, you can use the SDL_AudioInit() function instead.
    Then:
       a) Open Audio device: We do this with the SDL_OpenAudio() function.
       This takes two pointers of  SDL_AudioSpec struct. One for desired, one for obtained. We can also set obtained to zero.
       (There's a slightly more advanced function for opening the audio device, SDL_OpenAudioDevice().
       This lets you open multiple audio devices, open capture devices for recording audio, and tell SDL which parts of your SDL_AudioSpec
       you must get back exactly and which you don't really care about.)

       SDL_AudioSpec AudioSettings = {0};

        AudioSettings.freq = SamplesPerSecond;
        AudioSettings.format = AUDIO_S16LE;
        AudioSettings.channels = 2;
        AudioSettings.samples = BufferSize;
        AudioSettings.callback = &SDLAudioCallback;

        SDL_OpenAudio(&AudioSettings, 0);

        Audio starts as paused:
        Unpause using: SDL_PauseAudio(0);
        Pause using    SDL_PauseAudio(1);




7. Additional extensions of SDL.



8. For Additional features in the game, use, AVCODEC and avformat for video playback and swscale for scaling.
   Outline the tasks which can be done:


























### Polling on events and reacting thereof
5. Polling on an event:
    SDL_Event event;
    SDL_PollEvent(&event)

   We can then add switch cases to handle the events.
    switch(Event->type) {
    case SDL_ACTIVEEVENT: {
        switch(Event->active.state) {
        case SDL_APPMOUSEFOCUS: {
            if ( Event->active.gain )    OnMouseFocus();
            else                OnMouseBlur();

            break;
        }
        case SDL_APPINPUTFOCUS: {
            if ( Event->active.gain )    OnInputFocus();
            else                OnInputBlur();

            break;
        }
        case SDL_APPACTIVE:    {
            if ( Event->active.gain )    OnRestore();
            else                OnMinimize();

            break;
        }
        }
        break;
    }

    case SDL_KEYDOWN: {
        OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }

    case SDL_KEYUP: {
        OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }

    case SDL_MOUSEMOTION: {
        OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
        break;
    }

    default:
    }
