#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>
#include <GL/glx.h>
#include <iostream>

#define PRINT(x) std::cout << x << std::endl;

class MyWindow : public Fl_Gl_Window {
    void draw();
    int handle(int);
    int id;
public:
    MyWindow(int X, int Y, int W, int H, const char *L, int id)
        : Fl_Gl_Window(X, Y, W, H, L),id(id) {}
    static GLXContext glContext;
};

GLXContext MyWindow::glContext = NULL;


void MyWindow::draw() {
    PRINT("drawing")
    bool success = glXMakeCurrent(XOpenDisplay(0),glXGetCurrentDrawable(),glContext);
    if(!success)
        PRINT("failed to switch to window");
    PRINT("current glX drawable is " << glXGetCurrentDrawable());
    PRINT("current glX context is " << glXGetCurrentContext());
    if(id == 1) {
        glClearColor(1.0f,0.0f,0.0f,0.0f);
    } else if(id == 2) {
        glClearColor(0.0f,1.0f,0.0f,0.0f);
    } else {
        glClearColor(0.0f,0.0f,1.0f,0.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);

}

int MyWindow::handle(int event) {
    if(event == FL_KEYBOARD) {
        PRINT("Key pressed in window " << id);
        this->redraw();
    }
}

int main(int argc, char ** argv) {

    // Create GL context
    int sngBuf[] = { GLX_RGBA,
                     GLX_DOUBLEBUFFER,
                     GLX_RED_SIZE, 1,
                     GLX_GREEN_SIZE, 1,
                     GLX_BLUE_SIZE, 1,
                     GLX_DEPTH_SIZE, 12,
                     None
    };
    Display * display = XOpenDisplay(0);
    XVisualInfo* vi = glXChooseVisual(display, DefaultScreen(display), sngBuf);

    MyWindow::glContext = glXCreateContext(display, vi, 0, GL_TRUE);

    MyWindow window(0,0,400,400,"Window 1", 1);
    window.show(argc,argv);

    MyWindow window2(400,0,400,400,"Window 2", 2);
    window2.show(argc,argv);

    MyWindow window3(800,0,400,400,"Window 3", 3);
    window3.show(argc,argv);

    return Fl::run();
}
