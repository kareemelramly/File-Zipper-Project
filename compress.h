#ifndef COMPRESS_H
#define COMPRESS_H
#include <QDialog>

namespace Ui {
class compress;
}

class compress : public QDialog
{
    Q_OBJECT

public:
    explicit compress(QWidget *parent = nullptr);
    void onCompressionFinished(bool success);
    ~compress();

private slots:
    void on_com_sel_clicked();        // File selection button handler

    void on_docompression_clicked();  // Start compression button handler

private:
    Ui::compress *ui;
     QString selectedFilePath;        // Full path of selected file
    QTimer* progressTimer;            // Timer for progress updates
};

#endif // COMPRESS_H
