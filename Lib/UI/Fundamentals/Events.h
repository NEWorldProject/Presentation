#pragma once

#include <tuple>
#include <vector>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include "Core/Delegate.h"
#include "Element.h"

namespace Presentation::UI {
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

        static EventCatalog& GetDefault() noexcept;
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
    protected:
        EventNode* const GetEventNode() const noexcept override;
    private:
        struct SharedMutexHandler {
            SharedMutexHandler() = default;

            explicit SharedMutexHandler(std::mutex& mutex) noexcept: _PMutex(std::addressof(mutex)) {}

            void lock() { _PMutex->lock(); }

            bool try_lock() noexcept { return _PMutex->try_lock(); }

            void unlock() noexcept { _PMutex->unlock(); }
        private:
            std::mutex* _PMutex = nullptr;
        };
        const EventCatalog* _Catalog;
        std::unique_ptr<GenericSignal<Element, SharedMutexHandler>[]> _Signals;
    };
}
