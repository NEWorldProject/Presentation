#pragma once

#include "Common.h"
#include "Fundamentals.h"
#include <string>

namespace Presentation::UI {
    class Window : public LayoutElement, public Renderable, public UIResponder {
    public:
        enum Position {
            Centered,                 /**< Centred On The Primary Display */
            DoNotCare                 /**< Appear Anywhere On The Primary Display */
        };

        enum CreationFlags {
            CreateFullScreen = 1 << 0,          /**< fullscreen window */
            CreateShown = 1 << 1,               /**< window is visible */
            CreateHidden = 1 << 2,              /**< window is not visible */
            CreateBorderless = 1 << 3,          /**< no window decoration */
            CreateResizeable = 1 << 4,          /**< window can be resized */
            CreateMinimized = 1 << 5,           /**< window is minimized */
            CreateMaximized = 1 << 6,           /**< window is maximized */
            CreateInputGrabbed = 1 << 7,        /**< window has grabbed input focus */
            CreateInputFocus = 1 << 8,          /**< window has input focus */
            CreateMouseFocus = 1 << 9,          /**< window has mouse focus */
            CreateFullScreenDesktop = 1 << 10,
            CreateAllowHighDpi = 1 << 11,       /**< window should be created in high-DPI mode if supported.
                                                     On macOS NSHighResolutionCapable must be set true in the
                                                     application's Info.plist for this to have any effect. */
            CreateCapturemouse = 1 << 12,       /**< window has mouse captured (unrelated to INPUT_GRABBED) */
            CreateAlwaysonTop = 1 << 13,        /**< window should always be above others */
            CreateSkipTaskbar = 1 << 14,        /**< window should not be added to the taskbar */
            CreateUtility = 1 << 15,            /**< window should be treated as a utility window */
            CreateTooltip = 1 << 16,            /**< window should be treated as a tooltip */
            CreatePopupMenu = 1 << 17,          /**< window should be treated as a popup menu */
        };

        Window() noexcept : _Handle(nullptr) {}
        
        Window(const std::string& name, const Rect& rect, uint32_t flags);

        ~Window() noexcept;

        auto NativeHandle() const noexcept { return _Handle; }

        Point2D GetPosition() noexcept;

        Point2D GetSize() noexcept;

        std::string GetTitle() noexcept;

        void Hide() noexcept;

        void Maximize() noexcept;

        void Minimize() noexcept;

        void Raise() noexcept;

        void Restore() noexcept;

        void SetFullscreen(bool enable) noexcept;

        void SetIcon() noexcept;

        void SetPosition(const Point2D& pt) noexcept;

        void SetSize(const Point2D& size) noexcept;

        void SetBordered(bool bordered) noexcept;

        void SetResizable(bool resizeable) noexcept;

        void SetTitle(const std::string& title) noexcept;

        void Show() noexcept;
    protected:
        void DoRender() override;
    private:
        void* _Handle;
    };
}
