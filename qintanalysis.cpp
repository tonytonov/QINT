#include "qintanalysis.h"
#include "NodeSequence/sobolsequence.h"
#include "TestFunction/genzfunction.h"
#include "EstimationAlgorithm/mcconfint.h"
#include "intguiparams.h"
#include <QtGui>

QIntAnalysis::QIntAnalysis(RInside &R) : instR(R)
{
    tempfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("tfile <- tempfile()")));
    svgfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("sfile <- tempfile()")));

    params = new IntGuiParams();
    params->setFunctionIndex(0);
    params->setFunctionDim(5);
    params->setRuleIndex(0);
    params->setSeqLength(100);

    setupDisplay();
}

QIntAnalysis::~QIntAnalysis()
{
    delete params;
    delete svg;
    QFile outfile(svgfile);
    outfile.remove();
}

void QIntAnalysis::setupDisplay()
{
    QWidget *window = new QWidget;
    window->setWindowTitle("QINT: numerical integration with error control");

    QComboBox *testFunctionPick = new QComboBox;
    testFunctionPick->addItem("foo1");
    testFunctionPick->addItem("foo2");
    testFunctionPick->addItem("foo3");
    testFunctionPick->setCurrentIndex(params->getFunctionIndex());
    QObject::connect(testFunctionPick, SIGNAL(activated(int)), this->params, SLOT(setFunctionIndex(int)));

    QValidator *dimValidator = new QIntValidator(1, 10);
    QLineEdit *dimEdit = new QLineEdit;
    dimEdit->setValidator(dimValidator);
    dimEdit->setText(QString::number(params->getFunctionDim()));
    QObject::connect(dimEdit, SIGNAL(textEdited(QString)), this->params, SLOT(setFunctionDim(QString)));

    QVBoxLayout *topleft = new QVBoxLayout;
    topleft->addWidget(testFunctionPick);
    topleft->addWidget(dimEdit);
    QGroupBox *testFunctionBox = new QGroupBox("Test function");
    testFunctionBox->setMinimumSize(360,140);
    testFunctionBox->setMaximumSize(360,140);
    testFunctionBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    testFunctionBox->setLayout(topleft);

    QComboBox *intRulePick = new QComboBox;
    intRulePick->addItem("bar1");
    intRulePick->addItem("bar2");
    intRulePick->addItem("bar3");
    intRulePick->setCurrentIndex(params->getRuleIndex());
    QObject::connect(intRulePick, SIGNAL(activated(int)), this->params, SLOT(setRuleIndex(int)));

    QValidator *lenValidator = new QIntValidator(1, 100);
    QLineEdit *lenEdit = new QLineEdit;
    lenEdit->setValidator(lenValidator);
    lenEdit->setText(QString::number(params->getSeqLength()));
    QObject::connect(lenEdit, SIGNAL(textEdited(QString)), this->params, SLOT(setSeqLength(QString)));

    QPushButton *startButton = new QPushButton("Launch");
    QObject::connect(startButton, SIGNAL(released()), this, SLOT(configure()));

    QVBoxLayout *topright = new QVBoxLayout;
    topright->addWidget(intRulePick);
    topright->addWidget(lenEdit);
    topright->addWidget(startButton);
    QGroupBox *integrationRuleBox = new QGroupBox("Integration rule and parameters");
    integrationRuleBox->setMinimumSize(360,140);
    integrationRuleBox->setMaximumSize(360,140);
    integrationRuleBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    integrationRuleBox->setLayout(topright);

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

void QIntAnalysis::configure()
{
    NodeSequence *seq;
    switch (params->getRuleIndex())
    {
    case 0:
        seq = new SobolSequence(params->getFunctionDim(), params->getSeqLength());
        break;
    case 1:
        //TODO: implement mc sequence
        //seq = new monte-carlo sequence
    default:
        break;
    }

    TestFunction *fun;
    fun = new GenzFunction(params->getFunctionIndex() + 1, params->getFunctionDim());

    EstimationAlgorithm *alg;
    alg = new MCConfint(0.95, 1.64);

    routine.setSeq(seq);
    routine.setFun(fun);
    routine.setAlg(alg);
    routine.RunAnalysis();
}

void QIntAnalysis::filterFile()
{
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
