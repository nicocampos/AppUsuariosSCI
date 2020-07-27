#ifndef USUARIO_H
#define USUARIO_H

#include "xmlhandler.h"
#include "miusuario.h"
#include "photoedit.h"
#include "camera.h"
#include <QDialog>
#include <QFile>
#include <QList>

#define VER_USUARIOS    6

namespace Ui{
class Usuarioconfig;
}

class Usuarioconfig : public QDialog
{
    Q_OBJECT

public:
    explicit Usuarioconfig(QWidget *parent = 0);
    ~Usuarioconfig();

//    void setUsuarios(QFile &);

private slots:
    void on_PB_USR_ADD_clicked();

    void on_PB_Cancelar_clicked();

    void on_lineEdit_Nombre_editingFinished();

    void on_lineEdit_Apellido_editingFinished();

    void on_lineEdit_Username_editingFinished();

//    void on_lineEdit_Foto_editingFinished();

    void on_lineEdit_Username_textEdited(const QString &arg1);

    void nombreClicked(void);

    void apellidoClicked(void);

    void userNameClicked(void);

//    void fotoClicked(void);

    void on_PB_Aceptar_clicked();

    void on_PB_SelecFoto_clicked();

    void on_PB_SacarFoto_clicked();

private:
    Ui::Usuarioconfig *ui;

    QPushButton *PB_usuarios[6];
    QList<Miusuario> usuarios;
    int posScroll;
    QStringList *listaUsuarios;
    QString *pathFoto;
    XmlHandler *m_datosXml;

    Photoedit *editPhoto;
    Camera *camWindow;

    void setEnabled_Add(bool);
    void validateUserName(const QString &);
    void CargarUsuarios(void);
    void MostrarUsuario(void);
};

#endif // USUARIO_H
