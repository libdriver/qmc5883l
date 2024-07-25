### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(qmc5883l REQUIRED)
```

### 3. QMC5883L

#### 3.1 Command Instruction

1. Show qmc5883l chip and driver information.

   ```shell
   qmc5883l (-i | --information)
   ```

2. Show qmc5883l help.

   ```shell
   qmc5883l (-h | --help)
   ```

3. Show qmc5883l pin connections of the current board.

   ```shell
   qmc5883l (-p | --port)
   ```

4. Run qmc5883l register test.

   ```shell
   qmc5883l (-t reg | --test=reg)
   ```

5. Run qmc5883l read test, num means test times.

   ```shell
   qmc5883l (-t read | --test=read) [--times=<num>]
   ```

6. Run qmc5883l read function, num means read times.

   ```shell
   qmc5883l (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
./qmc5883l -i

qmc5883l: chip is QST QMC5883L.
qmc5883l: manufacturer is QST.
qmc5883l: interface is IIC.
qmc5883l: driver version is 1.0.
qmc5883l: min supply voltage is 2.2V.
qmc5883l: max supply voltage is 3.6V.
qmc5883l: max current is 2.60mA.
qmc5883l: max temperature is 85.0C.
qmc5883l: min temperature is -40.0C.
```

```shell
./qmc5883l -p

qmc5883l: SCL connected to GPIO3(BCM).
qmc5883l: SDA connected to GPIO2(BCM).
```

```shell
./qmc5883l -t reg

qmc5883l: chip is QST QMC5883L.
qmc5883l: manufacturer is QST.
qmc5883l: interface is IIC.
qmc5883l: driver version is 1.0.
qmc5883l: min supply voltage is 2.2V.
qmc5883l: max supply voltage is 3.6V.
qmc5883l: max current is 2.60mA.
qmc5883l: max temperature is 85.0C.
qmc5883l: min temperature is -40.0C.
qmc5883l: start register test.
qmc5883l: qmc5883l_set_mode/qmc5883l_get_mode test.
qmc5883l: set continuous mode.
qmc5883l: check mode ok.
qmc5883l: set standby mode.
qmc5883l: check mode ok.
qmc5883l: qmc5883l_set_output_rate/qmc5883l_get_output_rate test.
qmc5883l: set output rate 10Hz.
qmc5883l: check output rate ok.
qmc5883l: set output rate 50Hz.
qmc5883l: check output rate ok.
qmc5883l: set output rate 100Hz.
qmc5883l: check output rate ok.
qmc5883l: set output rate 200Hz.
qmc5883l: check output rate ok.
qmc5883l: qmc5883l_set_full_scale/qmc5883l_get_full_scale test.
qmc5883l: set 2 gauss.
qmc5883l: check full scale ok.
qmc5883l: set 8 gauss.
qmc5883l: check full scale ok.
qmc5883l: qmc5883l_set_over_sample/qmc5883l_get_over_sample test.
qmc5883l: set over sample 512.
qmc5883l: check over sample ok.
qmc5883l: set over sample 256.
qmc5883l: check over sample ok.
qmc5883l: set over sample 128.
qmc5883l: check over sample ok.
qmc5883l: set over sample 64.
qmc5883l: check over sample ok.
qmc5883l: qmc5883l_set_interrupt/qmc5883l_get_interrupt test.
qmc5883l: enable interrupt.
qmc5883l: check interrupt ok.
qmc5883l: disable interrupt.
qmc5883l: check interrupt ok.
qmc5883l: qmc5883l_set_pointer_roll_over/qmc5883l_get_pointer_roll_over test.
qmc5883l: enable pointer roll over.
qmc5883l: check pointer roll over ok.
qmc5883l: disable pointer roll over.
qmc5883l: check pointer roll over ok.
qmc5883l: qmc5883l_set_period/qmc5883l_get_period test.
qmc5883l: set period 103.
qmc5883l: check period ok.
qmc5883l: qmc5883l_get_status test.
qmc5883l: status is 0x01.
qmc5883l: qmc5883l_soft_reset test.
qmc5883l: soft reset.
qmc5883l: finished register test.
```

```shell
./qmc5883l -t read --times=3

qmc5883l: chip is QST QMC5883L.
qmc5883l: manufacturer is QST.
qmc5883l: interface is IIC.
qmc5883l: driver version is 1.0.
qmc5883l: min supply voltage is 2.2V.
qmc5883l: max supply voltage is 3.6V.
qmc5883l: max current is 2.60mA.
qmc5883l: max temperature is 85.0C.
qmc5883l: min temperature is -40.0C.
qmc5883l: 2gauss full scale test.
qmc5883l: read x 494.75 m_gauss.
qmc5883l: read y -260.42 m_gauss.
qmc5883l: read z 332.67 m_gauss.
qmc5883l: temperature 22.47C.
qmc5883l: read x 495.42 m_gauss.
qmc5883l: read y -258.08 m_gauss.
qmc5883l: read z 331.83 m_gauss.
qmc5883l: temperature 22.54C.
qmc5883l: read x 490.58 m_gauss.
qmc5883l: read y -260.42 m_gauss.
qmc5883l: read z 333.08 m_gauss.
qmc5883l: temperature 22.54C.
qmc5883l: 8gauss full scale test.
qmc5883l: read x 498.67 m_gauss.
qmc5883l: read y -256.67 m_gauss.
qmc5883l: read z 338.33 m_gauss.
qmc5883l: temperature 22.49C.
qmc5883l: read x 492.00 m_gauss.
qmc5883l: read y -262.33 m_gauss.
qmc5883l: read z 332.33 m_gauss.
qmc5883l: temperature 22.49C.
qmc5883l: read x 496.00 m_gauss.
qmc5883l: read y -264.00 m_gauss.
qmc5883l: read z 335.00 m_gauss.
qmc5883l: temperature 22.47C.
qmc5883l: finish read test.
```

```shell
./qmc5883l -e read --times=3

1/3
x is 246.833 m_gauss.
y is -85.833 m_gauss.
z is 124.167 m_gauss.
2/3
x is 248.083 m_gauss.
y is -87.500 m_gauss.
z is 126.667 m_gauss.
3/3
x is 248.083 m_gauss.
y is -84.167 m_gauss.
z is 126.667 m_gauss.
```

```shell
./qmc5883l -h

Usage:
  qmc5883l (-i | --information)
  qmc5883l (-h | --help)
  qmc5883l (-p | --port)
  qmc5883l (-t reg | --test=reg)
  qmc5883l (-t read | --test=read) [--times=<num>]
  qmc5883l (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>
                                 Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

