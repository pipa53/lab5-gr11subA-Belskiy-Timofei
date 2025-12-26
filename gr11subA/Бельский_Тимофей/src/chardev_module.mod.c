#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xba3889c7, "cdev_init" },
	{ 0xa7e2fa48, "cdev_add" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0xcbaa3a2c, "kmalloc_caches" },
	{ 0xfb794c10, "__kmalloc_cache_noprof" },
	{ 0xa855cd46, "cdev_del" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x43a349ca, "strlen" },
	{ 0xd268ca91, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x092a35a2,
	0x9f222e1e,
	0xba3889c7,
	0xa7e2fa48,
	0x0bc5fb0d,
	0xbd03ed67,
	0xcbaa3a2c,
	0xfb794c10,
	0xa855cd46,
	0xcb8b6ec6,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xa61fd7aa,
	0x092a35a2,
	0x43a349ca,
	0xd268ca91,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"_copy_to_user\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"unregister_chrdev_region\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"cdev_del\0"
	"kfree\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"strlen\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1D0F6B0FF326354578D0747");
