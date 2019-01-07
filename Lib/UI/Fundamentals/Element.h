#pragma once
#include <string>
#include <typeindex>
#include "Core/Intrusive.h"

namespace Presentation::UI {
    class CapabliltyDescriptorBase {

    };

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

        intptr_t GetCurrentAddress() const noexcept { return reinterpret_cast<intptr_t>(this);}

        intptr_t ComputeOffset(intptr_t subclass) const noexcept { return subclass-GetCurrentAddress(); }
    private:
        Identifier _Id;
        intptr_t _TypeInfo;
        Element* _Parent = nullptr;
    };

    class TreeNode : public virtual Element {
    protected:
        template <class T>
        TreeNode() : TreeNode(std::type_index(typeid(T))) {}

        virtual void AddChildPartial(Element* element, intptr_t target_node) noexcept = 0;
    private:
        friend class Element;

        explicit TreeNode(const std::type_index& index);
    };
}