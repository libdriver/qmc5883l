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
 * @file      driver_qmc5883l_basic.c
 * @brief     driver qmc5883l basic source file
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

#include "driver_qmc5883l_basic.h"

static qmc5883l_handle_t gs_handle;        /**< qmc5883l handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t qmc5883l_basic_init(void)
{
    uint8_t res;

    /* link interface function */
    DRIVER_QMC5883L_LINK_INIT(&gs_handle, qmc5883l_handle_t);
    DRIVER_QMC5883L_LINK_IIC_INIT(&gs_handle, qmc5883l_interface_iic_init);
    DRIVER_QMC5883L_LINK_IIC_DEINIT(&gs_handle, qmc5883l_interface_iic_deinit);
    DRIVER_QMC5883L_LINK_IIC_READ(&gs_handle, qmc5883l_interface_iic_read);
    DRIVER_QMC5883L_LINK_IIC_WRITE(&gs_handle, qmc5883l_interface_iic_write);
    DRIVER_QMC5883L_LINK_DELAY_MS(&gs_handle, qmc5883l_interface_delay_ms);
    DRIVER_QMC5883L_LINK_DEBUG_PRINT(&gs_handle, qmc5883l_interface_debug_print);

    /* qmc5883l init */
    res = qmc5883l_init(&gs_handle);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: init failed.\n");

        return 1;
    }

    /* set the default period */
    res = qmc5883l_set_period(&gs_handle, QMC5883L_BASIC_DEFAULT_PERIOD);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set period failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default pointer roll over */
    res = qmc5883l_set_pointer_roll_over(&gs_handle, QMC5883L_BASIC_DEFAULT_POINTER_ROLL_OVER);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt */
    res = qmc5883l_set_interrupt(&gs_handle, QMC5883L_BASIC_DEFAULT_INTERRUPT);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default over sample */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_BASIC_DEFAULT_OVER_SAMPLE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default full scale */
    res = qmc5883l_set_full_scale(&gs_handle, QMC5883L_BASIC_DEFAULT_FULL_SCALE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default output rate */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_BASIC_DEFAULT_OUTPUT_RATE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    /* set the default mode */
    res = qmc5883l_set_mode(&gs_handle, QMC5883L_MODE_CONTINUOUS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);

        return 1;
    }

    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t qmc5883l_basic_read(float m_gauss[3])
{
    int16_t raw[3];

    /* read x, y, z data */
    if (qmc5883l_read(&gs_handle, (int16_t *)raw, m_gauss) != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t qmc5883l_basic_deinit(void)
{
    /* close qmc5883l */
    if (qmc5883l_deinit(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}
