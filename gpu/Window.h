#pragma once

#define NORINMAX
#include <Windows.h>
#include <string>
#include <map>
#include <functional>

#define WINDOW_GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define WINDOW_GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

using CallbackFunc = std::function<void()>;

class Window {
public:
    HWND hwnd;
    HINSTANCE hinstance;
    int windowWidth, windowHeight;
    std::string windowName;
    std::map<WPARAM, CallbackFunc> keysCallbacks;

    bool keys[256];
    int mousex;
    int mousey;
    bool mouseButtons[3];

    Window();
    void init(int _windowHeight, int _windowWidth, int window_x, int window_y, std::string _windowName);

    void updateMouse(int x, int y) {
        mousex = x;
        mousey = y;
    }

    void registerKeyCallback(WPARAM key, CallbackFunc func) {
        keysCallbacks.insert({ key, func });
    }

    void runKeyCallback(WPARAM key) {
        if (keysCallbacks.find(key) == keysCallbacks.end()) {
            return;
        }
        CallbackFunc func = keysCallbacks[key];
        func();
    }

    void processMessages();
};