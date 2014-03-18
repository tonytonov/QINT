#ifndef QINTANALYSIS_H
#define QINTANALYSIS_H

#include <RInside.h>
#include <QSvgWidget>
#include <IntegrationScenario.h>
#include <IntGUIParams.h>

class QIntAnalysis : public QObject
{
    Q_OBJECT
    
public:
    QIntAnalysis(RInside &R);
    ~QIntAnalysis();

    QSvgWidget *getSvgWidget() const;
    void configureSvgWidget(int w, int h);

private:
    void setupDisplay();
    void filterFile();
    void loadDataIntoR();
    void plot(void);

public slots:
    void configure(IntGuiParams *params);
    void exportData();

private:
    RInside &instR;                 // reference to R instance passed to constructor
    IntegrationScenario routine;    // contains test function, node sequence and estimation algorithm
    QSvgWidget *svg;                // SVG device
    QString tempfile;               // temporary file for initial R plot
    QString svgfile;                // temporary file for resulting R plot
};

#endif // QINTANALYSIS_H
