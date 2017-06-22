#include "xftypedef.h"
#include "xfmalloc.h"

//#include "api/logcat.h"

typedef uint8 addr;

struct mem_control_block {
    uint8 is_available;
    uint8 size;
};

//static uint8 memory_poll[XF_MALLOC_SIZE];
//static int16 memory_avaliable = 0;
//static uint16 memory_counter = 0;

static uint8 has_initialized = 0;
static addr *managed_memory_start;
static addr *last_valid_address;

static void malloc_init() {
    //memory_avaliable = XF_MallocConfig.size;
    XF_MallocConfig.sizeAvalid = XF_MallocConfig.size;
    XF_MallocConfig.sizeUsed = 0;

    managed_memory_start = (addr *)XF_MallocConfig.addr;
    last_valid_address = managed_memory_start;
    has_initialized = 1;
}

void *XF_malloc(uint8 numbytes) {
    addr *current_location;
    struct mem_control_block *current_location_mcb;
    addr *memory_location;

    if(! has_initialized) {
        malloc_init();
    }

    numbytes = numbytes + sizeof(struct mem_control_block);
    memory_location = 0;
    current_location = managed_memory_start;

    //Keep going until we have searched all allocated space
    while(current_location != last_valid_address) {
        current_location_mcb = (struct mem_control_block *)current_location;
        if(current_location_mcb->is_available) {
            if(current_location_mcb->size >= numbytes) {
                //We''ve found an appropriately-size location.
                current_location_mcb->is_available = 0;
                memory_location = current_location;
                break;
            }
        }
        //move to the next one
        current_location = current_location + current_location_mcb->size;
    }

    // If we still don''t have a valid location, we''ll have to ask the static poll for more memory
    if(! memory_location) {
        //memory_avaliable -= numbytes;
        XF_MallocConfig.sizeAvalid -= numbytes;
        memory_location = last_valid_address;
        last_valid_address = last_valid_address + numbytes;
        //if(last_valid_address >= (managed_memory_start + XF_MALLOC_SIZE)) {
        if(last_valid_address >= (managed_memory_start + XF_MallocConfig.size)) {
            return 0;
        }
        //We need to initialize the mem_control_block
        current_location_mcb = (struct mem_control_block *)memory_location;
        current_location_mcb->is_available = 0;
        current_location_mcb->size = numbytes;
    }

    memory_location = memory_location + sizeof(struct mem_control_block);

    XF_MallocConfig.sizeUsed += current_location_mcb->size;
    //memory_counter += current_location_mcb->size;
    //printf("xfmalloc: [0x%8x: %d]\n", (int)memory_location, current_location_mcb->size);
    //LOG_I("xfmalloc:", "[0x%4x: %d]\n", (int)memory_location, current_location_mcb->size);

    return memory_location;
}

void XF_free(void *firstbyte) {
    struct mem_control_block *mcb;

    if(last_valid_address <= (addr *)firstbyte || (addr *)firstbyte <= managed_memory_start) return;

    mcb = (struct mem_control_block*)((addr *)firstbyte - sizeof(struct mem_control_block));
    if(0 == mcb->is_available) mcb->is_available = 1;

    XF_MallocConfig.sizeUsed -= mcb->size;
    //memory_counter -= mcb->size;
    //printf("xffree: [0x%8x: %d]\n", (int)firstbyte, mcb->size);
    //LOG_I("xffree:", "[0x%4x: %d]\n", (int)firstbyte, mcb->size);

    return;
}