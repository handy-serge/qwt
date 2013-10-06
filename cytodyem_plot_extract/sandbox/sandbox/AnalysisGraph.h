#pragma once

#include "ScatterGraph.h"

namespace sandbox {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AnalysisGraph
	/// </summary>
	public ref class AnalysisGraph : public System::Windows::Forms::UserControl
	{
	public:
		AnalysisGraph(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

            // Store name and/or id of graph

            m_ScatterGraph = gcnew ScatterGraph();
            m_ScatterGraph->Parent = panelGraph;
            m_ScatterGraph->Visible = true;
            m_ScatterGraph->Dock = DockStyle::Fill;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AnalysisGraph()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Panel^  panelGraph;
    protected: 

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
            this->panelGraph = (gcnew System::Windows::Forms::Panel());
            this->SuspendLayout();
            // 
            // panelGraph
            // 
            this->panelGraph->Location = System::Drawing::Point(10, 13);
            this->panelGraph->Name = L"panelGraph";
            this->panelGraph->Size = System::Drawing::Size(270, 241);
            this->panelGraph->TabIndex = 0;
            // 
            // AnalysisGraph
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->panelGraph);
            this->Name = L"AnalysisGraph";
            this->Size = System::Drawing::Size(300, 300);
            this->ResumeLayout(false);

        }
#pragma endregion
    public:
            void ReDraw(std::vector<Result>& results);
            void SetMarkerType(GateDrawing::PlotMarkerType markerType );
    private:
        ScatterGraph ^m_ScatterGraph;
	};
}
