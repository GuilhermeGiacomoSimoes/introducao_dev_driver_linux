#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/device.h>

#include "my_class.h" 

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("Classes de dispositivos");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static int __init class_init(void)
{
	device_class = (struct class *) kzalloc(sizeof(struct class), GFP_ATOMIC);
	if(!device_class) 
	  pr_err("ERRO NA ALOCACAO DA CLASSE");

	device_class->name = "7segment";
	class_register(device_class);

	pr_info("class registrada");

	return 0;
}

static void __exit class_exit(void)
{
	class_unregister(device_class);
	class_destroy(device_class);
	pr_info("Modulo removido");

}

module_init(class_init);
module_exit(class_exit);
