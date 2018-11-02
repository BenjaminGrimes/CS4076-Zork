#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"

StartMenuWindow::StartMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartMenuWindow)
{
    ui->setupUi(this);

    this->resize(400, 200);

    setUpLayout();
}

StartMenuWindow::~StartMenuWindow()
{
    delete ui;
}

void StartMenuWindow::setUpLayout()
{
    QVBoxLayout *container = new QVBoxLayout;
    QLabel *imageLabel = new QLabel;
    QImage image(":/ZORK_TITLE.png");
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(200,100, Qt::KeepAspectRatio));

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

    formLayout = new QFormLayout;
    formLayout->addRow("Name:", name_lineEdit);
    formLayout->addRow("Age:", age_slider);
    formLayout->addRow("Sex:", sex_comboBox);

    QHBoxLayout *btn_container = new QHBoxLayout;
    btn_container->addWidget(start_btn);
    btn_container->addWidget(exit_btn);

    container->addWidget(imageLabel, 0, Qt::AlignCenter);
    container->addLayout(formLayout);
    container->addLayout(btn_container);


    auto central = new QWidget;
    central->setLayout(container);
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
