/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_qmc5883l.c
 * @brief     driver qmc5883l source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-07-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/07/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_qmc5883l.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "QST QMC5883L"        /**< chip name */
#define MANUFACTURER_NAME         "QST"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.16f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                  /**< chip max supply voltage */
#define MAX_CURRENT               2.6f                  /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            1000                  /**< driver version */

/**
 * @brief iic address definition
 */
#define QMC5883L_ADDRESS           0x1A        /**< iic address */

/**
 * @brief chip register definition
 */
#define QMC5883L_REG_X_LSB          0x00      /**< data output x lsb register */
#define QMC5883L_REG_X_MSB          0x01      /**< data output x msb register */
#define QMC5883L_REG_Y_LSB          0x02      /**< data output y lsb register */
#define QMC5883L_REG_Y_MSB          0x03      /**< data output y msb register */
#define QMC5883L_REG_Z_LSB          0x04      /**< data output z lsb register */
#define QMC5883L_REG_Z_MSB          0x05      /**< data output z msb register */
#define QMC5883L_REG_STATUS         0x06      /**< status register */
#define QMC5883L_REG_TEMP_LSB       0x07      /**< temperature data lsb register */
#define QMC5883L_REG_TEMP_MSB       0x08      /**< temperature data msb register */
#define QMC5883L_REG_CONTROL1       0x09      /**< control 1 register */
#define QMC5883L_REG_CONTROL2       0x0A      /**< control 2 register */
#define QMC5883L_REG_PERIOD         0x0B      /**< period register */
#define QMC5883L_REG_ID             0x0D      /**< chip id register */

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a qmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is invalid
 *            - 4 soft reset failed
 * @note      none
 */
uint8_t qmc5883l_init(qmc5883l_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    uint8_t id;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->debug_print == NULL)                                                              /* check debug_print */
    {
        return 3;                                                                                 /* return error */
    }
    if (handle->iic_init == NULL)                                                                 /* check iic_init */
    {
        handle->debug_print("qmc5883l: iic_init is null.\n");                                     /* iic_init is null */
        
        return 3;                                                                                 /* return error */
    }
    if (handle->iic_deinit == NULL)                                                               /* check iic_deinit */
    {
        handle->debug_print("qmc5883l: iic_deinit is null.\n");                                   /* iic_deinit is null */
        
        return 3;                                                                                 /* return error */
    }
    if (handle->iic_read == NULL)                                                                 /* check iic_read */
    {
        handle->debug_print("qmc5883l: iic_read is null.\n");                                     /* iic_read is null */
        
        return 3;                                                                                 /* return error */
    }
    if (handle->iic_write == NULL)                                                                /* check iic_write */
    {
        handle->debug_print("qmc5883l: iic_write is null.\n");                                    /* iic_write is null */
        
        return 3;                                                                                 /* return error */
    }
    if (handle->delay_ms == NULL)                                                                 /* check delay_ms */
    {
        handle->debug_print("qmc5883l: delay_ms is null.\n");                                     /* delay_ms is null */
        
        return 3;                                                                                 /* return error */
    }
    
    if (handle->iic_init() != 0)                                                                  /* iic init */
    {
        handle->debug_print("qmc5883l: iic init failed.\n");                                      /* iic init failed */
        
        return 1;                                                                                 /* return error */
    }
    if (handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_ID, (uint8_t *)&id, 1) != 0)              /* read id failed */
    {
        handle->debug_print("qmc5883l: read failed.\n");                                          /* read failed */
        (void)handle->iic_deinit();                                                               /* iic deinit */
        
        return 4;                                                                                 /* return error */
    }
    if (id != 0xFF)                                                                               /* check id */
    {
        handle->debug_print("qmc5883l: id is invalid.\n");                                        /* id is invalid */
        (void)handle->iic_deinit();                                                               /* iic deinit */
        
        return 4;                                                                                 /* return error */
    }
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        (void)handle->iic_deinit();                                                               /* iic deinit */
        
        return 5;                                                                                 /* return error */
    }
    prev &= ~(1 << 7);                                                                            /* clear settings */
    prev |= 1 << 7;                                                                               /* set bool */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        (void)handle->iic_deinit();                                                               /* iic deinit */
        
        return 5;                                                                                 /* return error */
    }
    handle->delay_ms(100);                                                                        /* delay 100ms */
    handle->inited = 1;                                                                           /* flag finish initialization */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to a qmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 soft reset failed
 * @note      none
 */
uint8_t qmc5883l_deinit(qmc5883l_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }

    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */

        return 4;                                                                                 /* return error */
    }
    prev &= ~(1 << 7);                                                                            /* clear settings */
    prev |= 1 << 7;                                                                               /* set bool */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */

        return 4;                                                                                 /* return error */
    }
    handle->delay_ms(10);                                                                         /* delay 10ms */    
    if (handle->iic_deinit() != 0)                                                                /* iic deinit */
    {
        handle->debug_print("qmc5883l: iic deinit failed.\n");                                    /* return error */
        
        return 1;                                                                                 /* iic deinit failed */
    }   
    handle->inited = 0;                                                                           /* flag close */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get status
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_status(qmc5883l_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_STATUS, (uint8_t *)status, 1);        /* read status config */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("qmc5883l: read status failed.\n");                                 /* read status failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief      read temperature
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *deg points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       temperature sensor gain is factory-calibrated,
 *             but its offset has not been compensated, 
 *             only relative temperature value is accurate.
 */
uint8_t qmc5883l_read_temperature(qmc5883l_handle_t *handle, int16_t *raw, float *deg)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_TEMP_LSB, buf, 2);        /* read temp config */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("qmc5883l: read temp failed.\n");                       /* return temp failed */
        
        return 1;                                                                   /* return error */
    }
    *raw = (int16_t)(((uint16_t)(buf[1]) << 8) | buf[0]);                           /* combine data */
    *deg = (float)(*raw) / 100.0f;                                                  /* convert data */

    return 0;                                                                       /* success return 0 */
}

/**
 * @brief     set the chip mode
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_mode(qmc5883l_handle_t *handle, qmc5883l_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(3 << 0);                                                                            /* clear settings */
    prev |= mode << 0;                                                                            /* set mode */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_mode(qmc5883l_handle_t *handle, qmc5883l_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *mode = (qmc5883l_mode_t)((prev >> 0) & 0x3);                                                 /* get mode */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     set the output rate
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] rate is the output rate
 * @return    status code
 *            - 0 success
 *            - 1 set output rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_output_rate(qmc5883l_handle_t *handle, qmc5883l_output_rate_t rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(3 << 2);                                                                            /* clear settings */
    prev |= rate << 2;                                                                            /* set rate */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get the output rate
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *rate points to an output rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_output_rate(qmc5883l_handle_t *handle, qmc5883l_output_rate_t *rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *rate = (qmc5883l_output_rate_t)((prev >> 2) & 0x3);                                          /* get rate */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     set the full scale
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] scale is the set full scale
 * @return    status code
 *            - 0 success
 *            - 1 set full scale failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_full_scale(qmc5883l_handle_t *handle, qmc5883l_full_scale_t scale)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(3 << 4);                                                                            /* clear settings */
    prev |= scale << 4;                                                                           /* set scale */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get the full scale
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *scale points to a full scale buffer
 * @return     status code
 *             - 0 success
 *             - 1 get full scale failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_full_scale(qmc5883l_handle_t *handle, qmc5883l_full_scale_t *scale)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *scale = (qmc5883l_full_scale_t)((prev >> 4) & 0x3);                                          /* get scale */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     set the over sample
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] sample is the over sample
 * @return    status code
 *            - 0 success
 *            - 1 set over sample failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_over_sample(qmc5883l_handle_t *handle, qmc5883l_over_sample_t sample)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(3 << 6);                                                                            /* clear settings */
    prev |= sample << 6;                                                                          /* set sample */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get the over sample
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *sample points to an over sample buffer
 * @return     status code
 *             - 0 success
 *             - 1 get over sample failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_over_sample(qmc5883l_handle_t *handle, qmc5883l_over_sample_t *sample)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *sample = (qmc5883l_over_sample_t)((prev >> 6) & 0x3);                                        /* get sample */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable interrupt
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_interrupt(qmc5883l_handle_t *handle, qmc5883l_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(1 << 0);                                                                            /* clear settings */
    prev |= (!enable) << 0;                                                                       /* set bool */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get interrupt status
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_interrupt(qmc5883l_handle_t *handle, qmc5883l_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *enable = (qmc5883l_bool_t)(!(prev & 0x01));                                                  /* get the bool */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable pointer roll over
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set pointer roll over failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_pointer_roll_over(qmc5883l_handle_t *handle, qmc5883l_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(1 << 6);                                                                            /* clear settings */
    prev |= enable << 6;                                                                          /* set bool */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get pointer roll over status
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pointer roll over failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_pointer_roll_over(qmc5883l_handle_t *handle, qmc5883l_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    *enable = (qmc5883l_bool_t)((prev >> 6) & 0x01);                                              /* get the bool */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     soft reset
 * @param[in] *handle points to a qmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_soft_reset(qmc5883l_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);         /* read control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: read control1.\n");                                        /* read control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(1 << 7);                                                                            /* clear settings */
    prev |= 1 << 7;                                                                               /* set bool */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL2, (uint8_t *)&prev, 1);        /* write control1 */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("qmc5883l: write control1.\n");                                       /* write control1 failed */
        
        return 1;                                                                                 /* return error */
    }
    handle->delay_ms(100);                                                                        /* delay 100ms */
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     set period
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] fbr is the set param
 * @return    status code
 *            - 0 success
 *            - 1 set period failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_period(qmc5883l_handle_t *handle, uint8_t fbr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    prev = fbr;                                                                                 /* set fbr */
    res = handle->iic_write(QMC5883L_ADDRESS, QMC5883L_REG_PERIOD, (uint8_t *)&prev, 1);        /* write period */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("qmc5883l: write period.\n");                                       /* write period failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief      get period
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *fbr points to a param buffer
 * @return     status code
 *             - 0 success
 *             - 1 get period failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_period(qmc5883l_handle_t *handle, uint8_t *fbr)
{
    uint8_t res;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_PERIOD, (uint8_t *)fbr, 1);         /* read period */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("qmc5883l: read period.\n");                                      /* read period failed */
        
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief      read data
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_read(qmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3])
{
    uint8_t res;
    uint8_t prev;
    uint8_t status;
    uint16_t num = 5000;
    uint8_t buf[6];
    float resolution;
    
    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }
    
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_CONTROL1, (uint8_t *)&prev, 1);          /* read control1 */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("qmc5883l: read control1 failed.\n");                                  /* read control1 failed */
        
        return 1;                                                                                  /* return error */
    }
    prev = prev >> 4;                                                                              /* set gain */
    switch (prev)                                                                                  /* choose resolution */
    {
        case 0x00 :
        {
            resolution = 1000.0f / 12000.0f;                                                       /* set resolution 2gauss */
            
            break;                                                                                 /* break */
        }
        case 0x01 :
        {
            resolution = 1000.0f / 3000.0f;                                                        /* set resolution 8gauss */
            
            break;                                                                                 /* break */
        }
        default :                                                                                  /* unknown code */
        {
            resolution = 0.00f;                                                                    /* set resolution 0.00 */
            
            break;                                                                                 /* break */
        }
    }
    while (num != 0)                                                                               /* check num */
    {
        res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_STATUS, (uint8_t *)&status, 1);      /* read status register */
        if (res != 0)                                                                              /* check result */
        {
            handle->debug_print("qmc5883l: read failed.\n");                                       /* read status failed */
            
            return 1;                                                                              /* return error */
        }
        if ((status & 0x01) != 0)                                                                  /* check status */
        {
            break;                                                                                 /* break loop */
        }
        handle->delay_ms(10);                                                                      /* check 10 ms */
        num--;
        if (num == 0)                                                                              /* if timeout */
        {
            handle->debug_print("qmc5883l: ready bit not be set.\n");                              /* timeout */
            
            return 1;                                                                              /* return error */
        }
    }
    res = handle->iic_read(QMC5883L_ADDRESS, QMC5883L_REG_X_LSB, (uint8_t *)buf, 6);               /* read raw data */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("qmc5883l: read data failed.\n");                                      /* read data failed */
        
        return 1;                                                                                  /* return error */
    }
    raw[0] = (int16_t)(((uint16_t)buf[1] << 8) | buf[0]);                                          /* get x raw */
    raw[1] = (int16_t)(((uint16_t)buf[3] << 8) | buf[2]);                                          /* get y raw */
    raw[2] = (int16_t)(((uint16_t)buf[5] << 8) | buf[4]);                                          /* get z raw */
    m_gauss[0] = (float)(raw[0]) * resolution;                                                     /* calculate x */
    m_gauss[1] = (float)(raw[1]) * resolution;                                                     /* calculate y */
    m_gauss[2] = (float)(raw[2]) * resolution;                                                     /* calculate z */
   
    return 0;                                                                                      /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle points to a qmc5883l handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t qmc5883l_set_reg(qmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    } 
    
    return handle->iic_write(QMC5883L_ADDRESS, reg, buf, len);       /* write data */
}

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a qmc5883l handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t qmc5883l_get_reg(qmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    } 
    
    return handle->iic_read(QMC5883L_ADDRESS, reg, buf, len);       /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a qmc5883l info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t qmc5883l_info(qmc5883l_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(qmc5883l_info_t));                       /* initialize qmc5883l info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
