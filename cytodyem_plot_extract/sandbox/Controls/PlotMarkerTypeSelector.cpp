#include "stdafx.h"
#include "PlotMarkerTypeSelector.h"

CustomControls::PlotMarkerTypeSelector::PlotMarkerTypeSelector( void )
{
    InitializeComponent();
    m_comboBox->SelectedIndex = 0;
}

CustomControls::PlotMarkerTypeSelector::~PlotMarkerTypeSelector()
{
    if (components)
    {
        delete components;
    }
}

System::Void CustomControls::PlotMarkerTypeSelector::OnComboBoxValueChanged( System::Object^ sender, System::EventArgs^ e )
{
    MarkerTypeSelected();
}
