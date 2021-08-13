#ifndef ATORIO_GLRECTANGLE
#define ATORIO_GLRECTANGLE

#include <GL/glew.h>

class GLRectangle {
public:
    GLRectangle();
    virtual ~GLRectangle();

    static void init(unsigned int n);
    void bind();
    void draw();
private:
    GLuint vao;
    GLuint vbo[3];
};

#endif
