//
// Created by 刘予顺 on 2018/11/27.
//

#include <SDL.h>
#include "Application.h"

namespace Presentation {
    int __Compact() noexcept;

    void UI::Run() {
        bool quit = false;
        SDL_Event evt{};
        while (!quit) {
            while (SDL_WaitEvent(&evt)==1) {
                auto evtp = static_cast<SDL_EventType>(evt.type);
                switch (evtp) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_APP_TERMINATING:
                    break;
                case SDL_APP_LOWMEMORY:
                    __Compact();
                    break;
                case SDL_APP_WILLENTERBACKGROUND:break;
                case SDL_APP_DIDENTERBACKGROUND:break;
                case SDL_APP_WILLENTERFOREGROUND:break;
                case SDL_APP_DIDENTERFOREGROUND:break;
                case SDL_WINDOWEVENT:break;
                case SDL_SYSWMEVENT:break;
                case SDL_KEYDOWN:break;
                case SDL_KEYUP:break;
                case SDL_TEXTEDITING:break;
                case SDL_TEXTINPUT:break;
                case SDL_KEYMAPCHANGED:break;
                case SDL_MOUSEMOTION:break;
                case SDL_MOUSEBUTTONDOWN:break;
                case SDL_MOUSEBUTTONUP:break;
                case SDL_MOUSEWHEEL:break;
                case SDL_FINGERDOWN:break;
                case SDL_FINGERUP:break;
                case SDL_FINGERMOTION:break;
                case SDL_MULTIGESTURE:break;
                case SDL_CLIPBOARDUPDATE:break;
                case SDL_DROPFILE:break;
                case SDL_DROPTEXT:break;
                case SDL_DROPBEGIN:break;
                case SDL_DROPCOMPLETE:break;
                case SDL_AUDIODEVICEADDED:break;
                case SDL_AUDIODEVICEREMOVED:break;
                case SDL_RENDER_TARGETS_RESET:break;
                case SDL_RENDER_DEVICE_RESET:break;
                default: break;
                }
            }
        }
    }
}
