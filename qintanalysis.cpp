#include "qintanalysis.h"
#include "NodeSequence/sobolsequence.h"
#include "NodeSequence/mcuniformsequence.h"
#include "TestFunction/genzfunction.h"
#include "EstimationAlgorithm/mcconfint.h"
#include "EstimationAlgorithm/qmcqconfint.h"
#include "intguiparams.h"
#include <cmath>
#include <QSvgWidget>
#include <QTemporaryFile>
#include <QTextStream>

QIntAnalysis::QIntAnalysis(RInside &R) : instR(R)
{
    tempfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("tfile <- tempfile()")));
    svgfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("sfile <- tempfile()")));
}

QIntAnalysis::~QIntAnalysis()
{
    delete svg;
    QFile outfile(svgfile);
    outfile.remove();
}

void QIntAnalysis::configureSvgWidget(int w, int h)
{
    svg = new QSvgWidget();
    svg->setMinimumSize(w, h);
    svg->setMaximumSize(w, h);
    svg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSvgWidget *QIntAnalysis::getSvgWidget() const
{
    return svg;
}

void QIntAnalysis::configure(IntGuiParams *params)
{
    NodeSequence *seq;
    EstimationAlgorithm *alg;
    switch (params->getRuleIndex())
    {
    case 0:
        seq = new SobolSequence(params->getFunctionDim(), params->getSeqLength());
        alg = new QMCQConfint(seq, params->getkParam(), params->getsParam());
        break;
    case 1:
        seq = new MCUniformSequence(params->getFunctionDim(), params->getSeqLength(), 1, instR);
        alg = new MCConfint(0.95, 1.64);
    default:
        break;
    }

    TestFunction *fun;
    fun = new GenzFunction(params->getFunctionIndex() + 1, params->getFunctionDim());

    routine.setSeq(seq);
    routine.setFun(fun);
    routine.setAlg(alg);
    routine.RunAnalysis();
    plot();
}

void QIntAnalysis::exportData()
{
    //TODO: disable button if no data
    std::string cmd = "dir.create('~/QINT', showWarnings = FALSE); "
            "filename <- gsub(' ', '_', Sys.time()); "
            "filename <- gsub(':', '', filename); "
            "write.csv(image.df, file = paste('~/QINT/', filename, '.csv', sep = ''));";
    instR.parseEvalQ(cmd);
}

void QIntAnalysis::plot()
{
    loadDataIntoR();
    std::string cmd0 = "require(ggplot2);require(reshape2);"
            "image.melt.df <- melt(image.df, id.vars='number');"
            "image <- ggplot(image.melt.df, aes(x=number, y=value, colour=variable, group=variable)) + "
            "geom_path(size=1.2) + "
            "labs(title=paste('QINT ', sep=''),"
            "    y='', x='', colour='', size='') + "
            "scale_colour_brewer(palette='Set1') + "
            "theme("
            "   legend.text = element_text(size = 16, face = 'bold'),"
            "   legend.title = element_text(size = 16, face = 'bold'),"
            "   plot.title = element_text(size = 16, face = 'bold', vjust = 1.2),"
            "   axis.title.x = element_text(size = 16, face = 'bold', vjust = -0.2),"
            "   axis.title.y = element_text(size = 16, face = 'bold', vjust = 0.2),"
            "   axis.text.x = element_text(size = 14, colour = 'black'),"
            "   axis.text.y = element_text(size = 14, colour = 'black')"
            "   ) + "
            "ylim(0, max(image.df[nrow(image.df), -ncol(image.df)]) * 8); ";
    std::string cmd1 = "ggsave(file=tfile, plot=image, device=svg, width=10, height=8);";
    std::string cmd = cmd0 + cmd1;
    instR.parseEvalQ(cmd);
    filterFile();
    svg->load(svgfile);
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

void QIntAnalysis::loadDataIntoR()
{
    typedef QMap<int, double> QBorderMap;
    std::vector<double> estimate = routine.getAlg()->getEstimate().toStdVector();
    QList<QBorderMap> border = routine.getAlg()->getBorder();
    std::vector<int> borderIndices;
    std::vector<double> borderValues;
    foreach (const QBorderMap& singleBorder, border) {
        foreach (int borderKey, singleBorder.keys()) {
            borderIndices.push_back(borderKey);
            borderValues.push_back(singleBorder.value(borderKey));
        }
    }
    instR["estimate"] = estimate;
    instR["exact"] = routine.getExact();
    instR["borderIndices"] = borderIndices;
    instR["borderValues"] = borderValues;

    std::string cmd = "image.df <- data.frame(error = abs(estimate - exact), border = NA);"
            "image.df$border[borderIndices] <- borderValues;"
            "image.df$number <- as.numeric(rownames(image.df));";
    instR.parseEvalQ(cmd);
}
