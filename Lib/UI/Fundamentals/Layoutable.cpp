#include "Layoutable.h"

namespace Presentation::UI {
    Layoutable::Layoutable() = default;

    void Layoutable::OnLayoutUpdate() {
        if (auto evn = GetEventNode(); evn) {
            LayoutUpdateEvent event{};
            evn->Cast<LayoutUpdateEvent>(event);
        }
    }

    const std::pair<AnchorType, Layoutable*> Layoutable::GetAnchor(Anchor anchor) const noexcept {
        return _Anchors[static_cast<int32_t>(anchor)];
    }

    void Layoutable::SetAnchor(Anchor anchor, AnchorType type, Layoutable& sibling) noexcept {
        _Anchors[static_cast<int32_t>(anchor)] = { type, std::addressof(sibling) };
    }

    Margin Layoutable::GetMargin() const noexcept { return _Margin; }

    void Layoutable::SetMargin(const Margin& margin) noexcept { _Margin = margin; }

    void Layoutable::CacheFlush() noexcept { MarkForLayoutUpdate(); }

    void Layoutable::MarkForLayoutUpdate() {

    }

    Math::Rect Layoutable::Measure() const noexcept {
        return Math::Rect();
    }
}
