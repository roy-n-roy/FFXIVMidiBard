#pragma once
#include "MidiInDevice.h"

namespace FFXIVMidiBard {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainWindow の概要
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	private:

	public:
		MainWindow(void)
		{
			InitializeComponent();
			cli::array<System::String^>^ midiInDeviceArray = MidiInDevice::GetNames();

			for (int i = 0; i < midiInDeviceArray->Length; i++) {
				MidiInPortComboBox->Items->Add(midiInDeviceArray[i]);
			}

			if (MidiInPortComboBox->Items->Count > 0) {
				MidiInPortComboBox->SelectedIndex = 0;
				MidiInDevice::Start(0);
			}
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ComboBox^ MidiInPortComboBox;
	protected:

	private: System::Windows::Forms::Label^ MidiInPortLabel;

	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->MidiInPortComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->MidiInPortLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// MidiInPortComboBox
			// 
			this->MidiInPortComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->MidiInPortComboBox->FormattingEnabled = true;
			this->MidiInPortComboBox->ItemHeight = 12;
			this->MidiInPortComboBox->Location = System::Drawing::Point(24, 52);
			this->MidiInPortComboBox->Name = L"MidiInPortComboBox";
			this->MidiInPortComboBox->Size = System::Drawing::Size(249, 20);
			this->MidiInPortComboBox->TabIndex = 0;
			this->MidiInPortComboBox->SelectionChangeCommitted += gcnew System::EventHandler(this, &MainWindow::MidiInPortComboBox_SelectionChangeCommitted);
			// 
			// MidiInPortLabel
			// 
			this->MidiInPortLabel->AutoSize = true;
			this->MidiInPortLabel->Location = System::Drawing::Point(10, 24);
			this->MidiInPortLabel->Name = L"MidiInPortLabel";
			this->MidiInPortLabel->Size = System::Drawing::Size(53, 12);
			this->MidiInPortLabel->TabIndex = 1;
			this->MidiInPortLabel->Text = L"MIDI Port";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(285, 91);
			this->Controls->Add(this->MidiInPortLabel);
			this->Controls->Add(this->MidiInPortComboBox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"FFXIV MIDI Bard";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MidiInPortComboBox_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
		MidiInDevice::Stop();
		MidiInDevice::Start(MidiInPortComboBox->SelectedIndex);
	}
	};
}
