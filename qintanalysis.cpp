#include "qintanalysis.h"
#include "NodeSequence/sobolsequence.h"
#include "TestFunction/genzfunction.h"
#include <QtGui>

QIntAnalysis::QIntAnalysis(RInside & R) : instR(R)
{
    tempfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("tfile <- tempfile()")));
    svgfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("sfile <- tempfile()")));
    SobolSequence *seq = new SobolSequence(10, 5);
    GenzFunction *fun = new GenzFunction(1, 10, new double{0}, new double{1});
    routine = IntegrationScenario(seq, fun);
    routine.RunAnalysis();
    setupDisplay();
}


QIntAnalysis::~QIntAnalysis()
{
    QFile outfile(svgfile);
    outfile.remove();
}

void QIntAnalysis::setupDisplay()
{
    QWidget *window = new QWidget;
    window->setWindowTitle("QINT: numerical integration with error control");

    QGroupBox *testFunctionBox = new QGroupBox("Test function");

    QGroupBox *integrationRuleBox = new QGroupBox("Integration rule and parameters");

    QHBoxLayout *upperlayout = new QHBoxLayout;
    upperlayout->addWidget(testFunctionBox);
    upperlayout->addWidget(integrationRuleBox);

    QHBoxLayout *lowerlayout = new QHBoxLayout;
    svg = new QSvgWidget();
    plot();

    lowerlayout->addWidget(svg);

    QVBoxLayout *outer = new QVBoxLayout;
    outer->addLayout(upperlayout);
    outer->addLayout(lowerlayout);
    window->setLayout(outer);
    window->show();
}

void QIntAnalysis::plot()
{
    std::string cmd0 = "require(ggplot2);";
    std::string cmd1 = "image <- qplot(1:50);";
    std::string cmd2 = "ggsave(file=tfile, plot=image, device=svg, width=10, height=8)";
    std::string cmd = cmd0 + cmd1 + cmd2;
    instR.parseEvalQ(cmd);
    filterFile();
    svg->load(svgfile);
}

void QIntAnalysis::filterFile() {
    // cairoDevice creates richer SVG than Qt can display
    QFile infile(tempfile);
    infile.open(QFile::ReadOnly);
    QFile outfile(svgfile);
    outfile.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream in(&infile);
    QTextStream out(&outfile);
    QRegExp rx1("<symbol");
    QRegExp rx2("</symbol");
    while (!in.atEnd()) {
        QString line = in.readLine();
        line.replace(rx1, "<g"); // so '<symbol' becomes '<g ...'
        line.replace(rx2, "</g");// and '</symbol becomes '</g'
        out << line << "\n";
    }
    infile.close();
    infile.remove();
    outfile.close();
}

