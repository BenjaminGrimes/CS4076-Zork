#include "startmenuwindow.h"
#include "ui_startmenuwindow.h"

#define MIN_AGE_VAL 1
#define MAX_AGE_VAL 100

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 100

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
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(WINDOW_WIDTH, WINDOW_HEIGHT, Qt::KeepAspectRatio));

    name_label = new QLabel("Enter name:");
    name_lineEdit = new QLineEdit;
    name_lineEdit->setPlaceholderText("Enter your name");

    age_label = new QLabel("Select Age:");
    age_slider = new QSlider(Qt::Horizontal, this);
    age_slider->setRange(MIN_AGE_VAL, MAX_AGE_VAL);
    //cout << age_slider->value() << endl;
    age_value = new QSpinBox;
    age_value->setRange(MIN_AGE_VAL, MAX_AGE_VAL);
    age_value->setSingleStep(1);
    QHBoxLayout *age_container = new QHBoxLayout;
    age_container->addWidget(age_value, 0, Qt::AlignLeft);
    age_container->addWidget(age_slider);
    connect(age_slider, SIGNAL(valueChanged(int)), age_value, SLOT(setValue(int)));
    connect(age_value, SIGNAL(valueChanged(int)), age_slider, SLOT(setValue(int)));

    sex_label = new QLabel("Select Sex:");
    sex_comboBox = new QComboBox;
    sex_comboBox->addItem("---");
    sex_comboBox->addItem("Male");
    sex_comboBox->addItem("Female");

    error_label = new QLabel("");

    start_btn = new QPushButton("Start", this);
    connect(start_btn, SIGNAL(released()), this, SLOT(start_btn_onclick()));

    exit_btn = new QPushButton("Exit", this);
    connect(exit_btn, SIGNAL(released()), this, SLOT(exit_btn_onclick()));

    formLayout = new QFormLayout;
    formLayout->addRow("Name:", name_lineEdit);
    formLayout->addRow("Age:", age_container);
    formLayout->addRow("Sex:", sex_comboBox);

    QHBoxLayout *btn_container = new QHBoxLayout;
    btn_container->addWidget(start_btn);
    btn_container->addWidget(exit_btn);

    container->addWidget(imageLabel, 0, Qt::AlignCenter);
    container->addLayout(formLayout);
    container->addWidget(error_label, 0, Qt::AlignCenter);
    container->addLayout(btn_container);


    auto central = new QWidget;
    central->setLayout(container);
    setCentralWidget(central);
}

void StartMenuWindow::start_btn_onclick()
{
    // Get the count of character in name_lineEdit
    int n_count = name_lineEdit->text().count();
    cout << n_count << endl;

    if(n_count == 0)
    {
        // TODO tell user to enter name
        error_label->setText("Please enter a name");
    }
    // TODO check for age selected
    else if(sex_comboBox->currentIndex() == 0)
    {
        error_label->setText("Please select a sex");
    }
    else
    {
        w.zUL.player.setPlayerInfo(name_lineEdit->text(), age_slider->value(), sex_comboBox->currentText());
        w.setWindowTitle("ZORK");
        w.showMaximized();
        w.setUpLayout();

        connect(w.restartAct, &QAction::triggered, this, &StartMenuWindow::clearAndReset);

        // Hide this window
        this->hide();
    }
}

void StartMenuWindow::exit_btn_onclick()
{
    this->close();
}

void StartMenuWindow::clearAndReset()
{
    qApp->exit(MainWindow::EXIT_CODE_REBOOT);
}
