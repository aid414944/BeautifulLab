#ifndef BEAUTIFULLABGLWIDGET_H
#define BEAUTIFULLABGLWIDGET_H

#include <QGLWidget>
#include <QOpenGLExtraFunctions>
#include <QImage>
#include <QOpenGLTexture>

class BeautifulLabGLWidget : public QGLWidget, protected QOpenGLExtraFunctions
{
public:
    BeautifulLabGLWidget();
    virtual ~BeautifulLabGLWidget();

protected:
    void initializeGL()override;
    void resizeGL(int width, int height)override;
    void paintGL()override;

private:
    QImage image;
    int imageWidth;
    int imageHeight;
public:
    void loadImage(QString path);
    void setSamplingRadius(int radius);
    void setBeautifulStrength(float strength);


private:
    GLuint program;
    GLuint vao;
    GLuint arrayBuffer;
    GLuint indexBuffer;
    GLuint texture;
    GLint xScaleFactor;
    GLint yScaleFactor;
    GLint imageWidthLocation;
    GLint imageHeightLocation;
    GLint samplingRadiusLocation;
    GLint strengthLocation;
private:
    void __updateScaleFactor();
    GLuint __loadShader(GLenum type, const char *shaderSrc);
    GLuint __createProgram(GLuint vertexShader, GLuint fragmentShader);
    void __checkError();
};

#endif // BEAUTIFULLABGLWIDGET_H
