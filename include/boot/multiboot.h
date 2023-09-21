#ifndef __MULTIBOOT_H
#define __MULTIBOOT_H

#include "../types.h"


/* The full documentation of Multiboot specifications is at :
*https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
*/

typedef struct multiboot_header {
	__u32 magic;	/*required*/
	__u32 flags;	/*required*/
	__u32 checksum; /*required*/

	/* If flags[16] is set */

	 /* Physical Memory at which the struct is loaded */
	__u32 header_addr;

	/* Physical Memory of the begining of the text segment */
	__u32 load_addr;

	/* Physical Memory of the end of data segment */
	__u32 load_end_addr;

	/* Physical Memory of the end of bss segment */
	__u32 bss_end_addr;

	/* Physical Memory where the bootloader should jump to start the kernel */
	__u32 entry_addr; 

	/* If flags[2] is set */

	__u32 mode_type;
	__u32 width;
	__u32 height;
	__u32 depth;

}multiboot_header;

typedef struct multiboot_info_struct {
	__u32 flags; /* Required */
	__u32 mem_lower;
	__u32 mem_upper;
	__u32 boot_device;
	__u32 cmd_line ;
	__u32 mods_count ;
	__u32 mods_addr;

	/* TODO */

	__u32 mmap_length;
	__u32 mmap_addr ;
	__u32 drives_length;
	__u32 drives_addr;
	__u32 config_table;
	__u32 boot_loader_name ;
	__u32 apm_table;
	__u32 vbe_control_info;  
	__u32 vbe_mode_info;
	__u32 vbe_mode;    
	__u32 vbe_interface_seg;
	__u32 vbe_interface_off;
	__u32 vbe_interface_len;
	__u32 framebuffer_addr  ;
	__u32 framebuffer_pitch ;
	__u32 framebuffer_width ;
	__u32 framebuffer_height;
	__u32 framebuffer_bpp   ;
	__u32 framebuffer_type  ;
	__u32 color_info        ;
};