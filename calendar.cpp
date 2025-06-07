#include "calendar.h"

Calendar::Calendar(QWidget *parent) : QDialog(parent)
{
    setupUI();
    loadActivities();
}

Calendar::~Calendar()
{
    saveActivities();
}

void Calendar::setupUI()
{
    setWindowTitle("Календарь активности");
    resize(800, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);

    // Календарь
    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setStyleSheet("QCalendarWidget { font-size: 12px; }");
    mainLayout->addWidget(calendarWidget);

    // Отображение активности
    activityDisplay = new QTextEdit(this);
    activityDisplay->setReadOnly(true);
    activityDisplay->setStyleSheet("QTextEdit { font-size: 14px; border: 1px solid #ddd; padding: 10px; }");
    mainLayout->addWidget(activityDisplay);

    // Кнопки управления
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    addButton = new QPushButton("Добавить активность", this);
    addButton->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 15px;"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        );

    removeButton = new QPushButton("Удалить активность", this);
    removeButton->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 15px;"
        "  background-color: #f44336;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #d32f2f; }"
        );

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // Подключение сигналов
    connect(calendarWidget, &QCalendarWidget::clicked, this, &Calendar::onDateClicked);
    connect(addButton, &QPushButton::clicked, this, &Calendar::onAddActivityClicked);
    connect(removeButton, &QPushButton::clicked, this, &Calendar::onRemoveActivityClicked);

    // Инициализация
    currentSelectedDate = QDate::currentDate();
    calendarWidget->setSelectedDate(currentSelectedDate);
    updateActivityDisplay();
}

void Calendar::viewActivities()
{
    show();
}

void Calendar::onDateClicked(const QDate &date)
{
    currentSelectedDate = date;
    updateActivityDisplay();
}

void Calendar::onAddActivityClicked()
{
    bool ok;
    QString text = QInputDialog::getText(
        this,
        "Добавление активности",
        "Введите описание активности:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !text.isEmpty()) {
        addActivity(text, currentSelectedDate);
        updateActivityDisplay();
        QMessageBox::information(this, "Успех", "Активность успешно добавлена!");
    }
}

void Calendar::onRemoveActivityClicked()
{
    if (activities.contains(currentSelectedDate)) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Подтверждение",
            "Вы действительно хотите удалить активность на выбранную дату?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            removeActivity(currentSelectedDate);
            updateActivityDisplay();
            QMessageBox::information(this, "Успех", "Активность успешно удалена!");
        }
    } else {
        QMessageBox::information(
            this,
            "Информация",
            "На выбранную дату нет активностей для удаления"
            );
    }
}

void Calendar::updateActivityDisplay()
{
    if (activities.contains(currentSelectedDate)) {
        QString displayText = QString("<b>Активность на %1:</b><br><br>%2")
                                  .arg(currentSelectedDate.toString("dd.MM.yyyy"))
                                  .arg(activities[currentSelectedDate]);
        activityDisplay->setHtml(displayText);
    } else {
        activityDisplay->setHtml(
            QString("<i>Нет активностей на %1</i>")
                .arg(currentSelectedDate.toString("dd.MM.yyyy"))
            );
    }
}

void Calendar::addActivity(const QString &activity, const QDate &date)
{
    activities[date] = activity;
    saveActivities();
}

void Calendar::removeActivity(const QDate &date)
{
    activities.remove(date);
    saveActivities();
}

void Calendar::closeEvent(QCloseEvent *event)
{
    saveActivities();
    event->accept();
}

void Calendar::saveActivities()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);

    QString filePath = dataPath + "/activities.dat";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << activities;
        file.close();
        qDebug() << "Активности сохранены в:" << filePath;
    } else {
        qWarning() << "Ошибка при сохранении активностей:" << file.errorString();
    }
}

void Calendar::loadActivities()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/activities.dat";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> activities;
        file.close();
        qDebug() << "Активности загружены из:" << filePath;
    } else {
        qDebug() << "Файл с активностями не найден, будет создан новый";
    }
}
