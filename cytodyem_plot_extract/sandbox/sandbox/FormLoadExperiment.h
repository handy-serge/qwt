#pragma once

#include <iostream>

namespace sandbox {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for FormLoadExperiment
	/// </summary>
	public ref class FormLoadExperiment : public System::Windows::Forms::Form
	{
	public:
		FormLoadExperiment(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            this->cancelled = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormLoadExperiment()
		{
			if (components)
			{
				delete components;
			}
		}

    private: System::Windows::Forms::TextBox^  filePathAndName;
    private: System::Windows::Forms::Button^  browseButton;
    private: System::Windows::Forms::Button^  loadConfirmedButton;
    private: System::Windows::Forms::Button^  cancelButton;

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
            this->filePathAndName = (gcnew System::Windows::Forms::TextBox());
            this->browseButton = (gcnew System::Windows::Forms::Button());
            this->loadConfirmedButton = (gcnew System::Windows::Forms::Button());
            this->cancelButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // filePathAndName
            // 
            this->filePathAndName->Location = System::Drawing::Point(22, 39);
            this->filePathAndName->Name = L"filePathAndName";
            this->filePathAndName->Size = System::Drawing::Size(298, 20);
            this->filePathAndName->TabIndex = 4;
            this->filePathAndName->TextChanged += gcnew System::EventHandler(this, &FormLoadExperiment::filePathAndName_TextChanged);
            // 
            // browseButton
            // 
            this->browseButton->Location = System::Drawing::Point(326, 35);
            this->browseButton->Name = L"browseButton";
            this->browseButton->Size = System::Drawing::Size(63, 27);
            this->browseButton->TabIndex = 5;
            this->browseButton->Text = L"Browse";
            this->browseButton->UseVisualStyleBackColor = true;
            this->browseButton->Click += gcnew System::EventHandler(this, &FormLoadExperiment::browseButton_Click);
            // 
            // loadConfirmedButton
            // 
            this->loadConfirmedButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->loadConfirmedButton->Enabled = false;
            this->loadConfirmedButton->Location = System::Drawing::Point(122, 166);
            this->loadConfirmedButton->Name = L"loadConfirmedButton";
            this->loadConfirmedButton->Size = System::Drawing::Size(75, 23);
            this->loadConfirmedButton->TabIndex = 3;
            this->loadConfirmedButton->Text = L"Load";
            this->loadConfirmedButton->UseVisualStyleBackColor = true;
            // 
            // cancelButton
            // 
            this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->cancelButton->Location = System::Drawing::Point(203, 166);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(75, 23);
            this->cancelButton->TabIndex = 6;
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->UseVisualStyleBackColor = true;
            this->cancelButton->Click += gcnew System::EventHandler(this, &FormLoadExperiment::cancelButton_Click);
            // 
            // FormLoadExperiment
            //
            this->AcceptButton = this->loadConfirmedButton;
            this->CancelButton = this->cancelButton;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(401, 210);
            this->Controls->Add(this->filePathAndName);
            this->Controls->Add(this->browseButton);
            this->Controls->Add(this->loadConfirmedButton);
            this->Controls->Add(this->cancelButton);
            this->Name = L"FormLoadExperiment";
            this->Text = L"Load File";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    public:
        bool IsCancelled()
        {
           return this->cancelled;
        }    
        
        String^ GetFilePath()
        {
            return filePathAndName->Text;
        }

    private:
        bool cancelled;

private: System::Void filePathAndName_TextChanged(System::Object^  sender, System::EventArgs^  e) 
        {
            this->loadConfirmedButton->Enabled = true;
        }

private: System::Void browseButton_Click(System::Object^ sender, System::EventArgs^ e) 
        {
            System::Windows::Forms::OpenFileDialog^ browseDialog = gcnew System::Windows::Forms::OpenFileDialog();
            
            browseDialog->DefaultExt = L"fcs";
            browseDialog->Filter = L"FCS files|*.fcs";

            if (browseDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                filePathAndName->Text = browseDialog->FileName;
            }
        }

private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
        {
            this->cancelled = true;
        }
	};
}
