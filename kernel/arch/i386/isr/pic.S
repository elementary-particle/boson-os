.section .text

.global pic_setup
.type pic_setup, @function
pic_setup:
	out 0x20, 0x11
.size pic_setup, . - pic_setup
