#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "steganography.h"
#include <filesystem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sourceImage=new QImage();
    ui->labelSourceBitmapFilePath->setText("Select bitmap file");
    ui->plainTextEdit->setReadOnly(true);
    bitmapGraphicsScene=new QGraphicsScene();
    ui->progressBar->hide();
    ui->statusbar->addPermanentWidget(ui->progressBar);
}

MainWindow::~MainWindow()
{
    delete bitmapGraphicsScene;
    delete sourceImage;
    delete ui;
}

void MainWindow::on_pushButtonFileSelection_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Bitmap files (*.bmp);;All files (*.*)");

    if (dialog.exec() == QDialog::Accepted)
    {
        selectedBitmapFilePath = dialog.selectedFiles().first();
        std::string fileName = std::filesystem::path(selectedBitmapFilePath.toStdString()).filename();
        ui->labelSourceBitmapFilePath->setText(QString::fromStdString(fileName));
        qDebug() << "Selected file:" << fileName;
        openImage();
    }
}

void MainWindow::openImage()
{
    sourceImage->load(selectedBitmapFilePath);
    bitmapGraphicsScene->addPixmap(
                QPixmap::fromImage(*sourceImage)
                    .scaled(
                             ui->graphicsView->width(),
                             ui->graphicsView->height(),
                             Qt::KeepAspectRatio));
    ui->graphicsView->setScene(bitmapGraphicsScene);
    ui->graphicsView->show();
 }

void MainWindow::on_pushButtonDataFileSelection_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("All files (*.*)");

    if (dialog.exec() == QDialog::Accepted)
    {
        selectedDataFilePath = dialog.selectedFiles().first();
        std::string fileName = std::filesystem::path(selectedDataFilePath.toStdString()).filename();
        ui->labelDataFileSourcePath->setText(QString::fromStdString(fileName));
        qDebug() << "Selected file:" << fileName;
        loadTextFile();
    }
}

void MainWindow::loadTextFile()
{
    QFile file(selectedDataFilePath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString content;
    while(!file.atEnd())
    {
        content.append(file.readLine());
    }
    ui->plainTextEdit->setPlainText(content);
    ui->plainTextEdit->show();
    file.close();
}

void MainWindow::initializeActivity()
{
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}

void MainWindow::progressCallback(int progressPercentageComplete)
{
    qDebug() << "Percent complete:" << progressPercentageComplete;
    ui->progressBar->setValue(progressPercentageComplete);
    QApplication::processEvents();
}

void MainWindow::finalizeActivity()
{
    ui->statusbar->showMessage("Operation complete", 5000);

    // Hide the progress bar after 5 seconds
    QTimer::singleShot(5000, ui->progressBar, &QWidget::hide);
}

void MainWindow::activityWrapper(std::function<void()> activity)
{
    initializeActivity();

    try
    {
        activity();
    }
    catch (std::runtime_error &e)
    {
        QMessageBox::critical(this, "Encoding/extraction error", QString("Error during operation\n") + e.what(), QMessageBox::Ok);
    }

    finalizeActivity();
}

void MainWindow::on_pushButtonEmbed_clicked()
{
    if (selectedBitmapFilePath.isNull() ||
        selectedBitmapFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select bitmap file first", QMessageBox::Ok);
        return;
    }

    if (selectedDataFilePath.isNull() ||
        selectedDataFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select data file first", QMessageBox::Ok);
        return;
    }

    steganographyLib::Steganography steg;

    // Excellent article that describes usage of c++ functions/lambdas
    // https://blog.mbedded.ninja/programming/languages/c-plus-plus/callbacks/
    // this allows usage of (non-static) member functions in callbacks, which cannot be used with c-style
    // function pointers.
    steg.registerProgressCallback([this](int progressPercentageComplete) -> void
    {
        return this->progressCallback(progressPercentageComplete);
    }, /* percentGrain */ 1);
    activityWrapper([this, &steg]()->void
    {
        steg.embed(selectedBitmapFilePath.toStdString(),
                   selectedDataFilePath.toStdString(),
                   selectedBitmapFilePath.toStdString() + ".enc.bmp",
                   ui->spinBoxBitsPerPixel->value());
    });
}

void MainWindow::on_pushButtonExtract_clicked()
{
    if (selectedBitmapFilePath.isNull() ||
        selectedBitmapFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select bitmap file first", QMessageBox::Ok);
        return;
    }

    steganographyLib::Steganography steg;
    steg.registerProgressCallback([this](int progressPercentageComplete) -> void
    {
        return this->progressCallback(progressPercentageComplete);
    }, /* percentGrain */ 1);

    activityWrapper([this, &steg]()->void
    {
        steg.extract(selectedBitmapFilePath.toStdString(),
                     selectedBitmapFilePath.toStdString() + ".extracted",
                     ui->spinBoxBitsPerPixel->value());
    });
}
