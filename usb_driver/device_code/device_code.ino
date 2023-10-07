#include "usbconfig.h"
#include <VUSB.h>

const int VENDOR_RQ_READ_BUFFER = 0;
const int VENDOR_RQ_WRITE_BUFFER = 1;

static uchar buffer[64];
static uchar currentPosition, bytesRemaining;

void printBuffer() 
{
	for(int i = 0 ; i < 64; i ++) 
		Serial.print(buffer[i]);

	Serial.println();
}

/*
Enquanto o host envia ou recebe mensagens de controle do enpoint 0,
no qual e enderecado o "fornecedor" ou "classe", a funcao usbFunctionSetup()
e chamada no seu codigo. Ele somente recebe um unico parametro: um ponteiro de 
8 bits para os dados de configuracoes. 
*/
usbMsgLen_t usbFunctionSetup(uchar data[8]) 
{
	usbRequest_t *rq = (void *) data;
	switch(rq->bRequest){
		case VENDOR_RQ_WRITE_BUFFER:
			currentPosition = 0;
			bytesRemaining = rq->wLength.word;
			if(bytesRemaining > sizeof(buffer))
				bytesRemaining = sizeof(buffer);

			return USB_NO_MSG;

		case VENDOR_RQ_READ_BUFFER:
			currentPosition = 0;
			bytesRemaining = rq->wLength.word;
			return USB_NO_MSG;
	}

	return 0;
}

uchar usbFunctionRead(uchar *data, uchar len)
{
	uchar i;
	if(len > bytesRemaining) 
		len = bytesRemaining;

	bytesRemaining -= len;

	//for(i = 0; i < len; i++)
	//	data[i] = getData(currentPosition);

	return len;
}

uchar usbFunctionWrite(uchar *data, uchar len) 
{
	uchar i;
	if(len > bytesRemaining)
		len = bytesRemaining;
	
	bytesRemaining -= len;

	for(i = 0; i < len; i++) 
		buffer[currentPosition++] = data[i];

	printBuffer();

	return bytesRemaining == 0;
}

void setup() 
{
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
}
