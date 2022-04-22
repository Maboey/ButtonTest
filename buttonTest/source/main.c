// ====================================================================== INCLUDE & DEFINE ======================================================================
#include <time.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <switch.h>

#define SCREEN_W 1280
#define SCREEN_H 720

// ====================================================================== MAIN FUNCTION ==============================================================================

int main(int argc, char** argv) {
    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the fiRSt connected controller)
    PadState pad;
    padInitializeDefault(&pad);

    //Get media files directory
    romfsInit();
    chdir("romfs:/");

    int exit_requested = 0; //variable to quit main loop

    //SDL objects to render the images
    SDL_Texture *switchPNG_tex = NULL, *background_tex = NULL, 
    *a_tex = NULL, *b_tex = NULL, *x_tex = NULL, *y_tex = NULL,
    *aD_tex = NULL, *aU_tex = NULL, *aL_tex = NULL, *aR_tex = NULL,
    *r_tex = NULL, *l_tex = NULL, *zR_tex = NULL, *zL_tex = NULL,
    *rSL_tex = NULL, *rSR_tex = NULL, *rSU_tex = NULL, *rSD_tex = NULL, *rSC_tex = NULL,
    *lSL_tex = NULL, *lSR_tex = NULL, *lSU_tex = NULL, *lSD_tex = NULL, *lSC_tex = NULL,
    *minus_tex = NULL, *plus_tex = NULL;

    //position of our images
    SDL_Rect default_pos = { 0, 0, 0, 0 }, center_pos = { 0, 0, 0, 0 };

    //SDL inits
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);

    //we define the window for sdl to draw
    SDL_Window* window = SDL_CreateWindow("buttonsTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

//============================== IMAGE PRELOAD ==============================

    //-------------- Background and nitendo switch --------------------
    SDL_Surface *background = IMG_Load("data/background.png");
    if (background) {
        default_pos.w = background->w;
        default_pos.h = background->h;
        background_tex = SDL_CreateTextureFromSurface(renderer, background);
        SDL_FreeSurface(background);
    }

    SDL_Surface *switchPNG = IMG_Load("data/switch.png");
    if (switchPNG) {
        center_pos.x = SCREEN_W / 2 - switchPNG->w / 3;
        center_pos.y = SCREEN_H / 2 - switchPNG->h / 3;
        center_pos.w = switchPNG->w/1.5;
        center_pos.h = switchPNG->h/1.5;
        switchPNG_tex = SDL_CreateTextureFromSurface(renderer, switchPNG);
        SDL_FreeSurface(switchPNG);
    }

    //------------------ ABXY ----------------------------------
    SDL_Surface *APNG = IMG_Load("data/A.png");
    if (APNG) {
        a_tex = SDL_CreateTextureFromSurface(renderer, APNG);
        SDL_FreeSurface(APNG);
    }

    SDL_Surface *BPNG = IMG_Load("data/B.png");
    if (BPNG) {
        b_tex = SDL_CreateTextureFromSurface(renderer, BPNG);
        SDL_FreeSurface(APNG);
    }

    SDL_Surface *XPNG = IMG_Load("data/X.png");
    if (XPNG) {
        x_tex = SDL_CreateTextureFromSurface(renderer, XPNG);
        SDL_FreeSurface(APNG);
    }

    SDL_Surface *YPNG = IMG_Load("data/Y.png");
    if (YPNG) {
        y_tex = SDL_CreateTextureFromSurface(renderer, YPNG);
        SDL_FreeSurface(APNG);
    }

    //------------------ ARROWS ----------------------------------
    SDL_Surface *ADPNG = IMG_Load("data/ARROW_DOWN.png");
    if (ADPNG) {
        aD_tex = SDL_CreateTextureFromSurface(renderer, ADPNG);
        SDL_FreeSurface(ADPNG);
    }

    SDL_Surface *AUPNG = IMG_Load("data/ARROW_UP.png");
    if (AUPNG) {
        aU_tex = SDL_CreateTextureFromSurface(renderer, AUPNG);
        SDL_FreeSurface(AUPNG);
    }

    SDL_Surface *ALPNG = IMG_Load("data/ARROW_LEFT.png");
    if (ADPNG) {
        aL_tex = SDL_CreateTextureFromSurface(renderer, ALPNG);
        SDL_FreeSurface(ALPNG);
    }

    SDL_Surface *ARPNG = IMG_Load("data/ARROW_RIGHT.png");
    if (ARPNG) {
        aR_tex = SDL_CreateTextureFromSurface(renderer, ARPNG);
        SDL_FreeSurface(ARPNG);
    }

    //------------------ TRIGGERS ----------------------------------
    SDL_Surface *RPNG = IMG_Load("data/R.png");
    if (RPNG) {
        r_tex = SDL_CreateTextureFromSurface(renderer, RPNG);
        SDL_FreeSurface(RPNG);
    }

    SDL_Surface *LPNG = IMG_Load("data/L.png");
    if (LPNG) {
        l_tex = SDL_CreateTextureFromSurface(renderer, LPNG);
        SDL_FreeSurface(LPNG);
    }

    SDL_Surface *ZRPNG = IMG_Load("data/ZR.png");
    if (ZRPNG) {
        zR_tex = SDL_CreateTextureFromSurface(renderer, ZRPNG);
        SDL_FreeSurface(ZRPNG);
    }

    SDL_Surface *ZLPNG = IMG_Load("data/ZL.png");
    if (LPNG) {
        zL_tex = SDL_CreateTextureFromSurface(renderer, ZLPNG);
        SDL_FreeSurface(ZLPNG);
    }

    //------------------ LEFT STICK ----------------------------------
    SDL_Surface *LSCPNG = IMG_Load("data/LSTICK_CLICK.png");
    if (LSCPNG) {
        lSC_tex = SDL_CreateTextureFromSurface(renderer, LSCPNG);
        SDL_FreeSurface(LSCPNG);
    }

    SDL_Surface *LSUPNG = IMG_Load("data/LSTICK_UP.png");
    if (LSUPNG) {
        lSU_tex = SDL_CreateTextureFromSurface(renderer, LSUPNG);
        SDL_FreeSurface(LSUPNG);
    }

    SDL_Surface *LSDPNG = IMG_Load("data/LSTICK_DOWN.png");
    if (LSDPNG) {
        lSD_tex = SDL_CreateTextureFromSurface(renderer, LSDPNG);
        SDL_FreeSurface(LSDPNG);
    }

    SDL_Surface *LSLPNG = IMG_Load("data/LSTICK_LEFT.png");
    if (LSLPNG) {
        lSL_tex = SDL_CreateTextureFromSurface(renderer, LSLPNG);
        SDL_FreeSurface(LSLPNG);
    }

    SDL_Surface *LSRPNG = IMG_Load("data/LSTICK_RIGHT.png");
    if (LSRPNG) {
        lSR_tex = SDL_CreateTextureFromSurface(renderer, LSRPNG);
        SDL_FreeSurface(LSRPNG);
    }

    //------------------ RIGHT STICK ----------------------------------
    SDL_Surface *RSCPNG = IMG_Load("data/RSTICK_CLICK.png");
    if (RSCPNG) {
        rSC_tex = SDL_CreateTextureFromSurface(renderer, RSCPNG);
        SDL_FreeSurface(RSCPNG);
    }

    SDL_Surface *RSUPNG = IMG_Load("data/RSTICK_UP.png");
    if (RSUPNG) {
        rSU_tex = SDL_CreateTextureFromSurface(renderer, RSUPNG);
        SDL_FreeSurface(RSUPNG);
    }

    SDL_Surface *RSDPNG = IMG_Load("data/RSTICK_DOWN.png");
    if (RSDPNG) {
        rSD_tex = SDL_CreateTextureFromSurface(renderer, RSDPNG);
        SDL_FreeSurface(RSDPNG);
    }

    SDL_Surface *RSLPNG = IMG_Load("data/RSTICK_LEFT.png");
    if (RSLPNG) {
        rSL_tex = SDL_CreateTextureFromSurface(renderer, RSLPNG);
        SDL_FreeSurface(RSLPNG);
    }

    SDL_Surface *RSRPNG = IMG_Load("data/RSTICK_RIGHT.png");
    if (RSRPNG) {
        rSR_tex = SDL_CreateTextureFromSurface(renderer, RSRPNG);
        SDL_FreeSurface(LSRPNG);
    }

    //------------------ PLUS & MINUS ----------------------------------
    SDL_Surface *MPNG = IMG_Load("data/MINUS.png");
    if (MPNG) {
        minus_tex = SDL_CreateTextureFromSurface(renderer, MPNG);
        SDL_FreeSurface(MPNG);
    }

    SDL_Surface *PPNG = IMG_Load("data/PLUS.png");
    if (PPNG) {
        plus_tex = SDL_CreateTextureFromSurface(renderer, PPNG);
        SDL_FreeSurface(PPNG);
    }

// ======================================================================= INFINITE LOOP ============================================================================
    // we loop through those lines until the user requests otherwise or the main loop ends
    while (!exit_requested
        && appletMainLoop()
        ) {
        
        //draw the background
        if (background_tex)
            SDL_RenderCopy(renderer, background_tex, NULL, &default_pos);

        // Scan the gamepad
        padUpdate(&pad);
        u64 kHeld = padGetButtons(&pad);

        // ======== ABXY Buttons ===========================
        if(kHeld&HidNpadButton_A){SDL_RenderCopy(renderer, a_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_B){SDL_RenderCopy(renderer, b_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_X){SDL_RenderCopy(renderer, x_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_Y){SDL_RenderCopy(renderer, y_tex, NULL, &center_pos);}
 
        // ========= Sticks ================================
        //---- stick pressed ------------
        if(kHeld&HidNpadButton_StickL){SDL_RenderCopy(renderer, lSC_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickR){SDL_RenderCopy(renderer, rSC_tex, NULL, &center_pos);}

        //------ left stick move ---------
        if(kHeld&HidNpadButton_StickLLeft){SDL_RenderCopy(renderer, lSL_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickLUp){SDL_RenderCopy(renderer, lSU_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickLRight){SDL_RenderCopy(renderer, lSR_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickLDown){SDL_RenderCopy(renderer, lSD_tex, NULL, &center_pos);}
        
        //------ right stick move ---------
        if(kHeld&HidNpadButton_StickRLeft){SDL_RenderCopy(renderer, rSL_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickRUp){SDL_RenderCopy(renderer, rSU_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickRRight){SDL_RenderCopy(renderer, rSR_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_StickRDown){SDL_RenderCopy(renderer, rSD_tex, NULL, &center_pos);}

        // ========= TriggeRS ==============================            
        if(kHeld&HidNpadButton_L){SDL_RenderCopy(renderer, l_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_R){SDL_RenderCopy(renderer, r_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_ZL){SDL_RenderCopy(renderer, zL_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_ZR){SDL_RenderCopy(renderer, zR_tex, NULL, &center_pos);}

        //========== Plus and Minus ========================
        if(kHeld&HidNpadButton_Plus){SDL_RenderCopy(renderer, plus_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_Minus){SDL_RenderCopy(renderer, minus_tex, NULL, &center_pos);}
        if((kHeld&HidNpadButton_Plus)&&(kHeld&HidNpadButton_Minus)){exit_requested = 1;}

        //========= Arrows =================================            
        if(kHeld&HidNpadButton_Left){SDL_RenderCopy(renderer, aL_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_Up){SDL_RenderCopy(renderer, aU_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_Right){SDL_RenderCopy(renderer, aR_tex, NULL, &center_pos);}
        if(kHeld&HidNpadButton_Down){SDL_RenderCopy(renderer, aD_tex, NULL, &center_pos);}

        if (switchPNG_tex) {
            SDL_RenderCopy(renderer, switchPNG_tex, NULL, &center_pos);
        }

        //render the screen with all objects previously chosen
        SDL_RenderPresent(renderer);
    }

    // clean up your textures when you are done with them
    if (background_tex)
        SDL_DestroyTexture(background_tex);

    if (switchPNG_tex)
        SDL_DestroyTexture(switchPNG_tex);

    // we end all applications current process
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}
