#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFileSelection_clicked();
    void on_pushButtonDataFileSelection_clicked();
    void on_pushButtonEmbed_clicked();
    void on_pushButtonExtract_clicked();

private:
    Ui::MainWindow *ui;
    QImage *sourceImage;
    void openImage();
    void loadTextFile();
    QString selectedBitmapFilePath;
    QString selectedDataFilePath;
};
#endif // MAINWINDOW_H
