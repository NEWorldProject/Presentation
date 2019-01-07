#pragma once

#include "Base.h"
#include "Exceptions.h"
#include "Core/Intrusive.h"
#include "Fundamentals/Element.h"
#include "Fundamentals/Events.h"

namespace Presentation::UI {
    class Collection : public virtual Element {

    };

    template <class T>
    class CollectionOver : public virtual Collection {

    };

    class LayoutCollection : public LayoutElement, public CollectionOver<LayoutElement> {

    };

    class RenderableCollection : public Renderable, public CollectionOver<Renderable> {

    };

    class UIElement : public Renderable, public LayoutElement, public Interactable { };

    class UIContainerElement : public UIElement {
    public:
        auto& GetContent() const noexcept { return _Content; }

        void SetContent(IntrusivePtr<UIElement> element) noexcept { _Content = std::move(element); }
    private:
        IntrusivePtr<UIElement> _Content {};
    };

    class UICollectionElement : public RenderableCollection, public LayoutCollection, public Interactable {

    };
}