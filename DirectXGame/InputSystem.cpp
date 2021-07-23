#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
    if (sharedInstance == nullptr)
        InputSystem::intialize();
    return sharedInstance;
}

void InputSystem::intialize()
{
    sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
}

void InputSystem::update()
{
    POINT current_mouse_pos = {};
    ::GetCursorPos(&current_mouse_pos);

    if (first_time)
    {
        old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
        first_time = false;
    }

    if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y) 
    {
        std::unordered_set<InputListener*>::iterator it = set_listeners.begin();

        while (it != set_listeners.end())
        {
            (*it)->onMouseMove(Point(current_mouse_pos.x - old_mouse_pos.x, current_mouse_pos.y - old_mouse_pos.y));
            it++;
        }
    }
    old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

    if (::GetKeyboardState(key_states))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            if (key_states[i] & 0x80)
            {
                std::unordered_set<InputListener*>::iterator it = set_listeners.begin();

                while (it != set_listeners.end())
                {
                    if (i == VK_LBUTTON)
                    {
                        if (key_states[i] != old_key_states[i])
                            (*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    } 
                    else if (i == VK_RBUTTON)
                    {
                        if (key_states[i] != old_key_states[i])
                            (*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    } 
                    else
                    {
                        (*it)->onKeyDown(i);
                    }
                    it++;
                }
            }
            else
            {
                if (key_states[i] != old_key_states[i])
                {
                    std::unordered_set<InputListener*>::iterator it = set_listeners.begin();

                    while (it != set_listeners.end())
                    {
                        if (i == VK_LBUTTON)
                            (*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else if (i == VK_RBUTTON)
                            (*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else
                            (*it)->onKeyUp(i);
                        it++;
                    }
                }
            }
        }
        ::memcpy(old_key_states, key_states, sizeof(unsigned char) * 256);
    }
}

void InputSystem::addListener(InputListener* listener)
{
    set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
    set_listeners.erase(listener);
}

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}
