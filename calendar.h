#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>
#include <QCalendarWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>
#include <QDate>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QStandardPaths>

class Calendar : public QDialog
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();

    void addActivity(const QString &activity, const QDate &date);
    void removeActivity(const QDate &date);
    void viewActivities();
    void saveActivities();

    // Запрещаем копирование
    Calendar(const Calendar&) = delete;
    Calendar& operator=(const Calendar&) = delete;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onDateClicked(const QDate &date);
    void onAddActivityClicked();
    void onRemoveActivityClicked();

private:
    void setupUI();
    void updateActivityDisplay();
    void loadActivities();

    QCalendarWidget *calendarWidget;
    QTextEdit *activityDisplay;
    QPushButton *addButton;
    QPushButton *removeButton;
    QMap<QDate, QString> activities;
    QDate currentSelectedDate;
};

#endif // CALENDAR_H
