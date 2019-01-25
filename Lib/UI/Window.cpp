//
// Created by 刘予顺 on 2018/11/27.
//

#include "Window.h"
#include <SDL.h>

namespace Presentation::UI {
    namespace {
        SDL_Window* W(void* p) noexcept { return reinterpret_cast<SDL_Window*>(p); }

        int CWP(int wp) noexcept {
            switch (wp) {
            case Window::DoNotCare: return SDL_WINDOWPOS_UNDEFINED;
            case Window::Centered: return SDL_WINDOWPOS_CENTERED;
            default: return wp;
            }
        }

        uint32_t CFLG(uint32_t flags) noexcept {
            uint32_t ret = 0;
            #define A(V, P) if (flags & V) ret |= P;
            A(Window::CreateFullScreen, SDL_WINDOW_FULLSCREEN)
            A(Window::CreateShown, SDL_WINDOW_SHOWN)
            A(Window::CreateHidden, SDL_WINDOW_HIDDEN)
            A(Window::CreateBorderless, SDL_WINDOW_BORDERLESS)
            A(Window::CreateResizeable, SDL_WINDOW_RESIZABLE)
            A(Window::CreateMinimized, SDL_WINDOW_MINIMIZED)
            A(Window::CreateMaximized, SDL_WINDOW_MAXIMIZED)
            A(Window::CreateInputGrabbed, SDL_WINDOW_INPUT_GRABBED)
            A(Window::CreateInputFocus, SDL_WINDOW_INPUT_FOCUS)
            A(Window::CreateMouseFocus, SDL_WINDOW_MOUSE_FOCUS)
            A(Window::CreateFullScreenDesktop, SDL_WINDOW_FULLSCREEN_DESKTOP)
            A(Window::CreateAllowHighDpi, SDL_WINDOW_ALLOW_HIGHDPI)
            A(Window::CreateCapturemouse, SDL_WINDOW_MOUSE_CAPTURE)
            A(Window::CreateAlwaysonTop, SDL_WINDOW_ALWAYS_ON_TOP)
            A(Window::CreateSkipTaskbar, SDL_WINDOW_SKIP_TASKBAR)
            A(Window::CreateUtility, SDL_WINDOW_UTILITY)
            A(Window::CreateTooltip, SDL_WINDOW_TOOLTIP)
            A(Window::CreatePopupMenu, SDL_WINDOW_POPUP_MENU)
            #undef A
            return ret;
        }
    }

    Window::Window(const std::string& name, const AARect& rect, uint32_t flags):
            EventNode(EventCatalog::GetDefault()),
            _Handle(SDL_CreateWindow(name.c_str(), CWP(rect.Left), CWP(rect.Top), rect.Width, rect.Height,
                    CFLG(flags))) {
        if (!_Handle)
            throw SubSysFailure(SDL_GetError());
    }

    Point2D Window::GetPosition() noexcept {
        Point2D result{};
        SDL_GetWindowPosition(W(_Handle), &result.X, &result.Y);
        return result;
    }

    Point2D Window::GetSize() noexcept {
        Point2D result{};
        SDL_GetWindowSize(W(_Handle), &result.X, &result.Y);
        return result;
    }

    std::string Window::GetTitle() noexcept {
        return std::string(SDL_GetWindowTitle(W(_Handle)));
    }

    void Window::Hide() noexcept {
        SDL_HideWindow(W(_Handle));
    }

    void Window::Maximize() noexcept {
        SDL_MaximizeWindow(W(_Handle));
    }

    void Window::Minimize() noexcept {
        SDL_MinimizeWindow(W(_Handle));
    }

    void Window::Raise() noexcept {
        SDL_RaiseWindow(W(_Handle));
    }

    void Window::Restore() noexcept {
        SDL_RestoreWindow(W(_Handle));
    }

    void Window::SetFullscreen(bool enable) noexcept {
        SDL_SetWindowFullscreen(W(_Handle), enable ? SDL_WINDOW_FULLSCREEN : 0);
    }

    void Window::SetIcon() noexcept {

    }

    void Window::SetPosition(const Point2D& pt) noexcept {
        SDL_SetWindowPosition(W(_Handle), pt.X, pt.Y);
    }

    void Window::SetSize(const Point2D& size) noexcept {
        SDL_SetWindowSize(W(_Handle), size.X, size.Y);
    }

    void Window::SetBordered(bool bordered) noexcept {
        SDL_SetWindowBordered(W(_Handle), SDL_bool(bordered));
    }

    void Window::SetResizable(bool resizeable) noexcept {
        SDL_SetWindowResizable(W(_Handle), SDL_bool(resizeable));
    }

    void Window::SetTitle(const std::string& title) noexcept {
        SDL_SetWindowTitle(W(_Handle), title.c_str());
    }

    void Window::Show() noexcept {
        SDL_ShowWindow(W(_Handle));
    }

    Window::~Window() noexcept {
        if (_Handle) {
            SDL_DestroyWindow(W(_Handle));
            _Handle = nullptr;
        }
    }

    void Window::DoRender() {

    }
}
