#ifndef __ERROR_H
#define __ERROR_H


/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U,
  HAL_INCOMPLETE = 0x04U
} HAL_StatusTypeDef;

#endif