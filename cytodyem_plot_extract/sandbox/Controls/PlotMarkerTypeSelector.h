#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CustomControls {

    public delegate void PlotMarkerTypeSelected();

	/// <summary>
	/// Summary for PlotMarkerTypeSelector
	/// </summary>
	public ref class PlotMarkerTypeSelector : public System::Windows::Forms::UserControl
	{
	public:
		PlotMarkerTypeSelector(void);
        event PlotMarkerTypeSelected^ MarkerTypeSelected;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlotMarkerTypeSelector();

    private: 
        System::Void OnComboBoxValueChanged(System::Object^  sender, System::EventArgs^  e);

        System::Windows::Forms::ComboBox^  m_comboBox;


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
            this->m_comboBox = (gcnew System::Windows::Forms::ComboBox());
            this->SuspendLayout();
            // 
            // m_comboBox
            // 
            this->m_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->m_comboBox->FormattingEnabled = true;
            this->m_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"R", L"P", L"H"});
            this->m_comboBox->Location = System::Drawing::Point(6, 3);
            this->m_comboBox->Name = L"m_comboBox";
            this->m_comboBox->Size = System::Drawing::Size(36, 21);
            this->m_comboBox->TabIndex = 0;
            this->m_comboBox->SelectedValueChanged += gcnew System::EventHandler(this, &PlotMarkerTypeSelector::OnComboBoxValueChanged);
            // 
            // PlotMarkerTypeSelector
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->Controls->Add(this->m_comboBox);
            this->Name = L"PlotMarkerTypeSelector";
            this->Size = System::Drawing::Size(47, 29);
            this->ResumeLayout(false);

        }
#pragma endregion

    };
}
