#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xef0eea15, "module_layout" },
	{ 0x996327c5, "register_console" },
	{ 0x3302b500, "copy_from_user" },
	{ 0xea147363, "printk" },
	{ 0xfbe951b, "unregister_console" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

