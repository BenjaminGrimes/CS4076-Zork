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
    formLayout->addWidget(imageLabel);
    formLayout->addRow("Name:", name_lineEdit);
    formLayout->addRow("Age", age_slider);
    formLayout->addRow("Sex:", sex_comboBox);
    formLayout->addRow(start_btn, exit_btn);

    auto central = new QWidget;
    central->setLayout(formLayout);
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
