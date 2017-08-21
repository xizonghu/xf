#ifndef __DMA_H__
#define __DMA_H__

extern void fw_dma_init();

extern int dma_adc_config(int *buffer, int size);
extern void dma_adc_enable(char enable);


#endif  
	 



