# Builds

```bash
make -j$(nproc)                            # testar / iterar — use este no dia a dia
make release USE_LTO_ON_RELEASE=1 -j32     # release
```

Ambos geram `Soulgold.gba`.
