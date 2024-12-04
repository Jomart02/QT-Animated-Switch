#include "ToggleSwitchPlugin.h"
#include "ToggleSwitch.h"

ToggleSwitchPlugin::ToggleSwitchPlugin(QObject *parent) : QObject(parent){
    initialized = false;
}

bool ToggleSwitchPlugin::isContainer() const {
    return false;
};
bool ToggleSwitchPlugin::isInitialized() const {
    return initialized;
};
QIcon ToggleSwitchPlugin::icon() const {
    return QIcon(":/icon/switch");
};
QString ToggleSwitchPlugin::domXml() const {
    return QString("<ui language=\"c++\"><widget class=\"ToggleSwitch\" name=\"ToggleSwitch\"><header>ToggleSwitch.h</header><property name=\"geometry\"><rect><x>0</x><y>0</y><width>100</width><height>24</height></rect></property></widget></ui>");

};
QString ToggleSwitchPlugin::group() const {
    return QLatin1String("Buttons");
};
QString ToggleSwitchPlugin::includeFile() const {
    return QString("ToggleSwitch.h");
};
QString ToggleSwitchPlugin::name() const {
    return QLatin1String("ToggleSwitch");
}
QString ToggleSwitchPlugin::toolTip() const {
    return QLatin1String("");
};
QString ToggleSwitchPlugin::whatsThis() const {
    return QLatin1String("");
};
QWidget *ToggleSwitchPlugin::createWidget(QWidget *parent) {
    return new ToggleSwitch(parent);
};
void ToggleSwitchPlugin::initialize(QDesignerFormEditorInterface *core) {
    if (initialized)
        return;

    initialized = true;
};

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ToggleSwitch, ToggleSwitchPlugin)
#endif // QT_VERSION < 0x050000