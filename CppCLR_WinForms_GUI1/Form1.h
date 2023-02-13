#pragma once

// uncomment to execute the rk1-utils:
//    #include "rk1_Utils_demo.h"  // shows how the rk1-utils can be used

//#include "pch.h"
//#include "Header1.h"
//#include "Header2.h"

//#include <map>
/*
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
*/


namespace CppCLRWinFormsProject {

  
  /// <summary>
  /// Summary for Form1
  /// </summary>
  public ref class Form1 : public System::Windows::Forms::Form
  {
  public:
    Form1(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //

      // uncomment to execute the rk1-utils:
      //    N_rk1_Utils_demo::execute(); // shows how the rk1-utils can be used

    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }


  private: System::Windows::Forms::Button^ button_plus_1;
  private: System::Windows::Forms::Button^ button1;
  private: System::Windows::Forms::DataGridView^ dataGridView1;







  private: System::Windows::Forms::Label^ label1;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^ ProcessName;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^ PID;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^ LR_Addr;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^ RR_Addr;












  private: System::ComponentModel::IContainer^ components;

  protected:

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>


#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
        this->button_plus_1 = (gcnew System::Windows::Forms::Button());
        this->button1 = (gcnew System::Windows::Forms::Button());
        this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
        this->ProcessName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
        this->PID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
        this->LR_Addr = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
        this->RR_Addr = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
        this->label1 = (gcnew System::Windows::Forms::Label());
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
        this->SuspendLayout();
        // 
        // button_plus_1
        // 
        this->button_plus_1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
        this->button_plus_1->Location = System::Drawing::Point(597, 33);
        this->button_plus_1->Name = L"button_plus_1";
        this->button_plus_1->Size = System::Drawing::Size(100, 37);
        this->button_plus_1->TabIndex = 2;
        this->button_plus_1->Text = L"Start/Reload";
        this->button_plus_1->UseVisualStyleBackColor = true;
        this->button_plus_1->Click += gcnew System::EventHandler(this, &Form1::button_start_Click);
        // 
        // button1
        // 
        this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
        this->button1->Location = System::Drawing::Point(597, 86);
        this->button1->Name = L"button1";
        this->button1->Size = System::Drawing::Size(100, 37);
        this->button1->TabIndex = 3;
        this->button1->Text = L"Block Connection";
        this->button1->UseVisualStyleBackColor = true;
        // 
        // dataGridView1
        // 
        this->dataGridView1->AllowUserToDeleteRows = false;
        this->dataGridView1->AllowUserToResizeRows = false;
        this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
        this->dataGridView1->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
        dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
        dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
        dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Segoe Print", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
        dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
        dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
        dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
        dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
        this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
        this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
        this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
            this->ProcessName,
                this->PID, this->LR_Addr, this->RR_Addr
        });
        this->dataGridView1->Location = System::Drawing::Point(12, 33);
        this->dataGridView1->Name = L"dataGridView1";
        this->dataGridView1->ReadOnly = true;
        this->dataGridView1->RowHeadersVisible = false;
        this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        this->dataGridView1->Size = System::Drawing::Size(579, 429);
        this->dataGridView1->TabIndex = 4;
        this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
        // 
        // ProcessName
        // 
        this->ProcessName->HeaderText = L"ProcessName";
        this->ProcessName->Name = L"ProcessName";
        this->ProcessName->ReadOnly = true;
        // 
        // PID
        // 
        this->PID->HeaderText = L"PID";
        this->PID->Name = L"PID";
        this->PID->ReadOnly = true;
        this->PID->Width = 50;
        // 
        // LR_Addr
        // 
        this->LR_Addr->HeaderText = L"Local Reverse Addr";
        this->LR_Addr->Name = L"LR_Addr";
        this->LR_Addr->ReadOnly = true;
        // 
        // RR_Addr
        // 
        this->RR_Addr->HeaderText = L"Remote Reverse Addr";
        this->RR_Addr->Name = L"RR_Addr";
        this->RR_Addr->ReadOnly = true;
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(162, 9);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(353, 13);
        this->label1->TabIndex = 7;
        this->label1->Text = L"Note: Might look like its frozen after pressing Start/Reload, but give it time";
        this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
        // 
        // Form1
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(734, 490);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->dataGridView1);
        this->Controls->Add(this->button1);
        this->Controls->Add(this->button_plus_1);
        this->Name = L"Form1";
        this->Text = L"Privatsphären-orientierte Firewall für Windows";
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
        this->ResumeLayout(false);
        this->PerformLayout();

    }
#pragma endregion

   // You can call the functions at a button click. If you prefer, 
    // you can call them by clicking a menu item.



	/* Note: could also use malloc() and free() */


  private: System::Void button_start_Click(System::Object^, System::EventArgs^);
  /* {
      //start();
  } */


  private: System::Void out_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

  }

private: System::Void in_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
/* {
} */
private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
    
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
}; // end of class Form1


} // end of namespace CppCLRWinFormsProject
