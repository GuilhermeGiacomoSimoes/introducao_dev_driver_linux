#ifndef __USB_DRIVER_H__
#define __USB_DRIVER_H__

#define USB_SKEL_VENDOR_ID "7SEG_DRIVER"
#define USB_SKEL_PRODUCT_ID 0x0001

static int skel_probe(struct usb_interface *intf, const struct usb_device_id *id);
static void skel_disconnect(struct usb_interface *intf);
static int skel_suspend(struct usb_interface *intf, pm_message_t message);
static int skel_resume(struct usb_interface *intf);
static int skel_pre_reset(struct usb_interface *intf);
static int skel_post_reset(struct usb_interface *intf);

/*
Para permitir que o sistema linux-hotplug carregue o driver automaticamente quando o
dispositivo for conectado, voce precisa criar um MODULE_DEVICE_TABLE. O codigo a seguir
informa aos scripts hotplug que este modulo oferece suporte a um unico dispositivo
com um fornecedor e ID de produto especificos:
 */
static struct usb_device_id skel_table[] = {
	{ USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) },
	{ }
};


/*
no usb_driver e obrigatorio fornecer o campo name, probe, disconnect e id_table. O resto 
e opcional.
Os metodos probe() e disconnect() sao chamados em um contexto onde podem suspender o device.
Mas nao abuse desse privilegio. A maior parte do trabalho de conexao a um device deve ser 
realizada quando o device for inicializado e desfeito no ultimo fechamento. O codigo de 
desconexao precisa resolver problemas de simultaneidade com relacao aos metodos open()
e close(), bem como forcar a conclusao de todas as solicitacoes de E/S pendentes.
 */
static struct usb_driver skel_driver = {
	/*a descricao do drive deve ser unica dentro dos drivers usb e normalmente
	e a mesma do nome do modulo*/
	.name = "skeleton",

	/*
	Chamado na inicializacao do driver para verificar se o driver esta disposto ou
	precisa gerenciar uma interface de algum dispositivo em particular. Por ex, no 
	nosso caso, usaremos esse cara para gerenciar um usb para controlar um display
	de 7segmentos, entao ele vai precisar gerenciar um dispositivo em particular.
	Se precisasse gerenciar um mouse, nao precisaria informar uma interface especifica.
	 */
	.probe = skel_probe,

	/*
	 Funcao chamada quando o dispositivo usb e desconectado ou o modulo e removido
	 */
	.disconnect = skel_disconnect,

	/*
	 Chamado quando o dispositivo será suspenso pelo sistema no contexto de suspensão 
	 do sistema ou de suspensão do tempo de execução.
	*/
	.suspend = skel_suspend,

	/*
	Chamado quando o dispositivo volta da suspensao do sistema operacional. 
	 */
	.resume = skel_resume,

	/*
	Chamado por usb_reset_device() quando o dispositivo esta prestes a ser reiniciado 
	 */
	.pre_reset = skel_pre_reset,

	/*
	Chamado por usb_reset_device() apos o dispositivo ser reiniciado
	 */
	.post_reset = skel_post_reset,

	/*
	 Os drivers USB usam uma tabela de ID para suportar hotplugging. Exporte esse id_table com 
	 MODULE_DEVICE_TABLE(). Se voce nao exportar sua funcao `probe` jamais sera chamada.
	 */
	.id_table = skel_table,

	/*
	Se for 0 o nucleo USB do kernel jamais permitira a suspensao automatica para 
	interfaces vinculadas a esse driver
	 */
	.supports_autosuspend = 1
};

#endif
