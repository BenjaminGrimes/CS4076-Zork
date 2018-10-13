#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // zUL.play();
    grid = new QGridLayout;
    // these are temp cells for groups
    grid->addWidget(createImageGroup(), 0, 0);
    grid->addWidget(createMapGroup(), 0, 1);
    grid->addWidget(createStoryGroup(), 1, 0);
    grid->addWidget(createPlayerInfoGroup(), 1, 1);
    grid->addWidget(createInventoryGroup(), 2, 0);
    grid->addWidget(createNavigationGroup(), 2,1);

    // need to set central widget to display layout
    auto central = new QWidget;
    central->setLayout(grid);
    setCentralWidget(central);

    /*
    setUpLayout();
    setUpButtons();
    setUpLabels();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox* MainWindow::createImageGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Image Group"));
    QLabel *label = new QLabel;
    label->setText("IMAGE");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createMapGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Map Group"));
    QLabel *label = new QLabel;
    label->setText("MAP");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createStoryGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Story Group"));
    QLabel *label = new QLabel;
    label->setText("STORY");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createPlayerInfoGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Player Info Group"));
    QLabel *label = new QLabel;
    label->setText("PLAYER INFO");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createInventoryGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Inventory Group"));
    QLabel *label = new QLabel;
    label->setText("INVENTORY");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createNavigationGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Navigation Group"));
    QLabel *label = new QLabel;
    label->setText("NAVIGATION");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    groupBox->setLayout(vbox);
    return groupBox;
}

void MainWindow::setUpLayout()
{
    layout = new QGridLayout;
}

void MainWindow::setUpButtons ()
{
    btn = new QPushButton("Teleport", this);
    //btn->setGeometry(QRect(QPoint(100, 100),QSize(100, 100)));
    btn->connect(btn, SIGNAL(released()), this, SLOT(teleport_btn_onclick()));

    north_btn = new QPushButton("North", this);
    //north_btn->setGeometry(QRect(QPoint(500, 400), QSize(100, 100)));
    north_btn->connect(north_btn, SIGNAL(released()), this, SLOT(north_btn_onclick()));

    south_btn = new QPushButton("South", this);
    //south_btn->setGeometry(QRect(QPoint(500, 600), QSize(100, 100)));
    south_btn->connect(south_btn, SIGNAL(released()), this, SLOT(south_btn_onclick()));

    east_btn = new QPushButton("East", this);
    //east_btn->setGeometry(QRect(QPoint(600, 500), QSize(100, 100)));
    east_btn->connect(east_btn, SIGNAL(released()), this, SLOT(east_btn_onclick()));

    west_btn = new QPushButton("West", this);
    //west_btn->setGeometry(QRect(QPoint(400, 500), QSize(100, 100)));
    west_btn->connect(west_btn, SIGNAL(released()), this, SLOT(west_btn_onclick()));
}

void MainWindow::setUpLabels()
{
    current_room_label = new QLabel(this);
    //current_room_label->setGeometry(QRect(QPoint(200, 200), QSize(200, 50)));
    updateRoomLabel();
}

void MainWindow::updateRoomLabel()
{
    string temp = zUL.getCurrentRoom();
    QString c_room = QString::fromStdString(temp);
    current_room_label->setText("Current Room: " + c_room);
}

void MainWindow::teleport_btn_onclick()
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

    updateRoomLabel();
    //QMessageBox mBox(this);
    //QString mBox_title = "Current Room";
    //mBox.about(this, mBox_title, message);
}
