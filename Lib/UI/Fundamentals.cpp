//
// Created by 刘予顺 on 2018/11/29.
//

#include "Fundamentals.h"
namespace Presentation::UI {
    Element::Element(const Element::Identifier& id)
            :_Id(id) { }

    void Renderable::Render() {
        OnBeforeRender();
        DoRender();
        OnAfterRender();
    }

    void Renderable::OnBeforeRender() { _PreRender(this); }

    void Renderable::OnAfterRender() { _PreRender(this); }

    void LayoutElement::OnLayoutUpdate() { _LayoutUpdate(this); }

    void UIResponder::OnTouchEnter(const TouchInfo& info) { _TouchEnter(this, info); }

    void UIResponder::OnTouchLeave(const TouchInfo& info) { _TouchLeave(this, info); }

    void UIResponder::OnTouchDown(const TouchInfo& info) { _TouchDown(this, info); }

    void UIResponder::OnTouchMove(const TouchInfo& info) { _TouchMove(this, info); }

    void UIResponder::OnTouchUp(const TouchInfo& info) { _TouchUp(this, info); }

    void UIResponder::OnKeyDown(int key) { _KeyDown(this, key); }

    void UIResponder::OnKeyUp(int key) { _KeyUp(this, key); }

    void UIResponder::OnKeyPress(int key) { _KeyPress(this, key); }

    void UIResponder::OnTextInput(const char* text) { _TextInput(this, text); }

    void UIResponder::OnGainFocus() { _GainFocus(this); }

    void UIResponder::OnLoseFocus() { _LoseFocus(this); }

    void UIResponder::OnDropFile(const filesystem::path& path) { _FileDrop(this, path); }

    void UIContainerElement::OnLayoutUpdate() {
        LayoutElement::OnLayoutUpdate();
    }

    void UIContainerElement::Render() {
        Renderable::Render();
    }

    void UIContainerElement::OnTouchEnter(const TouchInfo& info) {
        UIResponder::OnTouchEnter(info);
    }

    void UIContainerElement::OnTouchLeave(const TouchInfo& info) {
        UIResponder::OnTouchLeave(info);
    }

    void UIContainerElement::OnTouchDown(const TouchInfo& info) {
        UIResponder::OnTouchDown(info);
    }

    void UIContainerElement::OnTouchMove(const TouchInfo& info) {
        UIResponder::OnTouchMove(info);
    }

    void UIContainerElement::OnTouchUp(const TouchInfo& info) {
        UIResponder::OnTouchUp(info);
    }

    void UIContainerElement::OnKeyDown(int key) {
        UIResponder::OnKeyDown(key);
    }

    void UIContainerElement::OnKeyUp(int key) {
        UIResponder::OnKeyUp(key);
    }

    void UIContainerElement::OnKeyPress(int key) {
        UIResponder::OnKeyPress(key);
    }

    void UIContainerElement::OnTextInput(const char* text) {
        UIResponder::OnTextInput(text);
    }

    void UIContainerElement::OnGainFocus() {
        UIResponder::OnGainFocus();
    }

    void UIContainerElement::OnLoseFocus() {
        UIResponder::OnLoseFocus();
    }

    void UIContainerElement::OnDropFile(const filesystem::path& path) {
        UIResponder::OnDropFile(path);
    }
}
