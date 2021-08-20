#include "ResourceManager.h"
#include <filesystem>

Resource* ResourceManager::createResourceFromFile(const wchar_t* file_path)
{
    std::wstring fullPath = std::filesystem::absolute(file_path);

    auto it = m_map_resources.find(fullPath);

    if (it != m_map_resources.end())
    {
        return it->second;
    }

    Resource* res = this->createResourceFromFileConcrete(fullPath.c_str());

    if (res)
    {
        m_map_resources[fullPath] = res;
        return res;
    }
    return nullptr;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
