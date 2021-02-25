#include <VirtualWire.h>
#include "RFWirelessReceiver.h"
RFWirelessReceiver rfWirelessReceiver(11, 50, 500);

float dataValue[6] = { 13.45,12.56,14.80,11.50,13.67,12.89 };
char* responseDataId[6] = { "B0","B1","B2","B3","B4","B5" };
char* thisDeviceName = "BY";
unsigned long timer;

//bool checkDataIdValue(char value[2])
//{
//	Serial.println(value);
//	for (int i = 0; i < (sizeof(responseDataId) / sizeof(responseDataId[0])); i++)
//	{
//		Serial.print("..."); Serial.println(responseDataId[i]);
//		if (responseDataId[i] == value) { 
//			Serial.println("Esco");
//			return true; }
//	}
//	return false;
//}

bool checkArrivedMessageFromMaster()
{
	bool result = false;
	String data = "";
	data = rfWirelessReceiver.GetMessage();

	if (data == "init device transmission")
	{
		Serial.println(data);
		do {
			data = rfWirelessReceiver.GetMessage();

			if (data != "")
			{
				/*Serial.println(data);
				Serial.println(rfWirelessReceiver.GetSensorID());*/
			}
			//char* valueToFind;
			//rfWirelessReceiver.GetSensorID().toCharArray(valueToFind, rfWirelessReceiver.GetSensorID().length());
			/*if (data != "" && rfWirelessReceiver.GetDeviceId() == thisDeviceName && checkDataIdValue(valueToFind))
			{
				Serial.println("Entro qui!");*/
				//Program Business Logic : Insert here your logic
				/*Serial.println(data);*/
				if (data == "OK")
				{
					//Serial.println("E' tutto ok!!!!!");
					digitalWrite(13, HIGH);
					delay(500);
					digitalWrite(13, LOW);
					result = true;
				}
			//}
		} while (data != "OK" && data != "KO");
	}
	return result;
}

bool checkArrivedSimpeMessage()
{
	bool result = false;
	String data = "";
	data = rfWirelessReceiver.GetMessage();
	delay(100);
	if (data == "OK")
	{
		Serial.println(data);
		result = true;
	}
	return result;
}

void setup()
{
	Serial.begin(9600);
	pinMode(13, OUTPUT);
	rfWirelessReceiver.begin();
	Serial.println("Begin receveing");
	timer = millis();
}

void loop()
{
	//rfWirelessReceiver.GetSimpleMessage();
	if (rfWirelessReceiver.GetSimpleMessage() == "OK")
	{
		timer = millis();
		Serial.println("resetto");
	}
	if (millis() - timer > 10000)
	{
		while (true)
		{
			alarm();
			digitalWrite(13, LOW);
			delay(1000);
			digitalWrite(13, HIGH);
			delay(1000);
		}
	}
	//checkArrivedMessageFromMaster();
}


void alarm()
{
	tone(7, 400, 500);
	delay(1000);
	noTone(7);
}





