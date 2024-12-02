#pragma once

#include <functional>
#include <type_traits>

#include "typedef.hpp"
#include "base.hpp"

namespace IMGV::Core
{
    /**
     * @brief Event categories
     *
     * Categories that an event can belong to. These are used to filter events
     * in the event bus.
     */
    enum class EventCategory
    {
        Window      = IMGV_BIT(1), //< Events related to the window, such as resizes, moves, and focus changes.
        Keyboard    = IMGV_BIT(2), //< Events related to the keyboard, such as key presses and releases.
        Mouse       = IMGV_BIT(3), //< Events related to the mouse, such as mouse moves and button presses.
        Unknown     = IMGV_BIT(4), //< Events that do not fit into any other category.
    };

    /**
     * @brief Event type enumeration
     *
     * This enumeration contains all the possible event types that can be
     * generated by the event system.
     */
    enum class EventType
    {
        WindowCloseEvent                    = IMGV_BIT(1),  //< The window has been closed.
        WindowResizeEvent                   = IMGV_BIT(2),  //< The window has been resized.
        WindowMoveEvent                     = IMGV_BIT(3),  //< The window has been moved.
        WindowFocusGainEvent                = IMGV_BIT(4),  //< The window has gained focus.
        WindowFocusLostEvent                = IMGV_BIT(5),  //< The window has lost focus.
        WindowFramePixelSizeChangeEvent     = IMGV_BIT(6),  //< The frame pixel size has changed.
        WindowMaximizeEvent                 = IMGV_BIT(7),  //< The window has been maximized.
        WindowMinimizeEvent                 = IMGV_BIT(8),  //< The window has been minimized.
        KeyboardKeyPressEvent               = IMGV_BIT(9),  //< A key has been pressed.
        KeyboardKeyReleaseEvent             = IMGV_BIT(10), //< A key has been released.
        KeyboardKeyRepeatEvent              = IMGV_BIT(11), //< A key has been repeated (e.g. by holding down the key).
        KeyboardKeyCharEvent                = IMGV_BIT(12), //< A key has been pressed and the character has been generated.
        MouseButtonPressEvent               = IMGV_BIT(13), //< A mouse button has been pressed.
        MouseButtonReleaseEvent             = IMGV_BIT(14), //< A mouse button has been released.
        MouseWheelEvent                     = IMGV_BIT(15), //< The mouse wheel has been scrolled.
        MouseCursorMovedEvent               = IMGV_BIT(16), //< The mouse cursor has been moved.
        MouseCursorEnterEvent               = IMGV_BIT(17), //< The mouse cursor has entered the window.
        MouseCursorLeaveEvent               = IMGV_BIT(18), //< The mouse cursor has left the window.
    };

    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; } \
		virtual EventType GetEventType() const override { return GetStaticType(); } \
		virtual CString GetName() const override { return #type; }
        
    #define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategory() const override { return category; }

    /**
     * @brief The base class for all events.
     * 
     * This class provides a common interface for all events, including
     * getting the event type and category, getting the event name as a
     * string, converting the event to a string, and determining if the
     * event has been handled.
     */
    class IMGV_API Event 
	{
		public:
			/**
			 * @brief The default constructor.
			 * This constructor is the default constructor for all events.
			 */
			Event() = default;

			/**
			 * @brief The virtual destructor.
			 * This destructor is the default destructor for all events.
			 */
			virtual ~Event() = default;

			/**
			 * @brief Gets the type of the event.
			 * @return The type of the event.
			 */
			virtual EventType GetEventType() const = IMGV_NULL;

			/**
			 * @brief Gets the category of the event.
			 * @return The category of the event.
			 */
			virtual EventCategory GetCategory() const = IMGV_NULL;

			/**
			 * @brief Gets the name of the event as a string.
			 * @return The name of the event as a string.
			 */
			virtual CString GetName() const = IMGV_NULL;

			/**
			 * @brief Converts the event to a string.
			 * @return The event as a string.
			 */
			virtual String ToString() const { return String(GetName()); }

			/**
			 * @brief Determines if the event category matches the given category.
			 * @param category The category to compare with.
			 * @return True if the category matches, false otherwise.
			 */
			Boolean CategoryEquals(EventCategory category) const 
			{
				return GetCategory() == category;
			}

		public:
			/**
			 * @brief Whether the event has been handled.
			 * This flag is used to determine if the event has been handled.
			 */
			Boolean Handled{ IMGV_FALSE };
	};

    /**
     * @brief A class that helps dispatch events to their respective handlers.
     *
     * This class is used to dispatch events to their respective handlers. It
     * is used by the event bus to dispatch events to their corresponding
     * handlers.
     */
    class IMGV_API EventHandler 
    {
        public:
            /**
             * @brief The constructor.
             * @param event The event to dispatch.
             */
            EventHandler(Event& event) : m_Event(event) {}

            /**
             * @brief The virtual destructor.
             * This destructor is the default destructor for all event handlers.
             */
            ~EventHandler() = default;

            /**
             * @brief Dispatches the event to its respective handler.
             * @param function The function to dispatch the event to.
             * @return True if the event was handled, false otherwise.
             */
            template<typename T, typename Function>
            Boolean Dispatch(const Function& function) 
            {
                if (m_Event.GetEventType() == T::GetStaticType()) 
                {
                    // Cast the event to the correct type and pass it to the
                    // function. If the event was handled, set the Handled flag
                    // to true.
                    m_Event.Handled |= function(static_cast<T&>(m_Event));
                    return IMGV_TRUE;
                }
                
                return IMGV_FALSE;
            }

        private:
            Event& m_Event; ///< The event to dispatch.
    };

    /**
     * @brief A type definition for an event callback function.
     * 
     * This is a std::function that takes an Event& as its argument and returns
     * void. The purpose of this function is to allow the user to pass a custom
     * function to the EventHandler class, which will be called when an event
     * of the correct type is dispatched.
     * 
     * The EventHandler class will pass the event as an argument to the
     * function, and will also set the Handled flag of the event to true if the
     * function returns true.
     */
    using EventCallBack = std::function<void(Event&)>;
}

    /**
     * @brief A macro to create an event callback.
     * 
     * This macro will create a lambda function that takes an Event& as its
     * argument and returns void. The lambda function will call the function
     * passed as an argument to the macro with the event as its argument, and
     * will also set the Handled flag of the event to true if the function
     * returns true.
     * 
     * @param fn The function to call when the event is dispatched.
     * 
     * @returns A lambda function that takes an Event& as its argument and
     * returns void.
     */
#define IMGV_EVENT_CALLBACK(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }