#include <VirtualWire.h>
#include <RFWirelessReceiver.h>
#include <RFWirelessTransmitter.h>
RFWirelessReceiver rfWirelessReceiver(11, 13, 500);
RFWirelessTransmitter rFWirelessTransmitter(12, 50, 500);

void setup()
{
	Serial.begin(9600);
	pinMode(13, OUTPUT);
	rfWirelessReceiver.begin();
	rFWirelessTransmitter.begin();
	Serial.println("Begin receveing");
}
void loop()
{
	if (checkArrivedMessageFromMaster())
	{
		sendDataToMaster();
	}
}
bool checkArrivedMessageFromMaster()
{
	bool result = false;
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
					result = true;
				}
			}
		} while (data != "OK" && data != "KO");
	}
	return result;
}
void sendDataToMaster()
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

