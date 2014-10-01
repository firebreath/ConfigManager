
#include "ConfigManager.h"
#include "logging.h"
#include "global/config.h"

static std::string configFilePath;

FB::VariantMap ConfigManager::defaultConfig;

void ConfigManager::setPath(const std::string& path) {
    configFilePath = path;
}
void ConfigManager::setDefaultConfig(const FB::VariantMap& defMap) {
    ConfigManager::defaultConfig = defMap;
}

ConfigManager::ConfigManager() {
    try {
        FB::variant doc = FB::loadYamlFileToVariant(filename);
        configMap = doc.convert_cast<FB::VariantMap>();
    } catch (const FB::bad_variant_cast &) {
        // if we can't parse the document, throw the values out
        FBLOG_WARN("ConfigManager", "Could not read YAML document from " << filename);
        configMap = ConfigManager::defaultConfig;
        setStringValue("CreatedByVersion", FBSTRING_PLUGIN_VERSION);
    }
}

void ConfigManager::initConfigFile() {
    configMap = ConfigManager::defaultConfig;
    setValue("CreatedByVersion", FBSTRING_PLUGIN_VERSION);
    saveConfig();
}

void ConfigManager::initConfig() {
    try {
        configMap = loadConfigMap(configFilePath);
    } catch (const FB::bad_variant_cast &) {
        // if we can't parse the document, throw the values out
        FBLOG_WARN("ConfigManager", "Could not read YAML document from " << filename);
        initConfigFile();
    }
}

void ConfigManager::saveConfig() {
    saveConfigMap(configFilePath, configMap);
}

virtual ConfigManager::~ConfigManager() {
}