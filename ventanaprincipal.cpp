#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanaPrincipal)
{
    ui->setupUi(this);

    longitudBarra = 10.0;

    crearMenus();
    crearFrameModelo();
    crearIconos();
    crearFrameDimension();
    crearBotonesPrincipales();
    crearPagGeometria();
    crearModeloAreas();
    crearPanelMensajes();

    escena = new QGraphicsScene(this);
    ui->vistaGeometria->setScene(escena);
    ui->vistaGeometria->setMinimumHeight(350);
    ui->vistaGeometria->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    modeloElegido = -1;

    mensajeStatusBar("Aplicación lista");
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
     frDinEst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     frDinEst->setMaximumWidth(140);
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
     frLinNoLin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     frLinNoLin->setMaximumWidth(140);
     frLinNoLin->setLayout(LNLlayout);

     modelLayout->addWidget(frLinNoLin);

     //--------------------------------------------------------------------------------
     //     Linea Vertical
     //--------------------------------------------------------------------------------

     QFrame *linea1 = new QFrame(this);
     linea1->setFrameShape(QFrame::VLine);
     modelLayout->addWidget(linea1);

     //--------------------------------------------------------------------------------
     //     Frame ecuacion
     //--------------------------------------------------------------------------------

     QFrame *frEcuacion = new QFrame(this);
     frEcuacion->setObjectName("frameEcuacion");

     QVBoxLayout* vbLayEcuacion = new QVBoxLayout;
     QLabel* ecLabel = new QLabel("Ecuación");
     vbLayEcuacion->addWidget(ecLabel);
     ecLabel->setAlignment(Qt::AlignCenter);
     frEcuacion->setLayout(vbLayEcuacion);

     //frEcuacion->setMaximumWidth(250);
     frEcuacion->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     modelLayout->addWidget(frEcuacion);

     //--------------------------------------------------------------------------------
     //     Linea Vertical
     //--------------------------------------------------------------------------------

     QFrame *linea2 = new QFrame(this);
     linea2->setFrameShape(QFrame::VLine);
     modelLayout->addWidget(linea2);


     //---------------------------------------------------------------------
     //     Seccion de checkboxes de status
     //---------------------------------------------------------------------

     int anguloRotacion = 45;

     QCheckBox* chBoxGeomLista = new QCheckBox("Geometría");
     QCheckBox* chBoxMallaLista = new QCheckBox("Malla");
     QCheckBox* chBoxParamFisLista = new QCheckBox("Param Fis");
     QCheckBox* chBoxCBLista = new QCheckBox("Cond Borde");
     QCheckBox* chBoxOpSalidaLista = new QCheckBox("Op Salida");
     QCheckBox* chBoxSimulacionLista = new QCheckBox("Simulación");

     chBoxGeomLista->setObjectName("chBoxGeometriaLista");
     chBoxMallaLista->setObjectName("chBoxMallaLista");
     chBoxParamFisLista->setObjectName("chBoxParamFisLista");
     chBoxCBLista->setObjectName("chBoxCBLista");
     chBoxOpSalidaLista->setObjectName("chBoxOpSalidaLista");
     chBoxSimulacionLista->setObjectName("chBoxSimulacionLista");

     QList<QCheckBox*> listaCheckBoxes =
     {chBoxGeomLista, chBoxMallaLista, chBoxParamFisLista,
      chBoxCBLista, chBoxOpSalidaLista, chBoxSimulacionLista};

     foreach(QCheckBox* cb, listaCheckBoxes)
     {
         cb->setLayoutDirection(Qt::RightToLeft);
     }

     QGraphicsScene* sceneStatusModulos = new QGraphicsScene(this);
     QGraphicsView* viewStatusModulos = new QGraphicsView(this);
     viewStatusModulos->setObjectName("vistaStatusModulos");
     viewStatusModulos->setMaximumHeight(130);
     viewStatusModulos->setMinimumHeight(120);
     viewStatusModulos->setMaximumWidth(350);
     viewStatusModulos->setScene(sceneStatusModulos);
     modelLayout->addWidget(viewStatusModulos);

     QList<QGraphicsProxyWidget*> listaGPWidgets;
     foreach(QCheckBox* cb, listaCheckBoxes)
     {
         cb->setFont(QFont(QApplication::font().family(),11));
         listaGPWidgets.append(sceneStatusModulos->addWidget(cb));
     }

     viewStatusModulos->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

     QList<int> posicionesHorizontales = {-120,-80,-40,0,40,80};

     //El TransformOriginPoint se mueve junto con el item al hacer moveBy, y no necesariamente
     //coincide con el origen del graphics item.

     int posIndx = 0;
     foreach(QGraphicsProxyWidget* gpw, listaGPWidgets)
     {
         gpw->setTransformOriginPoint(QPointF(gpw->size().width(), 0));
         gpw->moveBy(-gpw->size().width(), 0);
         gpw->setRotation(anguloRotacion);
         gpw->moveBy(posicionesHorizontales[posIndx++], 0);
     }

     //--------------------------------------------------------------------------------------------
     //   Boton Calcular
     //--------------------------------------------------------------------------------------------

     pbCalcular = new QPushButton(this);
     pbCalcular->setObjectName("pbCalcular");
     pbCalcular->setText("Calcular");
     pbCalcular->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     pbCalcular->setMaximumWidth(200);
     modelLayout->addWidget(pbCalcular);

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

void VentanaPrincipal::crearPagGeometria()
{
    QWidget* pGeom = ui->pagGeometria;
    modeloAreasBarra = new ModeloAreasBarra(longitudBarra);

    QHBoxLayout* hLayGeneral = new QHBoxLayout;
    QVBoxLayout* vBoxDimensiones = new QVBoxLayout;

    //---------------------------------------------------------------------
    //  Creacion linea de longitud de barra
    //---------------------------------------------------------------------

    QHBoxLayout* layLongitud = new QHBoxLayout;
    leLongitudBarra = new QLineEdit;
    leLongitudBarra->setText("10.0");
    leLongitudBarra->setMaximumWidth(100);
    lbLongitudBarra = new QLabel("Longitud de la barra");
    leLongitudBarra->setValidator(new QDoubleValidator(0.0, 1000.0, 1, this));
    layLongitud->addWidget(lbLongitudBarra);
    layLongitud->addSpacing(165);
    layLongitud->addWidget(leLongitudBarra);
    layLongitud->setAlignment(leLongitudBarra, Qt::AlignLeft);
    vBoxDimensiones->addItem(layLongitud);

    connect(leLongitudBarra, SIGNAL(editingFinished()),
            this, SLOT(longitudBarraCambiada()));

    //---------------------------------------------------------------------
    //  Creacion bloque seleccion de secciones
    //---------------------------------------------------------------------

    QVBoxLayout* vLayArea = new QVBoxLayout;
    QGroupBox* gbAreaTransversal = new QGroupBox("Area transversal", this);
    gbAreaTransversal->setMinimumHeight(150);

    // ---------- Seccion simetria ----------------------------------------

    QHBoxLayout* hLaySimetria = new QHBoxLayout;
    btgSimetria = new QButtonGroup;
    QRadioButton* rbSim = new QRadioButton("Simetrica");
    QRadioButton* rbUni = new QRadioButton("Unilateral");
    btgSimetria->addButton(rbSim);
    btgSimetria->addButton(rbUni);
    hLaySimetria->addWidget(rbSim);
    hLaySimetria->addSpacing(20);
    hLaySimetria->addWidget(rbUni);
    hLaySimetria->insertStretch(-1);
    vLayArea->addItem(hLaySimetria);

    // ---------- Seccion areas -------------------------------------------
    gdArea = new QGridLayout;
    //gdArea->setRowMinimumHeight(1, 50);
    QComboBox* cbArea = new QComboBox;
    cbArea->addItems({"Uniforme", "Variación lineal", "Variación multipunto"});
    cbArea->setCurrentIndex(-1);
    QLabel* lbArea = new QLabel("Area transversal");
    gdArea->addWidget(lbArea,0,0);
    gdArea->addWidget(cbArea,0,1);

    // ---------- Seleccion valor area ------------------------------------
    lbValorArea = new QLabel("Valor area");
    leValorArea = new QLineEdit;
    leValorArea->setMaximumWidth(100);
    gdArea->addWidget(lbValorArea,1,0);
    gdArea->addWidget(leValorArea,1,1,Qt::AlignLeft);

    gdArea->setColumnStretch(0,5);
    gdArea->setColumnStretch(1,3);
    gdArea->setSpacing(5);
    vLayArea->addItem(gdArea);

    connect(cbArea, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this,
            &VentanaPrincipal::cbVariacionAreaCambiado);

    connect(leValorArea, SIGNAL(editingFinished()),
            this, SLOT(valorAreaCambiada()));

    gbAreaTransversal->setLayout(vLayArea);

    vBoxDimensiones->addWidget(gbAreaTransversal);
    vBoxDimensiones->addSpacing(30);

    //---------------------------------------------------------------------
    //  Creacion bloque seleccion de coordenadas
    //---------------------------------------------------------------------

    QHBoxLayout* layCoord = new QHBoxLayout;
    QComboBox* cbCoord = new QComboBox();
    cbCoord->addItems({"Inicio de la barra","Centro de la barra","Final de la barra", "Otro punto"});
    QLabel* lbCoord = new QLabel("Posición del origen");
    layCoord->addWidget(lbCoord);
    layCoord->addWidget(cbCoord);
    vBoxDimensiones->addItem(layCoord);

    //---------------------------------------------------------------------
    //  Creacion de tabla
    //---------------------------------------------------------------------

    twPuntos = new QTableView;
    twPuntos->setModel(modeloAreasBarra);

    QVBoxLayout* vLayTabla = new QVBoxLayout;

    twPuntos->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    twPuntos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twPuntos->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twPuntos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    twPuntos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    twPuntos->verticalHeader()->setVisible(true);
    twPuntos->hide();
    twPuntos->hideColumn(1);
    twPuntos->hideColumn(3);

    vLayTabla->addWidget(twPuntos);

    //----------- Botones tabla ----------------------------------------

    QHBoxLayout* hBoxBotTabla = new QHBoxLayout;

    pbAgregarLineaTabla = new QPushButton;
    pbEliminarLineaTabla = new QPushButton;
    pbAgregarLineaTabla->setText("Agregar fila");
    pbEliminarLineaTabla->setText("Borrar fila");
    hBoxBotTabla->addWidget(pbAgregarLineaTabla);
    hBoxBotTabla->addWidget(pbEliminarLineaTabla);
    connect(pbAgregarLineaTabla, &QAbstractButton::pressed, [this](){modeloAreasBarra->insertRows(0,0);});
    connect(pbEliminarLineaTabla, &QAbstractButton::pressed, [this](){modeloAreasBarra->removeRows(0,0);});

    vLayTabla->addItem(hBoxBotTabla);

    // ---------- Seleccion valores relativos ------------------------------

    QHBoxLayout* hBoxChckTabla = new QHBoxLayout;
    hBoxChckTabla->addStretch();
    chbMostrarPosRelativa = new QCheckBox("Posición relativa");
    chbMostrarAreaRelativa = new QCheckBox("Area relativa");
    hBoxChckTabla->addWidget(chbMostrarPosRelativa);
    hBoxChckTabla->addSpacing(20);
    hBoxChckTabla->addWidget(chbMostrarAreaRelativa);

    connect(chbMostrarAreaRelativa, &QCheckBox::stateChanged, [this](int state){
            state==Qt::Unchecked ? twPuntos->hideColumn(3) : twPuntos->showColumn(3);});

    connect(chbMostrarPosRelativa, &QCheckBox::stateChanged, [this](int state){
            state==Qt::Unchecked ? twPuntos->hideColumn(1) : twPuntos->showColumn(1);});

    vLayTabla->addItem(hBoxChckTabla);

    //---------------------------------------------------------------------
    //  Layout general
    //---------------------------------------------------------------------

    QGroupBox* gbDimensiones = new QGroupBox("Dimensiones",this);
    gbDimensiones->setLayout(vBoxDimensiones);
    gbDimensiones->setMinimumWidth(700);

    hLayGeneral->addWidget(gbDimensiones);
    hLayGeneral->addItem(vLayTabla);
    hLayGeneral->setAlignment(gbDimensiones, Qt::AlignLeft);

    cbArea->setCurrentIndex(0);
    pGeom->setLayout(hLayGeneral);

}

void VentanaPrincipal::moduloSeleccionado(bool seleccionado)
{
    if(seleccionado) ui->stackedWidget->setCurrentIndex(grBotonesModulos->checkedId());
}

void VentanaPrincipal::crearPanelMensajes()
{
    QTextEdit* teMensaje = new QTextEdit(this);
    teMensaje->setText("Aca van a aparecer mensajes copados");

    QPushButton* miBoton = new QPushButton("O",this);

    ui->panelMensajes->addWidget(teMensaje,0,0,2,1);
    ui->panelMensajes->addWidget(miBoton,1,1);

    teMensaje->setMaximumHeight(50);

    connect(miBoton, &QAbstractButton::pressed, [teMensaje](){
        teMensaje->setMaximumHeight(teMensaje->maximumHeight() == 50 ? 200 : 50);
    });
}

void VentanaPrincipal::crearModeloAreas()
{

}

void VentanaPrincipal::mensajeStatusBar(const QString& msj)
{
    statusBar()->showMessage(msj);
}

void VentanaPrincipal::cbVariacionAreaCambiado(const QString &s)
{
    if(s == "Uniforme")
    {
        twPuntos->hide();
        lbValorArea->show();
        leValorArea->show();
        pbAgregarLineaTabla->hide();
        pbEliminarLineaTabla->hide();
        chbMostrarPosRelativa->hide();
        chbMostrarAreaRelativa->hide();
        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(false);
    }
    else if (s == "Variación lineal")
    {
        twPuntos->show();
        lbValorArea->hide();
        leValorArea->hide();
        pbAgregarLineaTabla->hide();
        pbEliminarLineaTabla->hide();
        chbMostrarPosRelativa->show();
        chbMostrarAreaRelativa->show();
        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(true);
    }
    else
    {
        twPuntos->show();
        lbValorArea->hide();
        leValorArea->hide();
        pbAgregarLineaTabla->show();
        pbEliminarLineaTabla->show();
        chbMostrarPosRelativa->show();
        chbMostrarAreaRelativa->show();
        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(true);
    }
}

void VentanaPrincipal::longitudBarraCambiada()
{
    longitudBarra = leLongitudBarra->text().toDouble();
    modeloAreasBarra->longitudCambiada(longitudBarra);
}

void VentanaPrincipal::valorAreaCambiada()
{
    areaReferencia = leValorArea->text().toDouble();
    modeloAreasBarra->areaReferenciaCambiada(areaReferencia);
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
