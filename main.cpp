#include "mainwindow.h"
#include "steganography.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    steganographyLib::Steganography steg;
    steg.embed("/home/luismi/Documents/repos/QTSampleApp/data/sample.bmp",
               "/home/luismi/Documents/repos/QTSampleApp/data/sampleInput.txt",
               "/home/luismi/Documents/repos/QTSampleApp/data/encoded.bmp",
               6);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
