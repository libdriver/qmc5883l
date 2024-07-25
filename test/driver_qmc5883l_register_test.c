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
 * @file      driver_qmc5883l_register_test.c
 * @brief     driver qmc5883l register test source file
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

#include <stdlib.h>
#include "driver_qmc5883l_register_test.h"

static qmc5883l_handle_t gs_handle;        /**< qmc5883l handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t qmc5883l_register_test(void)
{
    uint8_t res; 
    uint8_t reg;
    uint8_t reg_check;
    qmc5883l_info_t info;
    qmc5883l_mode_t mode;
    qmc5883l_output_rate_t rate;
    qmc5883l_full_scale_t scale;
    qmc5883l_over_sample_t sample;
    qmc5883l_bool_t enable;
    uint8_t status;
    
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
    
    /* start register test */
    qmc5883l_interface_debug_print("qmc5883l: start register test.\n");
    
    /* qmc5883l_set_mode/qmc5883l_get_mode test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_mode/qmc5883l_get_mode test.\n");
    
    /* set continuous mode */
    res = qmc5883l_set_mode(&gs_handle, QMC5883L_MODE_CONTINUOUS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set continuous mode.\n");
    res = qmc5883l_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check mode %s.\n", mode == QMC5883L_MODE_CONTINUOUS ? "ok" : "error");
    
    /* set standby mode */
    res = qmc5883l_set_mode(&gs_handle, QMC5883L_MODE_STANDBY);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set standby mode.\n");
    res = qmc5883l_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get mode failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check mode %s.\n", mode == QMC5883L_MODE_STANDBY ? "ok" : "error");
    
    /* qmc5883l_set_output_rate/qmc5883l_get_output_rate test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_output_rate/qmc5883l_get_output_rate test.\n");
    
    /* set output rate 10Hz */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_OUTPUT_RATE_10HZ);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set output rate 10Hz.\n");
    res = qmc5883l_get_output_rate(&gs_handle, &rate);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check output rate %s.\n", rate == QMC5883L_OUTPUT_RATE_10HZ ? "ok" : "error");
    
    /* set output rate 50Hz */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_OUTPUT_RATE_50HZ);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set output rate 50Hz.\n");
    res = qmc5883l_get_output_rate(&gs_handle, &rate);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check output rate %s.\n", rate == QMC5883L_OUTPUT_RATE_50HZ ? "ok" : "error");
    
    /* set output rate 100Hz */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_OUTPUT_RATE_100HZ);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set output rate 100Hz.\n");
    res = qmc5883l_get_output_rate(&gs_handle, &rate);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check output rate %s.\n", rate == QMC5883L_OUTPUT_RATE_100HZ ? "ok" : "error");
    
    /* set output rate 200Hz */
    res = qmc5883l_set_output_rate(&gs_handle, QMC5883L_OUTPUT_RATE_200HZ);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set output rate 200Hz.\n");
    res = qmc5883l_get_output_rate(&gs_handle, &rate);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get output rate failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check output rate %s.\n", rate == QMC5883L_OUTPUT_RATE_200HZ ? "ok" : "error");
    
    /* qmc5883l_set_full_scale/qmc5883l_get_full_scale test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_full_scale/qmc5883l_get_full_scale test.\n");
    
    /* set 2 gauss */
    res = qmc5883l_set_full_scale(&gs_handle, QMC5883L_FULL_SCALE_2GAUSS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set 2 gauss.\n");
    res = qmc5883l_get_full_scale(&gs_handle, &scale);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check full scale %s.\n", scale == QMC5883L_FULL_SCALE_2GAUSS ? "ok" : "error");
    
    /* set 8 gauss */
    res = qmc5883l_set_full_scale(&gs_handle, QMC5883L_FULL_SCALE_8GAUSS);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set 8 gauss.\n");
    res = qmc5883l_get_full_scale(&gs_handle, &scale);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get full scale failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check full scale %s.\n", scale == QMC5883L_FULL_SCALE_8GAUSS ? "ok" : "error");
    
    /* qmc5883l_set_over_sample/qmc5883l_get_over_sample test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_over_sample/qmc5883l_get_over_sample test.\n");
    
    /* set over sample 512 */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_OVER_SAMPLE_512);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set over sample 512.\n");
    res = qmc5883l_get_over_sample(&gs_handle, &sample);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check over sample %s.\n", sample == QMC5883L_OVER_SAMPLE_512 ? "ok" : "error");
    
    /* set over sample 256 */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_OVER_SAMPLE_256);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set over sample 256.\n");
    res = qmc5883l_get_over_sample(&gs_handle, &sample);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check over sample %s.\n", sample == QMC5883L_OVER_SAMPLE_256 ? "ok" : "error");
    
    /* set over sample 128 */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_OVER_SAMPLE_128);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set over sample 128.\n");
    res = qmc5883l_get_over_sample(&gs_handle, &sample);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check over sample %s.\n", sample == QMC5883L_OVER_SAMPLE_128 ? "ok" : "error");
    
    /* set over sample 64 */
    res = qmc5883l_set_over_sample(&gs_handle, QMC5883L_OVER_SAMPLE_64);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set over sample 64.\n");
    res = qmc5883l_get_over_sample(&gs_handle, &sample);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get over sample failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check over sample %s.\n", sample == QMC5883L_OVER_SAMPLE_64 ? "ok" : "error");
    
    /* qmc5883l_set_interrupt/qmc5883l_get_interrupt test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_interrupt/qmc5883l_get_interrupt test.\n");
    
    /* enable interrupt */
    res = qmc5883l_set_interrupt(&gs_handle, QMC5883L_BOOL_TRUE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: enable interrupt.\n");
    res = qmc5883l_get_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check interrupt %s.\n", enable == QMC5883L_BOOL_TRUE ? "ok" : "error");
    
    /* disable interrupt */
    res = qmc5883l_set_interrupt(&gs_handle, QMC5883L_BOOL_FALSE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: disable interrupt.\n");
    res = qmc5883l_get_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get interrupt failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check interrupt %s.\n", enable == QMC5883L_BOOL_FALSE ? "ok" : "error");
    
    /* qmc5883l_set_pointer_roll_over/qmc5883l_get_pointer_roll_over test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_pointer_roll_over/qmc5883l_get_pointer_roll_over test.\n");
    
    /* enable pointer roll over */
    res = qmc5883l_set_pointer_roll_over(&gs_handle, QMC5883L_BOOL_TRUE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: enable pointer roll over.\n");
    res = qmc5883l_get_pointer_roll_over(&gs_handle, &enable);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check pointer roll over %s.\n", enable == QMC5883L_BOOL_TRUE ? "ok" : "error");
    
    /* disable pointer roll over */
    res = qmc5883l_set_pointer_roll_over(&gs_handle, QMC5883L_BOOL_FALSE);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: disable pointer roll over.\n");
    res = qmc5883l_get_pointer_roll_over(&gs_handle, &enable);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get pointer roll over failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check pointer roll over %s.\n", enable == QMC5883L_BOOL_FALSE ? "ok" : "error");
    
    /* qmc5883l_set_period/qmc5883l_get_period test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_set_period/qmc5883l_get_period test.\n");
    
    reg = rand() % 256;
    res = qmc5883l_set_period(&gs_handle, reg);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: set period failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: set period %d.\n", reg);
    res = qmc5883l_get_period(&gs_handle, &reg_check);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get period failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: check period %s.\n", reg == reg_check ? "ok" : "error");
    
    /* qmc5883l_get_status test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_get_status test.\n");
    
    res = qmc5883l_get_status(&gs_handle, &status);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: get status failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: status is 0x%02X.\n", status);
    
    /* qmc5883l_soft_reset test */
    qmc5883l_interface_debug_print("qmc5883l: qmc5883l_soft_reset test.\n");
    
    /* soft reset */
    res = qmc5883l_soft_reset(&gs_handle);
    if (res != 0)
    {
        qmc5883l_interface_debug_print("qmc5883l: soft reset failed.\n");
        (void)qmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: soft reset.\n");
    
    /* finished register test */
    qmc5883l_interface_debug_print("qmc5883l: finished register test.\n");
    (void)qmc5883l_deinit(&gs_handle);
    
    return 0;
}
