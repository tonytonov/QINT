#ifndef QINTANALYSIS_H
#define QINTANALYSIS_H

#include <RInside.h>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
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
    QIntAnalysis(RInside & R);
    ~QIntAnalysis();

private:
    void setupDisplay(void);
    void filterFile();
    void plot(void);

private slots:
    void configure(void);

private:
    RInside & instR;          // reference to the R instance passed to constructor
    QSvgWidget *svg;          // the SVG device
    QString tempfile;         // temporary file for initial R plot
    QString svgfile;          // temporary file for resulting R plot
    IntegrationScenario routine;
    IntGuiParams *params;
};

#endif // QINTANALYSIS_H
