#pragma once

#include "Result.h"
#include "AnalysisGraph.h"
#include "FormLoadExperiment.h"
#include "ImportFile.h"
#include <vector>

namespace sandbox 
{;

/// <summary>
/// Summary for MainWindow
/// </summary>
public ref class MainWindow : public System::Windows::Forms::Form
{
public:
    MainWindow(void);

protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~MainWindow();
private: System::Windows::Forms::Button^  eraseMarkerButton;
protected: 

protected: 

protected: 

    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>

    void MainWindow::InitializeComponent( void )
    {
        System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
        this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
        this->tableLayoutPlotPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
        this->panelGraph1 = (gcnew System::Windows::Forms::Panel());
        this->panelGraph2 = (gcnew System::Windows::Forms::Panel());
        this->flowLayoutPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
        this->loadButton = (gcnew System::Windows::Forms::Button());
        this->plotMarkerTypeSelector = (gcnew CustomControls::PlotMarkerTypeSelector());
        this->eraseMarkerButton = (gcnew System::Windows::Forms::Button());
        this->tableLayoutPanel1->SuspendLayout();
        this->tableLayoutPlotPanel->SuspendLayout();
        this->flowLayoutPanel->SuspendLayout();
        this->SuspendLayout();
        // 
        // tableLayoutPanel1
        // 
        this->tableLayoutPanel1->ColumnCount = 1;
        this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
            50)));
        this->tableLayoutPanel1->Controls->Add(this->tableLayoutPlotPanel, 0, 1);
        this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel, 0, 0);
        this->tableLayoutPanel1->Location = System::Drawing::Point(12, 3);
        this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
        this->tableLayoutPanel1->RowCount = 2;
        this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.30556F)));
        this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 455)));
        this->tableLayoutPanel1->Size = System::Drawing::Size(732, 490);
        this->tableLayoutPanel1->TabIndex = 0;
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
        // flowLayoutPanel
        // 
        this->flowLayoutPanel->Controls->Add(this->loadButton);
        this->flowLayoutPanel->Controls->Add(this->plotMarkerTypeSelector);
        this->flowLayoutPanel->Controls->Add(this->eraseMarkerButton);
        this->flowLayoutPanel->Dock = System::Windows::Forms::DockStyle::Fill;
        this->flowLayoutPanel->Location = System::Drawing::Point(3, 3);
        this->flowLayoutPanel->Name = L"flowLayoutPanel";
        this->flowLayoutPanel->Size = System::Drawing::Size(726, 29);
        this->flowLayoutPanel->TabIndex = 2;
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
        // plotMarkerTypeSelector
        // 
        this->plotMarkerTypeSelector->AutoSize = true;
        this->plotMarkerTypeSelector->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->plotMarkerTypeSelector->Location = System::Drawing::Point(84, 3);
        this->plotMarkerTypeSelector->Name = L"plotMarkerTypeSelector";
        this->plotMarkerTypeSelector->Size = System::Drawing::Size(78, 24);
        this->plotMarkerTypeSelector->TabIndex = 2;
        this->plotMarkerTypeSelector->MarkerTypeSelected += gcnew System::EventHandler<CustomControls::MarkerTypeChangedEventArgs^ >(this, &MainWindow::OnMarkerTypeSelected);
        // 
        // eraseMarkerButton
        // 
        this->eraseMarkerButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"eraseMarkerButton.BackgroundImage")));
        this->eraseMarkerButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
        this->eraseMarkerButton->Location = System::Drawing::Point(168, 3);
        this->eraseMarkerButton->Name = L"eraseMarkerButton";
        this->eraseMarkerButton->Size = System::Drawing::Size(26, 23);
        this->eraseMarkerButton->TabIndex = 3;
        this->eraseMarkerButton->UseVisualStyleBackColor = true;
        this->eraseMarkerButton->Click += gcnew System::EventHandler(this, &MainWindow::button1_Click);
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
        this->flowLayoutPanel->ResumeLayout(false);
        this->flowLayoutPanel->PerformLayout();
        this->ResumeLayout(false);

    }
#pragma endregion


    // Designers variables.
    System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
    System::Windows::Forms::Button^  loadButton;

    System::Windows::Forms::TableLayoutPanel^  tableLayoutPlotPanel;
    System::Windows::Forms::Panel^  panelGraph1;
    System::Windows::Forms::Panel^  panelGraph2;

    System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel;
    CustomControls::PlotMarkerTypeSelector^  plotMarkerTypeSelector;

    // Event handlers
    System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void OnMarkerTypeSelected(System::Object^  sender, CustomControls::MarkerTypeChangedEventArgs^  e);

private:
    Result *m_Result;
    AnalysisGraph ^m_Graph1;
    AnalysisGraph ^m_Graph2;


private: System::Void plotMarkerTypeSelector_Load(System::Object^  sender, System::EventArgs^  e) {
         }
private: System::Void removeGateControl_Click(System::Object^  sender, System::EventArgs^  e) {
             m_Graph1->EraseMarker();
             m_Graph2->EraseMarker();
         }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
             m_Graph1->EraseMarker();
             m_Graph2->EraseMarker();
         }
};
}

