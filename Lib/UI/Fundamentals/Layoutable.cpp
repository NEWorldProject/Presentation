#include "Layoutable.h"
#include <stack>

namespace Presentation::UI {
    BasicLayoutable::BasicLayoutable()
            :TreeNode(this), _Resolved(0, 0), _Margin{0, 0, 0, 0}, _Anchors{{
            {AnchorType::None, nullptr},
            {AnchorType::None, nullptr},
            {AnchorType::None, nullptr},
            {AnchorType::None, nullptr}
    }} { }

    void BasicLayoutable::OnLayoutUpdate() {
        if (auto evn = GetEventNode(); evn) {
            LayoutUpdateEvent event{};
            evn->Cast<LayoutUpdateEvent>(event);
        }
    }

    const std::pair<AnchorType, BasicLayoutable*> BasicLayoutable::GetAnchor(Anchor anchor) const noexcept {
        return _Anchors[static_cast<int32_t>(anchor)];
    }

    void BasicLayoutable::SetAnchor(Anchor anchor, AnchorType type, BasicLayoutable& sibling) noexcept {
        _Anchors[static_cast<int32_t>(anchor)] = {type, std::addressof(sibling)};
    }

    Margin BasicLayoutable::GetMargin() const noexcept { return _Margin; }

    void BasicLayoutable::SetMargin(const Margin& margin) noexcept { _Margin = margin; }

    void BasicLayoutable::MarkForLayoutUpdate() {

    }

    Math::AARect BasicLayoutable::Measure() {
        struct TreeMeasure {
            explicit TreeMeasure(BasicLayoutable* root)
                    :_Root(root) {
                Init(*root);
                SearchAll(*root);
                ResolveAll();
            }

            Math::AARect Get() { return _Rect; }
        private:
            void Init(BasicLayoutable& root) noexcept {
                root._In = root._Out = true;
                for (auto iter = root.GetChildBegin(); iter!=nullptr; iter = iter->GetRight()) {
                    auto cl = reinterpret_cast<BasicLayoutable*>(iter->GetClass());
                    for (auto&[_, ach] : cl->_Anchors)
                        ach->_In = ach->_Out = ach->_Dump = true;
                }
            }

            void DFS(BasicLayoutable* node) {
                node->_In = true;
                for (const auto&[_, ach] : node->_Anchors)
                    if (ach) {
                        if (!TestAndVisit(ach))
                            ReferenceValidation(ach);
                        if (ach != _Root && ach->_Dump)
                            ach->_Dump = false;
                    }
                node->_Out = true;
                _ResolveList.push_back(node);
            }

            bool TestAndVisit(BasicLayoutable* node) {
                if (!(node->_In)) {
                    DFS(node);
                    return true;
                }
                return false;
            }

            void ResolveNode(BasicLayoutable* node) {
                // resolve the current sub-node
                auto rect = node->Measure(); // Get the base size rect
                // position it with layout anchors
                const auto&[left, right, top, bottom] = node->_Anchors;
                if (left.second && left.second!=_Root)
                    rect.Left = AnchorLeft(left.second->_Resolved, left.first);
                rect.Left += node->_Margin.Left;
                if (top.second && top.second!=_Root)
                    rect.Top = AnchorTop(top.second->_Resolved, top.first);
                rect.Top += node->_Margin.Top;
                if (right.second && right.second!=_Root)
                    rect.Include(AnchorRight(right.second->_Resolved, right.first)-node->_Margin.Right, rect.Top);
                if (bottom.second && left.second!=_Root)
                    rect.Include(rect.Left, AnchorBottom(bottom.second->_Resolved, bottom.first)-node->_Margin.Bottom);
            }

            void ResolveAll() {
                for (auto& x : _ResolveList) {
                    ResolveNode(x);
                    if (x->_Dump)
                        _Rect.Merge(x->_Resolved.Move(-x->_Resolved.Echo()));
                }
            }

            static int AnchorTop(Math::AARect& rect, AnchorType anchor) noexcept {
                switch (anchor) {
                case AnchorType::None: return 0;
                case AnchorType::Center: return rect.Top+rect.Height/2;
                case AnchorType::Align: return rect.Top;
                case AnchorType::Opposite: return rect.Top+rect.Height;
                }
            }

            static int AnchorBottom(Math::AARect& rect, AnchorType anchor) noexcept {
                switch (anchor) {
                case AnchorType::None: return 0;
                case AnchorType::Center: return rect.Top+rect.Height/2;
                case AnchorType::Align: return rect.Top+rect.Height;
                case AnchorType::Opposite: return rect.Top;
                }
            }

            static int AnchorLeft(Math::AARect& rect, AnchorType anchor) noexcept {
                switch (anchor) {
                case AnchorType::None: return 0;
                case AnchorType::Center: return rect.Left+rect.Width/2;
                case AnchorType::Align: return rect.Left;
                case AnchorType::Opposite: return rect.Left+rect.Width;
                }
            }

            static int AnchorRight(Math::AARect& rect, AnchorType anchor) noexcept {
                switch (anchor) {
                case AnchorType::None: return 0;
                case AnchorType::Center: return rect.Left+rect.Width/2;
                case AnchorType::Align: return rect.Left+rect.Width;
                case AnchorType::Opposite: return rect.Left;
                }
            }

            static void ReferenceValidation(BasicLayoutable* node) {
                // some explanations: if _Out is not set, then the node is part of the parent tree which depends on the
                // working node, which means there is a circular reference which is definitely a design error. If the
                // _Out is set, the node will bw a node from another part of the tree, which is perfectly valid
                //
                // normally if this is only meant to be used hard-coded, it would be fine to just assert and crash.
                // but as we might implement a XML (or whatever) loader later, I think it would be better to be able to
                // report this to the loader rather than just crashing so users might get a chance to see what is wrong.
                // but it should be noted that this is a program bug report mechanism an users should never even try to
                // recover form this exception
                if (!node->_Out)
                    throw CircularReferenceException();
            }

            void SearchAll(BasicLayoutable& root) {
                for (auto iter = root.GetChildBegin(); iter!=nullptr; iter = iter->GetRight())
                    TestAndVisit(reinterpret_cast<BasicLayoutable*>(iter->GetClass()));
            }

            BasicLayoutable* _Root;
            Math::AARect _Rect{0, 0};
            std::vector<BasicLayoutable*> _ResolveList;
        };

        return GetCurrentMinRect().Merge(TreeMeasure(this).Get());
    }

    void BasicLayoutable::AddChildPartial(Element* element, TreeNode* newNode) noexcept {
        MarkForLayoutUpdate();
        TreeNode::AddChildPartial(element, newNode);
    }

    Math::AARect BasicLayoutable::Organize(const Math::AARect& available) {
        auto ret = Math::AARect(0, 0);
        for (auto iter = GetChildBegin(); iter!=nullptr; iter = iter->GetRight())
            ret.Merge(reinterpret_cast<BasicLayoutable*>(iter->GetClass())->Organize(available));
        return ret;
    }

    Math::AARect BasicLayoutable::GetCurrentMinRect() const noexcept { return Math::AARect(0, 0); }

    TransformableLayoutable::TransformableLayoutable() { Content(_Transforms); }

    void TransformableLayoutable::CacheFlush() noexcept { MarkForLayoutUpdate(); }

    Math::AARect TransformableLayoutable::Measure() {
        auto rect = BasicLayoutable::Measure();
        rect.Move(-rect.Echo()-(rect.Size()/2));
        const auto p0 = rect.Echo();
        const auto p1 = rect.Echo()+rect.Size();
        const auto t0 = _Transforms.ApplyMatrix(Math::Vec3D(p0.X, p0.Y, 0.0));
        const auto t1 = _Transforms.ApplyMatrix(Math::Vec3D(p1.X, p1.Y, 0));
        const auto t2 = _Transforms.ApplyMatrix(Math::Vec3D(p0.X, p1.Y, 0.0));
        const auto t3 = _Transforms.ApplyMatrix(Math::Vec3D(p1.X, p0.Y, 0));
        auto ret = Math::AARect(0, 0);
        ret.Include(Math::Vec2I(t0.X, t0.Y)).Include(Math::Vec2I(t1.X, t1.Y)).Include(Math::Vec2I(t2.X, t2.Y))
                .Include(Math::Vec2I(t3.X, t3.Y));
        return ret.Move(-ret.Echo());
    }

    Math::AARect TransformableLayoutable::Organize(const Math::AARect& available) {
        auto rect = available;
        rect.Move(-rect.Echo()-(rect.Size()/2));
        const auto p0 = rect.Echo();
        const auto p1 = rect.Echo()+rect.Size();
        const auto t0 = _Transforms.ApplyReverse(Math::Vec3D(p0.X, p0.Y, 0.0));
        const auto t1 = _Transforms.ApplyReverse(Math::Vec3D(p1.X, p1.Y, 0));
        const auto t2 = _Transforms.ApplyReverse(Math::Vec3D(p0.X, p1.Y, 0.0));
        const auto t3 = _Transforms.ApplyReverse(Math::Vec3D(p1.X, p0.Y, 0));
        // Try to expand by X-axis
        // Try to expand by Y-axis
        return BasicLayoutable::Organize(available);
    }

    const char* CircularReferenceException::what() const noexcept { return "Circular reference in anchor settings"; }
}
