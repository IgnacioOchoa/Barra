#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanaPrincipal)
{
    ui->setupUi(this);

    crearMenus();
    crearFrameModelo();
    crearIconos();
    crearFrameDimension();
    crearBotonesPrincipales();

    escena = new QGraphicsScene(this);
    ui->vistaGeometria->setScene(escena);

    ui->textEdit->setText("Aca van a aparecer mensajes copados");

    modeloElegido = -1;

}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::crearMenus()
{
    menuArchivo = menuBar()->addMenu("Archivo");
    menuProyecto = menuBar()->addMenu("Proyecto");
    menuOpciones = menuBar()->addMenu("Opciones");
    menuAjustes = menuBar()->addMenu("Ajustes");
    menuAyuda = menuBar()->addMenu("Ayuda");
}

void VentanaPrincipal::crearFrameModelo()
{
     QLabel* modelo = new QLabel("Transferencia térmica", this);
     QLabel* estado = new QLabel("Estado estacionario", this);
     QLabel* incognita = new QLabel("Incógnita: temperatura", this);

     QVBoxLayout* labelLayout = new QVBoxLayout;
     labelLayout->addWidget(modelo);
     labelLayout->addWidget(estado);
     labelLayout->addWidget(incognita);

     QHBoxLayout* modelLayout = new QHBoxLayout;

     QPixmap pixmap1D(":/imagenesIconos/Imagenes/icono1D.png");
     QIcon icono1D(pixmap1D);
     pbDim = new QPushButton(pixmap1D, QString(), this);
     pbDim->setIconSize(QSize(200,100));
     pbDim->setCursor(Qt::PointingHandCursor);
     pbDim->setObjectName("pbDim");
     pbDim->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     pbDim->installEventFilter(this);

     modelLayout->addWidget(pbDim);

     QPixmap pixmapProblemaFisico(":/imagenesIconos/Imagenes/iconoProblemaVacio.png");
     QIcon iconoModelo(pixmapProblemaFisico);
     pbModelo = new QPushButton(iconoModelo, QString(), this);
     pbModelo->setIconSize(QSize(100,100));
     pbModelo->setCursor(Qt::PointingHandCursor);
     pbModelo->setObjectName("pbModelo");
     pbModelo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

     modelLayout->addWidget(pbModelo);

     //---------------------------------------------------------------------
     //     Frame seleccion Estatico-Dinamico
     //---------------------------------------------------------------------

     QButtonGroup* bgDinEst = new QButtonGroup;
     QVBoxLayout* DElayout = new QVBoxLayout;
     QCheckBox* chBoxEstatico = new QCheckBox("Estático");
     QCheckBox* chBoxDinamico = new QCheckBox("Dinámico");

     bgDinEst->addButton(chBoxEstatico);
     bgDinEst->addButton(chBoxDinamico);
     DElayout->addWidget(chBoxEstatico);
     DElayout->addWidget(chBoxDinamico);

     chBoxEstatico->setChecked(true);

     QFrame* frDinEst = new QFrame(this);
     frDinEst->setObjectName("FrameEstaticoDinamico");
     frDinEst->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
     frDinEst->setLayout(DElayout);

     modelLayout->addWidget(frDinEst);

     //---------------------------------------------------------------------
     //     Frame seleccion Lineal-No Lineal
     //---------------------------------------------------------------------

     QButtonGroup* bgLinNoLin = new QButtonGroup;
     QVBoxLayout* LNLlayout = new QVBoxLayout;
     QCheckBox* chBoxLineal = new QCheckBox("Lineal");
     QCheckBox* chBoxNoLineal = new QCheckBox("No Lineal");

     bgLinNoLin->addButton(chBoxLineal);
     bgLinNoLin->addButton(chBoxNoLineal);
     LNLlayout->addWidget(chBoxLineal);
     LNLlayout->addWidget(chBoxNoLineal);

     chBoxLineal->setChecked(true);

     QFrame* frLinNoLin = new QFrame(this);
     frLinNoLin->setObjectName("FrameLinealNoLineal");
     frLinNoLin->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
     frLinNoLin->setLayout(LNLlayout);

     modelLayout->addWidget(frLinNoLin);

     //---------------------------------------------------------------------------------

     QFrame *linea1 = new QFrame(this);
     linea1->setFrameShape(QFrame::VLine);
     modelLayout->addWidget(linea1);
     modelLayout->addItem(labelLayout);

     ui->frameModelo->setLayout(modelLayout);
     connect(pbModelo, &QAbstractButton::clicked, this, &VentanaPrincipal::lanzarVentanaModelo);
     connect(pbDim, &QAbstractButton::clicked, this, &VentanaPrincipal::seleccionarDimension);

}

void VentanaPrincipal::crearIconos()
{
    iconoDim1D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono1D.png"));
    iconoDim2D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono2D.png"));
    iconoDim3D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono3D.png"));
}

void VentanaPrincipal::crearBotonesPrincipales()
{
    grBotonesModulos = new QButtonGroup;

    QList<QPushButton*> listaBotones = {ui->pbGeometria, ui->pbMalla, ui->pbFisica, ui->pbCondBorde,
                                       ui->pbSalida, ui->pbSimulacion};

    for(int i=0; i < listaBotones.length(); i++)
    {
        grBotonesModulos->addButton(listaBotones[i],i);
        listaBotones[i]->setCheckable(true);
        connect(listaBotones[i], &QAbstractButton::clicked, this, &VentanaPrincipal::moduloSeleccionado);
        listaBotones[i]->installEventFilter(this);
    }

    grBotonesModulos->setExclusive(true);
    listaBotones[0]->setChecked(true);
}

void VentanaPrincipal::crearFrameDimension()
{
    frDimension = new QFrame(this);
    frDimension->setStyleSheet("QFrame { background-color : white}");
    frDimension->setGeometry(20,170,300,500);
    frDimension->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frDimension->setFrameShape(QFrame::Panel);
    QVBoxLayout* vbLay = new QVBoxLayout;

    QList<QIcon*> iconos = {iconoDim1D, iconoDim2D, iconoDim3D};

    foreach (QIcon* icn, iconos)
    {
        QPushButton* bt = new QPushButton(*icn, QString(), frDimension);
        bt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        bt->setIconSize(QSize(frDimension->width()-30,frDimension->height()/3));
        bt->setStyleSheet("QPushButton {background-color : transparent}");
        bt->setCursor(Qt::PointingHandCursor);
        connect(bt, &QAbstractButton::pressed, [this](){frDimension->hide();});
        vbLay->addWidget(bt);
    }

    frDimension->setLayout(vbLay);
    frDimension->hide();
}

void VentanaPrincipal::moduloSeleccionado(bool seleccionado)
{
    if(seleccionado) ui->stackedWidget->setCurrentIndex(grBotonesModulos->checkedId());
}

void VentanaPrincipal::lanzarVentanaModelo()
{
    DialogSeleccionModelo* dlg = new DialogSeleccionModelo(this, modeloElegido);

    dlg->show();
    connect(dlg, &DialogSeleccionModelo::sigModeloCambiado, this, &VentanaPrincipal::modeloCambiado);

}

void VentanaPrincipal::seleccionarDimension()
{
    if(!frDimension->isVisible()) frDimension->show();
}

void VentanaPrincipal::modeloCambiado(int nroModelo)
//Este slot es llamado desde DialogoSeleccionModelo con el nuevo modelo elegido
{
    if (nroModelo == -1) return;
    QPixmap px(Modelos::getListaModelosFisicos()[nroModelo].imagenIcono);
    pbModelo->setIcon(QIcon(px));
    modeloElegido = nroModelo;
}

bool VentanaPrincipal::eventFilter(QObject *obj, QEvent *ev)
{
    if (QString(obj->metaObject()->className()) == "QPushButton")
    {
        if(ev->type() == QEvent::MouseButtonPress || ev->type() == QEvent::WindowBlocked)
        {
            mousePressEvent(static_cast<QMouseEvent*>(ev));
        }
    }
    return false;
}

void VentanaPrincipal::mousePressEvent(QMouseEvent *event)
{
    // Si el frDimension esta desplegado y hago click en otro lugar que no sea el frame,
    // quiero que el frame se minimice sin hacer nada mas.
    if (frDimension->isVisible()
            && !(frDimension->geometry().contains(event->pos()))
            && !(pbDim->geometry().contains(event->pos())))
    {
        frDimension->setVisible(false);
    }
    QMainWindow::mousePressEvent(event);
}
