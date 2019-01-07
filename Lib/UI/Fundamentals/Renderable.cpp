#include "Renderable.h"

namespace Presentation::UI {
    Renderable::Renderable() = default;

    void Renderable::Render() {
        OnBeforeRender();
        DoRender();
        OnAfterRender();
    }

    void Renderable::OnBeforeRender() {
        if (auto evn = GetEventNode(); evn) {
            BeforeRenderEvent event{};
            evn->Cast<BeforeRenderEvent>(event);
        }
    }

    void Renderable::OnAfterRender() {
        if (auto evn = GetEventNode(); evn) {
            AfterRenderEvent event{};
            evn->Cast<AfterRenderEvent>(event);
        }
    }
}
