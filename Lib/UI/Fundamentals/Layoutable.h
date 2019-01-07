#pragma once

#include <array>
#include "Element.h"
#include "Events.h"
#include "Math/Rect.h"
#include "Transform.h"

namespace Presentation::UI {
    enum class Anchor : int32_t {
        Left, Right, Top, Bottom
    };

    enum class AnchorType {
        Center, Align, Opposite
    };

    struct Margin {
        int Left, Right, Top, Bottom;
    };

    struct LayoutUpdateEvent : MessageBase { };

    class Layoutable : public virtual Element, protected TransformBase {
    public:
        Layoutable();

        void SetAnchor(Anchor anchor, AnchorType type, Layoutable& sibling) noexcept;

        const std::pair<AnchorType, Layoutable*> GetAnchor(Anchor anchor) const noexcept;

        void SetMargin(const Margin& margin) noexcept;

        Margin GetMargin() const noexcept;

        virtual Math::Rect Measure() const noexcept;
    protected:
        void CacheFlush() noexcept override;
        virtual void OnLayoutUpdate();
    private:
        Margin _Margin { 0, 0, 0, 0 };
        Transforms _Transforms;
        std::array<std::pair<AnchorType, Layoutable*>, 4> _Anchors;
        void MarkForLayoutUpdate();
    };

}