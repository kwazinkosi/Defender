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

/**
 * @brief 
 * 
 * @tparam Resource 
 * @tparam Identifier 
 */
template<typename Resource, typename Identifier>
class ResourceManager                       
{
    public:
    /**
     * @brief  Loads a resource from a file.
     * 
     * @param ID 
     * @param filename 
     */
        void load(Identifier ID, const std::string& filename); // Loads a resource from a file.
        /**
         * @brief Get the Resource By Id object
         * 
         * @param ID 
         * @return Resource& 
         */
        Resource& getResourceById(Identifier ID); 
        /**
         * @brief  Get the Resource By Id object
         * 
         * @return const int 
         */
        const int resourseSize() const; // Returns the size of the resource map.
        
    
    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
        //std::unordered_map<std::string, std::pair<Resource*, unsigned int>>mResources;
};
#include "ResourceManager.cpp"
#endif // RESOURCEHANDLER_H