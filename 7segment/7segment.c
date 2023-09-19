#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/of_device.h>
#include <linux/gpio/consumer.h>

#include "7segment.h" 

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("7segment");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static int gpio_init_probe(struct platform_device *pdev) 
{
	pr_info("Driver inicializado");
	a = devm_gpiod_get(&pdev->dev, "a", GPIOD_OUT_LOW);
	b = devm_gpiod_get(&pdev->dev, "b", GPIOD_OUT_LOW);
	c = devm_gpiod_get(&pdev->dev, "c", GPIOD_OUT_LOW);
	d = devm_gpiod_get(&pdev->dev, "d", GPIOD_OUT_LOW);
	e = devm_gpiod_get(&pdev->dev, "e", GPIOD_OUT_LOW);
	f = devm_gpiod_get(&pdev->dev, "f", GPIOD_OUT_LOW);
	g = devm_gpiod_get(&pdev->dev, "g", GPIOD_OUT_LOW);

	return 0;
}

static int gpio_exit_remove(struct platform_device *pdev) 
{
	pr_info("Driver inicializado");
	return 0;
}

static ssize_t show_value(struct class *class, 
		struct class_attribute *attr, char* buf)
{
	pr_info("valor do display %s - LEITURA", value_display);
	return sprintf(buf, "%d", value_display);
}

static ssize_t store_value(struct class *class, 
		struct class_attribute *attr, const char* buf, size_t count)
{
	sscanf(buf, "%d", &value_display);
	pr_info("valor do display %d - ESCRITA", value_display);

	if(value_display == 0) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 1);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 0);
	}
	else if(value_display == 1) {
		gpiod_set_value(a, 0);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 0);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 0);                 
		gpiod_set_value(g, 0);
	}
	else if(value_display == 2) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 0);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 1);                 
		gpiod_set_value(f, 0);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 3) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 0);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 4) {
		gpiod_set_value(a, 0);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 0);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 5) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 0);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 6) {
		gpiod_set_value(a, 0);                 
		gpiod_set_value(b, 0);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 1);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 7) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 0);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 0);                 
		gpiod_set_value(g, 0);
	}

	else if(value_display == 8) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 1);      
		gpiod_set_value(e, 1);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 1);
	}
	else if(value_display == 9) {
		gpiod_set_value(a, 1);                 
		gpiod_set_value(b, 1);                
		gpiod_set_value(c, 1);                 
		gpiod_set_value(d, 0);      
		gpiod_set_value(e, 0);                 
		gpiod_set_value(f, 1);                 
		gpiod_set_value(g, 1);
	}
	else {
		gpiod_set_value(a, 1);
		gpiod_set_value(b, 0);
		gpiod_set_value(c, 0);
		gpiod_set_value(d, 1);
		gpiod_set_value(e, 1);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
	}

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

	if(platform_driver_register(&display_driver)) {
		pr_err("ERRO! nao foi possivel carregar o driver");
		return -1;
	}


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
