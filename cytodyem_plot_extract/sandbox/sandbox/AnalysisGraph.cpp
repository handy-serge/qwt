#include "StdAfx.h"
#include "AnalysisGraph.h"
#include <cliext/vector>


namespace sandbox {

void AnalysisGraph::ReDraw(std::vector<Result>& results)
{
    size_t Index = 0;
    Result* pResultX = &results[1];    // TBD PHIL - SSC - Remove magic number
    Result* pResultY = &results[0];    // TBD PHIL - FSC - Remove magic number

    std::vector<Peak>::iterator itCur1 = pResultX->m_ListPeaks.begin();
    std::vector<Peak>::iterator itEnd1 = pResultX->m_ListPeaks.end();
    std::vector<Peak>::iterator itCur2 = pResultY->m_ListPeaks.begin();
    std::vector<Peak>::iterator itEnd2 = pResultY->m_ListPeaks.end();

    cliext::vector<double> xValues;
    cliext::vector<double> yValues;

    xValues.reserve(pResultX->m_ListPeaks.size());
    yValues.reserve(pResultY->m_ListPeaks.size());

    for (itCur1; itCur1 != itEnd1; ++itCur1, ++itCur2, ++Index)
    {
        double Val1 = (*itCur1).GetHeight()/* * m_DisplayMultiplierX */;
        double Val2 = (*itCur2).GetHeight()/* * m_DisplayMultiplierY */;

        xValues.push_back(Val1);
        yValues.push_back(Val2);
    }

    cli::array<double>^ xValuesArray =  xValues.to_array();
    cli::array<double>^ yValuesArray =  yValues.to_array();

    m_ScatterGraph->Draw(xValuesArray, yValuesArray);
}

}