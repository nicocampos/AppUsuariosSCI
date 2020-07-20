#include "miusuario.h"

Miusuario::Miusuario()
{
    nombre = nullptr;
    apellido = nullptr;
    nombreDeUsuario = nullptr;
    foto = nullptr;
}

Miusuario::Miusuario(const Miusuario &usuario)
{
    nombre = usuario.nombre;
    apellido = usuario.apellido;
    nombreDeUsuario = usuario.nombreDeUsuario;
    foto = usuario.foto;
}

Miusuario::Miusuario(const QString &pNombre,const QString &pApellido, const QString &pNombreUsuario, const QIcon &pFoto)
{
    nombre = new QString(pNombre);
    apellido = new QString(pApellido);
    nombreDeUsuario = new QString(pNombreUsuario);
    foto = new QIcon(pFoto);
}

Miusuario::~Miusuario()
{

}

void Miusuario::setNombre(QString pNombre)
{
    nombre = new QString(pNombre);
}

void Miusuario::setApellido(QString pApellido)
{
    apellido = new QString(pApellido);
}

void Miusuario::setNombreUsuario(QString pNombreUsuario)
{
    nombreDeUsuario = new QString(pNombreUsuario);
}

void Miusuario::setFoto(QString pFoto)
{
    foto = new QIcon(pFoto);
}

QIcon Miusuario::getFoto()
{
    return *foto;
}
