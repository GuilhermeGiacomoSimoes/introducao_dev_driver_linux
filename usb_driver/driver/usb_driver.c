#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "usb_driver.h"

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("Introducao a criacao de driver pra linux");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_DEVICE_TABLE(usb, skel_table);

/*
Quando um dispositivo e conectado ao barramento USB que corresponde
ao padrao de ID de dispositivo que seu driver registou no nucleo USB, 
a funcao probe() e chamada. A struct usb_device, o numero da interface
e o ID da interface sao passados para a funcao como parametro
*/
static int skel_probe(struct usb_interface *intf, 
		const struct usb_device_id *id) 
{
	pr_info("o usb 7segmento foi conectado");
	return 0;
}

static void skel_disconnect(struct usb_interface *intf)
{  
	pr_info("o usb 7segmento foi desconectado");
}

static int __init usb_skel_init(void)
{
	//registrando este driver com subsistema USB
	int result = usb_register(&skel_driver);
	if(result < 0) {
		pr_err("usb_register falhou para o driver %s. Erro numero %s"
				, skel_driver.name, result);
		return -1;
	}

	return 0;
}

static void __exit usb_skel_exit(void)
{
	usb_deregister(&skel_driver);
	pr_info("Modulo removido\n");
}

module_init(usb_skel_init);
module_exit(usb_skel_exit);
