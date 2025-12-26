#include <linux/module.h>    // Обязательно для всех модулей
#include <linux/kernel.h>    // Для KERN_INFO, printk
#include <linux/init.h>      // Для макросов __init и __exit
#include <linux/moduleparam.h> // Для параметров модуля

// Параметр по умолчанию
static char *message = "default";
module_param(message, charp, 0644); // Регистрация параметра
MODULE_PARM_DESC(message, "Custom message to display");

// Функция инициализации (вызывается при insmod)
static int __init hello_init(void) {
    if (!message) { // Проверка на NULL
        printk(KERN_ERR "Error: Invalid or missing message parameter.\n");
        return -EINVAL; // Возвращаем ошибку
    }

    if (strcmp(message, "default") == 0) {
        printk(KERN_INFO "Hello from [Наркевич Алексей] module!\n");
    } else {
        printk(KERN_INFO "%s\n", message);
    }
    return 0; // 0 = успех
}

// Функция выгрузки (вызывается при rmmod)
static void __exit hello_exit(void) {
    if (!message) { // Проверка на NULL
        printk(KERN_ERR "Error: Invalid or missing message parameter during exit.\n");
        return;
    }

    if (strcmp(message, "default") == 0) {
        printk(KERN_INFO "Goodbye from [Наркевич Алексей] module!\n");
    } else {
        printk(KERN_INFO "Module unloaded with message: %s\n", message);
    }
}

// Регистрация функций init/exit
module_init(hello_init);
module_exit(hello_exit);

// Метаданные модуля
MODULE_LICENSE("GPL"); // Лицензия (обязательно!)
MODULE_AUTHOR("Наркевич Алексей"); // Автор
MODULE_DESCRIPTION("Простой Hello World модуль с параметром"); // Описание
MODULE_VERSION("1.0"); // Версия
