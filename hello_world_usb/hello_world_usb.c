#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define USB_VENDOR_ID 0x2341
#define USB_PRODUCT_ID 0x0043

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("Introducao a criacao de driver pra linux");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static struct usb_device_id hello_world_usb_table[] = {
	{ USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
	{ }
};
MODULE_DEVICE_TABLE(usb, hello_world_usb_table);

static int hello_world_usb_probe(struct usb_interface *intf, 
		const struct usb_device_id *id) 
{
	pr_info("Dispositivo %s foi conectado", USB_PRODUCT_ID);
	return 0;
}

static void hello_world_usb_disconnect(struct usb_interface *intf)
{
	pr_info("Dispositivo desconectado");
}

static struct usb_driver hello_world_usb = {
	.name = "hello world usb",
	.probe = hello_world_usb_probe,
	.disconnect = hello_world_usb_disconnect,
	.id_table = hello_world_usb_table,
};

static int __init hello_world_init(void)
{
	int result = usb_register(&hello_world_usb);
	if(result) {
		pr_err("usb_register falhou para o driver %s. Erro numero %s"
				, hello_world_usb.name, result);
		return -1;
	}

	return 0;
}

static void __exit hello_world_exit(void)
{
	usb_deregister(&hello_world_usb);
	pr_info("Adeus mundo cruel\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
