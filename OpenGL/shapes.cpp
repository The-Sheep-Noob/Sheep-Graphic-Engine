#include "shapes.h"
#include <iostream>
#include <vector>
#include "settings.h"


Square::Square() :Z_rotate(0) , Y_rotate(0) , X_rotate(0), proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), Z_index(0), R(0), G(0), B(0), A(255), Size(1), Texture(""), X(0), Y(0) {

    Shapes::sub_objects.push_back(this);
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
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    setUniform1b("has_texture", false);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_Z_index = Z_index;
    prev_Size = Size;
    prev_Texture = Texture;
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
    const float X_1 = X - X_size;
    const float Y_1 = Y - Y_size;
    const float X_2 = X + X_size;
    const float Y_2 = Y + Y_size;

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
    prev_Z_index = Z_index;
    prev_Size = Size;
}

int count = 1;

void Square::draw() 
{
    std::cout << count <<": ";
    count++;
    std::cout << (Texture != "" ? Texture : "no texture") << std::endl;

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Z_index != Z_index ||
        prev_Size != Size
    ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture(); 

    updateColors();
    updateRotation();
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



















void Shapes::renderShapes() 
{
    for (Object* obj : Shapes::sub_objects) {
        obj->draw(); // draw object
    }
}

std::vector<Object*> Shapes::sub_objects = std::vector<Object*>();