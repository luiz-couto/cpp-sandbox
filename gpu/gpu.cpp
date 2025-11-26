#include "Window.h"
#include "Core.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    Core core;
    win.init(1024, 1024, 0, 0, "My Window");
    core.init(win.hwnd, win.windowWidth, win.windowHeight);

    while (true) {
        core.resetCommandList();
        core.beginFrame();
        win.processMessages();
        if (win.keys[VK_ESCAPE] == 1) {
            break;
        }
        core.finishFrame();
    }

    core.flushGraphicsQueue();
    return 0;
}
