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
class ToggleSwitch : public QWidget
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
        
    public:
        ToggleSwitch(QWidget* parent = nullptr) : QWidget(parent), m_toggled(false)
        {
            // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Установим политику изменения размеров виджета
            //  resize(parent->size()); // Установка начального размера равным размеру родительского виджета
            setMouseTracking(true);
            Q_INIT_RESOURCE(Switch);

            QFile styleFile(":/style/StyleSwitch");
            bool opened = styleFile.open(QFile::ReadOnly);
            QString styleContent = styleFile.readAll();
            setStyleSheet(styleContent);
        }

        void paintEvent(QPaintEvent* event) override
        {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            // Отображение тени
            QPainterPath path;

            path.addRoundedRect(rect().adjusted(3, 3, -3, -3), height() / 2, height() / 2); // Здесь мы создаем скругленный прямоугольник с небольшим смещением
            QColor shadowColor = QColor(0, 0, 0, 50); // Цвет и прозрачность тени
            painter.fillPath(path, shadowColor);


            // Swhitch
            painter.setPen(Qt::NoPen);  // Добавить обводку можно тут
            colorSwitch.setBlue(colorHover);
            qDebug() << colorHover;
            colorSwitch.setAlpha(opacity);
            painter.setBrush(colorSwitch);

            // painter.setBrush(m_toggled ? QColor("#4150DE") : QColor("#CECECE"));
            painter.drawRoundedRect(rect(), height() / 2, height() / 2);

            // Slider
            int sliderSize = height() - 10;
            int sliderX = slider;
            painter.setBrush(Qt::white);
            painter.drawEllipse(sliderX, 5, sliderSize, sliderSize);
        }

        void mousePressEvent(QMouseEvent* event) override
        {
            if(event->button() == Qt::LeftButton) {
                m_toggled = !m_toggled;
                // update();
                startAnimation();
                emit toggledChanged(m_toggled);
            }
        }


        bool isToggled() const
        {
            return m_toggled;
        }

        QSize sizeHint() const override
        {
            return QSize(50, 30);
        }

    public slots:
        void setToggled(bool toggled)
        {
            if(m_toggled != toggled) {
                m_toggled = toggled;
                update();

                emit toggledChanged(m_toggled);
            }
        }

        void setSize(int width, int height)
        {
            setFixedSize(width, height);
        }

    signals:
        void toggledChanged(bool toggled);

    protected:
        /// @brief Наведение на виджет
        /// @param event
        void enterEvent(QEnterEvent* event) override
        {
            hovered = true;
            startHoverAnimation();
        }
        /// @brief Отведение с виджета
        /// @param event
        void leaveEvent(QEvent* event) override
        {
            hovered = false;
            startHoverAnimation();
        }

        void resizeEvent(QResizeEvent* event) override
        {
            update();  // Обновляем виджет при изменении его размеров
        }
    private:

        void startAnimation()
        {

            QPropertyAnimation* ani = new QPropertyAnimation(this, "opacity");
            if(m_toggled) {
                ani->setStartValue(minOpacity);
                ani->setEndValue(maxOpacity);
            } else {
                ani->setStartValue(maxOpacity);
                ani->setEndValue(minOpacity);
            }

            ani->setDuration(300);
            connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
            connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
            ani->start();

            QPropertyAnimation* ani2 = new QPropertyAnimation(this, "sliderPos");
            if(m_toggled) {
                ani2->setStartValue(5);
                ani2->setEndValue(width() - (height() - 10) - 5);
            } else {
                ani2->setStartValue(width() - (height() - 10) - 5);
                ani2->setEndValue(5);
            }

            ani2->setDuration(200);
            connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
            connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
            ani2->start();

        }

        void startHoverAnimation()
        {

            if(m_toggled) {
                QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");
                if(hovered) {
                    ani->setStartValue(mincolorHover);
                    ani->setEndValue(maxcolorHover);
                } else {
                    ani->setStartValue(maxcolorHover);
                    ani->setEndValue(mincolorHover);
                }
                ani->setDuration(120);
                connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
                connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
                ani->start();
            } else {
                QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");

                if(hovered) {
                    ani->setStartValue(mincolorHover);
                    ani->setEndValue(maxcolorHover);
                } else {
                    ani->setStartValue(maxcolorHover);
                    ani->setEndValue(mincolorHover);
                }

                ani->setDuration(20);
                connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
                connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));


                QPropertyAnimation* ani2 = new QPropertyAnimation(this, "opacity");
                if(hovered) {
                    ani2->setStartValue(0);
                    ani2->setEndValue(maxHoverOpacity);
                } else {
                    ani2->setStartValue(maxHoverOpacity);
                    ani2->setEndValue(0);
                }

                ani->setDuration(120);
                connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
                connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
                ani->start();
                ani2->start();
            }


        }


        double getOpacity() const
        {
            return opacity;
        }
        void setOpacity(double background)
        {
            this->opacity = background;
            update();
        }
        int getSliderPos() const
        {
            return slider;
        }
        void setSliderPos(int slider)
        {
            this->slider = slider;
            update();
        }
        double getcolorHover()
        {
            return colorHover;
        }
        void setcolorHover(double colorHover)
        {
            this->colorHover = colorHover;
            update();
        }

        QColor getcolorSwitch()
        {
            return colorSwitch;
        }
        void setcolorSwitch(QColor colorSwitch)
        {
            this->colorSwitch = colorSwitch;
            update();
        }

        double getmaxOpacity()
        {
            return maxOpacity;
        }
        void setmaxOpacity(double maxOpacity)
        {
            this->maxOpacity = maxOpacity;
            update();
        }

        double getminOpacity()
        {
            return minOpacity;
        }
        void setminOpacity(double minOpacity)
        {
            this->minOpacity = minOpacity;
            update();
        }
        double getmaxHoverOpacity()
        {
            return maxHoverOpacity;
        }
        void setmaxHoverOpacity(double maxHoverOpacity)
        {
            this->maxHoverOpacity = maxHoverOpacity;
            update();
        }
        double getmaxcolorHover()
        {
            return maxcolorHover;
        }
        void setmaxcolorHover(double maxcolorHover)
        {
            this->maxcolorHover = maxcolorHover;
            update();
        }
        double getmincolorHover()
        {
            return mincolorHover;
        }
        void setmincolorHover(double mincolorHover)
        {
            this->mincolorHover = mincolorHover;
            update();
        }
    private:
        double opacity = 0;
        int slider = 5;
        bool m_toggled;
        bool hovered = false;
        double colorHover = 0;
        QColor colorSwitch = QColor(65, 80, 255,100);


        double maxOpacity = 255;
        double minOpacity = 0;
        double maxcolorHover = 50;
        double mincolorHover = 0;
        double maxHoverOpacity = 50;
};