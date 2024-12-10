#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <functional> // std::function

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
    // Member variables
    Ui::MainWindow *ui;
    QImage *sourceImage;
    QGraphicsScene* bitmapGraphicsScene;
    QString selectedBitmapFilePath;
    QString selectedDataFilePath;

    // Methods
    void openImage();
    void loadTextFile();
    void initializeActivity();
    void progressCallback(int progressPercentageComplete);
    void finalizeActivity();
    void activityWrapper(std::function<void()> activity);
};
#endif // MAINWINDOW_H
