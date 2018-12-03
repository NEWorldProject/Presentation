#pragma once

#include <cstdint>
#include <string>
#include "Core/Filesystem.h"
#include "Core/Intrusive.h"
#include "Common.h"

namespace Presentation::UI {
    class Element : public IntrusiveVTBase {
    public:
        struct Identifier {
            uint64_t Iuid = 0;
            std::string Name;
        };

        Element() = default;

        explicit Element(const Identifier& id);

        Element(const Element&) = delete;

        Element& operator=(const Element&) = delete;

        Element(Element&&) = delete;

        Element& operator=(Element&&) = delete;

        auto& GetName() const noexcept { return _Id.Name; }

        auto GetIuid() const noexcept { return _Id.Iuid; }
    private:
        Identifier _Id;
    };

    class Collection : public virtual Element {

    };

    template <class T>
    class CollectionOver : public virtual Collection {

    };

    class LayoutElement : public virtual Element {
    public:
        virtual void OnLayoutUpdate();

        Signal<void(Element*)>& LayoutUpdate() noexcept { return _LayoutUpdate; }
    private:
        Signal<void(Element*)> _LayoutUpdate;
    };

    class LayoutCollection : public LayoutElement, public CollectionOver<LayoutElement> {

    };

    class Renderable : public virtual Element {
    public:
        using RenderEvent = Signal<void(Element*)>;
        
        virtual void Render();

        virtual void OnBeforeRender();

        virtual void OnAfterRender();

        RenderEvent& BeforeRender() noexcept { return _PreRender; }

        RenderEvent& AfterRender() noexcept { return _PostRender; }
    private:
        virtual void DoRender() = 0;

        RenderEvent _PreRender, _PostRender;
    };

    class RenderableCollection : public Renderable, public CollectionOver<Renderable> {

    };

    struct TouchInfo {

    };

    class UIResponder : public virtual Element {
    public:
        using TouchEvent = Signal<void(Element*, const TouchInfo&)>;

        using KeyEvent = Signal<void(Element*, int)>;

        using TextEvent = Signal<void(Element*, const char*)>;

        using FocusEvent = Signal<void(Element*)>;

        using FileDropEvent = Signal<void(Element*, filesystem::path)>;

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

        TouchEvent& TouchEnter() noexcept { return _TouchEnter; }
        
        TouchEvent& TouchLeave() noexcept { return _TouchLeave; }
        
        TouchEvent& TouchDown() noexcept { return _TouchDown; }
        
        TouchEvent& TouchMove() noexcept { return _TouchMove; }
        
        TouchEvent& TouchUp() noexcept { return _TouchUp; }

        KeyEvent& KeyDown() noexcept { return _KeyDown; }

        KeyEvent& KeyUp() noexcept { return _KeyUp; }

        KeyEvent& KeyPress() noexcept { return _KeyPress; }

        TextEvent& TextInput() noexcept { return _TextInput; }

        FocusEvent& GainFocus() noexcept { return _GainFocus; }

        FocusEvent& LoseFocus() noexcept { return _LoseFocus; }

        FileDropEvent& FileDrop() noexcept { return _FileDrop; }
    private:
        TouchEvent _TouchEnter, _TouchLeave, _TouchDown, _TouchMove, _TouchUp;

        KeyEvent _KeyDown, _KeyUp, _KeyPress;

        Signal<void(Element*, const char*)> _TextInput;

        Signal<void(Element*)> _GainFocus, _LoseFocus;

        Signal<void(Element*, filesystem::path)> _FileDrop;
    };

    class UIElement : public Renderable, public LayoutElement, public UIResponder {

    };

    class UIContainerElement : public UIElement {
    public:
        void OnLayoutUpdate() override;
        void Render() override;
        void OnTouchEnter(const TouchInfo& info) override;
        void OnTouchLeave(const TouchInfo& info) override;
        void OnTouchDown(const TouchInfo& info) override;
        void OnTouchMove(const TouchInfo& info) override;
        void OnTouchUp(const TouchInfo& info) override;
        void OnKeyDown(int key) override;
        void OnKeyUp(int key) override;
        void OnKeyPress(int key) override;
        void OnTextInput(const char* text) override;
        void OnGainFocus() override;
        void OnLoseFocus() override;
        void OnDropFile(const filesystem::path& path) override;
    };

    class UICollectionElement : public RenderableCollection, public LayoutCollection, public UIResponder {

    };
}