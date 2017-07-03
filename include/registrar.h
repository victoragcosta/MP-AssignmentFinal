#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <QWidget>

namespace Ui {
class Registrar;
}

class Registrar : public QWidget
{
    Q_OBJECT

public:
    explicit Registrar(QWidget *parent = 0);
    ~Registrar();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Registrar *ui;
};

#endif // REGISTRAR_H
