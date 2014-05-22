#include "Tools.h"
using namespace Tools;
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::ComponentModel;

namespace FindHost
{	
	public ref class Form1 : public Form
	{
		private: TextBox ^ textBox1;
		private: Button ^ button1;
		private: RichTextBox ^  richTextBox1;
		private: ProgressBar ^  progressBar1;
		private: System::Windows::Forms::Timer^  timer1;
		private: TabControl^  tabControl1;
		private: TabPage^  tabPage1, ^ tabPage2;
		private: SplitContainer^  splitContainer1;
		private: TreeView^  treeView1;
		private: ImageList^  imageList1;
		private: ListView^  listView1;
		private: ColumnHeader^  columnHeader1, ^ columnHeader2, ^ columnHeader3;
		private: IContainer ^  components;
		private: int correctTimerCount = 0;

		public: Form1(void)
		{
			InitializeComponent();
		}

		protected: ~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(5, 5);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(416, 23);
			this->textBox1->TabIndex = 0;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyDown);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(424, 5);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(32, 22);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Go!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			this->button1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::button1_KeyDown);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->ForeColor = System::Drawing::Color::Blue;
			this->richTextBox1->Location = System::Drawing::Point(0, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(445, 255);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"";
			this->richTextBox1->WordWrap = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar1->Location = System::Drawing::Point(5, 33);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(451, 16);
			this->progressBar1->TabIndex = 4;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// tabControl1
			// 
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Bottom;
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(5, 51);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(453, 281);
			this->tabControl1->TabIndex = 5;
			this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::tabControl1_SelectedIndexChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->richTextBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 4);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(445, 255);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Network";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->splitContainer1);
			this->tabPage2->Location = System::Drawing::Point(4, 4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(445, 255);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Browser";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(3, 3);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->listView1);
			this->splitContainer1->Size = System::Drawing::Size(439, 249);
			this->splitContainer1->SplitterDistance = 145;
			this->splitContainer1->TabIndex = 0;
			// 
			// treeView1
			// 
			this->treeView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->treeView1->HideSelection = false;
			this->treeView1->ImageIndex = 0;
			this->treeView1->ImageList = this->imageList1;
			this->treeView1->Location = System::Drawing::Point(0, 0);
			this->treeView1->Name = L"treeView1";
			this->treeView1->SelectedImageIndex = 0;
			this->treeView1->Size = System::Drawing::Size(145, 249);
			this->treeView1->TabIndex = 0;
			this->treeView1->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &Form1::treeView1_BeforeSelect);
			this->treeView1->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &Form1::treeView1_NodeMouseClick);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"Folder.ico");
			this->imageList1->Images->SetKeyName(1, L"Doc.ico");
			this->imageList1->Images->SetKeyName(2, L"Private.ico");
			this->imageList1->Images->SetKeyName(3, L"Network.ico");
			this->imageList1->Images->SetKeyName(4, L"Rotate1.ico");
			this->imageList1->Images->SetKeyName(5, L"Rotate2.ico");
			this->imageList1->Images->SetKeyName(6, L"Rotate3.ico");
			this->imageList1->Images->SetKeyName(7, L"Rotate4.ico");
			this->imageList1->Images->SetKeyName(8, L"Rotate5.ico");
			this->imageList1->Images->SetKeyName(9, L"Rotate6.ico");
			this->imageList1->Images->SetKeyName(10, L"Rotate7.ico");
			this->imageList1->Images->SetKeyName(11, L"Rotate8.ico");
			this->imageList1->Images->SetKeyName(12, L".exe");
			this->imageList1->Images->SetKeyName(13, L".lab");
			this->imageList1->Images->SetKeyName(14, L".txt");
			this->imageList1->Images->SetKeyName(15, L".png");
			this->imageList1->Images->SetKeyName(16, L".bmp");
			this->imageList1->Images->SetKeyName(17, L".jpg");
			this->imageList1->Images->SetKeyName(18, L".log");
			this->imageList1->Images->SetKeyName(19, L".xml");
			this->imageList1->Images->SetKeyName(20, L".tmp");
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3
			});
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->Location = System::Drawing::Point(0, 0);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(290, 249);
			this->listView1->SmallImageList = this->imageList1;
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Name";
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Type";
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Last Modified";
			this->columnHeader3->Width = 98;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(461, 335);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Form1";
			this->Text = L"FindHost";
			this->TopMost = true;
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		private: Void button1_Click(Object ^ sender, EventArgs ^ e)
		{
			CheckHost::CheckingHost(textBox1->Text, richTextBox1, button1, timer1, progressBar1, tabControl1);

			textBox1->Focus();
		}

		private: Void textBox1_KeyDown(Object ^ sender, KeyEventArgs ^ e)
		{
			if (e->KeyCode == Keys::Enter)
			{
				CheckHost::CheckingHost(textBox1->Text, richTextBox1, button1, timer1, progressBar1, tabControl1);

				e->SuppressKeyPress = true;
			}
		}
	
		private: Void button1_KeyDown(Object ^ sender, KeyEventArgs ^ e)
		{
			if (e->KeyCode == Keys::Enter)
				CheckHost::CheckingHost(textBox1->Text, richTextBox1, button1, timer1, progressBar1, tabControl1);
		}
	
		private: Void textBox2_KeyDown(Object ^ sender, KeyEventArgs ^ e)
		{
			if (e->KeyCode == Keys::Enter)
				CheckHost::CheckingHost(textBox1->Text, richTextBox1, button1, timer1, progressBar1, tabControl1);
		}
		
		private: Void timer1_Tick(Object^  sender, EventArgs^  e)
		{
			correctTimerCount++;
		
			if (correctTimerCount == 5)
			{
				correctTimerCount = 0;
				if (progressBar1->Value < 100)
					progressBar1->Value += 1;
			}

			for (int i = 0; i < treeView1->Nodes->Count; i++)
			{
				ComponentChanges::LoopIconChanger(treeView1->Nodes[i]);
			}
		}
		
		private: Void tabControl1_SelectedIndexChanged(Object^  sender, EventArgs^  e)
		{
			if (tabControl1->SelectedIndex == 1 && richTextBox1->Text->Contains("Name:		"))
			{
				CheckDirectory::PopulateTreeView(treeView1, richTextBox1, progressBar1);
			}
		}
		
		private: Void treeView1_NodeMouseClick(Object^  sender, TreeNodeMouseClickEventArgs^  e)
		{
			if (!CheckFiles::threadRunning && CheckFiles::treeNode != treeView1->SelectedNode)
				CheckFiles::PopulateListView(treeView1, listView1, e->Node, imageList1);
		}

		private: System::Void treeView1_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) 
		{
			if (CheckFiles::threadRunning)
				e->Cancel = true;
		}
	};
}