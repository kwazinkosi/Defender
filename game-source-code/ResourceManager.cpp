#ifndef RESOURCEMANAGER_CPP
#define RESOURCEMANAGER_CPP

#include "ResourceManager.hpp"
#include <stdexcept>

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> resource(new Resource()); // Create a new resource object eg. sf::Texture, sf::Font, etc.
    
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource))); 
    
    assert(inserted.second);
}
 
template <typename Resource, typename Identifier>
Resource &ResourceManager<Resource, Identifier>::getResourceById(Identifier ID)
{
    auto found = mResourceMap.find(ID);
    if (found == mResourceMap.end()) {
        
        throw std::runtime_error("Resource not found with the provided ID ");
    }
    return *found->second; 
}

template <typename Resource, typename Identifier>
const int ResourceManager<Resource, Identifier>::resourseSize() const
{
    return mResourceMap.size();
}

#endif // RESOURCEMANAGER_CPP