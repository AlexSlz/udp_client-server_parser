#pragma once
#include "serverH.h"
#include <cstdio>
#using <mscorlib.dll>


int height = 500, width = 500;


namespace winForm {

	using namespace System;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			for (size_t i = 0; i < getCommandsLen(); i++)
			{
				listBox1->Items->Add(gcnew String(getCommandsName(i).c_str()));
			}
			SerialPort a;
			if(a.GetPortNames())
				comboBox1->Items->AddRange(a.GetPortNames());
			//myServerThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::ThreadStartServer));
			initwindow(width, height, "drawBox");
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ListBox^ listBox1;

	private: System::Windows::Forms::Label^ label1;
	private: Thread^ myServerThread;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label3;
	private: System::IO::Ports::SerialPort^ serialPort1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;

	private: System::ComponentModel::IContainer^ components;





	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 25;
			this->listBox1->Location = System::Drawing::Point(12, 37);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(360, 229);
			this->listBox1->TabIndex = 1;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(12, 386);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 24);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Arduino";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 309);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(360, 35);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Send to Arduino";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(7, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(160, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Commands List";
			// 
			// serialPort1
			// 
			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MyForm::serialPort1_DataReceived);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 350);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(360, 33);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 272);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(360, 31);
			this->textBox1->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(12, 434);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 24);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Form";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(384, 496);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBox1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (serialPort1->IsOpen) {
			formData = textBox1->Text;
			serialPort1->WriteLine(formData);
			this->Invoke(gcnew Action(this, &MyForm::SetFormInfo));
		}
		else {
			label1->Text = "Port Closed...";
		}
		/*
		if (!myServerThread->IsAlive) {
			myServerThread->Start();
			button1->Text = "Stop";
		}
		else {
			myServerThread->Abort();
			button1->Text = "Start";
		}
		button1->Text += " server";
		*/
	}
		   String^ arData;
		   String^ formData;
	/*
	public: void ThreadStartServer() {
		StartServer();
	}
		  const char* clientMsg;
		  const char* req;
		  SOCKET Socket;
		  void sendToClient(const char* text, sockaddr_in client_addr) {
			  sendto(Socket, text, strlen(text), 0, (sockaddr*)&client_addr, sizeof(client_addr));
		  }
		  string StartServer() {
			  char buff[1024];
			  if (WSAStartup(0x202, (WSADATA*)&buff[0]))
			  {
				  return "WSAStartup error!";
			  };

			  Socket = socket(AF_INET, SOCK_DGRAM, 0);
			  if (Socket == INVALID_SOCKET)
			  {
				  WSACleanup();
				  return "Socket error!";
			  };

			  sockaddr_in local_addr;
			  local_addr.sin_family = AF_INET;
			  local_addr.sin_addr.s_addr = INADDR_ANY;
			  local_addr.sin_port = htons(PORT);
			  //parseCommand("snake", 0);
			  bind(Socket, (sockaddr*)&local_addr, sizeof(local_addr));
			  while (1)
			  {
				  sockaddr_in client_addr;
				  int client_addr_size = sizeof(client_addr);
				  int bsize = recvfrom(Socket, &buff[0], sizeof(buff) - 1, 0, (sockaddr*)&client_addr, &client_addr_size);
				  HOSTENT* hst;
				  hst = gethostbyaddr((char*)&client_addr.sin_addr, 4, AF_INET);

				  buff[bsize] = 0;
				  clientMsg = buff;
				  req = parseCommand(buff, bsize);
				  sendToClient(req, client_addr);
				  this->Invoke(gcnew Action(this, &MyForm::SetInfo));
				  //printf("%s [%s:%d]: %s", (hst) ? hst->h_name : "Unknown host", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), &buff[0]);

			  }
		  }

			void SetInfo() {
				this->label1->Text = "Client: \n> " + (gcnew System::String(clientMsg));
				this->label2->Text = "Server: \n> " + (gcnew System::String(req));
			}
			*/
private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	if (serialPort1->IsOpen)
		serialPort1->Close();
	/*
	if (myServerThread->IsAlive) {
	myServerThread->Abort();
	}
	*/
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if(serialPort1->IsOpen)
		serialPort1->Close();
	try {
		serialPort1->PortName = comboBox1->SelectedItem->ToString();
		serialPort1->Open();
		label1->Text = "Conn...";
	}
	catch (...) {
		label1->Text = "Port Closed...";
	}
}
private: System::Void serialPort1_DataReceived(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e) {
	arData = serialPort1->ReadExisting();
	char* str = (char*)Marshal::StringToHGlobalAnsi(arData).ToPointer();
	arData = gcnew String(parseCommand(str, 0));
	this->Invoke(gcnew Action(this, &MyForm::SetArdInfo));
}
	   void SetArdInfo() {
		   this->label1->Text = "Arduino: \n> " + (gcnew System::String(arData));
	   }
	   void SetFormInfo() {
		   this->label2->Text = "Form: \n> " + (gcnew System::String(formData));
	   }
private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Text = listBox1->SelectedItem->ToString();
}
};

}
