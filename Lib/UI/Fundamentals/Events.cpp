#include "Events.h"

namespace Presentation::UI {
    namespace { std::mutex UILock; }

    EventNode::EventNode(const EventCatalog& catalog)
            :_Catalog(std::addressof(catalog)),
             _Signals(std::make_unique<GenericSignal<Element, SharedMutexHandler>[]>(catalog.Count())) {
        for (auto i = 0u; i<catalog.Count(); ++i)
            _Signals[i].SetMutex(SharedMutexHandler(UILock));
    }

    EventNode* const EventNode::GetEventNode() const noexcept { return const_cast<EventNode*>(this); }
}
