#pragma once

#include "Result.h"
#include "AnalysisGraph.h"
#include "FormLoadExperiment.h"
#include "ImportFile.h"
#include <vector>

namespace sandbox {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            m_Result = new Result;

            m_Graph1 = gcnew AnalysisGraph();
            m_Graph1->Parent = panelGraph1;
            m_Graph1->Visible = true;
            m_Graph1->Dock = DockStyle::Fill;

            m_Graph2 = gcnew AnalysisGraph();
            m_Graph2->Parent = panelGraph2;
            m_Graph2->Visible = true;
            m_Graph2->Dock = DockStyle::Fill;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
    private: System::Windows::Forms::Button^  loadButton;
    protected: 

    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPlotPanel;
    private: System::Windows::Forms::Panel^  panelGraph1;
    private: System::Windows::Forms::Panel^  panelGraph2;
    private: CustomControls::PlotMarkerTypeSelector^  plotMarkerTypeSelector1;
    private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;


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
            this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->loadButton = (gcnew System::Windows::Forms::Button());
            this->tableLayoutPlotPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->panelGraph1 = (gcnew System::Windows::Forms::Panel());
            this->panelGraph2 = (gcnew System::Windows::Forms::Panel());
            this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->plotMarkerTypeSelector1 = (gcnew CustomControls::PlotMarkerTypeSelector());
            this->tableLayoutPanel1->SuspendLayout();
            this->tableLayoutPlotPanel->SuspendLayout();
            this->flowLayoutPanel1->SuspendLayout();
            this->SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this->tableLayoutPanel1->ColumnCount = 1;
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
                50)));
            this->tableLayoutPanel1->Controls->Add(this->tableLayoutPlotPanel, 0, 1);
            this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 0);
            this->tableLayoutPanel1->Location = System::Drawing::Point(12, 3);
            this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
            this->tableLayoutPanel1->RowCount = 2;
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.30556F)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 455)));
            this->tableLayoutPanel1->Size = System::Drawing::Size(732, 490);
            this->tableLayoutPanel1->TabIndex = 0;
            // 
            // loadButton
            // 
            this->loadButton->Location = System::Drawing::Point(3, 3);
            this->loadButton->Name = L"loadButton";
            this->loadButton->Size = System::Drawing::Size(75, 23);
            this->loadButton->TabIndex = 0;
            this->loadButton->Text = L"Load";
            this->loadButton->UseVisualStyleBackColor = true;
            this->loadButton->Click += gcnew System::EventHandler(this, &MainWindow::loadButton_Click);
            // 
            // tableLayoutPlotPanel
            // 
            this->tableLayoutPlotPanel->ColumnCount = 2;
            this->tableLayoutPlotPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
                50)));
            this->tableLayoutPlotPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
                50)));
            this->tableLayoutPlotPanel->Controls->Add(this->panelGraph1, 0, 0);
            this->tableLayoutPlotPanel->Controls->Add(this->panelGraph2, 1, 0);
            this->tableLayoutPlotPanel->Location = System::Drawing::Point(3, 38);
            this->tableLayoutPlotPanel->Name = L"tableLayoutPlotPanel";
            this->tableLayoutPlotPanel->RowCount = 1;
            this->tableLayoutPlotPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 
                50)));
            this->tableLayoutPlotPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 
                443)));
            this->tableLayoutPlotPanel->Size = System::Drawing::Size(726, 443);
            this->tableLayoutPlotPanel->TabIndex = 1;
            // 
            // panelGraph1
            // 
            this->panelGraph1->Location = System::Drawing::Point(3, 3);
            this->panelGraph1->Name = L"panelGraph1";
            this->panelGraph1->Size = System::Drawing::Size(356, 250);
            this->panelGraph1->TabIndex = 0;
            // 
            // panelGraph2
            // 
            this->panelGraph2->Location = System::Drawing::Point(366, 3);
            this->panelGraph2->Name = L"panelGraph2";
            this->panelGraph2->Size = System::Drawing::Size(357, 250);
            this->panelGraph2->TabIndex = 1;
            // 
            // flowLayoutPanel1
            // 
            this->flowLayoutPanel1->Controls->Add(this->loadButton);
            this->flowLayoutPanel1->Controls->Add(this->plotMarkerTypeSelector1);
            this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->flowLayoutPanel1->Location = System::Drawing::Point(3, 3);
            this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
            this->flowLayoutPanel1->Size = System::Drawing::Size(726, 29);
            this->flowLayoutPanel1->TabIndex = 2;
            // 
            // plotMarkerTypeSelector1
            // 
            this->plotMarkerTypeSelector1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                | System::Windows::Forms::AnchorStyles::Left) 
                | System::Windows::Forms::AnchorStyles::Right));
            this->plotMarkerTypeSelector1->AutoSize = true;
            this->plotMarkerTypeSelector1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->plotMarkerTypeSelector1->Location = System::Drawing::Point(84, 3);
            this->plotMarkerTypeSelector1->Name = L"plotMarkerTypeSelector1";
            this->plotMarkerTypeSelector1->Size = System::Drawing::Size(79, 27);
            this->plotMarkerTypeSelector1->TabIndex = 2;
            // 
            // MainWindow
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(756, 496);
            this->Controls->Add(this->tableLayoutPanel1);
            this->Name = L"MainWindow";
            this->Text = L"Cytodyem Sandbox";
            this->tableLayoutPanel1->ResumeLayout(false);
            this->tableLayoutPlotPanel->ResumeLayout(false);
            this->flowLayoutPanel1->ResumeLayout(false);
            this->flowLayoutPanel1->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e)
             {
                FormLoadExperiment form;
                System::Windows::Forms::DialogResult res = form.ShowDialog(this);

                if (res == System::Windows::Forms::DialogResult::OK && !form.IsCancelled())
                {
                    std::vector<Result> Results(5);
                    ImportFile import;

                    import.LoadFCS(form.GetFilePath(), 5, Results);

                    m_Graph1->ReDraw(Results);
                    m_Graph2->ReDraw(Results);
                }
             }

private:
    Result *m_Result;
    AnalysisGraph ^m_Graph1;
    AnalysisGraph ^m_Graph2;
};
}

