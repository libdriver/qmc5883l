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
 * @file      driver_qmc5883l_read_test.c
 * @brief     driver qmc5883l read test source file
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

#include "driver_qmc5883l_read_test.h"

static qmc5883l_handle_t gs_handle;        /**< qmc5883l handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t qmc5883l_read_test(uint32_t times)
{
    uint8_t res; 
    uint32_t i;
    int16_t raw[3];
    float m_gauss[3];
    int16_t raw_deg;
    float deg;
    qmc5883l_info_t info;
    
    /* link interface function */
    DRIVER_QMC5883L_LINK_INIT(&gs_handle, qmc5883l_handle_t);
    DRIVER_QMC5883L_LINK_IIC_INIT(&gs_handle, qmc5883l_interface_iic_init);
    DRIVER_QMC5883L_LINK_IIC_DEINIT(&gs_handle, qmc5883l_interface_iic_deinit);
    DRIVER_QMC5883L_LINK_IIC_READ(&gs_handle, qmc5883l_interface_iic_read);
    DRIVER_QMC5883L_LINK_IIC_WRITE(&gs_handle, qmc5883l_interface_iic_write);
    DRIVER_QMC5883L_LINK_DELAY_MS(&gs_handle, qmc5883l_interface_delay_ms);
    DRIVER_QMC5883L_LINK_DEBUG_PRINT(&gs_handle, qmc5883l_interface_debug_print);
    
    /* get qmc5883l info */
    res = qmc5883l_info(&info);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip information */
        qmc5883l_interface_debug_print("qmc5883l: chip is %s.\n", info.chip_name);
        qmc5883l_interface_debug_print("qmc5883l: manufacturer is %s.\n", info.manufacturer_name);
        qmc5883l_interface_debug_print("qmc5883l: interface is %s.\n", info.interface);
        qmc5883l_interface_debug_print("qmc5883l: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        qmc5883l_interface_debug_print("qmc5883l: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        qmc5883l_interface_debug_print("qmc5883l: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        qmc5883l_interface_debug_print("qmc5883l: max current is %0.2fmA.\n", info.max_current_ma);
        qmc5883l_interface_debug_print("qmc5883l: max temperature is %0.1fC.\n", info.temperature_max);
        qmc5883l_interface_debug_print("qmc5883l: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* qmc5883l init */
    res = qmc5883l_init(&gs_handle);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: init failed.\n");
       
        return 1;
    }
    
    /* set output rate 10Hz */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_OUTPUT_RATE_10HZ);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set full scale 2gauss */
    res = qmc5883l_set_full_scale(&gs_handle, QMC5883L_FULL_SCALE_2GAUSS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set over sample 512 */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_OVER_SAMPLE_512);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable interrupt */
    res = qmc5883l_set_interrupt(&gs_handle, QMC5883L_BOOL_FALSE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable pointer roll over */
    res = qmc5883l_set_pointer_roll_over(&gs_handle, QMC5883L_BOOL_TRUE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 0x01 */
    res = qmc5883l_set_period(&gs_handle, 0x01);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set period failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set continuous mode */
    res = qmc5883l_set_mode(&gs_handle, QMC5883L_MODE_CONTINUOUS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }

    /* output */
    qmc5883l_interface_debug_print("qmc5883l: 2gauss full scale test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        qmc5883l_interface_delay_ms(1000);

        /* read */
        res = qmc5883l_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            qmc5883l_interface_debug_print("qmc5883l: read failed.\n");
            (void)qmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* read temperature */
        res = qmc5883l_read_temperature(&gs_handle, &raw_deg, &deg);
        if (res != 0)
        {
            qmc5883l_interface_debug_print("qmc5883l: read temperature failed.\n");
            (void)qmc5883l_deinit(&gs_handle);
            
            return 1;
        }
        
        /* print result */
        qmc5883l_interface_debug_print("qmc5883l: read x %.2f m_gauss.\n", m_gauss[0]);
        qmc5883l_interface_debug_print("qmc5883l: read y %.2f m_gauss.\n", m_gauss[1]);
        qmc5883l_interface_debug_print("qmc5883l: read z %.2f m_gauss.\n", m_gauss[2]);
        qmc5883l_interface_debug_print("qmc5883l: temperature %.2fC.\n", deg + 30.0f);
    }
    
    /* set full scale 8gauss */
    res = qmc5883l_set_full_scale(&gs_handle, QMC5883L_FULL_SCALE_8GAUSS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    qmc5883l_interface_debug_print("qmc5883l: 8gauss full scale test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        qmc5883l_interface_delay_ms(1000);

        /* read */
        res = qmc5883l_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            qmc5883l_interface_debug_print("qmc5883l: read failed.\n");
            (void)qmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* read temperature */
        res = qmc5883l_read_temperature(&gs_handle, &raw_deg, &deg);
        if (res != 0)
        {
            qmc5883l_interface_debug_print("qmc5883l: read temperature failed.\n");
            (void)qmc5883l_deinit(&gs_handle);
            
            return 1;
        }
        
        /* print result */
        qmc5883l_interface_debug_print("qmc5883l: read x %.2f m_gauss.\n", m_gauss[0]);
        qmc5883l_interface_debug_print("qmc5883l: read y %.2f m_gauss.\n", m_gauss[1]);
        qmc5883l_interface_debug_print("qmc5883l: read z %.2f m_gauss.\n", m_gauss[2]);
        qmc5883l_interface_debug_print("qmc5883l: temperature %.2fC.\n", deg + 30.0f);
    }
    
    /* finish read test */
    qmc5883l_interface_debug_print("qmc5883l: finish read test.\n");
    (void)qmc5883l_deinit(&gs_handle);
    
    return 0;
}
