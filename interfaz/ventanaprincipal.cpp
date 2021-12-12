#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(Kernel *k, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanaPrincipal)
    , ker(k)
    , escena(new GraficoPrincipal(this))
    , barraYaGraficada(false)
{
    ui->setupUi(this);

    crearMenus();
    crearFrameModelo();
    crearIconos();
    crearFrameDimension();
    crearBotonesPrincipales();
    crearPagGeometria();
    crearPanelMensajes();
    crearVistaPrincipal();
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

    QHBoxLayout* hLayGeneral = new QHBoxLayout;
    QVBoxLayout* vBoxDimensiones = new QVBoxLayout;

    //---------------------------------------------------------------------
    // Seleccion de tipo de perfil de barra
    //---------------------------------------------------------------------

    QHBoxLayout* layTipoBarra = new QHBoxLayout;
    cbTipoBarra = new QComboBox;
    cbTipoBarra->addItems(PG.geometriaPerfilBarra);
    cbTipoBarra->setCurrentIndex(-1);
    QLabel* lbTipoBarra = new QLabel(PG.lbPerfilBarra);
    layTipoBarra->addWidget(lbTipoBarra);
    layTipoBarra->addWidget(cbTipoBarra);

    vBoxDimensiones->addItem(layTipoBarra);

    //---------------------------------------------------------------------
    //  Creacion linea de longitud de barra
    //---------------------------------------------------------------------

    QHBoxLayout* layLongitud = new QHBoxLayout;
    leLongitudBarra = new QLineEdit;
    leLongitudBarra->setText(QString::number(PG.longBarraInicial));
    leLongitudBarra->setMaximumWidth(100);
    lbLongitudBarra = new QLabel(PG.lbLongitudBarra);
    leLongitudBarra->setValidator(new QDoubleValidator(0.0, 1000.0, 1, this));
    layLongitud->addWidget(lbLongitudBarra);
    layLongitud->addWidget(leLongitudBarra);
    layLongitud->setAlignment(leLongitudBarra, Qt::AlignLeft);
    vBoxDimensiones->addItem(layLongitud);

    connect(leLongitudBarra, SIGNAL(editingFinished()),
            this, SLOT(longitudBarraCambiada()));

    //---------------------------------------------------------------------
    //  Creacion bloque seleccion de secciones
    //---------------------------------------------------------------------

    QVBoxLayout* vLayArea = new QVBoxLayout;
    QGroupBox* gbAreaTransversal = new QGroupBox(PG.gbAreaTransversal, this);
    gbAreaTransversal->setMinimumHeight(150);

    // ---------- Seccion simetria ----------------------------------------

    QHBoxLayout* hLaySimetria = new QHBoxLayout;
    btgSimetria = new QButtonGroup;
    QRadioButton* rbSim = new QRadioButton(PG.geometriaSimetria[0]);
    QRadioButton* rbUni = new QRadioButton(PG.geometriaSimetria[1]);
    btgSimetria->addButton(rbSim);
    btgSimetria->addButton(rbUni);
    hLaySimetria->addWidget(rbSim);
    hLaySimetria->addSpacing(20);
    hLaySimetria->addWidget(rbUni);
    hLaySimetria->insertStretch(-1);
    vLayArea->addItem(hLaySimetria);

    // ---------- Seleccion valor area ------------------------------------
    gdArea = new QGridLayout;
    lbValorArea1 = new QLabel();
    leValorArea1 = new QLineEdit;
    leValorArea1->setText(QString::number(PG.area1BarraInicial));
    leValorArea1->setMaximumWidth(100);
    gdArea->addWidget(lbValorArea1,0,0);
    gdArea->addWidget(leValorArea1,0,1,Qt::AlignLeft);

    lbValorArea2 = new QLabel();
    leValorArea2 = new QLineEdit;
    leValorArea2->setText(QString::number(PG.area2BarraInicial));
    leValorArea2->setMaximumWidth(100);
    gdArea->addWidget(lbValorArea2,1,0);
    gdArea->addWidget(leValorArea2,1,1,Qt::AlignLeft);

    gdArea->setSpacing(5);
    vLayArea->addItem(gdArea);

    //---------- Metodo interpolacion -----------------------------------

    cbInterpolacion = new QComboBox;
    cbInterpolacion->addItems(PG.cbInterpolacion);
    lbInterpolacion = new QLabel(PG.lbInterpolacion);
    gdArea->addWidget(lbInterpolacion,2,0);
    gdArea->addWidget(cbInterpolacion,2,1);


    //--------------------------------------------------------------------

    connect(cbTipoBarra, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this,
            &VentanaPrincipal::cbVariacionAreaCambiado);

    connect(leValorArea1, SIGNAL(editingFinished()),
            this, SLOT(valorAreaCambiado()));

    connect(leValorArea2, SIGNAL(editingFinished()), this, SLOT(valorAreaFinalCambiado()));

    gbAreaTransversal->setLayout(vLayArea);

    vBoxDimensiones->addWidget(gbAreaTransversal);
    vBoxDimensiones->addSpacing(30);

    //---------------------------------------------------------------------
    //  Creacion bloque seleccion de coordenadas
    //---------------------------------------------------------------------

    QHBoxLayout* layCoord = new QHBoxLayout;
    QComboBox* cbCoord = new QComboBox();
    cbCoord->addItems(PG.cbPosCoord);
    QLabel* lbCoord = new QLabel(PG.lbCoord);
    layCoord->addWidget(lbCoord);
    layCoord->addWidget(cbCoord);
    vBoxDimensiones->addItem(layCoord);

    //---------------------------------------------------------------------
    //  Creacion de tabla
    //---------------------------------------------------------------------

    tvPuntos = new QTableView;
    ker->conectarTVAreas(tvPuntos);

    vLayTabla = new QVBoxLayout;

    tvPuntos->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    tvPuntos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tvPuntos->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tvPuntos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tvPuntos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tvPuntos->verticalHeader()->setVisible(true);
    tvPuntos->hide();
    tvPuntos->hideColumn(1);
    tvPuntos->hideColumn(3);

    vLayTabla->addWidget(tvPuntos);

    vLayTabla->addStretch(1);

    //----------- Botones tabla ----------------------------------------

    QHBoxLayout* hBoxBotTabla = new QHBoxLayout;

    pbAgregarLineaTabla = new QPushButton;
    pbEliminarLineaTabla = new QPushButton;
    pbAgregarLineaTabla->setText(PG.pbAgregarLineaTabla);
    pbEliminarLineaTabla->setText(PG.pbEliminarLineaTabla);
    hBoxBotTabla->addWidget(pbAgregarLineaTabla);
    hBoxBotTabla->addWidget(pbEliminarLineaTabla);
    connect(pbAgregarLineaTabla, &QAbstractButton::pressed, [this](){ker->modificarNroLineasModAreas(1);});
    connect(pbEliminarLineaTabla, &QAbstractButton::pressed, [this](){ker->modificarNroLineasModAreas(-1);});

    vLayTabla->addItem(hBoxBotTabla);

    // ---------- Seleccion valores relativos ------------------------------

    QHBoxLayout* hBoxChckTabla = new QHBoxLayout;
    hBoxChckTabla->addStretch();
    chbMostrarPosRelativa = new QCheckBox(PG.chbMostrarPosRelativa);
    chbMostrarAreaRelativa = new QCheckBox(PG.chbMostrarAreaRelativa);
    hBoxChckTabla->addWidget(chbMostrarPosRelativa);
    hBoxChckTabla->addSpacing(20);
    hBoxChckTabla->addWidget(chbMostrarAreaRelativa);

    connect(chbMostrarAreaRelativa, &QCheckBox::stateChanged, [this](int state){
            state==Qt::Unchecked ? tvPuntos->hideColumn(3) : tvPuntos->showColumn(3);});

    connect(chbMostrarPosRelativa, &QCheckBox::stateChanged, [this](int state){
            state==Qt::Unchecked ? tvPuntos->hideColumn(1) : tvPuntos->showColumn(1);});

    vLayTabla->addItem(hBoxChckTabla);

    //---------------------------------------------------------------------
    //  Layout general
    //---------------------------------------------------------------------

    QGroupBox* gbDimensiones = new QGroupBox(PG.gbDimensiones,this);
    gbDimensiones->setLayout(vBoxDimensiones);
    gbDimensiones->setMinimumWidth(700);

    hLayGeneral->addWidget(gbDimensiones);
    hLayGeneral->addItem(vLayTabla);
    hLayGeneral->setAlignment(gbDimensiones, Qt::AlignLeft);

    cbTipoBarra->setCurrentIndex(0);
    pGeom->setLayout(hLayGeneral);

}

void VentanaPrincipal::moduloSeleccionado(bool seleccionado)
{
    if(seleccionado) ui->stackedWidget->setCurrentIndex(grBotonesModulos->checkedId());
}

void VentanaPrincipal::crearPanelMensajes()
{
    teLogMensaje = new QTextEdit(this);
    teLogMensaje->setText("Aca van a aparecer mensajes copados");

    QPushButton* miBoton = new QPushButton("O",this);

    ui->panelMensajes->addWidget(teLogMensaje,0,0,2,1);
    ui->panelMensajes->addWidget(miBoton,1,1);

    teLogMensaje->setMaximumHeight(50);

    connect(miBoton, &QAbstractButton::pressed, [this](){
        teLogMensaje->setMaximumHeight(teLogMensaje->maximumHeight() == 50 ? 200 : 50);
    });
}

void VentanaPrincipal::crearVistaPrincipal()
{
    ui->vistaGeometria->setScene(escena);
    ui->vistaGeometria->setMinimumHeight(350);
    ui->vistaGeometria->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton* btnVista = new QPushButton(ui->vistaGeometria);
    btnVista->setText("Graficar");
    btnVista->setStyleSheet("QPushButton {background-color: #f7f3c6; border-radius: 4;"
                            "border-color:black; border-style: solid; border-width : 2}");
    btnVista->move(5,5);

    QPushButton* btnBorrar = new QPushButton(ui->vistaGeometria);
    btnBorrar->setText("Borrar");
    btnBorrar->setStyleSheet("QPushButton {background-color: #eba29d; border-radius: 4;"
                            "border-color:black; border-style: solid; border-width : 2}");
    btnBorrar->move(5,55);

    QPushButton* btnCentrar = new QPushButton(ui->vistaGeometria);
    btnCentrar->setText("Centrar");
    btnCentrar->setStyleSheet("QPushButton {background-color: #e1a8ff; border-radius: 4;"
                              "border-color:black; border-style: solid; border-width : 2}");

    btnCentrar->move(5,110);

    connect(btnVista, &QAbstractButton::pressed, this, &VentanaPrincipal::graficarBarra);
    connect(btnBorrar, &QAbstractButton::pressed, this, &VentanaPrincipal::borrarBarra);
    connect(btnCentrar, &QAbstractButton::pressed, this, &VentanaPrincipal::centrarBarra);

    QPushButton* btnRotar = new QPushButton(ui->vistaGeometria);
    btnRotar->setText("Rotar");
    btnRotar->setStyleSheet("QPushButton {background-color: #e3e0bf; border-radius: 4;"
                              "border-color:black; border-style: solid; border-width : 2}");

    btnRotar->move(5,165);
    connect(btnRotar, &QAbstractButton::pressed, this, &VentanaPrincipal::rotarBarra);

}

void VentanaPrincipal::graficarBarra()
{
    borrarBarra();
    barraYaGraficada = true;
    QVector<QPointF> verticesBarra;
    QVector<QPointF> puntosControl;

    ker->calcularPuntosBarra(verticesBarra,puntosControl);
    escena->graficarBarra(verticesBarra,puntosControl, ker->getPerfilVariacionArea());

    ui->vistaGeometria->ajustarViewport();
    ui->vistaGeometria->maximizarContenido();
}

void VentanaPrincipal::actualizarDibujoBarra()
{
    if(barraYaGraficada) graficarBarra();
}

void VentanaPrincipal::borrarBarra()
{
    barraYaGraficada = false;
    escena->clear();
}

void VentanaPrincipal::centrarBarra()
{
    if (barraYaGraficada)
        ui->vistaGeometria->maximizarContenido();
}

void VentanaPrincipal::rotarBarra()
{
    ui->vistaGeometria->rotate(15);
}

void VentanaPrincipal::mensajeStatusBar(const QString& msj)
{
    statusBar()->showMessage(msj);
}

void VentanaPrincipal::actualizarBarra(double area1, double area2, double longitud)
{
    if(leValorArea1->text().toDouble() != area1) {
        leValorArea1->setText(QString::number(area1,'g',2));
        emit sigValorArea1Cambiado(area1);
    }

    if(leValorArea2->text().toDouble() != area2) {
        leValorArea2->setText(QString::number(area2,'g',2));
        emit sigValorArea2Cambiado(area2);
    }

    if(leLongitudBarra->text().toDouble() != longitud) {
        leLongitudBarra->setText(QString::number(longitud,'g',2));
        emit sigLongitudBarraCambiado(longitud);
    }
}

void VentanaPrincipal::actualizarPuntoBarra(int pto, double pos, double area)
{
    emit sigPuntoCambiado(pto, pos, area);
}

void VentanaPrincipal::printMensaje(const QString &msj, tipoMensaje t)
{
    QString msjEditado;
    QString hora = "[" + QTime::currentTime().toString().trimmed() + "]  ";
    if(t == tipoMensaje::ERROR)
    {
        msjEditado = R"(<p style="color:red">)" + hora + msj + R"(</p>)";
    }
    teLogMensaje->append(msjEditado);
}

void VentanaPrincipal::cbVariacionAreaCambiado(const QString &s)
{

    if(s == PG.geometriaPerfilBarra[0])  //Uniforme
    {
        leLongitudBarra->show();
        lbLongitudBarra->show();

        lbValorArea1->show();
        lbValorArea1->setText(PG.lbAreaUnica);
        leValorArea1->show();
        lbValorArea2->hide();
        leValorArea2->hide();

        tvPuntos->hide();
        pbAgregarLineaTabla->hide();
        pbEliminarLineaTabla->hide();
        chbMostrarPosRelativa->hide();
        chbMostrarAreaRelativa->hide();

        cbInterpolacion->hide();
        lbInterpolacion->hide();

        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(false);

        emit sigPerfilAreaCambiado(perfilVariacionArea::CONSTANTE);
    }
    else if (s == PG.geometriaPerfilBarra[1]) //Variacion lineal
    {
        leLongitudBarra->show();
        lbLongitudBarra->show();

        lbValorArea1->show();
        lbValorArea1->setText(PG.lbAreaDual[0]);
        leValorArea1->show();
        lbValorArea2->show();
        lbValorArea2->setText(PG.lbAreaDual[1]);
        leValorArea2->show();

        tvPuntos->hide();
        pbAgregarLineaTabla->hide();
        pbEliminarLineaTabla->hide();
        chbMostrarPosRelativa->hide();
        chbMostrarAreaRelativa->hide();

        cbInterpolacion->hide();
        lbInterpolacion->hide();

        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(true);

        emit sigPerfilAreaCambiado(perfilVariacionArea::LINEAL);
    }
    else if (s == PG.geometriaPerfilBarra[2]) // Constante por tramos
    {
        leLongitudBarra->hide();
        lbLongitudBarra->hide();

        tvPuntos->show();
        lbValorArea1->hide();
        leValorArea1->hide();
        lbValorArea2->hide();
        leValorArea2->hide();
        pbAgregarLineaTabla->show();
        pbEliminarLineaTabla->show();
        chbMostrarPosRelativa->show();
        chbMostrarAreaRelativa->show();

        cbInterpolacion->hide();
        lbInterpolacion->hide();

        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(true);

        emit sigPerfilAreaCambiado(perfilVariacionArea::CONSTANTEPORTRAMOS);
    }
    else if (s == PG.geometriaPerfilBarra[3]) // Variacion multipunto
    {
        leLongitudBarra->hide();
        lbLongitudBarra->hide();

        tvPuntos->show();
        lbValorArea1->hide();
        leValorArea1->hide();
        lbValorArea2->hide();
        leValorArea2->hide();
        pbAgregarLineaTabla->show();
        pbEliminarLineaTabla->show();
        chbMostrarPosRelativa->show();
        chbMostrarAreaRelativa->show();

        cbInterpolacion->show();
        lbInterpolacion->show();

        foreach(QAbstractButton* bt, btgSimetria->buttons()) bt->setEnabled(true);

        emit sigPerfilAreaCambiado(perfilVariacionArea::MULTIPUNTO);
    }
}

void VentanaPrincipal::longitudBarraCambiada()
{
    float longitudBarra = leLongitudBarra->text().toDouble();
    emit sigLongitudBarraCambiado(longitudBarra);
    graficarBarra();
}

void VentanaPrincipal::valorAreaCambiado()
{
    float areaReferencia = leValorArea1->text().toDouble();
    emit sigValorArea1Cambiado(areaReferencia);
    graficarBarra();
}

void VentanaPrincipal::valorAreaFinalCambiado()
{
    float areaReferencia = leValorArea2->text().toDouble();
    emit sigValorArea2Cambiado(areaReferencia);
    graficarBarra();
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
