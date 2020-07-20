#include "usuario.h"
#include "ui_usuario.h"
#include <QIcon>
#include <QDir>
#include <QFileDialog>
#include <QDebug>

#define VALIUSERNAME    " !#$%&/()=?'¿¡*,\"|°¬~´¨+\\{}[]:;,-@<>`^"
#define DIRUSUARIOS     QDir::currentPath()+"/sci/usuarios/"
#define CANT_USUARIOS   listaUsuarios->length()-2                   // el 2 es para no tener en cuenta el . y ..


Usuario::Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usuario)
{
    ui->setupUi(this);
    m_datosXml = nullptr;
    pathFoto = nullptr;
    posScroll = 0;

    //*****************************************************************************
    //         Connect asociados al evento del click sobre los Line Edit
    //*****************************************************************************
    connect(ui->lineEdit_Nombre,SIGNAL(MousePressed()),this,SLOT(nombreClicked()));
    connect(ui->lineEdit_Apellido,SIGNAL(MousePressed()),this,SLOT(apellidoClicked()));
    connect(ui->lineEdit_Username,SIGNAL(MousePressed()),this,SLOT(userNameClicked()));
    connect(ui->lineEdit_Foto,SIGNAL(MousePressed()),this,SLOT(fotoClicked()));
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los pushbutton asociados a los usuarios en una lista
    //*****************************************************************************
    PB_usuarios[0] = ui->PB_USR1;
    PB_usuarios[1] = ui->PB_USR2;
    PB_usuarios[2] = ui->PB_USR3;
    PB_usuarios[3] = ui->PB_USR4;
    PB_usuarios[4] = ui->PB_USR5;
    PB_usuarios[5] = ui->PB_USR6;
    //*****************************************************************************

    CargarUsuarios();
    MostrarUsuario();
}

Usuario::~Usuario()
{
    delete ui;
}

void Usuario::CargarUsuarios(void)
{
    QFile filename;
    QDir dirUsuarios(DIRUSUARIOS);
    //dirUsuarios.setFilter(QDir::NoDotAndDotDot);
    listaUsuarios = new QStringList(dirUsuarios.entryList());

    Miusuario aux;
    m_datosXml = new XmlHandler();
    for(int i = 2; i < listaUsuarios->length(); i++){
        filename.setFileName(DIRUSUARIOS+listaUsuarios->at(i));
        m_datosXml->load(filename);
        aux.setNombre(m_datosXml->getContenidoGeneral(NOMBRE));
        aux.setApellido(m_datosXml->getContenidoGeneral(APELLIDO));
        aux.setNombreUsuario(m_datosXml->getContenidoGeneral(NOMBRE_USUARIO));
        aux.setFoto(m_datosXml->getContenidoGeneral(IMAGEN));

        usuarios.append(aux);
    }
}

void Usuario::MostrarUsuario(void)
{
    // VER_USUARIOS es por la cantidad de usuarios que puedo mostrar
    if(CANT_USUARIOS <= VER_USUARIOS){
        for(int i = 0; i < CANT_USUARIOS; i++){
//            QPixmap photo(usuarios.value(i).getPhoto());
//            photo.scaled(70,90);
            PB_usuarios[i]->setIcon(usuarios.value(i).getFoto());
            PB_usuarios[i]->setEnabled(true);
        }
    }
    else{
        // Pendiente....
    }
}

/**
 * \brief void Usuario::setEnabled_Add(bool opcion)
 * \param opcion Si es verdadero, habilita los lineEdit y PushBottom,
 *              caso contrario los deshabilita
 * \return Void
 */
void Usuario::setEnabled_Add(bool opcion)
{
    ui->PB_Aceptar->setEnabled(opcion);
    ui->PB_Cancelar->setEnabled(opcion);

    ui->lineEdit_Nombre->setEnabled(opcion);
    ui->lineEdit_Apellido->setEnabled(opcion);
    ui->lineEdit_Username->setEnabled(opcion);
    ui->lineEdit_Foto->setEnabled(opcion);
}

// Valido que el nombre de usuario no tenga
// caracteres extraños
void Usuario::validateUserName(const QString &arg1)
{
    QString text = arg1;
    QString Vali_UserName(VALIUSERNAME);
    for(int i = 0; i < text.size(); ++i)
        foreach(const QChar &x, Vali_UserName)
            if(text.at(i) == x)
                text.remove(x);
    ui->lineEdit_Username->setText(text);
}



void Usuario::on_PB_USR_ADD_clicked()
{
    // Habilito los campos a rellenar y buttons
    setEnabled_Add(true);
}

void Usuario::on_PB_Aceptar_clicked()
{
    if(ui->PB_Aceptar->text() == "Aceptar"){
        m_datosXml = new XmlHandler(ui->lineEdit_Username->text(), NUEVO_XML_USUARIO);
        // Estos métodos cargan los datos a la estructura XML
        m_datosXml->setContenidoGeneral(NOMBRE, ui->lineEdit_Nombre->text());
        m_datosXml->setContenidoGeneral(APELLIDO, ui->lineEdit_Apellido->text());
        m_datosXml->setContenidoGeneral(NOMBRE_USUARIO, ui->lineEdit_Username->text());
        m_datosXml->setContenidoGeneral(IMAGEN, *pathFoto);
        m_datosXml->setContenidoGeneral(CARPETA, DIRUSUARIOS);

        if (m_datosXml->save() == true)
            on_PB_Cancelar_clicked();
    }
//    else{

//    }
}

void Usuario::on_PB_Cancelar_clicked()
{
    // Vuelvo al color de fondo de la ventana
    ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: window;}");

    // Deshabilito los campos a rellenar y buttons
    setEnabled_Add(false);

    // Seteo los nombres por defecto de los campos
    ui->lineEdit_Nombre->setText("Nombre:");
    ui->lineEdit_Apellido->setText("Apellido:");
    ui->lineEdit_Username->setText("Nombre de usuario:");
    ui->lineEdit_Foto->setText("Foto:");

    // Borro la vista previa
    QIcon vista_previa;
    ui->PB_VistaPrevia->setIcon(vista_previa);  // Seteo un QIcon vacio
}

// **************************************************
// Auto-completar los campos en caso de estar vacios
// **************************************************
void Usuario::on_lineEdit_Nombre_editingFinished()
{
    if(ui->lineEdit_Nombre->text() == "")
        ui->lineEdit_Nombre->setText("Nombre:");
}

void Usuario::on_lineEdit_Apellido_editingFinished()
{
    if(ui->lineEdit_Apellido->text() == "")
        ui->lineEdit_Apellido->setText("Apellido:");
}

void Usuario::on_lineEdit_Username_editingFinished()
{
    if(ui->lineEdit_Username->text() == ""){
        ui->lineEdit_Username->setText("Nombre de usuario:");
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: white;}");
    }
}

void Usuario::on_lineEdit_Foto_editingFinished()
{
    if(ui->lineEdit_Foto->text() == "")
        ui->lineEdit_Foto->setText("Foto:");
}
// **************************************************
// **************************************************

// **************************************************
//  Chequeo de nombre de usuarios
// **************************************************
void Usuario::on_lineEdit_Username_textEdited(const QString &new_user)
{
    QFile fileUsuario;

    validateUserName(new_user);

    if(fileUsuario.exists(DIRUSUARIOS+"/"+new_user+".sci")){
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: rgb(255, 88, 32);}");
    }
    else{
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: rgb(157, 255, 65);}");
    }
}
// **************************************************
// **************************************************

// **************************************************
//  Acciones frente a evento del click en Line Edit
// **************************************************
void Usuario::nombreClicked()
{
    ui->lineEdit_Nombre->clear();
}

void Usuario::apellidoClicked()
{
    ui->lineEdit_Apellido->clear();
}

void Usuario::userNameClicked()
{
    ui->lineEdit_Username->clear();
}

void Usuario::fotoClicked()
{
    // Abro la ventana para buscar la imagen
    pathFoto = new QString(QFileDialog::getOpenFileName(this, tr("Elegir Imagen"),
                                                    QDir::homePath(), tr("Imagenes (*.png *.jpg *.jpeg)")));

    // Si esta vacio no hago nada
    if(!pathFoto->isEmpty()){
        // Seteo la imagen en vista previa
        QIcon vista_previa(*pathFoto);
        ui->PB_VistaPrevia->setIcon(vista_previa);
        // Cargo el nombre de la imagen en el line edit
        ui->lineEdit_Foto->clear();
        ui->lineEdit_Foto->setText(pathFoto->section('/',pathFoto->count('/'),pathFoto->count('/')));
    }

}
// **************************************************
// **************************************************




