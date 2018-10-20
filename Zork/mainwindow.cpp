#include "mainwindow.h"
#include "ui_mainwindow.h"
// test 2
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // zUL.play();

    setUpLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpLayout()
{
    grid = new QGridLayout;
    // these are temp cells for groups
    grid->addWidget(createImageGroup(), 0, 0, 1, 2);
    grid->addWidget(createMapGroup(), 0, 2, 2, 1);
    grid->addWidget(createStoryGroup(), 1, 0, 1, 2);
    grid->addWidget(createPlayerInfoGroup(), 3, 0);
    grid->addWidget(createInventoryGroup(), 3, 1);
    grid->addWidget(createNavigationGroup(), 3,2);

    // need to set central widget to display layout
    auto central = new QWidget;
    central->setLayout(grid);
    setCentralWidget(central);

    createActions();
    createMenus();

    updateRoomLabel();
    updateStoryText();
    updateNavButtons();
}

void MainWindow::createActions()
{
    restartAct = new QAction(tr("Restart"), this);
    restartAct->setShortcuts(QKeySequence::New); //What does this do?
    restartAct->setStatusTip(tr("Restart the game"));
    connect(restartAct, &QAction::triggered, this, &MainWindow::restart);

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the game"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(restartAct);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAct);
}

void MainWindow::restart()
{
    cout << "Restarting..." << endl;
}

QGroupBox* MainWindow::createImageGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Image Group"));
    QLabel *label = new QLabel;
    label->setText("IMAGE");
    QVBoxLayout *vbox = new QVBoxLayout;
    //vbox->addWidget(label);

    QLabel *imageLabel = new QLabel;
    QImage image(":/TestImage1.jpg");
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(100, 100, Qt::KeepAspectRatio));

    vbox->addWidget(imageLabel);

    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createMapGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Map Group"));
    QLabel *label = new QLabel;
    label->setText("MAP");
    QVBoxLayout *vbox = new QVBoxLayout;
    //vbox->addWidget(label);


    QLabel *imageLabel = new QLabel;
    QImage image(":/TestImage2.jpg");
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(100, 100, Qt::KeepAspectRatio));

    vbox->addWidget(imageLabel);

    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox* MainWindow::createStoryGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Story Group"));
    QLabel *label = new QLabel;
    label->setText("STORY");

    story_text_browser = new QTextBrowser;
    story_text_browser->append("Some text");


    QGridLayout *story_grid = new QGridLayout;
    story_grid->addWidget(story_text_browser, 0, 0, 2, 2);
    story_grid->addWidget(label, 0, 2, 2, 1);

    story_text_browser->append("Some more text");

    groupBox->setLayout(story_grid);
    return groupBox;
}

QGroupBox* MainWindow::createPlayerInfoGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Player Info Group"));
    QLabel *label = new QLabel;
    label->setText("Health");

    player_health_bar = new QProgressBar;
    player_health_bar->setRange(0, 100);
    player_health_bar->setValue(50);

    health_status_bar = new QStatusBar;
    health_status_bar->addPermanentWidget(label, 1);
    health_status_bar->addPermanentWidget(player_health_bar, 4);

    QGridLayout *p_info_grid = new QGridLayout;
    //p_info_grid->addWidget(label, 0, 0, 1, 1);
    p_info_grid->addWidget(health_status_bar, 0, 0, 2, 2 );

    groupBox->setLayout(p_info_grid);
    return groupBox;
}

QGroupBox* MainWindow::createInventoryGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Inventory Group"));

    QRadioButton *radio1 = new QRadioButton(tr("Item 1"));
    QRadioButton *radio2 = new QRadioButton(tr("Item 2"));
    QRadioButton *radio3 = new QRadioButton(tr("Item 3"));

    radio1->setChecked(true);

    listWidget = new QListWidget(this);
    QListWidgetItem *it;
    it = new QListWidgetItem(listWidget);
    listWidget->setItemWidget(it, radio1);

    it = new QListWidgetItem(listWidget);
    listWidget->setItemWidget(it, radio2);

    it = new QListWidgetItem(listWidget);
    listWidget->setItemWidget(it, radio3);

    use_item_btn = new QPushButton("Use item", this);
    use_item_btn->connect(use_item_btn, SIGNAL(released()), this, SLOT(use_item_btn_onclick()));

    QGridLayout *inv_grid = new QGridLayout;

    inv_grid->addWidget(listWidget, 0, 0, 2, 2);
    inv_grid->addWidget(use_item_btn, 2, 0, 2, 2);

    groupBox->setLayout(inv_grid);

    return groupBox;
}

QGroupBox* MainWindow::createNavigationGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Navigation Group"));

    current_room_label = new QLabel(this);

    teleport_btn = new QPushButton("Teleport", this);
    teleport_btn->connect(teleport_btn, SIGNAL(released()), this, SLOT(teleport_btn_onclick()));

    north_btn = new QPushButton("North", this);
    north_btn->connect(north_btn, SIGNAL(released()), this, SLOT(north_btn_onclick()));

    south_btn = new QPushButton("South", this);
    south_btn->connect(south_btn, SIGNAL(released()), this, SLOT(south_btn_onclick()));

    east_btn = new QPushButton("East", this);
    east_btn->connect(east_btn, SIGNAL(released()), this, SLOT(east_btn_onclick()));

    west_btn = new QPushButton("West", this);
    west_btn->connect(west_btn, SIGNAL(released()), this, SLOT(west_btn_onclick()));

    QGridLayout *nav_grid = new QGridLayout;
    nav_grid->addWidget(current_room_label, 0, 0);
    nav_grid->addWidget(north_btn, 0, 1);
    nav_grid->addWidget(west_btn, 1, 0);
    nav_grid->addWidget(teleport_btn, 1, 1);
    nav_grid->addWidget(east_btn, 1, 2);
    nav_grid->addWidget(south_btn, 2, 1);
    groupBox->setLayout(nav_grid);
    return groupBox;
}

void MainWindow::updateNavButtons()
{
    teleport_btn->setEnabled(false);

    vector<bool>exits = zUL.currentRoom->getExits();

    if(!exits[0])
    {
        north_btn->setEnabled(false);
        north_btn->setToolTip("No north exit");
    }
    else
    {
        north_btn->setEnabled(true);
        north_btn->setToolTip("");
    }

    if(!exits[1])
    {
        east_btn->setEnabled(false);
        east_btn->setToolTip("No east exit");
    }
    else
    {
        east_btn->setEnabled(true);
        east_btn->setToolTip("");
    }

    if(!exits[2])
    {
        south_btn->setEnabled(false);
        south_btn->setToolTip("No south exit");
    }
    else
    {
        south_btn->setEnabled(true);
        south_btn->setToolTip("");
    }
    if(!exits[3])
    {
        west_btn->setEnabled(false);
        west_btn->setToolTip("No west exit");
    }
    else
    {
        west_btn->setEnabled(true);
        west_btn->setToolTip("");
    }

    if(!exits[4])
    {
        teleport_btn->setEnabled(false);
        teleport_btn->setToolTip("Teleport unavailable");
    }
    else
    {
        teleport_btn->setEnabled(true);
        teleport_btn->setToolTip("");
    }
}

void MainWindow::updateRoomLabel()
{
    string temp = zUL.getCurrentRoom();
    QString c_room = QString::fromStdString(temp);
    current_room_label->setText("Current Room: " + c_room);
}

void MainWindow::updateStoryText()
{
    story_text_browser->append(QString::fromStdString(zUL.getCurrentRoomDescription()));
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

void MainWindow::use_item_btn_onclick()
{
    // TODO remove item from room, play in player inventory
    QListWidgetItem *item = listWidget->currentItem();
    delete listWidget->takeItem(listWidget->row(item));

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
    updateStoryText();
    updateNavButtons();
    //QMessageBox mBox(this);
    //QString mBox_title = "Current Room";
    //mBox.about(this, mBox_title, message);
}
