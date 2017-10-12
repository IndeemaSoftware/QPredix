#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QUaa;
class QTimeSeries;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void loginSucced();

private:
    Ui::MainWindow *ui;

    QUaa *mUaa;
    QTimeSeries *mTimeSeries;
};

#endif // MAINWINDOW_H
