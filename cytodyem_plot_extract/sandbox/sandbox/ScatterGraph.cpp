#include "StdAfx.h"
#include "ScatterGraph.h"


namespace sandbox {

void ScatterGraph::Draw(cli::array<double>^ xValuesArray, cli::array<double>^ yValuesArray)
{
    NI_scatterPlot->ClearData();
    NI_scatterPlot->PlotXY(xValuesArray, yValuesArray);
}

}
