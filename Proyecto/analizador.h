#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Analizador; }
QT_END_NAMESPACE

class Analizador : public QWidget
{
    Q_OBJECT

public:
    Analizador(QWidget *parent = nullptr);
    ~Analizador();

private slots:
    void on_btnAbrir_clicked();

    void on_btnGuardar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnAnalizar_clicked();

private:
    Ui::Analizador *ui;
};
#endif // ANALIZADOR_H
