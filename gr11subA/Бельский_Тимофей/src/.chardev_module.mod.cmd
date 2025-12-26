savedcmd_chardev_module.mod := printf '%s\n'   chardev_module.o | awk '!x[$$0]++ { print("./"$$0) }' > chardev_module.mod
