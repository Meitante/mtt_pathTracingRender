#include <iostream>
#include <_stdio.h>
#include <assert.h>


#include "Renderer.h"

std::mutex mutex_ins;
inline float deg2rad(const float& deg) { return deg * M_PI / 180.0; }

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

void Renderer::renderWithTimestampLogged()
{
    auto start = std::chrono::system_clock::now();
    render();
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(stop - start).count();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    milliseconds -= seconds * 1000;
    seconds -= minutes*60; 
    std::cout << "Time taken: \n";
    std::cout << "           " << minutes << " minutes\n";
    std::cout << "           " << seconds << " seconds\n";
    std::cout << "           " << milliseconds << " milliseconds\n";
}

void Renderer::render()
{
    float scale = tan(deg2rad(scene->fov * 0.5));
    float imageAspectRatio = scene->width / (float)scene->height;
    
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
            framebuffer[getFramebufferPosFromXY(x, y)] = Eigen::Vector3f(0, 0, 0);// scene->backgroundColor;
        }
    }
    assert(framebuffer.size() == scene->width * scene->height);


    /*
        two test code block for make sure the 
    */
    // {
    //         unsigned int x = 100;
    //         for(unsigned int y = 0; y < scene->height; ++y)
    //         {
    //             static unsigned int posFramebuffer =  0;
    //             posFramebuffer = getFramebufferPosFromXY(x, y);
    //             framebuffer[posFramebuffer] = Eigen::Vector3f(240.0f/255, 0.0f, 0.0f);
    //         }

    // }

    // {
    //         unsigned int y = 50;
    //         for(unsigned int x = 0; x < scene->width; ++x)
    //         {
    //             static unsigned int posFramebuffer =  0;
    //             posFramebuffer = getFramebufferPosFromXY(x, y);
    //             framebuffer[posFramebuffer] = Eigen::Vector3f(0.0f, 240.0f/255, 0.0f);
    //         }

    // }

    float height = 2*scale*1;
    float width = imageAspectRatio * height;
    int spp = 32;
    int done = 0;
    /*
        multithreading or not.
    */
    if(true)
    {
        auto castRayMultiThreading = [&](uint32_t rowStart, uint32_t rowEnd)
        {
            // std::string a = "start rendering row : " + std::to_string(rowStart) + " to " + std::to_string(rowEnd);
            // std::cout << a << std::endl;
            for(uint32_t i = 0; i < scene->width; ++i)
            {
                for(uint32_t j = rowStart; j < rowEnd; ++j)
                {
                    int m = getFramebufferPosFromXY(i, j);

                    float x = -width/2 + width*(i + 0.5)/scene->width;
                    float y = -height/2 + height*(j + 0.5)/scene->height;
                    Eigen::Vector3f dir = Eigen::Vector3f(x, y, -1);
                    dir.normalize();
                    for(int k = 0; k < spp; ++k)
                    {
                        framebuffer[m] += scene->getColorByTracingRay(Ray(scene->eyePos, dir))/spp;
                    }
                    done++;
                    std::lock_guard<std::mutex> g1(mutex_ins);
                    UpdateProgress(done, scene->width * scene->height);
                }
            }
        };

        int id = 0;
        constexpr int numOfThreading = 8;
        std::vector<std::thread> th(numOfThreading);

        int strideY = (scene->height + 1) / (numOfThreading - 1);
        for(unsigned int i = 0; i < scene->height; i += strideY)
        {
            th[id] = std::thread(castRayMultiThreading, i , std::min(i + strideY, scene->height));
            id++;
        }

        for (int i = 0; i < numOfThreading; i++)
        {
            th[i].join();
        }
        UpdateProgress(scene->width * scene->height, scene->width * scene->height);

    }
    else
    {
        for(int i  = 0; i < scene->width; ++i)
        {
            for(int j = 0; j < scene->height; ++j)
            {
                int m = getFramebufferPosFromXY(i, j);

                float x = -width/2 + width*(i + 0.5)/scene->width;
                float y = -height/2 + height*(j + 0.5)/scene->height;
                Eigen::Vector3f dir = Eigen::Vector3f(x, y, -1);
                dir.normalize();
                for(int k = 0; k < spp; ++k)
                {
                    framebuffer[m] += scene->getColorByTracingRay(Ray(scene->eyePos, dir))/spp;
                }
                done++;
                UpdateProgress(done, scene->width * scene->height);
            }
        }

        UpdateProgress(done, scene->width * scene->height);
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