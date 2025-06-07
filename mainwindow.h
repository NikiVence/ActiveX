#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "calendar.h"
#include "workoutplan.h"
#include "nutritionplan.h"
#include "imtcalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void showMainMenu();
    void showCalendar();
    void showWorkoutPlans();
    void showNutritionPlans();
    void showIMTCalculator();
    void exitApp();

private:
    Ui::MainWindow *ui;
    void setupUI();

    Calendar *calendar;          // Изменено на указатель
    WorkoutPlan *workoutPlans;   // Изменено на указатель
    NutritionPlan *nutritionPlans; // Изменено на указатель
    IMTCalculator *imtCalculator; // Изменено на указатель
};

#endif // MAINWINDOW_H
