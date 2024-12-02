#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace IMGV::Core
{
    class IMGV_API MouseButtonPressEvent : public Event
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

    class IMGV_API MouseButtonReleaseEvent : public Event
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

    class IMGV_API MouseCursorMovedEvent : public Event
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

    class IMGV_API MouseScrollEvent : public Event
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

    class IMGV_API MouseCursorEnterEvent : public Event
    {
        public:
            MouseCursorEnterEvent() = default;
            virtual ~MouseCursorEnterEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseCursorEnterEvent)
    };

    class IMGV_API MouseCursorLeaveEvent : public Event
    {
        public:
            MouseCursorLeaveEvent() = default;
            virtual ~MouseCursorLeaveEvent() = default;

            EVENT_CLASS_CATEGORY(EventCategory::Mouse)
            EVENT_CLASS_TYPE(EventType::MouseCursorLeaveEvent)
    };
}