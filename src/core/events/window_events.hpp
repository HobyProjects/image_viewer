#pragma once

#include "events.hpp"

namespace IMGV::Core
{
    /**
     * @brief Event emitted when the user closes the window.
     * 
     * This event is emitted when the user closes the window, either by clicking
     * the close button or by pressing Alt+F4.
     */
    class IMGV_API WindowCloseEvent final : public Event
    {
        public:
            WindowCloseEvent() = default;
            virtual ~WindowCloseEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowCloseEvent);
    };

    /**
     * @brief Event emitted when the window is resized.
     * 
     * This event is triggered whenever the window's size is changed.
     * It contains the new width and height of the window.
     */
    class IMGV_API WindowResizeEvent final : public Event
    {
        public:
            WindowResizeEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}
            virtual ~WindowResizeEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowResizeEvent);

            IMGV_NODISCARD UInt32 GetWidth() const { return m_Width; }
            IMGV_NODISCARD UInt32 GetHeight() const { return m_Height; }

        private:
            UInt32 m_Width; 
            UInt32 m_Height;
    };

    /**
     * @brief Event emitted when the window's frame size is changed.
     * 
     * This event is triggered whenever the window's frame size is changed.
     * It contains the new width and height of the window's frame.
     * The frame size is the size of the window including the title bar and
     * decorations.
     * 
     * The frame size is different from the client size, which is the size of
     * the window's content area.
     */
    class IMGV_API WindowFramePixelSizeChangedEvent final : public Event
    {
        public:
            WindowFramePixelSizeChangedEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}
            virtual ~WindowFramePixelSizeChangedEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowFramePixelSizeChangeEvent);

            IMGV_NODISCARD UInt32 GetWidth() const { return m_Width; }
            IMGV_NODISCARD UInt32 GetHeight() const { return m_Height; }

        private:
            UInt32 m_Width{IMGV_NULL};
            UInt32 m_Height{IMGV_NULL};
    };

    /**
     * @brief Event emitted when the window is moved.
     *
     * This event is triggered whenever the window's position is changed.
     * It contains the new x and y coordinates of the window.
     */
    class IMGV_API WindowMovedEvent final : public Event
    {
        public:
            WindowMovedEvent(UInt32 x, UInt32 y) : m_X(x), m_Y(y) {}
            virtual ~WindowMovedEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowMoveEvent);

            IMGV_NODISCARD UInt32 GetX() const { return m_X; }
            IMGV_NODISCARD UInt32 GetY() const { return m_Y; }

        private:
            UInt32 m_X{IMGV_NULL};
            UInt32 m_Y{IMGV_NULL}; 
    };

    /**
     * @brief Event emitted when the window gains focus.
     * 
     * This event is triggered whenever the window gains focus, indicating 
     * that it is now the active window receiving input.
     */
    class IMGV_API WindowFocusGainedEvent final : public Event
    {
        public:
            WindowFocusGainedEvent() = default;
            virtual ~WindowFocusGainedEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowFocusGainEvent);
    };

    /**
     * @brief Event emitted when the window loses focus.
     * 
     * This event is triggered whenever the window loses focus, indicating
     * that it is no longer the active window receiving input.
     */
    class IMGV_API WindowFocusLostEvent final : public Event
    {
        public:
            WindowFocusLostEvent() = default;
            virtual ~WindowFocusLostEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowFocusLostEvent);
    };

    /**
     * @brief Event emitted when the window is maximized.
     * 
     * This event is triggered whenever the window is maximized, either by
     * clicking the maximize button or by calling the corresponding function
     * in the windowing API.
     */
    class IMGV_API WindowMaximizedEvent final : public Event
    {
        public:
            WindowMaximizedEvent() = default;
            virtual ~WindowMaximizedEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowMaximizeEvent);
    };

    /**
     * @brief Event emitted when the window is minimized.
     * 
     * This event is triggered whenever the window is minimized, 
     * either by clicking the minimize button or by calling the 
     * corresponding function in the windowing API.
     */
    class IMGV_API WindowMinimizedEvent final : public Event
    {
        public:
            WindowMinimizedEvent() = default;
            virtual ~WindowMinimizedEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Window);
            EVENT_CLASS_TYPE(EventType::WindowMinimizeEvent);
    };
}