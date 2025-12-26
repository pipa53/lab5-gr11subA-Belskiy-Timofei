#include <linux/module.h>    // Обязательно для всех модулей
#include <linux/kernel.h>    // Для KERN_INFO, printk
#include <linux/init.h>      // Для макросов __init и __exit
#include <linux/proc_fs.h>   // Для работы с /proc
#include <linux/uaccess.h>   // Для copy_to_user
#include <linux/jiffies.h>   // Для jiffies

// Глобальные переменные
static struct proc_dir_entry *proc_file;
static unsigned long load_time; // Время загрузки модуля (в jiffies)
static int read_count = 0;      // Счетчик обращений к файлу

// Функция чтения из /proc/student_info
static ssize_t proc_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {
    char buf[256];
    int len;

    // Если уже читали (ppos > 0), завершаем
    if (*ppos > 0)
        return 0;

    // Увеличиваем счетчик только при первом чтении
    read_count++;

    // Формируем строку с информацией
    len = snprintf(buf, sizeof(buf),
                   "Name: Наркевич Алексей\n"
                   "Group: 11, Subgroup: A\n"
                   "Module loaded at: %lu jiffies\n"
                   "Read count: %d\n",
                   load_time, read_count);

    // Копируем данные в пользовательское пространство
    if (copy_to_user(ubuf, buf, len))
        return -EFAULT;

    *ppos = len; // Обновляем позицию чтения
    return len;  // Возвращаем количество прочитанных байт
}

// Определяем операции для файла /proc/student_info
static const struct proc_ops proc_fops = {
    .proc_read = proc_read,
};

// Функция инициализации модуля
static int __init proc_init(void) {
    // Запоминаем время загрузки модуля
    load_time = jiffies;

    // Создаем файл /proc/student_info
    proc_file = proc_create("student_info", 0444, NULL, &proc_fops);
    if (!proc_file) {
        printk(KERN_ERR "Error: Could not create /proc/student_info\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Module loaded: /proc/student_info created\n");
    return 0; // Успех
}

// Функция выгрузки модуля
static void __exit proc_exit(void) {
    // Удаляем файл /proc/student_info
    proc_remove(proc_file);
    printk(KERN_INFO "Module unloaded: /proc/student_info removed\n");
}

// Регистрация функций init/exit
module_init(proc_init);
module_exit(proc_exit);

// Метаданные модуля
MODULE_LICENSE("GPL"); // Лицензия (обязательно!)
MODULE_AUTHOR("Наркевич Алексей"); // Автор
MODULE_DESCRIPTION("Модуль для создания файла /proc/student_info"); // Описание
MODULE_VERSION("1.0"); // Версия
