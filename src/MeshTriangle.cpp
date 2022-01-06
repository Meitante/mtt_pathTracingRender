#include "MeshTriangle.h"


MeshTriangle::MeshTriangle(const std::string& filename, const Material& material)
{
    objl::Loader loader;
    if(!loader.LoadFile(filename))
    {
        std::cout << "Loading file failing: " << filename << std::endl;
        assert(false);
    }
}