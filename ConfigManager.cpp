
#include "ConfigManager.h"
#include "logging.h"

static std::string configFilePath;

FB::VariantMap ConfigManager::defaultConfig;

void ConfigManager::setPath(const std::string& path) {
    configFilePath = path;
}
void ConfigManager::setDefaultConfig(const FB::VariantMap& defMap) {
    ConfigManager::defaultConfig = defMap;
}

void ConfigManager::initConfigFile() {
    configMap = ConfigManager::defaultConfig;
    saveConfig();
}

void ConfigManager::initConfig() {
    try {
        configMap = loadConfigMap(configFilePath);
    } catch (...) {
        // if we can't parse the document, throw the values out
        FBLOG_WARN("ConfigManager", "Could not read document from " << configFilePath);
        initConfigFile();
    }
}

void ConfigManager::saveConfig() {
    saveConfigMap(configFilePath, configMap);
}
