#include "ToggleSwitchPlugin.h"
#include "ToggleSwitch.h"

ToggleSwitchPlugin::ToggleSwitchPlugin(QObject *parent) : QObject(parent){
    Q_INIT_RESOURCE(res);
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
    QFile File(":/xml/switchxml");
    bool opened = File.open(QFile::ReadOnly);

    if(opened){
        qDebug() << "opem";
        QString xml = File.readAll();
        return QString(xml);
    }else{
        return QString("<ui language=\"c++\"><widget class=\"ToggleSwitch\" name=\"Switch\"><property name=\"geometry\"><rect><x>0</x><y>0</y><width>100</width><height>24</height></rect></property></widget></ui>");
    }


};
QString ToggleSwitchPlugin::group() const {
    return QString("Buttons");
};
QString ToggleSwitchPlugin::includeFile() const {
    return QString("ToggleSwitch.h");
};
QString ToggleSwitchPlugin::name() const {
    return QString("ToggleSwitch");
}
QString ToggleSwitchPlugin::toolTip() const {
    return QString("");
};
QString ToggleSwitchPlugin::whatsThis() const {
    return QString("");
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