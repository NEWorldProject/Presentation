#pragma once

#include "Base.h"
#include "Exceptions.h"
#include "Core/Delegate.h"
#include "Core/Intrusive.h"
#include "Core/Filesystem.h"
#include <string>
#include <vector>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <unordered_map>

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

    class EventCatalog {
    public:
        using TypeInfoRef = std::reference_wrapper<const std::type_info>;

        template <template <class T> class ContT>
        EventCatalog(const EventCatalog& extends, const ContT<TypeInfoRef>& cont)
                : _CheckTable(extends._CheckTable), _Names(extends._Names) {
            for (const auto& node : cont) {
                _Names.insert_or_assign(_CheckTable.size(), node);
                _CheckTable.push_back(node);
            }
        }

        template <template <class T> class ContT>
        explicit EventCatalog(const ContT<TypeInfoRef>& cont)
                : _CheckTable{}, _Names{} {
            for (const auto& node : cont) {
                _Names.insert_or_assign(node, std::make_pair(this, _CheckTable.size()));
                _CheckTable.push_back(this);
            }
        }

        template <class ...Ts>
        static EventCatalog Create() {
            return EventCatalog(std::initializer_list<TypeInfoRef>{TypeInfoRef(typeid(Ts))...});
        }

        auto Count() const noexcept { return _Names.size(); }

        auto Search(const TypeInfoRef& type) const noexcept {
            if (auto res = _Names.find(type); res!=_Names.end())
                return std::make_tuple(true, res->second.first, res->second.second);
            else
                return std::make_tuple(false, (const EventCatalog*) (nullptr), 0);
        }

        bool Check(const std::pair<const EventCatalog*, int>& info) const noexcept {
            if (info.second<_CheckTable.size())
                return info.first==_CheckTable[info.second];
            return false;
        }
    private:
        struct Hash {
            std::size_t operator()(TypeInfoRef code) const noexcept {
                return code.get().hash_code();
            }
        };

        struct EqualTo {
            bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const noexcept {
                return lhs.get()==rhs.get();
            }
        };

        std::vector<const EventCatalog*> _CheckTable;
        std::unordered_map<TypeInfoRef, std::pair<const EventCatalog*, int>, Hash, EqualTo> _Names;
    };

    class MessageBase {
        friend class EventNode;
    private:
        std::pair<const EventCatalog*, int> _CastInfo;
    };

    class EventNode : public virtual Element {
        template <class Message>
        using CheckMessage = std::enable_if<std::is_convertible_v<Message*, MessageBase*>>;
    public:
        EventNode();

        explicit EventNode(const EventCatalog& catalog);

        template <class MessageType, class Func, class = CheckMessage<MessageType>>
        Connection Listen(Func&& function) {
            if (const auto[found, _, Id] = _Catalog->Search(typeid(MessageType)); found)
                return _Signals[Id].ConnectUnsafe<MessageType>(std::forward<std::decay_t<Func>>(function));
            return Connection();
        }

        template <class MessageType, class = CheckMessage<MessageType>>
        void Cast(MessageType& message) {
            if (const auto[found, catalog, Id] = _Catalog->Search(typeid(MessageType)); found) {
                message._CastInfo = std::make_pair(catalog, Id);
                _Signals[Id].CastUnsafe<MessageType>(*this, message);
            }
        }

        template <class MessageType, class = CheckMessage<MessageType>>
        void Recast(MessageType& message) {
            if (_Catalog->Check(message._CastInfo))
                _Signals[message._CastInfo.second].template CastUnsafe<MessageType>(*this, message);
            else
                Cast(message);
        }
    private:
        const EventCatalog* _Catalog;
        std::unique_ptr<GenericSignal<Element>[]> _Signals;
    };

    class Collection : public virtual Element {

    };

    template <class T>
    class CollectionOver : public virtual Collection {

    };

    struct LayoutUpdateEvent : MessageBase { };

    class LayoutElement : public virtual EventNode {
    public:
        virtual void OnLayoutUpdate();
    };

    class LayoutCollection : public LayoutElement, public CollectionOver<LayoutElement> {

    };

    struct BeforeRenderEvent : MessageBase { };

    struct AfterRenderEvent : MessageBase { };

    class Renderable : public virtual EventNode {
    public:
        virtual void Render();

        virtual void OnBeforeRender();

        virtual void OnAfterRender();
    private:
        virtual void DoRender() = 0;
    };

    class RenderableCollection : public Renderable, public CollectionOver<Renderable> {

    };

    struct TouchInfo {

    };

    struct TouchEvent : MessageBase { TouchInfo Info; };

    struct TouchEnterEvent : TouchEvent { };

    struct TouchLeaveEvent : TouchEvent { };

    struct TouchDownEvent : TouchEvent { };

    struct TouchMoveEvent : TouchEvent { };

    struct TouchUpEvent : TouchEvent { };

    struct KeyEvent : MessageBase { int Key = 0; };

    struct KeyDownEvent : KeyEvent { };

    struct KeyUpEvent : KeyEvent { };

    struct KeyPressEvent : KeyEvent { };

    struct FileDropEvent : MessageBase { filesystem::path File; };

    struct FocusEvent : MessageBase { };

    struct GainFocusEvent : FocusEvent { };

    struct LoseFocusEvent : FocusEvent { };

    struct TextInputEvent : MessageBase { const char* Text{}; };

    class UIResponder : public virtual EventNode {
    public:
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
    };

    class UIElement : public Renderable, public LayoutElement, public UIResponder {

    };

    class UIContainerElement : public UIElement {
    public:
    };

    class UICollectionElement : public RenderableCollection, public LayoutCollection, public UIResponder {

    };
}