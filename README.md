# code-inspector

Inspects an LLVM bitcode file to extract function plus basic block (BB) metadata, as well as inter-procedural control-flow graphs (iCFG), and writes the results to a JSON file.

## Requirements

- [LLVM 12](https://llvm.org/)
- [SVF 2.2](https://github.com/SVF-tools/SVF)
- CMake >= 3.16
- A C++17-capable compiler

## Getting Started

### Dev Container

The easiest way to get started is via the included [Dev Container](https://containers.visualstudio.com/). It sets up all dependencies (LLVM 12, SVF 2.2) automatically.

1. Open the repository in VS Code.
2. When prompted, click **Reopen in Container** (or run the *Dev Containers: Reopen in Container* command).
3. CMake Tools will configure the project automatically using the settings in `.devcontainer/devcontainer.json`.

### Manual Build

```bash
cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_DIR=/usr/lib/llvm-12/lib/cmake/llvm \
    -DSVF_DIR=/opt/svf-2.2

cmake --build build --parallel
```

For a debug build, replace `Release` with `Debug`.

## Usage

The input bitcode file must be compiled with debug information (`-g`). For whole-program bitcode from real-world projects, use [gllvm](https://github.com/SRI-CSL/gllvm).

Analyze a bitcode file and write function and BB metadata to a JSON file:

```bash
./build/code-inspector input.bc output.json
```

Include the iCFG in the output:

```bash
./build/code-inspector --icfg input.bc output.json
```

When `--icfg` is used, the JSON output includes an additional `iCFG` array where each entry maps a source BB ID (`src`) to a list of successor BB IDs (`dst`).

> **Note:** The `LoC` field in the output counts the number of source lines spanned by each function or BB.

### Example Output

```bash
./build/code-inspector --icfg data/test_files/bitcode/quicksort.bc output.json
```

`output.json`:

```json
{
    "functions": [
        ...,
        {
            "name": "quickSort",
            "location": {
                "filename": "quicksort.c",
                "line": { "start": 40, "end": 53 },
                "reachable_from_main": true
            },
            "LoC": 7,
            "basic_blocks": [
                {
                    "id": 8,
                    "location": { "line": { "start": 40, "end": 41 } },
                    "LoC": 2
                },
                {
                    "id": 9,
                    "location": { "line": { "start": 45, "end": 52 } },
                    "LoC": 4
                },
                {
                    "id": 10,
                    "location": { "line": { "start": 53, "end": 53 } },
                    "LoC": 1
                }
            ]
        },
        ...
    ],
    "iCFG": [
        { "src": 8,  "dst": [8, 9, 10]    },
        { "src": 9,  "dst": [1, 8, 9, 10] },
        { "src": 10, "dst": [9, 10, 16]   },
        ...
    ]
}
```

## Development

### Checks and Tests

- Run tests:

    ```bash
    cd build && ctest --output-on-failure
    ```

- Format source files:

    ```bash
    find src include -name "*.cpp" -o -name "*.h" | xargs clang-format -i --style=file
    ```

- Run static analysis:

    ```bash
    clang-tidy -p build $(find src include -name "*.cpp" -o -name "*.h")
    ```

### Code Coverage

Configure, build, and run tests with coverage instrumentation enabled:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON \
    -DLLVM_DIR=/usr/lib/llvm-12/lib/cmake/llvm \
    -DSVF_DIR=/opt/svf-2.2

cmake --build build --parallel
cd build && ctest
```
