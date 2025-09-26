# ROS

## 一、前言

使用的ros版本为Noetic版本，基于Ubuntu20.04.6

## 二、ros是什么

- ROS：Robot Operating System
- 包括了四个part：通信机制、开发工具、应用功能、生态系统
- 这种模式旨在提高机器人研发中的软件复用率

### 1.节点(Node) 与 节点管理器(Node Master)

![img](https://i-blog.csdnimg.cn/blog_migrate/e4cf4abf66181a4b6c4d6ccd5ff8c5e9.png#pic_center)

### 2.通信模式之一——Topic模式

![img](https://i-blog.csdnimg.cn/blog_migrate/6b5151a88a7d50ae4b4ac6e995fbe274.png#pic_center)

- Message：定义数据的类型，具有一定的数据结构定义
- 单向的，可多次
- 数据的管道称为Topic（话题）
- 使用 发布&订阅 模型，右下图显示了Camera Node是发布者，图像处理节点和图像显示节点是订阅者。
- 话题的消息的接口使用 .msg 文件定义

### 3通信模式之二——Service模式

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/5526214ed935d789e03d828b463f0ad4.png#pic_center)

- C/S模型
- 带有反馈的机制
- 双向的，来往一次
- 如左下图，图像处理节点向Camera节点发出请求（比如上调图像分辨率），Camera节点上调分辨率后向图像处理节点发出反馈。
- 服务的数据内容可用 .srv 自定义

### 4.两者对比

![img](https://i-blog.csdnimg.cn/blog_migrate/5797a3624420670cdd2c0962a3a6efcb.png#pic_center)

### 参数(Parameter)

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/a43896255ea289882e9ec61987f5cf2f.png#pic_center)

- 参数是一个“字典”
- 存储在ROS Master服务器，节点可以对参数存储、检索、更新（如图）
- 适合静态存储、非二进制

## 三、文件系统

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/f92abef3679ce9fee72cd879d885ff98.png#pic_center)

- 文件系统代表了代码的结构

## 四、ROS命令行工具

###  1.回顾第一个小海龟程序

打开小海龟程序：
 终端，启动ROS Master：

```powershell
roscore
```

终端2，启动小海龟仿真器：
 （输入`rosrun turtlesim`，敲两下`Tab`健可查看该命令下有哪些功能）

```powershell
rosrun turtlesim turtlesim_node
```

终端3，启动海龟控制节点：

```powershell
rosrun turtlesim turtle_teleop_key
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/697323cffea407d3f72f3cdaee58a02a.png#pic_center)

### 2.查看系统中的计算图：rqt_graph

新建终端窗口：

```powershell
rqt_graph
```

可展示系统中运行的计算图：
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/99b2537f738a69cc0a22ab5e3a82acbc.png#pic_center)可以清晰地了解系统节点间通信的部分信息。
 teleop_turtle节点（键盘控制节点）通过cmd_vel（[topic](https://so.csdn.net/so/search?q=topic&spm=1001.2101.3001.7020)）向turtlesim节点（海归仿真器节点）发出消息，使得小海龟移动。

### 3.rosnode

#### 显示节点列表：rosnode list

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/925ad456811072eabab0b16e704def72.png#pic_center)可以看到有3个节点。

#### 查看节点信息：rosnode info

查看节点的具体信息：`rosnode info /节点名`
 我们查看海龟仿真器节点/turtlesim的信息：
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/6f3eb2ad18e3173f7adc066991ce6d41.png#pic_center)
 可以看到海龟仿真器节点/turtlesim自己有一些发布和订阅，也有一些服务。

### 4.rostopic

#### 显示topic列表：rostopic list

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/ab34938183af1424055c4a3c20159ea7.png#pic_center)

#### 手动发布数据给topic

我们来手动发布数据给topic来控制海龟移动，使用`rostopic pub`
 上图我们看到小海龟是通过/cmd_vel这个topic进行发布信息而移动的，这次我们通过手动publish数据给这个topic来控制小海龟移动。
 格式：`rostopic pub (参数) 话题名 消息数据结构 “具体数据”`
 例，我们输入：（我们可以使用Tab键让我们自动填充数据，使用方向键←→移动到指定位置修改数据，比如我们把x的0.0改成了1.0）

```powershell
rostopic pub /turtle1/cmd_vel geometry_msgs/Twist "linear:
  x: 1.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0"
```

小海龟沿着正前方向移动了1单位，我们再使用参数`-r 5`移动5次，小海龟就撞上了南墙。
 Ctrl+C就可以终止。
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/000001a66bd5d198841ecc3c559f628b.png#pic_center)

### 5.rosmsg

#### 查看消息数据结构

上例我们使用了**消息数据结构**定义了一个消息传给topic，我们可以查看有哪些消息数据结构。
 查看消息数据结构使用：rosmsg show …
 在输入过程中，我们可以勤使用Tab键查看或填充内容。
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/a446daca224d4bc77e761ef2692c3a45.png#pic_center)我们可以看到geometry_msgs/Twist数据结构的内容。

### 6.使用服务[通信方式](https://so.csdn.net/so/search?q=通信方式&spm=1001.2101.3001.7020)：rosservice

上例我们使用了向topic传msg来控制节点，这次我们试试第二种通信方式service。

#### 查看服务列表：rosservice list

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/32719771b899013c1c6ac95849ddcdb5.png#pic_center)

#### 手动通过服务来进行操作

这次我们通过人工产生服务（service）来诞生一只新海龟，使用rosservice call /spawn …
 在服务列表中，有个/spawn服务，可以产生一只新的海龟。
 格式：`rosservice call (参数) 服务名 “具体数据”`
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/db80ee57a72b73228a2a1050d5cb6ed9.png#pic_center)
 这时我们再输入`rostopic list`，可以看到turtle2已经在topic里了。

### 7.话题记录和复现：rosbag

试想我们尝试让海龟以我们指定的路径移动了一回，我们想要把它 记录下来，拷贝到自己的实验室再复现出来，我们就可以使用话题记录功能。
 常用命令：`rosbag record -a -O 文件名`
 比如我们使用之前打开的键盘操作器让海龟移动一圈并记录下来：
 （1）打开新终端输入`rosbag record -a -O cmd_record`
 这样就开始记录了：
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/8c34c3e8ba55b97fef872094a0e9967e.png#pic_center)（2）移动一下：
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/d4a97523dd1e02ba3d9f3de572cc0ddd.png#pic_center)到记录界面按Ctrl+C停止：
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/ab9d48b8d0bb0f1958b197bcc8102c3f.png#pic_center)文件就记录在了这里：![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/02513d9713deb389df68bf2e412308d9.png#pic_center)
 （3）接下去关闭所有打开的ros节点
 重新开启roscore，开启海龟节点rosrun turtlesim turtlesim_node
 这时我们输入 `rosbag play cmd_record`就可以复现之前的移动啦！
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/f2b14c6c527a5afe88585f93ceed7931.png#pic_center)

## 五、创建ros工作空间与功能包

###  1.What is Workspace(工作空间)

工作空间（Workspace）：存放工程开发相关文件的文件夹。类似一个IDE（例如Pycharm）新建一个工程，就是一个工作空间。包含4个文件夹：

- src：代码空间（Source Space）：放置功能包代码
- build：编译空间（Build Space）：编译过程中产生的中间文件，不用过多关注
- devel：开发空间（Development Space）：放置编译生成的可执行文件、库、脚本
- install：安装空间（Install Space）：存放可执行文件，与上面有一定重复

### 2 .创建工作空间
#### 创建:

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src 		//进入路径
catkin_init_workspace	//创建
```

我们先创建一个src文件夹，然后进入该文件夹
第3行catkin_init_workspace意为将当前文件夹变为工作空间，使其拥有工作空间的属性

注：“~/”意为当前用户名目录；“-p”意为递归创建目录，即直接创建多级目录。
src文件夹即代码空间，**不能自行用别的名称代替**

![img](https://i-blog.csdnimg.cn/blog_migrate/295b716b8c61ab30db59a08f20365092.png#pic_center)可以看到创建了这么一个txt文件，说明创建工作空间成功。
#### 编译空代码的工作空间

要编译工作空间，先要回到工作空间的根目录。

```powershell
cd ~/catkin_ws //
catkin_make
```

使用catkin_make为编译指令，将src里的源码进行编译

![img](https://i-blog.csdnimg.cn/blog_migrate/200bc54200a700eaebfd9d1884fc8b08.png#pic_center)

可以看到生成了build和devel两个新文件夹，devel存放了编译完成的内容。
 这里没有生成install文件夹，要生成install文件夹，输入`catkin_make install`：

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/a0d7c51839653be7056a87d3248cea71.png#pic_center)

install中生成了可执行文件。

这样一个空的工作空间创建好了，并且空的代码空间（功能包）编译完成。

### 3.创建功能包

**功能包**是放置ROS源码的最小单元。

上面我们创建了一个空的工作空间，src文件夹里面没写东西，现在我们创建一个自己的功能包。

**注意同一工作空间下，不允许存在同名功能包；不同工作空间下，允许存在同名功能包**。

指令格式：**catkin_create_pkg <package_name> [depend1] [depend2] [depend3]**

<package_name>为包名

[depend]为依赖，即指明编译的时候需要ROS中的其他功能包，如需要调用python、C++库，就要指明rospy、roscpp

```powershell
cd ~/catkin_ws/src
catkin_create_pkg test_pkg std_msgs rospy roscpp
```

创建后记得编译一下。

### 4.设置并检查环境变量

编译完功能包后，为了运行，先[设置环境变量](https://so.csdn.net/so/search?q=设置环境变量&spm=1001.2101.3001.7020)，以便系统找到我们的工作空间和功能包。

```powershell
source ~/catkin_ws/devel/setup.bash
```

检查：

```powershell
echo $ROS_PACKAGE_PATH
```

## 六、发布者Publisher的编程实现

编程publisher 发送 message 产生topic，让海龟（sub）订阅实现功能。

进入src，创建功能包。

```powershell
catkin_create_pkg learning_topic roscpp rospy std_msgs geometry_msgs turtlesim
```

### 如何实现一个发布者程序：

- 初始化ROS节点
- 向ROS Master 注册节点信息，包括话题名和话题数据类型
- 创建消息数据
- 按照一定频率循环发布消息

### 具体操作如下：

- 先在src目录下创建源文件（c++/Python）

- 编写程序，修改cmakelist文件，回到工作空间编译并source
- 终端运行roscore，再打开一个终端运行rosrun +功能包下的程序
- 最终能看到小海龟按设定的程序运动

### 具体程序如下：

```c++
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
	// ROS节点初始化
	ros::init(argc, argv, "velocity_publisher");
	// 创建节点句柄
	ros::NodeHandle n;
	// 创建一个Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry_msgs::Twist，队列长度10
	ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

	// 设置循环的频率
	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok())
	{
	    // 初始化geometry_msgs::Twist类型的消息
		geometry_msgs::Twist vel_msg;
		vel_msg.linear.x = 0.5;
		vel_msg.angular.z = 0.2;
	    // 发布消息
		turtle_vel_pub.publish(vel_msg);
		ROS_INFO("Publsh turtle velocity command[%0.2f m/s, %0.2f rad/s]", vel_msg.linear.x, vel_msg.angular.z);
	    // 按照循环频率延时
	    loop_rate.sleep();
	}
	return 0;
}
```

## 七、订阅者Sub的实现

- 初始化ROS节点
- 订阅需要的话题
- 循环等待话题消息，接收到消息后进入回调函数
- 在回调函数中完成消息处理

操作和上面pub一样

### 程序如下

```c++
#include <geometry_msgs/Twist.h>
#include <ros/init.h>
#include <ros/node_handle.h>
#include <ros/subscriber.h>
#include <turtlesim/Pose.h>
void poseCallback(const turtlesim::Pose::ConstPtr& msg) {
    ROS_INFO("turtle pose : x :%0.6f, y :%0.6f",msg->x,msg->y);
}

int main(int argc, char **argv) {
    //ros初始化
    ros::init(argc, argv, "pose_subscriber");
    //创建节点的句柄
    ros::NodeHandle n ;
    //创建一个Subscriber，订阅名为/turtle/pose,注册回调函数poseCallback
    ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 10 , poseCallback) ;
    //循环等待回调函数
    ros::spin();

    return 0;
}
```

此程序可以读取小海龟的位置







将pub和sub结合起来后的效果就是，海龟沿着设定的运动，然后sub获取他的位置



使用rqt-graph进行查看

![image-20250919211003647](/home/chonqin/.config/Typora/typora-user-images/image-20250919211003647.png)

## 八、话题消息的定义和使用

- Message 是一种自定义的数据结构，用于话题间的数据存储和传输



- 之前两节使用了Topic模型，我们先使用了Twist类型（geometry_msgs.msg库下的Twist类）的Message作为输入指令进行发布，接着使用了Pose类型（Turtlesim.msg库下的Pose类）的Message作为订阅消息进行接收。

    

    使用rosmsg show命令查看

    ![image-20250920110325714](/home/chonqin/.config/Typora/typora-user-images/image-20250920110325714.png)

    以上的**Message**消息都是预定义好的，当我们需要自定义消息该怎么做呢？

如何操作：

- 创建msg文件

    进入功能包目录里，新建msg文件夹，将所有自定义msg文件放入里面

    使用touch命令新建一个msg文件，将定义的东西放入msg中

    ```powershell
    touch Person.msg//P要大写
    ```

    ![image-20250920105335067](/home/chonqin/.config/Typora/typora-user-images/image-20250920105335067.png)

- 在package.xml添加功能包依赖

    将以下两行粘贴进入文件内

```
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```



- 在cmakelist中也要更改编译选项，把自定义msg文件添加到编译环境中

    ```
    find_package( ...... message_generation)
    
    add_message_files(FILES Person.msg)
    generate_messages(DEPENDENCIES std_msgs)
    
    catkin_package( ...... message_runtime)
    ```

    说明如下：

    

    - 因为在package.xml添加了功能包编译依赖，在CMakeList.txt里的find_package中也要加上对应的部分；

    - 需要将定义的Person.msg作为消息接口，针对它做编译；
        需要指明编译这个消息接口需要哪些ROS已有的包；
    - 有了34这两个配置才可将定义的msg编译成不同的程序文件
    - 因为在package.xml添加了功能包执行依赖，在CMakeList.txt里的catkin_package中也要加上对应的部分

- 最后回到工作空间进行编译

## 九、Servce模式的编程与使用

![image-20250920173350676](/home/chonqin/.config/Typora/typora-user-images/image-20250920173350676.png)

Sever端是海龟仿真器节点，Client端是等待实现的节点，产生Request的请求，发送给Sever端。Sever端接受请求后产生一只海龟，并返回Response。中间传输的数据结构为定义好的turtlesim：：Spawn。



- 老样子，创建一个learing_servce的pkg，添加必要的依赖

- 新建一个c++文件，放入src目录下

- 更改cmakelist文件的编译选项，编译文件

- 开启roscore，进行rosrun，实现功能

    ### 程序如下

    ```c++
    int main(int argc, char** argv)
    {
        // 初始化ROS节点
    	ros::init(argc, argv, "turtle_spawn");
    
        // 创建节点句柄
    	ros::NodeHandle node;
    
        // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
    	ros::service::waitForService("/spawn");
    	ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
    
        // 初始化turtlesim::Spawn的请求数据
    	turtlesim::Spawn srv;
    	srv.request.x = 2.0;
    	srv.request.y = 2.0;
    	srv.request.name = "turtle2";
    
        // 请求服务调用
    	ROS_INFO("Call service to spwan turtle[x:%0.6f, y:%0.6f, name:%s]", 
    			 srv.request.x, srv.request.y, srv.request.name.c_str());
    
    	add_turtle.call(srv);
    
    	// 显示服务调用结果
    	ROS_INFO("Spwan turtle successfully [name:%s]", srv.response.name.c_str());
    
    	return 0;
    };
    
    ```

    ![image-20250920165919601](/home/chonqin/.config/Typora/typora-user-images/image-20250920165919601.png)

启动turle_spawn后，可以看到先是等待service应答

随后开启turtlrsim节点后，服务应答，就在对应位置添加了一个新的小海龟

![image-20250920170115886](/home/chonqin/.config/Typora/typora-user-images/image-20250920170115886.png)

## 十、服务端Sever的编程实现

![image-20250920174015847](/home/chonqin/.config/Typora/typora-user-images/image-20250920174015847.png)

Server端本身是进行模拟海龟运动的命令端，它的实现是通过给海龟发送速度（Twist）的指令，来控制海龟运动（本身通过Topic实现）。

Client端相当于海龟运动的开关，其发布Request来控制Server端。
通过自定义名为 /turtle_command 的Service实现，中间传输消息的数据类型为std_srvs::Trigger（一种针对服务标准std_srvs下的数据定义）来通信。Trigger意为触发，通过Trigger信号来触发Server端的运动指令。
Server端接收这个Trigger信号后，可控制其是否要给海龟发送Twist指令，同时给Client发送Response反馈告诉它海龟的运动状态



![img](https://i-blog.csdnimg.cn/blog_migrate/b71bbe429ce84281c88ef0c910dd78f8.png#pic_center)

开启rosmaster，turtlesim之后

 接着我们使用`rosservice call ...`请求海龟动起来，再打开一个终端。
 （输入完 /turtle_command 后敲个空格再用Tab键可自动填充空指令内容）

```powershell
rosservice call /turtle_command "{}"
```

就可以看到海龟动起来了



## 十一、服务数据srv的使用

在第8节我们讲解了话题消息msg的定义与使用，在第8节的例子中我们曾自定义了一个消息类型“Person”以发布个人信息，Publisher发布个人信息，Subscriber接收个人信息。

这个例子中，Publisher会不断地发信息，Subscriber不停地接数据，一开动就停不下来了，也是topic模式的缺陷。

本节我们使用Service模式用自定义的服务数据srv来实现，我们希望Request一次才发一次信息来显示。

### 创建srv文件

在pkg功能包目录下创建srv文件夹，并使用touch命令生成.srv文件

![image-20250922190659468](/home/chonqin/.config/Typora/typora-user-images/image-20250922190659468.png)

在文件中写入数据结构的内容

```
string name
uint8 sex
uint8 age

uint8 unknown = 0
uint8 male = 1
uint8 female = 2
---
string result
//与之前Person.msg不同的是，多了破折号下面这个Response结果，上面的是Request内容。
//定义好srv数据接口后，就可以根据这个定义用C++或Python编译
```

### 添加功能包依赖

由于此srv是自定义的，最初创建的时候没有添加依赖，所以要手动修改package.xml文件添加依赖。找到文件，把下面复制进去就好了。

```
<build_depend>message_generation</build_depend>
//添加编译依赖
<exec_depend>message_runtime</exec_depend>
//添加执行依赖
```

### 添加编译选项

打开CMakeLists.txt，添加编译选项，才能顺利的把srv文件编译出来。

大致上为四条，找到对应的部分进行更改即可。

每一部分都有注释在上方进行介绍。

```
find_package( ...... message_generation)

add_service_files(FILES Person.srv)
generate_messages(DEPENDENCIES std_msgs)

catkin_package( ...... message_runtime)

```

还得把自己写的cpp文件添加进去编译

```
add_executable(person_server src/person_server.cpp)
target_link_libraries(person_server ${catkin_LIBRARIES})
add_dependencies(person_server ${PROJECT_NAME}_gencpp)

add_executable(person_client src/person_client.cpp)
target_link_libraries(person_client ${catkin_LIBRARIES})
add_dependencies(person_client ${PROJECT_NAME}_gencpp)
```

第三项是添加依赖项，因为代码涉及到动态生成，我们需要将可执行文件与动态生成的程序产生依赖关系。
**注：这里添加的依赖项用到的是gencpp包，是一个C++用的ROS message 和 service 生成器，以依赖动态生成的cpp文件**。

### 最后，编译并运行

运行rosmaster，及其功能包，不再重复。

可以看到运行Server后，启动Client会发一次人物信息，在Server端看到，看到后反馈给Client确认后终止这次发送行为。
先运行Client的话则会一直等待Server端接收，直到Server端启动接收到信息



## 十二、参数的使用与编程

- 至此我们学习了ROS中的两种核心通信机制：Topic（话题）模式 和 Service（服务）模式。

- Topic中的Publisher、Subscriber，Service中的Client、Server，消息类型msg、srv以及它们的自定义数据类型。 
- 这次讲讲参数的使用

### 简介

在ROS Master中，存在一个参数服务器（Parameter Server），它是一个全局字典，即一个全局变量的存储空间，用来保存各个节点的配置参数。各个节点都可以对参数进行全局访问。

### 创建pkg

```
cd ~/Ros_WorkSpace/src
catkin_create_pkg learning_parameter roscpp rospy std_srvs
```

### rosparam使用

在ROS中，参数文件常以YAML文件的格式保存

![image-20250922194609158](/home/chonqin/.config/Typora/typora-user-images/image-20250922194609158.png)

打开海龟节点后使用list命令看一下：

![image-20250922194738800](/home/chonqin/.config/Typora/typora-user-images/image-20250922194738800.png)

可以使用get命令获取某个参数值

eg：

```
rosparam get /turtlesim/background_b 
```

![image-20250922194923502](/home/chonqin/.config/Typora/typora-user-images/image-20250922194923502.png)

也可以更改这些参数，使用set命令，随后使用get查看到已经更改。

![image-20250922195108210](/home/chonqin/.config/Typora/typora-user-images/image-20250922195108210.png)

但是，实际海龟背景尚未改变，发送一个clear的空内容服务请求。

![image-20250922195238238](/home/chonqin/.config/Typora/typora-user-images/image-20250922195238238.png)

这样子命令行更改有点麻烦，可以导出参数文件，更改后再load回去。

```powershell
rosparam dump param.yaml
//导出参数，并保存为param.yaml文件
```

![image-20250922195757467](/home/chonqin/.config/Typora/typora-user-images/image-20250922195757467.png)

打开后，更改参数然后保存。

![image-20250922195829768](/home/chonqin/.config/Typora/typora-user-images/image-20250922195829768.png)

```powershell
rosparam load param.yaml
```

随后，导入参数，再clear一下，可以看到颜色更改了。

![image-20250922200000961](/home/chonqin/.config/Typora/typora-user-images/image-20250922200000961.png)

其他的命令自己可以尝试。

### 利用程序来使用参数

程序如下

```c++
int main(int argc, char **argv)
{
	int red, green, blue;

    // ROS节点初始化
    ros::init(argc, argv, "parameter_config");

    // 创建节点句柄
    ros::NodeHandle node;

    // 读取背景颜色参数
	ros::param::get("/turtlesim/background_r", red);
	ros::param::get("/turtlesim/background_g", green);
	ros::param::get("/turtlesim/background_b", blue);

	ROS_INFO("Get Backgroud Color[%d, %d, %d]", red, green, blue);

	// 设置背景颜色参数
	ros::param::set("/turtlesim/background_r", 255);
	ros::param::set("/turtlesim/background_g", 255);
	ros::param::set("/turtlesim/background_b", 255);

	ROS_INFO("Set Backgroud Color[255, 255, 255]");

    // 读取背景颜色参数
	ros::param::get("/turtlesim/background_r", red);
	ros::param::get("/turtlesim/background_g", green);
	ros::param::get("/turtlesim/background_b", blue);

	ROS_INFO("Re-get Backgroud Color[%d, %d, %d]", red, green, blue);

	// 调用服务，刷新背景颜色
	ros::service::waitForService("/clear");
	ros::ServiceClient clear_background = node.serviceClient<std_srvs::Empty>("/clear");
	std_srvs::Empty srv;
	clear_background.call(srv);
	
	sleep(1);

    return 0;
}
```

添加cmake编译选项，不再重复。

运行后，更改了。

![image-20250922205135270](/home/chonqin/.config/Typora/typora-user-images/image-20250922205135270.png)

## 十三、launch文件的使用

上文中，启动一个ros节点需要使用rosrun命令，每次启动都有打开一个新的终端，十分麻烦。

通过编写launch文件，将多个节点的内容写入进去，就可以一次性开启多个节点。

- launch文件可以放在任意一个软件包的目录下
- 启动launch文件时自动运行roscore，启动rosmaseter。
- 必须按照launch文件内容的格式进行编写，/为结尾。

```c++
<launch>
		//节点1
        <node pkg="learning_service" type="turtle_spawn" name="turtle_spawn" />
    	//节点2
        <node pkg="turtlesim" type="turtlesim_node" name="turtlesim_node"/>

</launch>
```

在launch文件中，为一个节点添加 **launch-prefix="gnome-terminal-e"**属性，可以让节点单独运行在一个独立终端中。

```c++
<node pkg="learning_service" type="turtle_spawn" name="turtle_spawn" launch-prefix="gnome-terminal-e"/>
```



## 十四、Ros机器人运动控制

在上面的基本实验中，我们掌握了基本的话题消息订阅发布、客户端服务端服务发送。

现在，可以添加机器人仿真环境，利用ros来实验控制机器人运行了。

### 安装机器人仿真环境

打开src目录，下载仿真环境pkg

```
git clone https://github.com/6-robot/wpr_simulation.git
```

运行包内的安装程序

```
cd Ros_WorkSpace/wpr_simulation/scrips
./install_for_noetic.sh
```

安装完成后，回到workspace编译（source和编译再后文中默认进行）

```
roslaunch wpr_simulation wpb_simple.launch
```

可以看到一个仿真界面

### 创建pkg，编写程序实现基本的运动控制

创建vel_pkg并添加roscpp rospy geometry_msgs依赖

添加vel_node函数，内容如下：

```c++
int main(int argc, char **argv) {
    //初始化
    ros::init(argc, argv, "vel_node");
	//创建句柄
    ros::NodeHandle n ;
	//定义发布对象vel_pub
    ros::Publisher vel_pub = 	
    //发布话题，类型是geo内的twist，话题名叫cmd_vel
    n.advertise<geometry_msgs::Twist("/cmd_vel", 10);
	//定义数据类型 
    geometry_msgs::Twist vel_msg;

    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;

    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0.6;
	
    ros::Rate r(30);
    //开启while循环，不断发布消息
    while (ros::ok()) {
        vel_pub.publish(vel_msg);
        r.sleep();
    }
    return 0 ;
}
```

在cmakelist中找到这两个选项，复制并取消注释，里面名字更改成自己的c++文件名

经典操作了，以后不再赘述

![image-20250923123719319](/home/chonqin/.config/Typora/typora-user-images/image-20250923123719319.png)

编译运行后，就可以看到仿真里面的机器人按照你的程序进行运动了。

## 十五、激光雷达

### TOF激光雷达

雷达分为激光发射和接受两个模块，通过激光的发射与接收能测定障碍物的距离，再不断旋转雷达，就能测定周围的环境。

只要激光发射接收频率足够快，旋转速度足够快，就能实时得到周围环境。

而在ros中Rviz，我们得到的是一个激光雷达的点阵图。

![image-20250924114550648](/home/chonqin/.config/Typora/typora-user-images/image-20250924114550648.png)

### Rviz

全名叫做Robot Visualization Tool ，是一个可视化工具。可以可视化传感器的数据，机器人运算处理的中间结果，比如显示路径规划，目标框选。

#### 操作：

- 启动仿真程序后，在终端中输入rviz。![image-20250924115406006](/home/chonqin/.config/Typora/typora-user-images/image-20250924115406006.png)

- 修改左边界面显示，左下角add RobotModel和LaserScan，如图（如果没有机器人模型的话就source一下再打开rviz）

![image-20250924120357814](/home/chonqin/.config/Typora/typora-user-images/image-20250924120357814.png)****

- 这一排红色点阵就是雷达获取的数据，可以在仿真环境中添加障碍物来查看rviz的显示

    ![image-20250924121504960](/home/chonqin/.config/Typora/typora-user-images/image-20250924121504960.png)

- 可以导出此次的配置文件，然后下次打开rviz后再open配置文件。点击左上角的flies目录就可以看到

#### Tips

- rviz只是一个数据可视化界面，用于显示机器人获取的数据，无论他是仿真机器人还是真实的机器人
- 可以通过launch文件来自动配置rviz的参数
- 

#### Ros中激光雷达的消息包格式

在roswiki官网中可以打开sensor_msgs/LaserScan Message，注释翻译成中文



![image-20250924121815175](/home/chonqin/.config/Typora/typora-user-images/image-20250924121815175.png)

可以在终端中显示消息类型

输入rostopic echo /scan --noarr

![image-20250924121950186](/home/chonqin/.config/Typora/typora-user-images/image-20250924121950186.png)

### 用c++实现获取激光雷达

![image-20250924195957070](/home/chonqin/.config/Typora/typora-user-images/image-20250924195957070.png)

- 构建一个新的软件包，包名为lidar_pkg

- 新建一个节点，lidar_node

- 在节点中，向ros大管家nodehandle申请订阅话题，并设置回调函数为lidarcallback（）

- 构建回调函数，接受并处理数据

- 调用ros_info()显示雷达检测到的前方障碍物距离

    

    函数如下：

```c++
void lidar_Callback(const sensor_msgs::LaserScan msg) {
    float fMidDist = msg.ranges[180];
    ROS_INFO("前方测距 ranges[180] = %f 米",fMidDist);
}


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "lidar_node");

    ros::NodeHandle n ;

    ros::Subscriber lidar_sub = n.subscribe("/scan", 10, &lidar_Callback);

    ros::spin ();
    return 0;
}
    
```

编译运行后，再打开仿真工具，移动前方的书架，可以看到距离的变化

![image-20250924205150384](/home/chonqin/.config/Typora/typora-user-images/image-20250924205150384.png)

![image-20250924205207354](/home/chonqin/.config/Typora/typora-user-images/image-20250924205207354.png)

## 十六、实现简单的避障控制

![image-20250924205557332](/home/chonqin/.config/Typora/typora-user-images/image-20250924205557332.png)

在上一节的基础上修改程序就可以了

- 发布速度控制话题/cmd_vel
- 构建速度控制消息包，vel_cmd用于数据传输
- 根据激光雷达的测距值，调整机器人运动速度，避开障碍

```c++
ros::Publisher vel_pub ;
int n = 0;
void lidar_Callback(const sensor_msgs::LaserScan msg) {
    float fMidDist = msg.ranges[180];
    ROS_INFO("前方测距 ranges[180] = %f 米",fMidDist);

    if (n>0) {
        n--;
        return;
    }
    geometry_msgs::Twist vel_cmd;
    if (fMidDist < 1.5) {
        vel_cmd.angular.z = 0.3;
        n=50;
    }
    else {
        vel_cmd.linear.x = 0.1;
    }
    vel_pub.publish(vel_cmd);
  	//如果没有速度的输入，机器人会按照最近一次的速度运动
}


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "lidar_node");

    ros::NodeHandle n ;

    ros::Subscriber lidar_sub = n.subscribe("/scan", 10, &lidar_Callback);

                    vel_pub  = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin ();

    return 0;
}
```

## 十七、Ros中IMU的使用

### Imu Message

![image-20250925105143048](/home/chonqin/.config/Typora/typora-user-images/image-20250925105143048.png)

- angular_veloity ——————x,y,z三轴的旋转速度
- liner——acceleration——————xyz三轴矢量加速度
- orientation——————xyz经处理后的偏移量，数据类型是Quaternion，包含float x，y ，z ，w。四元数描述。

### C++实现imu数据获取

Ros官方给出了三个话题

![image-20250925110052247](/home/chonqin/.config/Typora/typora-user-images/image-20250925110052247.png)

- 六轴原始数据

- 六轴原始数据和融合后的四元数姿态描述

- 加上磁力计的九轴数据

    **Cpp实现步骤**：

- 创建一个新的pkg
- 建立节点，imu_node
- 编程构建imu_node,利用回调函数对imu的数据进行处理

- 使用tf工具转换数据，并屏幕打印

```c++
void IMUCallback(const sensor_msgs::Imu msg)
{
    // 检测消息包中四元数数据是否存在
    if(msg.orientation_covariance[0] < 0)
        return;
    // 四元数转成欧拉角
    tf::Quaternion quaternion(
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w
    );
    double roll, pitch, yaw;
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    // 弧度换算成角度
    roll = roll*180/M_PI;
    pitch = pitch*180/M_PI;
    yaw = yaw*180/M_PI;
    ROS_INFO("滚转= %.0f 俯仰= %.0f 朝向= %.0f", roll, pitch, yaw);
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv, "demo_imu_data");

    ros::NodeHandle n;
    // 订阅 IMU 的数据话题
    ros::Subscriber sub = n.subscribe("imu/data", 100, IMUCallback);
    ros::spin();

    return 0;
}
```

### 实现与运动控制的结合

```c++
ros::Publisher vel_pub ;
// IMU 回调函数
void IMUCallback(const sensor_msgs::Imu msg)
{
    // 检测消息包中四元数数据是否存在
    if(msg.orientation_covariance[0] < 0)
        return;
    // 四元数转成欧拉角
    tf::Quaternion quaternion(
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w
    );
    double roll, pitch, yaw;
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    // 弧度换算成角度
    roll = roll*180/M_PI;
    pitch = pitch*180/M_PI;
    yaw = yaw*180/M_PI;
    ROS_INFO("滚转= %.0f 俯仰= %.0f 朝向= %.0f", roll, pitch, yaw);
		//此处可以设计pid算法
    double t_yaw = 90;
    float kp ,ki ,kd ;
    double error = t_yaw - yaw ;

    geometry_msgs::Twist vel_cmd;
    kp = 0.02 ;
    vel_cmd.angular.z = error *kp ;
    vel_cmd.linear.x = 0.1 ;
    vel_pub.publish(vel_cmd);
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv, "demo_imu_data");

    ros::NodeHandle n;
    // 订阅 IMU 的数据话题
    ros::Subscriber sub = n.subscribe("imu/data", 100, IMUCallback);
        vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
    ros::spin();

    return 0;
}

```

## 十八、栅格地图

假设地图上有两个障碍物，以俯视观察他。将地图用大小相同的方格代替，被占据的格子（哪怕只占据一点）涂上黑色，未被占据的栅格涂上白色。如图

![image-20250925193257940](/home/chonqin/.config/Typora/typora-user-images/image-20250925193257940.png)

**切换栅格的大小可以让障碍物的表示更加精准，理论上可以无限逼近实际的大小**。

![image-20250925193415756](/home/chonqin/.config/Typora/typora-user-images/image-20250925193415756.png)

- 一个小正方形的边长（栅格边长）即为**地图分辨率**。
- 将黑色格子标记为1，空白格子为0，这样整个地图就可以以数组的形式存储数据来表示。

### Ros栅格地图消息的数据结构

![image-20250925193836624](/home/chonqin/.config/Typora/typora-user-images/image-20250925193836624.png)

info的包含如下：

![image-20250925194150699](/home/chonqin/.config/Typora/typora-user-images/image-20250925194150699.png)



### C++编写节点

![image-20250925194447759](/home/chonqin/.config/Typora/typora-user-images/image-20250925194447759.png)

```c++
int main(int argc, char **argv) {
    ros::init(argc,argv,"map_pub_node");
    ros::NodeHandle n ;
    ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("/map",10);

    ros::Rate r(1) ;
    while (ros::ok) {
      	//定义数据类型
        nav_msgs::OccupancyGrid msg ;
      	//设置地图参数
        msg.header.frame_id = "map";
        msg.header.stamp = ros::Time::now();

        msg.info.origin.position.x = 0;
        msg.info.origin.position.y = 0;

        msg.info.resolution = 1.0;
        msg.info.width = 4;
        msg.info.height = 2;

        msg.data.resize(8);//将八个格子的值清0
				//给地图赋值
        msg.data[0] = 100;
        msg.data[1] = 100;
        msg.data[2] = 0;
        msg.data[3] = -1;
				
        pub.publish(msg);
        r.sleep();

    }
    return 0 ;
}
```

启动roscore，启动节点，启动rviz

添加起始点（Axes）和Map，topic选择写好的/map话题。可以看到地图按照我们定义的样子展现出来。

![image-20250925201732674](/home/chonqin/.config/Typora/typora-user-images/image-20250925201732674.png)

```
msg.info.origin.position.x = 2.0;
msg.info.origin.position.y = 1.0;
```

如果更改了上面的数值，他们不再为0，就会出现这样子的情况：

![image-20250925202124104](/home/chonqin/.config/Typora/typora-user-images/image-20250925202124104.png)

## 十九、SLAM

全程是simultaneous localization and mapping，同时定位与地图创建。

**定位**：是指机器人确定自己的位置。

### Slam的原理

如何创建地图呢？？

先选定一个原点作为参照系，建立坐标轴，通过记录当前观测点与对应参照物的坐标，改变不同观测点，将多次记录的坐标进行比对，将参照物重合构建出一张完整的地图。

**在Ros中如何实现建图的功能呢**

首先，Ros是地图是栅格地图，机器人放置在环境中，没有开启传感器感知周围时，所有格子的值均为-1，涂上灰色。

假设此时机器人开启了雷达扫描功能，激光发射出去穿过的格子都标记为0，涂上白色，代表没有障碍物。直到激光撞到障碍物，反射回来，这个格子标记为100，涂上黑色。这样子就能得到当前观测点的周围障碍物情况，改变观测点后，又进行一次扫描，标记出周围的情况。将两次的标记情况进行特征重合，构建出局部的地图。不断重复这个过程，就可以得到一副完整的地图了。

![image-20250926185458750](/home/chonqin/.config/Typora/typora-user-images/image-20250926185458750.png)

### Ros中通过c++实现Slam

![image-20250926185810196](/home/chonqin/.config/Typora/typora-user-images/image-20250926185810196.png)

激光雷达发送数据到slam节点进行处理（建图算法），在发布map话题让rviz可视化界面订阅，就可以显示地图出来了。

Slam算法节点在ros中有提供，叫做Hector_Mapping节点。不用重复造轮子。

![image-20250926200118226](/home/chonqin/.config/Typora/typora-user-images/image-20250926200118226.png)

通过运行前三条指令可以开启slam的扫描功能，在rviz界面中add选项添加机器人model和map地图

![image-20250926201134977](/home/chonqin/.config/Typora/typora-user-images/image-20250926201134977.png)

第四行指令可以开启一个图像化界面来控制机器人运动

![image-20250926201231220](/home/chonqin/.config/Typora/typora-user-images/image-20250926201231220.png)

控制机器人移动，建模成功。

![image-20250926201452881](/home/chonqin/.config/Typora/typora-user-images/image-20250926201452881.png)
