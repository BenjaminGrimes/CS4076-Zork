#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"

StartMenuWindow::StartMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartMenuWindow)
{
    ui->setupUi(this);

    setUpLayout();
}

StartMenuWindow::~StartMenuWindow()
{
    delete ui;
}

void StartMenuWindow::setUpLayout()
{
    name_label = new QLabel("Enter name:");
    name_lineEdit = new QLineEdit;

    age_label = new QLabel("Select Age:");
    age_slider = new QSlider(Qt::Horizontal, this);

    sex_label = new QLabel("Select Sex:");
    sex_comboBox = new QComboBox;

    start_btn = new QPushButton("Start", this);
    connect(start_btn, SIGNAL(released()), this, SLOT(start_btn_onclick()));

    exit_btn = new QPushButton("Exit", this);
    connect(exit_btn, SIGNAL(released()), this, SLOT(exit_btn_onclick()));

    grid = new QGridLayout;
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);
    for(int i = 0; i <= 3; i++)
        grid->setRowStretch(i, 1);

    grid->addWidget(name_label, 0, 0);
    grid->addWidget(name_lineEdit, 0, 1);
    grid->addWidget(sex_label, 1, 0);
    grid->addWidget(sex_comboBox, 1, 1);
    grid->addWidget(age_label, 2, 0);
    grid->addWidget(age_slider, 2, 1);
    grid->addWidget(start_btn, 3, 0);
    grid->addWidget(exit_btn, 3, 1);

    auto central = new QWidget;
    central->setLayout(grid);
    setCentralWidget(central);
}

void StartMenuWindow::start_btn_onclick()
{
    w.setWindowTitle("ZORK");
    w.showMaximized();

    // Hide this window
    this->hide();
}

void StartMenuWindow::exit_btn_onclick()
{
    this->close();
}
