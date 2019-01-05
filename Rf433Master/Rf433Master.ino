#include <VirtualWire.h>
#include <RFWirelessTransmitter.h>
#include <RFWirelessReceiver.h>
RFWirelessReceiver rfWirelessReceiver(11, 13, 500);
RFWirelessTransmitter rFWirelessTransmitter(12, 50, 500);

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	rfWirelessReceiver.begin();
	rFWirelessTransmitter.begin();
	/* add setup code here */
}
void loop()
{
	sendMessageToSlave();
	//delay(5000);
	for (int i = 0; i < 50; i++)
	{
		if (checkIfGotAMessageFromSlave()) return;
	}
}
void sendMessageToSlave()
{
	rFWirelessTransmitter.startTrasmission("S1", "TD", 10);
	float data = 0.00;
	while (data < 0.50)
	{
		data = data + 0.05;

		rFWirelessTransmitter.SendBufferData("S1", "T", "TD", data, "0", "0");
	}
	rFWirelessTransmitter.endTrasmission("S1", "TD");
}
bool checkIfGotAMessageFromSlave()
{
	bool response = false;
	String data = "";
	//data = rfWirelessReceiver.GetMessage("BI","A0");
	data = rfWirelessReceiver.GetMessage();
	if (data == "init device transmission")
	{
		do {
			data = rfWirelessReceiver.GetMessage();
			if (data != "" && rfWirelessReceiver.GetDeviceId() == "S1")
			{
				//Program Business Logic : Insert here your logic
				Serial.println(data);
				if (data == "OK")
				{
					digitalWrite(13, HIGH);
					delay(500);
					digitalWrite(13, LOW);
					response = true;
				}
			}
		} while (data != "OK" && data != "KO");
	}
	return response;
}
