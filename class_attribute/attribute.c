#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/device.h>

#include "attribute.h" 

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("Classes de dispositivos");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static ssize_t show_value(const struct class *class, 
		const struct class_attribute *attr, char* buf) 
{
	pr_info("valor do display %s - LEITURA", value_display);
	return sprintf(buf, "%d", value_display);
}

static ssize_t store_value(const struct class *class, 
		const struct class_attribute *attr, const char* buf, size_t count) 
{
	sscanf(buf, "%d", &value_display);
	pr_info("valor do display %d - ESCRITA", value_display);
	return count;
}

static int __init class_init(void)
{
	device_class = (struct class *) kzalloc(sizeof(struct class), GFP_ATOMIC);
	if(!device_class) 
	  pr_err("ERRO NA ALOCACAO DA CLASSE");

	device_class->name = "7segment";
	class_register(device_class);

	attr = (struct class_attribute *) kzalloc(sizeof(struct class_attribute), GFP_ATOMIC);
    attr->show = show_value;
    attr->store = store_value;
    attr->attr.name = "value";
    attr->attr.mode = 0777;
    class_create_file(device_class, attr);

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
