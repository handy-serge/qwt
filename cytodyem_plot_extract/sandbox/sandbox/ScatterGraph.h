#pragma once

#include "Result.h"
#include <vector>

#using "Interfaces.dll"

namespace sandbox {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ScatterGraph
	/// </summary>
	public ref class ScatterGraph : public System::Windows::Forms::UserControl
	{
	public:
		ScatterGraph(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ScatterGraph()
		{
			if (components)
			{
				delete components;
			}
		}

    // Represents the class for Measurement Studio Windows Forms graphs that accept both x and y data values.
    private: NationalInstruments::UI::WindowsForms::ScatterGraph ^NI_scatterGraph;
    // Defines a class for plotting y values against x values.
    private: NationalInstruments::UI::ScatterPlot ^NI_scatterPlot;
    private: NationalInstruments::UI::XAxis ^NI_xAxis;
    private: NationalInstruments::UI::YAxis ^NI_yAxis;
    protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->NI_scatterGraph = (gcnew NationalInstruments::UI::WindowsForms::ScatterGraph());
            this->NI_scatterPlot = (gcnew NationalInstruments::UI::ScatterPlot());
            this->NI_xAxis = (gcnew NationalInstruments::UI::XAxis());
            this->NI_yAxis = (gcnew NationalInstruments::UI::YAxis());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NI_scatterGraph))->BeginInit();
            this->SuspendLayout();
            // 
            // NI_scatterGraph
            // 
            this->NI_scatterGraph->Border = NationalInstruments::UI::Border::None;
            this->NI_scatterGraph->Dock = System::Windows::Forms::DockStyle::Fill;
            this->NI_scatterGraph->InteractionMode = static_cast<NationalInstruments::UI::GraphInteractionModes>(((((NationalInstruments::UI::GraphInteractionModes::ZoomX | NationalInstruments::UI::GraphInteractionModes::ZoomY) 
                | NationalInstruments::UI::GraphInteractionModes::ZoomAroundPoint) 
                | NationalInstruments::UI::GraphInteractionModes::DragCursor) 
                | NationalInstruments::UI::GraphInteractionModes::DragAnnotationCaption));
            this->NI_scatterGraph->Location = System::Drawing::Point(0, 0);
            this->NI_scatterGraph->Name = L"NI_scatterGraph";
            this->NI_scatterGraph->PlotAreaColor = System::Drawing::Color::White;
            this->NI_scatterGraph->Plots->AddRange(gcnew cli::array< NationalInstruments::UI::ScatterPlot^  >(1) {this->NI_scatterPlot});
            this->NI_scatterGraph->Size = System::Drawing::Size(306, 309);
            this->NI_scatterGraph->TabIndex = 0;
            this->NI_scatterGraph->ZoomAnimation = false;
            this->NI_scatterGraph->XAxes->AddRange(gcnew cli::array< NationalInstruments::UI::XAxis^ >(1) {this->NI_xAxis});
            this->NI_scatterGraph->YAxes->AddRange(gcnew cli::array< NationalInstruments::UI::YAxis^ >(1) {this->NI_yAxis});
            // 
            // NI_scatterPlot
            // 
            this->NI_scatterPlot->HistoryCapacity = 25000;
            this->NI_scatterPlot->LineStyle = NationalInstruments::UI::LineStyle::None;
            this->NI_scatterPlot->PointColor = System::Drawing::Color::CornflowerBlue;
            this->NI_scatterPlot->PointSize = System::Drawing::Size(1, 1);
            this->NI_scatterPlot->PointStyle = NationalInstruments::UI::PointStyle::SolidSquare;
            this->NI_scatterPlot->XAxis = this->NI_xAxis;
            this->NI_scatterPlot->YAxis = this->NI_yAxis;
            // 
            // NI_xAxis
            // 
            this->NI_xAxis->Caption = L"Channel 1";
            this->NI_xAxis->MajorDivisions->Base = 1;
            this->NI_xAxis->MajorDivisions->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(205)), 
                static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(203)));
            this->NI_xAxis->MajorDivisions->GridVisible = true;
            this->NI_xAxis->MinorDivisions->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(237)), 
                static_cast<System::Int32>(static_cast<System::Byte>(234)), static_cast<System::Int32>(static_cast<System::Byte>(234)));
            this->NI_xAxis->MinorDivisions->GridVisible = true;
            this->NI_xAxis->MinorDivisions->TickVisible = true;
            this->NI_xAxis->Mode = NationalInstruments::UI::AxisMode::Fixed;
            this->NI_xAxis->Range = (gcnew NationalInstruments::UI::Range(0.01, 10000));
            this->NI_xAxis->ScaleType = NationalInstruments::UI::ScaleType::Logarithmic;
            // 
            // NI_yAxis
            // 
            this->NI_yAxis->Caption = L"Channel 2";
            this->NI_yAxis->MajorDivisions->Base = 1;
            this->NI_yAxis->MajorDivisions->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(205)), 
                static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(203)));
            this->NI_yAxis->MajorDivisions->GridVisible = true;
            this->NI_yAxis->MinorDivisions->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(237)), 
                static_cast<System::Int32>(static_cast<System::Byte>(234)), static_cast<System::Int32>(static_cast<System::Byte>(234)));
            this->NI_yAxis->MinorDivisions->GridVisible = true;
            this->NI_yAxis->MinorDivisions->TickVisible = true;
            this->NI_yAxis->Mode = NationalInstruments::UI::AxisMode::Fixed;
            this->NI_yAxis->Range = (gcnew NationalInstruments::UI::Range(0.01, 10000));
            this->NI_yAxis->ScaleType = NationalInstruments::UI::ScaleType::Logarithmic;
            // 
            // ScatterGraph
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->NI_scatterGraph);
            this->Name = L"ScatterGraph";
            this->Size = System::Drawing::Size(306, 309);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NI_scatterGraph))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
    public:
        void Draw(cli::array<double>^ xValuesArray, cli::array<double>^ yValuesArray);
        void ChangeGateDrawing( GateDrawing::IGateDrawing^ gateDrawing);
    private:
        GateDrawing::IGateDrawing ^m_GateDrawing;

    };
}
