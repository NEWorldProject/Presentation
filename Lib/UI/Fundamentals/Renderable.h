#pragma once

#include "Events.h"

namespace Presentation::UI {
    struct BeforeRenderEvent : MessageBase { };

    struct AfterRenderEvent : MessageBase { };

    class Renderable : public virtual EventNode {
    public:
        Renderable();
    protected:
        virtual void Render();

        virtual void OnBeforeRender();

        virtual void OnAfterRender();

        virtual void DoRender() = 0;
    };
}