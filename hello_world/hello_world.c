#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("SEU NOME <seu_email@email.com>");
MODULE_DESCRIPTION("Introducao a criacao de driver pra linux");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static int __init hello_world_init(void)
{
 pr_info("Hello World\n");
 return 0;  /* successo */
}

static void __exit hello_world_exit(void)
{
 pr_info("Adeus mundo cruel\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
