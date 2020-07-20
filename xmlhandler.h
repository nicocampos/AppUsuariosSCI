#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QtXml>
#include <QFile>
#include <QDir>

/*!
 * Tags de la estrucura de datos XML
 */
#define USUARIO        "usuario"

#define GENERAL         "general"
    #define NOMBRE          "nombre"
    #define APELLIDO        "apellido"
    #define NOMBRE_USUARIO  "nombreUsuario"
    #define IMAGEN          "imagen"
    #define CARPETA         "carpeta"

#define CONFIG          "config"
    #define MODO_ENTRADA    "modoEntrada"
    #define TIEMPO_BARRIDO  "tiempoBarrido"

#define APPS        "apps"

#define DEFAULT_INDENT  4

enum XmlType {NUEVO_XML_USUARIO, ABRIR_XML_USUARIO};

class XmlHandler
{
public:
    XmlHandler();
    XmlHandler(const QString &nombreArchivo, XmlType modo);

    bool save(); // escribe los datos en el archivo XML
    bool load (QFileDevice &file); // recupera los datos del archivo XML

    bool setContenidoGeneral(const QString &tagName, const QString &contenido);
    QString getContenidoGeneral(const QString &tagName);
    bool setContenidoConfig(const QString &tagName, const QString &contenido);
    QString getContenidoConfig(const QString &tagName);
    bool setContenidoApps(const QString &tagName, const QString &contenido);
    QString getContenidoApps(const QString &tagName);

private:
    void crearEstructuraUsuario();
    void addElemento(const QString &parentNode, const QString &tagName,
                     const QString &contenido = QString());

    QDomDocument m_doc;
    QFile m_file;
    QDir m_dir;
};

#endif // XMLHANDLER_H
