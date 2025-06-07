#ifndef NUTRITIONPLAN_H
#define NUTRITIONPLAN_H

#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class NutritionPlan : public QDialog
{
    Q_OBJECT
public:
    explicit NutritionPlan(QWidget *parent = nullptr);
    void showNutrition();
    QString getNutritionPlan(const QString &goal);
};

#endif // NUTRITIONPLAN_H
