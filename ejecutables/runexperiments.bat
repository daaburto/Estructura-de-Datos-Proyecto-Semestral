@echo off
echo ejecutable,tiempo

for /L %%c in (1,1,20) do (
    for %%n in (tests\10\*) do (
        suffix-tree.exe %%n
    )
)