#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

#include <eigen3/Eigen/Eigen>
#include <iostream>

class Scene
{
public:
    Scene(unsigned int w, unsigned int h);
    Scene(const Scene& s) = delete;
    Scene(Scene&& s) = delete;
    
    

public:
    unsigned int width;
    unsigned int height;
    
    Eigen::Vector3f backgroundColor;

private:

};


#endif