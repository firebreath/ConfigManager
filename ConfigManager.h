#ifndef ConfigManager_h__
#define ConfigManager_h__

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "APITypes.h"

class ConfigManager
{
public:
    static void setPath(const std::string& path);
    static void setDefaultConfig(const FB::VariantMap& defMap);

    template<typename T>
    T getValue(const std::string& key) {
        return configMap[key].convert_cast<T>();
    }
    
    template<typename T>
    void setValue(const std::string& key, const T& val) {
        configMap[key] = val;
        saveConfig();
    }
    
protected:
    ConfigManager() {}
    virtual ~ConfigManager() {}
    
    void initConfigFile();
    virtual void saveConfigMap(const std::string& filePath, const FB::VariantMap& map) = 0;
    virtual FB::VariantMap loadConfigMap(const std::string& filePath) = 0;
    
    void saveConfig();
    void initConfig();
    
    FB::VariantMap configMap;
    static FB::VariantMap defaultConfig;
};

#endif // ConfigManager_h__
