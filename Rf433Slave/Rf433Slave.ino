#include <VirtualWire.h>
#include <RFWirelessReceiver.h>
#include <RFWirelessTransmitter.h>
RFWirelessReceiver rfWirelessReceiver(11, 13, 500);
RFWirelessTransmitter rFWirelessTransmitter(12, 50, 500);

float dataValue[6] = { 13.45,12.56,14.80,11.50,13.67,12.89 };

char* responseDataId[6] = { "B0","B1","B2","B3","B4","B5" };

char* thisDeviceName = "BY";

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

bool checkDataIdValue(char* value)
{
	for (int i = 0; i < (sizeof(responseDataId) / sizeof(responseDataId[0])); i++)
	{
		//Serial.println(a[i]);
		if (responseDataId[i] == value) { return true; }
	}
	return false;
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
			char* valueToFind;
			rfWirelessReceiver.GetSensorID().toCharArray(valueToFind, rfWirelessReceiver.GetSensorID().length());
			if (data != "" && rfWirelessReceiver.GetDeviceId() == thisDeviceName && checkDataIdValue(valueToFind))
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
	rFWirelessTransmitter.startTrasmission("B0", "XX", 1);
	float data = 15.00;
	/*while (data < 0.50)
	{
		data = data + 0.05;*/

		rFWirelessTransmitter.sendBufferData("B0", "X", "XX", data, "0", "0");
	//}
	rFWirelessTransmitter.endTrasmission("B0", "XX");
}

