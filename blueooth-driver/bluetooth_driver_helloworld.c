#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <acpi/acpi_bus.h>
#include <acpi/acpi_drivers.h>

MODULE_AUTHOR("GUILHERME <trintaeoitogc@gmail.com>");
MODULE_DESCRIPTION("Introducao a criacao de driver bluetooth");
MODULE_LICENSE("GPL");

static const struct acpi_device_id bt_device_id[] = {
	{"", ""},
};
MODULE_DEVICE_TABLE(acpi, bt_device_id);

static int hello_world_bluetooth_add(struct acpi_device *device)
{
	return 0;
}

static int hello_world_bluetooth_remove(struct acpi_device *device)
{
	pr_info("goodbye bluetooth driver");
	return 0;
}

static struct acpi_driver hello_world_bluetooth_acpi = {
	.name = "Hello World ACPI bluetooth",
	.class = "HelloWorld",
	.ids = bt_device_id,
	.ops = {
		.add = hello_world_bluetooth_add,
		.remove = hello_world_bluetooth_remove,
	},
	.owner = THIS_MODULE,
}

static int __init hello_world_bluetooth_init(void)
{
	int result = result = acpi_bus_register_driver(&hello_world_bluetooth_acpi);
	if(result < 0) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR, "error registering driver\n"));
		pr_err("error when register driver: %s", result);
		return -ENODEV;
	}

	return 0;
}

static void __exit hello_world_bluetooth_exit(void)
{
	pr_info("goodbye bluetooth driver");
	acpi_bus_unregister_driver(&hello_world_bluetooth_acpi);
}

module_init(hello_world_bluetooth_init);
module_exit(hello_world_bluetooth_exit);
