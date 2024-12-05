#pragma once

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QObject>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QFile>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT ToggleSwitch : public QWidget
{
        Q_OBJECT
        Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
        Q_PROPERTY(double sliderPos READ getSliderPos WRITE setSliderPos)
        Q_PROPERTY(double colorHover READ getcolorHover WRITE setcolorHover)
        Q_PROPERTY(QColor colorSwitch READ getcolorSwitch WRITE setcolorSwitch)

        Q_PROPERTY(double maxOpacity READ getmaxOpacity WRITE setmaxOpacity)
        Q_PROPERTY(double minOpacity READ getmaxOpacity WRITE setmaxOpacity)
        Q_PROPERTY(double maxHoverOpacity READ getmaxHoverOpacity WRITE setmaxHoverOpacity)

        Q_PROPERTY(double maxcolorHover READ getmaxcolorHover WRITE setmaxcolorHover)
        Q_PROPERTY(double mincolorHover READ getmincolorHover WRITE setmincolorHover)
        
        Q_PROPERTY(int durationToggledHovered READ getDurationToggledHovered WRITE setDurationToggledHovered)
        Q_PROPERTY(int durationUnToggledHovered READ getDurationUnToggledHovered WRITE setDurationUnToggledHovered)
        Q_PROPERTY(int durationToggledHovered_opacity READ getDurationToggledHovered_opacity WRITE setDurationToggledHovered_opacity)
        Q_PROPERTY(int durationToggledProcces_opacity READ getDurationToggledProcces_opacity  WRITE setDurationToggledProcces_opacity )
        Q_PROPERTY(int durationToggledProcces_sliderPos READ getDurationToggledProcces_sliderPos WRITE setDurationToggledProcces_sliderPos)
        Q_PROPERTY(bool toggled READ isToggled WRITE setToggled NOTIFY toggledChanged)
    
    public:
        explicit ToggleSwitch(QWidget* parent = nullptr);
        ~ToggleSwitch();

        bool isToggled() const;

    public slots:
        void setToggled(bool toggled);

        void setSize(int width, int height);

    signals:
        void toggledChanged(bool toggled);

    protected:
        QSize sizeHint() const override;
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        /// @brief Наведение на виджет
        /// @param event
        void enterEvent(QEnterEvent* event) override;
        /// @brief Отведение с виджета
        /// @param event
        void leaveEvent(QEvent* event) override;

        void resizeEvent(QResizeEvent* event) override;
    public:

        double getOpacity() const;
        void setOpacity(double background);
        int getSliderPos() const;
        void setSliderPos(int slider);
        double getcolorHover();
        void setcolorHover(double colorHover);

        QColor getcolorSwitch();
        void setcolorSwitch(QColor colorSwitch);

        double getmaxOpacity();
        void setmaxOpacity(double maxOpacity);

        double getminOpacity();
        void setminOpacity(double minOpacity);
        double getmaxHoverOpacity();
        void setmaxHoverOpacity(double maxHoverOpacity);
        double getmaxcolorHover();
        void setmaxcolorHover(double maxcolorHover);
        
        double getmincolorHover();
        void setmincolorHover(double mincolorHover);

///================================================================

        int getDurationToggledHovered();
        void setDurationToggledHovered(int durationToggledHovered);

        int getDurationUnToggledHovered();
        void setDurationUnToggledHovered(int durationUnToggledHovered);

        int getDurationToggledProcces_opacity();
        void setDurationToggledProcces_opacity(int durationToggledProcces_opacity);

        int getDurationToggledProcces_sliderPos();
        void setDurationToggledProcces_sliderPos(int durationToggledProcces_sliderPos);

        int getDurationToggledHovered_opacity();
        void setDurationToggledHovered_opacity(int durationToggledHovered_opacity);

    private:
        void startAnimation();
        void startHoverAnimation();
    private:
        double opacity = 0;
        int slider = 5;
        bool m_toggled = false;
        bool hovered = false;

        //Параметры цветовой палитры
        double colorHover = 180;
        QColor colorSwitch = QColor(65, 80, 180,0);
        double maxOpacity = 255;
        double minOpacity = 0;
        double maxcolorHover = 222;
        double mincolorHover = 180;
        double maxHoverOpacity = 50;

        //Параметры скорости анимаций
        int durationToggledHovered = 120; // Скорость анимации наводки при наведении в включенном режиме
        int durationUnToggledHovered = 20;// Скорость анимации наводки при наведении в выключенном режиме
        int durationToggledHovered_opacity = 120;

        int durationToggledProcces_opacity = 300; // Скорость анимации отрисовки прозрачности при нажатии на свитч
        int durationToggledProcces_sliderPos = 300; // Скорость анимации перемещения слайдера при нажатии на свитч
};