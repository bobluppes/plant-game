#include "window_manager.h"

int main() {

    WindowManager window_manager{"Plant Game"};

    while(!window_manager.should_close())
    {
        window_manager.process_input();

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window_manager.render();
    }

    glfwTerminate();

    return 0;
}
