#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace IMGV::Core
{
    class IMGV_API KeyboardKeyPressEvent final : public Event
    {
        public:
            KeyboardKeyPressEvent(KeyCodes keyCode) : m_KeyCode(keyCode) {}
            virtual ~KeyboardKeyPressEvent() = default;

            IMGV_NODISCARD KeyCodes GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategory::Keyboard);
            EVENT_CLASS_TYPE(EventType::KeyboardKeyPressEvent);

        private:
            KeyCodes m_KeyCode;
    };

    class IMGV_API KeyboardKeyReleaseEvent final : public Event
    {
        public:
            KeyboardKeyReleaseEvent(KeyCodes keyCode) : m_KeyCode(keyCode) {}
            virtual ~KeyboardKeyReleaseEvent() = default;

            IMGV_NODISCARD KeyCodes GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategory::Keyboard);
            EVENT_CLASS_TYPE(EventType::KeyboardKeyReleaseEvent);

        private:
            KeyCodes m_KeyCode;
    };

    class IMGV_API KeyboardKeyRepeatEvent final : public Event
    {
        public:
            KeyboardKeyRepeatEvent(KeyCodes keyCode) : m_KeyCode(keyCode) {}
            virtual ~KeyboardKeyRepeatEvent() = default;

            IMGV_NODISCARD KeyCodes GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategory::Keyboard);
            EVENT_CLASS_TYPE(EventType::KeyboardKeyRepeatEvent);

        private:
            KeyCodes m_KeyCode;
    };

    class IMGV_API KeyboardKeyCharEvent final : public Event
    {
        public:
            KeyboardKeyCharEvent(UInt32 character) : m_Character(character) {}
            virtual ~KeyboardKeyCharEvent() = default;

            IMGV_NODISCARD UInt32 GetCharacter() const { return m_Character; }

            EVENT_CLASS_CATEGORY(EventCategory::Keyboard);
            EVENT_CLASS_TYPE(EventType::KeyboardKeyCharEvent);

        private:
            UInt32 m_Character;
    };
}