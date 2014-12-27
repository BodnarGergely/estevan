/*
 * Flash.c
 *
 *  Created on: 2014.07.17.
 *      Author: Gergo
 */
#include "Flash.h"
#include "stm32f4xx_flash.h"
#include "stm32f4_discovery.h"
#include "Timers.h"


uint32_t GetSector(uint32_t Address);

void FlashReset()
{
	uint32_t uwStartSector = 0;
	uint32_t uwEndSector = 0;
	uint32_t uwAddress = 0;
	uint32_t uwSectorCounter = 0;
	__IO uint32_t uwData32 = 0;
	__IO uint32_t uwMemoryProgramStatus = 0;

	FLASH_Unlock();

	/* Erase the user Flash area ************************************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
				   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	/* Get the number of the start and end sectors */
	uwStartSector = GetSector(FLASH_USER_START_ADDR);
	uwEndSector = GetSector(FLASH_USER_END_ADDR);

	/* Strat the erase operation */
	uwSectorCounter = uwStartSector;

	while (uwSectorCounter <= uwEndSector)
	{
		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		be done by word */
		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
		/* Error occurred while sector erase.
		  User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
		/* jump to the next sector */
		if (uwSectorCounter == FLASH_Sector_11)
		{
			uwSectorCounter += 40;
		}
		else
		{
			uwSectorCounter += 8;
		}
	}

	FLASH_Lock();
}

void FlashSample()
{
	uint32_t uwStartSector = 0;
	uint32_t uwEndSector = 0;
	uint32_t uwAddress = 0;
	uint32_t uwSectorCounter = 0;
	__IO uint32_t uwData32 = 0;
	__IO uint32_t uwMemoryProgramStatus = 0;

	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);

	FLASH_Unlock();

	/* Erase the user Flash area ************************************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
				   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	/* Get the number of the start and end sectors */
	uwStartSector = GetSector(FLASH_USER_START_ADDR);
	uwEndSector = GetSector(FLASH_USER_END_ADDR);

	/* Strat the erase operation */
	uwSectorCounter = uwStartSector;

	while (uwSectorCounter <= uwEndSector)
	{
		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		be done by word */
		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
		/* Error occurred while sector erase.
		  User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
		/* jump to the next sector */
		if (uwSectorCounter == FLASH_Sector_11)
		{
			uwSectorCounter += 40;
		}
		else
		{
			uwSectorCounter += 8;
		}
	}

	/* Program the user Flash area word by word ********************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

	uwAddress = FLASH_USER_START_ADDR;

	while (uwAddress < FLASH_USER_END_ADDR)
	{
		if (FLASH_ProgramWord(uwAddress, DATA_32) == FLASH_COMPLETE)
		{
			uwAddress = uwAddress + 4;
		}
		else
		{
		/* Error occurred while writing data in Flash memory.
		  User can add here some code to deal with this error */
			while (1)
			{
			}
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	  to protect the FLASH memory against possible unwanted operation) */
	FLASH_Lock();

	/* Check if the programmed data is OK ***************************************/
	/*  MemoryProgramStatus = 0: data programmed correctly
	   MemoryProgramStatus != 0: number of words not programmed correctly */
	uwAddress = FLASH_USER_START_ADDR;
	uwMemoryProgramStatus = 0;

	while (uwAddress < FLASH_USER_END_ADDR)
	{
		uwData32 = *(__IO uint32_t*)uwAddress;

		if (uwData32 != DATA_32)
		{
			uwMemoryProgramStatus++;
		}

		uwAddress = uwAddress + 4;
	}

	/* Check Data correctness */
	if(uwMemoryProgramStatus)
	{
		/* KO */
		/* Turn on LD2 */
		STM_EVAL_LEDOn(LED4);
	}
	else
	{
		/* OK */
		/* Turn on LD1 */
		STM_EVAL_LEDOn(LED5);
	}

	while (1)
	{
	}
}

/**
   * @brief  Gets the sector of a given address
   * @param  None
   * @retval The sector of a given address
   */
uint32_t GetSector(uint32_t Address)
{
	uint32_t sector = 0;

	if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
	 sector = FLASH_Sector_0;
	}
	else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
	{
	 sector = FLASH_Sector_1;
	}
	else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
	{
	 sector = FLASH_Sector_2;
	}
	else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
	{
	 sector = FLASH_Sector_3;
	}
	else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
	{
	 sector = FLASH_Sector_4;
	}
	else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
	{
	 sector = FLASH_Sector_5;
	}
	else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
	{
	 sector = FLASH_Sector_6;
	}
	else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
	{
	 sector = FLASH_Sector_7;
	}
	else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
	{
	 sector = FLASH_Sector_8;
	}
	else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
	{
	 sector = FLASH_Sector_9;
	}
	else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
	{
	 sector = FLASH_Sector_10;
	}
	else
	{
	 sector = FLASH_Sector_11;
	}
	return sector;
}

void GetSectorStamp2(FlashStampStruct* returnStruct)
{
	uint8_t i = 0;
	uint32_t uwAddress = ADDR_FLASH_SELECTOR;

	uwAddress = ((*(__IO uint16_t*)uwAddress) == FlashSectorSelector_End) ? ( ADDR_FLASH_SECTOR_4 + ( sizeof(FlashStampStruct) * 15 )) :  ADDR_FLASH_SECTOR_4;

	for(i = 0; i < 15; i++)
	{
		returnStruct[i].FlashStampStruct_uwAddress = *(__IO uint32_t*)uwAddress;
		uwAddress += 4;

		returnStruct[i].FlashStampStruct_uwSectorCounter = *(__IO uint32_t*)uwAddress;
		uwAddress += 4;

		returnStruct[i].FlashStampStruct_uwSelector = *(__IO uint8_t*)uwAddress;
		uwAddress++;

		returnStruct[i].FlashStampStruct_Length = *(__IO uint32_t*)uwAddress;
		uwAddress += 4;

		returnStruct[i].FlashStampStruct_StateMState = *(__IO uint8_t*)uwAddress;
		uwAddress++;
	}
}


void GetSectorStamp(FlashStampStruct* returnStruct)
{
	FlashStampStruct getStruct[15];
	uint8_t i = 0;

	GetSectorStamp2(&getStruct[0]);

	for(i = 0; i < 15; i++)
	{
		if(getStruct[i].FlashStampStruct_StateMState == 0xFF )
		{
			returnStruct[SectorStampSelector_Current].FlashStampStruct_Length = getStruct[i].FlashStampStruct_Length;
			returnStruct[SectorStampSelector_Current].FlashStampStruct_uwAddress = getStruct[i].FlashStampStruct_uwAddress;
			returnStruct[SectorStampSelector_Current].FlashStampStruct_uwSectorCounter = getStruct[i].FlashStampStruct_uwSectorCounter;
			returnStruct[SectorStampSelector_Current].FlashStampStruct_uwSelector = getStruct[i].FlashStampStruct_uwSelector;
			returnStruct[SectorStampSelector_Current].FlashStampStruct_StateMState = getStruct[i].FlashStampStruct_StateMState;

			--i;

			returnStruct[SectorStampSelector_Prev].FlashStampStruct_Length = getStruct[i].FlashStampStruct_Length;
			returnStruct[SectorStampSelector_Prev].FlashStampStruct_uwAddress = getStruct[i].FlashStampStruct_uwAddress;
			returnStruct[SectorStampSelector_Prev].FlashStampStruct_uwSectorCounter = getStruct[i].FlashStampStruct_uwSectorCounter;
			returnStruct[SectorStampSelector_Prev].FlashStampStruct_uwSelector = getStruct[i].FlashStampStruct_uwSelector;
			returnStruct[SectorStampSelector_Prev].FlashStampStruct_StateMState = getStruct[i].FlashStampStruct_StateMState;

			break;
		}
	}
}

/*
 * Csak elõzõleg törölt szektoron alkalmazható
 * Szükséges a Flash memória Unlock-olása
 * */
FlashBool_Type SetSectorStamp(FlashStampStruct* dataStruct)
{
	//uint32_t uwAddress = ADDR_FLASH_SECTOR_4;
	FlashStampStruct returnStruct[2];
	FlashStampStruct returnStruct2[15];
	uint8_t i = 0;
	uint32_t uwAddress = ADDR_FLASH_SELECTOR;

	uwAddress = ((*(__IO uint16_t*)uwAddress) == FlashSectorSelector_End) ? ( ADDR_FLASH_SECTOR_4 + ( sizeof(FlashStampStruct) * 15 )) :  ADDR_FLASH_SECTOR_4;


	GetSectorStamp2(&returnStruct2[0]);

	for(i = 0; i < 15; ++i)
	{
		if(returnStruct2[i].FlashStampStruct_StateMState == 0xFF)
		{
			uwAddress += 9;

			if (FLASH_ProgramByte(uwAddress, (((dataStruct->FlashStampStruct_Length) & 0xFF))) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((dataStruct->FlashStampStruct_Length) & 0xFF00) >> 8)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((dataStruct->FlashStampStruct_Length) & 0xFF0000) >> 16)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((dataStruct->FlashStampStruct_Length) & 0xFF000000) >> 24)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, ((dataStruct->FlashStampStruct_StateMState))) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			break;
		}

		else
		{
			uwAddress += 14;
		}
	}

	GetSectorStamp2(&returnStruct2[0]);
/*
	if((returnStruct.FlashStampStruct_Length == dataStruct->FlashStampStruct_Length) && (returnStruct.FlashStampStruct_StateMState == dataStruct->FlashStampStruct_StateMState))
		return FlashBool_True;
	else
		return FlashBool_False;*/
	return FlashBool_True;
}

void FlashSectorStampToDefault(SectorStampToDefaultMode mode)
{
	uint32_t uwSectorCounter = 0;
	uint32_t targetSectorCounter = 0;
	uint32_t targetAddress = 0;
	uint8_t  targetSelector = 0;
	uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_4);
	uint32_t uwAddress = ADDR_FLASH_SECTOR_4;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t selector = 0;
	uint8_t cycle = 0;

	selector = *(__IO uint8_t*)ADDR_FLASH_SELECTOR;

	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
				FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	/* Strat the erase operation */
	/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
	be done by word */
	if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
	{
	/* Error occurred while sector erase.
	  User can add here some code to deal with this error  */
		while (1)
		{
		}
	}

	for(i = 0; i < 15; i++)
	{
		switch(i)
		{
		case 0 :
			targetSectorCounter = FLASH_Sector_5;
			targetAddress = ADDR_FLASH_SECTOR_5;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 1 :
			targetSectorCounter = FLASH_Sector_5;
			targetAddress = ADDR_FLASH_SECTOR_5;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 2 :
			targetSectorCounter = FLASH_Sector_5;
			targetAddress = ADDR_FLASH_SECTOR_5;
			targetSelector = FlashSectorSelector_End;
			break;

		case 3 :
			targetSectorCounter = FLASH_Sector_6;
			targetAddress = ADDR_FLASH_SECTOR_6;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 4 :
			targetSectorCounter = FLASH_Sector_6;
			targetAddress = ADDR_FLASH_SECTOR_6;
			targetSelector = FlashSectorSelector_End;
			break;

		case 5 :
			targetSectorCounter = FLASH_Sector_7;
			targetAddress = ADDR_FLASH_SECTOR_7;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 6 :
			targetSectorCounter = FLASH_Sector_7;
			targetAddress = ADDR_FLASH_SECTOR_7;
			targetSelector = FlashSectorSelector_End;
			break;

		case 7 :
			targetSectorCounter = FLASH_Sector_8;
			targetAddress = ADDR_FLASH_SECTOR_8;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 8 :
			targetSectorCounter = FLASH_Sector_8;
			targetAddress = ADDR_FLASH_SECTOR_8;
			targetSelector = FlashSectorSelector_End;
			break;

		case 9 :
			targetSectorCounter = FLASH_Sector_9;
			targetAddress = ADDR_FLASH_SECTOR_9;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 10 :
			targetSectorCounter = FLASH_Sector_9;
			targetAddress = ADDR_FLASH_SECTOR_9;
			targetSelector = FlashSectorSelector_End;
			break;

		case 11 :
			targetSectorCounter = FLASH_Sector_10;
			targetAddress = ADDR_FLASH_SECTOR_10;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 12 :
			targetSectorCounter = FLASH_Sector_10;
			targetAddress = ADDR_FLASH_SECTOR_10;
			targetSelector = FlashSectorSelector_End;
			break;

		case 13 :
			targetSectorCounter = FLASH_Sector_11;
			targetAddress = ADDR_FLASH_SECTOR_11;
			targetSelector = FlashSectorSelector_Beginning;
			break;

		case 14 :
			targetSectorCounter = FLASH_Sector_11;
			targetAddress = ADDR_FLASH_SECTOR_11;
			targetSelector = FlashSectorSelector_End;
			break;
		}

		if(mode == SectorStampToDefaultMode_Only_First)
			cycle = 2;
		else
			cycle = 1;

		for(j = 0; j < cycle; j++)
		{
			if((j == 1) || (selector == FlashStumpSelector_Beginning))
				uwAddress = ADDR_FLASH_SECTOR_4 + ( sizeof(FlashStampStruct) * 15 );

			if (FLASH_ProgramByte(uwAddress, ((targetAddress) & 0xFF)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetAddress) & 0xFF00) >> 8)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetAddress) & 0xFF0000) >> 16)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetAddress) & 0xFF000000) >> 24)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;



			if (FLASH_ProgramByte(uwAddress, ((targetSectorCounter) & 0xFF)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetSectorCounter) & 0xFF00) >> 8)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetSectorCounter) & 0xFF0000) >> 16)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if (FLASH_ProgramByte(uwAddress, (((targetSectorCounter) & 0xFF000000) >> 24)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;



			if (FLASH_ProgramByte(uwAddress, (targetSelector)) != FLASH_COMPLETE)
			{
				while (1)
				{
				}
			}
			uwAddress++;

			if(i == 0)
			{
				if (FLASH_ProgramByte(uwAddress, 0) != FLASH_COMPLETE)
				{
					while (1)
					{
					}
				}
				uwAddress++;

				if (FLASH_ProgramByte(uwAddress, 0) != FLASH_COMPLETE)
				{
					while (1)
					{
					}
				}
				uwAddress++;

				if (FLASH_ProgramByte(uwAddress, 0) != FLASH_COMPLETE)
				{
					while (1)
					{
					}
				}
				uwAddress++;

				if (FLASH_ProgramByte(uwAddress, 0) != FLASH_COMPLETE)
				{
					while (1)
					{
					}
				}
				uwAddress++;

				if (FLASH_ProgramByte(uwAddress, 0) != FLASH_COMPLETE)
				{
					while (1)
					{
					}
				}
				uwAddress++;
			}

			else
				uwAddress += 5;
		}
	}

	if(mode == SectorStampToDefaultMode_In_Use)
	{

	}

	FLASH_Lock();
}

void CopyToFlashTest(uint16_t* matrix, uint32_t numberOfHalfWorlds)
{
	static uint8_t ReceiveMatrix[8 * (sizeof(FlashStampStruct))];
	static uint16_t ADCConvertedValuesCheck[14][ADC_PACKAGE_MAX_NUMBER * 12 * 2];
	static uint16_t ADCConvertedValuesCheck2[14][ADC_PACKAGE_MAX_NUMBER * 12];
	uint32_t uwAddress = 0;
	uint32_t uwAddressRef = 0;
	uint32_t uwAddressAccu = 0;
	uint32_t uwSectorCounter = 0;
	uint8_t uwSelector = 0;
	uint16_t* matrixTemp = 0;
	FlashStampStruct flashStructGet[2];
	FlashStampStruct flashStructSet;
	FlashStampStruct flashStructBlock[14];
	uint8_t i = 0;
	uint8_t j = 0;
	static uint8_t k = 0;


	matrixTemp = matrix;

	for(i = 0; i < numberOfHalfWorlds; ++i)
	{
		ADCConvertedValuesCheck2[k][i] = *matrixTemp;
		matrixTemp++;
	}
	k = (k == 13) ? 0 : k + 1;

	GetSectorStamp(&flashStructGet[0]);

	uwSectorCounter = flashStructGet[SectorStampSelector_Current].FlashStampStruct_uwSectorCounter;
	uwAddress = flashStructGet[SectorStampSelector_Current].FlashStampStruct_uwAddress;
	uwSelector = flashStructGet[SectorStampSelector_Current].FlashStampStruct_uwSelector;

	if(uwSelector == FlashSectorSelector_Beginning)
	{
		flashStructSet.FlashStampStruct_Length = numberOfHalfWorlds;
	}
	else if(uwSelector == FlashSectorSelector_End)
	{
		uwAddress += (flashStructGet[SectorStampSelector_Prev].FlashStampStruct_Length * 2);
		flashStructSet.FlashStampStruct_Length = flashStructGet[SectorStampSelector_Prev].FlashStampStruct_Length + numberOfHalfWorlds;
	}

	FLASH_Unlock();

	if(uwSelector == FlashSectorSelector_Beginning)
	{
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

		/* Strat the erase operation */
		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		be done by word */
		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
		/* Error occurred while sector erase.
		  User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
	}

	uwAddressAccu = uwAddress;
	uwAddressRef = uwAddress;
	matrixTemp = matrix;

	while(uwAddress < (uwAddressRef + (2 * (flashStructSet.FlashStampStruct_Length))))
	{
		if (FLASH_ProgramHalfWord(uwAddress, *matrixTemp) == FLASH_COMPLETE)
		{
			uwAddress = uwAddress + 2;
			matrixTemp++;
		}
		else
		{
			while (1)
			{
			}
		}
	}

	if(flashStructGet[SectorStampSelector_Prev].FlashStampStruct_StateMState == 13)
	{
		FlashSectorStampToDefault(SectorStampToDefaultMode_In_Use);

		for(i = 0; i < 14; i++)
		{
			for(j = 0; j < (ADC_PACKAGE_MAX_NUMBER * 12 * 2); j++)
				ADCConvertedValuesCheck[i][j] = 0;
		}

		for(i = 0; i < 14; i++)
		{
			for(j = 0; j < (ADC_PACKAGE_MAX_NUMBER * 12); j++)
				ADCConvertedValuesCheck2[i][j] = 0;
		}
	}

	else
	{
		flashStructSet.FlashStampStruct_StateMState = flashStructGet[SectorStampSelector_Prev].FlashStampStruct_StateMState + 1;
		SetSectorStamp(&flashStructSet);
	}

	FLASH_Lock();

	GetSectorStamp2(&flashStructBlock[0]);

	for(i = 0; i < 14; i++)
	{
		j = 0;

		uwAddress = flashStructBlock[i].FlashStampStruct_uwAddress;
		uwAddressRef = uwAddress;

		if(flashStructBlock[i].FlashStampStruct_Length != 0xFFFFFFFF)
		{
			while(uwAddress < (uwAddressRef + (2 * flashStructBlock[i].FlashStampStruct_Length)))
			{
				ADCConvertedValuesCheck[i][j] = *(__IO uint16_t*)uwAddress;
				j++;
				uwAddress = uwAddress + 2;
			}
		}
	}
}

/*
void CopyToFlash(uint16_t* matrix, uint32_t numberOfHalfWorlds)
{
	uint8_t flashState= 0;
	uint8_t flashStateIndicator = 0;
	uint32_t uwAddress = 0;
	uint32_t uwAddressRef = 0;
	uint32_t uwAddressTemp = 0;
	uint32_t uwAddress2 = 0;
	uint32_t uwSectorCounter = 0;
	static uint16_t ADCConvertedValuesRec[8][ADC_PACKAGE_MAX_NUMBER * 12 * 2];
	static uint16_t ADCConvertedValuesCheck[8][ADC_PACKAGE_MAX_NUMBER * 12];
	uint32_t k = 0;
	uint32_t i = 0;
	static uint32_t j = 0;
	FlashStampStruct sstruct;
	FlashStampStruct gstruct;
	uint16_t* matrixValue = matrix;

	for(k = 0; k < numberOfHalfWorlds; k++)
	{
		ADCConvertedValuesCheck[j][k] = *matrixValue;
		matrixValue++;
	}

	matrixValue = matrix;

	//uwAddress = ADDR_FLASH_SECTOR_5 - 1;
	//flashState = *(__IO uint8_t*)uwAddress;
//	GetSectorStamp(FLASH_Sector_4, &gstruct);
	flashState = gstruct.FlashStampStruct_StateMState;

	FLASH_Unlock();

	if(flashState > 28)
		flashState = 0;
	else if(flashState == 28)
		flashState = 1;
	else
		flashState++;

	if((flashState % 2))
	{
		sstruct.FlashStampStruct_Length = numberOfHalfWorlds;

		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
					   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

		uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_4);


		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
			while (1)
			{
			}
		}

		uwAddressRef = ADDR_FLASH_SECTOR_4;
		uwAddress = ADDR_FLASH_SECTOR_4;

		while (uwAddress < (uwAddressRef + (2 * numberOfHalfWorlds)))
		{
			if (FLASH_ProgramHalfWord(uwAddress, *matrixValue) == FLASH_COMPLETE)
			{
				uwAddress = uwAddress + 2;
				matrixValue++;
			}
			else
			{
				while (1)
				{
				}
			}
		}
	}

	else
	{
		switch(flashState)
		{
			case 2:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_5);
				uwAddress = ADDR_FLASH_SECTOR_5;
				break;
			case 4:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_6);
				uwAddress = ADDR_FLASH_SECTOR_6;
				break;

			case 6:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_7);
				uwAddress = ADDR_FLASH_SECTOR_7;
				break;

			case 8:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_8);
				uwAddress = ADDR_FLASH_SECTOR_8;
				break;

			case 10:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_9);
				uwAddress = ADDR_FLASH_SECTOR_9;
				break;

			case 12:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_10);
				uwAddress = ADDR_FLASH_SECTOR_10;
				break;

			case 14:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_11);
				uwAddress = ADDR_FLASH_SECTOR_11;
				break;

			case 16:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_5);
				uwAddress = ADDR_FLASH_SECTOR_5;
				break;

			case 18:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_6);
				uwAddress = ADDR_FLASH_SECTOR_6;
				break;

			case 20:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_7);
				uwAddress = ADDR_FLASH_SECTOR_7;
				break;

			case 22:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_8);
				uwAddress = ADDR_FLASH_SECTOR_8;
				break;

			case 24:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_9);
				uwAddress = ADDR_FLASH_SECTOR_9;
				break;

			case 26:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_10);
				uwAddress = ADDR_FLASH_SECTOR_10;
				break;

			case 28:
				uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_11);
				uwAddress = ADDR_FLASH_SECTOR_11;
				break;

			default:

				break;
		}


		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
					   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
			while (1)
			{
			}
		}

// Flash írása.



		uwAddressTemp = uwAddress;
		uwAddressRef = uwAddress;
		uwAddress2 = ADDR_FLASH_SECTOR_4;
	//	GetSectorStamp(FLASH_Sector_4, &gstruct);

		while(uwAddress < (uwAddressRef + (2 * gstruct.FlashStampStruct_Length)))
		{
			if (FLASH_ProgramHalfWord(uwAddress, (*(__IO uint16_t*)uwAddress2)) == FLASH_COMPLETE)
			{
				uwAddress = uwAddress + 2;
				uwAddress2 = uwAddress2 + 2;
			}
			else
			{
				while (1)
				{
				}
			}
		}
		//uwAddress = uwAddressRef = uwAddressTemp;
		uwAddressRef = uwAddress;

		while (uwAddress < (uwAddressRef + (2 * numberOfHalfWorlds)))
		{
			if (FLASH_ProgramHalfWord(uwAddress, *matrixValue) == FLASH_COMPLETE)
			{
				uwAddress = uwAddress + 2;
				matrixValue++;
			}
			else
			{
				while (1)
				{
				}
			}
		}
	}


 // A 64k-os utolsó bájtja az állapotgép állapotát jelöli. Ezt a sikeres írás után írhatjuk csak.
 // Ez alapján dönt, hogy melyik Sector legyen a következõ, illetve olvasáskor milyen a kronológiája az adatoknak.


	//uwAddress = ADDR_FLASH_SECTOR_5 - 1;
//	if (FLASH_ProgramByte(uwAddress, flashState) != FLASH_COMPLETE)
	//{
	//	while(1);
	//}

	//FLASH_Lock();

		switch(j)
		{
		case 0:
			uwAddress = ADDR_FLASH_SECTOR_4;
			break;
		case 1:
			uwAddress = ADDR_FLASH_SECTOR_5;
			break;
		case 2:
			uwAddress = ADDR_FLASH_SECTOR_4;
			break;
		case 3:
			uwAddress = ADDR_FLASH_SECTOR_6;
			break;
		case 4:
			uwAddress = ADDR_FLASH_SECTOR_4;
			break;
		case 5:
			uwAddress = ADDR_FLASH_SECTOR_7;
			break;
		case 6:
			uwAddress = ADDR_FLASH_SECTOR_4;
			break;
		case 7:
			uwAddress = ADDR_FLASH_SECTOR_8;
			break;
		}
		uwAddressRef = uwAddress;

		while (uwAddress < (uwAddressRef + (2 * (2 * numberOfHalfWorlds))))
		{
			ADCConvertedValuesRec[j][i] = *(__IO uint16_t*)uwAddress;
			i++;
			uwAddress = uwAddress + 2;
		}
		j++;

		if(j == 8)
		{
			j = 0;
		}


		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
					   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

		uwSectorCounter = GetSector(ADDR_FLASH_SECTOR_4);

		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
			while (1)
			{
			}
		}


		 // A 64k-os utolsó bájtja az állapotgép állapotát jelöli. Ezt a sikeres írás után írhatjuk csak.
		 // Ez alapján dönt, hogy melyik Sector legyen a következõ, illetve olvasáskor milyen a kronológiája az adatoknak.


		sstruct.FlashStampStruct_StateMState = flashState;

		SetSectorStamp(FLASH_Sector_4, &sstruct);


		FLASH_Lock();
}*/
