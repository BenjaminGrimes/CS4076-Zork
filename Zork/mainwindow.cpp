#include "mainwindow.h"
#include "ui_mainwindow.h"

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // zUL.play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpLayout()
{
    grid = new QGridLayout;
    // these are temp cells for groups
    //grid->addWidget(createImageGroup(), 0, 0, 1, 2);
    grid->addWidget(createStoryGroup(), 0, 0, 2, 2);
    grid->addWidget(createMapGroup(), 0, 2, 2, 1);
    grid->addWidget(createPlayerInfoGroup(), 3, 0);
    grid->addWidget(createInventoryGroup(), 3, 1);
    grid->addWidget(createNavigationGroup(), 3,2);

    // need to set central widget to display layout
    auto central = new QWidget;
    central->setLayout(grid);
    setCentralWidget(central);

    createActions();

    updateRoomLabel();
    updateStoryText();
    updateNavButtons();
    updateRoomItems();
    updateCombatField();
}

void MainWindow::createActions()
{
    gameMenu = menuBar()->addMenu(tr("Game"));
    QToolBar *gameToolBar = addToolBar(tr("Game"));
    // Temp image
    const QIcon restartIcon = QIcon::fromTheme("document-restart", QIcon(":/restart.png"));
    restartAct = new QAction(restartIcon, tr("Restart"), this);
    restartAct->setShortcut((QKeySequence::New));
    restartAct->setStatusTip("Restart the game");
    //connect(restartAct, &QAction::triggered, this, &MainWindow::restart);
    gameMenu->addAction(restartAct);
    gameToolBar->addAction(restartAct);

    // Temp image
    const QIcon exitIcon = QIcon::fromTheme("document-exit", QIcon(":/exit.png"));
    exitAct = new QAction(exitIcon, tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the game"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
    gameMenu->addAction(exitAct);
    gameToolBar->addAction(exitAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

QGroupBox* MainWindow::createMapGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Map"));
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
    QGroupBox *groupBox = new QGroupBox(tr("Story"));

    story_text_browser = new QTextBrowser;

    combat_container = new QVBoxLayout;

    QLabel *enemy_health_label = new QLabel("Enemy Health:", this);

    enemy_name_label = new QLabel("Enemy Name:", this);
    enemy_health_bar = new QProgressBar(this);
    enemy_health_bar->setRange(0, 100);
    enemy_health_bar->setValue(50);

    enemy_status_bar = new QStatusBar(this);
    enemy_status_bar->addPermanentWidget(enemy_health_label, 1);
    enemy_status_bar->addPermanentWidget(enemy_health_bar, 4);

    use_sword_radio = new QRadioButton("Attack using weapon", this);
    use_magic_radio = new QRadioButton("Attack using magic", this);
    use_sword_radio->setChecked(true);

    combat_container->addWidget(enemy_name_label);
    combat_container->addWidget(enemy_status_bar);
    combat_container->addWidget(use_sword_radio);
    combat_container->addWidget(use_magic_radio);

    attack_btn = new QPushButton("Attack", this);
    connect(attack_btn, SIGNAL(released()), this, SLOT(attack_btn_onclick()));

    room_items_container = new QVBoxLayout;

    take_item_btn = new QPushButton("Take item(s)", this);
    connect(take_item_btn, SIGNAL(released()), this, SLOT(take_item_btn_onclick()));

    QGridLayout *story_grid = new QGridLayout;
    story_grid->addWidget(story_text_browser, 0, 0, 2, 3);
    story_grid->addLayout(combat_container, 2, 0, 2, 2);
    story_grid->addWidget(attack_btn, 4, 0, 1, 2);
    story_grid->addLayout(room_items_container, 2, 2, 2, 1);
    story_grid->addWidget(take_item_btn, 4, 2, 1, 1);

    groupBox->setLayout(story_grid);
    return groupBox;
}

QGroupBox* MainWindow::createPlayerInfoGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Player Info"));
    QLabel *label = new QLabel;
    label->setText("Health:");

    player_health_bar = new QProgressBar;
    player_health_bar->setRange(0, 100);
    player_health_bar->setValue(zUL.player.getHealth());

    health_status_bar = new QStatusBar;
    health_status_bar->addPermanentWidget(label, 1);
    health_status_bar->addPermanentWidget(player_health_bar, 4);

    QLabel *name_title_label = new QLabel;
    name_title_label->setText("Name:");
    QLabel *name_label = new QLabel;
    name_label->setText(QString::fromStdString(zUL.player.getName()));
    cout << name_label->text().toStdString() << endl;

    QLabel *age_title_label = new QLabel;
    age_title_label->setText("Age:");
    QLabel *age_label = new QLabel;
    age_label->setText(QString::number(zUL.player.getAge()));

    QLabel *sex_title_label = new QLabel;
    sex_title_label->setText("Sex:");
    QLabel *sex_label = new QLabel;
    sex_label->setText(QString::fromStdString(zUL.player.getSex()));

    QGridLayout *p_info_grid = new QGridLayout;
    //p_info_grid->addWidget(label, 0, 0, 1, 1);
    p_info_grid->addWidget(name_title_label, 0, 0, 1, 1);
    p_info_grid->addWidget(name_label, 0, 1, 1, 1);
    p_info_grid->addWidget(health_status_bar, 1, 0, 1, 2);
    p_info_grid->addWidget(age_title_label, 2, 0, 1 ,1);
    p_info_grid->addWidget(age_label, 2, 1, 1, 1);
    p_info_grid->addWidget(sex_title_label, 3, 0, 1, 1);
    p_info_grid->addWidget(sex_label, 3, 1, 1, 1);

    groupBox->setLayout(p_info_grid);
    return groupBox;
}

QGroupBox* MainWindow::createInventoryGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Inventory"));

    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::NoSelection);

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
    QGroupBox *groupBox = new QGroupBox(tr("Navigation"));

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
    string temp = zUL.getCurrentRoomName();
    QString c_room = QString::fromStdString(temp);
    current_room_label->setText("Current Room: " + c_room);
}

void MainWindow::updateStoryText()
{
    story_text_browser->append(QString::fromStdString(zUL.getCurrentRoomDescription()));
}

void MainWindow::updateRoomItems()
{
    // TODO Disable take button if no items in the room.
    // Clear and delete checkboxes
    while (auto item = room_items_container->takeAt(0)) {
          delete item->widget();
    }
    room_items_checkboxes.clear();

    // Get items in current room
    current_room = zUL.getCurrentRoom();
    itemsInRoom = current_room->getItemsInRoom();

    if(current_room->getItemsInRoom()->size() == 0)
    {
        take_item_btn->setEnabled(false);
        take_item_btn->setToolTip("No items to take");
    }
    else
    {
        take_item_btn->setEnabled(true);
        take_item_btn->setToolTip("");

        unsigned int i = 0;
        for(Item item : *itemsInRoom)
        {
            cout << item.getShortDescription() << endl;
            QCheckBox *temp_cbox = new QCheckBox;
            room_items_checkboxes.push_back(temp_cbox);
            temp_cbox->setText(QString::fromStdString(item.getShortDescription()));
            room_items_container->addWidget(room_items_checkboxes.at(i));
            ++i;
        }
    }
}

void MainWindow::updateInventory()
{
    vector<Item> p_inv = zUL.player.getInventory();

    cout<< "Player inventory: ";
    for(unsigned int i = 0; i < p_inv.size(); i++)
        cout << p_inv.at(i).getShortDescription() << " ";
    cout << endl;

    QListWidgetItem *it;

    listWidget->clear();

    for(unsigned int i = 0; i < p_inv.size(); i++)
    {
        it = new QListWidgetItem(listWidget);
        listWidget->setItemWidget(it, new QRadioButton(QString::fromStdString(p_inv.at(i).getShortDescription())));
    }
}

void MainWindow::updatePlayerInfo()
{
    cout << "Updating player info..." << endl;
    cout << "Player health: " << zUL.player.getHealth() << endl;

    if(zUL.player.getHealth() <= 0)
    {
        //QMessageBox mBox(this);
        //QString mBox_title = "GAME OVER";
        //mBox.about(this, mBox_title, "GAMEOVER!");

        QMessageBox mBox;
        mBox.setText("Game Over!");
        QAbstractButton *restartBtn = mBox.addButton("Restart", QMessageBox::YesRole);
        QAbstractButton *exitBtn = mBox.addButton("Exit", QMessageBox::NoRole);
        mBox.exec();

        if(mBox.clickedButton() == restartBtn)
        {
            cout << "Restarting..." << endl;
            restartAct->trigger();
        }
        else if(mBox.clickedButton() == exitBtn)
        {
            cout << "Exiting..." << endl;
            qApp->exit(0);
        }
    }
    else
    {
        player_health_bar->setValue(zUL.player.getHealth());
    }
}

void MainWindow::updateCombatField()
{
    if(zUL.currentRoom->isEnemyInRoom())
    {
        if(attack_btn->isEnabled() == false)
        {
            attack_btn->setEnabled(true);
            attack_btn->setToolTip("");
        }

        // Start combat

        // Enable Enemy info widgets
        enemy_name_label->setVisible(true);
        enemy_status_bar->setVisible(true);
        use_sword_radio->setVisible(true);
        use_magic_radio->setVisible(true);

        // Set widgets
        enemy_name_label->setText("Name: " + QString::fromStdString(zUL.currentRoom->getEnemy()->getName()));
        enemy_health_bar->setValue(zUL.currentRoom->getEnemy()->getHealth());
        use_sword_radio->setChecked(true);

        // disable nav buttons
        north_btn->setEnabled(false);
        north_btn->setToolTip("Cannot go to room, you are in combat");
        north_btn->setChecked(false);

        east_btn->setEnabled(false);
        east_btn->setToolTip("Cannot go to room, you are in combat");
        east_btn->setChecked(false);

        south_btn->setEnabled(false);
        south_btn->setToolTip("Cannot go to room, you are in combat");
        south_btn->setChecked(false);

        west_btn->setEnabled(false);
        west_btn->setToolTip("Cannot go to room, you are in combat");
        west_btn->setChecked(false);
    }
    else
    {
        if(attack_btn->isEnabled())
        {
            attack_btn->setEnabled(false);
            attack_btn->setToolTip("No enemy in current room");
        }

        enemy_name_label->setVisible(false);
        enemy_status_bar->setVisible(false);
        use_sword_radio->setVisible(false);
        use_magic_radio->setVisible(false);
    }
}

void MainWindow::teleport_btn_onclick()
{
    zUL.teleport();
    string message = zUL.getCurrentRoomName();
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
    // https://forum.qt.io/topic/91040/how-do-i-check-the-state-of-a-qlistwidget-s-item-s-radiobuttons/3
    for(int i = 0; i < listWidget->count(); i++)
    {
        auto temp_radio_btn = static_cast<QRadioButton*>(listWidget->itemWidget(listWidget->item(i)));
        if(temp_radio_btn->isChecked())
        {
            cout << temp_radio_btn->text().toStdString() << " RB is checked" << endl;

            // Remove item from player inventory
            vector<Item> inv = zUL.player.getInventory();
            zUL.player.removeItemFromInventory(i);

            inv = zUL.player.getInventory();
            for(Item i : inv)
                cout << i.getShortDescription() << " ";
            cout << endl;

            // Remove item from the list
            delete listWidget->item(i);
        }
    }

    //QListWidgetItem *item = listWidget->currentItem();
    //delete listWidget->takeItem(listWidget->row(item));

}

void MainWindow::take_item_btn_onclick()
{
    // TODO remove item(s) from list of items in room.
    cout << "Taking Item(s)..." << endl;

    cout << "Size: " << room_items_checkboxes.size() << endl;
    for(unsigned int i = 0; i < room_items_checkboxes.size(); )
    {
        cout << "Here in the loop..." << endl;
        // If QCheckBox is checked add it to players inventory
        if(room_items_checkboxes.at(i)->isChecked())
        {
            cout << room_items_checkboxes.at(i)->text().toStdString() << " is checked" << endl;
            zUL.player.addItemToInvetory(itemsInRoom->at(i));

            // Remove the item from the room
            zUL.currentRoom->removeItemFromRoom(i);

            // Remove element from vector, this avoids a crash
            room_items_checkboxes.erase(room_items_checkboxes.begin()+i);
        }
        else
            i++;
    }

    // Update layout
    updateRoomItems();
    updateInventory();
    updatePlayerInfo();
}

void MainWindow::attack_btn_onclick()
{
    cout << "Attack pressed..." << endl;
    if(use_sword_radio->isChecked())
    {
        cout << "use weapon..." << endl;

    }
    else if(use_magic_radio->isChecked())
    {
        cout << "use magic..." << endl;
    }
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
        message = QString::fromStdString(zUL.getCurrentRoomName());
    }

    updateRoomLabel();
    updateStoryText();
    updateNavButtons();
    updateRoomItems();
    updateCombatField();

    //QMessageBox mBox(this);
    //QString mBox_title = "Current Room";
    //mBox.about(this, mBox_title, message);
}
