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
| target      | arrya of floats  | expected output.      |

