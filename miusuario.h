#ifndef MIUSUARIO_H
#define MIUSUARIO_H

#include <QIcon>
#include <QString>

class Miusuario
{
public:
    Miusuario();
    Miusuario(const Miusuario &);
    Miusuario(const QString &, const QString &, const QString &, const QIcon &);
    ~Miusuario();

    void setNombre(QString );
    void setApellido(QString );
    void setNombreUsuario(QString );
    void setFoto(QString);

    QIcon getFoto(void);
    QString getPhoto(){return foto2;}

private:
    QString *nombre;
    QString *apellido;
    QString *nombreDeUsuario;
    QIcon *foto;
    QString foto2;

};

#endif // MIUSUARIO_H
