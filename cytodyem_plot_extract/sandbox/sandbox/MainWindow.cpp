#include "stdafx.h"
#include "MainWindow.h"

sandbox::MainWindow::MainWindow( void )
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

sandbox::MainWindow::~MainWindow()
{
    if (components)
    {
        delete components;
    }
}

System::Void sandbox::MainWindow::loadButton_Click( System::Object^ sender, System::EventArgs^ e )
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

System::Void sandbox::MainWindow::OnMarkerTypeSelected(
    System::Object^ sender
    , CustomControls::MarkerTypeChangedEventArgs^ e)
{
    m_Graph1->SetMarkerType(e->MarkerType);
    m_Graph2->SetMarkerType(e->MarkerType);
}

