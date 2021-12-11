#include "Renderer.h"

/*
    This file is to test the output directly.
*/

int main()
{
    auto scene = std::make_unique<Scene>(480, 270);
    Renderer r(std::move(scene), "test.ppm");
    r.render();
    return 0;
}