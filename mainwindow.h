#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "compress.h"
#include "Decompress.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Compress_clicked();      // Opens compression dialog

    void on_Decompress_clicked();    // Opens decompression dialog

private:
    Ui::MainWindow *ui;
    compress *compres;        // Compression dialog instance
    Decompress * decompress;  // Decompression dialog instance
};
#endif // MAINWINDOW_H
