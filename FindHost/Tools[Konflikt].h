#include "ColorOutput.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Net::NetworkInformation;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace Tools
{
	class CheckHost
	{
		public: static void CheckingHost(String ^ input, RichTextBox ^ output, Button ^ button1, List<String^> ^ colorTextList, List<String^> ^ colorList)
		{
			// Do nothing if nothing has been typed.
			if (input == "")
				return;
			
			// Check if the "Go"-button is enabled.
			if (button1->Enabled)
			{
				try
				{
					// Disable the "Go"-button.
					button1->Enabled = false;

					// Empty the colorTextList.
					colorTextList->Clear();

					// Empty the colorList.
					colorList->Clear();

					// Start the request for info about the host.
					GetHostEntry(input, output, "", colorTextList, colorList);
				}
				catch (...)
				{
					// Output that the host is not resolved.
					output->Text = L"Can't resolve\r\n  - " + ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, input, "Red");
				}

				// Update the layout for the output.
				ColorOutput::ColorText::UpdateOutput(input, output, colorTextList, colorList);


				// Enable the "Go"-button again.
				button1->Enabled = true;
			}
		}

		private: static void GetHostEntry(String ^ input, RichTextBox ^ output, String ^ domainString, List<String^> ^ colorTextList, List<String^> ^ colorList)
		{
			try
			{
				// Request info about host.
				IPHostEntry^ host = Dns::GetHostEntry(input + domainString);

				// Output the recieved hostname.
				output->Text = "Name:		" + ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, host->HostName, "Navy");
					
				// Go through the recieved list of IP-Addresses.
				for (int i = 0; i < host->AddressList->Length; i++)
				{
					// Output the IPV4-Address.
					output->Text += "\r\nIP-Address:	" + ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, host->AddressList[i]->ToString() + " ", "Navy");

					// Ping the host, and output the result.
					PingHost(host->AddressList[i]->ToString(), output, colorTextList, colorList);
				}
			}
			catch (SocketException ^ e)
			{
				if (domainString == "")
				{
					// Start the request for info about the host from the emea-domain.
					GetHostEntry(input, output, ".emea", colorTextList, colorList);
				}
				else if (domainString == ".emea")
				{
					// Start the request for info about the host from the emea-domain.
					GetHostEntry(input, output, ".america", colorTextList, colorList);
				}
				else if (domainString == ".america")
				{
					// Start the request for info about the host from the emea-domain.
					GetHostEntry(input, output, ".asia", colorTextList, colorList);
				}
				else
					// Output that the host is not resolved.
					output->Text = L"Can't resolve\r\n  - " + ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, input, "Red");
			}
		}

		private: static void PingHost(String ^ input, RichTextBox ^ output, List<String^> ^ colorTextList, List<String^> ^ colorList)
		{
			// Declare and initialize a new instance of Ping.
			Ping ^ pingSender = gcnew Ping;

			// Ping the host.
			PingReply ^ reply = pingSender->Send(input);

			// Check if the ping was successful.
			if (reply->Status == IPStatus::Success)
			{
				// Output "Responding" if there was a reply on the ping.
				output->Text += ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, " - Responding to ping!", "Green");
			}
			else
			{
				// Output "No response" if there was no reply on the ping.
				output->Text += ColorOutput::ColorText::AddToColoringList(colorTextList, colorList, "	  - No response to ping!", "Red");
			}
		}
	};
}