#pragma once
#include "Window.hpp"

class GameObject {
public:
    virtual void render(Window &window) = 0;

protected:
    int x, y, width, height;
};
