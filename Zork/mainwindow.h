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

#include <string>

#include "ZorkUL.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void teleport_btn_onclick();
    void north_btn_onclick();
    void south_btn_onclick();
    void east_btn_onclick();
    void west_btn_onclick();

    void use_item_btn_onclick();

private:
    Ui::MainWindow *ui;

    ZorkUL zUL;

    QGridLayout *grid;

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
    // -------------------------------------


    // ------ Map Group Widgets ------------

    // -------------------------------------


    // ------ Story Group Widgets ----------

    // -------------------------------------


    // ------ Image Group Widgets ----------

    // -------------------------------------

    void setUpLayout();

    QGroupBox* createNavigationGroup();
    QGroupBox* createPlayerInfoGroup();
    QGroupBox* createMapGroup();
    QGroupBox* createInventoryGroup();
    QGroupBox* createStoryGroup();
    QGroupBox* createImageGroup();

    void updateNavButtons();
    void updateRoomLabel();
    void goDirection(QString direction);
};

#endif // MAINWINDOW_H
