#include "BeautifulLabGLWidget.h"

#include <QOpenGLTexture>
#include "Log.h"
#include <iostream>

using namespace std;

static const char * vertexShader = R"(
#version 300 es
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
out vec2 v_texCoord;
uniform float xScaleFactor;
uniform float yScaleFactor;
void main(){
    mat2 scale = mat2(xScaleFactor,             0,
                                 0, yScaleFactor);

    gl_Position = vec4(scale*a_position.xy, a_position.z, 1.0);
    v_texCoord = a_texCoord;
}
)";

static const char * fShaderStr = R"(
#version 300 es
precision mediump float;
in vec2 v_texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
void main(){
    outColor = texture(textureSampler, v_texCoord);
}
)";

static GLfloat verticeAndTexturePosition[20] = {
        1.0f, 1.0f, 0.0f,// vertice 3
        1.0f, 1.0f,        // texture 3

        1.0f, -1.0f, 0.0f,// vertice 2
        1.0f, 0.0f,       // texture 2

        -1.0f, -1.0f, 0.0f,// vertice 1
        0.0f ,0.0f,        // texture 1

        -1.0f, 1.0f, 0.0f, // vertice 0
        0.0f, 1.0f        // texture 0
};

static GLushort verticeIndex[6] = {
        2, 1, 0, // 第一个三角形
        2, 3, 0  // 第二个三角形
};

BeautifulLabGLWidget::BeautifulLabGLWidget():
    texture(0)
{

}

BeautifulLabGLWidget::~BeautifulLabGLWidget()
{
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &arrayBuffer);
    glDeleteVertexArrays(1, &vao);
    if (texture != 0)
        glDeleteTextures(1, &texture);
}

void BeautifulLabGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GLuint vShader = __loadShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fShader = __loadShader(GL_FRAGMENT_SHADER, fShaderStr);
    program = __createProgram(vShader, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    GLint uniformVariable = glGetUniformLocation(program, "textureSampler");
    xScaleFactor = glGetUniformLocation(program, "xScaleFactor");
    yScaleFactor = glGetUniformLocation(program, "yScaleFactor");
    glUseProgram(program);
    glUniform1i(uniformVariable, 0);
    glUniform1f(xScaleFactor, 1.0f);
    glUniform1f(xScaleFactor, 1.0f);
    glUseProgram(0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // 上传顶点数据
    glGenBuffers(1, &arrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, 20*sizeof(GLfloat), verticeAndTexturePosition, GL_STATIC_DRAW);
    // 上传顶点绘制顺序
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), verticeIndex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(GLfloat), (const void *) (3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    imageWidth = width();
    imageHeight = height();
}

void BeautifulLabGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    __updateScaleFactor();
    updateGL();
}

void BeautifulLabGLWidget::paintGL()
{
    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BeautifulLabGLWidget::loadImage(QString path)
{
    image.load(path);
    qDebug("%s\n", path.toStdString().c_str());
    if (texture != 0){
        deleteTexture(texture);
    }
    texture = bindTexture(image);
    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, texture);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // TODO 设置纹理采样参数

    imageWidth = image.width();
    imageHeight = image.height();
    __updateScaleFactor();

    updateGL();
}

void BeautifulLabGLWidget::__updateScaleFactor()
{
    float widgetAspectRatio = width()/(float)height();
    float imageAspectRatio = imageWidth/(float)imageHeight;
    glUseProgram(program);
    if (widgetAspectRatio > imageAspectRatio){
        // 左右黑边
        glUniform1f(xScaleFactor, imageAspectRatio*height()/width());
        glUniform1f(yScaleFactor, 1.0f);
    } else{
        // 上下黑边
        glUniform1f(xScaleFactor, 1.0f);
        glUniform1f(yScaleFactor, width()/imageAspectRatio/height());
    }
    glUseProgram(0);
}

GLuint BeautifulLabGLWidget::__loadShader(GLenum type, const char *shaderSrc)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        // 失败
        logError("Load shader failed:");

        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            logError(infoLog);
            delete infoLog;
        }

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint BeautifulLabGLWidget::__createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    if (program == 0) {
        logError("glCreateProgram() failed!");
        return 0;
    }
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        logError("program link failed!");
        GLchar errorInfo[256];
        glGetProgramInfoLog(program, sizeof(errorInfo), 0, errorInfo);
        logError("%s", errorInfo);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

void BeautifulLabGLWidget::__checkError()
{
    GLenum error = glGetError();
    switch (error){
    case GL_NO_ERROR:
        logError("GL_NO_ERROR");
        break;
    case GL_INVALID_ENUM:
        logError("GL_INVALID_ENUM");
        break;
    case GL_INVALID_VALUE:
        logError("GL_INVALID_VALUE");
        break;
    case GL_INVALID_OPERATION:
        logError("GL_INVALID_OPERATION");
        break;
    case GL_OUT_OF_MEMORY:
        logError("GL_OUT_OF_MEMORY");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        logError("GL_INVALID_FRAMEBUFFER_OPERATION");
        break;
    default:
        logError("other error: %d", error);
    }
}
