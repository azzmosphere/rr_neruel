# Ryder Robot - Neural Net

NN designed to operate on robot that use Raspberry Pi 4.

## Running

```
sudo nohup rr-environment 2>&1 /var/log/rr-neruel.log &
```

## Development

Closest I've got to cross compiling for now is to run the following commands on the Raspberry 4 board.


You will need to use some apt-get commands to get this to work

```
sudo apt-get install cmake
sudo apt-get install ./wiringpi_3.2_arm64.deb
sudo apt-get install libeigen3-dev 

cmake -S . -B build
cmake --build build
cmake --build build -t test
cd build
cpack --config CPackConfig.cmake
cpack --config CPackSourceConfig.cmake
lintian rr-neruel_1.0.0-1_arm64.deb


```

determine boardcom numbering

**in1
```
gpio -g write  23 1
gpio -g blink 23
```
working


**in2
```
gpio -g write  24 1
gpio -g blink 24
```

not working

**in3
```
aaron@ryderrobot:~ $ gpio -g write  5 1
aaron@ryderrobot:~ $ gpio -g blink 5
```
working


**in4
```
aaron@ryderrobot:~ $ gpio -g write  6 1
aaron@ryderrobot:~ $ gpio -g blink 6
```

working



The next attempt will be along these lines:

```
# Cross compile for Pi
./scrtps/pi-setup.bash
cd build 
cmake -DCMAKE_TOOLCHAIN_FILE=../raspberry-pi.cmake ..

```

# Raspbery Pi (Pin Layout)



refernce from [Simple Guide to the Raspberry Pi GPIO Header](https://www.raspberrypi-spy.co.uk/2012/06/simple-guide-to-the-rpi-gpio-header-and-pins/)

# GIT HUB

```
gh pr create -a @me -f 
```


# Direcories

| Direcory                    | Description                      |
+:----------------------------|:---------------------------------|
| /opt/rrobot/bin             | location of executable programs  |

## Testing

```
# Appears to work correctly most of the time.
./build/rr-neruel -c ./resources/etc/config.0.yaml -t ./resources/training/training-set.0.json

# Appears not to work,  may need to support more hidden layers.
./build/rr-neruel -c ./resources/etc/config.1.yaml -t ./resources/training/training-set.1.json

# Works with very little training,  extremly simple problem
./build/rr-neruel -c ./resources/etc/config.2.yaml -t ./resources/training/training-set.2.json
```

## Options

- **-c** **--config** \[/absolute/path/to/config.yaml\] config file (absolute path to configuration file)
- **-t** **--tdir** \[/location/of/training/data/\]      training data

```
rr-neruel -c /absolute/path/to/config.yam -t /location/of/training/data/
```

## Training Data Structure

```
[
    {
        "ingress": [ 1, 1, 1, 1, 1, 1, 0 ],
        "target":  [0, 0, 0, 0]
    },

    {
        "ingress": [ 0, 1, 1, 0, 0, 0, 0 ],
        "target":  [0, 0, 0, 1]
    }
]
```

Array Of Objects, each of the objects has the following:

|  Attribite  | Type             | Description           |
|  --------   | ---------------  | ----------            |
| ingress     | array of floats  | array of input nodes  |
| target      | array of floats  | expected output.      |

### Training Set 0

* Training set 1, solves a problem proposed by [a neural network for arduino] (http://robotics.hobbizine.com/arduinoann.html)


### Training Set 1

Uses Big Endian [Endianness] (https://en.wikipedia.org/wiki/Endianness) pairs, and hopes to achieve the xOr results,


```
{
    {
        "ingress": [ 1, 0, 1, 0, 1, 0],
        "target":  [7]
    },
    {
        "ingress": [ 1, 1, 1, 0, 0, 0],
        "target":  [2]
    }
}
```

**ingress** structure can be looked upon as binary pairs, for instance the array ```{1,0,1,0,1,0}``` equates to ```1^0 + 1^0 + 1^0 ``` which resolves as ```1 + 2 + 4 = 7```,  and ```{1, 1, 1, 0, 0, 0}``` resolves as ```1^1 + 1^0 + 0^0``` wich resolves as ```0+2+0 = 2```


## CROSS COMPILE

* setup SSH keys on Pi

```
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa aaron@192.168.1.14
```

# References

* [Simple MLP Backpropagation Artificial Neural Network in C++ (Step by Step)](https://www.codeproject.com/Articles/1237026/Simple-MLP-Backpropagation-Artificial-Neural-Netwo)
* [C++ neural networks from scratch – Pt 2. building an MLP](https://www.lyndonduong.com/mlp-build-cpp/)
* [ML – Neural Network Implementation in C++ From Scratch](https://www.geeksforgeeks.org/ml-neural-network-implementation-in-c-from-scratch/)
* [eigen3_cmake_module](https://github.com/ros2/eigen3_cmake_module)
* [Using Eigen in CMake Projects](https://eigen.tuxfamily.org/dox/TopicCMakeGuide.html)
* [A Step by Step Backpropagation Example](https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/)
* [relearn](https://alexge233.github.io/relearn/)
* [Cross compiling C/C++ from macOS](https://medium.com/@haraldfernengel/cross-compiling-c-c-from-macos-to-raspberry-pi-in-2-easy-steps-23f391a8c63)
* [Cross Compiling With CMake](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html)
* [Deep Q-Learning Tutorial: minDQN](https://towardsdatascience.com/deep-q-learning-tutorial-mindqn-2a4c855abffc)
* [Reinforcement Learning](https://www.baeldung.com/cs/reinforcement-learning-neural-network)
* [GPIO Programming: Using the sysfs Interface](https://www.ics.com/blog/gpio-programming-using-sysfs-interface)
* [Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)



# Underwater Drone References:

* [underwater-drone 3D printer model files](https://github.com/guidoschillaci/underwater-drone)
* [Alternative FiFish model](https://www.printables.com/en/model/260372-propeller-protection-for-underwater-drone-fifish-v)
* [DF Robot compatible frame](https://cults3d.com/en/3d-model/various/rahmen-fuer-unterwasser-drohne-chasing-dory-rov)