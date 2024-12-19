#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace IMGV::Core
{
    /**
     * @brief Event emitted when a mouse button is pressed.
     * 
     * This event is emitted when a mouse button is pressed. It contains the
     * button that was pressed.
     */
    class IMGV_API MouseButtonPressEvent final : public Event
    {
        public:
            MouseButtonPressEvent(MouseButton button) : m_Button(button) {}
            virtual ~MouseButtonPressEvent() = default;

            IMGV_NODISCARD MouseButton GetButton() const { return m_Button; }

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseButtonPressEvent)
        
        private:
            MouseButton m_Button;
    };

    /**
     * @brief Event emitted when a mouse button is released.
     * 
     * This event is emitted when a mouse button is released. It contains the
     * button that was released.
     */
    class IMGV_API MouseButtonReleaseEvent final : public Event
    {
        public:
            MouseButtonReleaseEvent(MouseButton button) : m_Button(button) {}
            virtual ~MouseButtonReleaseEvent() = default;
        
            IMGV_NODISCARD MouseButton GetButton() const { return m_Button; }

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseButtonReleaseEvent)

        private:
            MouseButton m_Button;
    };

    /**
     * @brief Event emitted when the mouse cursor is moved.
     * 
     * This event is emitted when the mouse cursor is moved. It contains the
     * new x and y coordinates of the mouse cursor.
     */
    class IMGV_API MouseCursorMovedEvent final : public Event
    {
        public:
            MouseCursorMovedEvent(Double x, Double y) : m_X(x), m_Y(y) {}
            virtual ~MouseCursorMovedEvent() = default;

            IMGV_NODISCARD Double GetX() const { return m_X; }
            IMGV_NODISCARD Double GetY() const { return m_Y; }

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseCursorMovedEvent)

        private:
            Double m_X, m_Y;
    };

    /**
     * @brief Event emitted when the mouse wheel is scrolled.
     * 
     * This event is emitted when the mouse wheel is scrolled. It contains the
     * offset of the mouse wheel in x and y coordinates.
     */
    class IMGV_API MouseScrollEvent final : public Event
    {
        public:
            MouseScrollEvent(Double offsetX, Double offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}
            virtual ~MouseScrollEvent() = default;

            IMGV_NODISCARD Double GetMouseScrollOffsetX() const { return m_OffsetX; }
            IMGV_NODISCARD Double GetMouseScrollOffsetY() const { return m_OffsetY; }

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseWheelEvent)

        private:
            Double m_OffsetX, m_OffsetY;
    };

    /**
     * @brief Event emitted when the mouse cursor enters the window.
     * 
     * This event is emitted when the mouse cursor enters the window,
     * indicating that the cursor has moved from outside to inside the window.
     */
    class IMGV_API MouseCursorEnterEvent final : public Event
    {
        public:
            MouseCursorEnterEvent() = default;
            virtual ~MouseCursorEnterEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseCursorEnterEvent)
    };

    /**
     * @brief Event emitted when the mouse cursor leaves the window.
     * 
     * This event is emitted when the mouse cursor leaves the window,
     * indicating that the cursor has moved from inside to outside the window.
     */
    class IMGV_API MouseCursorLeaveEvent final : public Event
    {
        public:
            MouseCursorLeaveEvent() = default;
            virtual ~MouseCursorLeaveEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseCursorLeaveEvent)
    };

}