#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

static struct class *device_class = NULL;
static struct class_attribute *attr = NULL;

static ssize_t show_value(const struct class *class, 
		const struct class_attribute *attr, char* buf);

static ssize_t store_value(const struct class *class, 
		const struct class_attribute *attr, const char* buf, size_t count);

volatile int value_display;

#endif 
