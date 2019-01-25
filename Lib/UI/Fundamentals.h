#pragma once

#include "Base.h"
#include "Exceptions.h"
#include "Core/Intrusive.h"
#include "Fundamentals/Element.h"
#include "UI/Fundamentals/Layoutable.h"
#include "Fundamentals/Renderable.h"
#include "Fundamentals/Interactable.h"

namespace Presentation::UI {
    class UIElement : public Renderable, public BasicLayoutable, public Interactable { };

    class UIContainerElement : public UIElement {
    public:
        auto& GetContent() const noexcept { return _Content; }

        void SetContent(IntrusivePtr<UIElement> element) noexcept { _Content = std::move(element); }
    private:
        IntrusivePtr<UIElement> _Content {};
    };
}