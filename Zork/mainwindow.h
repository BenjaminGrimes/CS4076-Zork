#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QListWidget>
#include <QProgressBar>
#include <QTextBrowser>
#include <QStatusBar>
#include <QScrollArea>
#include <QCheckBox>
#include <QFormLayout>

#include <QActionGroup>

#include <string>

#include "ZorkUL.h"
#include "item.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int const EXIT_CODE_REBOOT;

private slots:
    void teleport_btn_onclick();
    void north_btn_onclick();
    void south_btn_onclick();
    void east_btn_onclick();
    void west_btn_onclick();

    void use_item_btn_onclick();

    void take_item_btn_onclick();

private:
    Ui::MainWindow *ui;

    friend class StartMenuWindow;

    ZorkUL zUL;

    QGridLayout *grid;

    Room *current_room;

    // ----- Menus ------------
    void createActions();
    void createStatusBar();

    QMenu *gameMenu;
    QAction *restartAct;
    QAction *exitAct;
    // -----------------------

    // ----- Groups -----------
    QGroupBox *nav_box;
    QGroupBox *player_box;
    QGroupBox *inventory_box;
    QGroupBox *map_box;
    QGroupBox *story_box;
    // ------------------------

    // ----- Navigation group widgets -----
    QLabel *current_room_label;
    QPushButton *teleport_btn;
    QPushButton *north_btn;
    QPushButton *south_btn;
    QPushButton *east_btn;
    QPushButton *west_btn;
    // ------------------------------------

    // ------ Inventory Group Widgets ------
    QPushButton *use_item_btn;
    QListWidget *listWidget;
    // -------------------------------------

    // ------ Player Info Group Widgets ----
    QProgressBar *player_health_bar;
    QStatusBar *health_status_bar;
    // -------------------------------------


    // ------ Map Group Widgets ------------

    // -------------------------------------


    // ------ Story Group Widgets ----------
    QTextBrowser *story_text_browser;
    QPushButton *take_item_btn;
    vector<Item>* itemsInRoom;
    vector<QCheckBox*> room_items_checkboxes;
    QVBoxLayout *room_items_container;
    // -------------------------------------

    void setUpLayout();

    QGroupBox* createNavigationGroup();
    QGroupBox* createPlayerInfoGroup();
    QGroupBox* createMapGroup();
    QGroupBox* createInventoryGroup();
    QGroupBox* createStoryGroup();

    void updateNavButtons();
    void updateRoomLabel();
    void updateStoryText();
    void updateRoomItems();
    void updateInventory();
    void updatePlayerInfo();
    void goDirection(QString direction);
};

#endif // MAINWINDOW_H
