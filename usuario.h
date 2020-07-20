#ifndef USUARIO_H
#define USUARIO_H

#include "xmlhandler.h"
#include "miusuario.h"
#include <QDialog>
#include <QFile>
#include <QList>

#define VER_USUARIOS    6

namespace Ui {
class Usuario;
}

class Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Usuario(QWidget *parent = 0);
    ~Usuario();

//    void setUsuarios(QFile &);

private slots:
    void on_PB_USR_ADD_clicked();

    void on_PB_Cancelar_clicked();

    void on_lineEdit_Nombre_editingFinished();

    void on_lineEdit_Apellido_editingFinished();

    void on_lineEdit_Username_editingFinished();

    void on_lineEdit_Foto_editingFinished();

    void on_lineEdit_Username_textEdited(const QString &arg1);

    void nombreClicked(void);

    void apellidoClicked(void);

    void userNameClicked(void);

    void fotoClicked(void);

    void on_PB_Aceptar_clicked();

private:
    Ui::Usuario *ui;

    QPushButton *PB_usuarios[6];
    QList<Miusuario> usuarios;
    int posScroll;
    QStringList *listaUsuarios;
    QString *pathFoto;
    XmlHandler *m_datosXml;


    void setEnabled_Add(bool);
    void validateUserName(const QString &);
    void CargarUsuarios(void);
    void MostrarUsuario(void);
};

#endif // USUARIO_H
