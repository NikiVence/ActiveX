#include "imtcalculator.h"
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDoubleValidator>

IMTCalculator::IMTCalculator(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Калькулятор ИМТ");
    resize(400, 300);
    setStyleSheet("QDialog { background-color: #000000; }");

    QFormLayout *layout = new QFormLayout(this);

    // Поля ввода
    QLineEdit *heightInput = new QLineEdit(this);
    heightInput->setPlaceholderText("В см (например: 175 или 175.5)");

    // Валидатор для роста (разрешает числа с точкой)
    QDoubleValidator *heightValidator = new QDoubleValidator(100, 250, 1, this);
    heightValidator->setNotation(QDoubleValidator::StandardNotation);
    heightInput->setValidator(heightValidator);

    QLineEdit *weightInput = new QLineEdit(this);
    weightInput->setPlaceholderText("В кг (например: 70 или 70.5)");

    // Валидатор для веса (разрешает числа с точкой)
    QDoubleValidator *weightValidator = new QDoubleValidator(30, 300, 1, this);
    weightValidator->setNotation(QDoubleValidator::StandardNotation);
    weightInput->setValidator(weightValidator);

    // Остальной код остается без изменений...
    // Кнопка расчета
    QPushButton *calculateBtn = new QPushButton("Рассчитать ИМТ", this);
    calculateBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border: none;"
        "  padding: 8px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        );

    // Поле вывода результата
    QLabel *resultLabel = new QLabel("Введите свои данные", this);
    resultLabel->setWordWrap(true);
    resultLabel->setStyleSheet("font-size: 14px; margin-top: 15px;");

    // Добавление элементов в layout
    layout->addRow("Рост (см):", heightInput);
    layout->addRow("Вес (кг):", weightInput);
    layout->addRow(calculateBtn);
    layout->addRow("Результат:", resultLabel);

    // Обработка нажатия кнопки
    connect(calculateBtn, &QPushButton::clicked, [=]() {
        bool ok;
        double height = heightInput->text().replace(",", ".").toDouble(&ok);
        if (!ok || height <= 0) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректный рост (100-250 см)");
            return;
        }

        double weight = weightInput->text().replace(",", ".").toDouble(&ok);
        if (!ok || weight <= 0) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректный вес (30-300 кг)");
            return;
        }

        double imt = calculate(height, weight);
        QString recommendation = getRecommendation(imt);

        QString result = QString("Ваш ИМТ: <b>%1</b><br>").arg(imt, 0, 'f', 1);
        result += recommendation;
        resultLabel->setText(result);
    });
}

double IMTCalculator::calculate(double height, double weight)
{
    // ИМТ = вес (кг) / (рост (м))^2
    return weight / ((height / 100) * (height / 100));
}

QString IMTCalculator::getRecommendation(double imt)
{
    QString color;
    QString status;
    QString advice;

    if (imt < 16) {
        color = "#FF5252";
        status = "Выраженный дефицит массы";
        advice = "Рекомендуется срочно обратиться к врачу и увеличить калорийность питания";
    }
    else if (imt < 18.5) {
        color = "#FF9800";
        status = "Недостаточная масса тела";
        advice = "Рекомендуется план питания для набора массы";
    }
    else if (imt < 25) {
        color = "#4CAF50";
        status = "Нормальный вес";
        advice = "Ваш вес в норме, рекомендуется план поддержания формы";
    }
    else if (imt < 30) {
        color = "#FF9800";
        status = "Избыточная масса тела";
        advice = "Рекомендуется план питания для похудения";
    }
    else if (imt < 35) {
        color = "#FF5252";
        status = "Ожирение 1 степени";
        advice = "Рекомендуется консультация диетолога и программа похудения";
    }
    else if (imt < 40) {
        color = "#FF0000";
        status = "Ожирение 2 степени";
        advice = "Необходима консультация врача и программа коррекции веса";
    }
    else {
        color = "#C62828";
        status = "Ожирение 3 степени";
        advice = "Требуется срочная медицинская помощь";
    }

    return QString("<span style='color:%1;'><b>%2</b></span><br>%3")
        .arg(color)
        .arg(status)
        .arg(advice);
}

void IMTCalculator::calculateIMT()
{
    show();
}
