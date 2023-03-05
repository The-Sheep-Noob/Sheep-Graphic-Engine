#include "shapes.h"
#include <iostream>
#include <vector>
#include "settings.h"
#include <algorithm>
#include "program.h"


Square::Square() :Z_rotate(0) , Transform_from_middle(true), Y_rotate(0) , X_rotate(0), proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), R(0), G(0), B(0), A(255), Size(100), Texture(""), X(0), Y(0) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
      0.9f, 1.0f, 1.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}


void Square::updateTexture()
{
    if (Texture == "")
    {
        setUniform1b("has_texture", false);
    }
    else
    {
        setUniform1b("has_texture", true);
        setTexture(Texture, "c_texture", true);
    }
    prev_Texture = Texture;
}


void Square::updateColors()
{
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
}

void Square::updateRotation()
{
    glm::mat4 mvp = 
        glm::rotate(glm::mat4(1.0f), glm::radians((float)Z_rotate), glm::vec3(0.0f, 0.0f, 1.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians((float)Y_rotate), glm::vec3(0.0f, 1.0f, 0.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians((float)X_rotate), glm::vec3(1.0f, 0.0f, 0.0f))
      * proj;
    setUniformMatrix4fv("mvp", mvp);
}

void Square::updateVertexBuffer()
{
    const int X_size = Size / 2;
    const int Y_size = Size / 2;
    float X_1 = X - X_size;
    float Y_1 = Y - Y_size;
    float X_2 = X + X_size;
    float Y_2 = Y + Y_size;

    if (!Transform_from_middle) {
        X_1 = X + Size;
        Y_1 = Y + Size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 0.0f, 1.0f,
      X_2, Y_1, 0.0f, 0.0f,
      X_1, Y_1 , 1.0f, 0.0f,
      X_1, Y_2, 1.0f, 1.0f,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
}

void Square::scale(int scaler) {
    Size *= scaler;
}


void Square::draw() 
{

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size
    ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture(); 

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}

void Square::removeTexture()
{
    Texture = "";
}

void Square::setColors(int c_R, int c_G, int c_B) 
{
    R = c_R;
    G = c_G;
    B = c_B;
}

void Square::setColors(int RGB)
{
    R = RGB;
    G = RGB;
    B = RGB;
}

void Square::setColors(int c_R, int c_G, int c_B, int c_A)
{
    R = c_R;
    G = c_G;
    B = c_B;
    A = c_A;
}

void Square::setColorsTexture(int c_R, int c_G, int c_B)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
}

void Square::setColorsTexture(int RGB)
{
    Texture_colors.R = RGB;
    Texture_colors.G = RGB;
    Texture_colors.B = RGB;
}

void Square::setColorsTexture(int c_R, int c_G, int c_B, int c_A)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
    Texture_colors.A = c_A;
}

void Square::setPositions(int XY)
{
    X = XY;
    Y = XY;
}

void Square::setPositions(int _X, int _Y)
{
    X = _X;
    Y = _Y;
}

void Square::setPositions(int _X, int _Y, int _Z)
{
    X = _X;
    Y = _Y;
    Z_index = _Z;
}

void Square::setRotation(int Z)
{
    Z_rotate = Z;
}

void Square::setRotations(int X, int Y, int Z)
{
    X_rotate = X;
    Y_rotate = Y;
    Z_rotate = Z;
}


void Square::updateTextureColors() {
    setUniform4f("t_color", (float)Texture_colors.R / 255, (float)Texture_colors.G / 255, (float)Texture_colors.B / 255, (float)Texture_colors.A / 255);
};

void Rectangle::updateTextureColors() {
    setUniform4f("t_color", (float)Texture_colors.R / 255, (float)Texture_colors.G / 255, (float)Texture_colors.B / 255, (float)Texture_colors.A / 255);
};



Rectangle::Rectangle() :Z_rotate(0), Transform_from_middle(true), Y_rotate(0), X_rotate(0), proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), R(0), G(0), B(0), A(255), X_size(100) , Y_size(50), Texture(""), X(0), Y(0) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
      0.9f, 1.0f, 1.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}


void Rectangle::updateTexture()
{
    if (Texture == "")
    {
        setUniform1b("has_texture", false);
    }
    else
    {
        setUniform1b("has_texture", true);
        setTexture(Texture, "c_texture", true);
    }
    prev_Texture = Texture;
}


void Rectangle::updateColors()
{
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
}

void Rectangle::updateRotation()
{
    glm::mat4 mvp =
        glm::rotate(glm::mat4(1.0f), glm::radians((float)Z_rotate), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)Y_rotate), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)X_rotate), glm::vec3(1.0f, 0.0f, 0.0f))
        * proj;
    setUniformMatrix4fv("mvp", mvp);
}

void Rectangle::updateVertexBuffer()
{
    const int _X_size = X_size / 2;
    const int _Y_size = Y_size / 2;
    float X_1 = X - _X_size;
    float Y_1 = Y - _Y_size;
    float X_2 = X + _X_size;
    float Y_2 = Y + _Y_size;

    if (!Transform_from_middle) {
        X_1 = X + X_size;
        Y_1 = Y + Y_size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 0.0f, 1.0f,
      X_2, Y_1, 0.0f, 0.0f,
      X_1, Y_1 , 1.0f, 0.0f,
      X_1, Y_2, 1.0f, 1.0f,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
}


void Rectangle::scale(int scaler) {
    X_size *= scaler;
    Y_size *= scaler;
}

void Rectangle::draw()
{

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_X_size != X_size ||   
        prev_Y_size != Y_size
        ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}

void Rectangle::removeTexture()
{
    Texture = "";
}

void Rectangle::setColors(int c_R, int c_G, int c_B)
{
    R = c_R;
    G = c_G;
    B = c_B;
}

void Rectangle::setColors(int RGB)
{
    R = RGB;
    G = RGB;
    B = RGB;
}

void Rectangle::setColors(int c_R, int c_G, int c_B, int c_A)
{
    R = c_R;
    G = c_G;
    B = c_B;
    A = c_A;
}

void Rectangle::setColorsTexture(int c_R, int c_G, int c_B)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
}

void Rectangle::setColorsTexture(int RGB)
{
    Texture_colors.R = RGB;
    Texture_colors.G = RGB;
    Texture_colors.B = RGB;
}

void Rectangle::setColorsTexture(int c_R, int c_G, int c_B, int c_A)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
    Texture_colors.A = c_A;
}

void Rectangle::setPositions(int XY)
{
    X = XY;
    Y = XY;
}

void Rectangle::setPositions(int _X, int _Y)
{
    X = _X;
    Y = _Y;
}

void Rectangle::setPositions(int _X, int _Y, int _Z)
{
    X = _X;
    Y = _Y;
    Z_index = _Z;
}

void Rectangle::setRotation(int Z)
{
    Z_rotate = Z;
}

void Rectangle::setRotations(int X, int Y, int Z)
{
    X_rotate = X;
    Y_rotate = Y;
    Z_rotate = Z;
}

void Rectangle::setSizes(int X, int Y)
{
    X_size = X;
    Y_size = Y;

}

void Rectangle::setSizes(int XY)
{
    X_size = XY;
    Y_size = XY;
}



Circle::Circle() :Z_rotate(0), Transform_from_middle(true), Y_rotate(0), X_rotate(0), proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), R(0), G(0), B(0), A(255), Size(100), Texture(""), X(0), Y(0) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
      0.9f, 1.0f, 1.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_circle.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}


void Circle::updateTexture()
{
    if (Texture == "")
    {
        setUniform1b("has_texture", false);
    }
    else
    {
        setUniform1b("has_texture", true);
        setTexture(Texture, "c_texture", true);
    }
    prev_Texture = Texture;
}


void Circle::updateColors()
{
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
}

void Circle::updateRotation()
{
    glm::mat4 mvp =
        glm::rotate(glm::mat4(1.0f), glm::radians((float)Z_rotate), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)Y_rotate), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)X_rotate), glm::vec3(1.0f, 0.0f, 0.0f))
        * proj;
    setUniformMatrix4fv("mvp", mvp);
}

void Circle::updateVertexBuffer()
{
    const int X_size = Size / 2;
    const int Y_size = Size / 2;
    float X_1 = X - X_size;
    float Y_1 = Y - Y_size;
    float X_2 = X + X_size;
    float Y_2 = Y + Y_size;

    if (!Transform_from_middle) {
        X_1 = X + Size;
        Y_1 = Y + Size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 0.0f, 1.0f,
      X_2, Y_1, 0.0f, 0.0f,
      X_1, Y_1 , 1.0f, 0.0f,
      X_1, Y_2, 1.0f, 1.0f,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
}

void Circle::scale(int scaler) {
    Size *= scaler;
}


void Circle::draw()
{

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size
        ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}

void Circle::removeTexture()
{
    Texture = "";
}

void Circle::setColors(int c_R, int c_G, int c_B)
{
    R = c_R;
    G = c_G;
    B = c_B;
}

void Circle::setColors(int RGB)
{
    R = RGB;
    G = RGB;
    B = RGB;
}

void Circle::setColors(int c_R, int c_G, int c_B, int c_A)
{
    R = c_R;
    G = c_G;
    B = c_B;
    A = c_A;
}

void Circle::setColorsTexture(int c_R, int c_G, int c_B)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
}

void Circle::setColorsTexture(int RGB)
{
    Texture_colors.R = RGB;
    Texture_colors.G = RGB;
    Texture_colors.B = RGB;
}

void Circle::setColorsTexture(int c_R, int c_G, int c_B, int c_A)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
    Texture_colors.A = c_A;
}

void Circle::setPositions(int XY)
{
    X = XY;
    Y = XY;
}

void Circle::setPositions(int _X, int _Y)
{
    X = _X;
    Y = _Y;
}

void Circle::setPositions(int _X, int _Y, int _Z)
{
    X = _X;
    Y = _Y;
    Z_index = _Z;
}

void Circle::setRotation(int Z)
{
    Z_rotate = Z;
}

void Circle::setRotations(int X, int Y, int Z)
{
    X_rotate = X;
    Y_rotate = Y;
    Z_rotate = Z;
}


void Circle::updateTextureColors() {
    setUniform4f("t_color", (float)Texture_colors.R / 255, (float)Texture_colors.G / 255, (float)Texture_colors.B / 255, (float)Texture_colors.A / 255);
};
