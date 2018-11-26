MODULE_NAME = benis

obj-m += $(MODULE_NAME).o

EXTRA_CFLAGS += -Werror
