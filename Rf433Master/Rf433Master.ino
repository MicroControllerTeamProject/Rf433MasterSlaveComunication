#include <VirtualWire.h>
#include <RFWirelessTransmitter.h>
#include <RFWirelessReceiver.h>

RFWirelessReceiver rfWirelessReceiver(11, 13, 500);
RFWirelessTransmitter rFWirelessTransmitter(12, 50, 500);

char* devicesID[6] = { "B0","B1","B2","B3","B4","B5"};
bool  status[6] = { false,false,false,false,false,false };

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	rfWirelessReceiver.begin();
	rFWirelessTransmitter.begin();
	/* add setup code here */
}
uint8_t ciclo = 0;

void loop()
{
	if(status[ciclo])
	{
		if (ciclo == 6) 
		{ 
			ciclo = 0; 
		}
		ciclo++;
	}
	trasmitMessageToSlave();
	//wait for receve data from slave
	for (int i = 0; i < 50; i++)
	{
		if (receiveMessageFromSlave()) return;
	}
}
void trasmitMessageToSlave()
{
	rFWirelessTransmitter.startTrasmission(devicesID[ciclo], "XX", 1);
	float data = 0.00;
	/*while (data < 0.10)
	{
		data = data + 0.05;*/
		rFWirelessTransmitter.SendBufferData(devicesID[ciclo], "XX", "X",  data, "0", "0");
	//}
	rFWirelessTransmitter.endTrasmission(devicesID[ciclo], "XX");
}
bool receiveMessageFromSlave()
{
	bool response = false;
	String data = "";
	//data = rfWirelessReceiver.GetMessage("BI","A0");
	data = rfWirelessReceiver.GetMessage();
	if (data == "init device transmission")
	{
		do {
			data = rfWirelessReceiver.GetMessage();
			if (data != "" && rfWirelessReceiver.GetDeviceId() == devicesID[ciclo])
			{
				//Program Business Logic : Insert here your logic
				Serial.println(data);
				if (data == "OK")
				{
					digitalWrite(13, HIGH);
					delay(500);
					digitalWrite(13, LOW);
					response = true;
					status[ciclo] = true;
				}
			}
		} while (data != "OK" && data != "KO");
	}
	return response;
}
