#include "Element.h"
#include <mutex>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <unordered_map>

namespace Presentation::UI {
    namespace {
        // This is the raii type system of UI components. Features lazy type registration
        // We only consider the AddChildPartial function and the tree node type index here,
        // as it is the only function in this scenario which needs extra info upon execution
        // since we cannot automatically wire up all these functions by inheritance statically

        struct ChainBlock {
            ChainBlock(const std::type_index& idx, intptr_t offset) noexcept
                    :Index(idx), Offset(offset) { }

            std::type_index Index;
            // This will be the offset to TreeNode type, which will have a virtual function to do further wiring
            intptr_t Offset;

            bool operator<(const ChainBlock& r) const noexcept { return Index<r.Index; }

            bool operator>(const ChainBlock& r) const noexcept { return Index>r.Index; }

            bool operator<=(const ChainBlock& r) const noexcept { return Index<=r.Index; }

            bool operator>=(const ChainBlock& r) const noexcept { return Index>=r.Index; }

            bool operator==(const ChainBlock& r) const noexcept { return Index==r.Index; }

            bool operator!=(const ChainBlock& r) const noexcept { return Index!=r.Index; }
        };

        struct TypeRegistry {
            void Load() noexcept {
                std::call_once(_Once, [this]() noexcept {
                    std::sort(Blocks.begin(), Blocks.end());
                    Lock = true;
                });
            }
            std::atomic_bool Lock{false};
            std::vector<ChainBlock> Blocks;
        private:
            std::once_flag _Once;
        };

        std::unordered_map<std::type_index, TypeRegistry> _Registry;

        TypeRegistry* CheckType(const std::type_info& type) {
            if (auto result = _Registry.find(std::type_index(type)); result!=_Registry.end()) {
                result->second.Load();
                return &result->second;
            }
            else
                return &(_Registry.try_emplace(std::type_index(type)).first->second);
        }
    }

    Element::Element()
            :_TypeInfo(reinterpret_cast<intptr_t>(CheckType(typeid((*this))))) { }

    Element::Element(const Element::Identifier& id)
            :_Id(id) { }

    EventNode* const Element::GetEventNode() const noexcept { return nullptr; }

    void Element::AddChildBase(Element* element) noexcept {
        // Hook Up All Tree Nodes
        auto reg_this = reinterpret_cast<TypeRegistry*>(GetTypeInfo());
        auto reg_target = reinterpret_cast<TypeRegistry*>(element->GetTypeInfo());
        reg_this->Load();
        reg_target->Load();
        decltype(auto) _this = reg_this->Blocks.begin(), _other = reg_target->Blocks.begin();
        for (; _this!=reg_this->Blocks.end(); ++_this) {
            for (; *_other<*_this; ++_other);
            if (*_other==*_this) {
                auto _this_node = reinterpret_cast<TreeNode*>(GetBaseAddress()+_this->Offset);
                _this_node->AddChildPartial(element, reinterpret_cast<TreeNode*>(element->GetBaseAddress()+_other->Offset));
            }
        }
    }

    TreeNode::TreeNode(const std::type_index& index, intptr_t ptr)
            :_Parent(nullptr), _Left(nullptr), _Right(nullptr), _CBegin(nullptr), _CLast(nullptr), _Class(ptr) {
        if (auto reg = reinterpret_cast<TypeRegistry*>(GetTypeInfo()); !reg->Lock)
            reg->Blocks.emplace_back(index, ComputeOffset(reinterpret_cast<intptr_t>(this)));
    }

    void TreeNode::AddChildPartial(Element* element, TreeNode* target_node) noexcept {
        if (_CBegin == nullptr) {
            _CBegin = _CLast = target_node;
        }
        else {
            _CLast->_Right = target_node;
            target_node->_Left = _CLast;
            _CLast = target_node;
        }
        target_node->_Parent = this;
    }

}
