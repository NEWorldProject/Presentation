#include "Interactable.h"

namespace Presentation::UI {
    Interactable::Interactable() {
        if (auto evn = GetEventNode(); evn) {
            evn->Listen<TouchEnterEvent>([this](Element&, const TouchEvent& evt) { OnTouchEnter(evt.Info); });
            evn->Listen<TouchLeaveEvent>([this](Element&, const TouchEvent& evt) { OnTouchLeave(evt.Info); });
            evn->Listen<TouchDownEvent>([this](Element&, const TouchEvent& evt) { OnTouchDown(evt.Info); });
            evn->Listen<TouchMoveEvent>([this](Element&, const TouchEvent& evt) { OnTouchMove(evt.Info); });
            evn->Listen<TouchUpEvent>([this](Element&, const TouchEvent& evt) { OnTouchUp(evt.Info); });
            evn->Listen<KeyDownEvent>([this](Element&, const KeyEvent& evt) { OnKeyDown(evt.Key); });
            evn->Listen<KeyUpEvent>([this](Element&, const KeyEvent& evt) { OnKeyUp(evt.Key); });
            evn->Listen<KeyPressEvent>([this](Element&, const KeyEvent& evt) { OnKeyPress(evt.Key); });
            evn->Listen<TextInputEvent>([this](Element&, const TextInputEvent& evt) { OnTextInput(evt.Text); });
            evn->Listen<GainFocusEvent>([this](Element&, const MessageBase&) { OnGainFocus(); });
            evn->Listen<LoseFocusEvent>([this](Element&, const MessageBase&) { OnLoseFocus(); });
            evn->Listen<FileDropEvent>([this](Element&, const FileDropEvent& evt) { OnDropFile(evt.File); });
        }
    }

    void Interactable::OnTouchEnter(const TouchInfo& info) { }

    void Interactable::OnTouchLeave(const TouchInfo& info) { }

    void Interactable::OnTouchDown(const TouchInfo& info) { }

    void Interactable::OnTouchMove(const TouchInfo& info) { }

    void Interactable::OnTouchUp(const TouchInfo& info) { }

    void Interactable::OnKeyDown(int key) { }

    void Interactable::OnKeyUp(int key) { }

    void Interactable::OnKeyPress(int key) { }

    void Interactable::OnTextInput(const char* text) { }

    void Interactable::OnGainFocus() { }

    void Interactable::OnLoseFocus() { }

    void Interactable::OnDropFile(const filesystem::path& path) { }
}
