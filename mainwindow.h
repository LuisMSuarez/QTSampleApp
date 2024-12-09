#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

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
    QGraphicsScene* bitmapGraphicsScene;
    QString selectedBitmapFilePath;
    QString selectedDataFilePath;
    void openImage();
    void loadTextFile();
    void progressCallback(int progressPercentageComplete);
};
#endif // MAINWINDOW_H
