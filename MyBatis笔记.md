## MyBatis

SSM框架中的M

### 1、简介

![image-20240305152409870](image-20240305152409870.png)

* 持久层框架

* 支持定制化SQL存储过程以及高级映射

* 避免了几乎所有jdbc代码以及手动设置参数设置结果集

* 使用简单xml或注解来配置或映射原生类型、接口和java的opjo为数据库中的记录

* 原为apache项目

* 现在迁移到github

  

##### 获取MyBatis？

* maven

  ```xml
  <!-- https://mvnrepository.com/artifact/org.mybatis/mybatis -->
  <dependency>
      <groupId>org.mybatis</groupId>
      <artifactId>mybatis</artifactId>
      <version>3.5.6</version>
  </dependency>
  
  ```

  

* github：

* 中文文档

#### 1.2 持久层

数据持久化

* 将程序数据在持久状态和瞬时状态转化
* 内存：断电即失
* 数据库（jdbc），io文件持久化（浪费资源）

#### 1.3 持久层

Dao层，Service层，Controller层

dao：data access object

* 完成持久化工作的代码块
* 层界限很明显



#### 1.4 为什么需要MyBatis？

* 方便，
* 传统的JDBC代码太复杂了，简化。框架，自动化
* 技术没有高低之分
* 优点：
  * 简单易学
  * 灵活
  * sql和代码分离
  * 提供映射标签
  * 提供对象关系映射标签
  * 提供xml标签

**最重要一点**！：**使用的人多**

spring springMVC SpringBoot

### 2、第一个MyBatis程序

思路：搭建环境 - 》 导入MyBatis -》

#### 1.环境

```
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>


    <!--父工程-->
    <groupId>com.cui</groupId>
    <artifactId>MyBatis-Demo01</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <!-- https://mvnrepository.com/artifact/org.mybatis/mybatis -->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.6</version>
        </dependency>
        <!-- https://mvnrepository.com/artifact/com.mysql/mysql-connector-j -->
        <dependency>
            <groupId>com.mysql</groupId>
            <artifactId>mysql-connector-j</artifactId>
            <version>8.3.0</version>
        </dependency>
        <!-- https://mvnrepository.com/artifact/junit/junit -->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.1</version>
            <scope>test</scope>
        </dependency>



    </dependencies>


    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>



</project>
```



#### 2.创建模块 依赖放在父项目下

* 编写mybatis核心文件

  ```xml
  <?xml version="1.0" encoding="UTF-8" ?>
  <!DOCTYPE configuration
          PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
          "https://mybatis.org/dtd/mybatis-3-config.dtd">
  <!--mybatis核心配置文件-->
  <configuration>
      <environments default="development">
          <environment id="development">
              <transactionManager type="JDBC"/>
  <!--            默认使用jdbc事物管理-->
              <dataSource type="POOLED">
                  <property name="driver" value="com.mysql.jdbc.Driver"/>
                  <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=true&amp;useUnicode=true&amp;characterEncoding=UTF-8"/>
                  <property name="username" value="root"/>
                  <property name="password" value="cby20151304219"/>
              </dataSource>
          </environment>
      </environments>
  </configuration>
  ```

  

* 编写工具类

  ```
  package com.cui.utils;/*
   *com.cui.utils
   *Dell
   *2024 2024/3/5 16:38
   */
  
  import org.apache.ibatis.io.Resources;
  import org.apache.ibatis.session.SqlSession;
  import org.apache.ibatis.session.SqlSessionFactory;
  import org.apache.ibatis.session.SqlSessionFactoryBuilder;
  
  import java.io.IOException;
  import java.io.InputStream;
  
  public class MyBatisUtils {
      private static final SqlSessionFactory sqlSessionFactory;
      static {
          String resource = "org/mybatis/example/mybatis-config.xml";
          InputStream inputStream = null;
          try {
              inputStream = Resources.getResourceAsStream(resource);
          } catch (IOException e) {
              throw new RuntimeException(e);
          }
          sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
      }
      // 有了工厂类即可创建对象
      // SqlSession完全包含了面向数据库执行SQL命令所需的所有方法
  
      public static SqlSession getSqlSession(){
          return sqlSessionFactory.openSession();
      }
  
  }
  
  ```

* 编写代码

  * Dao接口

    ```java
    public interface UserDao {
        List<User> getUserList();
    }
    
    ```

  * 接口实现类由UserDaoImpl变为mapper配置文件

    ```xml
    <?xml version="1.0" encoding="UTF-8" ?>
    <!DOCTYPE mapper
            PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
            "https://mybatis.org/dtd/mybatis-3-mapper.dtd">
    <!--namespace绑定一个对应的DAO/Mapper接口-->
    <mapper namespace="com.cui.dao.UserDao">
    
        <!-- id对应方法名字-->
        <select id="getUserList" resultType="com.cui.pojo.User">
            select * from mybatis.user
        </select>
    </mapper>
    ```

* 编写测试类




遇到的问题：

1、配置文件没有注册mapper

2、绑定接口错误

3、方法名不对

5、maven导出资源文件问题



### 3、CRUD

![image-20240315191225481](image-20240315191225481.png) 

#### 1、namespace

namespace中名字要和接口类对应

#### 2、select

查询选择语句

* id：接口类namespace中的方法名
* resultType：Sql语句执行的返回值
* parameterType：参数类型

```xml
 <!-- id对应方法名字-->
    <select id="getUserList" resultType="com.cui.pojo.User">
        select * from mybatis.user
    </select>

    <select id="getUserById" parameterType="int" resultType="com.cui.pojo.User" >
        select * from mybatis.user where id = #{id}
    </select>

<!--    对象中的属性可以直接取出来-->
    <insert id="addUser" parameterType="com.cui.pojo.User" >
        insert into mybatis.user (id, name, pwd) values
        (#{id},#{name},#{pwd})
    </insert>
    
    <update id="updateUser" parameterType="com.cui.pojo.User">
        update mybatis.user
            set name = #{name},
                pwd = #{pwd}
        where id = #{id};
    </update>
```



#### 5、错误

* 

#### 6、使用map传参

基本类型可以不加类型，

多个参数需要msp或者 **注解**

![image-20240319150456711](image-20240319150456711.png) 



#### 7、思考 sql的注入问题？



```java

```



### 4、配置解析

#### 1、核心配置文件

* mybatisconfig.xml

  <img src="image-20240315203228734.png" alt="image-20240315203228734" style="zoom:50%;" /> 



#### 2、环江配置（environments）

可以配置成适用多种环境

每个实例只选择一种

MyBatis默认事务管理器是jdbc 连接池是pooled

#### 3、属性（properties）

可以通过properties属性来引用配置文件

这些属性可以在外部进行配置，并可以进行动态替换。你既可以在典型的 Java 属性文件中配置这些属性，也可以在 properties 元素的子元素中设置。【db.properties】

```properties
编写配置文件 
driver = com.mysql.jdbc.Driver
url = jdbc:mysql://localhost:3306/mybatis?useSSL=true&amp;useUnicode=true&amp;characterEncoding=UTF-8
username = root
password = cby20151304219
```

![image-20240319162333990](image-20240319162333990.png)

xml需要遵循一定顺序

#### 4、别名（typeAliases）

类型别名可为 Java 类型设置一个缩写名字。 它仅用于 XML 配置，意在降低冗余的全限定类名书写。

```xml
 <typeAliases>
        <typeAlias type="com.cui.pojo.User" alias="User"/>
        <!--可以给实体类起别名-->

        <package name="com.cui.pojo"/>
        <!--扫描实体类的包 默认别名就是这个类的类名 首字母小写 也可以使用大写-->
        <!--这里User映射为 user-->

        <!--实体类较少用第一种，较多用第二种-->
        <!--实体类可以加注解 则会优先使用注解的别名-->
    </typeAliases>
```



#### 5、设置（settings）



![image-20240319164608618](image-20240319164608618.png)

命名 ： 数据库把命名转为小写 因此常用下划线分割

![image-20240319164448471](image-20240319164448471.png)

打印日志

![image-20240319164541100](image-20240319164541100.png)

#### 6、其他配置

插件

![image-20240319164814606](image-20240319164814606.png)

#### 7、映射器（mappers）

MapperRegister

![image-20240319164930253](image-20240319164930253.png)

##### 方式一：

```xml
<mappers>
        <mapper resource="com/cui/dao/UserMapper.xml"/>
    </mappers>
```

##### 方式二：

通过class文件绑定注册

```xml
<mappers>
        <!--<mapper resource="com/cui/dao/UserMapper.xml"/>-->
        <mapper class="com.cui.dao.UserMapper"/>
    </mappers>
```

注意点：

* 接口和mapper配置文件必须同名
* 接口和mapper必须在同一个包下

##### 方式三：

使用包扫描

和方式二注意点一样

```xml
<mappers>
        <!--<mapper resource="com/cui/dao/UserMapper.xml"/>-->
        <!--<mapper class="com.cui.dao.UserMapper"/>-->
        <package name="com.cui.dao"/>
    </mappers>
```



练习：

* 外部引入配置文件
* 实体类别名



#### 8、生命周期和作用域

是至关重要的，错误使用会导致严重问题

程序执行

![image-20240319170247349](image-20240319170247349.png)



**SqlSessionFactoryBuilder：**

* 一旦创建SqlSessionFactory就不再需要SqlSessionFactoryBuilder
* 局部变量

**SqlSessionFactory**

* 可以理解为数据库连接池
* SqlSessionFactory一旦创建就不应丢弃或重新创建
* 因此最佳作用域就是全局作用域
* 最简单就是使用单例模式或静态单例模式

**SqlSession**

* 连接到数据库的请求
* 用完应及时关闭，实例是线程不安全的

![image-20240319170851069](image-20240319170851069.png)



### 5、解决属性名和字段名不一致的问题



#### 1、问题

![image-20240319172339732](image-20240319172339732.png)

#### 解决方式 

* 起别名

  ```sql
  select userpwd as pwd from ...
  ```

#### 2、resultMap

修改mapper.xml中resultType为 ResultMap

结果集映射

```
sql: id name pwd
class : id name password
```

![image-20240319173547886](image-20240319173547886.png)





## 6、日志

#### 6.1 日志工厂

如果数据库操作出现异常，需要排错，日志即是最好的助手

曾经 sout debug

现在：日志工厂

![image-20240319203724415](image-20240319203724415.png)

* SLF4J
* LOG4J【掌握】
* LOG4J2
* JDK_LOGGING
* STDOUT_LOGGING【掌握】【默认的】
* NO_LOGGING

在MyBatis中具体哪个日志实现要看设置

**STDOUT_LOGGING**

在maybatis核心配置文件中配置日志

```xml
<settings>
        <setting name="logImpl" value="STDOUT_LOGGING"/>
    </settings>

```



![image-20240319204510127](image-20240319204510127.png)



#### 6.2、log4j

什么是log4j

* 是apache开源项目 可以控制日志输出位置为文件控制台或GUI组件
* 控制日志输出格式
* 定义日志级别
* 通过配置文件配置不需要修改代码

1.导log4j的包

```xml
<!-- https://mvnrepository.com/artifact/org.apache.logging.log4j/log4j-core -->
<dependency>
    <groupId>org.apache.logging.log4j</groupId>
    <artifactId>log4j-core</artifactId>
    <version>2.17.1</version>
</dependency>

```

2. log4j.properties

```properties
#将等级为DEBUG的日志信息输出到console和file这两个目的地，console和file的定义在下面的代码
log4j.rootLogger=DEBUG,console,file

#控制台输出的相关设置
log4j.appender.console = org.apache.log4j.ConsoleAppender
log4j.appender.console.Target = System.out
log4j.appender.console.Threshold=DEBUG
log4j.appender.console.layout = org.apache.log4j.PatternLayout
log4j.appender.console.layout.ConversionPattern=[%c]-%m%n

#文件输出的相关设置
log4j.appender.file = org.apache.log4j.RollingFileAppender
log4j.appender.file.File=./log/logFile.log
log4j.appender.file.MaxFileSize=10mb
log4j.appender.file.Threshold=DEBUG
log4j.appender.file.layout=org.apache.log4j.PatternLayout
log4j.appender.file.layout.ConversionPattern=[%p][%d{yy-MM-dd}][%c]%m%n

#日志输出级别
log4j.logger.org.mybatis=DEBUG
log4j.logger.java.sql=DEBUG
log4j.logger.java.sql.Statement=DEBUG
log4j.logger.java.sql.ResultSet=DEBUG
log4j.logger.java.sql.PreparedStatement=DEBUG
```

![image-20240319205920866](image-20240319205920866.png)



##### 简单使用

1.导入apache的log4j的包



## 7、分页

**思考：为什么分页？**

* 减少数据处理量
* 效率高 更可控



**使用limit分页**

```sql
select * from user limit 0,2
```

a,b  从a开始 间隔是b（查b个）

a 从0到a

**使用MyBatis实现分页**

1.接口

2.mapper.xml

3.测试









