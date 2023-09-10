#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <cassert>
#include "Utills.hpp"


template<typename Resource, typename Identifier>
class ResourceManager                       
{
    public:
        void load(Identifier ID, const std::string& filename); // Loads a resource from a file.
        Resource& getResourceById(Identifier ID); 
        const int resourseSize() const; // Returns the size of the resource map.
        
    
    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
        //std::unordered_map<std::string, std::pair<Resource*, unsigned int>>mResources;
};
#include "ResourceManager.cpp"
#endif // RESOURCEHANDLER_H