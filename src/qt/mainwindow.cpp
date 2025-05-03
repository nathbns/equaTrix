#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QTimer>
#include <QScrollBar>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QIcon>
#include <complex>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

const unsigned int MATRIX_COLUMN_WIDTH = 50;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    
    // Set window title, size and icon
    setWindowTitle("equaTrix");
    this->showMaximized();

    QIcon appIcon(":/logo.png");
    QApplication::setWindowIcon(appIcon);   

    // Loading the external style file
    QFile styleFile(":/styles.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QTextStream stream(&styleFile);
        this->setStyleSheet(stream.readAll());
        styleFile.close();
    } else {
        qDebug() << "Impossible de charger le fichier de style";
    }
    
    // Initialize dark mode to false
    isDarkMode = false;
    
    // Create main tab widget
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    
    // Create the dark mode button
    darkModeButton = new QPushButton(this);
    darkModeButton->setText("◑");
    darkModeButton->setFixedSize(40, 32); 
    darkModeButton->setToolTip("Changer de thème (clair/sombre)");
    darkModeButton->setStyleSheet("font-size: 18px; font-weight: bold; padding-bottom: 3px;");

    
    // Position the button in the upper right corner
    QWidget *cornerWidget = new QWidget(this);
    QHBoxLayout *cornerLayout = new QHBoxLayout(cornerWidget);
    cornerLayout->addWidget(darkModeButton);
    cornerLayout->setContentsMargins(0, 0, 10, 0);
    tabWidget->setCornerWidget(cornerWidget, Qt::TopRightCorner);
    
    // Connect the button signal to the toggle function
    connect(darkModeButton, &QPushButton::clicked, this, &MainWindow::toggleDarkMode);
    
    // Setup tabs
    setupMatrixTab();
    setupSystemTab();
    setupIntegrationTab();
    setupFunctionTab();
    setupAnalysisTab();
    
    // Connect tab change signal
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged); // Connect the tab change signal to the onTabChanged method
}

void MainWindow::setupMatrixTab(){
    matrixTab = new QWidget(); // Create a new QWidget for the matrix tab
    QVBoxLayout *mainLayout = new QVBoxLayout(matrixTab); // Create a new QVBoxLayout for the matrix tab
    
    // Create top section with matrix inputs
    QHBoxLayout *matricesLayout = new QHBoxLayout();
    
    // Matrix A section
    QGroupBox *matrixAGroup = new QGroupBox("Matrice A :");
    QVBoxLayout *matrixALayout = new QVBoxLayout(matrixAGroup);
    
    // Matrix A size controls
    QHBoxLayout *matrixASizeLayout = new QHBoxLayout();
    QLabel *matrixASizeLabel = new QLabel("Taille :");
    matrixARowsSpinBox = new QSpinBox();
    matrixARowsSpinBox->setRange(2, 6);
    matrixARowsSpinBox->setValue(3);
    QLabel *matrixAXLabel = new QLabel("×");
    matrixAColsSpinBox = new QSpinBox();
    matrixAColsSpinBox->setRange(2, 6);
    matrixAColsSpinBox->setValue(3);
    
    matrixASizeLayout->addWidget(matrixASizeLabel);
    matrixASizeLayout->addWidget(matrixARowsSpinBox);
    matrixASizeLayout->addWidget(matrixAXLabel);
    matrixASizeLayout->addWidget(matrixAColsSpinBox);
    matrixALayout->addLayout(matrixASizeLayout);
    
    // Matrix A table
    matrixATable = new QTableWidget();
    matrixATable->setRowCount(3);
    matrixATable->setColumnCount(3);
    matrixATable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    matrixATable->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixATable->horizontalHeader()->hide();
    matrixATable->verticalHeader()->hide();
    
    // Enable automatic scroll bars
    matrixATable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    matrixATable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    matrixALayout->addWidget(matrixATable);
    
    // Matrix A operations
    QGroupBox *matrixAOpsGroup = new QGroupBox("Calcul sur A :");
    QGridLayout *matrixAOpsLayout = new QGridLayout(matrixAOpsGroup);
    
    determinantAButton = new QPushButton("Déterminant");
    transposeAButton = new QPushButton("Transposé");
    inverseAButton = new QPushButton("Inverse");
    rankAButton = new QPushButton("Rang");
    kerAButton = new QPushButton("Ker(A)");
    imAButton = new QPushButton("Im(A)");
    trAButton = new QPushButton("tr(A)");
    powAButton = new QPushButton("Puissances de A");
    eigenValAButton = new QPushButton("Spec(A)");
    vectAButton = new QPushButton("Vecteurs propres");
    
    matrixAOpsLayout->addWidget(determinantAButton, 0, 0);
    matrixAOpsLayout->addWidget(transposeAButton, 1, 0);
    matrixAOpsLayout->addWidget(inverseAButton, 2, 0);
    matrixAOpsLayout->addWidget(rankAButton, 3, 0);
    matrixAOpsLayout->addWidget(kerAButton, 0, 1);
    matrixAOpsLayout->addWidget(imAButton, 1, 1);
    matrixAOpsLayout->addWidget(trAButton, 2, 1);
    matrixAOpsLayout->addWidget(powAButton, 3, 1);
    matrixAOpsLayout->addWidget(eigenValAButton, 4, 0);
    matrixAOpsLayout->addWidget(vectAButton, 4, 1);
    
    
    matrixALayout->addWidget(matrixAOpsGroup);
    
    // Matrix B section
    QGroupBox *matrixBGroup = new QGroupBox("Matrice B :");
    QVBoxLayout *matrixBLayout = new QVBoxLayout(matrixBGroup); 
    
    // Matrix B size controls
    QHBoxLayout *matrixBSizeLayout = new QHBoxLayout();
    QLabel *matrixBSizeLabel = new QLabel("Taille :");
    matrixBRowsSpinBox = new QSpinBox();
    matrixBRowsSpinBox->setRange(2, 6);
    matrixBRowsSpinBox->setValue(3);
    QLabel *matrixBXLabel = new QLabel("×");
    matrixBColsSpinBox = new QSpinBox();
    matrixBColsSpinBox->setRange(2, 6);
    matrixBColsSpinBox->setValue(3);
    
    matrixBSizeLayout->addWidget(matrixBSizeLabel);
    matrixBSizeLayout->addWidget(matrixBRowsSpinBox);
    matrixBSizeLayout->addWidget(matrixBXLabel);
    matrixBSizeLayout->addWidget(matrixBColsSpinBox);
    matrixBLayout->addLayout(matrixBSizeLayout);
    
    // Matrix B table
    matrixBTable = new QTableWidget();
    matrixBTable->setRowCount(3);
    matrixBTable->setColumnCount(3);
    matrixBTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    matrixBTable->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixBTable->horizontalHeader()->hide();
    matrixBTable->verticalHeader()->hide();
    
    // Enable automatic scroll bars
    matrixBTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    matrixBTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    
    matrixBLayout->addWidget(matrixBTable);
    
    // Matrix B operations
    QGroupBox *matrixBOpsGroup = new QGroupBox("Calcul sur B :");
    QGridLayout *matrixBOpsLayout = new QGridLayout(matrixBOpsGroup);
    
    determinantBButton = new QPushButton("Déterminant");
    transposeBButton = new QPushButton("Transposé");
    inverseBButton = new QPushButton("Inverse");
    rankBButton = new QPushButton("Rang");
    kerBButton = new QPushButton("Ker(B)");
    imBButton = new QPushButton("Im(B)");
    trBButton = new QPushButton("tr(B)");
    powBButton = new QPushButton("Puissances de B");
    eigenValBButton = new QPushButton("Spec(B)");
    vectBButton = new QPushButton("Vecteurs propres");
    
    matrixBOpsLayout->addWidget(determinantBButton, 0, 0);
    matrixBOpsLayout->addWidget(inverseBButton, 1, 0);
    matrixBOpsLayout->addWidget(transposeBButton, 2, 0);
    matrixBOpsLayout->addWidget(rankBButton, 3, 0);
    matrixBOpsLayout->addWidget(kerBButton, 0, 1);
    matrixBOpsLayout->addWidget(imBButton, 1, 1);
    matrixBOpsLayout->addWidget(trBButton, 2, 1);
    matrixBOpsLayout->addWidget(powBButton, 3, 1);
    matrixBOpsLayout->addWidget(eigenValBButton, 4, 0);
    matrixBOpsLayout->addWidget(vectBButton, 4, 1);
    
    matrixBLayout->addWidget(matrixBOpsGroup);
    
    // Operations between A and B
    QGroupBox *matrixOpsGroup = new QGroupBox("Calcul sur A et B :");
    QVBoxLayout *matrixOpsLayout = new QVBoxLayout(matrixOpsGroup);
    
    multiplyButton = new QPushButton("A * B");
    addButton = new QPushButton("A + B");
    subtractButton = new QPushButton("A - B");
    compareButton = new QPushButton("<==>");
    
    matrixOpsLayout->addWidget(multiplyButton);
    matrixOpsLayout->addWidget(addButton);
    matrixOpsLayout->addWidget(subtractButton);
    matrixOpsLayout->addWidget(compareButton);
    
    // Add all sections to matrices layout
    matricesLayout->addWidget(matrixAGroup);
    matricesLayout->addWidget(matrixOpsGroup);
    matricesLayout->addWidget(matrixBGroup);

    // Create history section
    QGroupBox *historyGroup = new QGroupBox("Historique:");
    historyGroup->setObjectName("historyGroup");
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    historyTextEdit = new QTextEdit();
    historyTextEdit->setReadOnly(true);
    historyLayout->addWidget(historyTextEdit);
    
    // Add a button to clear history
    clearHistoryButton = new QPushButton("Effacer l'historique");
    historyLayout->addWidget(clearHistoryButton);
    
    // Create result section
    QGroupBox *resultGroup = new QGroupBox("Résultat :");
    resultGroup->setObjectName("resultGroup");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    resultMatrixTable = new QTableWidget();
    resultMatrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultMatrixTable->verticalHeader()->hide();
    resultMatrixTable->verticalHeader()->hide();
    
    // Initialize the result table
    resultMatrixTable->setRowCount(3);
    resultMatrixTable->setColumnCount(3);
    
    // Enable automatic scrollbars for the results table
    resultMatrixTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    resultMatrixTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    
    // Number the rows and columns for the result table
    for (int i = 0; i < 3; i++) {
        resultMatrixTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
        resultMatrixTable->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
    }
    
    resultLayout->addWidget(resultMatrixTable);
    
    // Add all sections to main layout
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(matricesLayout);
    topLayout->addWidget(resultGroup);
    
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(historyGroup);
    
    // Add tab to tab widget
    tabWidget->addTab(matrixTab, "Matrice");
    
    // Connect signals and slots for matrix resizing
    connect(matrixARowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeMatrixA);
    connect(matrixAColsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeMatrixA);
    connect(matrixBRowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeMatrixB);
    connect(matrixBColsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeMatrixB);
    
    // Connect button to clear history
    connect(clearHistoryButton, &QPushButton::clicked, this, &MainWindow::clearMatrixHistory);
    
    // Connect signals for operation buttons
    connect(multiplyButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixOperation);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixOperation);
    connect(subtractButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixOperation);
    connect(compareButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixOperation);
    
    // Connect signals for property buttons
    connect(determinantAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(transposeAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(inverseAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(rankAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(kerAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(imAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(trAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(powAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(eigenValAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(vectAButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);

    connect(determinantBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(transposeBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(inverseBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(rankBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(kerBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(imBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(trBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(powBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(eigenValBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);
    connect(vectBButton, &QPushButton::clicked, this, &MainWindow::calculateMatrixProperty);

    // Connect table cell changes to update the internal data model
    connect(matrixATable, &QTableWidget::cellChanged, [this](int row, int column) {
        if (row >= 0 && column >= 0 && row < matrixAData.size() && column < matrixAData[0].size()) {
            QTableWidgetItem *item = matrixATable->item(row, column);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixAData[row][column] = ok ? value : 0.0;
            }
        }
    });
    
    connect(matrixBTable, &QTableWidget::cellChanged, [this](int row, int column) {
        if (row >= 0 && column >= 0 && row < matrixBData.size() && column < matrixBData[0].size()) {
            QTableWidgetItem *item = matrixBTable->item(row, column);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixBData[row][column] = ok ? value : 0.0;
            }
        }
    });
    
    // Initialize matrices and data model
    matrixAData.resize(3);
    matrixBData.resize(3);
    for (int i = 0; i < 3; ++i) {
        matrixAData[i].resize(3);
        for (int j = 0; j < 3; ++j) {
            matrixAData[i][j] = 0.0;
        }
        
        matrixBData[i].resize(3);
        for (int j = 0; j < 3; ++j) {
            matrixBData[i][j] = 0.0;
        }
    }
    
    // Initialize matrices
    resizeMatrixA();
    resizeMatrixB();
    
    // Connect table widget resize events
    matrixATable->installEventFilter(this);
    matrixBTable->installEventFilter(this);
    resultMatrixTable->installEventFilter(this);
}

void MainWindow::setupIntegrationTab()
{
    integrationTab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(integrationTab);
    
    // Split the tab into left and right sections
    QHBoxLayout *splitLayout = new QHBoxLayout();
    mainLayout->addLayout(splitLayout);
    
    // Left section for controls
    QVBoxLayout *leftLayout = new QVBoxLayout();
    splitLayout->addLayout(leftLayout);
    
    // Input section
    QGroupBox *inputGroup = new QGroupBox("Paramètres d'intégration:");
    QGridLayout *inputLayout = new QGridLayout(inputGroup);
    
    // Function input
    QLabel *functionLabel = new QLabel("Fonction f(x):");
    integrationFunctionEdit = new QLineEdit();
    integrationFunctionEdit->setPlaceholderText("Exemple: x^2 + 3*x + 2");
    inputLayout->addWidget(functionLabel, 0, 0);
    inputLayout->addWidget(integrationFunctionEdit, 0, 1, 1, 3);
    
    // Bounds input
    QLabel *boundsLabel = new QLabel("Bornes:");
    QLabel *lowerBoundLabel = new QLabel("a ");
    integrationLowerBoundEdit = new QLineEdit();
    integrationLowerBoundEdit->setPlaceholderText("0");
    QLabel *upperBoundLabel = new QLabel("b ");
    integrationUpperBoundEdit = new QLineEdit();
    integrationUpperBoundEdit->setPlaceholderText("1");
    
    inputLayout->addWidget(boundsLabel, 1, 0);
    inputLayout->addWidget(lowerBoundLabel, 1, 1);
    inputLayout->addWidget(integrationLowerBoundEdit, 1, 2);
    inputLayout->addWidget(upperBoundLabel, 1, 3);
    inputLayout->addWidget(integrationUpperBoundEdit, 1, 4);
    
    // Intervals input
    QLabel *intervalsLabel = new QLabel("Nombre d'intervalles:");
    integrationIntervalsSpinBox = new QSpinBox();
    integrationIntervalsSpinBox->setRange(1, 1000);
    integrationIntervalsSpinBox->setValue(100);
    
    inputLayout->addWidget(intervalsLabel, 2, 0);
    inputLayout->addWidget(integrationIntervalsSpinBox, 2, 1);
    
    // Calculate button
    calculateIntegralButton = new QPushButton("Calculer l'intégrale");
    calculateIntegralButton->setProperty("class", "action");
    inputLayout->addWidget(calculateIntegralButton, 3, 0, 1, 5);
    
    // Result section
    QGroupBox *resultGroup = new QGroupBox("Résultat:");
    resultGroup->setObjectName("resultGroup");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    integrationResultLabel = new QLabel("Aucun calcul effectué");
    resultLayout->addWidget(integrationResultLabel);
    
    // History section
    QGroupBox *historyGroup = new QGroupBox("Historique:");
    historyGroup->setObjectName("historyGroup");
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    integrationHistoryList = new QListWidget();
    historyLayout->addWidget(integrationHistoryList);
    
    // Add input, result and history to left section
    leftLayout->addWidget(inputGroup);
    leftLayout->addWidget(resultGroup);
    leftLayout->addWidget(historyGroup);
    
    // Right section for graphs
    QVBoxLayout *graphsLayout = new QVBoxLayout();
    
    // First chart for rectangles method
    QGroupBox *rectangleGroup = new QGroupBox("Méthode des rectangles:");
    rectangleGroup->setObjectName("graphGroup");
    QVBoxLayout *rectangleLayout = new QVBoxLayout(rectangleGroup);
    
    // Initialize chart
    rectangleChart = new QChart();
    rectangleChart->setTitle("Intégration par rectangles");
    rectangleChart->legend()->setVisible(true);
    rectangleChart->legend()->setAlignment(Qt::AlignBottom);
    
    // Create axes
    QValueAxis *rectAxisX = new QValueAxis();
    rectAxisX->setTitleText("x");
    QValueAxis *rectAxisY = new QValueAxis();
    rectAxisY->setTitleText("f(x)");
    
    rectangleChart->addAxis(rectAxisX, Qt::AlignBottom);
    rectangleChart->addAxis(rectAxisY, Qt::AlignLeft);
    
    // Create chart view
    rectangleChartView = new QChartView(rectangleChart);
    rectangleChartView->setRenderHint(QPainter::Antialiasing);
    rectangleChartView->setMinimumWidth(500);
    rectangleChartView->setMinimumHeight(250);
    
    rectangleLayout->addWidget(rectangleChartView);
    
    // Second chart for trapezoid method
    QGroupBox *trapezoidGroup = new QGroupBox("Méthode des trapèzes:");
    trapezoidGroup->setObjectName("graphGroup");
    QVBoxLayout *trapezoidLayout = new QVBoxLayout(trapezoidGroup);
    
    // Initialize chart
    trapezoidChart = new QChart();
    trapezoidChart->setTitle("Intégration par trapèzes");
    trapezoidChart->legend()->setVisible(true);
    trapezoidChart->legend()->setAlignment(Qt::AlignBottom);
    
    // Create axes
    QValueAxis *trapAxisX = new QValueAxis();
    trapAxisX->setTitleText("x");
    QValueAxis *trapAxisY = new QValueAxis();
    trapAxisY->setTitleText("f(x)");
    
    trapezoidChart->addAxis(trapAxisX, Qt::AlignBottom);
    trapezoidChart->addAxis(trapAxisY, Qt::AlignLeft);
    
    // Create chart view
    trapezoidChartView = new QChartView(trapezoidChart);
    trapezoidChartView->setRenderHint(QPainter::Antialiasing);
    trapezoidChartView->setMinimumWidth(500);
    trapezoidChartView->setMinimumHeight(250);
    
    trapezoidLayout->addWidget(trapezoidChartView);
    
    // Add both chart groups to the right section
    graphsLayout->addWidget(rectangleGroup);
    graphsLayout->addWidget(trapezoidGroup);
    
    // Add right section to the main layout
    splitLayout->addLayout(graphsLayout);
    splitLayout->setStretch(0, 1); // Left side
    splitLayout->setStretch(1, 2); // Right side (graph takes more space)
    
    // Add tab to tab widget
    tabWidget->addTab(integrationTab, "Intégration");
    
    // Connect signal and slot
    connect(calculateIntegralButton, &QPushButton::clicked, this, &MainWindow::calculateIntegral);
}

void MainWindow::setupSystemTab(){
    systemTab = new QWidget();
    systemTab->setObjectName("systemTab");
    QVBoxLayout *mainLayout = new QVBoxLayout(systemTab);
    
    // System input section
    QGroupBox *inputGroup = new QGroupBox("Système d'équations linéaires:");
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);
    
    // System size controls
    QHBoxLayout *sizeLayout = new QHBoxLayout();
    QLabel *sizeLabel = new QLabel("Nombre d'équations:");
    systemSizeSpinBox = new QSpinBox();
    systemSizeSpinBox->setRange(1, 6);
    systemSizeSpinBox->setValue(3);
    
    QLabel *varsLabel = new QLabel("Nombre d'inconnues:");
    systemVarsSpinBox = new QSpinBox();
    systemVarsSpinBox->setRange(1, 6);
    systemVarsSpinBox->setValue(3);
    
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(systemSizeSpinBox);
    sizeLayout->addWidget(varsLabel);
    sizeLayout->addWidget(systemVarsSpinBox);
    sizeLayout->addStretch();
    
    inputLayout->addLayout(sizeLayout);
    
    // System coefficients grid
    systemGrid = new QGridLayout();
    inputLayout->addLayout(systemGrid);
    
    // Initialize the system grid with correct dimensions
    int rows = systemSizeSpinBox->value(); // number of equations
    int cols = systemVarsSpinBox->value(); // number of unknowns
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            QLineEdit *coefEdit = new QLineEdit("0");
            coefEdit->setFixedWidth(50);
            systemGrid->addWidget(coefEdit, i, j*2);
            
            if(j < cols - 1){
                QLabel *xLabel = new QLabel("x<sub>" + QString::number(j+1) + "</sub> +");
                systemGrid->addWidget(xLabel, i, j*2+1);
            }
            else{
                QLabel *xLabel = new QLabel("x<sub>" + QString::number(j+1) + "</sub> =");
                systemGrid->addWidget(xLabel, i, j*2+1);
                
                QLineEdit *constEdit = new QLineEdit("0");
                constEdit->setFixedWidth(50);
                systemGrid->addWidget(constEdit, i, j*2+2);
            }
        }
    }
    
    // Solve button
    solveSystemButton = new QPushButton("Résoudre le système");
    solveSystemButton->setProperty("class", "action");
    inputLayout->addWidget(solveSystemButton);
    
    // Result section
    QGroupBox *resultGroup = new QGroupBox("Résultat:");
    resultGroup->setObjectName("resultGroup");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    systemResultLabel = new QLabel("Aucun calcul effectué");
    systemResultLabel->setTextFormat(Qt::RichText);
    systemResultLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    systemResultLabel->setWordWrap(true);
    
    // Wrap the label in a scroll area for better display of long results
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(systemResultLabel);
    resultLayout->addWidget(scrollArea);
    
    // History section
    QGroupBox *historyGroup = new QGroupBox("Historique:");
    historyGroup->setObjectName("historyGroup");
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    systemHistoryList = new QListWidget();
    historyLayout->addWidget(systemHistoryList);
    
    // Clear history button
    clearSystemHistoryButton = new QPushButton("Effacer l'historique");
    historyLayout->addWidget(clearSystemHistoryButton);
    
    // Add all sections to main layout
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(resultGroup);
    mainLayout->addWidget(historyGroup);
    
    // Add tab to tab widget
    tabWidget->addTab(systemTab, "Système");
    
    // Connect signals and slots
    connect(systemSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeSystem);
    connect(systemVarsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::resizeSystem);
    connect(solveSystemButton, &QPushButton::clicked, this, &MainWindow::solveSystem);
    connect(clearSystemHistoryButton, &QPushButton::clicked, this, &MainWindow::clearSystemHistory);
}

void MainWindow::setupFunctionTab(){
    functionTab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(functionTab);
    
    // Function input section
    QGroupBox *inputGroup = new QGroupBox("Analyse de fonction:");
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);
    
    // Function input row
    QHBoxLayout *functionInputLayout = new QHBoxLayout();
    QLabel *functionLabel = new QLabel("f(x) =");
    functionEdit = new QLineEdit();
    functionEdit->setPlaceholderText("x^2 - 4*x + 4"); 
    functionInputLayout->addWidget(functionLabel);
    functionInputLayout->addWidget(functionEdit);
    inputLayout->addLayout(functionInputLayout);
    
    // X value input row
    QHBoxLayout *xInputLayout = new QHBoxLayout();
    QLabel *xLabel = new QLabel("x =");
    xValueEdit = new QLineEdit();
    xValueEdit->setPlaceholderText("2");
    xInputLayout->addWidget(xLabel);
    xInputLayout->addWidget(xValueEdit);
    inputLayout->addLayout(xInputLayout);
    
    // Analysis options
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    findDerivativeCheck = new QCheckBox("Dérivée");
    findRootsCheck = new QCheckBox("Racines");
    
    findDerivativeCheck->setChecked(false);
    findRootsCheck->setChecked(false);
    
    optionsLayout->addWidget(findDerivativeCheck);
    optionsLayout->addWidget(findRootsCheck);
    inputLayout->addLayout(optionsLayout);
    
    // Analyze button
    analyzeButton = new QPushButton("Analyser la fonction");
    analyzeButton->setProperty("class", "action");
    inputLayout->addWidget(analyzeButton);
    
    // Result section
    QGroupBox *resultGroup = new QGroupBox("Résultat:");
    resultGroup->setObjectName("resultGroup");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    functionResultText = new QTextEdit();
    functionResultText->setReadOnly(true);
    resultLayout->addWidget(functionResultText);
    
    // History section
    QGroupBox *historyGroup = new QGroupBox("Historique:");
    historyGroup->setObjectName("historyGroup");
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    functionHistoryList = new QListWidget();
    historyLayout->addWidget(functionHistoryList);
    
    // Add export button
    QPushButton *exportButton = new QPushButton("Exporter l'analyse");
    exportButton->setProperty("class", "action");
    mainLayout->addWidget(exportButton);
    
    // Add all sections to main layout
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(resultGroup);
    mainLayout->addWidget(historyGroup);
    
    // Add tab to tab widget
    tabWidget->addTab(functionTab, "Fonction");
    
    // Connect signals and slots
    connect(analyzeButton, &QPushButton::clicked, this, &MainWindow::analyzeFunction);
    connect(exportButton, &QPushButton::clicked, this, &MainWindow::exportFunctionAnalysis);
}

void MainWindow::setupAnalysisTab() {
    analysisTab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(analysisTab);
    
    // Group to load data
    QGroupBox *loadGroup = new QGroupBox("Charger des données:");
    QVBoxLayout *loadLayout = new QVBoxLayout(loadGroup);
    
    // Section for file type selection and upload button
    QHBoxLayout *fileLoadLayout = new QHBoxLayout();
    fileTypeComboBox = new QComboBox();
    fileTypeComboBox->addItem("CSV", "csv");
    fileTypeComboBox->addItem("JSON", "json");
    
    loadFileButton = new QPushButton("Charger un fichier");
    loadFileButton->setProperty("class", "action");
    
    fileLoadLayout->addWidget(fileTypeComboBox);
    fileLoadLayout->addWidget(loadFileButton);
    loadLayout->addLayout(fileLoadLayout);
    
    // Table to display the data
    dataTable = new QTableWidget();
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    loadLayout->addWidget(dataTable);
    
    // Group for visualization
    QGroupBox *visualGroup = new QGroupBox("Visualisation:");
    QVBoxLayout *visualLayout = new QVBoxLayout(visualGroup);
    
    // Button to generate the graph
    visualizeButton = new QPushButton("Générer le graphique");
    visualizeButton->setProperty("class", "action");
    visualizeButton->setEnabled(false); // Disabled until data is loaded
    visualLayout->addWidget(visualizeButton);
    
    // Graph view
    chart = new QChart();
    chart->setTitle("Analyse de fonction");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    visualLayout->addWidget(chartView);
    
    // Add the groups to the main layout
    mainLayout->addWidget(loadGroup, 1);
    mainLayout->addWidget(visualGroup, 2);
    
    // Add the tab to the tab widget
    tabWidget->addTab(analysisTab, "Analyse");
    
    // Connect signals and slots
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::loadDataFile);
    connect(visualizeButton, &QPushButton::clicked, this, &MainWindow::visualizeData);
}

void MainWindow::loadDataFile() {
    QString fileType = fileTypeComboBox->currentData().toString();
    QString filter = fileType == "csv" ? "Fichiers CSV (*.csv)" : "Fichiers JSON (*.json)";
    
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Charger un fichier"), "",
        filter);
        
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Erreur"),
                           tr("Impossible d'ouvrir le fichier %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName),
                                file.errorString()));
        return;
    }
    
    // Reset data
    analysisData.clear();
    dataHeaders.clear();
    dataTable->clear();
    dataTable->setRowCount(0);
    dataTable->setColumnCount(0);
    
    // Completely reset the graph
    chart->removeAllSeries();
    QList<QAbstractAxis*> axes = chart->axes();
    for (QAbstractAxis* axis : axes) {
        chart->removeAxis(axis);
        delete axis;
    }
    chart->setTitle("Analyse des Données");
    
    if (fileType == "csv") {
        // Load CSV data
        QTextStream in(&file);
        QString line = in.readLine(); // Read the first line (headers)
        if (!line.isEmpty()) {
            dataHeaders = line.split(",");
            dataTable->setColumnCount(dataHeaders.size());
            dataTable->setHorizontalHeaderLabels(dataHeaders);
            
            int row = 0;
            while (!in.atEnd()) {
                line = in.readLine();
                QStringList fields = line.split(",");
                
                if (fields.size() > 0) {
                    dataTable->setRowCount(row + 1);
                    QVector<double> rowData;
                    
                    for (int col = 0; col < fields.size() && col < dataHeaders.size(); ++col) {
                        QTableWidgetItem *item = new QTableWidgetItem(fields[col]);
                        dataTable->setItem(row, col, item);
                        
                        bool ok;
                        double value = fields[col].toDouble(&ok);
                        rowData.append(ok ? value : 0.0);
                    }
                    
                    // Ensure that rowData always contains all columns
                    while (rowData.size() < dataHeaders.size()) {
                        rowData.append(0.0);
                    }
                    
                    analysisData.append(rowData);
                    row++;
                }
            }
        }
    } else {
        // Load the JSON data
        QByteArray jsonData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        
        if (doc.isObject()) {
            QJsonObject jsonObj = doc.object();
            
            // If this is the format exported by the export function
            if (jsonObj.contains("function")) {
                dataHeaders << "Type" << "Expression" << "Valeur";
                dataTable->setColumnCount(3);
                dataTable->setHorizontalHeaderLabels(dataHeaders);
                
                int row = 0;
                
                // Function
                dataTable->setRowCount(row + 1);
                dataTable->setItem(row, 0, new QTableWidgetItem("Fonction"));
                dataTable->setItem(row, 1, new QTableWidgetItem(jsonObj["function"].toString()));
                dataTable->setItem(row, 2, new QTableWidgetItem(""));
                QVector<double> rowData = {0, 0, 0}; // Dummy digital data
                analysisData.append(rowData);
                row++;
                
                // Derivative
                if (jsonObj.contains("derivative")) {
                    dataTable->setRowCount(row + 1);
                    dataTable->setItem(row, 0, new QTableWidgetItem("Dérivée"));
                    dataTable->setItem(row, 1, new QTableWidgetItem(jsonObj["derivative"].toString()));
                    dataTable->setItem(row, 2, new QTableWidgetItem(""));
                    QVector<double> derivativeData = {1, 0, 0}; // Dummy digital data
                    analysisData.append(derivativeData);
                    row++;
                }
                
                // Evaluation
                if (jsonObj.contains("evaluation")) {
                    QJsonObject evalObj = jsonObj["evaluation"].toObject();
                    dataTable->setRowCount(row + 1);
                    dataTable->setItem(row, 0, new QTableWidgetItem(QString("Valeur en x=%1").arg(evalObj["x"].toDouble())));
                    dataTable->setItem(row, 1, new QTableWidgetItem(""));
                    dataTable->setItem(row, 2, new QTableWidgetItem(QString::number(evalObj["value"].toDouble())));
                    QVector<double> evalData = {2, evalObj["x"].toDouble(), evalObj["value"].toDouble()};
                    analysisData.append(evalData);
                    row++;
                }
            }
        }
    }
    
    // Enable the view button if data has been loaded
    visualizeButton->setEnabled(!analysisData.isEmpty());
    
    file.close();
}

void MainWindow::visualizeData() {
    // Clear the existing graph
    chart->removeAllSeries();
    
    // Also delete all existing axes to avoid overlapping
    QList<QAbstractAxis*> axes = chart->axes();
    for (QAbstractAxis* axis : axes) {
        chart->removeAxis(axis);
        delete axis;
    }
    
    // Create axes
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    // Determine the axis limits based on the data
    if (!analysisData.isEmpty() && analysisData.first().size() >= 2) {
        // If the array contains a function export
        if (dataHeaders.contains("Type") && dataHeaders.contains("Expression")) {
            // We will generate a graph of the function
            try {
                QString functionExpr;
                QString derivativeExpr;
                
                // Find the expression of the function and the derivative
                for (int i = 0; i < dataTable->rowCount(); ++i) {
                    if (dataTable->item(i, 0)->text() == "Fonction") {
                        functionExpr = dataTable->item(i, 1)->text();
                    }
                    else if (dataTable->item(i, 0)->text() == "Dérivée") {
                        derivativeExpr = dataTable->item(i, 1)->text();
                    }
                }
                
                if (!functionExpr.isEmpty()) {
                    // Create a series for the function
                    QLineSeries *series = new QLineSeries();
                    series->setName(QString("f(x)"));
                    
                    // Set the function to blue color
                    QPen pen = series->pen();
                    pen.setColor(QColor(0, 0, 255)); // Blue
                    pen.setWidth(2);
                    series->setPen(pen);
                    
                    // Calculate points for the function
                    Function f(functionExpr.toStdString());
                    
                    double minX = -10.0;
                    double maxX = 10.0;
                    double step = 0.1;
                    
                    double minY = std::numeric_limits<double>::max();
                    double maxY = std::numeric_limits<double>::lowest();
                    
                    for (double x = minX; x <= maxX; x += step) {
                        try {
                            double y = f.evaluate(x);
                            
                            // Avoid excessively large y values ​​which would distort the scale
                            if (std::isfinite(y) && std::abs(y) < 1000) {
                                series->append(x, y);
                                minY = std::min(minY, y);
                                maxY = std::max(maxY, y);
                            }
                        } catch (...) {
                            // Ignore points with errors
                            continue;
                        }
                    }
                    
                    // Add the series to the chart
                    chart->addSeries(series);
                    series->attachAxis(axisX);
                    series->attachAxis(axisY);
                    
                    // Set the axis limits
                    axisX->setRange(minX, maxX);
                    axisY->setRange(minY - 1, maxY + 1);
                    axisX->setTitleText("x");
                    axisY->setTitleText("y");
                    
                    // If we have a derivative, add it too
                    if (!derivativeExpr.isEmpty()) {
                        try {
                            QLineSeries *derivativeSeries = new QLineSeries();
                            derivativeSeries->setName(QString("f'(x)"));
                            
                            // Set the derivative to orange color
                            QPen pen = derivativeSeries->pen();
                            pen.setColor(QColor(255, 165, 0)); // Orange
                            pen.setWidth(2);
                            derivativeSeries->setPen(pen);
                            
                            Function df(derivativeExpr.toStdString());
                            
                            for (double x = minX; x <= maxX; x += step) {
                                try {
                                    auto [z,y] = df.automaticDifferentiation(x);
                                    if (std::isfinite(y) && std::abs(y) < 1000) {
                                        derivativeSeries->append(x, y);
                                    }
                                } catch (...) {
                                    continue;
                                }
                            }
                            
                            chart->addSeries(derivativeSeries);
                            derivativeSeries->attachAxis(axisX);
                            derivativeSeries->attachAxis(axisY);
                        } catch (...) {
                            qDebug() << "Erreur lors du tracé de la dérivée";
                        }
                    }
                    
                    // If we have any evaluations, add them as points
                    for (int i = 0; i < dataTable->rowCount(); ++i) {
                        if (dataTable->item(i, 0)->text().startsWith("Valeur en x=")) {
                            QString valueText = dataTable->item(i, 0)->text();
                            double x = valueText.mid(valueText.indexOf('=') + 1).toDouble();
                            double y = dataTable->item(i, 2)->text().toDouble();
                            
                            // Create a series for the point
                            QScatterSeries *pointSeries = new QScatterSeries();
                            pointSeries->setName(QString("f(%1) = %2").arg(x).arg(y));
                            pointSeries->setMarkerSize(10);
                            
                            // Set the color red for the evaluation points
                            pointSeries->setColor(QColor(255, 0, 0)); // Red
                            
                            pointSeries->append(x, y);
                            
                            chart->addSeries(pointSeries);
                            pointSeries->attachAxis(axisX);
                            pointSeries->attachAxis(axisY);
                        }
                    }
                }
            } catch (const std::exception& e) {
                QMessageBox::warning(this, tr("Erreur"),
                               tr("Erreur lors de l'analyse de la fonction: %1").arg(e.what()));
            }
        } else {
            // For CSV data, check if the second column could be a derivative
            bool hasDerivativeData = (analysisData.first().size() >= 3);
            
            // Create series with column data
            double minX = std::numeric_limits<double>::max();
            double maxX = std::numeric_limits<double>::lowest();
            double minY = std::numeric_limits<double>::max();
            double maxY = std::numeric_limits<double>::lowest();
            
            // Series for the main function (column 1)
            QLineSeries *mainSeries = new QLineSeries();
            mainSeries->setName(dataHeaders.size() > 1 ? dataHeaders[1] : "Fonction");
            
            // Set the main function to blue color
            QPen mainPen = mainSeries->pen();
            mainPen.setColor(QColor(0, 0, 255)); // Blue
            mainPen.setWidth(2);
            mainSeries->setPen(mainPen);
            
            // If we have an extra column that could be a derivative
            QLineSeries *derivativeSeries = nullptr;
            if (hasDerivativeData) {
                derivativeSeries = new QLineSeries();
                derivativeSeries->setName(dataHeaders.size() > 2 ? dataHeaders[2] : "Dérivée");
                
                // Set the derivative to orange color
                QPen derivativePen = derivativeSeries->pen();
                derivativePen.setColor(QColor(255, 165, 0)); // Orange
                derivativePen.setWidth(2);
                derivativeSeries->setPen(derivativePen);
            }
            
            // Populate the series with the data
            int mainPointCount = 0;
            int derivativePointCount = 0;
            
            for (int row = 0; row < analysisData.size(); ++row) {
                if (analysisData[row].size() > 1) {
                    double x = analysisData[row][0]; // First column as X axis
                    double y1 = analysisData[row][1]; // Second column as function
                    
                    if (std::isfinite(x) && std::isfinite(y1)) {
                        mainSeries->append(x, y1);
                        mainPointCount++;
                        minX = std::min(minX, x);
                        maxX = std::max(maxX, x);
                        minY = std::min(minY, y1);
                        maxY = std::max(maxY, y1);
                    }
                    
                    // If we have a third column, add it as a derivative
                    if (hasDerivativeData && analysisData[row].size() > 2) {
                        double y2 = analysisData[row][2]; // Third column as derivative
                        if (std::isfinite(y2)) {
                            derivativeSeries->append(x, y2);
                            derivativePointCount++;
                            minY = std::min(minY, y2);
                            maxY = std::max(maxY, y2);
                        }
                    }
                }
            }
            
            // Add the series to the chart
            chart->addSeries(mainSeries);
            mainSeries->attachAxis(axisX);
            mainSeries->attachAxis(axisY);
            
            if (hasDerivativeData && derivativeSeries && derivativePointCount > 0) {
                chart->addSeries(derivativeSeries);
                derivativeSeries->attachAxis(axisX);
                derivativeSeries->attachAxis(axisY);
            }
            
            // Set the axis limits
            if (std::isfinite(minX) && std::isfinite(maxX) && std::isfinite(minY) && std::isfinite(maxY)) {
                axisX->setRange(minX - 0.5, maxX + 0.5);
                axisY->setRange(minY - 1, maxY + 1);
                axisX->setTitleText(dataHeaders.size() > 0 ? dataHeaders[0] : "X");
                axisY->setTitleText("Valeur");
            } else {
                // Set default values ​​if no valid data was found
                axisX->setRange(-10, 10);
                axisY->setRange(-10, 10);
                axisX->setTitleText("X");
                axisY->setTitleText("Y");
            }
        }
    }
    
    // Update the graph
    chart->setTitle("Analyse des Données");
}

void MainWindow::exportFunctionAnalysis()
{
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Exporter"), "",
        tr("Fichiers CSV (*.csv);;Fichiers JSON (*.json)"),
        &selectedFilter);
        
    if (fileName.isEmpty())
        return;
        
    bool isCSV = selectedFilter.contains("CSV");
    
    // Ensure correct file extension
    if (isCSV && !fileName.endsWith(".csv")) {
        fileName += ".csv";
    } else if (!isCSV && !fileName.endsWith(".json")) {
        fileName += ".json";
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Erreur"),
                           tr("Impossible d'ouvrir le fichier %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName),
                                file.errorString()));
        return;
    }
    
    QTextStream out(&file);
    
    if (isCSV) {
        // CSV Format
        out << "Type,Expression,Valeur\n";
        out << "Fonction," << functionEdit->text() << ",\n";
        
        if (findDerivativeCheck->isChecked()) {
            try {
                Function f(functionEdit->text().toStdString());
                Function derivative(functionEdit->text().toStdString());
                out << "Dérivée," << QString::fromStdString(derivative.getExpression()) << ",\n";
            } catch (const std::exception&) {
                out << "Dérivée,Erreur de calcul,\n";
            }
        }
        
        if (!xValueEdit->text().isEmpty()) {
            try {
                Function f(functionEdit->text().toStdString());
                double value = f.evaluate(xValueEdit->text().toDouble());
                out << "Valeur en x=" << xValueEdit->text() << "," << "," << value << "\n";
            } catch (const std::exception&) {
                out << "Valeur en x=" << xValueEdit->text() << ",Erreur de calcul,\n";
            }
        }
    } else {
        // JSON Format
        QJsonObject jsonObj;
        jsonObj["function"] = functionEdit->text();
        
        if (findDerivativeCheck->isChecked()) {
            try {
                Function f(functionEdit->text().toStdString());
                Function derivative(functionEdit->text().toStdString());
                jsonObj["derivative"] = QString::fromStdString(derivative.getExpression());
            } catch (const std::exception&) {
                jsonObj["derivative"] = "Erreur de calcul";
            }
        }
        
        if (!xValueEdit->text().isEmpty()) {
            QJsonObject evaluationObj;
            evaluationObj["x"] = xValueEdit->text().toDouble();
            try {
                Function f(functionEdit->text().toStdString());
                double value = f.evaluate(xValueEdit->text().toDouble());
                evaluationObj["value"] = value;
            } catch (const std::exception&) {
                evaluationObj["value"] = "Erreur de calcul";
            }
            jsonObj["evaluation"] = evaluationObj;
        }
        
        QJsonDocument doc(jsonObj);
        out << doc.toJson();
    }
    
    file.close();
    
    QMessageBox::information(this, tr("Succès"),
                           tr("L'analyse a été exportée avec succès dans %1")
                           .arg(QDir::toNativeSeparators(fileName)));
}

void MainWindow::onTabChanged(int index){
    // Handle tab change if needed
}

void MainWindow::resizeMatrixA(){
    int rows = matrixARowsSpinBox->value();
    int cols = matrixAColsSpinBox->value();
    
    // Define the new dimensions
    matrixATable->setRowCount(rows);
    matrixATable->setColumnCount(cols);
    
    // Ensure all items are initialized
    for (int i = 0; i < rows; ++i) {        
        for (int j = 0; j < cols; ++j) {            
            QTableWidgetItem *item = matrixATable->item(i, j);
            if (!item) {
                item = new QTableWidgetItem("0");
                matrixATable->setItem(i, j, item);
            }
        }
    }

    adjustMatrixCellSizes(matrixATable);
}

void MainWindow::resizeMatrixB(){
    int rows = matrixBRowsSpinBox->value();
    int cols = matrixBColsSpinBox->value();
    
    // Define the new dimensions
    matrixBTable->setRowCount(rows);
    matrixBTable->setColumnCount(cols);
    
    // Ensure all items are initialized
    for (int i = 0; i < rows; ++i) {        
        for (int j = 0; j < cols; ++j) {            
            QTableWidgetItem *item = matrixBTable->item(i, j);
            if (!item) {
                item = new QTableWidgetItem("0");
                matrixBTable->setItem(i, j, item);
            }
        }
    }
    
    // Adjust cell size
    adjustMatrixCellSizes(matrixBTable);
}

void MainWindow::adjustMatrixCellSizes(QTableWidget *matrixTable) {
    if (!matrixTable) return;
    
    // Minimum size even smaller when many columns/rows
    int count = qMax(matrixTable->rowCount(), matrixTable->columnCount());
    int MIN_CELL_SIZE = (count <= 4) ? 40 : (count <= 5) ? 35 : 25;
    
    // Check if scrollbars are visible
    bool hasVerticalScrollBar = matrixTable->verticalScrollBar()->isVisible();
    bool hasHorizontalScrollBar = matrixTable->horizontalScrollBar()->isVisible();
    
    // Calculate the available space taking into account scroll bars
    int scrollBarWidth = hasVerticalScrollBar ? matrixTable->verticalScrollBar()->width() : 0;
    int scrollBarHeight = hasHorizontalScrollBar ? matrixTable->horizontalScrollBar()->height() : 0;
    
    // Calculate the ideal size based on the number of columns
    int headerWidth = matrixTable->verticalHeader()->width();
    int availableWidth = matrixTable->width() - headerWidth - scrollBarWidth - 10;
    int columnWidth = qMax(MIN_CELL_SIZE, availableWidth / matrixTable->columnCount());
    
    // Set the column width
    for (int i = 0; i < matrixTable->columnCount(); i++) {
        matrixTable->setColumnWidth(i, columnWidth);
    }
    
    // Calculate the ideal height based on the number of lines
    int headerHeight = matrixTable->horizontalHeader()->height();
    int availableHeight = matrixTable->height() - headerHeight - scrollBarHeight - 10;
    int rowHeight = qMax(MIN_CELL_SIZE, availableHeight / matrixTable->rowCount());
    
    // Set the height of the lines
    for (int i = 0; i < matrixTable->rowCount(); i++) {
        matrixTable->setRowHeight(i, rowHeight);
    }
    
    // If scrollbars appeared after adjustment, readjust once more
    if ((!hasVerticalScrollBar && matrixTable->verticalScrollBar()->isVisible()) ||
        (!hasHorizontalScrollBar && matrixTable->horizontalScrollBar()->isVisible())) {
        QTimer::singleShot(0, [matrixTable, this]() {
            adjustMatrixCellSizes(matrixTable);
        });
    }
    matrixTable->horizontalHeader()->hide();
}

void MainWindow::syncMatrixAFromUI() {
    int rows = matrixATable->rowCount();
    int cols = matrixATable->columnCount();
    
    // Resize the internal data structure
    matrixAData.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrixAData[i].resize(cols);
    }
    
    // Read values ​​from the interface
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = matrixATable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixAData[i][j] = ok ? value : 0.0;
            } else {
                matrixAData[i][j] = 0.0;
            }
        }
    }
}

void MainWindow::syncMatrixBFromUI() {
    int rows = matrixATable->rowCount();
    int cols = matrixATable->columnCount();
    
    // Resize the internal data structure
    matrixBData.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrixBData[i].resize(cols);
    }
    
    // Read values ​​from the interface
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = matrixBTable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixBData[i][j] = ok ? value : 0.0;
            } else {
                matrixBData[i][j] = 0.0;
            }
        }
    }
}

void MainWindow::syncMatrixAToUI() {
    int rows = matrixAData.size();
    int cols = rows > 0 ? matrixAData[0].size() : 0;
    
    // Make sure the table is the right size
    if (matrixATable->rowCount() != rows || matrixATable->columnCount() != cols) {
        matrixATable->setRowCount(rows);
        matrixATable->setColumnCount(cols);
    }
    
    // Update the interface with the values ​​from the internal model
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = matrixATable->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                matrixATable->setItem(i, j, item);
            }
            item->setText(QString::number(matrixAData[i][j]));
        }
    }
}

void MainWindow::syncMatrixBToUI() {
    int rows = matrixBData.size();
    int cols = rows > 0 ? matrixBData[0].size() : 0;
    
    // Make sure the table is the right size
    if (matrixBTable->rowCount() != rows || matrixBTable->columnCount() != cols) {
        matrixBTable->setRowCount(rows);
        matrixBTable->setColumnCount(cols);
    }
    
    // Update the interface with the values ​​from the internal model
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = matrixBTable->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                matrixBTable->setItem(i, j, item);
            }
            item->setText(QString::number(matrixBData[i][j]));
        }
    }
}

void MainWindow::calculateMatrixOperation()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    // Get matrices A and B
    int rowsA = matrixATable->rowCount();
    int colsA = matrixATable->columnCount();
    int rowsB = matrixBTable->rowCount();
    int colsB = matrixBTable->columnCount();
    
    QVector<QVector<double>> matrixAValues(rowsA, QVector<double>(colsA));
    QVector<QVector<double>> matrixBValues(rowsB, QVector<double>(colsB));

    // Ensure matrixAValues and matrixBValues are resized properly
    for (int i = 0; i < rowsA; ++i) {
        if (matrixAValues[i].size() != colsA) {
            matrixAValues[i].resize(colsA);
        }
    }

    for (int i = 0; i < rowsB; ++i) {
        if (matrixBValues[i].size() != colsB) {
            matrixBValues[i].resize(colsB);
        }
    }

    // Fill matrix A
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            QTableWidgetItem *item = matrixATable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixAValues[i][j] = ok ? value : 0.0;
            }
        }
    }
    
    // Fill matrix B
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            QTableWidgetItem *item = matrixBTable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                matrixBValues[i][j] = ok ? value : 0.0;
            }
        }
    }
    
    // Create the Matrix objects for calculations
    Matrix matrixA(rowsA, colsA);
    Matrix matrixB(rowsB, colsB);

    // Fill matrix A from the values ​​read
    for (unsigned int i = 0; i < rowsA; i++) {
        for (unsigned int j = 0; j < colsA; j++) {
            matrixA.setElem(matrixAValues[i][j], i, j);
        } 
    }
    
    // Fill matrix B from the values ​​read
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            matrixB.setElem(matrixBValues[i][j], i, j);
        }
    }
    
    // Display the contents of the matrices for debugging
    QString debugMsg = "Matrice A:\n";
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            debugMsg += QString::number(matrixA.getElem(i, j)) + " ";
        }
        debugMsg += "\n";
    }
    debugMsg += "\nMatrice B:\n";
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            debugMsg += QString::number(matrixB.getElem(i, j)) + " ";
        }
        debugMsg += "\n";
    }
    addToHistory("Matrices", debugMsg);
    
    // Perform the operation according to the button

    Matrix result;
    QString operation;
    QString resultStr;
    bool showMatrix = true;
    
    try {
        if (button == multiplyButton) {
            if (colsA != rowsB) {
                QMessageBox::warning(this, "Erreur", "Pour multiplier les matrices, le nombre de colonnes de A doit être égal au nombre de lignes de B.");
                return;
            }
            result = matrixA * matrixB;
            operation = "A * B";
        } else if (button == addButton) {
            if (rowsA != rowsB || colsA != colsB) {
                QMessageBox::warning(this, "Erreur", "Pour additionner les matrices, elles doivent avoir les mêmes dimensions.");
                return;
            }
            result = matrixA + matrixB;
            operation = "A + B";
        } else if (button == subtractButton) {
            if (rowsA != rowsB || colsA != colsB) {
                QMessageBox::warning(this, "Erreur", "Pour soustraire les matrices, elles doivent avoir les mêmes dimensions.");
                return;
            }
            result = matrixA - matrixB;
            operation = "A - B";
        } else if (button == compareButton) {
            bool equal = (matrixA == matrixB);
            resultStr = equal ? "Les matrices sont égales" : "Les matrices sont différentes";
            operation = "Comparaison A et B";
            showMatrix = false;
        }
        
        // Display the result
        if (showMatrix) {
            QVector<QVector<double>> matrixResult;
            for (unsigned int i = 0; i < result.getHeight(); ++i) {
                QVector<double> row;
                for (unsigned int j = 0; j < result.getLength(); ++j) {
                    row.append(result.getElem(i, j));
                }
                matrixResult.append(row);
            }
            displayResultMatrix(matrixResult);
            addToHistory(operation, "Voir résultat ci-contre");
        } else {
            addToHistory(operation, resultStr);
        }

        

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erreur", QString("Une erreur s'est produite : %1").arg(e.what()));
    }
}

void MainWindow::displayResultMatrix(const QVector<QVector<double>> &matrix)
{
    int rows = matrix.size();
    int cols = (rows > 0) ? matrix[0].size() : 0;
    
    resultMatrixTable->setRowCount(rows);
    resultMatrixTable->setColumnCount(cols);
    
    // Display values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(matrix[i][j]));
            resultMatrixTable->setItem(i, j, item);
        }
    }
    
    // Adjust cell sizes
    adjustMatrixCellSizes(resultMatrixTable);
}

void MainWindow::calculateMatrixProperty()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    // Get matrices A and B
    int rowsA = matrixATable->rowCount();
    int colsA = matrixATable->columnCount();
    int rowsB = matrixBTable->rowCount();
    int colsB = matrixBTable->columnCount();
    
    QVector<QVector<double>> matrixAValues(rowsA, QVector<double>(colsA));
    QVector<QVector<double>> matrixBValues(rowsB, QVector<double>(colsB));

    
    
    // Fill matrix A
    for (unsigned int i = 0; i < rowsA; ++i) {
        for (unsigned int j = 0; j < colsA; ++j) {
            QTableWidgetItem *item = matrixATable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    matrixAValues[i][j] = value;
                } else {
                    matrixAValues[i][j] = 0.0;
                }                
            } else {
                matrixAValues[i][j] = 0.0;
            }
        }
    }
    
    // Fill matrix B
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            QTableWidgetItem *item = matrixBTable->item(i, j);
            if (item) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    matrixBValues[i][j] = value;
                } else {
                    matrixBValues[i][j] = 0.0;
                }     
            } else {
                matrixBValues[i][j] = 0.0;
            }
        }
    }
    
    // Create the Matrix objects for calculations
    Matrix matrixA(rowsA, colsA);
    Matrix matrixB(rowsB, colsB);
    
    // Fill matrix A from the values ​​read
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            matrixA.setElem(matrixAValues[i][j], i, j);
        }
    }
    
    // Fill matrix B from the values ​​read
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            matrixB.setElem(matrixBValues[i][j], i, j);
        }
    }
    
    // Determine which matrix to use
    bool isMatrixA = (button == determinantAButton || button == transposeAButton || button == inverseAButton || button == rankAButton || button == kerAButton || button == imAButton || button == trAButton || button == powAButton || button == eigenValAButton || button == vectAButton);
    
    // Perform the operation according to the button
    QString operation;
    QString resultStr;
    bool showMatrix = false;
    Matrix resultMatrix;
    
    // Performs an action depending on the button clicked
    try {

        // Calculation of the determinant

        if (button == determinantAButton || button == determinantBButton) {
            // For the determinant, the matrix must be square
            if (isMatrixA) {
                if (rowsA != colsA) {
                    QMessageBox::warning(this, "Erreur", "Le déterminant n'est défini que pour les matrices carrées.");
                    return;
                }
                double det = matrixA.determinant();
                operation = "Déterminant de A";
                resultStr = QString::number(det);
            } else {
                if (rowsB != colsB) {
                    QMessageBox::warning(this, "Erreur", "Le déterminant n'est défini que pour les matrices carrées.");
                    return;
                }
                double det = matrixB.determinant();
                operation = "Déterminant de B";
                resultStr = QString::number(det);
            }



        // Calculation of the transpose

        } else if (button == transposeAButton || button == transposeBButton) {
            if (isMatrixA) {
                resultMatrix = matrixA.transpose();
                operation = "Transposée de A";
            } else {
                resultMatrix = matrixB.transpose();
                operation = "Transposée de B";
            }
            showMatrix = true;



        // Calculation of the inverse

        } else if (button == inverseAButton || button == inverseBButton) {
            if (isMatrixA) {
                if (rowsA != colsA) {
                    QMessageBox::warning(this, "Erreur", "L'inverse n'est définie que pour les matrices carrées.");
                    return;
                }
                
                if (std::abs(matrixA.determinant()) < 1e-10) {
                    QMessageBox::warning(this, "Erreur", "La matrice A n'est pas inversible (déterminant = 0).");
                    return;
                }
                
                resultMatrix = matrixA.getInverse();
                operation = "Inverse de A";
            } else {
                if (rowsB != colsB) {
                    QMessageBox::warning(this, "Erreur", "L'inverse n'est définie que pour les matrices carrées.");
                    return;
                }
                
                if (std::abs(matrixB.determinant()) < 1e-10) {
                    QMessageBox::warning(this, "Erreur", "La matrice B n'est pas inversible (déterminant = 0).");
                    return;
                }
                
                resultMatrix = matrixB.getInverse();
                operation = "Inverse de B";
            }
            showMatrix = true;

        

        // Rank calculation
        
        } else if (button == rankAButton || button == rankBButton) {
            if (isMatrixA){
                // Rank is not limited to square matrices
                unsigned int rank = matrixA.rank();
                operation = "Rang de A";
                resultStr = QString::number(rank);
            }
            else {
                // Rank is not limited to square matrices
                unsigned int rank = matrixB.rank();
                operation = "Rang de B";
                resultStr = QString::number(rank);
            }   



        // Calculation of the kernel base

        } else if (button == kerAButton || button == kerBButton){
            std::vector<std::vector<double>> kerRes;
            std::ostringstream sRes;
            if (isMatrixA){
                if (rowsA != colsA){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Base de ker(A)";
                kerRes = matrixA.getKerBase();
            }
            else {
                if (rowsB != colsB){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Base de ker(B)";
                kerRes = matrixB.getKerBase();
            }

            // Formatting the result into QString
            if (kerRes.size() == 0){
                resultStr = QString::fromStdString("Ensemble vide");
            }
            else{
                for (unsigned int i = 0; i < kerRes[0].size(); i++){
                    for (unsigned int j = 0; j < kerRes.size(); j++){
                        sRes << "| ";
                        std::ostringstream oss;
                        oss << std::setprecision(6) << kerRes[j][i];  // Format avec 6 décimales
                        std::string value = oss.str();
                        
                        // Remove zeros after the decimal point
                        value = std::regex_replace(value, std::regex("([0-9]+),0+$"), "$1");  // Remove zeros after the decimal point
                        value = std::regex_replace(value, std::regex(",?$"), "");             // Remove the comma if necessary
                        
                        sRes << value << "|\t";
                    }
                    sRes << "\n";
                }  
                sRes << "\n";
                std::string sResString = sRes.str();
                sResString = std::regex_replace(sResString, std::regex("\\.?0+$"), "");
                sResString = std::regex_replace(sResString, std::regex("\\.$"), "");
                resultStr = QString::fromUtf8(sResString.c_str());
            }



        // Image calculation
        
        } else if (button == imAButton || button == imBButton){
            std::vector<std::vector<double>> imRes;
            std::ostringstream sRes;
            if (isMatrixA){
                if (rowsA != colsA){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Base de im(A)";
                imRes = matrixA.getImBase();
            }
            else {
                if (rowsB != colsB){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Base de im(B)";
                imRes = matrixB.getImBase();
            }
            if (imRes.size() == 0){
                resultStr = QString::fromStdString("Ensemble vide");
            }
            else{
                for (unsigned int i = 0; i < imRes[0].size(); i++){
                    for (unsigned int j = 0; j < imRes.size(); j++){
                        sRes << "| ";
                        std::ostringstream oss;
                        oss << std::setprecision(6) << imRes[j][i];  // Format with 6 decimal places
                        std::string value = oss.str();
                        
                        // Remove zeros after the decimal point
                        value = std::regex_replace(value, std::regex("([0-9]+),0+$"), "$1");  // Remove zeros after the decimal point
                        value = std::regex_replace(value, std::regex(",?$"), "");             // Remove the comma if necessary
                        
                        sRes << value << "|\t";
                    }
                    sRes << "\n";
                }  
                sRes << "\n";
                std::string sResString = sRes.str();
                sResString = std::regex_replace(sResString, std::regex("\\.?0+$"), "");
                sResString = std::regex_replace(sResString, std::regex("\\.$"), "");
                resultStr = QString::fromUtf8(sResString.c_str());
            }



        // Trace calculation
            
        } else if (button == trAButton || button == trBButton){
            if (isMatrixA){
                double tr = matrixA.trace();
                operation = "Trace de A";
                resultStr = QString::number(tr);
            }
            else {
                double tr = matrixB.trace();
                operation = "Trace de B";
                resultStr = QString::number(tr);
            }


        // Calculation of a power

        } else if (button == powAButton || button == powBButton){
            // Creation of the popup
            QDialog dialog(this);
            dialog.setWindowTitle("Exposant de la matrice");
                
            // Label
            QLabel *label = new QLabel("Choisissez un exposant :", &dialog);
                
            // SpinBox
            QSpinBox *newBox = new QSpinBox(&dialog);
            newBox->setRange(2, 10);
            newBox->setValue(2);
                
            // OK buton
            QPushButton *okButton = new QPushButton("OK", &dialog);
                
            // Close the popup by clicking OK
            connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
                
            // Layout
            QVBoxLayout layout;
            layout.addWidget(label);
            layout.addWidget(newBox);
            layout.addWidget(okButton);
                
            dialog.setLayout(&layout);

            if (dialog.exec() == QDialog::Accepted) {
                int puissance = newBox->value();
                if (isMatrixA) resultMatrix = matrixA;
                else resultMatrix = matrixB;
                for (unsigned int i = 1; i < puissance; i++){
                    if (isMatrixA) resultMatrix = resultMatrix * matrixA;
                    else resultMatrix = resultMatrix * matrixB;
                }
                if (isMatrixA) operation = "Matrice A à la puissance " + QString::number(puissance);
                else operation = "Matrice B à la puissance " + QString::number(puissance);
                showMatrix = true;
            }
        

        // Spectrum calculation

        } else if (button == eigenValAButton || button == eigenValBButton){
            vector<complex<double>> res;
            if (isMatrixA){
                res = matrixA.eigenvalues();
                operation = "Spectre des valeurs propres de A";
            }
            else {
                res = matrixB.eigenvalues();
                operation = "Spectre des valeurs propres de B";
            }
            
            resultStr += "{ ";
            for (unsigned int i = 0; i < res.size(); i++){
                resultStr += QString::number(res[i].real()) + " ";
                if (res[i].imag() != 0){
                    if (res[i].imag() < 0) {
                        resultStr += "- " + QString::number(-res[i].imag()) + " i ";
                    }
                    else {
                        resultStr += "+ " + QString::number(res[i].imag()) + " i ";
                    }
                }
            }
            resultStr += "}";


        // Calculation of eigenvectors

        } else if (button == vectAButton || button == vectBButton){
            std::vector<std::vector<double>> eigRes;
            std::ostringstream sRes;
            if (isMatrixA){
                if (rowsA != colsA){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Vecteurs propres de A";
                eigRes = matrixA.eigenvectors();
            }
            else {
                if (rowsB != colsB){
                    QMessageBox::warning(this, "Erreur", "Seules les matrices carrées sont prises en charge.");
                    return;
                }                
                operation = "Vecteurs propres de B";
                eigRes = matrixB.eigenvectors();
            }

            if (eigRes.size() == 0){
                resultStr = QString::fromStdString("Aucun vecteur propre réel trouvé.");
            }
            else{
                for (unsigned int i = 0; i < eigRes[0].size(); i++){
                    for (unsigned int j = 0; j < eigRes.size(); j++){
                        sRes << "| ";
                        std::ostringstream oss;
                        oss << std::setprecision(6) << eigRes[j][i];  // Format with 6 decimal places
                        std::string value = oss.str();

                        // Display cleaning
                        value = std::regex_replace(value, std::regex("([0-9]+),0+$"), "$1");
                        value = std::regex_replace(value, std::regex(",?$"), "");
                        sRes << value << "|\t";
                    }
                    sRes << "\n";
                }  
                sRes << "\n";
                std::string sResString = sRes.str();
                sResString = std::regex_replace(sResString, std::regex("\\.?0+$"), "");
                sResString = std::regex_replace(sResString, std::regex("\\.$"), "");
                resultStr = QString::fromUtf8(sResString.c_str());
            }
        }
        
        // Display the result
        if (showMatrix) {
            QVector<QVector<double>> matrixResult;
            for (unsigned int i = 0; i < resultMatrix.getHeight(); ++i) {
                QVector<double> row;
                for (unsigned int j = 0; j < resultMatrix.getLength(); ++j) {
                    row.append(resultMatrix.getElem(i, j));
                }
                matrixResult.append(row);
            }
            displayResultMatrix(matrixResult);
            addToHistory(operation, "Voir résultat ci-contre");
        } else {
            addToHistory(operation, resultStr);
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erreur", QString("Une erreur s'est produite : %1").arg(e.what()));
    }
}

void MainWindow::addToHistory(const QString &operation, const QString &result){
    historyTextEdit->append(operation + " : \n" + result);
    historyTextEdit->verticalScrollBar()->setValue(historyTextEdit->verticalScrollBar()->maximum());
}

void MainWindow::calculateIntegral(){
    // Get values ​​from the user interface
    QString functionExpr = integrationFunctionEdit->text();
    if (functionExpr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une fonction à intégrer.");
        return;
    }
    
    // Get the terminals
    bool lowerOk, upperOk;
    double lowerBound = integrationLowerBoundEdit->text().toDouble(&lowerOk);
    double upperBound = integrationUpperBoundEdit->text().toDouble(&upperOk);
    
    if (!lowerOk || !upperOk) {
        QMessageBox::warning(this, "Erreur", "Les bornes d'intégration doivent être des nombres valides.");
        return;
    }
    
    // Get the number of intervals
    int intervals = integrationIntervalsSpinBox->value();
    
    try {
        // Create the Integral objects for both methods
        Integral rectangleIntegral(functionExpr.toStdString(), lowerBound, upperBound, intervals, IntegrationMethod::RECTANGLE);
        Integral trapezoidIntegral(functionExpr.toStdString(), lowerBound, upperBound, intervals, IntegrationMethod::TRAPEZOID);
        
        // Calculate the integrals
        double rectangleResult = rectangleIntegral.evaluate();
        double trapezoidResult = trapezoidIntegral.evaluate();
        
        // Show results
        QString resultText = QString("<b>Résultats pour ∫<sub>%1</sub><sup>%2</sup> %3 dx avec %4 intervalles:</b><br><br>")
                            .arg(lowerBound)
                            .arg(upperBound)
                            .arg(functionExpr)
                            .arg(intervals);
                            
        resultText += QString("<b>Méthode des rectangles:</b> %1<br>")
                      .arg(rectangleResult, 0, 'g', 6);
                      
        resultText += QString("<b>Méthode des trapèzes:</b> %1<br>")
                      .arg(trapezoidResult, 0, 'g', 6);
                      
        // Calculate the relative error between the two methods
        double diff = std::abs(rectangleResult - trapezoidResult);
        double relError = 0.0;
        if (std::abs(trapezoidResult) > 1e-10) {
            relError = diff / std::abs(trapezoidResult) * 100.0;
        }
        
        resultText += QString("<br><b>Différence:</b> %1 (%2%)<br>")
                      .arg(diff, 0, 'g', 6)
                      .arg(relError, 0, 'g', 4);
                      
        integrationResultLabel->setText(resultText);
        
        // Add to history
        QString historyEntry = QString("Fonction: %1, Bornes: [%2, %3], Intervalles: %4")
                              .arg(functionExpr)
                              .arg(lowerBound)
                              .arg(upperBound)
                              .arg(intervals);
        integrationHistoryList->addItem(historyEntry);
        
        // Update the graphics
        updateIntegrationGraph(rectangleIntegral, trapezoidIntegral);
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Erreur", 
            QString("Erreur lors du calcul de l'intégrale: %1").arg(e.what()));
    }
}

void MainWindow::updateIntegrationGraph(const Integral& rectangleIntegral, const Integral& trapezoidIntegral) {
    // Delete existing series
    rectangleChart->removeAllSeries();
    trapezoidChart->removeAllSeries();
    
    // Recover the terminals
    double lowerBound = rectangleIntegral.getLowerBound();
    double upperBound = rectangleIntegral.getUpperBound();
    
    // Extend the viewing range a little
    double margin = (upperBound - lowerBound) * 0.2;
    double minX = lowerBound - margin;
    double maxX = upperBound + margin;
    
    // Get the points to plot the function
    std::vector<std::pair<double, double>> points = rectangleIntegral.getPlotPoints(200);
    
    // Variables to determine the Y terminals
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();
    
    // Calculate Y limits from points
    for (const auto& point : points) {
        double y = point.second;
        if (std::isfinite(y)) {
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
        }
    }
    
    // Series for the function in the rectangle graph
    QLineSeries *rectFunctionSeries = new QLineSeries();
    rectFunctionSeries->setName("f(x)");
    
    // Series for the function in the trapezoid graph
    QLineSeries *trapFunctionSeries = new QLineSeries();
    trapFunctionSeries->setName("f(x)");
    
    // Fill the series with the points
    for (const auto& point : points) {
        double x = point.first;
        double y = point.second;
        
        rectFunctionSeries->append(x, y);
        trapFunctionSeries->append(x, y);
    }
    
    // --- GRAPH OF RECTANGLES ---
    
    // Create a series for the rectangles
    std::vector<std::pair<double, double>> rectanglePoints = rectangleIntegral.getRectanglePoints();
    QLineSeries *rectangleSeries = new QLineSeries();
    rectangleSeries->setName("Rectangles");
    
    // Style for rectangles
    QPen rectanglePen(QColor(255, 0, 0, 150)); // Semi-transparent red
    rectanglePen.setWidth(2);
    rectangleSeries->setPen(rectanglePen);
    
    // Add the points of the rectangles
    for (const auto& point : rectanglePoints) {
        rectangleSeries->append(point.first, point.second);
    }
    
    // Add the series to the rectangle chart
    rectangleChart->addSeries(rectangleSeries);
    rectangleChart->addSeries(rectFunctionSeries);
    
    // Display the result on the graph
    double rectResult = rectangleIntegral.evaluate();
    rectangleChart->setTitle(QString("Méthode des rectangles: %1").arg(rectResult, 0, 'g', 6));
    
    // --- TRAPEZOID GRAPH ---
    
    // Create a series for the trapezes
    std::vector<std::pair<double, double>> trapezoidPoints = trapezoidIntegral.getTrapezoidPoints();
    QLineSeries *trapezoidSeries = new QLineSeries();
    trapezoidSeries->setName("Trapèzes");
    
    // Style for trapezes
    QPen trapezoidPen(QColor(0, 0, 255, 150)); // Semi-transparent blue
    trapezoidPen.setWidth(2);
    trapezoidSeries->setPen(trapezoidPen);
    
    // Add the points of the trapezoids
    for (const auto& point : trapezoidPoints) {
        trapezoidSeries->append(point.first, point.second);
    }
    
    // Add the series to the trapezoid chart
    trapezoidChart->addSeries(trapezoidSeries);
    trapezoidChart->addSeries(trapFunctionSeries);
    
    // Display the result on the graph
    double trapResult = trapezoidIntegral.evaluate();
    trapezoidChart->setTitle(QString("Méthode des trapèzes: %1").arg(trapResult, 0, 'g', 6));
    
    // Synchronize the axes for both charts
    
    // Calculate the scale adapted to the function
    double yRange = maxY - minY;
    
    // If the function is of the type 1/x with strong variations
    if (rectangleIntegral.getFunctionExpression().find("1/x") != std::string::npos || 
        rectangleIntegral.getFunctionExpression().find("x^-1") != std::string::npos) {
        // Special adjustment for functions with asymptotes
        double yMargin = yRange * 0.3;
        minY = minY - yMargin;
        maxY = maxY + yMargin;
    } else {
        // Standard case - add a proportional margin
        double yMargin = yRange * 0.2;
        minY = minY - yMargin;
        maxY = maxY + yMargin;
    }
    
    // Avoid excessive or too small scales
    if (yRange < 0.001) {
        // If the scale is too small (almost constant function)
        double avgY = (minY + maxY) / 2;
        minY = avgY - 0.1;
        maxY = avgY + 0.1;
    } else if (yRange > 1000) {
        // For functions with very large variations
        double avgY = (minY + maxY) / 2;
        minY = avgY - yRange * 0.3;
        maxY = avgY + yRange * 0.3;
    }
    
    // Configure the axes for the rectangle chart
    QValueAxis *rectAxisX = qobject_cast<QValueAxis*>(rectangleChart->axes(Qt::Horizontal).first());
    QValueAxis *rectAxisY = qobject_cast<QValueAxis*>(rectangleChart->axes(Qt::Vertical).first());
    
    // Attach series to axes
    rectFunctionSeries->attachAxis(rectAxisX);
    rectFunctionSeries->attachAxis(rectAxisY);
    rectangleSeries->attachAxis(rectAxisX);
    rectangleSeries->attachAxis(rectAxisY);
    
    // Configure the axes for the trapezoid chart
    QValueAxis *trapAxisX = qobject_cast<QValueAxis*>(trapezoidChart->axes(Qt::Horizontal).first());
    QValueAxis *trapAxisY = qobject_cast<QValueAxis*>(trapezoidChart->axes(Qt::Vertical).first());
    
    // Attach series to axes
    trapFunctionSeries->attachAxis(trapAxisX);
    trapFunctionSeries->attachAxis(trapAxisY);
    trapezoidSeries->attachAxis(trapAxisX);
    trapezoidSeries->attachAxis(trapAxisY);
    
    // Set a fixed number of ticks on the axes
    rectAxisX->setTickCount(10);
    rectAxisY->setTickCount(10);
    trapAxisX->setTickCount(10);
    trapAxisY->setTickCount(10);
    
    // Apply the same limits to both graphs
    rectAxisX->setRange(minX, maxX);
    rectAxisY->setRange(minY, maxY);
    trapAxisX->setRange(minX, maxX);
    trapAxisY->setRange(minY, maxY);
    
    // Refresh the charts
    rectangleChartView->update();
    trapezoidChartView->update();
}

void MainWindow::resizeSystem(){
    int rows = systemSizeSpinBox->value(); // number of equations
    int cols = systemVarsSpinBox->value(); // number of unknowns
    
    // Clear existing grid
    QLayoutItem *child;
    while ((child = systemGrid->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }
    
    // Create a new grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QLineEdit *coefEdit = new QLineEdit("0");
            coefEdit->setFixedWidth(50);
            systemGrid->addWidget(coefEdit, i, j*2);
            
            if (j < cols - 1) {
                QLabel *varLabel = new QLabel("x<sub>" + QString::number(j+1) + "</sub> +");
                systemGrid->addWidget(varLabel, i, j*2+1);
            } else {
                QLabel *varLabel = new QLabel("x<sub>" + QString::number(j+1) + "</sub> =");
                systemGrid->addWidget(varLabel, i, j*2+1);
                
                QLineEdit *constEdit = new QLineEdit("0");
                constEdit->setFixedWidth(50);
                systemGrid->addWidget(constEdit, i, j*2+2);
            }
        }
    }
}

void MainWindow::solveSystem(){
    int rows = systemSizeSpinBox->value(); // number of equations
    int cols = systemVarsSpinBox->value(); // number of unknowns
    
    // Retrieve coefficients and constants
    std::vector<std::vector<double>> coefficients(rows, std::vector<double>(cols));
    std::vector<double> constants(rows);
    
    // Extract values ​​from the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLineEdit *coefEdit = qobject_cast<QLineEdit*>(systemGrid->itemAtPosition(i, j*2)->widget());
            if (coefEdit) {
                bool ok;
                double value = coefEdit->text().toDouble(&ok);
                coefficients[i][j] = ok ? value : 0.0;
            }
        }
        
        QLineEdit *constEdit = qobject_cast<QLineEdit*>(systemGrid->itemAtPosition(i, (cols-1)*2+2)->widget());
        if (constEdit) {
            bool ok;
            double value = constEdit->text().toDouble(&ok);
            constants[i] = ok ? value : 0.0;
        }
    }
    
    // Analyze the system type
    SystemSolver::SystemType type = SystemSolver::analyzeSystem(coefficients, constants);
    
    QString resultText;
    
    switch (type) {
        case SystemSolver::SystemType::Unique:
            {
                std::vector<double> solution = SystemSolver::solveLinearSystem(coefficients, constants);
                
                // Check if the solution is valid (non-empty)
                if (solution.empty()) {
                    resultText = "Erreur lors de la résolution du système. La matrice est peut-être singulière.";
                } else {
                    resultText = "Solution unique:<br>";
                    for (int i = 0; i < cols; ++i) {
                        resultText += QString("x<sub>%1</sub> = %2<br>").arg(i+1).arg(solution[i]);
                    }
                }
            }
            break;
            
        case SystemSolver::SystemType::InfinitelyManySolutions:
            {
                resultText = "Le système a une infinité de solutions.<br>";
                
                // Get the parametric solution
                SystemSolver::ParametricSolution paramSolution = 
                    SystemSolver::solveParametricSystem(coefficients, constants);
                
                // Identify free and dependent variables
                std::vector<int> freeVars;
                std::vector<int> depVars;
                
                for (int i = 0; i < cols; ++i) {
                    if (paramSolution.isFreeVariable[i]) {
                        freeVars.push_back(i);
                    } else {
                        depVars.push_back(i);
                    }
                }
                
                // Display free variables
                resultText += "<b>Variables libres:</b> ";
                for (size_t j = 0; j < freeVars.size(); ++j) {
                    resultText += QString("x<sub>%1</sub> ").arg(freeVars[j]+1);
                }
                resultText += "<br><br>";
                
                // Display the expressions of the dependent variables
                resultText += "<b>Solution paramétrique:</b><br>";
                for (size_t i = 0; i < depVars.size(); ++i) {
                    resultText += QString("x<sub>%1</sub> = %2").arg(depVars[i]+1).arg(paramSolution.constants[i]);
                    
                    int freeIndex = 0;
                    for (size_t j = 0; j < freeVars.size(); ++j) {
                        double coeff = paramSolution.coefficients[i][freeIndex];
                        freeIndex++;
                        
                        if (std::abs(coeff) < 1e-10) continue; // Ignore near-zero coefficients
                        
                        if (coeff > 0) {
                            resultText += QString(" + %1·x<sub>%2</sub>").arg(coeff).arg(freeVars[j]+1);
                        } else {
                            resultText += QString(" - %1·x<sub>%2</sub>").arg(std::abs(coeff)).arg(freeVars[j]+1);
                        }
                    }
                    resultText += "<br>";
                }
            }
            break;
            
        case SystemSolver::SystemType::NoSolution:
            resultText = "Le système n'a pas de solution.";
            break;
    }
    
    // Display the result
    systemResultLabel->setText(resultText);
    
    // Add to history
    QString historyEntry = QString("Système %1x%2: ").arg(rows).arg(cols) + 
        (type == SystemSolver::SystemType::Unique ? "Solution unique" : 
         type == SystemSolver::SystemType::InfinitelyManySolutions ? "Infinité de solutions" : 
         "Pas de solution");
    systemHistoryList->addItem(historyEntry);
}

void MainWindow::analyzeFunction()
{
    QString expression = functionEdit->text();
    if (expression.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une expression.");
        return;
    }

    try {
        Function f(expression.toStdString());
        QString result = "Analyse de la fonction f(x) = " + expression + "\n\n";

        if (findDerivativeCheck->isChecked()) {
            auto [value, derivative] = f.automaticDifferentiation(1);
            result += "Dérivée f'(x) en 1 = " + QString::number(derivative) + "\n\n";
        }
        if (findRootsCheck->isChecked()) {
            std::vector<double> roots = f.getRoots();
            result += "Racines de f(x) de [-10;10]: ";
            if (roots.empty()) {
                result += "Aucune racine trouvée.\n";
            } else {
                for (double root : roots) {
                    result += QString::number(root) + " ";
                }
            }
            result += "\n\n";
        }
        // Test function values at key points
        result += "f("+ xValueEdit->text() +") = " + QString::number(f.evaluate(xValueEdit->text().toDouble())) + "\n";
        
        // Update result display
        functionResultText->setText(result);
        
        // Add to history
        functionHistoryList->addItem("Analyse de: " + expression);
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Erreur", 
            QString("Erreur lors de l'analyse de la fonction: %1").arg(e.what()));
    }
}

void MainWindow::clearMatrixHistory()
{
    historyTextEdit->clear();
}

void MainWindow::updateMatrixA()
{
    // This method is now empty but retained for compatibility with the Qt metaclass
    // We now use the internal matrixAData data model
}

void MainWindow::updateMatrixB()
{
    // This method is now empty but retained for compatibility with the Qt metaclass
    // We now use the internal matrixBData data model
}

void MainWindow::clearSystemHistory()
{
    systemHistoryList->clear();
}

// Add a method to intercept resize events
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        // If the event is a resize and concerns one of our tables
        if (watched == matrixATable || watched == matrixBTable || watched == resultMatrixTable) {
            QTableWidget *table = qobject_cast<QTableWidget*>(watched);
            if (table) {
                adjustMatrixCellSizes(table);
                return false; // Continue normal event processing
            }
        }
    }
    
    // Let the parent class handle other events
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::toggleDarkMode() {
    isDarkMode = !isDarkMode;
    
    // Load the appropriate style file
    QString styleFileName = isDarkMode ? ":/styles_dark.qss" : ":/styles.qss";
    QFile styleFile(styleFileName);
    
    if (styleFile.open(QFile::ReadOnly)) {
        QTextStream stream(&styleFile);
        this->setStyleSheet(stream.readAll());
        styleFile.close();
        
        // Update the button text
        if (isDarkMode) {
            darkModeButton->setText("◐");
        } else {
            darkModeButton->setText("◑");
        }
    } else {
        qDebug() << "Impossible de charger le fichier de style" << styleFileName;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}