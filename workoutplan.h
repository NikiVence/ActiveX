#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class WorkoutPlan : public QDialog
{
    Q_OBJECT
public:
    explicit WorkoutPlan(QWidget *parent = nullptr);
    void showPlan();
    QString getWorkout(const QString &type, const QString &goal);
};

#endif // WORKOUTPLAN_H
