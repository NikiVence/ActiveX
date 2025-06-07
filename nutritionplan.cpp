#include "nutritionplan.h"
#include <QMessageBox>
#include <QLabel>


NutritionPlan::NutritionPlan(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Планы питания");
    resize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Выбор цели питания
    QComboBox *goalCombo = new QComboBox(this);
    goalCombo->addItems({"Похудение", "Набор массы", "Поддержание массы"});

    // Отображение плана питания
    QTextEdit *nutritionDisplay = new QTextEdit(this);
    nutritionDisplay->setReadOnly(true);
    nutritionDisplay->setFont(QFont("Arial", 10));

    // Кнопка генерации плана
    QPushButton *generateBtn = new QPushButton("Сгенерировать план питания", this);
    generateBtn->setStyleSheet("QPushButton { padding: 8px; font-weight: bold; }");

    // Компоновка элементов
    layout->addWidget(new QLabel("Выберите цель:", this));
    layout->addWidget(goalCombo);
    layout->addSpacing(10);
    layout->addWidget(nutritionDisplay);
    layout->addWidget(generateBtn);

    // Обработка нажатия кнопки
    connect(generateBtn, &QPushButton::clicked, [=]() {
        QString nutritionPlan = getNutritionPlan(goalCombo->currentText());
        nutritionDisplay->setText(nutritionPlan);
    });
}

void NutritionPlan::showNutrition()
{
    show();
}

QString NutritionPlan::getNutritionPlan(const QString &goal)
{
    QString plan = "🌟 План питания для цели: " + goal + " 🌟\n\n";
    plan += "🍳 Завтрак:\n";
    plan += "🥗 Обед:\n";
    plan += "🍲 Ужин:\n";
    plan += "🍎 Перекусы:\n\n";

    if (goal == "Похудение") {
        plan += "🍳 Овсянка на воде с ягодами (50г овсянки, 100г ягод)\n";
        plan += "🥗 Куриная грудка на гриле (150г) с овощным салатом\n";
        plan += "🍲 Запеченная рыба (150г) с брокколи\n";
        plan += "🍎 2 перекуса: творог (100г) или яблоко\n";
        plan += "\n💡 Калорийность: ~1500 ккал\n";
    }
    else if (goal == "Набор массы") {
        plan += "🍳 Омлет из 3 яиц с тостами и авокадо\n";
        plan += "🥗 Говядина (200г) с гречкой (100г сухой) и овощами\n";
        plan += "🍲 Лосось (200г) с бурым рисом (80г сухого)\n";
        plan += "🍎 3 перекуса: протеиновый коктейль, орехи (50г), банан\n";
        plan += "\n💡 Калорийность: ~3000 ккал\n";
    }
    else { // Поддержание массы
        plan += "🍳 Гречка (60г сухой) с яйцами (2 шт)\n";
        plan += "🥗 Индейка (180г) с картофелем (150г) и овощами\n";
        plan += "🍲 Овощное рагу с курицей (150г)\n";
        plan += "🍎 2 перекуса: йогурт, горсть орехов\n";
        plan += "\n💡 Калорийность: ~2200 ккал\n";
    }

    plan += "\n📌 Рекомендации:\n";
    plan += "- Пейте 2-3 литра воды в день\n";
    plan += "- Уменьшите потребление сахара и фастфуда\n";
    plan += "- Соблюдайте режим питания (5-6 приемов пищи)\n";
    plan += "- Подстраивайте порции под свои потребности\n";

    return plan;
}
