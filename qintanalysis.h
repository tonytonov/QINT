#ifndef QINTANALYSIS_H
#define QINTANALYSIS_H

#include <RInside.h>

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QTemporaryFile>
#include <QSvgWidget>

#include <integrationscenario.h>
#include <intguiparams.h>

class QIntAnalysis : public QMainWindow
{
    Q_OBJECT
    
public:
    QIntAnalysis(RInside &R);
    ~QIntAnalysis();

private:
    void setupDisplay();
    void filterFile();
    void plot(void);

private slots:
    void configure(void);

private:
    RInside &instR;               // reference to R instance passed to constructor
    QSvgWidget *svg;              // SVG device
    QString tempfile;             // temporary file for initial R plot
    QString svgfile;              // temporary file for resulting R plot
    IntegrationScenario routine;  // contains test function, node sequence and estimation algorithm
    IntGuiParams *params;         // params from GUI forms
};

#endif // QINTANALYSIS_H
