#include "StdAfx.h"
#include "ScatterGraph.h"


namespace sandbox 
{;

ScatterGraph::ScatterGraph(void)  
{
    InitializeComponent();

    m_GateDrawing = GateDrawing::IGateDrawing::createGateDrawingForScatterPlot();
    m_GateDrawing->Attach(NI_scatterGraph, NI_scatterPlot);
}


void ScatterGraph::Draw(cli::array<double>^ xValuesArray, cli::array<double>^ yValuesArray)
{
    NI_scatterPlot->ClearData();
    NI_scatterPlot->PlotXY(xValuesArray, yValuesArray);
}

}
