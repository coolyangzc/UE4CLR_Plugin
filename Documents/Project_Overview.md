# 工程概览

### Plugins/UE4CLR

UE4CLR插件，直接复制到UE4项目中使用。

- Runtime： 包含必须的.NET运行时（Win64 - 5.0.7）。
- Source：源代码。

### ManagedCode

托管代码示例文件夹。

- BuildSolution：托管代码的解决方案（详见[BuildSolution.csproj](../Projects/ManagedCode/src/BuildSolution/BuildSolution.csproj)）。
- ManagedLib：托管代码（C#）类库，实现了两个示例函数：`float Square(float x)` 和 `LibArgs FunctionReturnStruct(LibArgs libArgs)`。
- NativeHost：从native code（C++）运行.NET运行时，并测试ManagedLib。

### UE4CLR_Test

测试UE4CLR插件的UE4示例工程。

- Managed/Build：存放编译好的托管代码类库，在本示例中即为ManagedLib.dll与其他相关文件。
- Plugins/UE4CLR：将UE4CLR插件直接复制于此即可。
- Source/UE4CLR_Test/TestUE4CLR：调用UE4CLR插件的类库`UUE4CLRLibrary`并借助其接口调用`ManagedLib`类库的函数，并将结果输出在log与屏幕上。

### UE4CLR_Develop

开发UE4CLR插件时用的工程，基本与UE4CLR_Test相同。