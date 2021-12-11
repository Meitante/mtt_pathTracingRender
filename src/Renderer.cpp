#include <iostream>
#include <_stdio.h>
#include <assert.h>


#include "Renderer.h"

Renderer::Renderer(std::unique_ptr<Scene> in_scene, std::string in_outputPath)
:scene(std::move(in_scene))
,outputPath(in_outputPath)
{

}

unsigned int Renderer::getFramebufferPosFromXY(unsigned int x, unsigned int y)
{
    /*
        x from 0 to scene->width - 1
        y from 0 to scene->height - 1
    */
    return y + x * scene->height;
}


void Renderer::render()
{
    
    /*
        framebuffer from 0 to scene->width * scene->height - 1
        we hope it as a bijection between frambuffer and screen pixel

        The coordinate mapping should be like:
       yA
        |
        |
        |
        |
        |_________________>
                          x

    */
    auto framebuffer = std::vector<Eigen::Vector3f>(scene->width * scene->height);
    for(unsigned int x = 0; x < scene->width; ++x)
    {
        for(unsigned int y = 0; y < scene->height; ++y)
        {
            framebuffer[getFramebufferPosFromXY(x, y)] = scene->backgroundColor;
        }
    }
    assert(framebuffer.size() == scene->width * scene->height);


    /*
        two test code block for make sure the 
    */
    {
            unsigned int x = 100;
            for(unsigned int y = 0; y < scene->height; ++y)
            {
                static unsigned int posFramebuffer =  0;
                posFramebuffer = getFramebufferPosFromXY(x, y);
                framebuffer[posFramebuffer] = Eigen::Vector3f(240.0f/255, 0.0f, 0.0f);
            }

    }

    {
            unsigned int y = 50;
            for(unsigned int x = 0; x < scene->width; ++x)
            {
                static unsigned int posFramebuffer =  0;
                posFramebuffer = getFramebufferPosFromXY(x, y);
                framebuffer[posFramebuffer] = Eigen::Vector3f(0.0f, 240.0f/255, 0.0f);
            }

    }

    // start output to ppm
    {
        FILE* fp = fopen(outputPath.c_str(), "wb");
        fprintf(fp, "P6\n%d %d\n255\n", scene->width, scene->height);
        for(unsigned int y = 0; y < scene->height; ++y)
        {
            for(unsigned int x = 0; x < scene->width; ++x)
            {
                static unsigned char color[3] = {0, 0, 0};
                static unsigned int posFramebuffer = 0;
                // y set to height-y is because the wrtting style of ppm
                // ppm is writing from left top
                posFramebuffer = getFramebufferPosFromXY(x, scene->height - y);
                color[0] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].x(), 0.0f, 1.0f));
                color[1] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].y(), 0.0f, 1.0f));
                color[2] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].z(), 0.0f, 1.0f));
                fwrite(color, 1, 3, fp);
            }
        }
        fclose(fp);
    }

}