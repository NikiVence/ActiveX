#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , calendar(new Calendar(this))       // Инициализация указателей
    , workoutPlans(new WorkoutPlan(this))
    , nutritionPlans(new NutritionPlan(this))
    , imtCalculator(new IMTCalculator(this))
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete calendar;
    delete workoutPlans;
    delete nutritionPlans;
    delete imtCalculator;
    delete ui;
}

void MainWindow::setupUI()
{
    setWindowTitle("ActiveX");
    resize(400, 300);
    showMainMenu();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сохраняем данные при закрытии
    calendar->saveActivities();
    event->accept();
}

void MainWindow::showMainMenu()
{
    // Очистка текущего интерфейса
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // Создание кнопок меню
    QPushButton *calendarBtn = new QPushButton("Календарь активности", this);
    QPushButton *workoutBtn = new QPushButton("Тренировки", this);
    QPushButton *nutritionBtn = new QPushButton("Планы питания", this);
    QPushButton *imtBtn = new QPushButton("Калькулятор ИМТ", this);
    QPushButton *exitBtn = new QPushButton("Выход", this);

    // Подключение сигналов
    connect(calendarBtn, &QPushButton::clicked, this, &MainWindow::showCalendar);
    connect(workoutBtn, &QPushButton::clicked, this, &MainWindow::showWorkoutPlans);
    connect(nutritionBtn, &QPushButton::clicked, this, &MainWindow::showNutritionPlans);
    connect(imtBtn, &QPushButton::clicked, this, &MainWindow::showIMTCalculator);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitApp);

    // Добавление кнопок в layout
    layout->addWidget(calendarBtn);
    layout->addWidget(workoutBtn);
    layout->addWidget(nutritionBtn);
    layout->addWidget(imtBtn);
    layout->addWidget(exitBtn);

    setCentralWidget(central);
}

void MainWindow::showCalendar()
{
    calendar->viewActivities();
}

void MainWindow::showWorkoutPlans()
{
    workoutPlans->showPlan();
}

void MainWindow::showNutritionPlans()
{
    nutritionPlans->showNutrition();
}

void MainWindow::showIMTCalculator()
{
    imtCalculator->calculateIMT();
}

void MainWindow::exitApp()
{
    QMessageBox::information(this, "Выход", "Спасибо за использование приложения!");
    QApplication::quit();
}
