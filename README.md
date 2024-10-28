```bash
mkdir build-native
mkdir build-wasm
```

for native:
```bash
cd build-native
cmake ..
cmake --build . --target run
```

for wasm:
```bash
cd build-wasm
emcmake cmake ..
cmake --build . --target run-wasm
```
