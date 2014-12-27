/*
 * Flash.h
 *
 *  Created on: 2014.07.17.
 *      Author: Gergo
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "stdint.h"

#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_4   /* Start @ of user Flash area */

#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_11   /* End @ of user Flash area */

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define DATA_32                 ((uint32_t)0x12345678)

#define ADDR_FLASH_SELECTOR		((uint32_t)0x0801FFFF)

typedef enum {
	FlashBool_False = 0,
	FlashBool_True = 1
}FlashBool_Type;

typedef enum {
	FlashSectorSelector_Beginning = 0,
	FlashSectorSelector_End = 1
}FlashSectorSelector;

typedef enum {
	FlashStumpSelector_Default = 0,
	FlashStumpSelector_Beginning = 1,
	FlashStumpSelector_End = 2
}FlashStumpSelector;

typedef enum {
	SectorStampSelector_Prev = 0,
	SectorStampSelector_Current = 1
}SectorStampSelector;

typedef enum {
	SectorStampToDefaultMode_In_Use = 1,
	SectorStampToDefaultMode_Only_First = 2
}SectorStampToDefaultMode;

typedef struct {
	uint32_t FlashStampStruct_uwAddress;			//ADDR_FLASH_SECTOR_x
	uint32_t FlashStampStruct_uwSectorCounter;		//Flash_Sector_x
	uint8_t FlashStampStruct_uwSelector;			//FlashSectorSelector_Beginning/End

	uint32_t FlashStampStruct_Length;				//numberOfHalfWorlds
	uint8_t  FlashStampStruct_StateMState;
}
FlashStampStruct;

void FlashSample();
void CopyToFlash(uint16_t* matrix, uint32_t numberOfHalfWorlds);
void CopyToFlashTest();
void GetSectorStamp(FlashStampStruct* returnStruct);
void FlashSectorStampToDefault(SectorStampToDefaultMode mode);


#endif /* FLASH_H_ */
