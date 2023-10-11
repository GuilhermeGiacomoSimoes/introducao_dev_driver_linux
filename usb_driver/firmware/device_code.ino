#include <VUSB.h>

const int VENDOR_RQ_READ_BUFFER = 0;
const int VENDOR_RQ_WRITE_BUFFER = 1;

static uchar buffer[64];
static uchar currentPosition, bytesRemaining;
static uint8_t angle;

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
	static uchar replyBuffer[8];
	uchar replyLength;

	replyBuffer[0] = 0;
    switch (data[1]) {
    	case 0:            
    	    replyBuffer[0] = data[2];
    	    replyBuffer[1] = data[3];
    	    replyLength = 2;
    	    break;
    	case 1:             
    	    replyBuffer[0] = angle;
    	    replyLength = 1;
    	    break;
    	case 2:            
    	    angle = data[2];
    	    replyLength = 0;
    	    break;
    	default:                
    	    replyBuffer[0] = 1;
    	    replyLength = 1;
    	    break;
    }
    usbMsgPtr = replyBuffer;
    return replyLength;

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
	if(len > bytesRemaining)
		len = bytesRemaining;
	
	bytesRemaining -= len;

	for(int i = 0; i < len; i++) 
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
