#ifndef __7SEGMENT_H__
#define __7SEGMENT_H__

static struct class *device_class = NULL;
static struct class_attribute *attr = NULL;

static ssize_t show_value(struct class *class, 
		struct class_attribute *attr, char* buf);

static ssize_t store_value(struct class *class, 
		struct class_attribute *attr, const char* buf, size_t count);

volatile int value_display;

static struct of_device_id driver_ids[] = {
	{.compatible = "ggs-prd,7segment"},
	{}
};

static int gpio_init_probe(struct platform_device *pdev);
static int gpio_exit_remove(struct platform_device *pdev);

static struct platform_driver display_driver = {
	.probe = gpio_init_probe,
	.remove = gpio_exit_remove,
	.driver = { 
		.name = "display_driver",
		.owner = THIS_MODULE,
		.of_match_table = driver_ids,
	}
};

struct gpio_desc *a, *b, *c, *d,
	*e, *f, *g, *dp;

#endif 
