#include "mainwindow.h"
#include "ui_mainwindow.h"

// hello
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // zUL.play();

    setUpButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpButtons ()
{
    btn = new QPushButton("BUTTON", this);
    btn->setGeometry(QRect(QPoint(100, 100),QSize(100, 100)));
    btn->connect(btn, SIGNAL(released()), this, SLOT(btn_onclick()));

    north_btn = new QPushButton("North", this);
    north_btn->setGeometry(QRect(QPoint(500, 400), QSize(100, 100)));
    north_btn->connect(north_btn, SIGNAL(released()), this, SLOT(north_btn_onclick()));

    south_btn = new QPushButton("South", this);
    south_btn->setGeometry(QRect(QPoint(500, 600), QSize(100, 100)));
    south_btn->connect(south_btn, SIGNAL(released()), this, SLOT(south_btn_onclick()));

    east_btn = new QPushButton("East", this);
    east_btn->setGeometry(QRect(QPoint(600, 500), QSize(100, 100)));
    east_btn->connect(east_btn, SIGNAL(released()), this, SLOT(east_btn_onclick()));

    west_btn = new QPushButton("West", this);
    west_btn->setGeometry(QRect(QPoint(400, 500), QSize(100, 100)));
    west_btn->connect(west_btn, SIGNAL(released()), this, SLOT(west_btn_onclick()));
}

void MainWindow::btn_onclick()
{
    zUL.teleport();
    string message = zUL.getCurrentRoom();
    QString m = QString::fromStdString(message);
    QMessageBox messageBox(this);
    messageBox.about(this, "Current Room", m);
}

void MainWindow::north_btn_onclick()
{
    QString direction = north_btn->text();
    goDirection(direction);
}

void MainWindow::south_btn_onclick()
{
    QString direction = south_btn->text();
    goDirection(direction);
}

void MainWindow::east_btn_onclick()
{
    QString direction = east_btn->text();
    goDirection(direction);
}

void MainWindow::west_btn_onclick()
{
    QString direction = west_btn->text();
    goDirection(direction);
}

void MainWindow::goDirection(QString direction)
{
    direction = direction.toLower();
    string response = zUL.go(direction.toStdString());

    QString message;
    if(response == "ERROR")
    {
        message = "Can't go " + direction;
    }
    else
    {
        message = QString::fromStdString(zUL.getCurrentRoom());
    }

    QMessageBox mBox(this);
    QString mBox_title = "Current Room";
    mBox.about(this, mBox_title, message);
}
