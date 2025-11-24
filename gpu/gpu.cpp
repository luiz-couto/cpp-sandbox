#include "Window.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    Window win;
    win.init(1024, 1024, 0, 0, "My Window");
    while (true)
    {
        win.processMessages();
    }
    return 0;
}
