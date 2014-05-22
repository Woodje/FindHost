using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Net::NetworkInformation;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;

namespace Tools
{
	class ComponentChanges
	{
		public: static void LoopIconChanger(TreeNode ^ treeNode)
		{
			if (treeNode->ImageIndex >= 4 && treeNode->ImageIndex < 12)
			{
				treeNode->ImageIndex++;
				treeNode->SelectedImageIndex++;
			}
			if (treeNode->ImageIndex == 12)
			{
				treeNode->ImageIndex = 4;
				treeNode->SelectedImageIndex = 4;
			}

			for (int i = 0; i < treeNode->Nodes->Count; i++)
			{
				if (treeNode->Nodes[i]->ImageIndex >= 4 && treeNode->Nodes[i]->ImageIndex < 12)
				{
					treeNode->Nodes[i]->ImageIndex++;
					treeNode->Nodes[i]->SelectedImageIndex++;
				}
				if (treeNode->Nodes[i]->ImageIndex == 12)
				{
					treeNode->Nodes[i]->ImageIndex = 4;
					treeNode->Nodes[i]->SelectedImageIndex = 4;
				}
			}
		}

		public: static void progressBarValue(ProgressBar ^ progressBar, float value)
		{
			if (progressBar->InvokeRequired)
				progressBar->Invoke(gcnew Action<ProgressBar ^, float>(ComponentChanges::progressBarValue), progressBar, value);
			else
			if (progressBar->Value == 100 || value > progressBar->Value)
				progressBar->Value = value;
		}

		public: static void Output(RichTextBox ^ output, String ^ text, Color color)
		{
			// Check if an invoke is required.
			if (output->InvokeRequired)
			{
				// Do a delegate call by doing some recursion.
				output->Invoke(gcnew Action<RichTextBox ^, String ^, Color>(Output), output, text, color);
				return;
			}

			// Change the selection color.
			output->SelectionColor = color;

			// Append the text with the new selection color.
			output->AppendText(text);
		}

		public: static void buttonEnabledChange(Button ^ button, bool value)
		{
			if (button->InvokeRequired)
				button->Invoke(gcnew Action<Button ^, bool>(buttonEnabledChange), button, value);
			else
				button->Enabled = value;
		}

		public: static void tabControlSelectionChange(TabControl ^ tabControl, int value)
		{
					 if (tabControl->InvokeRequired)
						 tabControl->Invoke(gcnew Action<TabControl ^, int>(tabControlSelectionChange), tabControl, value);
					 else
						 tabControl->SelectedIndex = value;
		}

		public: static void TreeViewChangeToTreeNode(TreeView ^ treeView, TreeNode ^ targetTreeNode, TreeNode ^ value)
		{
			if (treeView->InvokeRequired)
				treeView->Invoke(gcnew Action<TreeView ^, TreeNode ^, TreeNode ^>(TreeViewChangeToTreeNode),treeView, targetTreeNode, value);
			else
				targetTreeNode->Nodes->Add(value);

		}

		public: static void TreeViewChange(TreeView ^ treeView, TreeNode ^ value)
		{
			if (treeView->InvokeRequired)
				treeView->Invoke(gcnew Action<TreeView ^, TreeNode ^>(TreeViewChange), treeView, value);
			else
				treeView->Nodes->Add(value);
		}
	
		public: static void TreeNodeImageChange(TreeView ^ treeView, TreeNode ^ targetTreeNode, int value)
		{
			if (treeView->InvokeRequired)
				treeView->Invoke(gcnew Action<TreeView ^, TreeNode ^, int>(TreeNodeImageChange), treeView, targetTreeNode, value);
			else
			{
				targetTreeNode->ImageIndex = value;
				targetTreeNode->SelectedImageIndex = value;
			}
		}

		public: static void ListViewItemsAdd(ListView ^ listView, ListViewItem ^ item)
		{
			if (listView->InvokeRequired)
				listView->Invoke(gcnew Action<ListView ^, ListViewItem ^>(ListViewItemsAdd), listView, item);
			else
				listView->Items->Add(item);
		}
	
		public: static void ListViewColumnsUpdate(ListView ^ listView)
		{
			if (listView->InvokeRequired)
				listView->Invoke(gcnew Action<ListView ^>(ListViewColumnsUpdate), listView);
			else
				listView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
		}

		public: static void ListViewBeginUpdate(ListView ^ listView)
		{
			if (listView->InvokeRequired)
				listView->Invoke(gcnew Action<ListView ^>(ListViewBeginUpdate), listView);
			else
				listView->BeginUpdate();
		}

		public: static void ListViewEndUpdate(ListView ^ listView)
		{
			if (listView->InvokeRequired)
				listView->Invoke(gcnew Action<ListView ^>(ListViewEndUpdate), listView);
			else
				listView->EndUpdate();
		}

		public: static void ImageListImageAdd(ListView ^ listView, ImageList ^ imageList, String ^ extensionString, Icon ^ icon)
		{
			if (listView->InvokeRequired)
				listView->Invoke(gcnew Action<ListView ^, ImageList ^, String ^, Icon ^>(ImageListImageAdd), listView, imageList, extensionString, icon);
			else
				imageList->Images->Add(extensionString, icon);
		}
	};

	ref class CheckHost
	{
		private: static String ^ input, ^ domainString;
		private: static RichTextBox ^ output;
		private: static Button ^ button;
		private: static ProgressBar ^ progressBar;
		private: static TabControl ^ tabControl;

		public: static void CheckingHost(String ^ input1, RichTextBox ^ output1, Button ^ button1, Timer ^ timer1, ProgressBar ^ progressBar1, TabControl ^ tabControl1)
		{
			// Gather different components.
			input = input1;
			output = output1;
			button = button1;
			progressBar = progressBar1;
			tabControl = tabControl1;

			// Instantiating AsyncDnsCallBack.
			AsyncCallback^ AsyncDnsCallback = gcnew AsyncCallback(ProcessDnsResults);

			// Do nothing if nothing has been typed.
			if (input == "")
				return;

			// Check if the "Go"-button is enabled.
			if (button1->Enabled)
			{
				try
				{
					// Go to the Network-tab.
					ComponentChanges::tabControlSelectionChange(tabControl, 0);

					// Start the timer for the progressbar.
					timer1->Start();

					// Restart the progressbar.
					ComponentChanges::progressBarValue(progressBar, 0);

					// Clear the output.
					output->Clear();

					// Disable the "Go"-button.
					ComponentChanges::buttonEnabledChange(button, false);

					// Start the request for info about the host, staring with no damain specified.
					domainString = "";
					Dns::BeginGetHostEntry(input, AsyncDnsCallback, nullptr);
				}
				catch (...)
				{
					// Bring the progress to the end.
					ComponentChanges::progressBarValue(progressBar, 100);

					// Output that the host is not resolved.
					ComponentChanges::Output(output, "Can't resolve\r\n  - ", Color::Blue);
					ComponentChanges::Output(output, input, Color::Red);

					// Enable the "Go"-button again.
					ComponentChanges::buttonEnabledChange(button, true);

					// Go to the Network-tab.
					ComponentChanges::tabControlSelectionChange(tabControl, 0);
				}
			}
		}

		private: static void ProcessDnsResults(IAsyncResult^ ar)
		{
			try
			{
				// Request info about host.
				IPHostEntry^ host = Dns::EndGetHostEntry(ar);

				// Output the recieved hostname.
				ComponentChanges::Output(output, "Name:		", Color::Blue);
				ComponentChanges::Output(output, host->HostName, Color::Navy);

				// Go through the recieved list of IP-Addresses.
				for (int i = 0; i < host->AddressList->Length; i++)
				{
					// Output the IPV4-Address.
					ComponentChanges::Output(output, "\r\nIP-Address:	", Color::Blue);
					ComponentChanges::Output(output, host->AddressList[i]->ToString(), Color::Navy);

					// Ping the host, and output the result.
					PingHost(host->AddressList[i]->ToString());

					// Update the progressbar.
					ComponentChanges::progressBarValue(progressBar, ((float)(1 + i) / (float)host->AddressList->Length) * 100);
				}

				// Enable the "Go"-button again.
				ComponentChanges::buttonEnabledChange(button, true);

				// Go to the Network-tab.
				ComponentChanges::tabControlSelectionChange(tabControl, 0);
			}
			catch (SocketException ^)
			{
				// Instantiating AsyncDnsCallBack.
				AsyncCallback^ AsyncDnsCallback = gcnew AsyncCallback(ProcessDnsResults);

				if (domainString == "")
				{
					// Start the request for info about the host from the emea-domain.
					domainString = ".domain1";
					Dns::BeginGetHostEntry(input + domainString, AsyncDnsCallback, nullptr);
				}
				else if (domainString == ".domain1")
				{
					// Start the request for info about the host from the emea-domain.
					domainString = ".domain2";
					Dns::BeginGetHostEntry(input + domainString, AsyncDnsCallback, nullptr);
				}
				else if (domainString == ".domain2")
				{
					// Start the request for info about the host from the emea-domain.
					domainString = ".domain3";
					Dns::BeginGetHostEntry(input + domainString, AsyncDnsCallback, nullptr);
				}
				else
				{
					// Bring the progress to the end.
					ComponentChanges::progressBarValue(progressBar, 100);

					// Output that the host is not resolved.
					ComponentChanges::Output(output, "Can't resolve\r\n  - ", Color::Blue);
					ComponentChanges::Output(output, input, Color::Red);

					// Enable the "Go"-button again.
					ComponentChanges::buttonEnabledChange(button, true);

					// Go to the Network-tab.
					ComponentChanges::tabControlSelectionChange(tabControl, 0);
				}
			}
		}

		private: static void PingHost(String ^ IPAddress)
		{
			// Declare and initialize a new instance of Ping.
			Ping ^ pingSender = gcnew Ping;

			// Ping the host.
			PingReply ^ reply = pingSender->Send(IPAddress);

			// Check if the ping was successful.
			if (reply->Status == IPStatus::Success)
			{
				// Output "Responding" if there was a reply on the ping.
				ComponentChanges::Output(output, "	  - Responding to ping!", Color::Green);
			}
			else
			{
				// Output "No response" if there was no reply on the ping.
				ComponentChanges::Output(output, "	  - No response to ping!", Color::Red);
			}
		}
	};

	ref class CheckDirectory
	{
		private: static bool doesNodeExist = false;
		private: static String ^ hostName;
		private: static RichTextBox ^ output;
		private: static ProgressBar ^ progressBar;
		private: static TreeView ^ treeView;
		private: static TreeNode ^ rootNode;
		private: static DirectoryInfo ^ info;

		public: static void PopulateTreeView(TreeView ^ treeView1, RichTextBox ^ output1, ProgressBar ^ progressBar1)
		{
			// Gather different components.
			treeView = treeView1;
			output = output1;
			progressBar = progressBar1;

			// Retrieve the host name of the remote computer.
			hostName = output->Lines[0]->ToString()->Remove(0, 7);

			// Check if the host already exists in the treeview.
			for (int i = 0; i < treeView->Nodes->Count; i++)
				if (treeView->Nodes[i]->Text == hostName)
					doesNodeExist = true;
			
			// Create a ThreadStart delegate which matches the function: "StartDirectoryInfoThread".
			Threading::Thread ^ DirectoryInfoThread = gcnew Threading::Thread(gcnew Threading::ThreadStart(CheckDirectory::StartDirectoryInfoThread));
			
			// Tell the thread to run in the background so that is stops when the main thread is stopped.
			DirectoryInfoThread->IsBackground = true;

			// Start the thread.
			DirectoryInfoThread->Start();
		}

		private: static void StartDirectoryInfoThread()
		{
			// Call the function that makes sure the we can connect to the host.
			ConnectWithCredentials(hostName);

			// Initialize the targets path.
			info = gcnew DirectoryInfo("\\\\" + hostName + "\\C$");

			// Check if the path exists and that no node with the same hostname already exists.
			if (info->Exists && !doesNodeExist)
			{
				// Create a ThreadStart delegate which matches the function: "GetDirectoriesThread".
				Threading::Thread ^ thread = gcnew Threading::Thread(gcnew Threading::ThreadStart(CheckDirectory::GetDirectoriesThread));

				// Tell the thread to run in the background so that is stops when the main thread is stopped.
				thread->IsBackground = true;

				// Start the thread.
				thread->Start();
			}
		}

		private: static void GetDirectoriesThread()
		{
			// Create a new treenode and name it with the hosts name and associate it with an icon (Rotate1.ico).
			rootNode = gcnew TreeNode(hostName, 4, 4);

			// Name the newly created treenodes tag with the full path.
			rootNode->Tag = info;

			// Add the currently connected location.
			rootNode->Nodes->Add(info->Name);

			// Give the newly added location a tag value.
			rootNode->Nodes[0]->Tag = info;
			
			// Set a key for the image that is displayed for the item.
			rootNode->Nodes[0]->ImageKey = "folder";

			// Add the structure of the targets directory.
			ComponentChanges::TreeViewChange(treeView, rootNode);

			// Call the function that runs through and adds the structure of the targets directory.
			GetDirectories(info->GetDirectories(), rootNode->Nodes[0]);
		}

		private: static void GetDirectories(array<DirectoryInfo^>^ subDirs, TreeNode ^ nodeToAddTo)
		{
			// Declare some variables.
			TreeNode ^ aNode;
			array<DirectoryInfo^>^ subSubDirs;

			// Associate a loading icon to the current directory which is being looked through (Rotate1.ico).
			ComponentChanges::TreeNodeImageChange(treeView, nodeToAddTo, 4);

			// Run through an array of folders.
			for (int i = 0; i < subDirs->Length; i++)
			{
				// Create a new treenode and name it with the folders name and associate it with an icon (Folder.ico).
				aNode = gcnew TreeNode(subDirs[i]->Name, 0, 0);
			
				// Name the newly created treenodes tag with the folders path.
				aNode->Tag = subDirs[i];

				// Set a key for the image that is displayed for the item.
				aNode->ImageKey = "folder";
				
				try
				{
					// Retrieve current folders structure.
					subSubDirs = subDirs[i]->GetDirectories();
												
					// Check if there are any more folders within the current folder.
					if (subSubDirs->Length != 0)
					{
						// Call the function that runs through and adds the structure of the targets directory.
						GetDirectories(subSubDirs, aNode);
					}
				}
				catch (...)
				{
					// Associate this node with an icon. (Private.ico)
					aNode->ImageIndex = 2;

					// Select an icon for when this node is selected (Private.ico).
					aNode->SelectedImageIndex = 2;
				}

				// Add the structure of the currently retrieved directory to the treeview.
				ComponentChanges::TreeViewChangeToTreeNode(treeView, nodeToAddTo, aNode);
			}
			
			// Bring the loading icon to a stop by using another icon (Folder.ico).
			ComponentChanges::TreeNodeImageChange(treeView, nodeToAddTo, 0);

			// Bring the loading icon to a stop by using another icon (Network.ico).
			if (nodeToAddTo->Parent != nullptr)
				for (int i = 0; i < treeView->Nodes->Count; i++)
					if (treeView->Nodes[i]->Text == nodeToAddTo->Parent->Text)
						ComponentChanges::TreeNodeImageChange(treeView, nodeToAddTo->Parent, 3);
		}

		private: static void ConnectWithCredentials(String ^ hostName)
		{
			// Prepare the variables.
			String ^ userName, ^ password, ^ domain = "";
			StreamReader ^ readConnections;
			ProcessStartInfo ^ networkConnection = gcnew ProcessStartInfo("cmd.exe");

			// Use the following command to retrieve the current connections and then output this to a file.
			networkConnection->Arguments = "/c net use > Connections.txt";
			
			// Make sure that this process runs while it is hidden.
			networkConnection->WindowStyle = ProcessWindowStyle::Hidden;

			// Start the process.
			Process ^ processNetworkConnection = Process::Start(networkConnection);
			
			// Wait for the process to finish before continuing.
			processNetworkConnection->WaitForExit();
			
			// Read the connections from the newly created file.
			readConnections = gcnew StreamReader("Connections.txt");

			// Check if a connection isn't already established.
			if (!readConnections->ReadToEnd()->Contains(hostName))
			{
				// Retrive the domain of the host.
				if (hostName->Contains("domain1") || hostName->Contains("DOMAIN1"))
					domain = "domain1\\";
				else if (hostName->Contains("domain1") || hostName->Contains("DOMAIN2"))
					domain = "domain2\\";
				else if (hostName->Contains("domain3") || hostName->Contains("DOMAIN3"))
					domain = "domain3\\";

				// Retrive what kind of username is to be used.
				if (hostName->Substring(0,6)->ToUpper()->StartsWith("USER"))
				{
					userName = "*" + hostName->Substring(hostName->IndexOf("*") + 1, 6);
					password = "*-*" + hostName->Substring(hostName->IndexOf("*") + 1, 6) + "+*";
				}
				else if (hostName->StartsWith("U") || hostName->StartsWith("u"))
				{
					userName = hostName->Substring(0, 7);
					password = hostName->Substring(0, 2)->ToUpper() + "+" + hostName->Substring(2, 5) + "+*";
				}
				else
					return;

				// Use the following command to establish a connection to the target using the earlier retrieved parameters.
				networkConnection->Arguments = "/c net use \\\\" + hostName + " " + password + " /user:" + domain + userName;

				// Start the process.
				Process ^ processNetworkConnection = Process::Start(networkConnection);

				// Wait for the process to finish before continuing.
				processNetworkConnection->WaitForExit();
			}
		}
	};

	ref class CheckFiles
	{
		public: static bool threadRunning = false;
		private: static ListView ^ listView;
		public: static TreeNode ^ treeNode;
		private: static ImageList ^ imageList;

		public: static void PopulateListView(TreeView ^ treeView, ListView ^ listView1, TreeNode ^ treeNode1, ImageList ^ imageList1)
		{
			// Gather different components.
			listView = listView1;
			treeNode = treeNode1;
			imageList = imageList1;
			
			// Clear the listview.
			listView->Items->Clear();

			// Check if one of the topnodes is selected, and if so then return.
			for (int i = 0; i < treeView->Nodes->Count; i++)
				if (treeView->Nodes[i]->Text == treeNode->Text)
					return;

			// Create a ThreadStart delegate which matches the function: "StartDirectoryInfoThread".
			Threading::Thread ^ thread = gcnew Threading::Thread(gcnew Threading::ThreadStart(CheckFiles::StartDirectoryInfoThread));

			// Tell the thread to run in the background so that is stops when the main thread is stopped.
			thread->IsBackground = true;

			// Start the thread.
			thread->Start();
		}

		private: static void StartDirectoryInfoThread()
		{
			// Announce that the thread is now running.
			threadRunning = true;

			// Declare some variables.
			array<ListViewItem::ListViewSubItem^>^ subItems;
			array<DirectoryInfo^>^ subFolders, ^ subSubFolders;
			array<FileInfo^>^ files, ^ extensionFiles;
			ListViewItem ^ item = nullptr;
			Icon ^ fileIcon;

			try
			{
				// Retrieve selected folders structure.
				subFolders = ((DirectoryInfo ^)treeNode->Tag)->GetDirectories();

				// Run through an array of folders.
				for (int i = 0; i < subFolders->Length; i++)
				{
					try
					{
						// Retrieve current folders structure.
						subFolders[i]->GetDirectories();

						// Create a new listviewitem and name it with the folders name and associate it with an icon (Folder.ico).
						item = gcnew ListViewItem(subFolders[i]->Name, 0);
					}
					catch (...)
					{
						// Create a new listviewitem and name it with the folders name and associate it with an icon (Private.ico).
						item = gcnew ListViewItem(subFolders[i]->Name, 2);
					}

					// Create an array of two new listviewsubitems.
					subItems = gcnew array<ListViewItem::ListViewSubItem^>
					{
						// Create two new listviewsubitems and call the first one "Directory"
						// and the second one is for when the item was last modified.
						gcnew ListViewItem::ListViewSubItem(item, "Directory"),
						gcnew ListViewItem::ListViewSubItem(item, subFolders[i]->LastAccessTime.ToString())
					};

					// Add the structure of the currently created subitems to the newly created item.
					item->SubItems->AddRange(subItems);

					// Add the newly created item to the listview.
					ComponentChanges::ListViewItemsAdd(listView, item);
				}

				// Update the columns width.
				ComponentChanges::ListViewColumnsUpdate(listView);

				// Retrieve selected folders files.
				files = ((DirectoryInfo ^)treeNode->Tag)->GetFiles();

				// Run through an array of files.
				for (int i = 0; i < files->Length; i++)
				{
					// Create a new listviewitem and name it with the files name.
					item = gcnew ListViewItem(files[i]->Name);

					// Check if the imagelist contains an icon for the files extension.
					if (imageList->Images->ContainsKey(files[i]->Extension))
					{
						// Associate the item with an icon called the files extension.
						item->ImageKey = files[i]->Extension;
					}
					else
					{
						// Initialize the path where we want to search for icons.
						DirectoryInfo ^ info = gcnew DirectoryInfo("C:\\");

						// Retrieve the folders files with the same extension as the targets files extension.
						extensionFiles = info->GetFiles("*" + files[i]->Extension);

						// Check if any files were found.
						if (extensionFiles->Length != 0)
						{
							// Retrive the icon from the first found file.
							fileIcon = Icon::ExtractAssociatedIcon(extensionFiles[0]->FullName);

							// Add the newly retrieved icon to the imagelist.
							ComponentChanges::ImageListImageAdd(listView, imageList, files[i]->Extension, fileIcon);

							// Associate the item with an icon called the files extension.
							item->ImageKey = files[i]->Extension;
						}
						else
						{
							// Retrieve the folders structure.
							subSubFolders = info->GetDirectories();

							// Run through an array of folders.
							for (int x = 0; x < subSubFolders->Length; x++)
							{	
								try
								{
									// Retrieve the folders files with the same extension as the targets files extension.
									extensionFiles = subSubFolders[x]->GetFiles("*" + files[i]->Extension, SearchOption::AllDirectories);

									// Check if any files were found.
									if (extensionFiles->Length != 0)
									{
										// Retrive the icon from the first found file.
										fileIcon = Icon::ExtractAssociatedIcon(extensionFiles[0]->FullName);

										// Add the newly retrieved icon to the imagelist.
										ComponentChanges::ImageListImageAdd(listView, imageList, files[i]->Extension, fileIcon);

										// Associate the item with an icon called the files extension.
										item->ImageKey = files[i]->Extension;

										// Break out the current loop because an icon was found.
										break;
									}
									else
										// Associate the item with an icon called "Doc.ico" from the imagelist.
										item->ImageKey = "Doc.ico";
								}
								catch (...)
								{
									// Associate the item with an icon called "Doc.ico" from the imagelist.
									item->ImageKey = "Doc.ico";
								}
							}
						}
					}

					// Create an array of two new listviewsubitems.
					subItems = gcnew array<ListViewItem::ListViewSubItem^>
					{
						// Create two new listviewsubitems and call the first one "File"
						// and the second one is for when the item was last modified.
						gcnew ListViewItem::ListViewSubItem(item, "File"),
						gcnew ListViewItem::ListViewSubItem(item, files[i]->LastAccessTime.ToString())
					};

					// Add the structure of the currently created subitems to the newly created item.
					item->SubItems->AddRange(subItems);

					// Add the newly created item to the listview.
					ComponentChanges::ListViewItemsAdd(listView, item);
				}

				// Update the columns width.
				ComponentChanges::ListViewColumnsUpdate(listView);
			}
			catch (...)
			{
				// Announce that the thread is not running..
				threadRunning = false;
			}

			// Announce that the thread is not running.
			threadRunning = false;
		}
	};
}