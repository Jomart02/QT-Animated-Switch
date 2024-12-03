#include "ToggleSwitchPlugin.h"

ToggleSwitchPlugin::ToggleSwitchPlugin(QObject *parent)    : QObject(parent){

}

bool ToggleSwitchPlugin::isContainer() const {
    return false;
};
bool ToggleSwitchPlugin::isInitialized() const {
    return initialized;
};
QIcon ToggleSwitchPlugin::icon() const {
    return QIcon();
};
QString ToggleSwitchPlugin::domXml() const {
    return QLatin1String("<ui language=\"c++\"><widget class=\"ToggleSwitch\" name=\"Switch\"><property name=\"geometry\"><rect><x>0</x><y>0</y><width>100</width><height>50</height></rect></property>");
};
QString ToggleSwitchPlugin::group() const {
    return QLatin1String("Buttons [Examples]");
};
QString ToggleSwitchPlugin::includeFile() const {
    return QLatin1String("ToggleSwitch.hpp");
};
QString ToggleSwitchPlugin::name() const {
    return QLatin1String("ToggleSwitch");
}
QString ToggleSwitchPlugin::toolTip() const {
    return {};
};
QString ToggleSwitchPlugin::whatsThis() const {
    return {};
};
QWidget *ToggleSwitchPlugin::createWidget(QWidget *parent) {
    return new ToggleSwitch(parent);
};
void ToggleSwitchPlugin::initialize(QDesignerFormEditorInterface *core) {
    if (initialized)
        return;

    initialized = true;
};
