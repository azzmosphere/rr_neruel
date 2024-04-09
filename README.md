# Ryder Robot - Neural Net

NN designed to operate on robot that use Raspberry Pi 4.


## Development

```
cmake -S . -B build
cmake --build build
cmake --build build -t test

```

## Options

- **t** training data

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
