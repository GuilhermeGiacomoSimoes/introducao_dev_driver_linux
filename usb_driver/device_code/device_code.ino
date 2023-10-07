#include "conf_usb.h"
#include <VUSB.h>

const int negative = 7;
const int positive = 6;
unsigned int stateSended = 0; 

static uchar buffer[64];

usbMsgLen_t usbFunctionSetup(uchar data[8]) 
{
	usbRequest_t *rq = (void *) data;
	switch(rq->bRequest){
		case VENDOR_RQ_READ_BUFFER:
			usbMsgLen_t len = 64;

			if(len > eq->wLength.word) 
				len = rq->wLength.word;

			usbMsgPtr = buffer;
			return len;

		case 1:
			Serial.println(rq->wValue.bytes[0]);
			return 0;
	}

	return 0;
}

void setup() 
{
  	pinMode(negative, INPUT);
  	pinMode(positive, INPUT);

	/*
	Isso impõe a (re)enumeração do dispositivo. 
	Em teoria, você não precisa disso, mas evita 
	inconsistências entre o host e o dispositivo 
	após redefinições de hardware
	*/
  	usbDeviceDisconnect();
  	delay(100);
  	usbDeviceConnect();

	usbInit();
}

void loop() 
{
	/*
	Em algum lugar durante o loop principal usbPoll() 
	deve ser chamado para executar tarefas administrativas 
	no driver
	*/
	usbPoll();

  	const int stateReceived = digitalRead(negative);

  	Serial.print("\n");
  	Serial.print("positive: ");
  	Serial.print(stateSended);
  	Serial.print("negative: ");
  	Serial.print(stateReceived);
  	Serial.print("\n");

  	stateSended -= 1;
}
