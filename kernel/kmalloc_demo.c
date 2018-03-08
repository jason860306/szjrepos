/**
 * ============================================================================
 * @file    kmalloc_demo.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-09-23 10:20:31
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <linux/slab.h>

static struct kmem_cache *my_cachep;

static void init_my_cache(void);
static void remove_my_cache(void);
static int slab_test(void);

int main(void)
{
	slab_test();
	return 0;
}

static void init_my_cache(void)
{
	my_cachep = kmem_cache_create("my_cache", 32, 0, SLAB_HWCACHE_ALIGN, NULL, NULL);
}

static void remove_my_cache(void)
{
	if (my_cachep)
	{
		kmem_cache_destroy(my_cachep);
	}
}

static int slab_test(void)
{
	void *obj;
	printk("cache name is %s\n", kmem_cache_name(my_cachep));
	printk("cache object size is %d\n", kmem_cache_size(my_cachep));

	obj = kmem_cache_alloc(my_cachep, GFP_KERNEL);
	if (obj)
	{
		kmem_cache_free(my_cachep, obj);
	}

	return 0;
}
