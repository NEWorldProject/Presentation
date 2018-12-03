#pragma once

#include "Common.h"
#include "Mpl/TypeTuple.h"
#include <type_traits>

namespace Presentation::UI {
    template <class T> struct Event;

    template <class ...Args>
    struct Event<void(Args...)> {
        using Arguments = TypeTuple<Args...>;
        using SignalType = Delegate<void(Args...)>;
    };

    class EventBus {
    public:
        template <class Event, class Sender, class ...Args>
        void Send(const Sender& sender, Args&&... args) {
            if constexpr(std::is_convertible_v<std::decay<Sender>*, EventBus*>) {

            }
        }

        template <class Event, class Sender, class ...Args>
        void Forward(const Sender& sender, Args&&... args) {
            if constexpr(std::is_convertible_v<std::decay<Sender>*, EventBus*>) {

            }
        }
    };
}
