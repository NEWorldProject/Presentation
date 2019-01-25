#pragma once

#include <array>
#include "Element.h"
#include "Events.h"
#include "Math/AARect.h"
#include "Transform.h"

namespace Presentation::UI {
    enum class Anchor : int32_t {
        Left = 0, Right = 1, Top = 2, Bottom = 3
    };

    enum class AnchorType {
        None = 0, Center = 1, Align = 2, Opposite = 3
    };

    struct Margin {
        int Left, Right, Top, Bottom;
    };

    struct LayoutUpdateEvent : MessageBase { };

    struct CircularReferenceException : std::exception {
        const char* what() const noexcept override;
    };

    class BasicLayoutable : public TreeNode {
    public:
        BasicLayoutable();

        void SetAnchor(Anchor anchor, AnchorType type, BasicLayoutable& sibling) noexcept;

        const std::pair<AnchorType, BasicLayoutable*> GetAnchor(Anchor anchor) const noexcept;

        void SetMargin(const Margin& margin) noexcept;

        Margin GetMargin() const noexcept;

        virtual Math::AARect GetCurrentMinRect() const noexcept;

        virtual Math::AARect Measure();

        virtual Math::AARect Organize(const Math::AARect& available);
    protected:
        void MarkForLayoutUpdate();

        virtual void OnLayoutUpdate();

        void AddChildPartial(Element* element, TreeNode* newNode) noexcept override;
    private:
        // Procedural variables
        bool _In, _Out, _Dump;
        Math::AARect _Resolved;
        // Properties
        Margin _Margin;
        std::array<std::pair<AnchorType, BasicLayoutable*>, 4> _Anchors;
    };

    class TransformableLayoutable : public BasicLayoutable, virtual public Transformable, protected TransformHolder {
    public:
        TransformableLayoutable();

        Transforms& LayoutTransforms() noexcept { return _Transforms; }

        Math::AARect Measure() override;

        Math::AARect Organize(const Math::AARect& available) override;
    protected:
        void CacheFlush() noexcept override;
    private:
        Transforms _Transforms;
    };

}
