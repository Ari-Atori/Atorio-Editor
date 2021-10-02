#ifndef ATORIO_GLRECTANGLE
#define ATORIO_GLRECTANGLE

#include <GL/glew.h>

/* GLRectangle will represent the most simple rectangle we can have:
 * One with coordinated which span the entire screen. This proves to
 * be somewhat useful. */

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
