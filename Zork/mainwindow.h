#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

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
    void btn_onclick();
    void north_btn_onclick();
    void south_btn_onclick();
    void east_btn_onclick();
    void west_btn_onclick();

private:
    Ui::MainWindow *ui;

    QPushButton *btn;
    QPushButton *north_btn;
    QPushButton *south_btn;
    QPushButton *east_btn;
    QPushButton *west_btn;

    QLabel *current_room_label;

    ZorkUL zUL;

    void setUpButtons();
    void setUpLabels();
    void updateRoomLabel();
    void goDirection(QString direction);
};

#endif // MAINWINDOW_H
