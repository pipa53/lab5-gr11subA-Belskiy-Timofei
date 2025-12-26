#include <linux/module.h>    // Обязательно для всех модулей
#include <linux/kernel.h>    // Для KERN_INFO, printk
#include <linux/init.h>      // Для макросов __init и __exit
#include <linux/fs.h>        // Для работы с файловой системой
#include <linux/cdev.h>      // Для cdev
#include <linux/uaccess.h>   // Для copy_to_user и copy_from_user
#include <linux/slab.h>      // Для kmalloc/kfree

// Глобальные переменные
static dev_t dev_num;          // Major и minor номера устройства
static struct cdev my_cdev;    // Структура cdev
static char *buffer;           // Буфер для хранения данных (1024 байта)

// Функция открытия устройства
static int dev_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Функция закрытия устройства
static int dev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Функция чтения из устройства
static ssize_t dev_read(struct file *file, char __user *ubuf, size_t len, loff_t *off) {
    int bytes_to_read = min(len, strlen(buffer) - *off);

    if (*off >= strlen(buffer)) {
        return 0; // Конец файла
    }

    if (copy_to_user(ubuf, buffer + *off, bytes_to_read)) {
        return -EFAULT;
    }

    *off += bytes_to_read;
    return bytes_to_read;
}

// Функция записи в устройство
static ssize_t dev_write(struct file *file, const char __user *ubuf, size_t len, loff_t *off) {
    int bytes_to_write = min(len, (size_t)(1024 - *off));

    if (*off >= 1024) {
        return -ENOMEM; // Нет места в буфере
    }

    if (copy_from_user(buffer + *off, ubuf, bytes_to_write)) {
        return -EFAULT;
    }

    *off += bytes_to_write;
    buffer[*off] = '\0'; // Добавляем завершающий ноль
    return bytes_to_write;
}

// Операции устройства
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
};

// Функция инициализации модуля
static int __init chardev_init(void) {
    // Выделение major/minor номеров
    if (alloc_chrdev_region(&dev_num, 0, 1, "mychardev") < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        return -1;
    }
    printk(KERN_INFO "Major: %d, Minor: %d\n", MAJOR(dev_num), MINOR(dev_num));

    // Инициализация cdev
    cdev_init(&my_cdev, &fops);
    if (cdev_add(&my_cdev, dev_num, 1) < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    // Выделение памяти для буфера
    buffer = kmalloc(1024, GFP_KERNEL);
    if (!buffer) {
        printk(KERN_ERR "Failed to allocate buffer\n");
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }
    memset(buffer, 0, 1024);

    printk(KERN_INFO "Character device /dev/mychardev created\n");
    return 0;
}

// Функция выгрузки модуля
static void __exit chardev_exit(void) {
    // Освобождение ресурсов
    kfree(buffer);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Character device /dev/mychardev removed\n");
}

// Регистрация функций init/exit
module_init(chardev_init);
module_exit(chardev_exit);

// Метаданные модуля
MODULE_LICENSE("GPL"); // Лицензия (обязательно!)
MODULE_AUTHOR("Наркевич Алексей"); // Автор
MODULE_DESCRIPTION("Простое символьное устройство /dev/mychardev"); // Описание
MODULE_VERSION("1.0"); // Версия
