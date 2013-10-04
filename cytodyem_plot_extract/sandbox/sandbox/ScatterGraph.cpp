#include "StdAfx.h"
#include "ScatterGraph.h"

#using "GateDrawing.dll"


namespace sandbox 
{;

ScatterGraph::ScatterGraph(void)  
{
    InitializeComponent();

    m_GateDrawing = GateDrawing::Factory::createGateDrawingForScatterPlot();
    m_GateDrawing->Attach(NI_scatterGraph, NI_scatterPlot);
}


void ScatterGraph::Draw(cli::array<double>^ xValuesArray, cli::array<double>^ yValuesArray)
{
    NI_scatterPlot->ClearData();
    NI_scatterPlot->PlotXY(xValuesArray, yValuesArray);
}

}
