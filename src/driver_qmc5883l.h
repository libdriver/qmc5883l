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
 * @file      driver_qmc5883l.h
 * @brief     driver qmc5883l header file
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

#ifndef DRIVER_QMC5883L_H
#define DRIVER_QMC5883L_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup qmc5883l_driver qmc5883l driver function
 * @brief    qmc5883l driver modules
 * @{
 */

/**
 * @addtogroup qmc5883l_base_driver
 * @{
 */

/**
 * @brief qmc5883l bool enumeration definition
 */
typedef enum
{
    QMC5883L_BOOL_FALSE = 0x00,        /**< false */
    QMC5883L_BOOL_TRUE  = 0x01,        /**< true */
} qmc5883l_bool_t;

/**
 * @brief qmc5883l status enumeration definition
 */
typedef enum
{
    QMC5883L_STATUS_DOR  = (1 << 2),        /**< data skip */
    QMC5883L_STATUS_OVL  = (1 << 1),        /**< out of range */
    QMC5883L_STATUS_DRDY = (1 << 0),        /**< data ready */
} qmc5883l_status_t;

/**
 * @brief qmc5883l mode enumeration definition
 */
typedef enum
{
    QMC5883L_MODE_STANDBY    = 0x00,        /**< standby mode */
    QMC5883L_MODE_CONTINUOUS = 0x01,        /**< continuous mode */
} qmc5883l_mode_t;

/**
 * @brief qmc5883l output rate enumeration definition
 */
typedef enum
{
    QMC5883L_OUTPUT_RATE_10HZ  = 0x00,        /**< 10Hz */
    QMC5883L_OUTPUT_RATE_50HZ  = 0x01,        /**< 50Hz */
    QMC5883L_OUTPUT_RATE_100HZ = 0x02,        /**< 100Hz */
    QMC5883L_OUTPUT_RATE_200HZ = 0x03,        /**< 200Hz */
} qmc5883l_output_rate_t;

/**
 * @brief qmc5883l full scale enumeration definition
 */
typedef enum
{
    QMC5883L_FULL_SCALE_2GAUSS = 0x00,        /**< 2gauss */
    QMC5883L_FULL_SCALE_8GAUSS = 0x01,        /**< 8gauss */
} qmc5883l_full_scale_t;

/**
 * @brief qmc5883l over sample enumeration definition
 */
typedef enum
{
    QMC5883L_OVER_SAMPLE_512 = 0x00,        /**< 512 */
    QMC5883L_OVER_SAMPLE_256 = 0x01,        /**< 256 */
    QMC5883L_OVER_SAMPLE_128 = 0x02,        /**< 128 */
    QMC5883L_OVER_SAMPLE_64  = 0x03,        /**< 64 */
} qmc5883l_over_sample_t;

/**
 * @brief qmc5883l handle structure definition
 */
typedef struct qmc5883l_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} qmc5883l_handle_t;

/**
 * @brief qmc5883l information structure definition
 */
typedef struct qmc5883l_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} qmc5883l_info_t;

/**
 * @}
 */

/**
 * @defgroup qmc5883l_link_driver qmc5883l link driver function
 * @brief    qmc5883l link driver modules
 * @ingroup  qmc5883l_driver
 * @{
 */

/**
 * @brief     initialize qmc5883l_handle_t structure
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] STRUCTURE is qmc5883l_handle_t
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a qmc5883l handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_QMC5883L_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup qmc5883l_base_driver qmc5883l base driver function
 * @brief    qmc5883l base driver modules
 * @ingroup  qmc5883l_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a qmc5883l info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t qmc5883l_info(qmc5883l_info_t *info);

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
uint8_t qmc5883l_init(qmc5883l_handle_t *handle);

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
uint8_t qmc5883l_deinit(qmc5883l_handle_t *handle);

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
uint8_t qmc5883l_read(qmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3]);

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
uint8_t qmc5883l_read_temperature(qmc5883l_handle_t *handle, int16_t *raw, float *deg);

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
uint8_t qmc5883l_get_status(qmc5883l_handle_t *handle, uint8_t *status);

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
uint8_t qmc5883l_set_mode(qmc5883l_handle_t *handle, qmc5883l_mode_t mode);

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
uint8_t qmc5883l_get_mode(qmc5883l_handle_t *handle, qmc5883l_mode_t *mode);

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
uint8_t qmc5883l_set_output_rate(qmc5883l_handle_t *handle, qmc5883l_output_rate_t rate);

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
uint8_t qmc5883l_get_output_rate(qmc5883l_handle_t *handle, qmc5883l_output_rate_t *rate);

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
uint8_t qmc5883l_set_full_scale(qmc5883l_handle_t *handle, qmc5883l_full_scale_t scale);

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
uint8_t qmc5883l_get_full_scale(qmc5883l_handle_t *handle, qmc5883l_full_scale_t *scale);

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
uint8_t qmc5883l_set_over_sample(qmc5883l_handle_t *handle, qmc5883l_over_sample_t sample);

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
uint8_t qmc5883l_get_over_sample(qmc5883l_handle_t *handle, qmc5883l_over_sample_t *sample);

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
uint8_t qmc5883l_set_interrupt(qmc5883l_handle_t *handle, qmc5883l_bool_t enable);

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
uint8_t qmc5883l_get_interrupt(qmc5883l_handle_t *handle, qmc5883l_bool_t *enable);

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
uint8_t qmc5883l_set_pointer_roll_over(qmc5883l_handle_t *handle, qmc5883l_bool_t enable);

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
uint8_t qmc5883l_get_pointer_roll_over(qmc5883l_handle_t *handle, qmc5883l_bool_t *enable);

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
uint8_t qmc5883l_soft_reset(qmc5883l_handle_t *handle);

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
uint8_t qmc5883l_set_period(qmc5883l_handle_t *handle, uint8_t fbr);

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
uint8_t qmc5883l_get_period(qmc5883l_handle_t *handle, uint8_t *fbr);

/**
 * @}
 */

/**
 * @defgroup qmc5883l_extend_driver qmc5883l extend driver function
 * @brief    qmc5883l extend driver modules
 * @ingroup  qmc5883l_driver
 * @{
 */

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
uint8_t qmc5883l_set_reg(qmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t qmc5883l_get_reg(qmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif
