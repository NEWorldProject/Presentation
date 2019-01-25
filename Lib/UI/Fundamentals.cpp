//
// Created by 刘予顺 on 2018/11/29.
//

#include "Fundamentals.h"

namespace Presentation::UI {
    namespace {
        auto Catalog0 = EventCatalog::Create<
                // Layout Event
                LayoutUpdateEvent,
                // Render Events
                BeforeRenderEvent,
                AfterRenderEvent,
                // UI Responder Events
                TouchEnterEvent,
                TouchLeaveEvent,
                TouchDownEvent,
                TouchMoveEvent,
                TouchUpEvent,
                KeyDownEvent,
                KeyUpEvent,
                KeyPressEvent,
                FileDropEvent,
                FocusEvent,
                GainFocusEvent,
                LoseFocusEvent,
                TextInputEvent
        >();
    }

    EventCatalog& EventCatalog::GetDefault() noexcept { return Catalog0; }
}
