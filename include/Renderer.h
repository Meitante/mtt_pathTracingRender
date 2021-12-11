#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <eigen3/Eigen/Eigen>
#include <cstdlib>
#include <algorithm>


#include "Scene.h"

/*
    Main renderer, output as a ppm
*/
class Renderer
{
public:
    Renderer(std::unique_ptr<Scene> in_scene, std::string in_outputPath);
    Renderer(const Renderer& renderer) = delete;
    Renderer(Renderer&& renderer) = delete;

    /*
        Main render function
    */
    void render();
    unsigned int getFramebufferPosFromXY(unsigned int x, unsigned int y);

private:
    std::unique_ptr<Scene> scene;
    std::string outputPath;

};


#endif