@echo off
echo ejecutable,tiempoConstruccion,tiempoEjecucion

for /L %%c in (1,1,1) do (
    for %%n in (tests\50\*) do (
        suffix-tree.exe %%n
    )
)