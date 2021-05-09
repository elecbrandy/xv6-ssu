#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"
#include "slab.h"

struct {
	struct spinlock lock;
	struct slab slab[NSLAB];
} stable;
char* clear_bit(char* size, int i) {

	char *tmp = size;
	tmp += (i / 8);
	i = i - (i / 8) * 8;
	unsigned char cri = 0x80;
	*(tmp + i) = *(tmp + i) & ~(cri >> i);
	return tmp;
}
void slabinit(){
	/* fill in the blank */
	
	struct slab *temp;
	int s_size = 8;
	for(temp = stable.slab; temp < &stable.slab[NSLAB]; temp++){
		temp->size = s_size;
		temp->num_pages = 1;
		temp->num_free_objects = 4096 / s_size; 
		temp->num_used_objects = 0;
		temp->num_objects_per_page = 4096 /s_size;
		temp->bitmap = kalloc();
		temp->page[0] = kalloc();
		s_size = s_size << 1;
	}
	
}

char *kmalloc(int size){
	/* fill in the blank */
	struct slab *s;
	acquire(&stable.lock);
	if(size <= 2048){
		int count = 0;
		int tmp;
		int byteaddr = 0;
		if(size && ! ( size & (size -1))){
			tmp = size;
		}
		else{
			while ( size != 0){
				size>>=1;
				count += 1;
			}
			tmp = 1 << count;
		}
			
		

		for(s=stable.slab; s<&stable.slab[NSLAB]; s++){
			if(s-> size == tmp){
				if(s->num_free_objects == 0){
					s->page[s->num_pages]= kalloc();
					s->num_pages++;
					s->num_free_objects += s->num_objects_per_page;
				}
				s->bitmap[byteaddr>>3] |= 1<<(byteaddr%8);
				s->num_used_objects++;
				s->num_free_objects--;
				break;
			}
		}
		byteaddr++;

		return &s->page[s->num_pages-1][s->num_objects_per_page-(s->num_free_objects+1)];
	}
	
	return 0;
}

void kmfree(char *addr){
	/* fill in the blank */
	struct slab *s;
	for(s = stable.slab ; s < &stable.slab[NSLAB] ; s++){
		int count = 0; 		
		for(int i = 0 ; i < s->num_pages ; i++){
			for(int j = 0 ; j < s->num_objects_per_page ; j++){
				if(addr == s->page[i] + (j * s->size)){
					s->num_free_objects++;
					s->num_used_objects--;
					clear_bit((s->bitmap), i * s->num_objects_per_page + j);
					if(s->num_used_objects < ((s->num_pages - 1) + count) * s->num_objects_per_page){
						s->num_free_objects -= s->num_objects_per_page;
						kfree(s->page[s->num_pages - 1 + count]);
						count--;
					}
					s->num_pages += count;
					return;
				}
			}
		}
		s->num_pages += count;
	}
	return;
}
			


void slabdump(){
	cprintf("__slabdump__\n");

	struct slab *s;

	cprintf("size\tnum_pages\tused_objects\tfree_objects\n");

	for(s = stable.slab; s < &stable.slab[NSLAB]; s++){
		cprintf("%d\t%d\t\t%d\t\t%d\n", 
			s->size, s->num_pages, s->num_used_objects, s->num_free_objects);
	}
}
