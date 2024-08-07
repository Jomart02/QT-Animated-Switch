#include "TestWindow.h"
#include "ui_TestWindow.h"


TestWindow::TestWindow(QWidget *parent) : QWidget(parent) , ui(new Ui::TestWindow){
    ui->setupUi(this);
   
}
TestWindow::~TestWindow()
{
    delete ui;
}
