# UE4CLR: An example plugin natively starts the .NET Core runtime for Unreal Engine 4

UE4CLR is an example plugin which natively starts the .NET Core runtime for Unreal Engine 4. It is inspired by and learned from [UnrealCLR](https://github.com/nxrighthere/UnrealCLR) and Microsoft's [Sample .NET Core Hosts](https://github.com/dotnet/samples/tree/main/core/hosting), and it keeps the minimal code to enable UE4 to call into a managed static method for learning purpose.

<br/>

UE4CLR是一个简单的UE4样例插件，通过启用.NET主机来实现在Unreal引擎中直接调用其它托管代码 (managed code，如C#)中的静态方法。

目前仅支持Win64平台；通过测试的.NET版本为5.0.7，但应可在.NET Core 3.0与以上版本运行。

实现上主要参考了[UnrealCLR](https://github.com/nxrighthere/UnrealCLR)与微软的[.NET Core Hosts样例](https://github.com/dotnet/samples/tree/main/core/hosting)，只保留了必须的部分并使代码尽量简单，以供个人学习与他人上手所用。

<br/>

## 文档链接

[工程概览](./Documents/Project_Overview.md)

[代码详解与运行效果](./Documents/Code_Description.md)

- [ManagedCode](./Documents/Code_Description.md#managedcode)
- [Plugins/UE4CLR](./Documents/Code_Description.md#ue4clr)
- [UE4CLR_Test](./Documents/Code_Description.md#ue4clr_test)

[参考文档与项目](./Documents/References.md)

