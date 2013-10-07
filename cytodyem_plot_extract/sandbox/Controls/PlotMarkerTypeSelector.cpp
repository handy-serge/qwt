#include "stdafx.h"
#include "PlotMarkerTypeSelector.h"
#include "MarkerTypeChangedEventArgs.h"
#using "Interfaces.dll"


using namespace System::Collections::Generic;

static void SetEnumValues(ComboBox^ cb)
{
    List<KeyValuePair<String^, GateDrawing::PlotMarkerType>>^ list = gcnew List<KeyValuePair<String^, GateDrawing::PlotMarkerType>>();
    Type^ t = GateDrawing::PlotMarkerType::typeid;
    Array^ values = Enum::GetValues(t);
    for each(GateDrawing::PlotMarkerType v in values)
    {
        String^ name = Enum::GetName(t, v);
        String^ description = name;
        switch (v)
        {
            // Todo: get description from attribute.
        case GateDrawing::PlotMarkerType::Rectangle:
            description = "Rectangle";
            break;
        case GateDrawing::PlotMarkerType::Polygon:
            description = "Polygon";
            break;
        case GateDrawing::PlotMarkerType::Stripe:
            description = "Stripe";
            break;
        }
        list->Add(KeyValuePair<String^, GateDrawing::PlotMarkerType>(description, v));
    }
    cb->DisplayMember = "Key";
    cb->ValueMember = "Value";
    cb->DataSource = list;
}

CustomControls::PlotMarkerTypeSelector::PlotMarkerTypeSelector( void )
{
     InitializeComponent();
     SetEnumValues(m_comboBox);
     m_comboBox->SelectedValue = GateDrawing::PlotMarkerType::Rectangle;
}

CustomControls::PlotMarkerTypeSelector::~PlotMarkerTypeSelector()
{
    if (components)
    {
        delete components;
    }
}

System::Void CustomControls::PlotMarkerTypeSelector::OnComboBoxIndexChanged( System::Object^ sender, System::EventArgs^ e )
{
    GateDrawing::PlotMarkerType markerType = (GateDrawing::PlotMarkerType)m_comboBox->SelectedValue;
    MarkerTypeSelected(
        this,
        gcnew MarkerTypeChangedEventArgs(markerType));
}
