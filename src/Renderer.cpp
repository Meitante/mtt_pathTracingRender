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
        
        
       yA
        |
        |
        |
        |
        |_________________>
                          x
    */
    return y + x * scene->width;
}


void Renderer::render()
{
    
    /*
        framebuffer from 0 to scene->width * scene->height - 1
        we hope it as a bijection between frambuffer and screen pixel
    */
    auto framebuffer = std::vector<Eigen::Vector3f>(0);


    for(int i = 0; i < scene->width * scene->height; i++)
    {
        framebuffer.emplace_back(scene->backgroundColor.x(), scene->backgroundColor.y(), scene->backgroundColor.z());
    }
    assert(framebuffer.size() == scene->width * scene->height);



    // start output to ppm
    {
        FILE* fp = fopen(outputPath.c_str(), "wb");
        fprintf(fp, "P6\n%d %d\n255\n", scene->width, scene->height);
        for(unsigned int x = 0; x < scene->width; ++x)
        {
            for(unsigned int y = 0; y < scene->height; ++y)
            {
                static unsigned char color[3] = {0, 0, 0};
                static unsigned int posFramebuffer = getFramebufferPosFromXY(x, y);
                color[0] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].x(), 0.0f, 1.0f));
                color[1] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].y(), 0.0f, 1.0f));
                color[2] = (unsigned char)(255 * std::clamp(framebuffer[posFramebuffer].z(), 0.0f, 1.0f));
                fwrite(color, 1, 3, fp);
            }
        }
        fclose(fp);
    }

}