#pragma once

#include <QWidget>

namespace Ui { class TestWindow; }

class TestWindow : public QWidget{
    Q_OBJECT

public:
    TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
};

