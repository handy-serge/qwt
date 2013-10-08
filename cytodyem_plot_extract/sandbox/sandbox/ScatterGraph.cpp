#include "StdAfx.h"
#include "ScatterGraph.h"

#using "GateDrawing.dll"


namespace sandbox 
{;

ScatterGraph::ScatterGraph(void)  
{
    InitializeComponent();
}


void ScatterGraph::Draw(cli::array<double>^ xValuesArray, cli::array<double>^ yValuesArray)
{
    NI_scatterPlot->ClearData();
    NI_scatterPlot->PlotXY(xValuesArray, yValuesArray);
}

void ScatterGraph::ChangeGateDrawing( GateDrawing::IGateDrawing^ gateDrawing )
{
    delete m_GateDrawing;

    m_GateDrawing = gateDrawing;
    m_GateDrawing->Attach(NI_scatterGraph, NI_scatterPlot);
}


void ScatterGraph::clearGate()
{
    m_GateDrawing->eraseMarker();
}

}
