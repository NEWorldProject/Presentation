#pragma once
#include <string>
#include <typeindex>
#include "Core/Intrusive.h"

namespace Presentation::UI {
    class EventNode;

    class Element : public IntrusiveVTBase {
    public:
        struct Identifier {
            uint64_t Iuid = 0;
            std::string Name;
        };

        Element();

        explicit Element(const Identifier& id);

        Element(const Element&) = delete;

        Element& operator=(const Element&) = delete;

        Element(Element&&) = delete;

        Element& operator=(Element&&) = delete;

        auto& GetName() const noexcept { return _Id.Name; }

        auto GetIuid() const noexcept { return _Id.Iuid; }
    protected:
        virtual EventNode* const GetEventNode() const noexcept;

        void AddChildBase(Element* element) noexcept;

        intptr_t GetTypeInfo() const noexcept { return _TypeInfo; }

        intptr_t GetBaseAddress() const noexcept { return reinterpret_cast<intptr_t>(this); }

        intptr_t ComputeOffset(intptr_t subclass) const noexcept { return subclass-GetBaseAddress(); }
    private:
        Identifier _Id;
        intptr_t _TypeInfo;
    };

    class TreeNode : public virtual Element {
    public:
        using PTreeNode = TreeNode*;
        PTreeNode GetLeft() const noexcept { return _Left; }
        PTreeNode GetRight() const noexcept { return _Right; }
        PTreeNode GetParent() const noexcept { return _Parent; }
        PTreeNode GetChildBegin() const noexcept { return _CBegin; }
        PTreeNode GetChildLast() const noexcept { return _CLast; }
        intptr_t GetClass() const noexcept { return _Class; }
    protected:
        template <class T>
        explicit TreeNode(T* ptr)
                :TreeNode(std::type_index(typeid(T)), reinterpret_cast<intptr_t>(ptr)) { }

        virtual void AddChildPartial(Element* element, TreeNode* target_node) noexcept;
    private:
        explicit TreeNode(const std::type_index& index, intptr_t ptr);
        friend class Element;
        PTreeNode _Parent, _Left, _Right, _CBegin, _CLast;
        const intptr_t _Class;
    };
}