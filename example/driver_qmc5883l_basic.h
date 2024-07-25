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
 * @file      driver_qmc5883l_basic.h
 * @brief     driver qmc5883l basic header file
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

#ifndef DRIVER_QMC5883L_BASIC_H
#define DRIVER_QMC5883L_BASIC_H

#include "driver_qmc5883l_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup qmc5883l_example_driver qmc5883l example driver function
 * @brief    qmc5883l example driver modules
 * @ingroup  qmc5883l_driver
 * @{
 */

/**
 * @brief qmc5883l basic example default definition
 */
#define QMC5883L_BASIC_DEFAULT_PERIOD                   0x01                              /**< 0x01 */
#define QMC5883L_BASIC_DEFAULT_POINTER_ROLL_OVER        QMC5883L_BOOL_TRUE                /**< enable pointer roll over */
#define QMC5883L_BASIC_DEFAULT_INTERRUPT                QMC5883L_BOOL_FALSE               /**< disable interrupt */
#define QMC5883L_BASIC_DEFAULT_OVER_SAMPLE              QMC5883L_OVER_SAMPLE_512          /**< 512 */
#define QMC5883L_BASIC_DEFAULT_FULL_SCALE               QMC5883L_FULL_SCALE_2GAUSS        /**< 2gauss */
#define QMC5883L_BASIC_DEFAULT_OUTPUT_RATE              QMC5883L_OUTPUT_RATE_10HZ         /**< 10Hz */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t qmc5883l_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t qmc5883l_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t qmc5883l_basic_read(float m_gauss[3]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
