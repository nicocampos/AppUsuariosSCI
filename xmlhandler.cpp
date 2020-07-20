#include "xmlhandler.h"

/*!
 * \brief XmlHandler::XmlHandler
 */
XmlHandler::XmlHandler()
{
    // Defino el nombre del archivo por default (vacío)
    m_file.setFileName(QString());
}

/*!
 * \brief XmlHandler::XmlHandler
 * \param nombreArchivo
 * \param modo
 */
XmlHandler::XmlHandler(const QString &nombreArchivo, XmlType modo)
{
    switch (modo) {
        case NUEVO_XML_USUARIO:
            m_file.setFileName(nombreArchivo+".sci");
            crearEstructuraUsuario();
            break;

        case ABRIR_XML_USUARIO:
            m_file.setFileName(nombreArchivo);
            break;

    }
}

/*!
 * \brief XmlHandler::save
 * \return
 */
bool XmlHandler::save()
{
    QFile file(getContenidoGeneral(CARPETA)+"/"+getContenidoGeneral(NOMBRE_USUARIO)+".sci");

    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) == true ) {
        // Escribe los datos en el archivo XML
        QTextStream stream(&file);
        m_doc.save(stream, DEFAULT_INDENT, QDomNode::EncodingFromDocument);
        file.close();
        return true;
    }
    else
        return false;
}

/*!
 * \brief XmlHandler::load
 * \param file
 * \return
 */
bool XmlHandler::load(QFileDevice &file)
{
    return (m_doc.setContent(&file));
}

bool XmlHandler::setContenidoGeneral(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(GENERAL).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true)
            element.firstChild().setNodeValue(contenido);
        else
            element.appendChild(m_doc.createTextNode(contenido));

        return true;
    } else
        return false;
}

QString XmlHandler::getContenidoGeneral(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(GENERAL).firstChildElement(tagName);
    if(!element.isNull())
        return (element.text());
    else
        return (QString::number(-1));
}

bool XmlHandler::setContenidoConfig(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(CONFIG).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true)
            element.firstChild().setNodeValue(contenido);
        else
            element.appendChild(m_doc.createTextNode(contenido));

        return true;
    } else
        return false;
}

QString XmlHandler::getContenidoConfig(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(CONFIG).firstChildElement(tagName);
    if(!element.isNull())
        return (element.text());
    else
        return (QString::number(-1));
}

bool XmlHandler::setContenidoApps(const QString &tagName, const QString &contenido)
{

}

QString XmlHandler::getContenidoApps(const QString &tagName)
{

}

/*!
 * \brief XmlHandler::crearEstructuraUsuario
 */
void XmlHandler::crearEstructuraUsuario()
{
    // Crea el encabezado del archivo XML y lo agrega al documento
    QDomProcessingInstruction instr = m_doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    m_doc.appendChild(instr);

    // Crea el elemento 'raiz' (usuario) y lo agrega al documento
    QDomElement root = m_doc.createElement(USUARIO);
    m_doc.appendChild(root);

    // Crea los elementos principales
    root.appendChild(m_doc.createElement(GENERAL));
    root.appendChild(m_doc.createElement(CONFIG));
    root.appendChild(m_doc.createElement(APPS));

    // Crea los sub-elementos dentro de 'general'
    addElemento(GENERAL, NOMBRE);
    addElemento(GENERAL, APELLIDO);
    addElemento(GENERAL, NOMBRE_USUARIO);
    addElemento(GENERAL, IMAGEN);
    addElemento(GENERAL, CARPETA);

    // Crea los sub-elementos dentro de 'config'
    addElemento(CONFIG, MODO_ENTRADA);
    addElemento(CONFIG, TIEMPO_BARRIDO);

    // Crea los sub-elementos dentro de 'apps'
    //addElemento(APPS, ); Falta definir!
}

/*!
 * \brief XmlHandler::addElemento
 * \param parentNode
 * \param tagName
 * \param contenido
 * Crea un nuevo 'tag' en un determinado 'parent node' ( puede o no incluir un 'contenido' )
 */
void XmlHandler::addElemento(const QString &parentNode, const QString &tagName, const QString &contenido)
{
    if( m_doc.documentElement().firstChildElement(parentNode).firstChildElement(tagName).isNull() )
    {
        QDomElement newElement = m_doc.createElement(tagName);

        m_doc.documentElement().firstChildElement(parentNode).appendChild(newElement);

        if( !contenido.isNull() )
            newElement.appendChild(m_doc.createTextNode(contenido));
    }
}
