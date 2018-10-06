#include "mainwindow.h"
#include "ui_mainwindow.h"
// hello
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // zUL.play();

    btn = new QPushButton("BUTTON", this);
    btn->setGeometry(
                QRect(
                    QPoint(100, 100),
                    QSize(100, 100)
                    ));
    btn->connect(btn, SIGNAL(released()), this, SLOT(btn_onclick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_onclick()
{
    zUL.teleport();
    string message = zUL.getCurrentRoom();
    QString m = QString::fromStdString(message);
    QMessageBox messageBox(this);
    messageBox.about(this, "Current Room", m);
}
