#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <vector>

// ANTLR4 includes
#include <antlr4-runtime.h>

// Qt includes
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QComboBox>
#include <QTableWidget>
#include <QScrollArea>
#include <QRadioButton>
#include <QCheckBox>
#include <QListWidget>
#include <QVector>
#include <QEvent>
#include <QFileDialog>
#include <QDir>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QIcon>

// Define that we are using the QtCharts namespace
#define QT_CHARTS_USE_NAMESPACE

// Backend includes - reorder to resolve dependencies
#include "../backend/Function.h"
#include "../backend/Matrix.h"
#include "../backend/Integral.h"
#include "../backend/System.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Macro for signals and slots

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    /**
     * @brief Updates the contents of matrix A.
     * 
     * This function is responsible for refreshing or modifying
     * the data stored in matrix A, ensuring it reflects the
     * latest changes or computations.
     */
    void updateMatrixA();

    /**
     * @brief Updates the contents of matrix B.
     * 
     * This function is responsible for refreshing or modifying the data
     * in matrix B based on the current application state or user input.
     */
    void updateMatrixB();


    /**
     * @brief Performs the calculation of a matrix operation.
     * 
     * This function handles the logic for computing operations on matrices,
     * such as addition, subtraction, multiplication, or other supported operations.
     */
    void calculateMatrixOperation();
    
    /**
     * @brief Calculates and displays properties of the current matrix.
     * 
     * This function computes various properties of the matrix, such as determinant,
     * rank, or other relevant characteristics, and updates the UI accordingly.
     */
    void calculateMatrixProperty();
    
    /**
     * @brief Calculates the integral of a given mathematical function.
     * 
     * This method performs the computation of the integral based on the 
     * provided parameters or user input. The specific details of the 
     * function and integration bounds are determined within the implementation.
     */
    void calculateIntegral();

    /**
     * @brief Updates the integration graph with the results of two integration methods.
     * 
     * This function updates the graphical representation of the integration results
     * using the rectangle and trapezoid methods.
     * 
     * @param rectangleIntegral The result of the integration using the rectangle method.
     * @param trapezoidIntegral The result of the integration using the trapezoid method.
     */
    void updateIntegrationGraph(const Integral& rectangleIntegral, const Integral& trapezoidIntegral);
    
    /**
     * @brief Adjusts the system's dimensions or layout.
     * 
     * This function is responsible for resizing or reconfiguring
     * the system to adapt to new requirements or constraints.
     */
    void resizeSystem();

    /**
     * @brief Solves the system of equations defined in the System tab.
     * 
     * This function processes the input equations and variables, performs
     * the necessary computations to find the solution, and displays the result
     * in the UI.
     */
    void solveSystem();

    /**
     * @brief Clears the history of the system.
     * 
     * This function removes all stored records or logs related to the system's history,
     * resetting it to an empty state.
     */
    void clearSystemHistory();
    
    /**
     * @brief Analyzes the mathematical function provided by the user.
     * 
     * This function processes the input function, performs necessary
     * computations or validations, and provides analysis results.
     */
    void analyzeFunction();

    /**
     * @brief Loads data from a file into the application.
     * 
     * This function is responsible for reading and importing data
     * from a specified file to initialize or update the application's
     * state or data structures.
     */
    void loadDataFile();

    /**
     * @brief Visualizes the data in the application.
     * 
     * This function is responsible for rendering or displaying
     * the relevant data in a visual format, providing a graphical
     * representation to the user.
     */
    void visualizeData();

    /**
     * @brief Toggles the application's dark mode theme.
     * 
     * This function switches between light mode and dark mode
     * for the application's user interface.
     */
    void toggleDarkMode();
    
    /**
     * @brief Slot triggered when the active tab in the QTabWidget changes.
     * 
     * This method is called whenever the user switches between tabs in the main window.
     * It performs necessary updates or actions based on the newly selected tab.
     * 
     * @param index The index of the newly selected tab in the QTabWidget.
     */
    void onTabChanged(int index);

    /**
     * @brief Updates the internal representation of Matrix A from the UI.
     * Synchronizes the UI table data for Matrix A with the internal storage.
     */
    void syncMatrixAFromUI();

    /**
     * @brief Updates the internal representation of Matrix B from the UI.
     * Synchronizes the UI table data for Matrix B with the internal storage.
     */
    void syncMatrixBFromUI();

    /**
     * @brief Updates the UI to reflect the internal data of Matrix A.
     * Synchronizes the internal storage of Matrix A with the UI table.
     */
    void syncMatrixAToUI();

    /**
     * @brief Updates the UI to reflect the internal data of Matrix B.
     * Synchronizes the internal storage of Matrix B with the UI table.
     */
    void syncMatrixBToUI();

    /**
     * @brief Exports the results of the function analysis to an external file.
     * Handles the process of saving analyzed function data for further use.
     */
    void exportFunctionAnalysis();

private:
    Ui::MainWindow* ui;
    
    // Main components
    QTabWidget* tabWidget;
    QPushButton* darkModeButton;
    bool isDarkMode;
    
    // Matrix tab components
    QWidget* matrixTab;

    QTableWidget* matrixATable;
    QTableWidget* matrixBTable;

    QTableWidget* resultMatrixTable;

    QPushButton* multiplyButton;
    QPushButton* addButton;
    QPushButton* subtractButton;
    QPushButton* compareButton;

    QPushButton* clearHistoryButton;
    QTextEdit* historyTextEdit;

    QSpinBox* matrixARowsSpinBox;
    QSpinBox* matrixBRowsSpinBox;
    QSpinBox* matrixAColsSpinBox;
    QSpinBox* matrixBColsSpinBox;
    
    QPushButton* inverseAButton;
    QPushButton* inverseBButton;

    QPushButton* determinantAButton;
    QPushButton* determinantBButton;

    QPushButton* transposeAButton;
    QPushButton* transposeBButton;
    
    QPushButton* rankAButton;
    QPushButton* rankBButton;

    QPushButton* kerAButton;
    QPushButton* kerBButton;

    QPushButton* imAButton;
    QPushButton* imBButton;

    QPushButton* trAButton;
    QPushButton* trBButton;

    QPushButton* powAButton;
    QPushButton* powBButton;

    QPushButton* eigenValAButton;
    QPushButton* eigenValBButton;

    QPushButton* vectAButton;
    QPushButton* vectBButton;
    
    // Integration tab components
    QWidget* integrationTab;
    QLineEdit* integrationFunctionEdit;
    QLineEdit* integrationLowerBoundEdit;
    QLineEdit* integrationUpperBoundEdit;
    QSpinBox* integrationIntervalsSpinBox;
    QPushButton* calculateIntegralButton;
    QLabel* integrationResultLabel;
    QListWidget* integrationHistoryList;
    QChartView* rectangleChartView;
    QChart* rectangleChart;
    QChartView* trapezoidChartView;
    QChart* trapezoidChart;
    
    // System tab components
    QWidget* systemTab;
    QSpinBox* systemSizeSpinBox;
    QSpinBox* systemVarsSpinBox;
    QGridLayout* systemGrid;
    QPushButton* solveSystemButton;
    QLabel* systemResultLabel;
    QListWidget* systemHistoryList;
    QPushButton* clearSystemHistoryButton;
    
    // Function tab components
    QWidget* functionTab;
    QLineEdit* functionEdit;
    QLineEdit* functionLowerBoundEdit;
    QLineEdit* functionUpperBoundEdit;
    QCheckBox* findDerivativeCheck;
    QCheckBox* findRootsCheck;
    QCheckBox* analyzeBehaviorCheck;
    QPushButton* analyzeButton;
    QTextEdit* functionResultText;
    QListWidget* functionHistoryList;
    QLineEdit* xValueEdit;
    
    // Analysis tab components
    QWidget* analysisTab;
    QPushButton* loadFileButton;
    QComboBox* fileTypeComboBox;
    QPushButton* visualizeButton;
    QTableWidget* dataTable;
    QChartView* chartView;
    QChart* chart;
    QVector<QVector<double>> analysisData;
    QStringList dataHeaders;
    
    // Internal storage of matrix values ​​(UI independent)
    QVector<QVector<double>> matrixAData;
    QVector<QVector<double>> matrixBData;
    
    // Methods to setup UI components

    /**
     * @brief Configures and initializes the matrix tab in the main window.
     * 
     * This function sets up the user interface components and layout
     * for the matrix tab, ensuring it is ready for interaction.
     */
    void setupMatrixTab();


    /**
     * @brief Sets up the Integration tab in the main window.
     * 
     * This function initializes and configures the UI components 
     * and layout for the Integration tab of the application.
     */
    void setupIntegrationTab();


    /**
     * @brief Configures and initializes the System tab in the main window.
     * 
     * This function sets up the user interface elements and functionality
     * for the System tab, ensuring it is ready for user interaction.
     */
    void setupSystemTab();


    /**
     * @brief Sets up the Function tab in the main window.
     * 
     * This method initializes and configures the components
     * and layout of the Function tab in the application's GUI.
     */
    void setupFunctionTab();


    /**
     * @brief Sets up the Analysis tab in the main window.
     * 
     * This function initializes and configures the components
     * of the Analysis tab, ensuring proper layout and functionality.
     */
    void setupAnalysisTab();
    
    // Helper methods


    /**
     * @brief Resizes the matrix A to match the required dimensions.
     *
     * This function adjusts the size of matrix A, ensuring it conforms
     * to the expected dimensions for further operations.
     */
    void resizeMatrixA();


    /**
     * @brief Resizes matrix B to match the required dimensions.
     * 
     * This function adjusts the size of matrix B, ensuring it conforms
     * to the necessary specifications for further operations.
     */
    void resizeMatrixB();

    /**
     * @brief Adjusts the sizes of the cells in the given matrix table.
     * 
     * This function ensures that the cells of the provided QTableWidget
     * are resized appropriately to fit their content or maintain a consistent
     * appearance.
     * 
     * @param matrixTable Pointer to the QTableWidget whose cell sizes need adjustment.
     */
    void adjustMatrixCellSizes(QTableWidget* matrixTable);

    /**
     * @brief Displays the result matrix in the user interface.
     * 
     * This function takes a 2D vector of doubles representing a matrix
     * and displays it in the application's user interface.
     * 
     * @param matrix A 2D QVector containing the matrix to be displayed.
     */
    void displayResultMatrix(const QVector<QVector<double>> &matrix);

    /**
     * @brief Adds an operation and its result to the history.
     * 
     * This function records a performed operation along with its result
     * into the application's history for later reference.
     * 
     * @param operation The mathematical operation performed as a QString.
     * @param result The result of the operation as a QString.
     */
    void addToHistory(const QString &operation, const QString &result);

    /**
     * @brief Clears the history of matrix operations or states.
     * 
     * This function resets or removes all stored matrix history, 
     * ensuring a clean slate for further operations.
     */
    void clearMatrixHistory();
    
    // Event handlers

    /**
     * @brief Overrides the event filter to handle custom events for the watched object.
     * 
     * This method is called to filter events before they reach the target object.
     * It can be used to intercept and process specific events for the given object.
     * 
     * @param watched The object being watched for events.
     * @param event The event to be filtered.
     * @return true if the event is handled and should not be propagated further; 
     *         false otherwise.
     */
    bool eventFilter(QObject* watched, QEvent* event) override;
};
#endif // MAINWINDOW_H
