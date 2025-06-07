#ifndef IMTCALCULATOR_H
#define IMTCALCULATOR_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class IMTCalculator : public QDialog
{
    Q_OBJECT
public:
    explicit IMTCalculator(QWidget *parent = nullptr);
    void calculateIMT();
    double calculate(double height, double weight);
    QString getRecommendation(double imt);
};

#endif // IMTCALCULATOR_H
