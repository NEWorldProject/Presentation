//
// Created by 刘予顺 on 2018/11/29.
//

#include "Fundamentals.h"

namespace Presentation::UI {
    namespace {
        auto Catalog0 = EventCatalog::Create<
                // Layout Event
                LayoutUpdateEvent,
                // Render Events
                BeforeRenderEvent,
                AfterRenderEvent,
                // UI Responder Events
                TouchEnterEvent,
                TouchLeaveEvent,
                TouchDownEvent,
                TouchMoveEvent,
                TouchUpEvent,
                KeyDownEvent,
                KeyUpEvent,
                KeyPressEvent,
                FileDropEvent,
                FocusEvent,
                GainFocusEvent,
                LoseFocusEvent,
                TextInputEvent
        >();
    }

    Element::Element(const Element::Identifier& id)
            :_Id(id) { }

    EventNode::EventNode(const EventCatalog& catalog)
            :_Catalog(std::addressof(catalog)), _Signals(std::make_unique<GenericSignal<Element>[]>(catalog.Count())) {
    }

    EventNode::EventNode() : EventNode(Catalog0) { }

    void Renderable::Render() {
        OnBeforeRender();
        DoRender();
        OnAfterRender();
    }

    void Renderable::OnBeforeRender() { }

    void Renderable::OnAfterRender() { }

    void LayoutElement::OnLayoutUpdate() { }

    void UIResponder::OnTouchEnter(const TouchInfo& info) { }

    void UIResponder::OnTouchLeave(const TouchInfo& info) { }

    void UIResponder::OnTouchDown(const TouchInfo& info) { }

    void UIResponder::OnTouchMove(const TouchInfo& info) { }

    void UIResponder::OnTouchUp(const TouchInfo& info) { }

    void UIResponder::OnKeyDown(int key) { }

    void UIResponder::OnKeyUp(int key) { }

    void UIResponder::OnKeyPress(int key) { }

    void UIResponder::OnTextInput(const char* text) { }

    void UIResponder::OnGainFocus() { }

    void UIResponder::OnLoseFocus() { }

    void UIResponder::OnDropFile(const filesystem::path& path) { }
}
