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
    void on_com_sel_clicked();

    void on_docompression_clicked();

private:
    Ui::compress *ui;
     QString selectedFilePath;
    QTimer* progressTimer;
};

#endif // COMPRESS_H
