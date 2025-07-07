@echo off
echo ejecutable;tamanoArchivo;tiempo

for /L %%c in (1,1,30) do (
    for %%n in (ejecutables\tests\test.txt ejecutables\tests\test2.txt ejecutables\tests\test3.txt) do (
        boyer-moore.exe %%n
    )
)