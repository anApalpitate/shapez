# 项目概述

​	本项目是基于shapez(白嫖自epic)编写的魔改版本,实现逻辑经过部分简化或调整,与原游戏存在差异，~~原著党求放过(~~

# 文件夹内容

上传zip文件中包含:

- 源代码文件
- 本说明文档
- 可执行文件

# 环境及安装说明

仅为本人食用方式，与运行关系不大

IDE：QtCreator 12.0.1  / Visual Studio(需要qt相关插件并配置)

Qt版本: 5.15.2

搭建方式: Cmake

> **相关说明**:
>
> 本项目除ui文件以及注释之外内不含中文字符，放心食用
>
> build项目过程中，需要build文件夹与项目在同一目录下(有用到部分相对路径)
>
> 使用源码过程中，需要将Save.txt与MenuInit.txt复制到build的相关目录下

# 玩法讲解

## 基本操作

选择设备后，左键地块放置，右键设备删除，按R旋转设备



## 全局BGM&&GUI

​	MC经典背景音乐   ~~有助于让你越玩越孤独（哭）~~

​	GUI还算炫酷（

## 菜单页

- 开始游戏——创建全新的一局游戏
- 读档——读取文档记录的一局游戏(文件名称为Save.txt)
- 全局商店——进入全局商店

## 地图风格

- 中央是交易中心（2x2）
- 地图上随机刷新三种矿物(铁、钻石、下界合金),三者数目递增，且下界合金总是刷新在距离交易中心较远处
- 右侧工具栏中五种可选择的工具，以及空手模式，同时有存档按钮和进入局内商店的按钮，此外还显示当前的货币和任务的相关信息

## 货币

游戏中有两种货币：硬币和绿宝石

#### 硬币

硬币是局内货币，读档时会读取其数值, 用于在局内商店升级，完成任务与提交任意矿物到交易中心都有相应的硬币奖励

#### 绿宝石

绿宝石是全局货币，其信息会记录在文件内（即永久记录在文件中）,完成任务或者提交下界合金到交易中心可以获得绿宝石奖励

## 任务

- 本游戏采用无尽模式的任务，前3个任务是固定（预设好），第4个任务开始任务内容会随机；
- 任务的奖励随着任务的序号递增;
- 随机任务的目标物品以及目标个数都是范围内随机值；

## 设备类(facility.h/facility.cpp)

*充分体现面向对象机制捏（自己看文件）*

**每个设备都拥有一个输出口，使用时注意输出位置**

### 传送带(1x1):

作用：传送物品

传送带进行了简化，机制改为了只传送当前地块的物品，传送方向为箭头方向

### 垃圾桶(1x1):

作用：销毁当前地块物品

### 采矿机(1x1)：

作用：从矿物地块中采掘矿物相应物品类，同时对刚采掘出来的物品发出移动信号

### 切割机(2x1):

将**铁**切成**铁粒**和**史**(脑洞)

对于不正确的物品不进行切割；

### 堆肥桶(1x1)**（额外添加的设备**）：

将史堆肥，有1%概率产生下界合金(概率可升级)

## 物品类（Item.h/Item.cpp）

*仍旧充分体现面向对象机制捏（bushi*

### 铁

运送到交易中心后增加硬币

从铁矿中采掘出来的item

### 钻石

运送到交易中心后增加硬币

从钻石矿中采掘出来的Item

### 下界合金

运送到交易中心后增加硬币和绿宝石

从下界合金矿中采掘出来的Item

### 铁粒

铁切割后的产物（一次加工物品）

运送到交易中心后增加硬币

### 屎  ~~(描述的是我的代码)~~

铁切割后产生的副产物（一次加工产出）

运送到交易中心后==减少==硬币和绿宝石（需要无害化处理掉捏）

### 物品生命值机制

不同种类的物品会在创建时被赋予一个生命值

对于无所事事的物品，我们将持续扣除其生命值，生命值扣完后即消亡；

对于回归正轨的物品，我们会给其一口回满	~~(正道的光~~

## 全局商店

强化内容

1. 增加各种矿物数目
2. 矿物交易产出双倍
3. 堆肥桶出金~~(下界合金)~~概率暴增        ~~~淘金客的福音~~

## 局内商店

强化内容

1.传送带加速

2.采矿机采掘加速

3.切割机切割加速

每种可以强化3次，第1，2，3次强化需要消耗的硬币数分别为200,500,1000

强化能缩减的时间分别为 10%,30%,50%

## 读档存档

局内存档按钮兼具返回主菜单功能，存档方式为将局内相关信息写进(Save.txt文档)

读档为读取Save.txt的相关信息

# 其他信息

具体见视频
# shapez

