#pragma once

#include "Base.h"
#include "Events.h"
#include "Element.h"
#include "Core/Filesystem.h"

namespace Presentation::UI {
    struct TouchInfo {
        int TUId {};
    private:
        Point2D _Array[64];
        std::atomic_uint8_t _Tail, _Head;
    };

    struct TouchEvent : MessageBase { TouchInfo Info; };

    struct TouchEnterEvent : TouchEvent { };

    struct TouchLeaveEvent : TouchEvent { };

    struct TouchDownEvent : TouchEvent { };

    struct TouchMoveEvent : TouchEvent { };

    struct TouchUpEvent : TouchEvent { };

    struct KeyEvent : MessageBase { int Key = 0; };

    struct KeyDownEvent : KeyEvent { };

    struct KeyUpEvent : KeyEvent { };

    struct KeyPressEvent : KeyEvent { };

    struct FileDropEvent : MessageBase { filesystem::path File; };

    struct FocusEvent : MessageBase { };

    struct GainFocusEvent : FocusEvent { };

    struct LoseFocusEvent : FocusEvent { };

    struct TextInputEvent : MessageBase { const char* Text{}; };

    class Interactable : public virtual Element {
    public:
        Interactable();
    protected:
        virtual void OnTouchEnter(const TouchInfo&);

        virtual void OnTouchLeave(const TouchInfo&);

        virtual void OnTouchDown(const TouchInfo&);

        virtual void OnTouchMove(const TouchInfo&);

        virtual void OnTouchUp(const TouchInfo&);

        virtual void OnKeyDown(int key);

        virtual void OnKeyUp(int key);

        virtual void OnKeyPress(int key);

        virtual void OnTextInput(const char* text);

        virtual void OnGainFocus();

        virtual void OnLoseFocus();

        virtual void OnDropFile(const filesystem::path& path);
    };
}