#include <VirtualWire.h>
#include <RFWirelessTransmitter.h>

RFWirelessTransmitter rFWirelessTransmitter(12, 50, 50);

char* slaveDeviceId[1] = { "BY" };
char* requestDataId[6] = { "B0","B1","B2","B3","B4","B5" };
bool  status[6] = { false,false,false,false,false,false };

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	rFWirelessTransmitter.begin();
}

void loop()
{
	trasmitMessageToSlave(slaveDeviceId[0], requestDataId[0]);
	//delay(1000);
}
void trasmitMessageToSlave(char* deviceId, char* dataId)
{
	rFWirelessTransmitter.startTrasmission(deviceId, dataId, 1);
	float data = 0.00;
	/*while (data < 0.10)
	{
		data = data + 0.05;*/
	rFWirelessTransmitter.sendBufferData(deviceId, dataId, "X", data, "0", "0");
	//}
	rFWirelessTransmitter.endTrasmission(deviceId, dataId);
}