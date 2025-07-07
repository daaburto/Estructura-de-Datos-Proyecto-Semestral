@echo off
echo ejecutable;tamanoArchivo;tiempo

for /L %%c in (1,1,20) do (
    for %%n in (ejecutables\tests\DNA\*) do (
        boyer-moore.exe %%n
    )
)